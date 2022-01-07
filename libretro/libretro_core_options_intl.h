#ifndef LIBRETRO_CORE_OPTIONS_INTL_H__
#define LIBRETRO_CORE_OPTIONS_INTL_H__

#if defined(_MSC_VER) && (_MSC_VER >= 1500 && _MSC_VER < 1900)
/* https://support.microsoft.com/en-us/kb/980263 */
#pragma execution_character_set("utf-8")
#pragma warning(disable:4566)
#endif

#include <libretro.h>

/*
 ********************************
 * VERSION: 2.0
 ********************************
 *
 * - 2.0: Add support for core options v2 interface
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
/* RETRO_LANGUAGE_AR */

#define HANDY_ROT_LABEL_AR NULL
#define HANDY_ROT_INFO_0_AR "تدوير شاشة وحدة التحكم الافتراضية لتحقيق التخطيط الصحيح للألعاب \"عمودية\" على العرض التقليدي (الأفقي)."
#define OPTION_VAL_NONE_AR "لاشيء"
#define OPTION_VAL_270_AR NULL
#define OPTION_VAL_90_AR NULL
#define HANDY_GFX_COLORS_LABEL_AR NULL
#define HANDY_GFX_COLORS_INFO_0_AR "حدد عدد الألوان لعرضها على الشاشة. 24 بت يزيد بشكل كبير من النفقات العامة للأداء، وهو غير متوفر على جميع المنصات."
#define OPTION_VAL_16BIT_AR NULL
#define OPTION_VAL_24BIT_AR NULL
#define HANDY_FRAMESKIP_LABEL_AR NULL
#define HANDY_FRAMESKIP_INFO_0_AR NULL
#define OPTION_VAL_AUTO_AR "تلقائي"
#define OPTION_VAL_MANUAL_AR "يدوي"
#define HANDY_FRAMESKIP_THRESHOLD_LABEL_AR NULL
#define HANDY_FRAMESKIP_THRESHOLD_INFO_0_AR "عندما يتم تعيين 'Frameskip' إلى 'يدوي'، يحدد عتبة شغل التخزين المؤقت الصوتي (النسبة المئوية) التي سيتم تخطي الأطر أدناه. فارتفاع القيم يقلل من خطر التشويش بالتسبب في انخفاض الأطر بصورة أكثر تواترا."

struct retro_core_option_v2_category option_cats_ar[] = {
   { NULL, NULL, NULL },
};
struct retro_core_option_v2_definition option_defs_ar[] = {
   {
      "handy_rot",
      HANDY_ROT_LABEL_AR,
      NULL,
      HANDY_ROT_INFO_0_AR,
      NULL,
      NULL,
      {
         { "None", OPTION_VAL_NONE_AR },
         { "270",  OPTION_VAL_270_AR },
         { "90",   OPTION_VAL_90_AR },
         { NULL, NULL },
      },
      "None"
   },
#if defined(FRONTEND_SUPPORTS_XRGB8888)
   {
      "handy_gfx_colors",
      HANDY_GFX_COLORS_LABEL_AR,
      NULL,
      HANDY_GFX_COLORS_INFO_0_AR,
      NULL,
      NULL,
      {
         { "16bit", OPTION_VAL_16BIT_AR },
         { "24bit", OPTION_VAL_24BIT_AR },
         { NULL,    NULL },
      },
      "16bit"
   },
#endif
   {
      "handy_frameskip",
      HANDY_FRAMESKIP_LABEL_AR,
      NULL,
      HANDY_FRAMESKIP_INFO_0_AR,
      NULL,
      NULL,
      {
         { "disabled", NULL },
         { "auto",     OPTION_VAL_AUTO_AR },
         { "manual",   OPTION_VAL_MANUAL_AR },
         { NULL, NULL },
      },
      "disabled"
   },
   {
      "handy_frameskip_threshold",
      HANDY_FRAMESKIP_THRESHOLD_LABEL_AR,
      NULL,
      HANDY_FRAMESKIP_THRESHOLD_INFO_0_AR,
      NULL,
      NULL,
      {
         { "15", NULL },
         { "18", NULL },
         { "21", NULL },
         { "24", NULL },
         { "27", NULL },
         { "30", NULL },
         { "33", NULL },
         { "36", NULL },
         { "39", NULL },
         { "42", NULL },
         { "45", NULL },
         { "48", NULL },
         { "51", NULL },
         { "54", NULL },
         { "57", NULL },
         { "60", NULL },
         { NULL, NULL },
      },
      "33"
   },
   { NULL, NULL, NULL, NULL, NULL, NULL, {{0}}, NULL },
};
struct retro_core_options_v2 options_ar = {
   option_cats_ar,
   option_defs_ar
};

/* RETRO_LANGUAGE_AST */

#define HANDY_ROT_LABEL_AST NULL
#define HANDY_ROT_INFO_0_AST "Voltia la pantalla de la consola virtual pa llograr la distribución correuta de los xuegos orientaos en vertical nuna pantalla panorámica convencional."
#define OPTION_VAL_NONE_AST NULL
#define OPTION_VAL_270_AST NULL
#define OPTION_VAL_90_AST NULL
#define HANDY_GFX_COLORS_LABEL_AST NULL
#define HANDY_GFX_COLORS_INFO_0_AST "Especifica'l númberu de colores a amosar na pantalla. Los 24 bits aumenten significativamente les sobrecargues nel rindimientu y nun tán disponibles en toles plataformes."
#define OPTION_VAL_16BIT_AST NULL
#define OPTION_VAL_24BIT_AST NULL
#define HANDY_FRAMESKIP_LABEL_AST NULL
#define HANDY_FRAMESKIP_INFO_0_AST NULL
#define OPTION_VAL_AUTO_AST NULL
#define OPTION_VAL_MANUAL_AST NULL
#define HANDY_FRAMESKIP_THRESHOLD_LABEL_AST NULL
#define HANDY_FRAMESKIP_THRESHOLD_INFO_0_AST NULL

struct retro_core_option_v2_category option_cats_ast[] = {
   { NULL, NULL, NULL },
};
struct retro_core_option_v2_definition option_defs_ast[] = {
   {
      "handy_rot",
      HANDY_ROT_LABEL_AST,
      NULL,
      HANDY_ROT_INFO_0_AST,
      NULL,
      NULL,
      {
         { "None", OPTION_VAL_NONE_AST },
         { "270",  OPTION_VAL_270_AST },
         { "90",   OPTION_VAL_90_AST },
         { NULL, NULL },
      },
      "None"
   },
#if defined(FRONTEND_SUPPORTS_XRGB8888)
   {
      "handy_gfx_colors",
      HANDY_GFX_COLORS_LABEL_AST,
      NULL,
      HANDY_GFX_COLORS_INFO_0_AST,
      NULL,
      NULL,
      {
         { "16bit", OPTION_VAL_16BIT_AST },
         { "24bit", OPTION_VAL_24BIT_AST },
         { NULL,    NULL },
      },
      "16bit"
   },
#endif
   {
      "handy_frameskip",
      HANDY_FRAMESKIP_LABEL_AST,
      NULL,
      HANDY_FRAMESKIP_INFO_0_AST,
      NULL,
      NULL,
      {
         { "disabled", NULL },
         { "auto",     OPTION_VAL_AUTO_AST },
         { "manual",   OPTION_VAL_MANUAL_AST },
         { NULL, NULL },
      },
      "disabled"
   },
   {
      "handy_frameskip_threshold",
      HANDY_FRAMESKIP_THRESHOLD_LABEL_AST,
      NULL,
      HANDY_FRAMESKIP_THRESHOLD_INFO_0_AST,
      NULL,
      NULL,
      {
         { "15", NULL },
         { "18", NULL },
         { "21", NULL },
         { "24", NULL },
         { "27", NULL },
         { "30", NULL },
         { "33", NULL },
         { "36", NULL },
         { "39", NULL },
         { "42", NULL },
         { "45", NULL },
         { "48", NULL },
         { "51", NULL },
         { "54", NULL },
         { "57", NULL },
         { "60", NULL },
         { NULL, NULL },
      },
      "33"
   },
   { NULL, NULL, NULL, NULL, NULL, NULL, {{0}}, NULL },
};
struct retro_core_options_v2 options_ast = {
   option_cats_ast,
   option_defs_ast
};

/* RETRO_LANGUAGE_CA */

#define HANDY_ROT_LABEL_CA NULL
#define HANDY_ROT_INFO_0_CA NULL
#define OPTION_VAL_NONE_CA NULL
#define OPTION_VAL_270_CA NULL
#define OPTION_VAL_90_CA NULL
#define HANDY_GFX_COLORS_LABEL_CA NULL
#define HANDY_GFX_COLORS_INFO_0_CA NULL
#define OPTION_VAL_16BIT_CA NULL
#define OPTION_VAL_24BIT_CA NULL
#define HANDY_FRAMESKIP_LABEL_CA NULL
#define HANDY_FRAMESKIP_INFO_0_CA NULL
#define OPTION_VAL_AUTO_CA NULL
#define OPTION_VAL_MANUAL_CA NULL
#define HANDY_FRAMESKIP_THRESHOLD_LABEL_CA NULL
#define HANDY_FRAMESKIP_THRESHOLD_INFO_0_CA NULL

struct retro_core_option_v2_category option_cats_ca[] = {
   { NULL, NULL, NULL },
};
struct retro_core_option_v2_definition option_defs_ca[] = {
   {
      "handy_rot",
      HANDY_ROT_LABEL_CA,
      NULL,
      HANDY_ROT_INFO_0_CA,
      NULL,
      NULL,
      {
         { "None", OPTION_VAL_NONE_CA },
         { "270",  OPTION_VAL_270_CA },
         { "90",   OPTION_VAL_90_CA },
         { NULL, NULL },
      },
      "None"
   },
#if defined(FRONTEND_SUPPORTS_XRGB8888)
   {
      "handy_gfx_colors",
      HANDY_GFX_COLORS_LABEL_CA,
      NULL,
      HANDY_GFX_COLORS_INFO_0_CA,
      NULL,
      NULL,
      {
         { "16bit", OPTION_VAL_16BIT_CA },
         { "24bit", OPTION_VAL_24BIT_CA },
         { NULL,    NULL },
      },
      "16bit"
   },
#endif
   {
      "handy_frameskip",
      HANDY_FRAMESKIP_LABEL_CA,
      NULL,
      HANDY_FRAMESKIP_INFO_0_CA,
      NULL,
      NULL,
      {
         { "disabled", NULL },
         { "auto",     OPTION_VAL_AUTO_CA },
         { "manual",   OPTION_VAL_MANUAL_CA },
         { NULL, NULL },
      },
      "disabled"
   },
   {
      "handy_frameskip_threshold",
      HANDY_FRAMESKIP_THRESHOLD_LABEL_CA,
      NULL,
      HANDY_FRAMESKIP_THRESHOLD_INFO_0_CA,
      NULL,
      NULL,
      {
         { "15", NULL },
         { "18", NULL },
         { "21", NULL },
         { "24", NULL },
         { "27", NULL },
         { "30", NULL },
         { "33", NULL },
         { "36", NULL },
         { "39", NULL },
         { "42", NULL },
         { "45", NULL },
         { "48", NULL },
         { "51", NULL },
         { "54", NULL },
         { "57", NULL },
         { "60", NULL },
         { NULL, NULL },
      },
      "33"
   },
   { NULL, NULL, NULL, NULL, NULL, NULL, {{0}}, NULL },
};
struct retro_core_options_v2 options_ca = {
   option_cats_ca,
   option_defs_ca
};

/* RETRO_LANGUAGE_CHS */

#define HANDY_ROT_LABEL_CHS NULL
#define HANDY_ROT_INFO_0_CHS "如果想要在横屏的显示器上竖屏显示游戏，请旋转你的模拟器屏幕。"
#define OPTION_VAL_NONE_CHS "无"
#define OPTION_VAL_270_CHS "顺时针"
#define OPTION_VAL_90_CHS "逆时针"
#define HANDY_GFX_COLORS_LABEL_CHS NULL
#define HANDY_GFX_COLORS_INFO_0_CHS "指定屏幕显示的颜色数量。设置为「24 位」将极大提高性能开销，且仅部分平台可用。"
#define OPTION_VAL_16BIT_CHS NULL
#define OPTION_VAL_24BIT_CHS NULL
#define HANDY_FRAMESKIP_LABEL_CHS "跳帧"
#define HANDY_FRAMESKIP_INFO_0_CHS "跳过帧以避免运行下的音频缓冲区(崩溃)。提高性能以牺牲视觉性能。 “自动”跳板帧在前端建议时。“手动”使用了“Frameskip 阈值(%)”设置。"
#define OPTION_VAL_AUTO_CHS "自动"
#define OPTION_VAL_MANUAL_CHS "手工"
#define HANDY_FRAMESKIP_THRESHOLD_LABEL_CHS "跳帧阈值(%)"
#define HANDY_FRAMESKIP_THRESHOLD_INFO_0_CHS "当“跳帧”功能设置成“手动”，请在下方指定跳帧占音频缓存的比例（百分比）。更高的值可以降低因频繁丢帧而导致的爆音风险。"

struct retro_core_option_v2_category option_cats_chs[] = {
   { NULL, NULL, NULL },
};
struct retro_core_option_v2_definition option_defs_chs[] = {
   {
      "handy_rot",
      HANDY_ROT_LABEL_CHS,
      NULL,
      HANDY_ROT_INFO_0_CHS,
      NULL,
      NULL,
      {
         { "None", OPTION_VAL_NONE_CHS },
         { "270",  OPTION_VAL_270_CHS },
         { "90",   OPTION_VAL_90_CHS },
         { NULL, NULL },
      },
      "None"
   },
#if defined(FRONTEND_SUPPORTS_XRGB8888)
   {
      "handy_gfx_colors",
      HANDY_GFX_COLORS_LABEL_CHS,
      NULL,
      HANDY_GFX_COLORS_INFO_0_CHS,
      NULL,
      NULL,
      {
         { "16bit", OPTION_VAL_16BIT_CHS },
         { "24bit", OPTION_VAL_24BIT_CHS },
         { NULL,    NULL },
      },
      "16bit"
   },
#endif
   {
      "handy_frameskip",
      HANDY_FRAMESKIP_LABEL_CHS,
      NULL,
      HANDY_FRAMESKIP_INFO_0_CHS,
      NULL,
      NULL,
      {
         { "disabled", NULL },
         { "auto",     OPTION_VAL_AUTO_CHS },
         { "manual",   OPTION_VAL_MANUAL_CHS },
         { NULL, NULL },
      },
      "disabled"
   },
   {
      "handy_frameskip_threshold",
      HANDY_FRAMESKIP_THRESHOLD_LABEL_CHS,
      NULL,
      HANDY_FRAMESKIP_THRESHOLD_INFO_0_CHS,
      NULL,
      NULL,
      {
         { "15", NULL },
         { "18", NULL },
         { "21", NULL },
         { "24", NULL },
         { "27", NULL },
         { "30", NULL },
         { "33", NULL },
         { "36", NULL },
         { "39", NULL },
         { "42", NULL },
         { "45", NULL },
         { "48", NULL },
         { "51", NULL },
         { "54", NULL },
         { "57", NULL },
         { "60", NULL },
         { NULL, NULL },
      },
      "33"
   },
   { NULL, NULL, NULL, NULL, NULL, NULL, {{0}}, NULL },
};
struct retro_core_options_v2 options_chs = {
   option_cats_chs,
   option_defs_chs
};

/* RETRO_LANGUAGE_CHT */

#define HANDY_ROT_LABEL_CHT NULL
#define HANDY_ROT_INFO_0_CHT NULL
#define OPTION_VAL_NONE_CHT "無"
#define OPTION_VAL_270_CHT NULL
#define OPTION_VAL_90_CHT NULL
#define HANDY_GFX_COLORS_LABEL_CHT NULL
#define HANDY_GFX_COLORS_INFO_0_CHT NULL
#define OPTION_VAL_16BIT_CHT NULL
#define OPTION_VAL_24BIT_CHT NULL
#define HANDY_FRAMESKIP_LABEL_CHT NULL
#define HANDY_FRAMESKIP_INFO_0_CHT NULL
#define OPTION_VAL_AUTO_CHT "自動"
#define OPTION_VAL_MANUAL_CHT NULL
#define HANDY_FRAMESKIP_THRESHOLD_LABEL_CHT NULL
#define HANDY_FRAMESKIP_THRESHOLD_INFO_0_CHT NULL

