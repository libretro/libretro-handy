#include "libretro.h"
#include "libretro_core_options.h"

#include <string/stdstring.h>
#include <file/file_path.h>
#include <streams/file_stream.h>

#include "handy.h"

#ifdef _3DS
extern "C" void* linearMemAlign(size_t size, size_t alignment);
extern "C" void linearFree(void* mem);
#endif

static retro_log_printf_t log_cb;
static retro_video_refresh_t video_cb;
static retro_audio_sample_batch_t audio_batch_cb;
static retro_environment_t environ_cb;
static retro_input_poll_t input_poll_cb;
static retro_input_state_t input_state_cb;

static CSystem *lynx = NULL;

static int16_t *soundBuffer = NULL;

#define RETRO_LYNX_WIDTH  160
#define RETRO_LYNX_HEIGHT 102

/* Note: Set 75Hz here to reflect the nominal
 * maximum of the Lynx hardware; actual 'core
 * options' default is 60Hz */
static uint16_t retro_refresh_rate  = 75;
static ULONG retro_cycles_per_frame = (HANDY_SYSTEM_FREQ / 75);

static bool retro_refresh_rate_updated = false;

// core options
static uint8_t lynx_rot         = MIKIE_NO_ROTATE;
static uint8_t lynx_width       = RETRO_LYNX_WIDTH;
static uint8_t lynx_height      = RETRO_LYNX_HEIGHT;
static uint8_t lynx_width_next  = RETRO_LYNX_WIDTH;
static uint8_t lynx_height_next = RETRO_LYNX_HEIGHT;

typedef enum
{
   ROTATION_PENDING_NONE = 0,
   ROTATION_PENDING_CORE,
   ROTATION_PENDING_FRONTEND
} lynx_rotation_pending_t;

static lynx_rotation_pending_t lynx_rotation_pending = ROTATION_PENDING_NONE;
bool lynx_rotation_button_down = false;

static int RETRO_PIX_BYTES = 2;
#if defined(FRONTEND_SUPPORTS_RGB565)
static int RETRO_PIX_DEPTH = 16;
#else
static int RETRO_PIX_DEPTH = 15;
#endif

static uint8_t *framebuffer = NULL;

static bool frame_available   = false;
static bool initialized       = false;
static bool video_out_enabled = false;

struct map { unsigned retro; unsigned lynx; };

static map btn_map_no_rot[] = {
   { RETRO_DEVICE_ID_JOYPAD_A, BUTTON_A },
   { RETRO_DEVICE_ID_JOYPAD_B, BUTTON_B },
   { RETRO_DEVICE_ID_JOYPAD_RIGHT, BUTTON_RIGHT },
   { RETRO_DEVICE_ID_JOYPAD_LEFT, BUTTON_LEFT },
   { RETRO_DEVICE_ID_JOYPAD_UP, BUTTON_UP },
   { RETRO_DEVICE_ID_JOYPAD_DOWN, BUTTON_DOWN },
   { RETRO_DEVICE_ID_JOYPAD_L, BUTTON_OPT1 },
   { RETRO_DEVICE_ID_JOYPAD_R, BUTTON_OPT2 },
   { RETRO_DEVICE_ID_JOYPAD_START, BUTTON_PAUSE },
};

static map btn_map_rot_270[] = {
   { RETRO_DEVICE_ID_JOYPAD_A, BUTTON_A },
   { RETRO_DEVICE_ID_JOYPAD_B, BUTTON_B },
   { RETRO_DEVICE_ID_JOYPAD_RIGHT, BUTTON_UP },
   { RETRO_DEVICE_ID_JOYPAD_LEFT, BUTTON_DOWN },
   { RETRO_DEVICE_ID_JOYPAD_UP, BUTTON_LEFT },
   { RETRO_DEVICE_ID_JOYPAD_DOWN, BUTTON_RIGHT },
   { RETRO_DEVICE_ID_JOYPAD_L, BUTTON_OPT1 },
   { RETRO_DEVICE_ID_JOYPAD_R, BUTTON_OPT2 },
   { RETRO_DEVICE_ID_JOYPAD_START, BUTTON_PAUSE },
};

