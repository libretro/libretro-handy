#include "libretro.h"
#include <string.h>
#include <fstream>
#include "handy.h"

static retro_log_printf_t log_cb;
static retro_video_refresh_t video_cb;
static retro_audio_sample_batch_t audio_batch_cb;
static retro_environment_t environ_cb;
static retro_input_poll_t input_poll_cb;
static retro_input_state_t input_state_cb;

static CSystem *lynx = NULL;

static int16_t *soundBuffer = NULL;


// core options
static uint8_t lynx_rot = MIKIE_NO_ROTATE;
static uint8_t lynx_width = 160;
static uint8_t lynx_height = 102;

static int RETRO_PIX_BYTES = 2;
static int RETRO_PIX_DEPTH = 15;


static uint8_t framebuffer[160*160*4];

static bool newFrame = false;
static bool initialized = false;

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

static bool update_video = false;

static void check_color_depth(void)
{
   if (RETRO_PIX_DEPTH == 24)
   {
      enum retro_pixel_format rgb888 = RETRO_PIXEL_FORMAT_XRGB8888;

      if(!environ_cb(RETRO_ENVIRONMENT_SET_PIXEL_FORMAT, &rgb888))
      {
         if(log_cb) log_cb(RETRO_LOG_ERROR, "Pixel format XRGB8888 not supported by platform.\n");

         RETRO_PIX_BYTES = 2;
         RETRO_PIX_DEPTH = 15;
      }
   }

   if (RETRO_PIX_BYTES == 2)
   {
#if defined(FRONTEND_SUPPORTS_RGB565)
      enum retro_pixel_format rgb565 = RETRO_PIXEL_FORMAT_RGB565;

      if (environ_cb(RETRO_ENVIRONMENT_SET_PIXEL_FORMAT, &rgb565))
      {
         if(log_cb) log_cb(RETRO_LOG_INFO, "Frontend supports RGB565 - will use that instead of XRGB1555.\n");

         RETRO_PIX_DEPTH = 16;
      }
#else
      enum retro_pixel_format rgb555 = RETRO_PIXEL_FORMAT_0RGB1555;

      if (environ_cb(RETRO_ENVIRONMENT_SET_PIXEL_FORMAT, &rgb555))
      {
         if(log_cb) log_cb(RETRO_LOG_INFO, "Using default 0RGB1555 pixel format.\n");

         RETRO_PIX_DEPTH = 15;
      }
#endif
   }
}

unsigned retro_api_version(void)
{
   return RETRO_API_VERSION;
}

static void update_geometry()
{
   struct retro_system_av_info info;

   retro_get_system_av_info(&info);
   environ_cb(RETRO_ENVIRONMENT_SET_GEOMETRY, &info);
}

static UBYTE* lynx_display_callback(ULONG objref)
{
   if(!initialized)
      return (UBYTE*)framebuffer;

   video_cb(framebuffer, lynx_width, lynx_height, 160*RETRO_PIX_BYTES);


   for(int total = 0; total < gAudioBufferPointer/4; )
      total += audio_batch_cb(soundBuffer + total*2, (gAudioBufferPointer/4) - total);
   gAudioBufferPointer = 0;


   newFrame = true;
   return (UBYTE*)framebuffer;
}