struct retro_core_option_v2_category option_cats_cht[] = {
   { NULL, NULL, NULL },
};
struct retro_core_option_v2_definition option_defs_cht[] = {
   {
      "handy_rot",
      HANDY_ROT_LABEL_CHT,
      NULL,
      HANDY_ROT_INFO_0_CHT,
      NULL,
      NULL,
      {
         { "None", OPTION_VAL_NONE_CHT },
         { "270",  OPTION_VAL_270_CHT },
         { "90",   OPTION_VAL_90_CHT },
         { NULL, NULL },
      },
      "None"
   },
#if defined(FRONTEND_SUPPORTS_XRGB8888)
   {
      "handy_gfx_colors",
      HANDY_GFX_COLORS_LABEL_CHT,
      NULL,
      HANDY_GFX_COLORS_INFO_0_CHT,
      NULL,
      NULL,
      {
         { "16bit", OPTION_VAL_16BIT_CHT },
         { "24bit", OPTION_VAL_24BIT_CHT },
         { NULL,    NULL },
      },
      "16bit"
   },
#endif
   {
      "handy_frameskip",
      HANDY_FRAMESKIP_LABEL_CHT,
      NULL,
      HANDY_FRAMESKIP_INFO_0_CHT,
      NULL,
      NULL,
      {
         { "disabled", NULL },
         { "auto",     OPTION_VAL_AUTO_CHT },
         { "manual",   OPTION_VAL_MANUAL_CHT },
         { NULL, NULL },
      },
      "disabled"
   },
   {
      "handy_frameskip_threshold",
      HANDY_FRAMESKIP_THRESHOLD_LABEL_CHT,
      NULL,
      HANDY_FRAMESKIP_THRESHOLD_INFO_0_CHT,
      NULL,
      NULL,
      {
         { "15", NULL },
         { "18", NULL },
         { "21", NULL },
         { "24", NULL },
         { "27", NULL },
         { "30", NULL },
         { "33", NULL },
         { "36", NULL },
         { "39", NULL },
         { "42", NULL },
         { "45", NULL },
         { "48", NULL },
         { "51", NULL },
         { "54", NULL },
         { "57", NULL },
         { "60", NULL },
         { NULL, NULL },
      },
      "33"
   },
   { NULL, NULL, NULL, NULL, NULL, NULL, {{0}}, NULL },
};
struct retro_core_options_v2 options_cht = {
   option_cats_cht,
   option_defs_cht
};

/* RETRO_LANGUAGE_CS */

#define HANDY_ROT_LABEL_CS NULL
#define HANDY_ROT_INFO_0_CS NULL
#define OPTION_VAL_NONE_CS NULL
#define OPTION_VAL_270_CS NULL
#define OPTION_VAL_90_CS NULL
#define HANDY_GFX_COLORS_LABEL_CS NULL
#define HANDY_GFX_COLORS_INFO_0_CS NULL
#define OPTION_VAL_16BIT_CS NULL
#define OPTION_VAL_24BIT_CS NULL
#define HANDY_FRAMESKIP_LABEL_CS NULL
#define HANDY_FRAMESKIP_INFO_0_CS NULL
#define OPTION_VAL_AUTO_CS NULL
#define OPTION_VAL_MANUAL_CS NULL
#define HANDY_FRAMESKIP_THRESHOLD_LABEL_CS NULL
#define HANDY_FRAMESKIP_THRESHOLD_INFO_0_CS NULL

struct retro_core_option_v2_category option_cats_cs[] = {
   { NULL, NULL, NULL },
};
struct retro_core_option_v2_definition option_defs_cs[] = {
   {
      "handy_rot",
      HANDY_ROT_LABEL_CS,
      NULL,
      HANDY_ROT_INFO_0_CS,
      NULL,
      NULL,
      {
         { "None", OPTION_VAL_NONE_CS },
         { "270",  OPTION_VAL_270_CS },
         { "90",   OPTION_VAL_90_CS },
         { NULL, NULL },
      },
      "None"
   },
#if defined(FRONTEND_SUPPORTS_XRGB8888)
   {
      "handy_gfx_colors",
      HANDY_GFX_COLORS_LABEL_CS,
      NULL,
      HANDY_GFX_COLORS_INFO_0_CS,
      NULL,
      NULL,
      {
         { "16bit", OPTION_VAL_16BIT_CS },
         { "24bit", OPTION_VAL_24BIT_CS },
         { NULL,    NULL },
      },
      "16bit"
   },
#endif
   {
      "handy_frameskip",
      HANDY_FRAMESKIP_LABEL_CS,
      NULL,
      HANDY_FRAMESKIP_INFO_0_CS,
      NULL,
      NULL,
      {
         { "disabled", NULL },
         { "auto",     OPTION_VAL_AUTO_CS },
         { "manual",   OPTION_VAL_MANUAL_CS },
         { NULL, NULL },
      },
      "disabled"
   },
   {
      "handy_frameskip_threshold",
      HANDY_FRAMESKIP_THRESHOLD_LABEL_CS,
      NULL,
      HANDY_FRAMESKIP_THRESHOLD_INFO_0_CS,
      NULL,
      NULL,
      {
         { "15", NULL },
         { "18", NULL },
         { "21", NULL },
         { "24", NULL },
         { "27", NULL },
         { "30", NULL },
         { "33", NULL },
         { "36", NULL },
         { "39", NULL },
         { "42", NULL },
         { "45", NULL },
         { "48", NULL },
         { "51", NULL },
         { "54", NULL },
         { "57", NULL },
         { "60", NULL },
         { NULL, NULL },
      },
      "33"
   },
   { NULL, NULL, NULL, NULL, NULL, NULL, {{0}}, NULL },
};
struct retro_core_options_v2 options_cs = {
   option_cats_cs,
   option_defs_cs
};

/* RETRO_LANGUAGE_CY */

#define HANDY_ROT_LABEL_CY NULL
#define HANDY_ROT_INFO_0_CY "Cylchdrowch y sgrin consol rhith i gael y cynllun cywir o gemau 'portread' ar dangosydd confensiynol (tirlun)."
#define OPTION_VAL_NONE_CY "Dim"
#define OPTION_VAL_270_CY NULL
#define OPTION_VAL_90_CY NULL
#define HANDY_GFX_COLORS_LABEL_CY NULL
#define HANDY_GFX_COLORS_INFO_0_CY "Nodwch nifer y lliwiau i'w harddangos ar y sgrin. Mae 24-did yn cynyddu gorbenion perfformiad yn sylweddol ac nid yw ar gael ar bob platfform."
#define OPTION_VAL_16BIT_CY NULL
#define OPTION_VAL_24BIT_CY NULL
#define HANDY_FRAMESKIP_LABEL_CY NULL
#define HANDY_FRAMESKIP_INFO_0_CY NULL
#define OPTION_VAL_AUTO_CY NULL
#define OPTION_VAL_MANUAL_CY NULL
#define HANDY_FRAMESKIP_THRESHOLD_LABEL_CY NULL
#define HANDY_FRAMESKIP_THRESHOLD_INFO_0_CY "Pan fydd 'Frameskip' yn cael ei osod i 'Manual', yn pennu'r trothwy meddiannaeth byffer sain (canran) islaw y bydd fframiau yn cael eu hepgor. Mae gwerthoedd uwch yn lleihau'r risg o graclo trwy achosi i fframiau ostwng yn amlach."

struct retro_core_option_v2_category option_cats_cy[] = {
   { NULL, NULL, NULL },
};
struct retro_core_option_v2_definition option_defs_cy[] = {
   {
      "handy_rot",
      HANDY_ROT_LABEL_CY,
      NULL,
      HANDY_ROT_INFO_0_CY,
      NULL,
      NULL,
      {
         { "None", OPTION_VAL_NONE_CY },
         { "270",  OPTION_VAL_270_CY },
         { "90",   OPTION_VAL_90_CY },
         { NULL, NULL },
      },
      "None"
   },
#if defined(FRONTEND_SUPPORTS_XRGB8888)
   {
      "handy_gfx_colors",
      HANDY_GFX_COLORS_LABEL_CY,
      NULL,
      HANDY_GFX_COLORS_INFO_0_CY,
      NULL,
      NULL,
      {
         { "16bit", OPTION_VAL_16BIT_CY },
         { "24bit", OPTION_VAL_24BIT_CY },
         { NULL,    NULL },
      },
      "16bit"
   },
#endif
   {
      "handy_frameskip",
      HANDY_FRAMESKIP_LABEL_CY,
      NULL,
      HANDY_FRAMESKIP_INFO_0_CY,
      NULL,
      NULL,
      {
         { "disabled", NULL },
         { "auto",     OPTION_VAL_AUTO_CY },
         { "manual",   OPTION_VAL_MANUAL_CY },
         { NULL, NULL },
      },
      "disabled"
   },
   {
      "handy_frameskip_threshold",
      HANDY_FRAMESKIP_THRESHOLD_LABEL_CY,
      NULL,
      HANDY_FRAMESKIP_THRESHOLD_INFO_0_CY,
      NULL,
      NULL,
      {
         { "15", NULL },
         { "18", NULL },
         { "21", NULL },
         { "24", NULL },
         { "27", NULL },
         { "30", NULL },
         { "33", NULL },
         { "36", NULL },
         { "39", NULL },
         { "42", NULL },
         { "45", NULL },
         { "48", NULL },
         { "51", NULL },
         { "54", NULL },
         { "57", NULL },
         { "60", NULL },
         { NULL, NULL },
      },
      "33"
   },
   { NULL, NULL, NULL, NULL, NULL, NULL, {{0}}, NULL },
};
struct retro_core_options_v2 options_cy = {
   option_cats_cy,
   option_defs_cy
};

/* RETRO_LANGUAGE_DA */

#define HANDY_ROT_LABEL_DA NULL
#define HANDY_ROT_INFO_0_DA "Rotér den virtuelle konsolskærm for at opnå det korrekte layout af 'portræt'-orienterede spil på en konventionel (landskabs-) skærm."
#define OPTION_VAL_NONE_DA NULL
#define OPTION_VAL_270_DA NULL
#define OPTION_VAL_90_DA NULL
#define HANDY_GFX_COLORS_LABEL_DA NULL
#define HANDY_GFX_COLORS_INFO_0_DA "Angiv antallet af farver vist på skærmen. 24-bit øger markant ydeevneomkostningerne og er ikke tilgængelig på alle platforme."
#define OPTION_VAL_16BIT_DA NULL
#define OPTION_VAL_24BIT_DA NULL
#define HANDY_FRAMESKIP_LABEL_DA NULL
#define HANDY_FRAMESKIP_INFO_0_DA NULL
#define OPTION_VAL_AUTO_DA NULL
#define OPTION_VAL_MANUAL_DA NULL
#define HANDY_FRAMESKIP_THRESHOLD_LABEL_DA NULL
#define HANDY_FRAMESKIP_THRESHOLD_INFO_0_DA "Når 'Frameskip' er sat til 'Manual', angiver den lydbufferbelægningstærsklen (procentdel), under hvilken frames overspringes. Højere værdier reducerer risikoen for crackling ved at foranledige hyppigere drop af frames."

struct retro_core_option_v2_category option_cats_da[] = {
   { NULL, NULL, NULL },
};
struct retro_core_option_v2_definition option_defs_da[] = {
   {
      "handy_rot",
      HANDY_ROT_LABEL_DA,
      NULL,
      HANDY_ROT_INFO_0_DA,
      NULL,
      NULL,
      {
         { "None", OPTION_VAL_NONE_DA },
         { "270",  OPTION_VAL_270_DA },
         { "90",   OPTION_VAL_90_DA },
         { NULL, NULL },
      },
      "None"
   },
#if defined(FRONTEND_SUPPORTS_XRGB8888)
   {
      "handy_gfx_colors",
      HANDY_GFX_COLORS_LABEL_DA,
      NULL,
      HANDY_GFX_COLORS_INFO_0_DA,
      NULL,
      NULL,
      {
         { "16bit", OPTION_VAL_16BIT_DA },
         { "24bit", OPTION_VAL_24BIT_DA },
         { NULL,    NULL },
      },
      "16bit"
   },
#endif
   {
      "handy_frameskip",
      HANDY_FRAMESKIP_LABEL_DA,
      NULL,
      HANDY_FRAMESKIP_INFO_0_DA,
      NULL,
      NULL,
      {
         { "disabled", NULL },
         { "auto",     OPTION_VAL_AUTO_DA },
         { "manual",   OPTION_VAL_MANUAL_DA },
         { NULL, NULL },
      },
      "disabled"
   },
   {
      "handy_frameskip_threshold",
      HANDY_FRAMESKIP_THRESHOLD_LABEL_DA,
      NULL,
      HANDY_FRAMESKIP_THRESHOLD_INFO_0_DA,
      NULL,
      NULL,
      {
         { "15", NULL },
         { "18", NULL },
         { "21", NULL },
         { "24", NULL },
         { "27", NULL },
         { "30", NULL },
         { "33", NULL },
         { "36", NULL },
         { "39", NULL },
         { "42", NULL },
         { "45", NULL },
         { "48", NULL },
         { "51", NULL },
         { "54", NULL },
         { "57", NULL },
         { "60", NULL },
         { NULL, NULL },
      },
      "33"
   },
   { NULL, NULL, NULL, NULL, NULL, NULL, {{0}}, NULL },
};
struct retro_core_options_v2 options_da = {
   option_cats_da,
   option_defs_da
};

/* RETRO_LANGUAGE_DE */

#define HANDY_ROT_LABEL_DE "Bildschirmrotation"
#define HANDY_ROT_INFO_0_DE "Den virtuellen Konsolen-Bildschirm drehen, um das richtige Layout von Spielen im Hochformat auf einem herkömmlichen (Quer-) Display zu erzielen."
#define OPTION_VAL_NONE_DE "Keine"
#define OPTION_VAL_270_DE "Im Uhrzeigersinn"
#define OPTION_VAL_90_DE "Gegen den Uhrzeigersinn"
#define HANDY_GFX_COLORS_LABEL_DE "Farbtiefe (Neustart erforderlich)"
#define HANDY_GFX_COLORS_INFO_0_DE "Anzahl der Farben angeben, die auf dem Bildschirm angezeigt werden sollen. 24-Bit erhöht den Leistungsaufwand erheblich und ist nicht auf allen Plattformen verfügbar."
#define OPTION_VAL_16BIT_DE "Tausende (16 Bit)"
#define OPTION_VAL_24BIT_DE "Millionen (24 Bit)"
#define HANDY_FRAMESKIP_LABEL_DE NULL
#define HANDY_FRAMESKIP_INFO_0_DE "Überspringen Sie Frames um zu vermeiden, dass Audio-Puffer unterlaufen (Knistern). Verbessert die Leistung auf Kosten der visuellen Glätte. 'Auto' überspringt Frames wenn vom Frontend empfohlen wird. 'Manuell' verwendet die Einstellung 'Frameskip Grenzwert (%)'."
#define OPTION_VAL_AUTO_DE "Automatisch"
#define OPTION_VAL_MANUAL_DE "Manuell"
#define HANDY_FRAMESKIP_THRESHOLD_LABEL_DE "Frameskip Grenzwert (%)"
#define HANDY_FRAMESKIP_THRESHOLD_INFO_0_DE "Gibt den Audiopuffer-Belegungsschwellenwert (Prozent) an, unter dem Frames übersprungen werden, wenn 'Frameskip' auf 'Manual' eingestellt ist. Höhere Werte verringern das Risiko von Knistern, da Frames häufiger weggelassen werden."

struct retro_core_option_v2_category option_cats_de[] = {
   { NULL, NULL, NULL },
};
struct retro_core_option_v2_definition option_defs_de[] = {
   {
      "handy_rot",
      HANDY_ROT_LABEL_DE,
      NULL,
      HANDY_ROT_INFO_0_DE,
      NULL,
      NULL,
      {
         { "None", OPTION_VAL_NONE_DE },
         { "270",  OPTION_VAL_270_DE },
         { "90",   OPTION_VAL_90_DE },
         { NULL, NULL },
      },
      "None"
   },
#if defined(FRONTEND_SUPPORTS_XRGB8888)
   {
      "handy_gfx_colors",
      HANDY_GFX_COLORS_LABEL_DE,
      NULL,
      HANDY_GFX_COLORS_INFO_0_DE,
      NULL,
      NULL,
      {
         { "16bit", OPTION_VAL_16BIT_DE },
         { "24bit", OPTION_VAL_24BIT_DE },
         { NULL,    NULL },
      },
      "16bit"
   },
#endif
   {
      "handy_frameskip",
      HANDY_FRAMESKIP_LABEL_DE,
      NULL,
      HANDY_FRAMESKIP_INFO_0_DE,
      NULL,
      NULL,
      {
         { "disabled", NULL },
         { "auto",     OPTION_VAL_AUTO_DE },
         { "manual",   OPTION_VAL_MANUAL_DE },
         { NULL, NULL },
      },
      "disabled"
   },
   {
      "handy_frameskip_threshold",
      HANDY_FRAMESKIP_THRESHOLD_LABEL_DE,
      NULL,
      HANDY_FRAMESKIP_THRESHOLD_INFO_0_DE,
      NULL,
      NULL,
      {
         { "15", NULL },
         { "18", NULL },
         { "21", NULL },
         { "24", NULL },
         { "27", NULL },
         { "30", NULL },
         { "33", NULL },
         { "36", NULL },
         { "39", NULL },
         { "42", NULL },
         { "45", NULL },
         { "48", NULL },
         { "51", NULL },
         { "54", NULL },
         { "57", NULL },
         { "60", NULL },
         { NULL, NULL },
      },
      "33"
   },
   { NULL, NULL, NULL, NULL, NULL, NULL, {{0}}, NULL },
};
struct retro_core_options_v2 options_de = {
   option_cats_de,
   option_defs_de
};

/* RETRO_LANGUAGE_EL */

#define HANDY_ROT_LABEL_EL NULL
#define HANDY_ROT_INFO_0_EL "Περιστρέφει την οθόνη της εικονικής κονσόλας για να επιτύχει τη σωστή διάταξη των παιχνιδιών όπου έχουν προσανατολισμό «πορτρέτο» σε συμβατική οθόνη (landscape)."
#define OPTION_VAL_NONE_EL "Κανείς"
#define OPTION_VAL_270_EL NULL
#define OPTION_VAL_90_EL NULL
#define HANDY_GFX_COLORS_LABEL_EL NULL
#define HANDY_GFX_COLORS_INFO_0_EL "Καθορίστε τον αριθμό των χρωμάτων που θα εμφανίζονται στην οθόνη. Τα 24-bit μειώνουν σημαντικά την απόδοση και δεν είναι διαθέσιμα σε όλες τις πλατφόρμες."
#define OPTION_VAL_16BIT_EL NULL
#define OPTION_VAL_24BIT_EL NULL
#define HANDY_FRAMESKIP_LABEL_EL NULL
#define HANDY_FRAMESKIP_INFO_0_EL NULL
#define OPTION_VAL_AUTO_EL NULL
#define OPTION_VAL_MANUAL_EL NULL
#define HANDY_FRAMESKIP_THRESHOLD_LABEL_EL NULL
#define HANDY_FRAMESKIP_THRESHOLD_INFO_0_EL NULL