static map btn_map_rot_90[] = {
   { RETRO_DEVICE_ID_JOYPAD_A, BUTTON_A },
   { RETRO_DEVICE_ID_JOYPAD_B, BUTTON_B },
   { RETRO_DEVICE_ID_JOYPAD_RIGHT, BUTTON_DOWN },
   { RETRO_DEVICE_ID_JOYPAD_LEFT, BUTTON_UP },
   { RETRO_DEVICE_ID_JOYPAD_UP, BUTTON_RIGHT },
   { RETRO_DEVICE_ID_JOYPAD_DOWN, BUTTON_LEFT },
   { RETRO_DEVICE_ID_JOYPAD_L, BUTTON_OPT1 },
   { RETRO_DEVICE_ID_JOYPAD_R, BUTTON_OPT2 },
   { RETRO_DEVICE_ID_JOYPAD_START, BUTTON_PAUSE },
};

static map* btn_map;

static bool libretro_supports_input_bitmasks;
static bool select_button;

/* Frameskipping Support START */

static unsigned frameskip_type             = 0;
static unsigned frameskip_threshold        = 0;
static uint16_t frameskip_counter          = 0;

static bool retro_audio_buff_active        = false;
static unsigned retro_audio_buff_occupancy = 0;
static bool retro_audio_buff_underrun      = false;
/* Maximum number of consecutive frames that
 * can be skipped */
#define FRAMESKIP_MAX 60

static unsigned audio_latency              = 0;
static bool update_audio_latency           = false;

static bool libretro_supports_option_categories = false;

static void retro_audio_buff_status_cb(
      bool active, unsigned occupancy, bool underrun_likely)
{
   retro_audio_buff_active    = active;
   retro_audio_buff_occupancy = occupancy;
   retro_audio_buff_underrun  = underrun_likely;
}

static void init_frameskip(void)
{
   if (frameskip_type > 0)
   {
      struct retro_audio_buffer_status_callback buf_status_cb;

      buf_status_cb.callback = retro_audio_buff_status_cb;
      if (!environ_cb(RETRO_ENVIRONMENT_SET_AUDIO_BUFFER_STATUS_CALLBACK,
            &buf_status_cb))
      {
         handy_log(RETRO_LOG_WARN,
               "Frameskip disabled - frontend does not support audio buffer status monitoring.\n");

         retro_audio_buff_active    = false;
         retro_audio_buff_occupancy = 0;
         retro_audio_buff_underrun  = false;
         audio_latency              = 0;
      }
      else
      {
         /* Frameskip is enabled - increase frontend
          * audio latency to minimise potential
          * buffer underruns
          * > Note: The core can run at a variety of
          *   (frontend) display refresh rates, and
          *   internally frames can be generated at
          *   any rate from 0 to 75Hz (possibly 79Hz).
          *   This makes it difficult to determine
          *   an appropriate audio latency level; for
          *   simplicity, assume that we are running
          *   at the default display refresh rate of
          *   60Hz (ultimately this will translate to
          *   a latency of 128ms, which should be
          *   sufficient in all cases) */
         float frame_time_msec = 1000.0f / 60.0f;

         /* Set latency to 6x current frame time */
         audio_latency = (unsigned)((6.0f * frame_time_msec) + 0.5f);

         /* ...then round up to nearest multiple of 32 */
         audio_latency = (audio_latency + 0x1F) & ~0x1F;
      }
   }
   else
   {
      environ_cb(RETRO_ENVIRONMENT_SET_AUDIO_BUFFER_STATUS_CALLBACK, NULL);
      audio_latency = 0;
   }

   update_audio_latency = true;
}

/* Frameskipping Support END */

void handy_log(enum retro_log_level level, const char *format, ...)
{
   char msg[512];
   va_list ap;

   msg[0] = '\0';

   if (string_is_empty(format))
      return;

   va_start(ap, format);
   vsprintf(msg, format, ap);
   va_end(ap);

   if (log_cb)
      log_cb(level, "[Handy] %s", msg);
   else
      fprintf((level == RETRO_LOG_ERROR) ? stderr : stdout,
            "[Handy] %s", msg);
}