static void lynx_rotate()
{
   if(!lynx) return;

   switch(lynx_rot)
   {
   default:
      lynx_rot = MIKIE_NO_ROTATE;
      // intentional fall-through

   case MIKIE_NO_ROTATE:
      lynx_width = 160;
      lynx_height = 102;
      btn_map = btn_map_no_rot;
      break;

   case MIKIE_ROTATE_R:
      lynx_width = 102;
      lynx_height = 160;
      btn_map = btn_map_rot_90;
      break;

   case MIKIE_ROTATE_L:
      lynx_width = 102;
      lynx_height = 160;
      btn_map = btn_map_rot_270;
      break;
   }

   switch (RETRO_PIX_DEPTH)
   {
      case 15: lynx->DisplaySetAttributes(lynx_rot, MIKIE_PIXEL_FORMAT_16BPP_555, 160*2, lynx_display_callback, (ULONG)0); break;
      case 16: lynx->DisplaySetAttributes(lynx_rot, MIKIE_PIXEL_FORMAT_16BPP_565, 160*2, lynx_display_callback, (ULONG)0); break;
      case 24: lynx->DisplaySetAttributes(lynx_rot, MIKIE_PIXEL_FORMAT_32BPP,     160*4, lynx_display_callback, (ULONG)0); break;
      default: lynx->DisplaySetAttributes(lynx_rot, MIKIE_PIXEL_FORMAT_32BPP,     160*4, lynx_display_callback, (ULONG)0); break;
   }

   update_geometry();
}

static void check_variables(void)
{
   struct retro_variable var = {0};

   var.key = "handy_rot";
   var.value = NULL;

   if (environ_cb(RETRO_ENVIRONMENT_GET_VARIABLE, &var) && var.value) {
      unsigned old_rotate = lynx_rot;

      if (strcmp(var.value, "None") == 0)
         lynx_rot = MIKIE_NO_ROTATE;
      else if (strcmp(var.value, "90") == 0)
         lynx_rot = MIKIE_ROTATE_R; 
      else if (strcmp(var.value, "270") == 0)
         lynx_rot = MIKIE_ROTATE_L;

      if (old_rotate != lynx_rot)
         lynx_rotate();
   }

   var.key = "handy_gfx_colors";
   var.value = NULL;

   if (environ_cb(RETRO_ENVIRONMENT_GET_VARIABLE, &var) && var.value)
   {
      int old_value = RETRO_PIX_BYTES;

      if (strcmp(var.value, "16bit") == 0)
      {
         RETRO_PIX_BYTES = 2;
         RETRO_PIX_DEPTH = 16;
      }
      else if (strcmp(var.value, "24bit") == 0)
      {
         RETRO_PIX_BYTES = 4;
         RETRO_PIX_DEPTH = 24;
      }

      if (old_value != RETRO_PIX_BYTES)
         update_video = true;
   }
}

void retro_init(void)
{
   struct retro_log_callback log;
   environ_cb(RETRO_ENVIRONMENT_GET_LOG_INTERFACE, &log);
   if (log.log)
      log_cb = log.log;

   uint64_t serialization_quirks = RETRO_SERIALIZATION_QUIRK_SINGLE_SESSION;
   environ_cb(RETRO_ENVIRONMENT_SET_SERIALIZATION_QUIRKS, &serialization_quirks);
}

void retro_reset(void)
{
   if(lynx){
      lynx->SaveEEPROM();
      lynx->Reset();
   }
}

void retro_deinit(void)
{
   initialized = false;

   if(lynx){
      lynx->SaveEEPROM();
      delete lynx;
      lynx=0;
   }
}