struct retro_core_option_v2_category option_cats_el[] = {
   { NULL, NULL, NULL },
};
struct retro_core_option_v2_definition option_defs_el[] = {
   {
      "handy_rot",
      HANDY_ROT_LABEL_EL,
      NULL,
      HANDY_ROT_INFO_0_EL,
      NULL,
      NULL,
      {
         { "None", OPTION_VAL_NONE_EL },
         { "270",  OPTION_VAL_270_EL },
         { "90",   OPTION_VAL_90_EL },
         { NULL, NULL },
      },
      "None"
   },
#if defined(FRONTEND_SUPPORTS_XRGB8888)
   {
      "handy_gfx_colors",
      HANDY_GFX_COLORS_LABEL_EL,
      NULL,
      HANDY_GFX_COLORS_INFO_0_EL,
      NULL,
      NULL,
      {
         { "16bit", OPTION_VAL_16BIT_EL },
         { "24bit", OPTION_VAL_24BIT_EL },
         { NULL,    NULL },
      },
      "16bit"
   },
#endif
   {
      "handy_frameskip",
      HANDY_FRAMESKIP_LABEL_EL,
      NULL,
      HANDY_FRAMESKIP_INFO_0_EL,
      NULL,
      NULL,
      {
         { "disabled", NULL },
         { "auto",     OPTION_VAL_AUTO_EL },
         { "manual",   OPTION_VAL_MANUAL_EL },
         { NULL, NULL },
      },
      "disabled"
   },
   {
      "handy_frameskip_threshold",
      HANDY_FRAMESKIP_THRESHOLD_LABEL_EL,
      NULL,
      HANDY_FRAMESKIP_THRESHOLD_INFO_0_EL,
      NULL,
      NULL,
      {
         { "15", NULL },
         { "18", NULL },
         { "21", NULL },
         { "24", NULL },
         { "27", NULL },
         { "30", NULL },
         { "33", NULL },
         { "36", NULL },
         { "39", NULL },
         { "42", NULL },
         { "45", NULL },
         { "48", NULL },
         { "51", NULL },
         { "54", NULL },
         { "57", NULL },
         { "60", NULL },
         { NULL, NULL },
      },
      "33"
   },
   { NULL, NULL, NULL, NULL, NULL, NULL, {{0}}, NULL },
};
struct retro_core_options_v2 options_el = {
   option_cats_el,
   option_defs_el
};

/* RETRO_LANGUAGE_EO */

#define HANDY_ROT_LABEL_EO NULL
#define HANDY_ROT_INFO_0_EO NULL
#define OPTION_VAL_NONE_EO NULL
#define OPTION_VAL_270_EO NULL
#define OPTION_VAL_90_EO NULL
#define HANDY_GFX_COLORS_LABEL_EO NULL
#define HANDY_GFX_COLORS_INFO_0_EO NULL
#define OPTION_VAL_16BIT_EO NULL
#define OPTION_VAL_24BIT_EO NULL
#define HANDY_FRAMESKIP_LABEL_EO NULL
#define HANDY_FRAMESKIP_INFO_0_EO NULL
#define OPTION_VAL_AUTO_EO NULL
#define OPTION_VAL_MANUAL_EO NULL
#define HANDY_FRAMESKIP_THRESHOLD_LABEL_EO NULL
#define HANDY_FRAMESKIP_THRESHOLD_INFO_0_EO NULL

struct retro_core_option_v2_category option_cats_eo[] = {
   { NULL, NULL, NULL },
};
struct retro_core_option_v2_definition option_defs_eo[] = {
   {
      "handy_rot",
      HANDY_ROT_LABEL_EO,
      NULL,
      HANDY_ROT_INFO_0_EO,
      NULL,
      NULL,
      {
         { "None", OPTION_VAL_NONE_EO },
         { "270",  OPTION_VAL_270_EO },
         { "90",   OPTION_VAL_90_EO },
         { NULL, NULL },
      },
      "None"
   },
#if defined(FRONTEND_SUPPORTS_XRGB8888)
   {
      "handy_gfx_colors",
      HANDY_GFX_COLORS_LABEL_EO,
      NULL,
      HANDY_GFX_COLORS_INFO_0_EO,
      NULL,
      NULL,
      {
         { "16bit", OPTION_VAL_16BIT_EO },
         { "24bit", OPTION_VAL_24BIT_EO },
         { NULL,    NULL },
      },
      "16bit"
   },
#endif
   {
      "handy_frameskip",
      HANDY_FRAMESKIP_LABEL_EO,
      NULL,
      HANDY_FRAMESKIP_INFO_0_EO,
      NULL,
      NULL,
      {
         { "disabled", NULL },
         { "auto",     OPTION_VAL_AUTO_EO },
         { "manual",   OPTION_VAL_MANUAL_EO },
         { NULL, NULL },
      },
      "disabled"
   },
   {
      "handy_frameskip_threshold",
      HANDY_FRAMESKIP_THRESHOLD_LABEL_EO,
      NULL,
      HANDY_FRAMESKIP_THRESHOLD_INFO_0_EO,
      NULL,
      NULL,
      {
         { "15", NULL },
         { "18", NULL },
         { "21", NULL },
         { "24", NULL },
         { "27", NULL },
         { "30", NULL },
         { "33", NULL },
         { "36", NULL },
         { "39", NULL },
         { "42", NULL },
         { "45", NULL },
         { "48", NULL },
         { "51", NULL },
         { "54", NULL },
         { "57", NULL },
         { "60", NULL },
         { NULL, NULL },
      },
      "33"
   },
   { NULL, NULL, NULL, NULL, NULL, NULL, {{0}}, NULL },
};
struct retro_core_options_v2 options_eo = {
   option_cats_eo,
   option_defs_eo
};

/* RETRO_LANGUAGE_ES */

#define HANDY_ROT_LABEL_ES "Rotación de imagen"
#define HANDY_ROT_INFO_0_ES "Rota la pantalla virtual de la consola para mostrar correctamente los juegos con orientación vertical en una pantalla con orientación horizontal."
#define OPTION_VAL_NONE_ES "Desactivada"
#define OPTION_VAL_270_ES "Girar a la derecha"
#define OPTION_VAL_90_ES "Girar a la izquierda"
#define HANDY_GFX_COLORS_LABEL_ES "Profundidad de color (es necesario reiniciar)"
#define HANDY_GFX_COLORS_INFO_0_ES "Especifica el número de colores a mostrar en pantalla. 24 bits reduce significativamente la carga de la CPU y no se encuentra disponible en todas las plataformas."
#define OPTION_VAL_16BIT_ES "Miles (16 bits)"
#define OPTION_VAL_24BIT_ES "Millones (24 bits)"
#define HANDY_FRAMESKIP_LABEL_ES "Omisión de fotogramas"
#define HANDY_FRAMESKIP_INFO_0_ES "Omite fotogramas para no saturar el búfer de audio (chasquidos en el sonido). Mejora el rendimiento a costa de perder fluidez visual. Selección automática omite fotogramas según lo aconseje el front-end. El valor Manual utiliza el ajuste Umbral de omisión de fotogramas (%)."
#define OPTION_VAL_AUTO_ES "Selección automática"
#define OPTION_VAL_MANUAL_ES NULL
#define HANDY_FRAMESKIP_THRESHOLD_LABEL_ES "Umbral de omisión de fotogramas (%)"
#define HANDY_FRAMESKIP_THRESHOLD_INFO_0_ES "Cuando la omisión de fotogramas esté configurada como Manual, este ajuste especifica el umbral de ocupación del búfer de audio (en porcentaje) por debajo del cual se omitirán fotogramas si el valor. Un valor más elevado reduce el riesgo de chasquidos omitiendo fotogramas con una mayor frecuencia."

struct retro_core_option_v2_category option_cats_es[] = {
   { NULL, NULL, NULL },
};
struct retro_core_option_v2_definition option_defs_es[] = {
   {
      "handy_rot",
      HANDY_ROT_LABEL_ES,
      NULL,
      HANDY_ROT_INFO_0_ES,
      NULL,
      NULL,
      {
         { "None", OPTION_VAL_NONE_ES },
         { "270",  OPTION_VAL_270_ES },
         { "90",   OPTION_VAL_90_ES },
         { NULL, NULL },
      },
      "None"
   },
#if defined(FRONTEND_SUPPORTS_XRGB8888)
   {
      "handy_gfx_colors",
      HANDY_GFX_COLORS_LABEL_ES,
      NULL,
      HANDY_GFX_COLORS_INFO_0_ES,
      NULL,
      NULL,
      {
         { "16bit", OPTION_VAL_16BIT_ES },
         { "24bit", OPTION_VAL_24BIT_ES },
         { NULL,    NULL },
      },
      "16bit"
   },
#endif
   {
      "handy_frameskip",
      HANDY_FRAMESKIP_LABEL_ES,
      NULL,
      HANDY_FRAMESKIP_INFO_0_ES,
      NULL,
      NULL,
      {
         { "disabled", NULL },
         { "auto",     OPTION_VAL_AUTO_ES },
         { "manual",   OPTION_VAL_MANUAL_ES },
         { NULL, NULL },
      },
      "disabled"
   },
   {
      "handy_frameskip_threshold",
      HANDY_FRAMESKIP_THRESHOLD_LABEL_ES,
      NULL,
      HANDY_FRAMESKIP_THRESHOLD_INFO_0_ES,
      NULL,
      NULL,
      {
         { "15", NULL },
         { "18", NULL },
         { "21", NULL },
         { "24", NULL },
         { "27", NULL },
         { "30", NULL },
         { "33", NULL },
         { "36", NULL },
         { "39", NULL },
         { "42", NULL },
         { "45", NULL },
         { "48", NULL },
         { "51", NULL },
         { "54", NULL },
         { "57", NULL },
         { "60", NULL },
         { NULL, NULL },
      },
      "33"
   },
   { NULL, NULL, NULL, NULL, NULL, NULL, {{0}}, NULL },
};
struct retro_core_options_v2 options_es = {
   option_cats_es,
   option_defs_es
};

/* RETRO_LANGUAGE_FA */

#define HANDY_ROT_LABEL_FA NULL
#define HANDY_ROT_INFO_0_FA "صفحه‌نمایش کنسول مجازی را بچرخانید تا به چیدمان صحیح بازی‌های «عمودی» روی یک نمایشگر معمولی (افقی) برسید."
#define OPTION_VAL_NONE_FA NULL
#define OPTION_VAL_270_FA NULL
#define OPTION_VAL_90_FA NULL
#define HANDY_GFX_COLORS_LABEL_FA NULL
#define HANDY_GFX_COLORS_INFO_0_FA "تعداد رنگ ها را برای نمایش روی صفحه مشخص کنید. 24 بیتی به طور قابل توجهی سربار عملکرد را افزایش می دهد و در همه سیستم ها در دسترس نیست."
#define OPTION_VAL_16BIT_FA NULL
#define OPTION_VAL_24BIT_FA NULL
#define HANDY_FRAMESKIP_LABEL_FA NULL
#define HANDY_FRAMESKIP_INFO_0_FA NULL
#define OPTION_VAL_AUTO_FA NULL
#define OPTION_VAL_MANUAL_FA NULL
#define HANDY_FRAMESKIP_THRESHOLD_LABEL_FA NULL
#define HANDY_FRAMESKIP_THRESHOLD_INFO_0_FA NULL

struct retro_core_option_v2_category option_cats_fa[] = {
   { NULL, NULL, NULL },
};
struct retro_core_option_v2_definition option_defs_fa[] = {
   {
      "handy_rot",
      HANDY_ROT_LABEL_FA,
      NULL,
      HANDY_ROT_INFO_0_FA,
      NULL,
      NULL,
      {
         { "None", OPTION_VAL_NONE_FA },
         { "270",  OPTION_VAL_270_FA },
         { "90",   OPTION_VAL_90_FA },
         { NULL, NULL },
      },
      "None"
   },
#if defined(FRONTEND_SUPPORTS_XRGB8888)
   {
      "handy_gfx_colors",
      HANDY_GFX_COLORS_LABEL_FA,
      NULL,
      HANDY_GFX_COLORS_INFO_0_FA,
      NULL,
      NULL,
      {
         { "16bit", OPTION_VAL_16BIT_FA },
         { "24bit", OPTION_VAL_24BIT_FA },
         { NULL,    NULL },
      },
      "16bit"
   },
#endif
   {
      "handy_frameskip",
      HANDY_FRAMESKIP_LABEL_FA,
      NULL,
      HANDY_FRAMESKIP_INFO_0_FA,
      NULL,
      NULL,
      {
         { "disabled", NULL },
         { "auto",     OPTION_VAL_AUTO_FA },
         { "manual",   OPTION_VAL_MANUAL_FA },
         { NULL, NULL },
      },
      "disabled"
   },
   {
      "handy_frameskip_threshold",
      HANDY_FRAMESKIP_THRESHOLD_LABEL_FA,
      NULL,
      HANDY_FRAMESKIP_THRESHOLD_INFO_0_FA,
      NULL,
      NULL,
      {
         { "15", NULL },
         { "18", NULL },
         { "21", NULL },
         { "24", NULL },
         { "27", NULL },
         { "30", NULL },
         { "33", NULL },
         { "36", NULL },
         { "39", NULL },
         { "42", NULL },
         { "45", NULL },
         { "48", NULL },
         { "51", NULL },
         { "54", NULL },
         { "57", NULL },
         { "60", NULL },
         { NULL, NULL },
      },
      "33"
   },
   { NULL, NULL, NULL, NULL, NULL, NULL, {{0}}, NULL },
};
struct retro_core_options_v2 options_fa = {
   option_cats_fa,
   option_defs_fa
};

/* RETRO_LANGUAGE_FI */

#define HANDY_ROT_LABEL_FI "Näytön kierto"
#define HANDY_ROT_INFO_0_FI "Kierrä virtuaalikonsolin näyttöä saadaksesi oikean ulkoasun tavallisella vaakatasonäytöllä sellaisille peleille, joiden oletuksena on pystykuvanäyttö."
#define OPTION_VAL_NONE_FI "Ei mitään"
#define OPTION_VAL_270_FI "Myötäpäivään"
#define OPTION_VAL_90_FI "Vastapäivään"
#define HANDY_GFX_COLORS_LABEL_FI "Värisyvyys (Uudelleenkäynnistys vaaditaan)"
#define HANDY_GFX_COLORS_INFO_0_FI "Määritä ruudulla näytettävien värien määrä. 24-bittinen kuormittaa suorituskykyä merkittävästi eikä ole käytettävissä kaikilla alustoilla."
#define OPTION_VAL_16BIT_FI "Tuhansissa (16-bit)"
#define OPTION_VAL_24BIT_FI "Miljoonissa (24-bittinen)"
#define HANDY_FRAMESKIP_LABEL_FI "Kuvanohitus"
#define HANDY_FRAMESKIP_INFO_0_FI "Ohita kuvia välttääksesi äänipuskurin ali ajon (säröily). Parantaa suorituskykyä visuaalisen tasaisuuden kustannuksella. \"Automaatti\" ohittaa kehykset käyttöliittymän asetusten mukaan. \"Manuaalinen\" käyttää \"Kuvienohituksen arvo (%)\" -asetusta."
#define OPTION_VAL_AUTO_FI "Automaattinen"
#define OPTION_VAL_MANUAL_FI "Manuaalinen"
#define HANDY_FRAMESKIP_THRESHOLD_LABEL_FI "Kuvienohituksen arvo (%)"
#define HANDY_FRAMESKIP_THRESHOLD_INFO_0_FI "Kun \"kehyksen ohitus\" on asetettu \"manuaaliksi\", määrittää äänipuskuri käyttökynnyksen (prosentteina), jonka alapuolella kehykset ohitetaan. Korkeammat arvot vähentävät särkymisen riskiä siten, että kehykset putoavat useammin."

struct retro_core_option_v2_category option_cats_fi[] = {
   { NULL, NULL, NULL },
};
struct retro_core_option_v2_definition option_defs_fi[] = {
   {
      "handy_rot",
      HANDY_ROT_LABEL_FI,
      NULL,
      HANDY_ROT_INFO_0_FI,
      NULL,
      NULL,
      {
         { "None", OPTION_VAL_NONE_FI },
         { "270",  OPTION_VAL_270_FI },
         { "90",   OPTION_VAL_90_FI },
         { NULL, NULL },
      },
      "None"
   },
#if defined(FRONTEND_SUPPORTS_XRGB8888)
   {
      "handy_gfx_colors",
      HANDY_GFX_COLORS_LABEL_FI,
      NULL,
      HANDY_GFX_COLORS_INFO_0_FI,
      NULL,
      NULL,
      {
         { "16bit", OPTION_VAL_16BIT_FI },
         { "24bit", OPTION_VAL_24BIT_FI },
         { NULL,    NULL },
      },
      "16bit"
   },
#endif
   {
      "handy_frameskip",
      HANDY_FRAMESKIP_LABEL_FI,
      NULL,
      HANDY_FRAMESKIP_INFO_0_FI,
      NULL,
      NULL,
      {
         { "disabled", NULL },
         { "auto",     OPTION_VAL_AUTO_FI },
         { "manual",   OPTION_VAL_MANUAL_FI },
         { NULL, NULL },
      },
      "disabled"
   },
   {
      "handy_frameskip_threshold",
      HANDY_FRAMESKIP_THRESHOLD_LABEL_FI,
      NULL,
      HANDY_FRAMESKIP_THRESHOLD_INFO_0_FI,
      NULL,
      NULL,
      {
         { "15", NULL },
         { "18", NULL },
         { "21", NULL },
         { "24", NULL },
         { "27", NULL },
         { "30", NULL },
         { "33", NULL },
         { "36", NULL },
         { "39", NULL },
         { "42", NULL },
         { "45", NULL },
         { "48", NULL },
         { "51", NULL },
         { "54", NULL },
         { "57", NULL },
         { "60", NULL },
         { NULL, NULL },
      },
      "33"
   },
   { NULL, NULL, NULL, NULL, NULL, NULL, {{0}}, NULL },
};
struct retro_core_options_v2 options_fi = {
   option_cats_fi,
   option_defs_fi
};