static void check_color_depth(void)
{
   if (RETRO_PIX_DEPTH == 24)
   {
      /* If XRGB8888 support is compiled in, attempt to
       * set 24 bit colour depth */
#if defined(FRONTEND_SUPPORTS_XRGB8888)
      enum retro_pixel_format rgb888 = RETRO_PIXEL_FORMAT_XRGB8888;

      if(!environ_cb(RETRO_ENVIRONMENT_SET_PIXEL_FORMAT, &rgb888))
      {
         handy_log(RETRO_LOG_ERROR,
               "Pixel format XRGB8888 not supported by platform.\n");

         RETRO_PIX_BYTES = 2;
#if defined(FRONTEND_SUPPORTS_RGB565)
         RETRO_PIX_DEPTH = 16;
#else
         RETRO_PIX_DEPTH = 15;
#endif
      }
#else
      /* XRGB8888 support is *not* compiled in.
       * If we reach this point, then unforeseen
       * errors have occurred - just 'reset' colour
       * depth to 16 bit */
      RETRO_PIX_BYTES = 2;
#if defined(FRONTEND_SUPPORTS_RGB565)
      RETRO_PIX_DEPTH = 16;
#else
      RETRO_PIX_DEPTH = 15;
#endif
#endif
   }

   if (RETRO_PIX_BYTES == 2)
   {
#if defined(FRONTEND_SUPPORTS_RGB565)
      enum retro_pixel_format rgb565 = RETRO_PIXEL_FORMAT_RGB565;

      if (environ_cb(RETRO_ENVIRONMENT_SET_PIXEL_FORMAT, &rgb565))
      {
         handy_log(RETRO_LOG_INFO,
               "Frontend supports RGB565 - will use that instead of XRGB1555.\n");

         RETRO_PIX_DEPTH = 16;
      }
#else
      enum retro_pixel_format rgb555 = RETRO_PIXEL_FORMAT_0RGB1555;

      if (environ_cb(RETRO_ENVIRONMENT_SET_PIXEL_FORMAT, &rgb555))
      {
         handy_log(RETRO_LOG_INFO,
               "Using default 0RGB1555 pixel format.\n");

         RETRO_PIX_DEPTH = 15;
      }
#endif
   }
}

unsigned retro_api_version(void)
{
   return RETRO_API_VERSION;
}

static void update_geometry(void)
{
   struct retro_system_av_info info;
   retro_get_system_av_info(&info);
   environ_cb(RETRO_ENVIRONMENT_SET_GEOMETRY, &info);
}

static void update_timing(void)
{
   struct retro_system_av_info info;
   retro_get_system_av_info(&info);
   environ_cb(RETRO_ENVIRONMENT_SET_SYSTEM_AV_INFO, &info);
}

static void lynx_rotate(void);

static UBYTE* lynx_display_callback(ULONG objref)
{
   if(!video_out_enabled)
      return (UBYTE*)framebuffer;

   /* lynx_display_callback() may be called multiple
    * times per retro_run(). Ensure that video_cb()
    * is only called once per retro_run(). */
   if (!frame_available)
   {
      /* Check whether current frame has a different
       * rotation from the previous one; if so,
       * notify the frontend before drawing it */
      if (!gSkipFrame &&
          (lynx_rotation_pending == ROTATION_PENDING_FRONTEND))
      {
         lynx_rotation_pending = ROTATION_PENDING_NONE;
         lynx_width            = lynx_width_next;
         lynx_height           = lynx_height_next;
         update_geometry();
      }

      video_cb((bool)gSkipFrame ? NULL : framebuffer,
            lynx_width, lynx_height,
            RETRO_LYNX_WIDTH * RETRO_PIX_BYTES);

      /* Check whether the next frame should be
       * rendered with a change in rotation */
      if (lynx_rotation_pending == ROTATION_PENDING_CORE)
      {
         lynx_rotation_pending = ROTATION_PENDING_FRONTEND;
         /* An annoyance: lynx_rotate() ends up calling
          * lynx_display_callback(), so to avoid infinite
          * circular recursion we must temporarily disable
          * lynx_display_callback()... */
         video_out_enabled = false;
         lynx_rotate();
         video_out_enabled = true;
      }

      frame_available = true;
      /* Must unset gSkipFrame here since the next
       * frame may be (partially) drawn before the
       * current retro_run() returns, and we will not
       * know if this frame is needed until the *next*
       * call of retro_run()... */
      gSkipFrame = 0;
   }

   return (UBYTE*)framebuffer;
}

