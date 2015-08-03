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

static unsigned char *snd_buffer8;
static unsigned short soundBuffer[4096 * 8];

static uint8_t lynx_width = 160;
static uint8_t lynx_height = 102;

static uint16_t framebuffer[160*102*2];

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

static map btn_map_rot_240[] = {
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

   enum retro_pixel_format fmt = RETRO_PIXEL_FORMAT_RGB565;

   if(!environ_cb(RETRO_ENVIRONMENT_SET_PIXEL_FORMAT, &fmt) && log_cb)
      log_cb(RETRO_LOG_ERROR, "[could not set RGB565]\n");
}

void retro_reset(void)
{
   if(lynx)
      lynx->Reset();
}

void retro_deinit(void)
{
   retro_reset();
   initialized = false;

   if(lynx)
      delete lynx;
}

void retro_set_environment(retro_environment_t cb)
{
   static const struct retro_variable vars[] = {
      { "handy_rot", "Display rotation; None|90|240" },
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

void retro_set_controller_port_device(unsigned, unsigned)
{
}

void retro_get_system_info(struct retro_system_info *info)
{
   memset(info, 0, sizeof(*info));
   info->library_name     = "Handy";
   info->library_version  = HANDYVER;
   info->need_fullpath    = true;
   info->valid_extensions = "lnx";
   info->block_extract = 0;
}

void retro_get_system_av_info(struct retro_system_av_info *info)
{
	struct retro_game_geometry geom = { lynx_width, lynx_height, lynx_width, lynx_height };
	struct retro_system_timing timing = { 75.0, 22050.0 };

	info->geometry = geom;
	info->timing   = timing;
}

void retro_run(void)
{
    lynx_input();

    while (!newFrame)
       lynx->Update();

    newFrame = false;
}

static void gettempfilename(char *dest)
{
    const char *dir = 0;
    environ_cb(RETRO_ENVIRONMENT_GET_SYSTEM_DIRECTORY, &dir);
    sprintf(dest, "%s%chandy.tmp", dir, SLASH_STR);
}

size_t retro_serialize_size(void)
{
   char tempfilename[1024];
   if(!lynx)
      return 0;

   gettempfilename(tempfilename);
   return lynx->MemoryContextSave(tempfilename, NULL);
}

bool retro_serialize(void *data, size_t size)
{
   char tempfilename[1024];
   if(!lynx)
      return false;

   gettempfilename(tempfilename);
   return lynx->MemoryContextSave(tempfilename, (char*)data) > 0;
}

bool retro_unserialize(const void *data, size_t size)
{
    if(!lynx)
       return false;

	return lynx->MemoryContextLoad((const char*)data, size);
}

static void lynx_initialize_sound(void)
{
    gAudioEnabled = true;
    snd_buffer8 = (unsigned char *) (&gAudioBuffer);
}

static bool lynx_romfilename(char *dest)
{
   const char *dir = 0;
   environ_cb(RETRO_ENVIRONMENT_GET_SYSTEM_DIRECTORY, &dir);

   sprintf(dest, "%s%c%s", dir, SLASH_STR, ROM_FILE);

   std::ifstream ifile(dest, std::ifstream::in);

   if(!ifile)
   {
      if (log_cb)
         log_cb(RETRO_LOG_ERROR, "[handy] ROM not found %s\n", dest);
      return false;
   }

   return true;
}

static void lynx_sound_stream_update(unsigned short *buffer, int buf_length)
{
   unsigned i;
   uint16_t left;

   for (i = 0; i < buf_length; i++)
   {
      left = (snd_buffer8[i] << 8) - 32768;
      *buffer = left;
      ++buffer;
      *buffer = left;
      ++buffer;
   }

   gAudioBufferPointer = 0;
}

static UBYTE* lynx_display_callback(ULONG objref)
{
   if(!initialized)
      return (UBYTE*)framebuffer;

   video_cb(framebuffer, lynx_width, lynx_height, 160*2);

   if(gAudioBufferPointer > 0)
   {
      int f = gAudioBufferPointer;
      lynx_sound_stream_update(soundBuffer, gAudioBufferPointer);
      audio_batch_cb((const int16_t*)soundBuffer, f);
   }

   newFrame = true;
   return (UBYTE*)framebuffer;
}

static void lynx_initialize_system(const char* gamepath)
{
   ULONG rot;
   char romfilename[1024];
   struct retro_variable var = {0};
   if(lynx)
      delete(lynx);

   lynx_romfilename(romfilename);

   lynx = new CSystem(gamepath, romfilename);

   rot = MIKIE_NO_ROTATE;
   lynx_width = 160;
   lynx_height = 102;
   btn_map = btn_map_no_rot;

   var.key = "handy_rot";

   if (environ_cb(RETRO_ENVIRONMENT_GET_VARIABLE, &var) && var.value)
   {
      if (strcmp(var.value, "90") == 0)
      {
         rot = MIKIE_ROTATE_R; 
         lynx_width = 102;
         lynx_height = 160;
         btn_map = btn_map_rot_90;
      }
      else if (strcmp(var.value, "240") == 0)
      {
         rot = MIKIE_ROTATE_L;
         lynx_width = 102;
         lynx_height = 160;
         btn_map = btn_map_rot_240;
      }
   }

   lynx->DisplaySetAttributes(rot, MIKIE_PIXEL_FORMAT_16BPP_565, 320, lynx_display_callback, (ULONG)0);
}

bool retro_load_game(const struct retro_game_info *info)
{
   struct retro_input_descriptor desc[] = {
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

   environ_cb(RETRO_ENVIRONMENT_SET_INPUT_DESCRIPTORS, desc);

   lynx_initialize_system(info->path);
   lynx_initialize_sound();

   initialized = true;
   return true;
}

bool retro_load_game_special(unsigned, const struct retro_game_info*, size_t)
{
    return false;
}

void retro_unload_game(void)
{
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
   if (lynx)
      return lynx->GetRamPointer();
   return NULL;
}

size_t retro_get_memory_size(unsigned type)
{
    return 1024 * 64;
}



