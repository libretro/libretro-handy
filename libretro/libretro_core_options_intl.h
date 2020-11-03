﻿#ifndef LIBRETRO_CORE_OPTIONS_INTL_H__
#define LIBRETRO_CORE_OPTIONS_INTL_H__

#if defined(_MSC_VER) && (_MSC_VER >= 1500 && _MSC_VER < 1900)
/* https://support.microsoft.com/en-us/kb/980263 */
#pragma execution_character_set("utf-8")
#pragma warning(disable:4566)
#endif

#include <libretro.h>

/*
 ********************************
 * VERSION: 1.3
 ********************************
 *
 * - 1.3: Move translations to libretro_core_options_intl.h
 *        - libretro_core_options_intl.h includes BOM and utf-8
 *          fix for MSVC 2010-2013
 *        - Added HAVE_NO_LANGEXTRA flag to disable translations
 *          on platforms/compilers without BOM support
 * - 1.2: Use core options v1 interface when
 *        RETRO_ENVIRONMENT_GET_CORE_OPTIONS_VERSION is >= 1
 *        (previously required RETRO_ENVIRONMENT_GET_CORE_OPTIONS_VERSION == 1)
 * - 1.1: Support generation of core options v0 retro_core_option_value
 *        arrays containing options with a single value
 * - 1.0: First commit
*/

#ifdef __cplusplus
extern "C" {
#endif

/*
 ********************************
 * Core Option Definitions
 ********************************
*/

/* RETRO_LANGUAGE_JAPANESE */

/* RETRO_LANGUAGE_FRENCH */

/* RETRO_LANGUAGE_SPANISH */

/* RETRO_LANGUAGE_GERMAN */

/* RETRO_LANGUAGE_ITALIAN */

/* RETRO_LANGUAGE_DUTCH */

/* RETRO_LANGUAGE_PORTUGUESE_BRAZIL */

/* RETRO_LANGUAGE_PORTUGUESE_PORTUGAL */

/* RETRO_LANGUAGE_RUSSIAN */

struct retro_core_option_definition option_defs_ru[] = {
   {
      "handy_rot",
      "Поворот дисплея",
      "Поверните изображение для правильного отображения портретно-ориентированных игр на экране с альбомной ориентацией.",
      {
         { "None", "Отключено" },
         { "270",  "По часовой стрелке" },
         { "90",   "Против часовой стрелки" },
         { NULL, NULL },
      },
      "None"
   },
#if defined(FRONTEND_SUPPORTS_XRGB8888)
   {
      "handy_gfx_colors",
      "Глубина цвета (перезапуск)",
      "Укажите количество цветов для вывода на экран. 24-битная палитра существенно влияет на производительность и недоступна для всех платформ.",
      {
         { "16bit", "Тысячи (16 бит)" },
         { "24bit", "Миллионы (24 бита)" },
         { NULL,    NULL },
      },
      "16bit"
   },
#endif   
   { NULL, NULL, NULL, {{0}}, NULL },
};

/* RETRO_LANGUAGE_KOREAN */

/* RETRO_LANGUAGE_CHINESE_TRADITIONAL */

/* RETRO_LANGUAGE_CHINESE_SIMPLIFIED */

/* RETRO_LANGUAGE_ESPERANTO */

/* RETRO_LANGUAGE_POLISH */

/* RETRO_LANGUAGE_VIETNAMESE */

/* RETRO_LANGUAGE_ARABIC */

/* RETRO_LANGUAGE_GREEK */

/* RETRO_LANGUAGE_TURKISH */

/* RETRO_LANGUAGE_SLOVAK */

/* RETRO_LANGUAGE_PERSIAN */

/* RETRO_LANGUAGE_HEBREW */

/* RETRO_LANGUAGE_ASTURIAN */

#ifdef __cplusplus
}
#endif

#endif