static void lynx_rotate(void)
{
   if (!lynx)
      return;

   switch (lynx_rot)
   {
      default:
         lynx_rot = MIKIE_NO_ROTATE;
         // intentional fall-through

      case MIKIE_NO_ROTATE:
         lynx_width_next  = RETRO_LYNX_WIDTH;
         lynx_height_next = RETRO_LYNX_HEIGHT;
         btn_map          = btn_map_no_rot;
         break;

      case MIKIE_ROTATE_R:
         lynx_width_next  = RETRO_LYNX_HEIGHT;
         lynx_height_next = RETRO_LYNX_WIDTH;
         btn_map          = btn_map_rot_90;
         break;

      case MIKIE_ROTATE_L:
         lynx_width_next  = RETRO_LYNX_HEIGHT;
         lynx_height_next = RETRO_LYNX_WIDTH;
         btn_map          = btn_map_rot_270;
         break;
   }

   switch (RETRO_PIX_DEPTH)
   {
      case 15:
         lynx->DisplaySetAttributes(lynx_rot,
               MIKIE_PIXEL_FORMAT_16BPP_555,
               RETRO_LYNX_WIDTH * 2,
               lynx_display_callback, (ULONG)0);
         break;
#if defined(ABGR1555)
      case 16:
         lynx->DisplaySetAttributes(lynx_rot,
               MIKIE_PIXEL_FORMAT_16BPP_BGR555,
               RETRO_LYNX_WIDTH * 2,
               lynx_display_callback, (ULONG)0);
         break;
#else
      case 16:
         lynx->DisplaySetAttributes(lynx_rot,
               MIKIE_PIXEL_FORMAT_16BPP_565,
               RETRO_LYNX_WIDTH * 2,
               lynx_display_callback, (ULONG)0);
         break;
#endif
      case 24:
         lynx->DisplaySetAttributes(lynx_rot,
               MIKIE_PIXEL_FORMAT_32BPP,
               RETRO_LYNX_WIDTH * 4,
               lynx_display_callback, (ULONG)0);
         break;
      default:
         lynx->DisplaySetAttributes(lynx_rot,
               MIKIE_PIXEL_FORMAT_32BPP,
               RETRO_LYNX_WIDTH * 4,
               lynx_display_callback, (ULONG)0);
         break;
   }
}