/* RETRO_LANGUAGE_FR */

#define HANDY_ROT_LABEL_FR "Rotation d'écran"
#define HANDY_ROT_INFO_0_FR "Faire pivoter l'écran de la console virtuelle pour obtenir la bonne présentation des jeux en mode 'portrait' sur un écran conventionnel (paysage)."
#define OPTION_VAL_NONE_FR "Aucune"
#define OPTION_VAL_270_FR "Horaire"
#define OPTION_VAL_90_FR "Anti-horaire"
#define HANDY_GFX_COLORS_LABEL_FR "Profondeur des couleurs (Redémarrage requis)"
#define HANDY_GFX_COLORS_INFO_0_FR "Spécifier le nombre de couleurs à afficher à l'écran. 24 bits augmente significativement la charge sur les performances et n'est pas disponible pour toutes les plateformes."
#define OPTION_VAL_16BIT_FR "Milliers (16 bits)"
#define OPTION_VAL_24BIT_FR "Millions (24 bits)"
#define HANDY_FRAMESKIP_LABEL_FR "Saut d'images"
#define HANDY_FRAMESKIP_INFO_0_FR "Sauter des images pour éviter que le tampon audio ne soit sous-exécuté (crépitements). Améliore les performances au détriment de la fluidité visuelle. 'Auto' saute des images lorsque le frontend le conseille. 'Manuel' utilise le paramètre 'Seuil de saut d'images (%)'."
#define OPTION_VAL_AUTO_FR NULL
#define OPTION_VAL_MANUAL_FR "Manuel"
#define HANDY_FRAMESKIP_THRESHOLD_LABEL_FR "Seuil de saut d'images (%)"
#define HANDY_FRAMESKIP_THRESHOLD_INFO_0_FR "Lorsque 'Saut d'images' est réglé sur 'Manuel', spécifie le seuil d'occupation du tampon audio (pourcentage) en dessous duquel des images seront sautées. Des valeurs plus élevées réduisent le risque de crépitements en faisant sauter des images plus fréquemment."

struct retro_core_option_v2_category option_cats_fr[] = {
   { NULL, NULL, NULL },
};
struct retro_core_option_v2_definition option_defs_fr[] = {
   {
      "handy_rot",
      HANDY_ROT_LABEL_FR,
      NULL,
      HANDY_ROT_INFO_0_FR,
      NULL,
      NULL,
      {
         { "None", OPTION_VAL_NONE_FR },
         { "270",  OPTION_VAL_270_FR },
         { "90",   OPTION_VAL_90_FR },
         { NULL, NULL },
      },
      "None"
   },
#if defined(FRONTEND_SUPPORTS_XRGB8888)
   {
      "handy_gfx_colors",
      HANDY_GFX_COLORS_LABEL_FR,
      NULL,
      HANDY_GFX_COLORS_INFO_0_FR,
      NULL,
      NULL,
      {
         { "16bit", OPTION_VAL_16BIT_FR },
         { "24bit", OPTION_VAL_24BIT_FR },
         { NULL,    NULL },
      },
      "16bit"
   },
#endif
   {
      "handy_frameskip",
      HANDY_FRAMESKIP_LABEL_FR,
      NULL,
      HANDY_FRAMESKIP_INFO_0_FR,
      NULL,
      NULL,
      {
         { "disabled", NULL },
         { "auto",     OPTION_VAL_AUTO_FR },
         { "manual",   OPTION_VAL_MANUAL_FR },
         { NULL, NULL },
      },
      "disabled"
   },
   {
      "handy_frameskip_threshold",
      HANDY_FRAMESKIP_THRESHOLD_LABEL_FR,
      NULL,
      HANDY_FRAMESKIP_THRESHOLD_INFO_0_FR,
      NULL,
      NULL,
      {
         { "15", NULL },
         { "18", NULL },
         { "21", NULL },
         { "24", NULL },
         { "27", NULL },
         { "30", NULL },
         { "33", NULL },
         { "36", NULL },
         { "39", NULL },
         { "42", NULL },
         { "45", NULL },
         { "48", NULL },
         { "51", NULL },
         { "54", NULL },
         { "57", NULL },
         { "60", NULL },
         { NULL, NULL },
      },
      "33"
   },
   { NULL, NULL, NULL, NULL, NULL, NULL, {{0}}, NULL },
};
struct retro_core_options_v2 options_fr = {
   option_cats_fr,
   option_defs_fr
};

/* RETRO_LANGUAGE_GL */

#define HANDY_ROT_LABEL_GL NULL
#define HANDY_ROT_INFO_0_GL NULL
#define OPTION_VAL_NONE_GL "Ningún"
#define OPTION_VAL_270_GL NULL
#define OPTION_VAL_90_GL NULL
#define HANDY_GFX_COLORS_LABEL_GL NULL
#define HANDY_GFX_COLORS_INFO_0_GL NULL
#define OPTION_VAL_16BIT_GL NULL
#define OPTION_VAL_24BIT_GL NULL
#define HANDY_FRAMESKIP_LABEL_GL NULL
#define HANDY_FRAMESKIP_INFO_0_GL NULL
#define OPTION_VAL_AUTO_GL NULL
#define OPTION_VAL_MANUAL_GL NULL
#define HANDY_FRAMESKIP_THRESHOLD_LABEL_GL NULL
#define HANDY_FRAMESKIP_THRESHOLD_INFO_0_GL "Cando a omisión de fotogramas sexa configurada en 'Manual', este axuste especifíca o umbral de ocupación do búfer de audio (en porcentaxe). Os valores altos reducen o risco de aparición de chasquidos omitindo fotogramas de forma máis frecuente."

struct retro_core_option_v2_category option_cats_gl[] = {
   { NULL, NULL, NULL },
};
struct retro_core_option_v2_definition option_defs_gl[] = {
   {
      "handy_rot",
      HANDY_ROT_LABEL_GL,
      NULL,
      HANDY_ROT_INFO_0_GL,
      NULL,
      NULL,
      {
         { "None", OPTION_VAL_NONE_GL },
         { "270",  OPTION_VAL_270_GL },
         { "90",   OPTION_VAL_90_GL },
         { NULL, NULL },
      },
      "None"
   },
#if defined(FRONTEND_SUPPORTS_XRGB8888)
   {
      "handy_gfx_colors",
      HANDY_GFX_COLORS_LABEL_GL,
      NULL,
      HANDY_GFX_COLORS_INFO_0_GL,
      NULL,
      NULL,
      {
         { "16bit", OPTION_VAL_16BIT_GL },
         { "24bit", OPTION_VAL_24BIT_GL },
         { NULL,    NULL },
      },
      "16bit"
   },
#endif
   {
      "handy_frameskip",
      HANDY_FRAMESKIP_LABEL_GL,
      NULL,
      HANDY_FRAMESKIP_INFO_0_GL,
      NULL,
      NULL,
      {
         { "disabled", NULL },
         { "auto",     OPTION_VAL_AUTO_GL },
         { "manual",   OPTION_VAL_MANUAL_GL },
         { NULL, NULL },
      },
      "disabled"
   },
   {
      "handy_frameskip_threshold",
      HANDY_FRAMESKIP_THRESHOLD_LABEL_GL,
      NULL,
      HANDY_FRAMESKIP_THRESHOLD_INFO_0_GL,
      NULL,
      NULL,
      {
         { "15", NULL },
         { "18", NULL },
         { "21", NULL },
         { "24", NULL },
         { "27", NULL },
         { "30", NULL },
         { "33", NULL },
         { "36", NULL },
         { "39", NULL },
         { "42", NULL },
         { "45", NULL },
         { "48", NULL },
         { "51", NULL },
         { "54", NULL },
         { "57", NULL },
         { "60", NULL },
         { NULL, NULL },
      },
      "33"
   },
   { NULL, NULL, NULL, NULL, NULL, NULL, {{0}}, NULL },
};
struct retro_core_options_v2 options_gl = {
   option_cats_gl,
   option_defs_gl
};

/* RETRO_LANGUAGE_HE */

#define HANDY_ROT_LABEL_HE NULL
#define HANDY_ROT_INFO_0_HE NULL
#define OPTION_VAL_NONE_HE NULL
#define OPTION_VAL_270_HE NULL
#define OPTION_VAL_90_HE NULL
#define HANDY_GFX_COLORS_LABEL_HE NULL
#define HANDY_GFX_COLORS_INFO_0_HE NULL
#define OPTION_VAL_16BIT_HE NULL
#define OPTION_VAL_24BIT_HE NULL
#define HANDY_FRAMESKIP_LABEL_HE NULL
#define HANDY_FRAMESKIP_INFO_0_HE NULL
#define OPTION_VAL_AUTO_HE NULL
#define OPTION_VAL_MANUAL_HE NULL
#define HANDY_FRAMESKIP_THRESHOLD_LABEL_HE NULL
#define HANDY_FRAMESKIP_THRESHOLD_INFO_0_HE NULL

struct retro_core_option_v2_category option_cats_he[] = {
   { NULL, NULL, NULL },
};
struct retro_core_option_v2_definition option_defs_he[] = {
   {
      "handy_rot",
      HANDY_ROT_LABEL_HE,
      NULL,
      HANDY_ROT_INFO_0_HE,
      NULL,
      NULL,
      {
         { "None", OPTION_VAL_NONE_HE },
         { "270",  OPTION_VAL_270_HE },
         { "90",   OPTION_VAL_90_HE },
         { NULL, NULL },
      },
      "None"
   },
#if defined(FRONTEND_SUPPORTS_XRGB8888)
   {
      "handy_gfx_colors",
      HANDY_GFX_COLORS_LABEL_HE,
      NULL,
      HANDY_GFX_COLORS_INFO_0_HE,
      NULL,
      NULL,
      {
         { "16bit", OPTION_VAL_16BIT_HE },
         { "24bit", OPTION_VAL_24BIT_HE },
         { NULL,    NULL },
      },
      "16bit"
   },
#endif
   {
      "handy_frameskip",
      HANDY_FRAMESKIP_LABEL_HE,
      NULL,
      HANDY_FRAMESKIP_INFO_0_HE,
      NULL,
      NULL,
      {
         { "disabled", NULL },
         { "auto",     OPTION_VAL_AUTO_HE },
         { "manual",   OPTION_VAL_MANUAL_HE },
         { NULL, NULL },
      },
      "disabled"
   },
   {
      "handy_frameskip_threshold",
      HANDY_FRAMESKIP_THRESHOLD_LABEL_HE,
      NULL,
      HANDY_FRAMESKIP_THRESHOLD_INFO_0_HE,
      NULL,
      NULL,
      {
         { "15", NULL },
         { "18", NULL },
         { "21", NULL },
         { "24", NULL },
         { "27", NULL },
         { "30", NULL },
         { "33", NULL },
         { "36", NULL },
         { "39", NULL },
         { "42", NULL },
         { "45", NULL },
         { "48", NULL },
         { "51", NULL },
         { "54", NULL },
         { "57", NULL },
         { "60", NULL },
         { NULL, NULL },
      },
      "33"
   },
   { NULL, NULL, NULL, NULL, NULL, NULL, {{0}}, NULL },
};
struct retro_core_options_v2 options_he = {
   option_cats_he,
   option_defs_he
};

/* RETRO_LANGUAGE_HU */

#define HANDY_ROT_LABEL_HU NULL
#define HANDY_ROT_INFO_0_HU NULL
#define OPTION_VAL_NONE_HU NULL
#define OPTION_VAL_270_HU NULL
#define OPTION_VAL_90_HU NULL
#define HANDY_GFX_COLORS_LABEL_HU NULL
#define HANDY_GFX_COLORS_INFO_0_HU NULL
#define OPTION_VAL_16BIT_HU NULL
#define OPTION_VAL_24BIT_HU NULL
#define HANDY_FRAMESKIP_LABEL_HU NULL
#define HANDY_FRAMESKIP_INFO_0_HU NULL
#define OPTION_VAL_AUTO_HU NULL
#define OPTION_VAL_MANUAL_HU "Kézi"
#define HANDY_FRAMESKIP_THRESHOLD_LABEL_HU NULL
#define HANDY_FRAMESKIP_THRESHOLD_INFO_0_HU NULL

struct retro_core_option_v2_category option_cats_hu[] = {
   { NULL, NULL, NULL },
};
struct retro_core_option_v2_definition option_defs_hu[] = {
   {
      "handy_rot",
      HANDY_ROT_LABEL_HU,
      NULL,
      HANDY_ROT_INFO_0_HU,
      NULL,
      NULL,
      {
         { "None", OPTION_VAL_NONE_HU },
         { "270",  OPTION_VAL_270_HU },
         { "90",   OPTION_VAL_90_HU },
         { NULL, NULL },
      },
      "None"
   },
#if defined(FRONTEND_SUPPORTS_XRGB8888)
   {
      "handy_gfx_colors",
      HANDY_GFX_COLORS_LABEL_HU,
      NULL,
      HANDY_GFX_COLORS_INFO_0_HU,
      NULL,
      NULL,
      {
         { "16bit", OPTION_VAL_16BIT_HU },
         { "24bit", OPTION_VAL_24BIT_HU },
         { NULL,    NULL },
      },
      "16bit"
   },
#endif
   {
      "handy_frameskip",
      HANDY_FRAMESKIP_LABEL_HU,
      NULL,
      HANDY_FRAMESKIP_INFO_0_HU,
      NULL,
      NULL,
      {
         { "disabled", NULL },
         { "auto",     OPTION_VAL_AUTO_HU },
         { "manual",   OPTION_VAL_MANUAL_HU },
         { NULL, NULL },
      },
      "disabled"
   },
   {
      "handy_frameskip_threshold",
      HANDY_FRAMESKIP_THRESHOLD_LABEL_HU,
      NULL,
      HANDY_FRAMESKIP_THRESHOLD_INFO_0_HU,
      NULL,
      NULL,
      {
         { "15", NULL },
         { "18", NULL },
         { "21", NULL },
         { "24", NULL },
         { "27", NULL },
         { "30", NULL },
         { "33", NULL },
         { "36", NULL },
         { "39", NULL },
         { "42", NULL },
         { "45", NULL },
         { "48", NULL },
         { "51", NULL },
         { "54", NULL },
         { "57", NULL },
         { "60", NULL },
         { NULL, NULL },
      },
      "33"
   },
   { NULL, NULL, NULL, NULL, NULL, NULL, {{0}}, NULL },
};
struct retro_core_options_v2 options_hu = {
   option_cats_hu,
   option_defs_hu
};

/* RETRO_LANGUAGE_ID */

#define HANDY_ROT_LABEL_ID NULL
#define HANDY_ROT_INFO_0_ID "Putar orientasi layar untuk mendapat tampilan layout konsol virtual game 'potret' yang tepat pada layar konvensional (lanskap)."
#define OPTION_VAL_NONE_ID NULL
#define OPTION_VAL_270_ID NULL
#define OPTION_VAL_90_ID NULL
#define HANDY_GFX_COLORS_LABEL_ID NULL
#define HANDY_GFX_COLORS_INFO_0_ID "Pilih kedalaman warna untuk ditampilkan di layar. Kedalaman warna 24-bit meningkatkan performa secara signifikan dan tidak tersedia di semua platform."
#define OPTION_VAL_16BIT_ID NULL
#define OPTION_VAL_24BIT_ID NULL
#define HANDY_FRAMESKIP_LABEL_ID NULL
#define HANDY_FRAMESKIP_INFO_0_ID NULL
#define OPTION_VAL_AUTO_ID NULL
#define OPTION_VAL_MANUAL_ID NULL
#define HANDY_FRAMESKIP_THRESHOLD_LABEL_ID NULL
#define HANDY_FRAMESKIP_THRESHOLD_INFO_0_ID "Saat 'Frameskip' di setel ke 'Manual', tentukan ambang batas hunian buffer audio (persentase) di bawah frame mana yang akan dilewati. Nilai yang lebih tinggi mengurangi risiko keretakan dengan menyebabkan bingkai frame lebih sering dijatuhkan."

