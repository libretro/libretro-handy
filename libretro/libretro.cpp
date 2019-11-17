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

static unsigned char *snd_buffer16s;
static unsigned short soundBuffer[4096 * 8];

static uint8_t lynx_rot = MIKIE_NO_ROTATE;
static uint8_t lynx_width = 160;
static uint8_t lynx_height = 102;

#define VIDEO_CORE_PIXELSIZE    2 // MIKIE_PIXEL_FORMAT_16BPP_565
//#define VIDEO_CORE_PIXELSIZE  4 // MIKIE_PIXEL_FORMAT_32BPP


static uint8_t framebuffer[160*102*VIDEO_CORE_PIXELSIZE];

static bool newFrame = false;
static bool initialized = false;
bool sleepHack = false;

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

unsigned retro_api_version(void)
{
   return RETRO_API_VERSION;
}

void retro_init(void)
{
   struct retro_log_callback log;
   environ_cb(RETRO_ENVIRONMENT_GET_LOG_INTERFACE, &log);
   if (log.log)
      log_cb = log.log;

   btn_map = btn_map_no_rot;

#if VIDEO_CORE_PIXELSIZE==2
   enum retro_pixel_format fmt = RETRO_PIXEL_FORMAT_RGB565;
#endif
#if VIDEO_CORE_PIXELSIZE==4
   enum retro_pixel_format fmt = RETRO_PIXEL_FORMAT_XRGB8888;
#endif

   if(!environ_cb(RETRO_ENVIRONMENT_SET_PIXEL_FORMAT, &fmt) && log_cb){
#if VIDEO_CORE_PIXELSIZE==2
      log_cb(RETRO_LOG_ERROR, "[could not set RGB565]\n");
#endif
#if VIDEO_CORE_PIXELSIZE==4
      log_cb(RETRO_LOG_ERROR, "[could not set RGB8888]\n");
#endif
   }

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
      { "handy_sleephack", "Disable CPU sleep (Hack); disabled|enabled" },
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
}

static bool lynx_initialize_sound(void)
{
   gAudioEnabled = true;
   snd_buffer16s = (unsigned char *) (&gAudioBuffer);
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

inline static void lynx_sound_stream_update(unsigned short *buffer, int buf_length)
{
   memcpy(buffer, snd_buffer16s, buf_length);
   gAudioBufferPointer = 0;
}

static UBYTE* lynx_display_callback(ULONG objref)
{
   if(!initialized)
      return (UBYTE*)framebuffer;

   video_cb(framebuffer, lynx_width, lynx_height, 160*VIDEO_CORE_PIXELSIZE);

   if(gAudioBufferPointer > 0)
   {
      int f = gAudioBufferPointer / 4; // /1 - 8 bit mono, /2 8 bit stereo, /4 16 bit stereo
      lynx_sound_stream_update(soundBuffer, gAudioBufferPointer);
      audio_batch_cb((const int16_t*)soundBuffer, f);
   }

   newFrame = true;
   return (UBYTE*)framebuffer;
}

static void update_geometry()
{
   struct retro_system_av_info info;

   retro_get_system_av_info(&info);
   environ_cb(RETRO_ENVIRONMENT_SET_GEOMETRY, &info);
}

static void check_variables(void)
{
   struct retro_variable var = {0};

   var.key = "handy_rot";

   if (environ_cb(RETRO_ENVIRONMENT_GET_VARIABLE, &var) && var.value)
   {
      unsigned old_rotate = lynx_rot;

      if (strcmp(var.value, "None") == 0)
      {
         lynx_rot = MIKIE_NO_ROTATE;
         lynx_width = 160;
         lynx_height = 102;
         btn_map = btn_map_no_rot;
      }
      else if (strcmp(var.value, "90") == 0)
      {
         lynx_rot = MIKIE_ROTATE_R; 
         lynx_width = 102;
         lynx_height = 160;
         btn_map = btn_map_rot_90;
      }
      else if (strcmp(var.value, "270") == 0)
      {
         lynx_rot = MIKIE_ROTATE_L;
         lynx_width = 102;
         lynx_height = 160;
         btn_map = btn_map_rot_270;
      }

      if (old_rotate != lynx_rot)
      {
      #if VIDEO_CORE_PIXELSIZE==2
         lynx->DisplaySetAttributes(lynx_rot, MIKIE_PIXEL_FORMAT_16BPP_565, 160*VIDEO_CORE_PIXELSIZE, lynx_display_callback, (ULONG)0);
      #elif VIDEO_CORE_PIXELSIZE==4
         lynx->DisplaySetAttributes(lynx_rot, MIKIE_PIXEL_FORMAT_32BPP, 160*VIDEO_CORE_PIXELSIZE, lynx_display_callback, (ULONG)0);
      #endif

         update_geometry();
      }
   }

   var.key = "handy_sleephack";

   if (environ_cb(RETRO_ENVIRONMENT_GET_VARIABLE, &var) && var.value)
   {
      sleepHack = !strcmp(var.value, "enabled") ? true : false;
   }
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

#if VIDEO_CORE_PIXELSIZE==2
   lynx->DisplaySetAttributes(lynx_rot, MIKIE_PIXEL_FORMAT_16BPP_565, 160*VIDEO_CORE_PIXELSIZE, lynx_display_callback, (ULONG)0);
#elif VIDEO_CORE_PIXELSIZE==4
   lynx->DisplaySetAttributes(lynx_rot, MIKIE_PIXEL_FORMAT_32BPP, 160*VIDEO_CORE_PIXELSIZE, lynx_display_callback, (ULONG)0);
#endif

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
   info->valid_extensions = "lnx";
   info->block_extract = 0;
}

void retro_get_system_av_info(struct retro_system_av_info *info)
{
   struct retro_game_geometry geom = { lynx_width, lynx_height, 160, 160, (float) lynx_width / (float) lynx_height };
   struct retro_system_timing timing = { 75.0, 48000.0 };

   memset(info, 0, sizeof(*info));
   info->geometry = geom;
   info->timing   = timing;
}

void retro_run(void)
{
   lynx_input();

   while (!newFrame)
      lynx->Update();

   newFrame = false;


   bool updated = false;
   if (environ_cb(RETRO_ENVIRONMENT_GET_VARIABLE_UPDATE, &updated) && updated)
      check_variables();
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

      { 0 },
   };

   if (!info)
      return false;

   environ_cb(RETRO_ENVIRONMENT_SET_INPUT_DESCRIPTORS, desc);

   if (!lynx_initialize_system(info->path))
      return false;

   if (!lynx_initialize_sound())
      return false;

   check_variables();

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