static void check_variables(void)
{
   struct retro_variable var = {0};
   unsigned old_lynx_rot;
   unsigned old_frameskip_type;
   uint16_t old_retro_refresh_rate;

   old_lynx_rot = lynx_rot;
   lynx_rot     = MIKIE_NO_ROTATE;
   var.key      = "handy_rot";
   var.value    = NULL;

   if (environ_cb(RETRO_ENVIRONMENT_GET_VARIABLE, &var) && var.value)
   {
      if (strcmp(var.value, "None") == 0)
         lynx_rot = MIKIE_NO_ROTATE;
      else if (strcmp(var.value, "90") == 0)
         lynx_rot = MIKIE_ROTATE_R; 
      else if (strcmp(var.value, "270") == 0)
         lynx_rot = MIKIE_ROTATE_L;

      if (initialized &&
          (lynx_rot != old_lynx_rot))
         lynx_rotation_pending = ROTATION_PENDING_CORE;
   }

#if defined(FRONTEND_SUPPORTS_XRGB8888)
   /* Only read colour depth setting on first run */
   if (!initialized)
   {
      var.key = "handy_gfx_colors";
      var.value = NULL;

      /* Set 16bpp by default */
      RETRO_PIX_BYTES = 2;
      RETRO_PIX_DEPTH = 16;

      if (environ_cb(RETRO_ENVIRONMENT_GET_VARIABLE, &var) && var.value)
         if (strcmp(var.value, "24bit") == 0)
         {
            RETRO_PIX_BYTES = 4;
            RETRO_PIX_DEPTH = 24;
         }
   }
#endif

   old_frameskip_type = frameskip_type;
   frameskip_type     = 0;
   var.key            = "handy_frameskip";
   var.value          = NULL;

   if (environ_cb(RETRO_ENVIRONMENT_GET_VARIABLE, &var) && var.value)
   {
      if (!strcmp(var.value, "auto"))
         frameskip_type = 1;
      else if (!strcmp(var.value, "manual"))
         frameskip_type = 2;
   }

   frameskip_threshold = 33;
   var.key             = "handy_frameskip_threshold";
   var.value           = NULL;

   if (environ_cb(RETRO_ENVIRONMENT_GET_VARIABLE, &var) && var.value)
      frameskip_threshold = strtol(var.value, NULL, 10);

   /* Reinitialise frameskipping, if required */
   if ((frameskip_type != old_frameskip_type) && initialized)
      init_frameskip();

   old_retro_refresh_rate = retro_refresh_rate;
   retro_refresh_rate     = 75;
   var.key                = "handy_refresh_rate";
   var.value              = NULL;

   if (environ_cb(RETRO_ENVIRONMENT_GET_VARIABLE, &var) && var.value)
   {
      retro_refresh_rate = strtol(var.value, NULL, 10);
      retro_refresh_rate = (retro_refresh_rate < 50)  ? 50 : retro_refresh_rate;
      retro_refresh_rate = (retro_refresh_rate > 120) ? 50 : retro_refresh_rate;
   }

   retro_cycles_per_frame = (HANDY_SYSTEM_FREQ / retro_refresh_rate);

   /* Notify frontend if timing has changed */
   if (initialized &&
       (retro_refresh_rate != old_retro_refresh_rate))
      retro_refresh_rate_updated = true;
}

void retro_init(void)
{
   struct retro_log_callback log;
   uint64_t serialization_quirks = RETRO_SERIALIZATION_QUIRK_SINGLE_SESSION;
   environ_cb(RETRO_ENVIRONMENT_GET_LOG_INTERFACE, &log);
   if (log.log)
      log_cb = log.log;

   environ_cb(RETRO_ENVIRONMENT_SET_SERIALIZATION_QUIRKS,
         &serialization_quirks);

   if (environ_cb(RETRO_ENVIRONMENT_GET_INPUT_BITMASKS, NULL))
      libretro_supports_input_bitmasks = true;

   frameskip_type             = 0;
   frameskip_threshold        = 0;
   frameskip_counter          = 0;
   retro_audio_buff_active    = false;
   retro_audio_buff_occupancy = 0;
   retro_audio_buff_underrun  = false;
   audio_latency              = 0;
   update_audio_latency       = false;
}

void retro_reset(void)
{
   if(lynx)
   {
      lynx->SaveEEPROM();
      lynx->Reset();
   }
}

void retro_deinit(void)
{
   if(lynx)
   {
      lynx->SaveEEPROM();
      delete lynx;
      lynx=0;
   }

   if (framebuffer)
#if defined(_3DS)
      linearFree(framebuffer);
#else
      free(framebuffer);
#endif
   framebuffer = NULL;

   libretro_supports_input_bitmasks = false;
   lynx_rotation_pending            = ROTATION_PENDING_NONE;
   lynx_rotation_button_down        = false;
   lynx_rot                         = MIKIE_NO_ROTATE;
   lynx_width                       = RETRO_LYNX_WIDTH;
   lynx_height                      = RETRO_LYNX_HEIGHT;
   lynx_width_next                  = RETRO_LYNX_WIDTH;
   lynx_height_next                 = RETRO_LYNX_HEIGHT;
   initialized                      = false;
   video_out_enabled                = false;
}