struct retro_core_option_v2_category option_cats_id[] = {
   { NULL, NULL, NULL },
};
struct retro_core_option_v2_definition option_defs_id[] = {
   {
      "handy_rot",
      HANDY_ROT_LABEL_ID,
      NULL,
      HANDY_ROT_INFO_0_ID,
      NULL,
      NULL,
      {
         { "None", OPTION_VAL_NONE_ID },
         { "270",  OPTION_VAL_270_ID },
         { "90",   OPTION_VAL_90_ID },
         { NULL, NULL },
      },
      "None"
   },
#if defined(FRONTEND_SUPPORTS_XRGB8888)
   {
      "handy_gfx_colors",
      HANDY_GFX_COLORS_LABEL_ID,
      NULL,
      HANDY_GFX_COLORS_INFO_0_ID,
      NULL,
      NULL,
      {
         { "16bit", OPTION_VAL_16BIT_ID },
         { "24bit", OPTION_VAL_24BIT_ID },
         { NULL,    NULL },
      },
      "16bit"
   },
#endif
   {
      "handy_frameskip",
      HANDY_FRAMESKIP_LABEL_ID,
      NULL,
      HANDY_FRAMESKIP_INFO_0_ID,
      NULL,
      NULL,
      {
         { "disabled", NULL },
         { "auto",     OPTION_VAL_AUTO_ID },
         { "manual",   OPTION_VAL_MANUAL_ID },
         { NULL, NULL },
      },
      "disabled"
   },
   {
      "handy_frameskip_threshold",
      HANDY_FRAMESKIP_THRESHOLD_LABEL_ID,
      NULL,
      HANDY_FRAMESKIP_THRESHOLD_INFO_0_ID,
      NULL,
      NULL,
      {
         { "15", NULL },
         { "18", NULL },
         { "21", NULL },
         { "24", NULL },
         { "27", NULL },
         { "30", NULL },
         { "33", NULL },
         { "36", NULL },
         { "39", NULL },
         { "42", NULL },
         { "45", NULL },
         { "48", NULL },
         { "51", NULL },
         { "54", NULL },
         { "57", NULL },
         { "60", NULL },
         { NULL, NULL },
      },
      "33"
   },
   { NULL, NULL, NULL, NULL, NULL, NULL, {{0}}, NULL },
};
struct retro_core_options_v2 options_id = {
   option_cats_id,
   option_defs_id
};

/* RETRO_LANGUAGE_IT */

#define HANDY_ROT_LABEL_IT "Rotazione Display"
#define HANDY_ROT_INFO_0_IT "Ruota lo schermo della console virtuale per ottenere il corretto layout dei giochi orientati al 'ritratto' su uno schermo convenzionale (orizzontale)."
#define OPTION_VAL_NONE_IT "Nessuno"
#define OPTION_VAL_270_IT "Orario"
#define OPTION_VAL_90_IT "Anticorveglianza"
#define HANDY_GFX_COLORS_LABEL_IT "Profondità Colore (Restart Richiesto)"
#define HANDY_GFX_COLORS_INFO_0_IT "Specifica il numero di colori da visualizzare sullo schermo. 24-bit aumenta significativamente le prestazioni generali e non è disponibile su tutte le piattaforme."
#define OPTION_VAL_16BIT_IT "Migliaia (16-bit)"
#define OPTION_VAL_24BIT_IT "Milioni (24-bit)"
#define HANDY_FRAMESKIP_LABEL_IT "Salta fotogramma"
#define HANDY_FRAMESKIP_INFO_0_IT "Salta i fotogrammi per evitare la sottoesecuzione del buffer audio (crackling). Migliora le prestazioni a scapito della fluidità visiva. 'Auto' salta i quadri quando consigliato dal frontend. 'Manuale' utilizza l'impostazione 'Frameskip Threshold (%)'."
#define OPTION_VAL_AUTO_IT NULL
#define OPTION_VAL_MANUAL_IT "Manuale"
#define HANDY_FRAMESKIP_THRESHOLD_LABEL_IT "Soglia Frameskip (%)"
#define HANDY_FRAMESKIP_THRESHOLD_INFO_0_IT "Quando 'Frameskip' è impostato a 'Manuale', specifica la soglia di occupazione del buffer audio (percentuale) al di sotto della quale i frame verranno saltati. Valori più elevati riducono il rischio di crepitii audio saltando i frame più frequentemente."

struct retro_core_option_v2_category option_cats_it[] = {
   { NULL, NULL, NULL },
};
struct retro_core_option_v2_definition option_defs_it[] = {
   {
      "handy_rot",
      HANDY_ROT_LABEL_IT,
      NULL,
      HANDY_ROT_INFO_0_IT,
      NULL,
      NULL,
      {
         { "None", OPTION_VAL_NONE_IT },
         { "270",  OPTION_VAL_270_IT },
         { "90",   OPTION_VAL_90_IT },
         { NULL, NULL },
      },
      "None"
   },
#if defined(FRONTEND_SUPPORTS_XRGB8888)
   {
      "handy_gfx_colors",
      HANDY_GFX_COLORS_LABEL_IT,
      NULL,
      HANDY_GFX_COLORS_INFO_0_IT,
      NULL,
      NULL,
      {
         { "16bit", OPTION_VAL_16BIT_IT },
         { "24bit", OPTION_VAL_24BIT_IT },
         { NULL,    NULL },
      },
      "16bit"
   },
#endif
   {
      "handy_frameskip",
      HANDY_FRAMESKIP_LABEL_IT,
      NULL,
      HANDY_FRAMESKIP_INFO_0_IT,
      NULL,
      NULL,
      {
         { "disabled", NULL },
         { "auto",     OPTION_VAL_AUTO_IT },
         { "manual",   OPTION_VAL_MANUAL_IT },
         { NULL, NULL },
      },
      "disabled"
   },
   {
      "handy_frameskip_threshold",
      HANDY_FRAMESKIP_THRESHOLD_LABEL_IT,
      NULL,
      HANDY_FRAMESKIP_THRESHOLD_INFO_0_IT,
      NULL,
      NULL,
      {
         { "15", NULL },
         { "18", NULL },
         { "21", NULL },
         { "24", NULL },
         { "27", NULL },
         { "30", NULL },
         { "33", NULL },
         { "36", NULL },
         { "39", NULL },
         { "42", NULL },
         { "45", NULL },
         { "48", NULL },
         { "51", NULL },
         { "54", NULL },
         { "57", NULL },
         { "60", NULL },
         { NULL, NULL },
      },
      "33"
   },
   { NULL, NULL, NULL, NULL, NULL, NULL, {{0}}, NULL },
};
struct retro_core_options_v2 options_it = {
   option_cats_it,
   option_defs_it
};

/* RETRO_LANGUAGE_JA */

#define HANDY_ROT_LABEL_JA "ディスプレイの回転"
#define HANDY_ROT_INFO_0_JA "仮想コンソール画面を回転させ, 従来の(横長画面) ディスプレイ上で縦長画面のゲームの正しいレイアウトを実現します."
#define OPTION_VAL_NONE_JA "なし"
#define OPTION_VAL_270_JA "時計回り"
#define OPTION_VAL_90_JA "反時計回り"
#define HANDY_GFX_COLORS_LABEL_JA "色深度 (再起動が必要)"
#define HANDY_GFX_COLORS_INFO_0_JA "画面上に表示色数を指定します. 24ビットは負荷が大幅に増加するため, 利用できないプラットフォームもあります."
#define OPTION_VAL_16BIT_JA "数千 (16ビット)"
#define OPTION_VAL_24BIT_JA "数百万 (24ビット)"
#define HANDY_FRAMESKIP_LABEL_JA "フレームスキップ"
#define HANDY_FRAMESKIP_INFO_0_JA "フレームをスキップしてオーディオバッファアンダーラン (音割れ) を回避します。視覚的な滑らかさを犠牲にしてパフォーマンスを向上させます。 「自動」は、フロントエンドにアドバイスされたときにフレームをスキップします。「マニュアル」は、「フレームスキップ閾値 (%)」設定を使用します。"
#define OPTION_VAL_AUTO_JA "自動"
#define OPTION_VAL_MANUAL_JA "手動"
#define HANDY_FRAMESKIP_THRESHOLD_LABEL_JA "フレームスキップ閾値 (%)"
#define HANDY_FRAMESKIP_THRESHOLD_INFO_0_JA "'フレームスキップ' が '手動' に設定されている場合, フレームがスキップされるオーディオバッファ占有しきい値 (%) を指定します. 値を大きくすると, フレームを頻繁に落とすことでクラッキングが発生するリスクが低下します."

struct retro_core_option_v2_category option_cats_ja[] = {
   { NULL, NULL, NULL },
};
struct retro_core_option_v2_definition option_defs_ja[] = {
   {
      "handy_rot",
      HANDY_ROT_LABEL_JA,
      NULL,
      HANDY_ROT_INFO_0_JA,
      NULL,
      NULL,
      {
         { "None", OPTION_VAL_NONE_JA },
         { "270",  OPTION_VAL_270_JA },
         { "90",   OPTION_VAL_90_JA },
         { NULL, NULL },
      },
      "None"
   },
#if defined(FRONTEND_SUPPORTS_XRGB8888)
   {
      "handy_gfx_colors",
      HANDY_GFX_COLORS_LABEL_JA,
      NULL,
      HANDY_GFX_COLORS_INFO_0_JA,
      NULL,
      NULL,
      {
         { "16bit", OPTION_VAL_16BIT_JA },
         { "24bit", OPTION_VAL_24BIT_JA },
         { NULL,    NULL },
      },
      "16bit"
   },
#endif
   {
      "handy_frameskip",
      HANDY_FRAMESKIP_LABEL_JA,
      NULL,
      HANDY_FRAMESKIP_INFO_0_JA,
      NULL,
      NULL,
      {
         { "disabled", NULL },
         { "auto",     OPTION_VAL_AUTO_JA },
         { "manual",   OPTION_VAL_MANUAL_JA },
         { NULL, NULL },
      },
      "disabled"
   },
   {
      "handy_frameskip_threshold",
      HANDY_FRAMESKIP_THRESHOLD_LABEL_JA,
      NULL,
      HANDY_FRAMESKIP_THRESHOLD_INFO_0_JA,
      NULL,
      NULL,
      {
         { "15", NULL },
         { "18", NULL },
         { "21", NULL },
         { "24", NULL },
         { "27", NULL },
         { "30", NULL },
         { "33", NULL },
         { "36", NULL },
         { "39", NULL },
         { "42", NULL },
         { "45", NULL },
         { "48", NULL },
         { "51", NULL },
         { "54", NULL },
         { "57", NULL },
         { "60", NULL },
         { NULL, NULL },
      },
      "33"
   },
   { NULL, NULL, NULL, NULL, NULL, NULL, {{0}}, NULL },
};
struct retro_core_options_v2 options_ja = {
   option_cats_ja,
   option_defs_ja
};

/* RETRO_LANGUAGE_KO */

#define HANDY_ROT_LABEL_KO "화면 회전"
#define HANDY_ROT_INFO_0_KO "가상 콘솔 화면을 회전시켜 '세로' 화면을 사용하는 게임들이 일반적인 가로 화면에서도 올바르게 표시되도록 합니다."
#define OPTION_VAL_NONE_KO "없음"
#define OPTION_VAL_270_KO "시계방향"
#define OPTION_VAL_90_KO "반시계방향"
#define HANDY_GFX_COLORS_LABEL_KO "색 깊이 (재시작 필요)"
#define HANDY_GFX_COLORS_INFO_0_KO "화면에 표시할 색상 수를 지정합니다. 24비트는 성능에 큰 영향을 끼치며 일부 기기에서는 사용할 수 없습니다."
#define OPTION_VAL_16BIT_KO "수천가지 (16비트)"
#define OPTION_VAL_24BIT_KO "수백만가지 (24비트)"
#define HANDY_FRAMESKIP_LABEL_KO "프레임 스킵"
#define HANDY_FRAMESKIP_INFO_0_KO "오디오 버퍼 언더런(소리깨짐) 을 줄이기 위해 프레임 건너뛰기를 합니다. 시각적인 부드러움을 포기하는 대신 성능이 향상됩니다. '자동'은 프론트엔드의 추천값으로 실행되고 '사용자 설정'은 '프레임 스킵 임계값(%)' 설정을 이용해 실행됩니다."
#define OPTION_VAL_AUTO_KO "자동"
#define OPTION_VAL_MANUAL_KO "사용자 설정"
#define HANDY_FRAMESKIP_THRESHOLD_LABEL_KO "프레임 스킵 임계값 (%)"
#define HANDY_FRAMESKIP_THRESHOLD_INFO_0_KO "'프레임 건너뛰기'가 '사용자 설정'일 경우 건너뛸 프레임에 대한 오디오 버퍼 점유 임계점 (퍼센트) 을 설정하게됩니다. 값이 높을 수록 프레임은 떨어지고 그 대신 소리 깨짐 현상은 줄어들게 됩니다."

struct retro_core_option_v2_category option_cats_ko[] = {
   { NULL, NULL, NULL },
};
struct retro_core_option_v2_definition option_defs_ko[] = {
   {
      "handy_rot",
      HANDY_ROT_LABEL_KO,
      NULL,
      HANDY_ROT_INFO_0_KO,
      NULL,
      NULL,
      {
         { "None", OPTION_VAL_NONE_KO },
         { "270",  OPTION_VAL_270_KO },
         { "90",   OPTION_VAL_90_KO },
         { NULL, NULL },
      },
      "None"
   },
#if defined(FRONTEND_SUPPORTS_XRGB8888)
   {
      "handy_gfx_colors",
      HANDY_GFX_COLORS_LABEL_KO,
      NULL,
      HANDY_GFX_COLORS_INFO_0_KO,
      NULL,
      NULL,
      {
         { "16bit", OPTION_VAL_16BIT_KO },
         { "24bit", OPTION_VAL_24BIT_KO },
         { NULL,    NULL },
      },
      "16bit"
   },
#endif
   {
      "handy_frameskip",
      HANDY_FRAMESKIP_LABEL_KO,
      NULL,
      HANDY_FRAMESKIP_INFO_0_KO,
      NULL,
      NULL,
      {
         { "disabled", NULL },
         { "auto",     OPTION_VAL_AUTO_KO },
         { "manual",   OPTION_VAL_MANUAL_KO },
         { NULL, NULL },
      },
      "disabled"
   },
   {
      "handy_frameskip_threshold",
      HANDY_FRAMESKIP_THRESHOLD_LABEL_KO,
      NULL,
      HANDY_FRAMESKIP_THRESHOLD_INFO_0_KO,
      NULL,
      NULL,
      {
         { "15", NULL },
         { "18", NULL },
         { "21", NULL },
         { "24", NULL },
         { "27", NULL },
         { "30", NULL },
         { "33", NULL },
         { "36", NULL },
         { "39", NULL },
         { "42", NULL },
         { "45", NULL },
         { "48", NULL },
         { "51", NULL },
         { "54", NULL },
         { "57", NULL },
         { "60", NULL },
         { NULL, NULL },
      },
      "33"
   },
   { NULL, NULL, NULL, NULL, NULL, NULL, {{0}}, NULL },
};
struct retro_core_options_v2 options_ko = {
   option_cats_ko,
   option_defs_ko
};

/* RETRO_LANGUAGE_MT */

#define HANDY_ROT_LABEL_MT NULL
#define HANDY_ROT_INFO_0_MT NULL
#define OPTION_VAL_NONE_MT NULL
#define OPTION_VAL_270_MT NULL
#define OPTION_VAL_90_MT NULL
#define HANDY_GFX_COLORS_LABEL_MT NULL
#define HANDY_GFX_COLORS_INFO_0_MT NULL
#define OPTION_VAL_16BIT_MT NULL
#define OPTION_VAL_24BIT_MT NULL
#define HANDY_FRAMESKIP_LABEL_MT NULL
#define HANDY_FRAMESKIP_INFO_0_MT NULL
#define OPTION_VAL_AUTO_MT NULL
#define OPTION_VAL_MANUAL_MT NULL
#define HANDY_FRAMESKIP_THRESHOLD_LABEL_MT NULL
#define HANDY_FRAMESKIP_THRESHOLD_INFO_0_MT NULL

struct retro_core_option_v2_category option_cats_mt[] = {
   { NULL, NULL, NULL },
};
struct retro_core_option_v2_definition option_defs_mt[] = {
   {
      "handy_rot",
      HANDY_ROT_LABEL_MT,
      NULL,
      HANDY_ROT_INFO_0_MT,
      NULL,
      NULL,
      {
         { "None", OPTION_VAL_NONE_MT },
         { "270",  OPTION_VAL_270_MT },
         { "90",   OPTION_VAL_90_MT },
         { NULL, NULL },
      },
      "None"
   },
#if defined(FRONTEND_SUPPORTS_XRGB8888)
   {
      "handy_gfx_colors",
      HANDY_GFX_COLORS_LABEL_MT,
      NULL,
      HANDY_GFX_COLORS_INFO_0_MT,
      NULL,
      NULL,
      {
         { "16bit", OPTION_VAL_16BIT_MT },
         { "24bit", OPTION_VAL_24BIT_MT },
         { NULL,    NULL },
      },
      "16bit"
   },
#endif
   {
      "handy_frameskip",
      HANDY_FRAMESKIP_LABEL_MT,
      NULL,
      HANDY_FRAMESKIP_INFO_0_MT,
      NULL,
      NULL,
      {
         { "disabled", NULL },
         { "auto",     OPTION_VAL_AUTO_MT },
         { "manual",   OPTION_VAL_MANUAL_MT },
         { NULL, NULL },
      },
      "disabled"
   },
   {
      "handy_frameskip_threshold",
      HANDY_FRAMESKIP_THRESHOLD_LABEL_MT,
      NULL,
      HANDY_FRAMESKIP_THRESHOLD_INFO_0_MT,
      NULL,
      NULL,
      {
         { "15", NULL },
         { "18", NULL },
         { "21", NULL },
         { "24", NULL },
         { "27", NULL },
         { "30", NULL },
         { "33", NULL },
         { "36", NULL },
         { "39", NULL },
         { "42", NULL },
         { "45", NULL },
         { "48", NULL },
         { "51", NULL },
         { "54", NULL },
         { "57", NULL },
         { "60", NULL },
         { NULL, NULL },
      },
      "33"
   },
   { NULL, NULL, NULL, NULL, NULL, NULL, {{0}}, NULL },
};
struct retro_core_options_v2 options_mt = {
   option_cats_mt,
   option_defs_mt
};