void retro_set_environment(retro_environment_t cb)
{
   static const struct retro_variable vars[] = {
      { "handy_rot", "Display rotation; None|90|270" },
      { "handy_gfx_colors", "Color depth; 16bit|24bit" },
      { NULL, NULL },
   };

   cb(RETRO_ENVIRONMENT_SET_VARIABLES, (void*)vars);

   environ_cb = cb;
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

static unsigned get_lynx_input(void)
{
   unsigned i, res = 0;
   for (i = 0; i < sizeof(btn_map_no_rot) / sizeof(map); ++i)
      res |= input_state_cb(0, RETRO_DEVICE_JOYPAD, 0, btn_map[i].retro) ? btn_map[i].lynx : 0;
   return res;
}

static void lynx_input(void)
{
   input_poll_cb();
   lynx->SetButtonData(get_lynx_input());


   static bool select_pressed_last_frame = false;
   bool select_button = input_state_cb(0, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_SELECT);

   if(select_button && !select_pressed_last_frame)
   {
      lynx_rot++;

      lynx_rotate();
   }
   
   select_pressed_last_frame = select_button;
}

static bool lynx_initialize_sound(void)
{
   gAudioEnabled = true;
   soundBuffer = (int16_t *) (&gAudioBuffer);
   return true;
}

static int file_exists(const char *path)
{
   FILE *dummy = fopen(path, "rb");

   if (!dummy)
      return 0;

   fclose(dummy);
   return 1;
}

static bool lynx_romfilename(char *dest)
{
   const char *dir = 0;
   environ_cb(RETRO_ENVIRONMENT_GET_SYSTEM_DIRECTORY, &dir);

   sprintf(dest, "%s%c%s", dir, SLASH_STR, ROM_FILE);

   if (!file_exists(dest))
   {
      if (log_cb)
         log_cb(RETRO_LOG_ERROR, "[handy] ROM not found %s\n", dest);
      return false;
   }

   return true;
}

static bool lynx_initialize_system(const char* gamepath)
{
   char romfilename[1024];

   if(lynx){
      lynx->SaveEEPROM();
      delete lynx;
      lynx=0;
   }

   lynx_romfilename(romfilename);

   lynx = new CSystem(gamepath, romfilename, true);

   return true;
}

void retro_set_controller_port_device(unsigned, unsigned)
{
}

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
   struct retro_game_geometry geom = { lynx_width, lynx_height, 160, 160, (float) lynx_width / (float) lynx_height };
   struct retro_system_timing timing = { 75.0, (float) HANDY_AUDIO_SAMPLE_FREQ };

   memset(info, 0, sizeof(*info));
   info->geometry = geom;
   info->timing   = timing;
}

void retro_run(void)
{
   bool updated = false;
   if (environ_cb(RETRO_ENVIRONMENT_GET_VARIABLE_UPDATE, &updated) && updated)
      check_variables();

   lynx_input();

   if (update_video /*|| update_audio*/)
   {
      struct retro_system_av_info system_av_info;

      if (update_video)
      {
         memset(&system_av_info, 0, sizeof(system_av_info));
         environ_cb(RETRO_ENVIRONMENT_SET_SYSTEM_AV_INFO, &system_av_info);

         check_color_depth();
         lynx_rotate();
      }

      retro_get_system_av_info(&system_av_info);
      environ_cb(RETRO_ENVIRONMENT_SET_SYSTEM_AV_INFO, &system_av_info);

      update_video = false;
      //update_audio = false;
   }

   gAudioLastUpdateCycle = gSystemCycleCount;

   while (!newFrame)
      lynx->Update();

   newFrame = false;
}

size_t retro_serialize_size(void)
{
   if(!lynx)
      return 0;

   return lynx->ContextSize();
}

bool retro_serialize(void *data, size_t size)
{
   if(!lynx)
      return false;

   LSS_FILE fp;
   fp.memptr = (UBYTE *) data;
   fp.index = 0;
   fp.index_limit = size;

   return lynx->ContextSave(&fp);
}

bool retro_unserialize(const void *data, size_t size)
{
   if(!lynx)
      return false;

   LSS_FILE fp;
   fp.memptr = (UBYTE *) data;
   fp.index = 0;
   fp.index_limit = size;

   return lynx->ContextLoad(&fp);
}

bool retro_load_game(const struct retro_game_info *info)
{
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

   if (!info)
      return false;

   environ_cb(RETRO_ENVIRONMENT_SET_INPUT_DESCRIPTORS, desc);

   check_variables();
   check_color_depth();

   if (!lynx_initialize_system(info->path))
      return false;

   if (!lynx_initialize_sound())
      return false;

   btn_map = btn_map_no_rot;
   lynx_rotate();

   update_video = false;
   //update_audio = false;

   initialized = true;

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

void retro_cheat_reset(void)
{
}

void retro_cheat_set(unsigned index, bool enabled, const char *code)
{
}

unsigned retro_get_region()
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