void retro_set_environment(retro_environment_t cb)
{
   struct retro_vfs_interface_info vfs_iface_info;
   static const struct retro_system_content_info_override content_overrides[] = {
      {
         "lnx|o", /* extensions */
         false,   /* need_fullpath */
         false    /* persistent_data */
      },
      { NULL, false, false }
   };

   environ_cb = cb;

   libretro_set_core_options(environ_cb,
         &libretro_supports_option_categories);

   vfs_iface_info.required_interface_version = 1;
   vfs_iface_info.iface                      = NULL;
   if (environ_cb(RETRO_ENVIRONMENT_GET_VFS_INTERFACE, &vfs_iface_info))
      filestream_vfs_init(&vfs_iface_info);

   environ_cb(RETRO_ENVIRONMENT_SET_CONTENT_INFO_OVERRIDE,
         (void*)content_overrides);
}

void retro_set_audio_sample(retro_audio_sample_t cb)
{
}

void retro_set_audio_sample_batch(retro_audio_sample_batch_t cb)
{
   audio_batch_cb = cb;
}

void retro_set_input_poll(retro_input_poll_t cb)
{
   input_poll_cb = cb;
}

void retro_set_input_state(retro_input_state_t cb)
{
   input_state_cb = cb;
}

void retro_set_video_refresh(retro_video_refresh_t cb)
{
   video_cb = cb;
}

void retro_set_controller_port_device(unsigned, unsigned) { }

void retro_get_system_info(struct retro_system_info *info)
{
   memset(info, 0, sizeof(*info));
   info->library_name     = "Handy";
#ifndef GIT_VERSION
#define GIT_VERSION ""
#endif
   info->library_version  = HANDYVER GIT_VERSION;
   info->need_fullpath    = true;
   info->valid_extensions = "lnx|o";
   info->block_extract = 0;
}

void retro_get_system_av_info(struct retro_system_av_info *info)
{
   memset(info, 0, sizeof(*info));

   info->timing.fps            = (double)retro_refresh_rate;
   info->timing.sample_rate    = (double)HANDY_AUDIO_SAMPLE_FREQ;

   info->geometry.base_width   = lynx_width;
   info->geometry.base_height  = lynx_height;
   info->geometry.max_width    = RETRO_LYNX_WIDTH;
   info->geometry.max_height   = RETRO_LYNX_WIDTH;
   info->geometry.aspect_ratio = (float)lynx_width / (float)lynx_height;
}