/* RETRO_LANGUAGE_NL */

#define HANDY_ROT_LABEL_NL NULL
#define HANDY_ROT_INFO_0_NL NULL
#define OPTION_VAL_NONE_NL "Geen"
#define OPTION_VAL_270_NL NULL
#define OPTION_VAL_90_NL NULL
#define HANDY_GFX_COLORS_LABEL_NL NULL
#define HANDY_GFX_COLORS_INFO_0_NL NULL
#define OPTION_VAL_16BIT_NL NULL
#define OPTION_VAL_24BIT_NL NULL
#define HANDY_FRAMESKIP_LABEL_NL NULL
#define HANDY_FRAMESKIP_INFO_0_NL NULL
#define OPTION_VAL_AUTO_NL "Automatisch"
#define OPTION_VAL_MANUAL_NL NULL
#define HANDY_FRAMESKIP_THRESHOLD_LABEL_NL NULL
#define HANDY_FRAMESKIP_THRESHOLD_INFO_0_NL NULL

struct retro_core_option_v2_category option_cats_nl[] = {
   { NULL, NULL, NULL },
};
struct retro_core_option_v2_definition option_defs_nl[] = {
   {
      "handy_rot",
      HANDY_ROT_LABEL_NL,
      NULL,
      HANDY_ROT_INFO_0_NL,
      NULL,
      NULL,
      {
         { "None", OPTION_VAL_NONE_NL },
         { "270",  OPTION_VAL_270_NL },
         { "90",   OPTION_VAL_90_NL },
         { NULL, NULL },
      },
      "None"
   },
#if defined(FRONTEND_SUPPORTS_XRGB8888)
   {
      "handy_gfx_colors",
      HANDY_GFX_COLORS_LABEL_NL,
      NULL,
      HANDY_GFX_COLORS_INFO_0_NL,
      NULL,
      NULL,
      {
         { "16bit", OPTION_VAL_16BIT_NL },
         { "24bit", OPTION_VAL_24BIT_NL },
         { NULL,    NULL },
      },
      "16bit"
   },
#endif
   {
      "handy_frameskip",
      HANDY_FRAMESKIP_LABEL_NL,
      NULL,
      HANDY_FRAMESKIP_INFO_0_NL,
      NULL,
      NULL,
      {
         { "disabled", NULL },
         { "auto",     OPTION_VAL_AUTO_NL },
         { "manual",   OPTION_VAL_MANUAL_NL },
         { NULL, NULL },
      },
      "disabled"
   },
   {
      "handy_frameskip_threshold",
      HANDY_FRAMESKIP_THRESHOLD_LABEL_NL,
      NULL,
      HANDY_FRAMESKIP_THRESHOLD_INFO_0_NL,
      NULL,
      NULL,
      {
         { "15", NULL },
         { "18", NULL },
         { "21", NULL },
         { "24", NULL },
         { "27", NULL },
         { "30", NULL },
         { "33", NULL },
         { "36", NULL },
         { "39", NULL },
         { "42", NULL },
         { "45", NULL },
         { "48", NULL },
         { "51", NULL },
         { "54", NULL },
         { "57", NULL },
         { "60", NULL },
         { NULL, NULL },
      },
      "33"
   },
   { NULL, NULL, NULL, NULL, NULL, NULL, {{0}}, NULL },
};
struct retro_core_options_v2 options_nl = {
   option_cats_nl,
   option_defs_nl
};

/* RETRO_LANGUAGE_OC */

#define HANDY_ROT_LABEL_OC NULL
#define HANDY_ROT_INFO_0_OC NULL
#define OPTION_VAL_NONE_OC NULL
#define OPTION_VAL_270_OC NULL
#define OPTION_VAL_90_OC NULL
#define HANDY_GFX_COLORS_LABEL_OC NULL
#define HANDY_GFX_COLORS_INFO_0_OC NULL
#define OPTION_VAL_16BIT_OC NULL
#define OPTION_VAL_24BIT_OC NULL
#define HANDY_FRAMESKIP_LABEL_OC NULL
#define HANDY_FRAMESKIP_INFO_0_OC NULL
#define OPTION_VAL_AUTO_OC NULL
#define OPTION_VAL_MANUAL_OC NULL
#define HANDY_FRAMESKIP_THRESHOLD_LABEL_OC NULL
#define HANDY_FRAMESKIP_THRESHOLD_INFO_0_OC NULL

struct retro_core_option_v2_category option_cats_oc[] = {
   { NULL, NULL, NULL },
};
struct retro_core_option_v2_definition option_defs_oc[] = {
   {
      "handy_rot",
      HANDY_ROT_LABEL_OC,
      NULL,
      HANDY_ROT_INFO_0_OC,
      NULL,
      NULL,
      {
         { "None", OPTION_VAL_NONE_OC },
         { "270",  OPTION_VAL_270_OC },
         { "90",   OPTION_VAL_90_OC },
         { NULL, NULL },
      },
      "None"
   },
#if defined(FRONTEND_SUPPORTS_XRGB8888)
   {
      "handy_gfx_colors",
      HANDY_GFX_COLORS_LABEL_OC,
      NULL,
      HANDY_GFX_COLORS_INFO_0_OC,
      NULL,
      NULL,
      {
         { "16bit", OPTION_VAL_16BIT_OC },
         { "24bit", OPTION_VAL_24BIT_OC },
         { NULL,    NULL },
      },
      "16bit"
   },
#endif
   {
      "handy_frameskip",
      HANDY_FRAMESKIP_LABEL_OC,
      NULL,
      HANDY_FRAMESKIP_INFO_0_OC,
      NULL,
      NULL,
      {
         { "disabled", NULL },
         { "auto",     OPTION_VAL_AUTO_OC },
         { "manual",   OPTION_VAL_MANUAL_OC },
         { NULL, NULL },
      },
      "disabled"
   },
   {
      "handy_frameskip_threshold",
      HANDY_FRAMESKIP_THRESHOLD_LABEL_OC,
      NULL,
      HANDY_FRAMESKIP_THRESHOLD_INFO_0_OC,
      NULL,
      NULL,
      {
         { "15", NULL },
         { "18", NULL },
         { "21", NULL },
         { "24", NULL },
         { "27", NULL },
         { "30", NULL },
         { "33", NULL },
         { "36", NULL },
         { "39", NULL },
         { "42", NULL },
         { "45", NULL },
         { "48", NULL },
         { "51", NULL },
         { "54", NULL },
         { "57", NULL },
         { "60", NULL },
         { NULL, NULL },
      },
      "33"
   },
   { NULL, NULL, NULL, NULL, NULL, NULL, {{0}}, NULL },
};
struct retro_core_options_v2 options_oc = {
   option_cats_oc,
   option_defs_oc
};

/* RETRO_LANGUAGE_PL */

#define HANDY_ROT_LABEL_PL NULL
#define HANDY_ROT_INFO_0_PL "Obróć wirtualny ekran konsoli, aby osiągnąć prawidłowy układ gier zorientowanych pionowo na konwencjonalnym wyświetlaczu (pejzaż)."
#define OPTION_VAL_NONE_PL "Brak"
#define OPTION_VAL_270_PL NULL
#define OPTION_VAL_90_PL NULL
#define HANDY_GFX_COLORS_LABEL_PL NULL
#define HANDY_GFX_COLORS_INFO_0_PL "Określ liczbę kolorów wyświetlanych na ekranie. 24-bitowe znacznie zwiększają zapotrzebowanie na moc obliczeniową i nie jest dostępne na wszystkich platformach."
#define OPTION_VAL_16BIT_PL NULL
#define OPTION_VAL_24BIT_PL NULL
#define HANDY_FRAMESKIP_LABEL_PL "Pomijanie klatek"
#define HANDY_FRAMESKIP_INFO_0_PL NULL
#define OPTION_VAL_AUTO_PL NULL
#define OPTION_VAL_MANUAL_PL "Ręczny"
#define HANDY_FRAMESKIP_THRESHOLD_LABEL_PL "Próg pominięcia ramki (%)"
#define HANDY_FRAMESKIP_THRESHOLD_INFO_0_PL "Gdy 'Frameskip' jest ustawiony na 'Manual', określa próg zajęcia bufora audio (procent) poniżej którego ramki zostaną pominięte. Wyższe wartości zmniejszają ryzyko trzasków poprzez częstsze opuszczanie ramek."

struct retro_core_option_v2_category option_cats_pl[] = {
   { NULL, NULL, NULL },
};
struct retro_core_option_v2_definition option_defs_pl[] = {
   {
      "handy_rot",
      HANDY_ROT_LABEL_PL,
      NULL,
      HANDY_ROT_INFO_0_PL,
      NULL,
      NULL,
      {
         { "None", OPTION_VAL_NONE_PL },
         { "270",  OPTION_VAL_270_PL },
         { "90",   OPTION_VAL_90_PL },
         { NULL, NULL },
      },
      "None"
   },
#if defined(FRONTEND_SUPPORTS_XRGB8888)
   {
      "handy_gfx_colors",
      HANDY_GFX_COLORS_LABEL_PL,
      NULL,
      HANDY_GFX_COLORS_INFO_0_PL,
      NULL,
      NULL,
      {
         { "16bit", OPTION_VAL_16BIT_PL },
         { "24bit", OPTION_VAL_24BIT_PL },
         { NULL,    NULL },
      },
      "16bit"
   },
#endif
   {
      "handy_frameskip",
      HANDY_FRAMESKIP_LABEL_PL,
      NULL,
      HANDY_FRAMESKIP_INFO_0_PL,
      NULL,
      NULL,
      {
         { "disabled", NULL },
         { "auto",     OPTION_VAL_AUTO_PL },
         { "manual",   OPTION_VAL_MANUAL_PL },
         { NULL, NULL },
      },
      "disabled"
   },
   {
      "handy_frameskip_threshold",
      HANDY_FRAMESKIP_THRESHOLD_LABEL_PL,
      NULL,
      HANDY_FRAMESKIP_THRESHOLD_INFO_0_PL,
      NULL,
      NULL,
      {
         { "15", NULL },
         { "18", NULL },
         { "21", NULL },
         { "24", NULL },
         { "27", NULL },
         { "30", NULL },
         { "33", NULL },
         { "36", NULL },
         { "39", NULL },
         { "42", NULL },
         { "45", NULL },
         { "48", NULL },
         { "51", NULL },
         { "54", NULL },
         { "57", NULL },
         { "60", NULL },
         { NULL, NULL },
      },
      "33"
   },
   { NULL, NULL, NULL, NULL, NULL, NULL, {{0}}, NULL },
};
struct retro_core_options_v2 options_pl = {
   option_cats_pl,
   option_defs_pl
};

/* RETRO_LANGUAGE_PT_BR */

#define HANDY_ROT_LABEL_PT_BR "Rotação de tela"
#define HANDY_ROT_INFO_0_PT_BR "Gire a tela do console virtual para alcançar o formato correto de jogos com orientação de 'retrato' para uma exibição convencional (modo retrato)."
#define OPTION_VAL_NONE_PT_BR "Nenhum"
#define OPTION_VAL_270_PT_BR "Sentido horário"
#define OPTION_VAL_90_PT_BR "Sentido anti-horário"
#define HANDY_GFX_COLORS_LABEL_PT_BR "Profundidade de cor (requer reinício)"
#define HANDY_GFX_COLORS_INFO_0_PT_BR "Especifica o quantidade de cores a serem exibidas na tela. 24-bit aumenta significativamente as sobrecarga de desempenho e não está disponível em todas as plataformas."
#define OPTION_VAL_16BIT_PT_BR "Milhares (16-bit)"
#define OPTION_VAL_24BIT_PT_BR "Milhões (24-bit)"
#define HANDY_FRAMESKIP_LABEL_PT_BR "Pulo de quadro"
#define HANDY_FRAMESKIP_INFO_0_PT_BR "Ignora quadros para evitar o esvaziamento do buffer do áudio (corte no áudio). Melhora o desempenho ao custo da suavidade visual. A opção 'Automático' ignora os quadros quando aconselhado pela interface. Já 'Manual' utiliza a configuração 'Limite de pulo de quadro (%)'."
#define OPTION_VAL_AUTO_PT_BR "Automático"
#define OPTION_VAL_MANUAL_PT_BR NULL
#define HANDY_FRAMESKIP_THRESHOLD_LABEL_PT_BR "Limite de pulo de quadro (%)"
#define HANDY_FRAMESKIP_THRESHOLD_INFO_0_PT_BR "Quando o 'Pulo de quadro' for definido como 'Manual', especifica o limite de ocupação do buffer de áudio (em porcentagem) abaixo do qual os quadros serão pulados. Valores maiores reduzem o risco de engasgos pois farão que os quadros sejam descartados com mais frequência."

struct retro_core_option_v2_category option_cats_pt_br[] = {
   { NULL, NULL, NULL },
};
struct retro_core_option_v2_definition option_defs_pt_br[] = {
   {
      "handy_rot",
      HANDY_ROT_LABEL_PT_BR,
      NULL,
      HANDY_ROT_INFO_0_PT_BR,
      NULL,
      NULL,
      {
         { "None", OPTION_VAL_NONE_PT_BR },
         { "270",  OPTION_VAL_270_PT_BR },
         { "90",   OPTION_VAL_90_PT_BR },
         { NULL, NULL },
      },
      "None"
   },
#if defined(FRONTEND_SUPPORTS_XRGB8888)
   {
      "handy_gfx_colors",
      HANDY_GFX_COLORS_LABEL_PT_BR,
      NULL,
      HANDY_GFX_COLORS_INFO_0_PT_BR,
      NULL,
      NULL,
      {
         { "16bit", OPTION_VAL_16BIT_PT_BR },
         { "24bit", OPTION_VAL_24BIT_PT_BR },
         { NULL,    NULL },
      },
      "16bit"
   },
#endif
   {
      "handy_frameskip",
      HANDY_FRAMESKIP_LABEL_PT_BR,
      NULL,
      HANDY_FRAMESKIP_INFO_0_PT_BR,
      NULL,
      NULL,
      {
         { "disabled", NULL },
         { "auto",     OPTION_VAL_AUTO_PT_BR },
         { "manual",   OPTION_VAL_MANUAL_PT_BR },
         { NULL, NULL },
      },
      "disabled"
   },
   {
      "handy_frameskip_threshold",
      HANDY_FRAMESKIP_THRESHOLD_LABEL_PT_BR,
      NULL,
      HANDY_FRAMESKIP_THRESHOLD_INFO_0_PT_BR,
      NULL,
      NULL,
      {
         { "15", NULL },
         { "18", NULL },
         { "21", NULL },
         { "24", NULL },
         { "27", NULL },
         { "30", NULL },
         { "33", NULL },
         { "36", NULL },
         { "39", NULL },
         { "42", NULL },
         { "45", NULL },
         { "48", NULL },
         { "51", NULL },
         { "54", NULL },
         { "57", NULL },
         { "60", NULL },
         { NULL, NULL },
      },
      "33"
   },
   { NULL, NULL, NULL, NULL, NULL, NULL, {{0}}, NULL },
};
struct retro_core_options_v2 options_pt_br = {
   option_cats_pt_br,
   option_defs_pt_br
};

/* RETRO_LANGUAGE_PT_PT */

#define HANDY_ROT_LABEL_PT_PT NULL
#define HANDY_ROT_INFO_0_PT_PT NULL
#define OPTION_VAL_NONE_PT_PT "Nenhum"
#define OPTION_VAL_270_PT_PT NULL
#define OPTION_VAL_90_PT_PT NULL
#define HANDY_GFX_COLORS_LABEL_PT_PT NULL
#define HANDY_GFX_COLORS_INFO_0_PT_PT NULL
#define OPTION_VAL_16BIT_PT_PT NULL
#define OPTION_VAL_24BIT_PT_PT NULL
#define HANDY_FRAMESKIP_LABEL_PT_PT NULL
#define HANDY_FRAMESKIP_INFO_0_PT_PT NULL
#define OPTION_VAL_AUTO_PT_PT NULL
#define OPTION_VAL_MANUAL_PT_PT NULL
#define HANDY_FRAMESKIP_THRESHOLD_LABEL_PT_PT NULL
#define HANDY_FRAMESKIP_THRESHOLD_INFO_0_PT_PT NULL

struct retro_core_option_v2_category option_cats_pt_pt[] = {
   { NULL, NULL, NULL },
};
struct retro_core_option_v2_definition option_defs_pt_pt[] = {
   {
      "handy_rot",
      HANDY_ROT_LABEL_PT_PT,
      NULL,
      HANDY_ROT_INFO_0_PT_PT,
      NULL,
      NULL,
      {
         { "None", OPTION_VAL_NONE_PT_PT },
         { "270",  OPTION_VAL_270_PT_PT },
         { "90",   OPTION_VAL_90_PT_PT },
         { NULL, NULL },
      },
      "None"
   },
#if defined(FRONTEND_SUPPORTS_XRGB8888)
   {
      "handy_gfx_colors",
      HANDY_GFX_COLORS_LABEL_PT_PT,
      NULL,
      HANDY_GFX_COLORS_INFO_0_PT_PT,
      NULL,
      NULL,
      {
         { "16bit", OPTION_VAL_16BIT_PT_PT },
         { "24bit", OPTION_VAL_24BIT_PT_PT },
         { NULL,    NULL },
      },
      "16bit"
   },
#endif
   {
      "handy_frameskip",
      HANDY_FRAMESKIP_LABEL_PT_PT,
      NULL,
      HANDY_FRAMESKIP_INFO_0_PT_PT,
      NULL,
      NULL,
      {
         { "disabled", NULL },
         { "auto",     OPTION_VAL_AUTO_PT_PT },
         { "manual",   OPTION_VAL_MANUAL_PT_PT },
         { NULL, NULL },
      },
      "disabled"
   },
   {
      "handy_frameskip_threshold",
      HANDY_FRAMESKIP_THRESHOLD_LABEL_PT_PT,
      NULL,
      HANDY_FRAMESKIP_THRESHOLD_INFO_0_PT_PT,
      NULL,
      NULL,
      {
         { "15", NULL },
         { "18", NULL },
         { "21", NULL },
         { "24", NULL },
         { "27", NULL },
         { "30", NULL },
         { "33", NULL },
         { "36", NULL },
         { "39", NULL },
         { "42", NULL },
         { "45", NULL },
         { "48", NULL },
         { "51", NULL },
         { "54", NULL },
         { "57", NULL },
         { "60", NULL },
         { NULL, NULL },
      },
      "33"
   },
   { NULL, NULL, NULL, NULL, NULL, NULL, {{0}}, NULL },
};
struct retro_core_options_v2 options_pt_pt = {
   option_cats_pt_pt,
   option_defs_pt_pt
};

/* RETRO_LANGUAGE_RO */

#define HANDY_ROT_LABEL_RO NULL
#define HANDY_ROT_INFO_0_RO NULL
#define OPTION_VAL_NONE_RO NULL
#define OPTION_VAL_270_RO NULL
#define OPTION_VAL_90_RO NULL
#define HANDY_GFX_COLORS_LABEL_RO NULL
#define HANDY_GFX_COLORS_INFO_0_RO NULL
#define OPTION_VAL_16BIT_RO NULL
#define OPTION_VAL_24BIT_RO NULL
#define HANDY_FRAMESKIP_LABEL_RO NULL
#define HANDY_FRAMESKIP_INFO_0_RO NULL
#define OPTION_VAL_AUTO_RO NULL
#define OPTION_VAL_MANUAL_RO NULL
#define HANDY_FRAMESKIP_THRESHOLD_LABEL_RO NULL
#define HANDY_FRAMESKIP_THRESHOLD_INFO_0_RO NULL

struct retro_core_option_v2_category option_cats_ro[] = {
   { NULL, NULL, NULL },
};
struct retro_core_option_v2_definition option_defs_ro[] = {
   {
      "handy_rot",
      HANDY_ROT_LABEL_RO,
      NULL,
      HANDY_ROT_INFO_0_RO,
      NULL,
      NULL,
      {
         { "None", OPTION_VAL_NONE_RO },
         { "270",  OPTION_VAL_270_RO },
         { "90",   OPTION_VAL_90_RO },
         { NULL, NULL },
      },
      "None"
   },
#if defined(FRONTEND_SUPPORTS_XRGB8888)
   {
      "handy_gfx_colors",
      HANDY_GFX_COLORS_LABEL_RO,
      NULL,
      HANDY_GFX_COLORS_INFO_0_RO,
      NULL,
      NULL,
      {
         { "16bit", OPTION_VAL_16BIT_RO },
         { "24bit", OPTION_VAL_24BIT_RO },
         { NULL,    NULL },
      },
      "16bit"
   },
#endif
   {
      "handy_frameskip",
      HANDY_FRAMESKIP_LABEL_RO,
      NULL,
      HANDY_FRAMESKIP_INFO_0_RO,
      NULL,
      NULL,
      {
         { "disabled", NULL },
         { "auto",     OPTION_VAL_AUTO_RO },
         { "manual",   OPTION_VAL_MANUAL_RO },
         { NULL, NULL },
      },
      "disabled"
   },
   {
      "handy_frameskip_threshold",
      HANDY_FRAMESKIP_THRESHOLD_LABEL_RO,
      NULL,
      HANDY_FRAMESKIP_THRESHOLD_INFO_0_RO,
      NULL,
      NULL,
      {
         { "15", NULL },
         { "18", NULL },
         { "21", NULL },
         { "24", NULL },
         { "27", NULL },
         { "30", NULL },
         { "33", NULL },
         { "36", NULL },
         { "39", NULL },
         { "42", NULL },
         { "45", NULL },
         { "48", NULL },
         { "51", NULL },
         { "54", NULL },
         { "57", NULL },
         { "60", NULL },
         { NULL, NULL },
      },
      "33"
   },
   { NULL, NULL, NULL, NULL, NULL, NULL, {{0}}, NULL },
};
struct retro_core_options_v2 options_ro = {
   option_cats_ro,
   option_defs_ro
};

/* RETRO_LANGUAGE_RU */

#define HANDY_ROT_LABEL_RU "Вращение экрана"
#define HANDY_ROT_INFO_0_RU "Поворачивает виртуальный экран консоли для правильного расположения портретно-ориентированных игр при использовании ландшафтной ориентации."
#define OPTION_VAL_NONE_RU "Нет"
#define OPTION_VAL_270_RU "По часовой стрелке"
#define OPTION_VAL_90_RU "Против часовой стрелки"
#define HANDY_GFX_COLORS_LABEL_RU "Глубина цвета (перезапуск)"
#define HANDY_GFX_COLORS_INFO_0_RU "Выбор количества цветов для отображения на экране. 24-битная палитра существенно повышает нагрузку на устройство и недоступна для всех платформ."
#define OPTION_VAL_16BIT_RU "Тысячи (16 бит)"
#define OPTION_VAL_24BIT_RU "Миллионы (24 бита)"
#define HANDY_FRAMESKIP_LABEL_RU "Пропуск кадров"
#define HANDY_FRAMESKIP_INFO_0_RU "Пропускать кадры, чтобы избежать опустошения аудиобуфера (треск). Улучшает производительность, но снижает плавность изображения. В режиме 'Авто' пропуск кадров регулируется фронтендом. В режиме 'Вручную' используется настройка 'Граница пропуска кадров (%)'."
#define OPTION_VAL_AUTO_RU "Авто"
#define OPTION_VAL_MANUAL_RU "Вручную"
#define HANDY_FRAMESKIP_THRESHOLD_LABEL_RU "Граница пропуска кадров (%)"
#define HANDY_FRAMESKIP_THRESHOLD_INFO_0_RU "Устанавливает порог заполнения аудиобуфера (в процентах), ниже которого будет включаться пропуск кадров при установке опции 'Пропуск кадров' в режим 'Вручную'. Большие значения снижают вероятность появления треска за счёт более частого пропуска кадров."

struct retro_core_option_v2_category option_cats_ru[] = {
   { NULL, NULL, NULL },
};
struct retro_core_option_v2_definition option_defs_ru[] = {
   {
      "handy_rot",
      HANDY_ROT_LABEL_RU,
      NULL,
      HANDY_ROT_INFO_0_RU,
      NULL,
      NULL,
      {
         { "None", OPTION_VAL_NONE_RU },
         { "270",  OPTION_VAL_270_RU },
         { "90",   OPTION_VAL_90_RU },
         { NULL, NULL },
      },
      "None"
   },
#if defined(FRONTEND_SUPPORTS_XRGB8888)
   {
      "handy_gfx_colors",
      HANDY_GFX_COLORS_LABEL_RU,
      NULL,
      HANDY_GFX_COLORS_INFO_0_RU,
      NULL,
      NULL,
      {
         { "16bit", OPTION_VAL_16BIT_RU },
         { "24bit", OPTION_VAL_24BIT_RU },
         { NULL,    NULL },
      },
      "16bit"
   },
#endif
   {
      "handy_frameskip",
      HANDY_FRAMESKIP_LABEL_RU,
      NULL,
      HANDY_FRAMESKIP_INFO_0_RU,
      NULL,
      NULL,
      {
         { "disabled", NULL },
         { "auto",     OPTION_VAL_AUTO_RU },
         { "manual",   OPTION_VAL_MANUAL_RU },
         { NULL, NULL },
      },
      "disabled"
   },
   {
      "handy_frameskip_threshold",
      HANDY_FRAMESKIP_THRESHOLD_LABEL_RU,
      NULL,
      HANDY_FRAMESKIP_THRESHOLD_INFO_0_RU,
      NULL,
      NULL,
      {
         { "15", NULL },
         { "18", NULL },
         { "21", NULL },
         { "24", NULL },
         { "27", NULL },
         { "30", NULL },
         { "33", NULL },
         { "36", NULL },
         { "39", NULL },
         { "42", NULL },
         { "45", NULL },
         { "48", NULL },
         { "51", NULL },
         { "54", NULL },
         { "57", NULL },
         { "60", NULL },
         { NULL, NULL },
      },
      "33"
   },
   { NULL, NULL, NULL, NULL, NULL, NULL, {{0}}, NULL },
};
struct retro_core_options_v2 options_ru = {
   option_cats_ru,
   option_defs_ru
};

/* RETRO_LANGUAGE_SI */

#define HANDY_ROT_LABEL_SI NULL
#define HANDY_ROT_INFO_0_SI NULL
#define OPTION_VAL_NONE_SI NULL
#define OPTION_VAL_270_SI NULL
#define OPTION_VAL_90_SI NULL
#define HANDY_GFX_COLORS_LABEL_SI NULL
#define HANDY_GFX_COLORS_INFO_0_SI NULL
#define OPTION_VAL_16BIT_SI NULL
#define OPTION_VAL_24BIT_SI NULL
#define HANDY_FRAMESKIP_LABEL_SI NULL
#define HANDY_FRAMESKIP_INFO_0_SI NULL
#define OPTION_VAL_AUTO_SI NULL
#define OPTION_VAL_MANUAL_SI NULL
#define HANDY_FRAMESKIP_THRESHOLD_LABEL_SI NULL
#define HANDY_FRAMESKIP_THRESHOLD_INFO_0_SI NULL

struct retro_core_option_v2_category option_cats_si[] = {
   { NULL, NULL, NULL },
};
struct retro_core_option_v2_definition option_defs_si[] = {
   {
      "handy_rot",
      HANDY_ROT_LABEL_SI,
      NULL,
      HANDY_ROT_INFO_0_SI,
      NULL,
      NULL,
      {
         { "None", OPTION_VAL_NONE_SI },
         { "270",  OPTION_VAL_270_SI },
         { "90",   OPTION_VAL_90_SI },
         { NULL, NULL },
      },
      "None"
   },
#if defined(FRONTEND_SUPPORTS_XRGB8888)
   {
      "handy_gfx_colors",
      HANDY_GFX_COLORS_LABEL_SI,
      NULL,
      HANDY_GFX_COLORS_INFO_0_SI,
      NULL,
      NULL,
      {
         { "16bit", OPTION_VAL_16BIT_SI },
         { "24bit", OPTION_VAL_24BIT_SI },
         { NULL,    NULL },
      },
      "16bit"
   },
#endif
   {
      "handy_frameskip",
      HANDY_FRAMESKIP_LABEL_SI,
      NULL,
      HANDY_FRAMESKIP_INFO_0_SI,
      NULL,
      NULL,
      {
         { "disabled", NULL },
         { "auto",     OPTION_VAL_AUTO_SI },
         { "manual",   OPTION_VAL_MANUAL_SI },
         { NULL, NULL },
      },
      "disabled"
   },
   {
      "handy_frameskip_threshold",
      HANDY_FRAMESKIP_THRESHOLD_LABEL_SI,
      NULL,
      HANDY_FRAMESKIP_THRESHOLD_INFO_0_SI,
      NULL,
      NULL,
      {
         { "15", NULL },
         { "18", NULL },
         { "21", NULL },
         { "24", NULL },
         { "27", NULL },
         { "30", NULL },
         { "33", NULL },
         { "36", NULL },
         { "39", NULL },
         { "42", NULL },
         { "45", NULL },
         { "48", NULL },
         { "51", NULL },
         { "54", NULL },
         { "57", NULL },
         { "60", NULL },
         { NULL, NULL },
      },
      "33"
   },
   { NULL, NULL, NULL, NULL, NULL, NULL, {{0}}, NULL },
};
struct retro_core_options_v2 options_si = {
   option_cats_si,
   option_defs_si
};

/* RETRO_LANGUAGE_SK */

#define HANDY_ROT_LABEL_SK NULL
#define HANDY_ROT_INFO_0_SK "Otočiť virtuálnu obrazovku konzoly a dosiahnuť tak správne rozloženie hier orientovaných na výšku na bežnej obrazovke orientovanej na šírku."
#define OPTION_VAL_NONE_SK "Žiadne"
#define OPTION_VAL_270_SK NULL
#define OPTION_VAL_90_SK NULL
#define HANDY_GFX_COLORS_LABEL_SK NULL
#define HANDY_GFX_COLORS_INFO_0_SK "Zvoliť farebnú hĺbku. 24 bitov značne zvýši výkonnostné réžie a nie je dostupná na všetky platformách."
#define OPTION_VAL_16BIT_SK NULL
#define OPTION_VAL_24BIT_SK NULL
#define HANDY_FRAMESKIP_LABEL_SK NULL
#define HANDY_FRAMESKIP_INFO_0_SK NULL
#define OPTION_VAL_AUTO_SK NULL
#define OPTION_VAL_MANUAL_SK NULL
#define HANDY_FRAMESKIP_THRESHOLD_LABEL_SK NULL
#define HANDY_FRAMESKIP_THRESHOLD_INFO_0_SK "Ak je 'Preskočenie snímkov' nastavené na 'Ručne', určuje obsadenosť zvukového zásobníka (v percentách) pod ktorou budú snímky preskočené. Vyššie hodnoty znižujú riziko praskania za cenu zahodenia snímkov častejšie."

struct retro_core_option_v2_category option_cats_sk[] = {
   { NULL, NULL, NULL },
};
struct retro_core_option_v2_definition option_defs_sk[] = {
   {
      "handy_rot",
      HANDY_ROT_LABEL_SK,
      NULL,
      HANDY_ROT_INFO_0_SK,
      NULL,
      NULL,
      {
         { "None", OPTION_VAL_NONE_SK },
         { "270",  OPTION_VAL_270_SK },
         { "90",   OPTION_VAL_90_SK },
         { NULL, NULL },
      },
      "None"
   },
#if defined(FRONTEND_SUPPORTS_XRGB8888)
   {
      "handy_gfx_colors",
      HANDY_GFX_COLORS_LABEL_SK,
      NULL,
      HANDY_GFX_COLORS_INFO_0_SK,
      NULL,
      NULL,
      {
         { "16bit", OPTION_VAL_16BIT_SK },
         { "24bit", OPTION_VAL_24BIT_SK },
         { NULL,    NULL },
      },
      "16bit"
   },
#endif
   {
      "handy_frameskip",
      HANDY_FRAMESKIP_LABEL_SK,
      NULL,
      HANDY_FRAMESKIP_INFO_0_SK,
      NULL,
      NULL,
      {
         { "disabled", NULL },
         { "auto",     OPTION_VAL_AUTO_SK },
         { "manual",   OPTION_VAL_MANUAL_SK },
         { NULL, NULL },
      },
      "disabled"
   },
   {
      "handy_frameskip_threshold",
      HANDY_FRAMESKIP_THRESHOLD_LABEL_SK,
      NULL,
      HANDY_FRAMESKIP_THRESHOLD_INFO_0_SK,
      NULL,
      NULL,
      {
         { "15", NULL },
         { "18", NULL },
         { "21", NULL },
         { "24", NULL },
         { "27", NULL },
         { "30", NULL },
         { "33", NULL },
         { "36", NULL },
         { "39", NULL },
         { "42", NULL },
         { "45", NULL },
         { "48", NULL },
         { "51", NULL },
         { "54", NULL },
         { "57", NULL },
         { "60", NULL },
         { NULL, NULL },
      },
      "33"
   },
   { NULL, NULL, NULL, NULL, NULL, NULL, {{0}}, NULL },
};
struct retro_core_options_v2 options_sk = {
   option_cats_sk,
   option_defs_sk
};

/* RETRO_LANGUAGE_SR */

#define HANDY_ROT_LABEL_SR NULL
#define HANDY_ROT_INFO_0_SR NULL
#define OPTION_VAL_NONE_SR NULL
#define OPTION_VAL_270_SR NULL
#define OPTION_VAL_90_SR NULL
#define HANDY_GFX_COLORS_LABEL_SR NULL
#define HANDY_GFX_COLORS_INFO_0_SR NULL
#define OPTION_VAL_16BIT_SR NULL
#define OPTION_VAL_24BIT_SR NULL
#define HANDY_FRAMESKIP_LABEL_SR NULL
#define HANDY_FRAMESKIP_INFO_0_SR NULL
#define OPTION_VAL_AUTO_SR NULL
#define OPTION_VAL_MANUAL_SR NULL
#define HANDY_FRAMESKIP_THRESHOLD_LABEL_SR NULL
#define HANDY_FRAMESKIP_THRESHOLD_INFO_0_SR NULL