void retro_run(void)
{
   unsigned i, res = 0;
   bool updated = false;
   if (environ_cb(RETRO_ENVIRONMENT_GET_VARIABLE_UPDATE, &updated) && updated)
      check_variables();

   input_poll_cb();
   if (libretro_supports_input_bitmasks)
   {
      int16_t ret = input_state_cb(0, RETRO_DEVICE_JOYPAD, 0,
            RETRO_DEVICE_ID_JOYPAD_MASK);
      for (i = 0; i < sizeof(btn_map_no_rot) / sizeof(map); i++)
         res |= ret & (1 << btn_map[i].retro) ? (btn_map[i].lynx) : 0;
      select_button = ret & (1 << RETRO_DEVICE_ID_JOYPAD_SELECT);
   }
   else
   {
      for (i = 0; i < sizeof(btn_map_no_rot) / sizeof(map); ++i)
         res |= input_state_cb(0, RETRO_DEVICE_JOYPAD, 0,
               btn_map[i].retro) ? btn_map[i].lynx : 0;
      select_button = input_state_cb(0, RETRO_DEVICE_JOYPAD, 0,
            RETRO_DEVICE_ID_JOYPAD_SELECT);
   }
   lynx->SetButtonData(res);

   if (select_button && !lynx_rotation_button_down)
   {
      lynx_rot++;
      lynx_rotation_pending = ROTATION_PENDING_CORE;
   }
   lynx_rotation_button_down = select_button;

   /* Check whether current frame should be skipped
    * > Note: if gSkipFrame is already set, then it
    *   means a frameskip was requested on the last
    *   call of retro_run() but no end of frame
    *   event occurred. We must therefore keep
    *   gSkipFrame latched on, since any partial frame
    *   from the previous retro_run() will be incomplete */
   if ((frameskip_type > 0) &&
       !gSkipFrame &&
       retro_audio_buff_active)
   {
      switch (frameskip_type)
      {
         case 1: /* auto */
            gSkipFrame = retro_audio_buff_underrun ? 1 : 0;
            break;
         case 2: /* manual */
            gSkipFrame = (retro_audio_buff_occupancy < frameskip_threshold) ? 1 : 0;
            break;
         default:
            gSkipFrame = 0;
            break;
      }

      if (!gSkipFrame ||
          (frameskip_counter >= FRAMESKIP_MAX))
      {
         gSkipFrame        = 0;
         frameskip_counter = 0;
      }
      else
         frameskip_counter++;
   }

   /* If frameskip settings have changed, update
    * frontend audio latency */
   if (update_audio_latency)
   {
      environ_cb(RETRO_ENVIRONMENT_SET_MINIMUM_AUDIO_LATENCY,
            &audio_latency);
      update_audio_latency = false;
   }

   if (retro_refresh_rate_updated)
   {
      update_timing();
      retro_refresh_rate_updated = false;
   }

   gLastRunCycleCount = gSystemCycleCount;
   frame_available = false;

   while (gSystemCycleCount - gLastRunCycleCount < retro_cycles_per_frame)
      lynx->Update();

   /* If no end of frame event was produced on this
    * run, upload NULL */
   if (!frame_available)
      video_cb(NULL, lynx_width, lynx_height,
            RETRO_LYNX_WIDTH * RETRO_PIX_BYTES);

   lynx->FetchAudioSamples();

   /* Divide gAudioBufferPointer by number of channels */
   audio_batch_cb(soundBuffer, gAudioBufferPointer >> 1);
   gAudioBufferPointer = 0;
}

size_t retro_serialize_size(void)
{
   if(!lynx)
      return 0;

   return lynx->ContextSize();
}

bool retro_serialize(void *data, size_t size)
{
   LSS_FILE fp;
   if(!lynx)
      return false;

   fp.memptr      = (UBYTE *) data;
   fp.index       = 0;
   fp.index_limit = size;

   return lynx->ContextSave(&fp);
}

bool retro_unserialize(const void *data, size_t size)
{
   LSS_FILE fp;
   if(!lynx)
      return false;

   fp.memptr      = (UBYTE *) data;
   fp.index       = 0;
   fp.index_limit = size;

   return lynx->ContextLoad(&fp);
}