struct retro_core_option_v2_category option_cats_sr[] = {
   { NULL, NULL, NULL },
};
struct retro_core_option_v2_definition option_defs_sr[] = {
   {
      "handy_rot",
      HANDY_ROT_LABEL_SR,
      NULL,
      HANDY_ROT_INFO_0_SR,
      NULL,
      NULL,
      {
         { "None", OPTION_VAL_NONE_SR },
         { "270",  OPTION_VAL_270_SR },
         { "90",   OPTION_VAL_90_SR },
         { NULL, NULL },
      },
      "None"
   },
#if defined(FRONTEND_SUPPORTS_XRGB8888)
   {
      "handy_gfx_colors",
      HANDY_GFX_COLORS_LABEL_SR,
      NULL,
      HANDY_GFX_COLORS_INFO_0_SR,
      NULL,
      NULL,
      {
         { "16bit", OPTION_VAL_16BIT_SR },
         { "24bit", OPTION_VAL_24BIT_SR },
         { NULL,    NULL },
      },
      "16bit"
   },
#endif
   {
      "handy_frameskip",
      HANDY_FRAMESKIP_LABEL_SR,
      NULL,
      HANDY_FRAMESKIP_INFO_0_SR,
      NULL,
      NULL,
      {
         { "disabled", NULL },
         { "auto",     OPTION_VAL_AUTO_SR },
         { "manual",   OPTION_VAL_MANUAL_SR },
         { NULL, NULL },
      },
      "disabled"
   },
   {
      "handy_frameskip_threshold",
      HANDY_FRAMESKIP_THRESHOLD_LABEL_SR,
      NULL,
      HANDY_FRAMESKIP_THRESHOLD_INFO_0_SR,
      NULL,
      NULL,
      {
         { "15", NULL },
         { "18", NULL },
         { "21", NULL },
         { "24", NULL },
         { "27", NULL },
         { "30", NULL },
         { "33", NULL },
         { "36", NULL },
         { "39", NULL },
         { "42", NULL },
         { "45", NULL },
         { "48", NULL },
         { "51", NULL },
         { "54", NULL },
         { "57", NULL },
         { "60", NULL },
         { NULL, NULL },
      },
      "33"
   },
   { NULL, NULL, NULL, NULL, NULL, NULL, {{0}}, NULL },
};
struct retro_core_options_v2 options_sr = {
   option_cats_sr,
   option_defs_sr
};

/* RETRO_LANGUAGE_SV */

#define HANDY_ROT_LABEL_SV NULL
#define HANDY_ROT_INFO_0_SV "Rotera den virtuella konsolskärmen för att uppnå rätt layout av \"porträtt\" orienterade spel på en konventionell (landskap) skärm."
#define OPTION_VAL_NONE_SV "Ingen"
#define OPTION_VAL_270_SV "Medurs"
#define OPTION_VAL_90_SV NULL
#define HANDY_GFX_COLORS_LABEL_SV NULL
#define HANDY_GFX_COLORS_INFO_0_SV "Ange antal färger att visa på skärmen. 24-bitars ökar prestandakraven och finns inte på alla plattformar."
#define OPTION_VAL_16BIT_SV NULL
#define OPTION_VAL_24BIT_SV NULL
#define HANDY_FRAMESKIP_LABEL_SV NULL
#define HANDY_FRAMESKIP_INFO_0_SV NULL
#define OPTION_VAL_AUTO_SV "Automatiskt"
#define OPTION_VAL_MANUAL_SV NULL
#define HANDY_FRAMESKIP_THRESHOLD_LABEL_SV NULL
#define HANDY_FRAMESKIP_THRESHOLD_INFO_0_SV "När 'Frameskip' är satt till 'Manuell', ange ljudbuffertens tröskel (i procent) under vilka ramar som kommer att hoppas över. Högre värden minskar risken för hackigt ljud genom att bildrutor tappas oftare."

struct retro_core_option_v2_category option_cats_sv[] = {
   { NULL, NULL, NULL },
};
struct retro_core_option_v2_definition option_defs_sv[] = {
   {
      "handy_rot",
      HANDY_ROT_LABEL_SV,
      NULL,
      HANDY_ROT_INFO_0_SV,
      NULL,
      NULL,
      {
         { "None", OPTION_VAL_NONE_SV },
         { "270",  OPTION_VAL_270_SV },
         { "90",   OPTION_VAL_90_SV },
         { NULL, NULL },
      },
      "None"
   },
#if defined(FRONTEND_SUPPORTS_XRGB8888)
   {
      "handy_gfx_colors",
      HANDY_GFX_COLORS_LABEL_SV,
      NULL,
      HANDY_GFX_COLORS_INFO_0_SV,
      NULL,
      NULL,
      {
         { "16bit", OPTION_VAL_16BIT_SV },
         { "24bit", OPTION_VAL_24BIT_SV },
         { NULL,    NULL },
      },
      "16bit"
   },
#endif
   {
      "handy_frameskip",
      HANDY_FRAMESKIP_LABEL_SV,
      NULL,
      HANDY_FRAMESKIP_INFO_0_SV,
      NULL,
      NULL,
      {
         { "disabled", NULL },
         { "auto",     OPTION_VAL_AUTO_SV },
         { "manual",   OPTION_VAL_MANUAL_SV },
         { NULL, NULL },
      },
      "disabled"
   },
   {
      "handy_frameskip_threshold",
      HANDY_FRAMESKIP_THRESHOLD_LABEL_SV,
      NULL,
      HANDY_FRAMESKIP_THRESHOLD_INFO_0_SV,
      NULL,
      NULL,
      {
         { "15", NULL },
         { "18", NULL },
         { "21", NULL },
         { "24", NULL },
         { "27", NULL },
         { "30", NULL },
         { "33", NULL },
         { "36", NULL },
         { "39", NULL },
         { "42", NULL },
         { "45", NULL },
         { "48", NULL },
         { "51", NULL },
         { "54", NULL },
         { "57", NULL },
         { "60", NULL },
         { NULL, NULL },
      },
      "33"
   },
   { NULL, NULL, NULL, NULL, NULL, NULL, {{0}}, NULL },
};
struct retro_core_options_v2 options_sv = {
   option_cats_sv,
   option_defs_sv
};

/* RETRO_LANGUAGE_TR */

#define HANDY_ROT_LABEL_TR "Ekran Döndürme"
#define HANDY_ROT_INFO_0_TR "Geleneksel (yatay) bir ekranda 'portre' odaklı oyunların doğru düzenini elde etmek için sanal konsol ekranını döndürün."
#define OPTION_VAL_NONE_TR "Yok"
#define OPTION_VAL_270_TR "Saat yönünde"
#define OPTION_VAL_90_TR "Saat yönünün tersi"
#define HANDY_GFX_COLORS_LABEL_TR "Renk Derinliği (Yeniden Başlatılmalı)"
#define HANDY_GFX_COLORS_INFO_0_TR "Ekranda görüntülenecek renk sayısını belirtin. 24 bit, genel performansı önemli ölçüde artırır ve tüm platformlarda kullanılamaz."
#define OPTION_VAL_16BIT_TR "Binlerce (16-bit)"
#define OPTION_VAL_24BIT_TR "Milyonlarca (24-bit)"
#define HANDY_FRAMESKIP_LABEL_TR "Kare Atlama"
#define HANDY_FRAMESKIP_INFO_0_TR "Yetersiz çalıştırılan ses arabelleğini (çatırtı) önlemek için kareleri atlayın. Görsel pürüzsüzlük pahasına performansı iyileştirir. \"Otomatik\", ön uç tarafından önerildiğinde kareleri atlar. 'El ile', 'Kare Atlama Eşiği (%)' ayarını kullanır."
#define OPTION_VAL_AUTO_TR "Otomatik"
#define OPTION_VAL_MANUAL_TR "El ile"
#define HANDY_FRAMESKIP_THRESHOLD_LABEL_TR "Kare Atlama Eşiği (%)"
#define HANDY_FRAMESKIP_THRESHOLD_INFO_0_TR "'Kare Atlama', 'El ile' olarak ayarlandığında, altındaki karelerin atlanacağı ses arabelleği doluluk eşiğini (yüzde) belirtir. Daha yüksek değerler, çerçevelerin daha sık düşmesine neden olarak çatlama riskini azaltır."

struct retro_core_option_v2_category option_cats_tr[] = {
   { NULL, NULL, NULL },
};
struct retro_core_option_v2_definition option_defs_tr[] = {
   {
      "handy_rot",
      HANDY_ROT_LABEL_TR,
      NULL,
      HANDY_ROT_INFO_0_TR,
      NULL,
      NULL,
      {
         { "None", OPTION_VAL_NONE_TR },
         { "270",  OPTION_VAL_270_TR },
         { "90",   OPTION_VAL_90_TR },
         { NULL, NULL },
      },
      "None"
   },
#if defined(FRONTEND_SUPPORTS_XRGB8888)
   {
      "handy_gfx_colors",
      HANDY_GFX_COLORS_LABEL_TR,
      NULL,
      HANDY_GFX_COLORS_INFO_0_TR,
      NULL,
      NULL,
      {
         { "16bit", OPTION_VAL_16BIT_TR },
         { "24bit", OPTION_VAL_24BIT_TR },
         { NULL,    NULL },
      },
      "16bit"
   },
#endif
   {
      "handy_frameskip",
      HANDY_FRAMESKIP_LABEL_TR,
      NULL,
      HANDY_FRAMESKIP_INFO_0_TR,
      NULL,
      NULL,
      {
         { "disabled", NULL },
         { "auto",     OPTION_VAL_AUTO_TR },
         { "manual",   OPTION_VAL_MANUAL_TR },
         { NULL, NULL },
      },
      "disabled"
   },
   {
      "handy_frameskip_threshold",
      HANDY_FRAMESKIP_THRESHOLD_LABEL_TR,
      NULL,
      HANDY_FRAMESKIP_THRESHOLD_INFO_0_TR,
      NULL,
      NULL,
      {
         { "15", NULL },
         { "18", NULL },
         { "21", NULL },
         { "24", NULL },
         { "27", NULL },
         { "30", NULL },
         { "33", NULL },
         { "36", NULL },
         { "39", NULL },
         { "42", NULL },
         { "45", NULL },
         { "48", NULL },
         { "51", NULL },
         { "54", NULL },
         { "57", NULL },
         { "60", NULL },
         { NULL, NULL },
      },
      "33"
   },
   { NULL, NULL, NULL, NULL, NULL, NULL, {{0}}, NULL },
};
struct retro_core_options_v2 options_tr = {
   option_cats_tr,
   option_defs_tr
};

/* RETRO_LANGUAGE_UK */

#define HANDY_ROT_LABEL_UK "Обертання екрану"
#define HANDY_ROT_INFO_0_UK "Повертає екран віртуальної консолі, для вірного відображення портретно-орієнтованих ігор на дисплеї з альбомною орієнтацією."
#define OPTION_VAL_NONE_UK NULL
#define OPTION_VAL_270_UK "За годин. стрілкою"
#define OPTION_VAL_90_UK "Проти годин. стрілки"
#define HANDY_GFX_COLORS_LABEL_UK "Глибина кольору (потрібен перезапуск)"
#define HANDY_GFX_COLORS_INFO_0_UK "Вказує кількість кольорів, які будуть відображатись на екрані. 24-бітна палітра суттєво впливає на продуктивність та доступна не на всіх платформах."
#define OPTION_VAL_16BIT_UK NULL
#define OPTION_VAL_24BIT_UK NULL
#define HANDY_FRAMESKIP_LABEL_UK "Пропуск кадру"
#define HANDY_FRAMESKIP_INFO_0_UK "Пропускати кадри, щоб уникнути спустошення буферу (тріскіт). Покращує швидкодію, погіршуючи плавність зображення. 'Авто' пропускає кадри, керуючись командами зовнішньої оболонки. 'Ручний' використовує налаштування 'Межа пропуску кадрів (%)'."
#define OPTION_VAL_AUTO_UK "Авто"
#define OPTION_VAL_MANUAL_UK "Ручний"
#define HANDY_FRAMESKIP_THRESHOLD_LABEL_UK "Межа пропуску кадрів (%)"
#define HANDY_FRAMESKIP_THRESHOLD_INFO_0_UK "Якщо 'Пропус кадрів' встановлено у 'Вручну', зазначає граничне значення оточення аудіо-буферу (відсоток), нижчі за які кадри будуть пропущені. Більш високі значення зменшують ризик зломування, викликаючи зменшення кадрів частіше."

struct retro_core_option_v2_category option_cats_uk[] = {
   { NULL, NULL, NULL },
};
struct retro_core_option_v2_definition option_defs_uk[] = {
   {
      "handy_rot",
      HANDY_ROT_LABEL_UK,
      NULL,
      HANDY_ROT_INFO_0_UK,
      NULL,
      NULL,
      {
         { "None", OPTION_VAL_NONE_UK },
         { "270",  OPTION_VAL_270_UK },
         { "90",   OPTION_VAL_90_UK },
         { NULL, NULL },
      },
      "None"
   },
#if defined(FRONTEND_SUPPORTS_XRGB8888)
   {
      "handy_gfx_colors",
      HANDY_GFX_COLORS_LABEL_UK,
      NULL,
      HANDY_GFX_COLORS_INFO_0_UK,
      NULL,
      NULL,
      {
         { "16bit", OPTION_VAL_16BIT_UK },
         { "24bit", OPTION_VAL_24BIT_UK },
         { NULL,    NULL },
      },
      "16bit"
   },
#endif
   {
      "handy_frameskip",
      HANDY_FRAMESKIP_LABEL_UK,
      NULL,
      HANDY_FRAMESKIP_INFO_0_UK,
      NULL,
      NULL,
      {
         { "disabled", NULL },
         { "auto",     OPTION_VAL_AUTO_UK },
         { "manual",   OPTION_VAL_MANUAL_UK },
         { NULL, NULL },
      },
      "disabled"
   },
   {
      "handy_frameskip_threshold",
      HANDY_FRAMESKIP_THRESHOLD_LABEL_UK,
      NULL,
      HANDY_FRAMESKIP_THRESHOLD_INFO_0_UK,
      NULL,
      NULL,
      {
         { "15", NULL },
         { "18", NULL },
         { "21", NULL },
         { "24", NULL },
         { "27", NULL },
         { "30", NULL },
         { "33", NULL },
         { "36", NULL },
         { "39", NULL },
         { "42", NULL },
         { "45", NULL },
         { "48", NULL },
         { "51", NULL },
         { "54", NULL },
         { "57", NULL },
         { "60", NULL },
         { NULL, NULL },
      },
      "33"
   },
   { NULL, NULL, NULL, NULL, NULL, NULL, {{0}}, NULL },
};
struct retro_core_options_v2 options_uk = {
   option_cats_uk,
   option_defs_uk
};

/* RETRO_LANGUAGE_VN */

#define HANDY_ROT_LABEL_VN NULL
#define HANDY_ROT_INFO_0_VN "Xoay màn hình để hiển thị chính xác trò chơi màn hình dọc ở chế độ hiển thị thông thường (ngang)."
#define OPTION_VAL_NONE_VN NULL
#define OPTION_VAL_270_VN NULL
#define OPTION_VAL_90_VN NULL
#define HANDY_GFX_COLORS_LABEL_VN NULL
#define HANDY_GFX_COLORS_INFO_0_VN "Chọn chế độ hiển thị màu trên màn hình. 24-bit làm tăng đáng kể hiệu suất và không hẳn có sẵn trên mọi nền tảng."
#define OPTION_VAL_16BIT_VN NULL
#define OPTION_VAL_24BIT_VN NULL
#define HANDY_FRAMESKIP_LABEL_VN "Bỏ qua khung hình"
#define HANDY_FRAMESKIP_INFO_0_VN NULL
#define OPTION_VAL_AUTO_VN "Tự động"
#define OPTION_VAL_MANUAL_VN "Thủ công"
#define HANDY_FRAMESKIP_THRESHOLD_LABEL_VN NULL
#define HANDY_FRAMESKIP_THRESHOLD_INFO_0_VN NULL

struct retro_core_option_v2_category option_cats_vn[] = {
   { NULL, NULL, NULL },
};
struct retro_core_option_v2_definition option_defs_vn[] = {
   {
      "handy_rot",
      HANDY_ROT_LABEL_VN,
      NULL,
      HANDY_ROT_INFO_0_VN,
      NULL,
      NULL,
      {
         { "None", OPTION_VAL_NONE_VN },
         { "270",  OPTION_VAL_270_VN },
         { "90",   OPTION_VAL_90_VN },
         { NULL, NULL },
      },
      "None"
   },
#if defined(FRONTEND_SUPPORTS_XRGB8888)
   {
      "handy_gfx_colors",
      HANDY_GFX_COLORS_LABEL_VN,
      NULL,
      HANDY_GFX_COLORS_INFO_0_VN,
      NULL,
      NULL,
      {
         { "16bit", OPTION_VAL_16BIT_VN },
         { "24bit", OPTION_VAL_24BIT_VN },
         { NULL,    NULL },
      },
      "16bit"
   },
#endif
   {
      "handy_frameskip",
      HANDY_FRAMESKIP_LABEL_VN,
      NULL,
      HANDY_FRAMESKIP_INFO_0_VN,
      NULL,
      NULL,
      {
         { "disabled", NULL },
         { "auto",     OPTION_VAL_AUTO_VN },
         { "manual",   OPTION_VAL_MANUAL_VN },
         { NULL, NULL },
      },
      "disabled"
   },
   {
      "handy_frameskip_threshold",
      HANDY_FRAMESKIP_THRESHOLD_LABEL_VN,
      NULL,
      HANDY_FRAMESKIP_THRESHOLD_INFO_0_VN,
      NULL,
      NULL,
      {
         { "15", NULL },
         { "18", NULL },
         { "21", NULL },
         { "24", NULL },
         { "27", NULL },
         { "30", NULL },
         { "33", NULL },
         { "36", NULL },
         { "39", NULL },
         { "42", NULL },
         { "45", NULL },
         { "48", NULL },
         { "51", NULL },
         { "54", NULL },
         { "57", NULL },
         { "60", NULL },
         { NULL, NULL },
      },
      "33"
   },
   { NULL, NULL, NULL, NULL, NULL, NULL, {{0}}, NULL },
};
struct retro_core_options_v2 options_vn = {
   option_cats_vn,
   option_defs_vn
};


#ifdef __cplusplus
}
#endif

#endif