bool retro_load_game(const struct retro_game_info *info)
{
   const struct retro_game_info_ext *info_ext = NULL;
   const char *content_path                   = NULL;
   const UBYTE *content_data                  = NULL;
   size_t content_size                        = 0;
   const char *system_dir                     = NULL;
   const char *eeprom_dir                     = NULL;
   bool bios_found                            = false;
   char bios_file[PATH_MAX_LENGTH];
   char eeprom_file[PATH_MAX_LENGTH];

   static struct retro_input_descriptor desc[] = {
      { 0, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_LEFT,  "D-Pad Left" },
      { 0, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_UP,    "D-Pad Up" },
      { 0, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_DOWN,  "D-Pad Down" },
      { 0, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_RIGHT, "D-Pad Right" },
      { 0, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_B,     "B" },
      { 0, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_A,     "A" },
      { 0, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_L,     "Option 1" },
      { 0, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_R,     "Option 2" },
      { 0, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_START, "Pause" },
      { 0, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_SELECT, "Rotate screen" },

      { 0 },
   };

   bios_file[0]   = '\0';
   eeprom_file[0] = '\0';

   /* Allocate video buffer */
#if defined(_3DS)
   framebuffer = (uint8_t*)linearMemAlign(
         RETRO_LYNX_WIDTH * RETRO_LYNX_WIDTH * 4 * sizeof(uint8_t), 128);
#else
   framebuffer = (uint8_t*)calloc(1,
         RETRO_LYNX_WIDTH * RETRO_LYNX_WIDTH * 4 * sizeof(uint8_t));
#endif
   if (!framebuffer)
      return false;

   environ_cb(RETRO_ENVIRONMENT_SET_INPUT_DESCRIPTORS, desc);

   /* Get save directory */
   environ_cb(RETRO_ENVIRONMENT_GET_SAVE_DIRECTORY, &eeprom_dir);

   /* Attempt to fetch extended game info */
   if (environ_cb(RETRO_ENVIRONMENT_GET_GAME_INFO_EXT, &info_ext) &&
       info_ext->data && (info_ext->size > 0))
   {
      content_path = NULL;
      content_data = (const UBYTE *)info_ext->data;
      content_size = info_ext->size;

      /* EEPROM file is <save_dir>/<content_name>.eeprom */
      if (eeprom_dir)
      {
         fill_pathname_join(eeprom_file, eeprom_dir,
               info_ext->name, sizeof(eeprom_file));
         strlcat(eeprom_file, ".eeprom", sizeof(eeprom_file));
      }
   }
   else
   {
      /* No extended info - just pass content
       * path to emulator */
      const char *content_file = NULL;

      if (!info || string_is_empty(info->path))
         return false;

      content_path = info->path;
      content_data = NULL;
      content_size = 0;

      /* Use content file name to build EEPROM path */
      content_file = path_basename(content_path);
      if (eeprom_dir && !string_is_empty(content_file))
      {
         char *content_name = strdup(content_file);
         path_remove_extension(content_name);

         fill_pathname_join(eeprom_file, eeprom_dir,
               content_name, sizeof(eeprom_file));
         strlcat(eeprom_file, ".eeprom", sizeof(eeprom_file));

         free(content_name);
      }
   }

   /* Get bios path */
   if (environ_cb(RETRO_ENVIRONMENT_GET_SYSTEM_DIRECTORY, &system_dir) &&
         system_dir)
      fill_pathname_join(bios_file, system_dir,
            ROM_FILE, sizeof(bios_file));

   if (!string_is_empty(bios_file) &&
       path_is_valid(bios_file))
      bios_found = true;
   else
      handy_log(RETRO_LOG_WARN, "BIOS file missing: %s\n",
            string_is_empty(bios_file) ? ROM_FILE : bios_file);

   /* Initialise emulator */
   check_variables();
   check_color_depth();
   init_frameskip();

   if (lynx)
   {
      lynx->SaveEEPROM();
      delete lynx;
      lynx=0;
   }

   lynx          = new CSystem(content_path, content_data, content_size,
         bios_file, !bios_found, eeprom_file);
   gAudioEnabled = true;
   soundBuffer   = (int16_t *)&gAudioBuffer;
   btn_map       = btn_map_no_rot;

   /* Apply initial rotation
    * > Effect is immediate, so update actual
    *   lynx_width/lynx_height values here */
   lynx_rotate();
   lynx_width  = lynx_width_next;
   lynx_height = lynx_height_next;

   gSkipFrame        = 0;
   initialized       = true;
   video_out_enabled = true;

   return true;
}

bool retro_load_game_special(unsigned, const struct retro_game_info*, size_t)
{
   return false;
}

void retro_unload_game(void)
{
   initialized = false;
}

void retro_cheat_reset(void) { }
void retro_cheat_set(unsigned index, bool enabled, const char *code) { }

unsigned retro_get_region(void)
{
   return RETRO_REGION_NTSC;
}

void *retro_get_memory_data(unsigned type)
{
   if (lynx && type == RETRO_MEMORY_SYSTEM_RAM)
      return lynx->GetRamPointer();
   return NULL;
}

size_t retro_get_memory_size(unsigned type)
{
   if (type == RETRO_MEMORY_SYSTEM_RAM)
      return 1024 * 64;
   return 0;
}
