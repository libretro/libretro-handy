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

#define HANDY_REFRESH_RATE_LABEL_AR NULL
#define HANDY_REFRESH_RATE_INFO_0_AR NULL
#define OPTION_VAL_50_AR NULL
#define OPTION_VAL_60_AR NULL
#define OPTION_VAL_75_AR NULL
#define OPTION_VAL_100_AR NULL
#define OPTION_VAL_120_AR NULL
#define HANDY_ROT_LABEL_AR NULL
#define HANDY_ROT_INFO_0_AR "تدوير شاشة وحدة التحكم الافتراضية لتحقيق التخطيط الصحيح للألعاب \"عمودية\" على العرض التقليدي (الأفقي)."
#define OPTION_VAL_270_AR NULL
#define OPTION_VAL_90_AR NULL
#define HANDY_GFX_COLORS_LABEL_AR NULL
#define HANDY_GFX_COLORS_INFO_0_AR "حدد عدد الألوان لعرضها على الشاشة. 24 بت يزيد بشكل كبير من النفقات العامة للأداء، وهو غير متوفر على جميع المنصات."
#define OPTION_VAL_16BIT_AR NULL
#define OPTION_VAL_24BIT_AR NULL
#define HANDY_LCD_GHOSTING_LABEL_AR NULL
#define HANDY_LCD_GHOSTING_INFO_0_AR NULL
#define OPTION_VAL_2FRAMES_AR NULL
#define OPTION_VAL_3FRAMES_AR NULL
#define OPTION_VAL_4FRAMES_AR NULL
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
      "handy_refresh_rate",
      HANDY_REFRESH_RATE_LABEL_AR,
      NULL,
      HANDY_REFRESH_RATE_INFO_0_AR,
      NULL,
      NULL,
      {
         { "50",  OPTION_VAL_50_AR },
         { "60",  OPTION_VAL_60_AR },
         { "75",  OPTION_VAL_75_AR },
         { "100", OPTION_VAL_100_AR },
         { "120", OPTION_VAL_120_AR },
         { NULL, NULL },
      },
      "60"
   },
   {
      "handy_rot",
      HANDY_ROT_LABEL_AR,
      NULL,
      HANDY_ROT_INFO_0_AR,
      NULL,
      NULL,
      {
         { "None", "disabled" },
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
      "handy_lcd_ghosting",
      HANDY_LCD_GHOSTING_LABEL_AR,
      NULL,
      HANDY_LCD_GHOSTING_INFO_0_AR,
      NULL,
      NULL,
      {
         { "disabled", NULL },
         { "2frames",  OPTION_VAL_2FRAMES_AR },
         { "3frames",  OPTION_VAL_3FRAMES_AR },
         { "4frames",  OPTION_VAL_4FRAMES_AR },
         { NULL, NULL },
      },
      "disabled"
   },
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

#define HANDY_REFRESH_RATE_LABEL_AST NULL
#define HANDY_REFRESH_RATE_INFO_0_AST NULL
#define OPTION_VAL_50_AST NULL
#define OPTION_VAL_60_AST NULL
#define OPTION_VAL_75_AST NULL
#define OPTION_VAL_100_AST NULL
#define OPTION_VAL_120_AST NULL
#define HANDY_ROT_LABEL_AST NULL
#define HANDY_ROT_INFO_0_AST "Voltia la pantalla de la consola virtual pa llograr la distribución correuta de los xuegos orientaos en vertical nuna pantalla panorámica convencional."
#define OPTION_VAL_270_AST NULL
#define OPTION_VAL_90_AST NULL
#define HANDY_GFX_COLORS_LABEL_AST NULL
#define HANDY_GFX_COLORS_INFO_0_AST "Especifica'l númberu de colores a amosar na pantalla. Los 24 bits aumenten significativamente les sobrecargues nel rindimientu y nun tán disponibles en toles plataformes."
#define OPTION_VAL_16BIT_AST "Miles (16 bits)"
#define OPTION_VAL_24BIT_AST "Millones (24 bits)"
#define HANDY_LCD_GHOSTING_LABEL_AST NULL
#define HANDY_LCD_GHOSTING_INFO_0_AST NULL
#define OPTION_VAL_2FRAMES_AST NULL
#define OPTION_VAL_3FRAMES_AST NULL
#define OPTION_VAL_4FRAMES_AST NULL
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
      "handy_refresh_rate",
      HANDY_REFRESH_RATE_LABEL_AST,
      NULL,
      HANDY_REFRESH_RATE_INFO_0_AST,
      NULL,
      NULL,
      {
         { "50",  OPTION_VAL_50_AST },
         { "60",  OPTION_VAL_60_AST },
         { "75",  OPTION_VAL_75_AST },
         { "100", OPTION_VAL_100_AST },
         { "120", OPTION_VAL_120_AST },
         { NULL, NULL },
      },
      "60"
   },
   {
      "handy_rot",
      HANDY_ROT_LABEL_AST,
      NULL,
      HANDY_ROT_INFO_0_AST,
      NULL,
      NULL,
      {
         { "None", "disabled" },
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
      "handy_lcd_ghosting",
      HANDY_LCD_GHOSTING_LABEL_AST,
      NULL,
      HANDY_LCD_GHOSTING_INFO_0_AST,
      NULL,
      NULL,
      {
         { "disabled", NULL },
         { "2frames",  OPTION_VAL_2FRAMES_AST },
         { "3frames",  OPTION_VAL_3FRAMES_AST },
         { "4frames",  OPTION_VAL_4FRAMES_AST },
         { NULL, NULL },
      },
      "disabled"
   },
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

#define HANDY_REFRESH_RATE_LABEL_CA NULL
#define HANDY_REFRESH_RATE_INFO_0_CA NULL
#define OPTION_VAL_50_CA NULL
#define OPTION_VAL_60_CA NULL
#define OPTION_VAL_75_CA NULL
#define OPTION_VAL_100_CA NULL
#define OPTION_VAL_120_CA NULL
#define HANDY_ROT_LABEL_CA NULL
#define HANDY_ROT_INFO_0_CA NULL
#define OPTION_VAL_270_CA NULL
#define OPTION_VAL_90_CA NULL
#define HANDY_GFX_COLORS_LABEL_CA NULL
#define HANDY_GFX_COLORS_INFO_0_CA NULL
#define OPTION_VAL_16BIT_CA NULL
#define OPTION_VAL_24BIT_CA NULL
#define HANDY_LCD_GHOSTING_LABEL_CA NULL
#define HANDY_LCD_GHOSTING_INFO_0_CA NULL
#define OPTION_VAL_2FRAMES_CA NULL
#define OPTION_VAL_3FRAMES_CA NULL
#define OPTION_VAL_4FRAMES_CA NULL
#define HANDY_FRAMESKIP_LABEL_CA NULL
#define HANDY_FRAMESKIP_INFO_0_CA NULL
#define OPTION_VAL_AUTO_CA "Automàtic"
#define OPTION_VAL_MANUAL_CA NULL
#define HANDY_FRAMESKIP_THRESHOLD_LABEL_CA NULL
#define HANDY_FRAMESKIP_THRESHOLD_INFO_0_CA NULL

struct retro_core_option_v2_category option_cats_ca[] = {
   { NULL, NULL, NULL },
};
struct retro_core_option_v2_definition option_defs_ca[] = {
   {
      "handy_refresh_rate",
      HANDY_REFRESH_RATE_LABEL_CA,
      NULL,
      HANDY_REFRESH_RATE_INFO_0_CA,
      NULL,
      NULL,
      {
         { "50",  OPTION_VAL_50_CA },
         { "60",  OPTION_VAL_60_CA },
         { "75",  OPTION_VAL_75_CA },
         { "100", OPTION_VAL_100_CA },
         { "120", OPTION_VAL_120_CA },
         { NULL, NULL },
      },
      "60"
   },
   {
      "handy_rot",
      HANDY_ROT_LABEL_CA,
      NULL,
      HANDY_ROT_INFO_0_CA,
      NULL,
      NULL,
      {
         { "None", "disabled" },
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
      "handy_lcd_ghosting",
      HANDY_LCD_GHOSTING_LABEL_CA,
      NULL,
      HANDY_LCD_GHOSTING_INFO_0_CA,
      NULL,
      NULL,
      {
         { "disabled", NULL },
         { "2frames",  OPTION_VAL_2FRAMES_CA },
         { "3frames",  OPTION_VAL_3FRAMES_CA },
         { "4frames",  OPTION_VAL_4FRAMES_CA },
         { NULL, NULL },
      },
      "disabled"
   },
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

#define HANDY_REFRESH_RATE_LABEL_CHS NULL
#define HANDY_REFRESH_RATE_INFO_0_CHS NULL
#define OPTION_VAL_50_CHS NULL
#define OPTION_VAL_60_CHS NULL
#define OPTION_VAL_75_CHS NULL
#define OPTION_VAL_100_CHS NULL
#define OPTION_VAL_120_CHS NULL
#define HANDY_ROT_LABEL_CHS "显示旋转"
#define HANDY_ROT_INFO_0_CHS "如果想要在横屏的显示器上竖屏显示游戏，请旋转你的模拟器屏幕。"
#define OPTION_VAL_270_CHS "顺时针"
#define OPTION_VAL_90_CHS "逆时针"
#define HANDY_GFX_COLORS_LABEL_CHS "色深(需要重启)"
#define HANDY_GFX_COLORS_INFO_0_CHS "指定屏幕显示的颜色数量。设置为「24 位」将极大提高性能开销，且仅部分平台可用。"
#define OPTION_VAL_16BIT_CHS "千位级(16-bit)"
#define OPTION_VAL_24BIT_CHS "百万位级(24-bit)"
#define HANDY_LCD_GHOSTING_LABEL_CHS "LCD重影过滤器"
#define HANDY_LCD_GHOSTING_INFO_0_CHS NULL
#define OPTION_VAL_2FRAMES_CHS NULL
#define OPTION_VAL_3FRAMES_CHS NULL
#define OPTION_VAL_4FRAMES_CHS NULL
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
      "handy_refresh_rate",
      HANDY_REFRESH_RATE_LABEL_CHS,
      NULL,
      HANDY_REFRESH_RATE_INFO_0_CHS,
      NULL,
      NULL,
      {
         { "50",  OPTION_VAL_50_CHS },
         { "60",  OPTION_VAL_60_CHS },
         { "75",  OPTION_VAL_75_CHS },
         { "100", OPTION_VAL_100_CHS },
         { "120", OPTION_VAL_120_CHS },
         { NULL, NULL },
      },
      "60"
   },
   {
      "handy_rot",
      HANDY_ROT_LABEL_CHS,
      NULL,
      HANDY_ROT_INFO_0_CHS,
      NULL,
      NULL,
      {
         { "None", "disabled" },
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
      "handy_lcd_ghosting",
      HANDY_LCD_GHOSTING_LABEL_CHS,
      NULL,
      HANDY_LCD_GHOSTING_INFO_0_CHS,
      NULL,
      NULL,
      {
         { "disabled", NULL },
         { "2frames",  OPTION_VAL_2FRAMES_CHS },
         { "3frames",  OPTION_VAL_3FRAMES_CHS },
         { "4frames",  OPTION_VAL_4FRAMES_CHS },
         { NULL, NULL },
      },
      "disabled"
   },
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

#define HANDY_REFRESH_RATE_LABEL_CHT NULL
#define HANDY_REFRESH_RATE_INFO_0_CHT NULL
#define OPTION_VAL_50_CHT NULL
#define OPTION_VAL_60_CHT NULL
#define OPTION_VAL_75_CHT NULL
#define OPTION_VAL_100_CHT NULL
#define OPTION_VAL_120_CHT NULL
#define HANDY_ROT_LABEL_CHT "螢幕旋轉"
#define HANDY_ROT_INFO_0_CHT NULL
#define OPTION_VAL_270_CHT NULL
#define OPTION_VAL_90_CHT NULL
#define HANDY_GFX_COLORS_LABEL_CHT NULL
#define HANDY_GFX_COLORS_INFO_0_CHT NULL
#define OPTION_VAL_16BIT_CHT NULL
#define OPTION_VAL_24BIT_CHT NULL
#define HANDY_LCD_GHOSTING_LABEL_CHT NULL
#define HANDY_LCD_GHOSTING_INFO_0_CHT NULL
#define OPTION_VAL_2FRAMES_CHT NULL
#define OPTION_VAL_3FRAMES_CHT NULL
#define OPTION_VAL_4FRAMES_CHT NULL
#define HANDY_FRAMESKIP_LABEL_CHT "跳幀"
#define HANDY_FRAMESKIP_INFO_0_CHT "設定跳幀用以避免音訊緩衝區不足(產生破音)。用影像流暢度為代價提高效能。\n設定 <自動> 由前端系統控制跳幀。設定 <手動> 由「跳幀上限 (%)」控制跳幀。"
#define OPTION_VAL_AUTO_CHT "自動"
#define OPTION_VAL_MANUAL_CHT "手動"
#define HANDY_FRAMESKIP_THRESHOLD_LABEL_CHT "跳幀上限 (%)"
#define HANDY_FRAMESKIP_THRESHOLD_INFO_0_CHT "設定「跳幀」為 <手動> 時音頻緩衝區使用上限(%)，低於上限的影格將被跳過。設定過高會導致頻繁丟失影格，過低則是出現破音。"

struct retro_core_option_v2_category option_cats_cht[] = {
   { NULL, NULL, NULL },
};
struct retro_core_option_v2_definition option_defs_cht[] = {
   {
      "handy_refresh_rate",
      HANDY_REFRESH_RATE_LABEL_CHT,
      NULL,
      HANDY_REFRESH_RATE_INFO_0_CHT,
      NULL,
      NULL,
      {
         { "50",  OPTION_VAL_50_CHT },
         { "60",  OPTION_VAL_60_CHT },
         { "75",  OPTION_VAL_75_CHT },
         { "100", OPTION_VAL_100_CHT },
         { "120", OPTION_VAL_120_CHT },
         { NULL, NULL },
      },
      "60"
   },
   {
      "handy_rot",
      HANDY_ROT_LABEL_CHT,
      NULL,
      HANDY_ROT_INFO_0_CHT,
      NULL,
      NULL,
      {
         { "None", "disabled" },
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
      "handy_lcd_ghosting",
      HANDY_LCD_GHOSTING_LABEL_CHT,
      NULL,
      HANDY_LCD_GHOSTING_INFO_0_CHT,
      NULL,
      NULL,
      {
         { "disabled", NULL },
         { "2frames",  OPTION_VAL_2FRAMES_CHT },
         { "3frames",  OPTION_VAL_3FRAMES_CHT },
         { "4frames",  OPTION_VAL_4FRAMES_CHT },
         { NULL, NULL },
      },
      "disabled"
   },
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

#define HANDY_REFRESH_RATE_LABEL_CS NULL
#define HANDY_REFRESH_RATE_INFO_0_CS NULL
#define OPTION_VAL_50_CS NULL
#define OPTION_VAL_60_CS NULL
#define OPTION_VAL_75_CS NULL
#define OPTION_VAL_100_CS NULL
#define OPTION_VAL_120_CS NULL
#define HANDY_ROT_LABEL_CS "Otáčení Displeje"
#define HANDY_ROT_INFO_0_CS "Otočením obrazovky virtuální konzole dosáhnete správného rozložení her orientovaných na výšku na běžném displeji (na šířku)."
#define OPTION_VAL_270_CS "Po směru hodinových ručiček"
#define OPTION_VAL_90_CS "Proti směru hodinových ručiček"
#define HANDY_GFX_COLORS_LABEL_CS "Hloubka Barev (Vyžadován Restart)"
#define HANDY_GFX_COLORS_INFO_0_CS "Zadejte počet barev, které se mají zobrazit na obrazovce. 24 bitů výrazně zvyšuje výkonnostní režii a není k dispozici na všech platformách."
#define OPTION_VAL_16BIT_CS "Tisíce (16 bitů)"
#define OPTION_VAL_24BIT_CS "Miliony (24 bitů)"
#define HANDY_LCD_GHOSTING_LABEL_CS "Filtr proti duchům na displeji LCD"
#define HANDY_LCD_GHOSTING_INFO_0_CS NULL
#define OPTION_VAL_2FRAMES_CS NULL
#define OPTION_VAL_3FRAMES_CS NULL
#define OPTION_VAL_4FRAMES_CS NULL
#define HANDY_FRAMESKIP_LABEL_CS "Přeskočení Snímku"
#define HANDY_FRAMESKIP_INFO_0_CS "Přeskočení snímků, aby se zabránilo nedostatečnému využití vyrovnávací paměti zvuku (praskání). Zlepšuje výkon na úkor vizuální plynulosti. Funkce 'Auto' přeskakuje snímky, pokud to doporučí frontend. 'Ruční' využívá nastavení 'Práh přeskakování snímků (%)'."
#define OPTION_VAL_AUTO_CS NULL
#define OPTION_VAL_MANUAL_CS "Ruční"
#define HANDY_FRAMESKIP_THRESHOLD_LABEL_CS "Hraniční Hodnota Přeskočení Snímku (%)"
#define HANDY_FRAMESKIP_THRESHOLD_INFO_0_CS "Pokud je položka 'Přeskočení Snímku' nastavena na hodnotu 'Ruční', určuje práh obsazení vyrovnávací paměti zvuku (v procentech), pod kterým budou snímky přeskočeny. Vyšší hodnoty snižují riziko praskání tím, že způsobují častější vynechávání snímků."

struct retro_core_option_v2_category option_cats_cs[] = {
   { NULL, NULL, NULL },
};
struct retro_core_option_v2_definition option_defs_cs[] = {
   {
      "handy_refresh_rate",
      HANDY_REFRESH_RATE_LABEL_CS,
      NULL,
      HANDY_REFRESH_RATE_INFO_0_CS,
      NULL,
      NULL,
      {
         { "50",  OPTION_VAL_50_CS },
         { "60",  OPTION_VAL_60_CS },
         { "75",  OPTION_VAL_75_CS },
         { "100", OPTION_VAL_100_CS },
         { "120", OPTION_VAL_120_CS },
         { NULL, NULL },
      },
      "60"
   },
   {
      "handy_rot",
      HANDY_ROT_LABEL_CS,
      NULL,
      HANDY_ROT_INFO_0_CS,
      NULL,
      NULL,
      {
         { "None", "disabled" },
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
      "handy_lcd_ghosting",
      HANDY_LCD_GHOSTING_LABEL_CS,
      NULL,
      HANDY_LCD_GHOSTING_INFO_0_CS,
      NULL,
      NULL,
      {
         { "disabled", NULL },
         { "2frames",  OPTION_VAL_2FRAMES_CS },
         { "3frames",  OPTION_VAL_3FRAMES_CS },
         { "4frames",  OPTION_VAL_4FRAMES_CS },
         { NULL, NULL },
      },
      "disabled"
   },
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

#define HANDY_REFRESH_RATE_LABEL_CY NULL
#define HANDY_REFRESH_RATE_INFO_0_CY NULL
#define OPTION_VAL_50_CY NULL
#define OPTION_VAL_60_CY NULL
#define OPTION_VAL_75_CY NULL
#define OPTION_VAL_100_CY NULL
#define OPTION_VAL_120_CY NULL
#define HANDY_ROT_LABEL_CY NULL
#define HANDY_ROT_INFO_0_CY "Cylchdrowch y sgrin consol rhith i gael y cynllun cywir o gemau 'portread' ar dangosydd confensiynol (tirlun)."
#define OPTION_VAL_270_CY NULL
#define OPTION_VAL_90_CY NULL
#define HANDY_GFX_COLORS_LABEL_CY NULL
#define HANDY_GFX_COLORS_INFO_0_CY "Nodwch nifer y lliwiau i'w harddangos ar y sgrin. Mae 24-did yn cynyddu gorbenion perfformiad yn sylweddol ac nid yw ar gael ar bob platfform."
#define OPTION_VAL_16BIT_CY NULL
#define OPTION_VAL_24BIT_CY NULL
#define HANDY_LCD_GHOSTING_LABEL_CY NULL
#define HANDY_LCD_GHOSTING_INFO_0_CY NULL
#define OPTION_VAL_2FRAMES_CY NULL
#define OPTION_VAL_3FRAMES_CY NULL
#define OPTION_VAL_4FRAMES_CY NULL
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
      "handy_refresh_rate",
      HANDY_REFRESH_RATE_LABEL_CY,
      NULL,
      HANDY_REFRESH_RATE_INFO_0_CY,
      NULL,
      NULL,
      {
         { "50",  OPTION_VAL_50_CY },
         { "60",  OPTION_VAL_60_CY },
         { "75",  OPTION_VAL_75_CY },
         { "100", OPTION_VAL_100_CY },
         { "120", OPTION_VAL_120_CY },
         { NULL, NULL },
      },
      "60"
   },
   {
      "handy_rot",
      HANDY_ROT_LABEL_CY,
      NULL,
      HANDY_ROT_INFO_0_CY,
      NULL,
      NULL,
      {
         { "None", "disabled" },
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
      "handy_lcd_ghosting",
      HANDY_LCD_GHOSTING_LABEL_CY,
      NULL,
      HANDY_LCD_GHOSTING_INFO_0_CY,
      NULL,
      NULL,
      {
         { "disabled", NULL },
         { "2frames",  OPTION_VAL_2FRAMES_CY },
         { "3frames",  OPTION_VAL_3FRAMES_CY },
         { "4frames",  OPTION_VAL_4FRAMES_CY },
         { NULL, NULL },
      },
      "disabled"
   },
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

#define HANDY_REFRESH_RATE_LABEL_DA NULL
#define HANDY_REFRESH_RATE_INFO_0_DA NULL
#define OPTION_VAL_50_DA NULL
#define OPTION_VAL_60_DA NULL
#define OPTION_VAL_75_DA NULL
#define OPTION_VAL_100_DA NULL
#define OPTION_VAL_120_DA NULL
#define HANDY_ROT_LABEL_DA NULL
#define HANDY_ROT_INFO_0_DA "Rotér den virtuelle konsolskærm for at opnå det korrekte layout af 'portræt'-orienterede spil på en konventionel (landskabs-) skærm."
#define OPTION_VAL_270_DA NULL
#define OPTION_VAL_90_DA NULL
#define HANDY_GFX_COLORS_LABEL_DA NULL
#define HANDY_GFX_COLORS_INFO_0_DA "Angiv antallet af farver vist på skærmen. 24-bit øger markant ydeevneomkostningerne og er ikke tilgængelig på alle platforme."
#define OPTION_VAL_16BIT_DA NULL
#define OPTION_VAL_24BIT_DA NULL
#define HANDY_LCD_GHOSTING_LABEL_DA NULL
#define HANDY_LCD_GHOSTING_INFO_0_DA NULL
#define OPTION_VAL_2FRAMES_DA NULL
#define OPTION_VAL_3FRAMES_DA NULL
#define OPTION_VAL_4FRAMES_DA NULL
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
      "handy_refresh_rate",
      HANDY_REFRESH_RATE_LABEL_DA,
      NULL,
      HANDY_REFRESH_RATE_INFO_0_DA,
      NULL,
      NULL,
      {
         { "50",  OPTION_VAL_50_DA },
         { "60",  OPTION_VAL_60_DA },
         { "75",  OPTION_VAL_75_DA },
         { "100", OPTION_VAL_100_DA },
         { "120", OPTION_VAL_120_DA },
         { NULL, NULL },
      },
      "60"
   },
   {
      "handy_rot",
      HANDY_ROT_LABEL_DA,
      NULL,
      HANDY_ROT_INFO_0_DA,
      NULL,
      NULL,
      {
         { "None", "disabled" },
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
      "handy_lcd_ghosting",
      HANDY_LCD_GHOSTING_LABEL_DA,
      NULL,
      HANDY_LCD_GHOSTING_INFO_0_DA,
      NULL,
      NULL,
      {
         { "disabled", NULL },
         { "2frames",  OPTION_VAL_2FRAMES_DA },
         { "3frames",  OPTION_VAL_3FRAMES_DA },
         { "4frames",  OPTION_VAL_4FRAMES_DA },
         { NULL, NULL },
      },
      "disabled"
   },
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

#define HANDY_REFRESH_RATE_LABEL_DE NULL
#define HANDY_REFRESH_RATE_INFO_0_DE NULL
#define OPTION_VAL_50_DE NULL
#define OPTION_VAL_60_DE NULL
#define OPTION_VAL_75_DE NULL
#define OPTION_VAL_100_DE NULL
#define OPTION_VAL_120_DE NULL
#define HANDY_ROT_LABEL_DE "Bildschirmrotation"
#define HANDY_ROT_INFO_0_DE "Den virtuellen Konsolen-Bildschirm drehen, um das richtige Layout von Spielen im Hochformat auf einem herkömmlichen (Quer-) Display zu erzielen."
#define OPTION_VAL_270_DE "Im Uhrzeigersinn"
#define OPTION_VAL_90_DE "Gegen den Uhrzeigersinn"
#define HANDY_GFX_COLORS_LABEL_DE "Farbtiefe (Neustart erforderlich)"
#define HANDY_GFX_COLORS_INFO_0_DE "Anzahl der Farben angeben, die auf dem Bildschirm angezeigt werden sollen. 24-Bit erhöht den Leistungsaufwand erheblich und ist nicht auf allen Plattformen verfügbar."
#define OPTION_VAL_16BIT_DE "Tausende (16 Bit)"
#define OPTION_VAL_24BIT_DE "Millionen (24 Bit)"
#define HANDY_LCD_GHOSTING_LABEL_DE "LCD-Ghosting-Filter"
#define HANDY_LCD_GHOSTING_INFO_0_DE NULL
#define OPTION_VAL_2FRAMES_DE NULL
#define OPTION_VAL_3FRAMES_DE NULL
#define OPTION_VAL_4FRAMES_DE NULL
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
      "handy_refresh_rate",
      HANDY_REFRESH_RATE_LABEL_DE,
      NULL,
      HANDY_REFRESH_RATE_INFO_0_DE,
      NULL,
      NULL,
      {
         { "50",  OPTION_VAL_50_DE },
         { "60",  OPTION_VAL_60_DE },
         { "75",  OPTION_VAL_75_DE },
         { "100", OPTION_VAL_100_DE },
         { "120", OPTION_VAL_120_DE },
         { NULL, NULL },
      },
      "60"
   },
   {
      "handy_rot",
      HANDY_ROT_LABEL_DE,
      NULL,
      HANDY_ROT_INFO_0_DE,
      NULL,
      NULL,
      {
         { "None", "disabled" },
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
      "handy_lcd_ghosting",
      HANDY_LCD_GHOSTING_LABEL_DE,
      NULL,
      HANDY_LCD_GHOSTING_INFO_0_DE,
      NULL,
      NULL,
      {
         { "disabled", NULL },
         { "2frames",  OPTION_VAL_2FRAMES_DE },
         { "3frames",  OPTION_VAL_3FRAMES_DE },
         { "4frames",  OPTION_VAL_4FRAMES_DE },
         { NULL, NULL },
      },
      "disabled"
   },
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

#define HANDY_REFRESH_RATE_LABEL_EL NULL
#define HANDY_REFRESH_RATE_INFO_0_EL NULL
#define OPTION_VAL_50_EL NULL
#define OPTION_VAL_60_EL NULL
#define OPTION_VAL_75_EL NULL
#define OPTION_VAL_100_EL NULL
#define OPTION_VAL_120_EL NULL
#define HANDY_ROT_LABEL_EL "Περιστροφή Οθόνης"
#define HANDY_ROT_INFO_0_EL "Περιστρέφει την οθόνη της εικονικής κονσόλας για να επιτύχει τη σωστή διάταξη των παιχνιδιών όπου έχουν προσανατολισμό «πορτρέτο» σε συμβατική οθόνη (landscape)."
#define OPTION_VAL_270_EL NULL
#define OPTION_VAL_90_EL NULL
#define HANDY_GFX_COLORS_LABEL_EL "Βάθος Χρώματος (Απαιτείται Επανεκκίνηση)"
#define HANDY_GFX_COLORS_INFO_0_EL "Καθορίστε τον αριθμό των χρωμάτων που θα εμφανίζονται στην οθόνη. Τα 24-bit μειώνουν σημαντικά την απόδοση και δεν είναι διαθέσιμα σε όλες τις πλατφόρμες."
#define OPTION_VAL_16BIT_EL "Χιλιάδες (16-bit)"
#define OPTION_VAL_24BIT_EL "Εκατομμύρια (24-bit)"
#define HANDY_LCD_GHOSTING_LABEL_EL NULL
#define HANDY_LCD_GHOSTING_INFO_0_EL NULL
#define OPTION_VAL_2FRAMES_EL NULL
#define OPTION_VAL_3FRAMES_EL NULL
#define OPTION_VAL_4FRAMES_EL NULL
#define HANDY_FRAMESKIP_LABEL_EL NULL
#define HANDY_FRAMESKIP_INFO_0_EL NULL
#define OPTION_VAL_AUTO_EL "Αυτόματο"
#define OPTION_VAL_MANUAL_EL "Χειροκίνητο"
#define HANDY_FRAMESKIP_THRESHOLD_LABEL_EL NULL
#define HANDY_FRAMESKIP_THRESHOLD_INFO_0_EL NULL

struct retro_core_option_v2_category option_cats_el[] = {
   { NULL, NULL, NULL },
};
struct retro_core_option_v2_definition option_defs_el[] = {
   {
      "handy_refresh_rate",
      HANDY_REFRESH_RATE_LABEL_EL,
      NULL,
      HANDY_REFRESH_RATE_INFO_0_EL,
      NULL,
      NULL,
      {
         { "50",  OPTION_VAL_50_EL },
         { "60",  OPTION_VAL_60_EL },
         { "75",  OPTION_VAL_75_EL },
         { "100", OPTION_VAL_100_EL },
         { "120", OPTION_VAL_120_EL },
         { NULL, NULL },
      },
      "60"
   },
   {
      "handy_rot",
      HANDY_ROT_LABEL_EL,
      NULL,
      HANDY_ROT_INFO_0_EL,
      NULL,
      NULL,
      {
         { "None", "disabled" },
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
      "handy_lcd_ghosting",
      HANDY_LCD_GHOSTING_LABEL_EL,
      NULL,
      HANDY_LCD_GHOSTING_INFO_0_EL,
      NULL,
      NULL,
      {
         { "disabled", NULL },
         { "2frames",  OPTION_VAL_2FRAMES_EL },
         { "3frames",  OPTION_VAL_3FRAMES_EL },
         { "4frames",  OPTION_VAL_4FRAMES_EL },
         { NULL, NULL },
      },
      "disabled"
   },
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

/* RETRO_LANGUAGE_EN */

#define HANDY_REFRESH_RATE_LABEL_EN NULL
#define HANDY_REFRESH_RATE_INFO_0_EN NULL
#define OPTION_VAL_50_EN NULL
#define OPTION_VAL_60_EN NULL
#define OPTION_VAL_75_EN NULL
#define OPTION_VAL_100_EN NULL
#define OPTION_VAL_120_EN NULL
#define HANDY_ROT_LABEL_EN NULL
#define HANDY_ROT_INFO_0_EN NULL
#define OPTION_VAL_270_EN NULL
#define OPTION_VAL_90_EN NULL
#define HANDY_GFX_COLORS_LABEL_EN "Colour Depth (Restart Required)"
#define HANDY_GFX_COLORS_INFO_0_EN "Specify number of colours to display on-screen. 24-bit significantly increases performance overheads and is not available on all platforms."
#define OPTION_VAL_16BIT_EN NULL
#define OPTION_VAL_24BIT_EN NULL
#define HANDY_LCD_GHOSTING_LABEL_EN NULL
#define HANDY_LCD_GHOSTING_INFO_0_EN NULL
#define OPTION_VAL_2FRAMES_EN NULL
#define OPTION_VAL_3FRAMES_EN NULL
#define OPTION_VAL_4FRAMES_EN NULL
#define HANDY_FRAMESKIP_LABEL_EN "Frame-skip"
#define HANDY_FRAMESKIP_INFO_0_EN "Skip frames to avoid audio buffer under-run (crackling). Improves performance at the expense of visual smoothness. 'Auto' skips frames when advised by the front-end. 'Manual' utilizes the 'Frame-skip Threshold (%)' setting."
#define OPTION_VAL_AUTO_EN NULL
#define OPTION_VAL_MANUAL_EN NULL
#define HANDY_FRAMESKIP_THRESHOLD_LABEL_EN "Frame-skip Threshold (%)"
#define HANDY_FRAMESKIP_THRESHOLD_INFO_0_EN "When 'Frame-skip' is set to 'Manual', this specifies the audio buffer occupancy threshold (percentage) below which frames will be skipped. Higher values reduce the risk of crackling by causing frames to be dropped more frequently."

struct retro_core_option_v2_category option_cats_en[] = {
   { NULL, NULL, NULL },
};
struct retro_core_option_v2_definition option_defs_en[] = {
   {
      "handy_refresh_rate",
      HANDY_REFRESH_RATE_LABEL_EN,
      NULL,
      HANDY_REFRESH_RATE_INFO_0_EN,
      NULL,
      NULL,
      {
         { "50",  OPTION_VAL_50_EN },
         { "60",  OPTION_VAL_60_EN },
         { "75",  OPTION_VAL_75_EN },
         { "100", OPTION_VAL_100_EN },
         { "120", OPTION_VAL_120_EN },
         { NULL, NULL },
      },
      "60"
   },
   {
      "handy_rot",
      HANDY_ROT_LABEL_EN,
      NULL,
      HANDY_ROT_INFO_0_EN,
      NULL,
      NULL,
      {
         { "None", "disabled" },
         { "270",  OPTION_VAL_270_EN },
         { "90",   OPTION_VAL_90_EN },
         { NULL, NULL },
      },
      "None"
   },
#if defined(FRONTEND_SUPPORTS_XRGB8888)
   {
      "handy_gfx_colors",
      HANDY_GFX_COLORS_LABEL_EN,
      NULL,
      HANDY_GFX_COLORS_INFO_0_EN,
      NULL,
      NULL,
      {
         { "16bit", OPTION_VAL_16BIT_EN },
         { "24bit", OPTION_VAL_24BIT_EN },
         { NULL,    NULL },
      },
      "16bit"
   },
#endif
   {
      "handy_lcd_ghosting",
      HANDY_LCD_GHOSTING_LABEL_EN,
      NULL,
      HANDY_LCD_GHOSTING_INFO_0_EN,
      NULL,
      NULL,
      {
         { "disabled", NULL },
         { "2frames",  OPTION_VAL_2FRAMES_EN },
         { "3frames",  OPTION_VAL_3FRAMES_EN },
         { "4frames",  OPTION_VAL_4FRAMES_EN },
         { NULL, NULL },
      },
      "disabled"
   },
   {
      "handy_frameskip",
      HANDY_FRAMESKIP_LABEL_EN,
      NULL,
      HANDY_FRAMESKIP_INFO_0_EN,
      NULL,
      NULL,
      {
         { "disabled", NULL },
         { "auto",     OPTION_VAL_AUTO_EN },
         { "manual",   OPTION_VAL_MANUAL_EN },
         { NULL, NULL },
      },
      "disabled"
   },
   {
      "handy_frameskip_threshold",
      HANDY_FRAMESKIP_THRESHOLD_LABEL_EN,
      NULL,
      HANDY_FRAMESKIP_THRESHOLD_INFO_0_EN,
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
struct retro_core_options_v2 options_en = {
   option_cats_en,
   option_defs_en
};

/* RETRO_LANGUAGE_EO */

#define HANDY_REFRESH_RATE_LABEL_EO NULL
#define HANDY_REFRESH_RATE_INFO_0_EO NULL
#define OPTION_VAL_50_EO NULL
#define OPTION_VAL_60_EO NULL
#define OPTION_VAL_75_EO NULL
#define OPTION_VAL_100_EO NULL
#define OPTION_VAL_120_EO NULL
#define HANDY_ROT_LABEL_EO NULL
#define HANDY_ROT_INFO_0_EO NULL
#define OPTION_VAL_270_EO NULL
#define OPTION_VAL_90_EO NULL
#define HANDY_GFX_COLORS_LABEL_EO NULL
#define HANDY_GFX_COLORS_INFO_0_EO NULL
#define OPTION_VAL_16BIT_EO NULL
#define OPTION_VAL_24BIT_EO NULL
#define HANDY_LCD_GHOSTING_LABEL_EO NULL
#define HANDY_LCD_GHOSTING_INFO_0_EO NULL
#define OPTION_VAL_2FRAMES_EO NULL
#define OPTION_VAL_3FRAMES_EO NULL
#define OPTION_VAL_4FRAMES_EO NULL
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
      "handy_refresh_rate",
      HANDY_REFRESH_RATE_LABEL_EO,
      NULL,
      HANDY_REFRESH_RATE_INFO_0_EO,
      NULL,
      NULL,
      {
         { "50",  OPTION_VAL_50_EO },
         { "60",  OPTION_VAL_60_EO },
         { "75",  OPTION_VAL_75_EO },
         { "100", OPTION_VAL_100_EO },
         { "120", OPTION_VAL_120_EO },
         { NULL, NULL },
      },
      "60"
   },
   {
      "handy_rot",
      HANDY_ROT_LABEL_EO,
      NULL,
      HANDY_ROT_INFO_0_EO,
      NULL,
      NULL,
      {
         { "None", "disabled" },
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
      "handy_lcd_ghosting",
      HANDY_LCD_GHOSTING_LABEL_EO,
      NULL,
      HANDY_LCD_GHOSTING_INFO_0_EO,
      NULL,
      NULL,
      {
         { "disabled", NULL },
         { "2frames",  OPTION_VAL_2FRAMES_EO },
         { "3frames",  OPTION_VAL_3FRAMES_EO },
         { "4frames",  OPTION_VAL_4FRAMES_EO },
         { NULL, NULL },
      },
      "disabled"
   },
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

#define HANDY_REFRESH_RATE_LABEL_ES NULL
#define HANDY_REFRESH_RATE_INFO_0_ES NULL
#define OPTION_VAL_50_ES NULL
#define OPTION_VAL_60_ES NULL
#define OPTION_VAL_75_ES NULL
#define OPTION_VAL_100_ES NULL
#define OPTION_VAL_120_ES NULL
#define HANDY_ROT_LABEL_ES "Rotación de imagen"
#define HANDY_ROT_INFO_0_ES "Rota la pantalla virtual de la consola para mostrar correctamente los juegos con orientación vertical en una pantalla con orientación horizontal."
#define OPTION_VAL_270_ES "Girar a la derecha"
#define OPTION_VAL_90_ES "Girar a la izquierda"
#define HANDY_GFX_COLORS_LABEL_ES "Profundidad de color (es necesario reiniciar)"
#define HANDY_GFX_COLORS_INFO_0_ES "Especifica el número de colores a mostrar en pantalla. 24 bits reduce significativamente la carga de la CPU y no se encuentra disponible en todas las plataformas."
#define OPTION_VAL_16BIT_ES "Miles (16 bits)"
#define OPTION_VAL_24BIT_ES "Millones (24 bits)"
#define HANDY_LCD_GHOSTING_LABEL_ES "Filtro de efecto fantasma («ghosting») de LCD"
#define HANDY_LCD_GHOSTING_INFO_0_ES NULL
#define OPTION_VAL_2FRAMES_ES NULL
#define OPTION_VAL_3FRAMES_ES NULL
#define OPTION_VAL_4FRAMES_ES NULL
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
      "handy_refresh_rate",
      HANDY_REFRESH_RATE_LABEL_ES,
      NULL,
      HANDY_REFRESH_RATE_INFO_0_ES,
      NULL,
      NULL,
      {
         { "50",  OPTION_VAL_50_ES },
         { "60",  OPTION_VAL_60_ES },
         { "75",  OPTION_VAL_75_ES },
         { "100", OPTION_VAL_100_ES },
         { "120", OPTION_VAL_120_ES },
         { NULL, NULL },
      },
      "60"
   },
   {
      "handy_rot",
      HANDY_ROT_LABEL_ES,
      NULL,
      HANDY_ROT_INFO_0_ES,
      NULL,
      NULL,
      {
         { "None", "disabled" },
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
      "handy_lcd_ghosting",
      HANDY_LCD_GHOSTING_LABEL_ES,
      NULL,
      HANDY_LCD_GHOSTING_INFO_0_ES,
      NULL,
      NULL,
      {
         { "disabled", NULL },
         { "2frames",  OPTION_VAL_2FRAMES_ES },
         { "3frames",  OPTION_VAL_3FRAMES_ES },
         { "4frames",  OPTION_VAL_4FRAMES_ES },
         { NULL, NULL },
      },
      "disabled"
   },
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

#define HANDY_REFRESH_RATE_LABEL_FA NULL
#define HANDY_REFRESH_RATE_INFO_0_FA NULL
#define OPTION_VAL_50_FA NULL
#define OPTION_VAL_60_FA NULL
#define OPTION_VAL_75_FA NULL
#define OPTION_VAL_100_FA NULL
#define OPTION_VAL_120_FA NULL
#define HANDY_ROT_LABEL_FA "چرخش نمایشگر"
#define HANDY_ROT_INFO_0_FA "صفحه‌نمایش کنسول مجازی را بچرخانید تا به چیدمان صحیح بازی‌های «عمودی» روی یک نمایشگر معمولی (افقی) برسید."
#define OPTION_VAL_270_FA "ساعتگرد"
#define OPTION_VAL_90_FA "پادساعتگرد"
#define HANDY_GFX_COLORS_LABEL_FA "عمق رنگ (نیازمند بازآغاز)"
#define HANDY_GFX_COLORS_INFO_0_FA "تعداد رنگ ها را برای نمایش روی صفحه مشخص کنید. 24 بیتی به طور قابل توجهی سربار عملکرد را افزایش می دهد و در همه سیستم ها در دسترس نیست."
#define OPTION_VAL_16BIT_FA "هزار (۱۶-بیتی)"
#define OPTION_VAL_24BIT_FA "میلیون (۲۴-بیتی)"
#define HANDY_LCD_GHOSTING_LABEL_FA NULL
#define HANDY_LCD_GHOSTING_INFO_0_FA NULL
#define OPTION_VAL_2FRAMES_FA NULL
#define OPTION_VAL_3FRAMES_FA NULL
#define OPTION_VAL_4FRAMES_FA NULL
#define HANDY_FRAMESKIP_LABEL_FA "پرش فریم"
#define HANDY_FRAMESKIP_INFO_0_FA "برای جلوگیری از اجرا شدن بافر صوتی (ترق زدن) از فریم‌ها پرش کنید. عملکرد را در ازای صاف‌بودن تصویر بهبود می‌بخشد. حالت «خودکار»هنگام توصیهٔ پیشانه از روی فریم‌ها می‌پرد. حالت «دستی» تنظیم «آستانهٔ پرش فریم (٪)» را فعال می‌کند."
#define OPTION_VAL_AUTO_FA "خودکار"
#define OPTION_VAL_MANUAL_FA "دستی"
#define HANDY_FRAMESKIP_THRESHOLD_LABEL_FA "آستانهٔ پرش فریم (٪)"
#define HANDY_FRAMESKIP_THRESHOLD_INFO_0_FA "زمانی که «پرش فریم» روی «دستی» تنظیم شده باشد، آستانهٔ (درصد) اشغال بافر صوتی را برای پرش از روی فریم‌ها تنظیم می‌کند. مقادیر بالاتر احتمال ترق خوردن صدا را با رها کردن فریم‌های بیشتر، کاهش می‌دهد."

struct retro_core_option_v2_category option_cats_fa[] = {
   { NULL, NULL, NULL },
};
struct retro_core_option_v2_definition option_defs_fa[] = {
   {
      "handy_refresh_rate",
      HANDY_REFRESH_RATE_LABEL_FA,
      NULL,
      HANDY_REFRESH_RATE_INFO_0_FA,
      NULL,
      NULL,
      {
         { "50",  OPTION_VAL_50_FA },
         { "60",  OPTION_VAL_60_FA },
         { "75",  OPTION_VAL_75_FA },
         { "100", OPTION_VAL_100_FA },
         { "120", OPTION_VAL_120_FA },
         { NULL, NULL },
      },
      "60"
   },
   {
      "handy_rot",
      HANDY_ROT_LABEL_FA,
      NULL,
      HANDY_ROT_INFO_0_FA,
      NULL,
      NULL,
      {
         { "None", "disabled" },
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
      "handy_lcd_ghosting",
      HANDY_LCD_GHOSTING_LABEL_FA,
      NULL,
      HANDY_LCD_GHOSTING_INFO_0_FA,
      NULL,
      NULL,
      {
         { "disabled", NULL },
         { "2frames",  OPTION_VAL_2FRAMES_FA },
         { "3frames",  OPTION_VAL_3FRAMES_FA },
         { "4frames",  OPTION_VAL_4FRAMES_FA },
         { NULL, NULL },
      },
      "disabled"
   },
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

#define HANDY_REFRESH_RATE_LABEL_FI NULL
#define HANDY_REFRESH_RATE_INFO_0_FI NULL
#define OPTION_VAL_50_FI NULL
#define OPTION_VAL_60_FI NULL
#define OPTION_VAL_75_FI NULL
#define OPTION_VAL_100_FI NULL
#define OPTION_VAL_120_FI NULL
#define HANDY_ROT_LABEL_FI "Näytön kierto"
#define HANDY_ROT_INFO_0_FI "Kierrä virtuaalikonsolin näyttöä saadaksesi oikean ulkoasun tavallisella vaakatasonäytöllä sellaisille peleille, joiden oletuksena on pystykuvanäyttö."
#define OPTION_VAL_270_FI "Myötäpäivään"
#define OPTION_VAL_90_FI "Vastapäivään"
#define HANDY_GFX_COLORS_LABEL_FI "Värisyvyys (Uudelleenkäynnistys vaaditaan)"
#define HANDY_GFX_COLORS_INFO_0_FI "Määritä ruudulla näytettävien värien määrä. 24-bittinen kuormittaa suorituskykyä merkittävästi eikä ole käytettävissä kaikilla alustoilla."
#define OPTION_VAL_16BIT_FI "Tuhansissa (16-bit)"
#define OPTION_VAL_24BIT_FI "Miljoonissa (24-bittinen)"
#define HANDY_LCD_GHOSTING_LABEL_FI NULL
#define HANDY_LCD_GHOSTING_INFO_0_FI NULL
#define OPTION_VAL_2FRAMES_FI NULL
#define OPTION_VAL_3FRAMES_FI NULL
#define OPTION_VAL_4FRAMES_FI NULL
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
      "handy_refresh_rate",
      HANDY_REFRESH_RATE_LABEL_FI,
      NULL,
      HANDY_REFRESH_RATE_INFO_0_FI,
      NULL,
      NULL,
      {
         { "50",  OPTION_VAL_50_FI },
         { "60",  OPTION_VAL_60_FI },
         { "75",  OPTION_VAL_75_FI },
         { "100", OPTION_VAL_100_FI },
         { "120", OPTION_VAL_120_FI },
         { NULL, NULL },
      },
      "60"
   },
   {
      "handy_rot",
      HANDY_ROT_LABEL_FI,
      NULL,
      HANDY_ROT_INFO_0_FI,
      NULL,
      NULL,
      {
         { "None", "disabled" },
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
      "handy_lcd_ghosting",
      HANDY_LCD_GHOSTING_LABEL_FI,
      NULL,
      HANDY_LCD_GHOSTING_INFO_0_FI,
      NULL,
      NULL,
      {
         { "disabled", NULL },
         { "2frames",  OPTION_VAL_2FRAMES_FI },
         { "3frames",  OPTION_VAL_3FRAMES_FI },
         { "4frames",  OPTION_VAL_4FRAMES_FI },
         { NULL, NULL },
      },
      "disabled"
   },
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

#define HANDY_REFRESH_RATE_LABEL_FR NULL
#define HANDY_REFRESH_RATE_INFO_0_FR NULL
#define OPTION_VAL_50_FR NULL
#define OPTION_VAL_60_FR NULL
#define OPTION_VAL_75_FR NULL
#define OPTION_VAL_100_FR NULL
#define OPTION_VAL_120_FR NULL
#define HANDY_ROT_LABEL_FR "Rotation d'écran"
#define HANDY_ROT_INFO_0_FR "Faire pivoter l'écran de la console virtuelle pour obtenir la bonne présentation des jeux en mode 'portrait' sur un écran conventionnel (paysage)."
#define OPTION_VAL_270_FR "Horaire"
#define OPTION_VAL_90_FR "Anti-horaire"
#define HANDY_GFX_COLORS_LABEL_FR "Profondeur des couleurs (Redémarrage requis)"
#define HANDY_GFX_COLORS_INFO_0_FR "Spécifier le nombre de couleurs à afficher à l'écran. 24 bits augmente significativement la charge sur les performances et n'est pas disponible pour toutes les plateformes."
#define OPTION_VAL_16BIT_FR "Milliers (16 bits)"
#define OPTION_VAL_24BIT_FR "Millions (24 bits)"
#define HANDY_LCD_GHOSTING_LABEL_FR "Filtre de rémanence LCD"
#define HANDY_LCD_GHOSTING_INFO_0_FR NULL
#define OPTION_VAL_2FRAMES_FR NULL
#define OPTION_VAL_3FRAMES_FR NULL
#define OPTION_VAL_4FRAMES_FR NULL
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
      "handy_refresh_rate",
      HANDY_REFRESH_RATE_LABEL_FR,
      NULL,
      HANDY_REFRESH_RATE_INFO_0_FR,
      NULL,
      NULL,
      {
         { "50",  OPTION_VAL_50_FR },
         { "60",  OPTION_VAL_60_FR },
         { "75",  OPTION_VAL_75_FR },
         { "100", OPTION_VAL_100_FR },
         { "120", OPTION_VAL_120_FR },
         { NULL, NULL },
      },
      "60"
   },
   {
      "handy_rot",
      HANDY_ROT_LABEL_FR,
      NULL,
      HANDY_ROT_INFO_0_FR,
      NULL,
      NULL,
      {
         { "None", "disabled" },
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
      "handy_lcd_ghosting",
      HANDY_LCD_GHOSTING_LABEL_FR,
      NULL,
      HANDY_LCD_GHOSTING_INFO_0_FR,
      NULL,
      NULL,
      {
         { "disabled", NULL },
         { "2frames",  OPTION_VAL_2FRAMES_FR },
         { "3frames",  OPTION_VAL_3FRAMES_FR },
         { "4frames",  OPTION_VAL_4FRAMES_FR },
         { NULL, NULL },
      },
      "disabled"
   },
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

#define HANDY_REFRESH_RATE_LABEL_GL NULL
#define HANDY_REFRESH_RATE_INFO_0_GL NULL
#define OPTION_VAL_50_GL NULL
#define OPTION_VAL_60_GL NULL
#define OPTION_VAL_75_GL NULL
#define OPTION_VAL_100_GL NULL
#define OPTION_VAL_120_GL NULL
#define HANDY_ROT_LABEL_GL NULL
#define HANDY_ROT_INFO_0_GL NULL
#define OPTION_VAL_270_GL NULL
#define OPTION_VAL_90_GL NULL
#define HANDY_GFX_COLORS_LABEL_GL NULL
#define HANDY_GFX_COLORS_INFO_0_GL NULL
#define OPTION_VAL_16BIT_GL NULL
#define OPTION_VAL_24BIT_GL NULL
#define HANDY_LCD_GHOSTING_LABEL_GL NULL
#define HANDY_LCD_GHOSTING_INFO_0_GL NULL
#define OPTION_VAL_2FRAMES_GL NULL
#define OPTION_VAL_3FRAMES_GL NULL
#define OPTION_VAL_4FRAMES_GL NULL
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
      "handy_refresh_rate",
      HANDY_REFRESH_RATE_LABEL_GL,
      NULL,
      HANDY_REFRESH_RATE_INFO_0_GL,
      NULL,
      NULL,
      {
         { "50",  OPTION_VAL_50_GL },
         { "60",  OPTION_VAL_60_GL },
         { "75",  OPTION_VAL_75_GL },
         { "100", OPTION_VAL_100_GL },
         { "120", OPTION_VAL_120_GL },
         { NULL, NULL },
      },
      "60"
   },
   {
      "handy_rot",
      HANDY_ROT_LABEL_GL,
      NULL,
      HANDY_ROT_INFO_0_GL,
      NULL,
      NULL,
      {
         { "None", "disabled" },
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
      "handy_lcd_ghosting",
      HANDY_LCD_GHOSTING_LABEL_GL,
      NULL,
      HANDY_LCD_GHOSTING_INFO_0_GL,
      NULL,
      NULL,
      {
         { "disabled", NULL },
         { "2frames",  OPTION_VAL_2FRAMES_GL },
         { "3frames",  OPTION_VAL_3FRAMES_GL },
         { "4frames",  OPTION_VAL_4FRAMES_GL },
         { NULL, NULL },
      },
      "disabled"
   },
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

#define HANDY_REFRESH_RATE_LABEL_HE NULL
#define HANDY_REFRESH_RATE_INFO_0_HE NULL
#define OPTION_VAL_50_HE NULL
#define OPTION_VAL_60_HE NULL
#define OPTION_VAL_75_HE NULL
#define OPTION_VAL_100_HE NULL
#define OPTION_VAL_120_HE NULL
#define HANDY_ROT_LABEL_HE NULL
#define HANDY_ROT_INFO_0_HE NULL
#define OPTION_VAL_270_HE NULL
#define OPTION_VAL_90_HE NULL
#define HANDY_GFX_COLORS_LABEL_HE NULL
#define HANDY_GFX_COLORS_INFO_0_HE NULL
#define OPTION_VAL_16BIT_HE NULL
#define OPTION_VAL_24BIT_HE NULL
#define HANDY_LCD_GHOSTING_LABEL_HE NULL
#define HANDY_LCD_GHOSTING_INFO_0_HE NULL
#define OPTION_VAL_2FRAMES_HE NULL
#define OPTION_VAL_3FRAMES_HE NULL
#define OPTION_VAL_4FRAMES_HE NULL
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
      "handy_refresh_rate",
      HANDY_REFRESH_RATE_LABEL_HE,
      NULL,
      HANDY_REFRESH_RATE_INFO_0_HE,
      NULL,
      NULL,
      {
         { "50",  OPTION_VAL_50_HE },
         { "60",  OPTION_VAL_60_HE },
         { "75",  OPTION_VAL_75_HE },
         { "100", OPTION_VAL_100_HE },
         { "120", OPTION_VAL_120_HE },
         { NULL, NULL },
      },
      "60"
   },
   {
      "handy_rot",
      HANDY_ROT_LABEL_HE,
      NULL,
      HANDY_ROT_INFO_0_HE,
      NULL,
      NULL,
      {
         { "None", "disabled" },
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
      "handy_lcd_ghosting",
      HANDY_LCD_GHOSTING_LABEL_HE,
      NULL,
      HANDY_LCD_GHOSTING_INFO_0_HE,
      NULL,
      NULL,
      {
         { "disabled", NULL },
         { "2frames",  OPTION_VAL_2FRAMES_HE },
         { "3frames",  OPTION_VAL_3FRAMES_HE },
         { "4frames",  OPTION_VAL_4FRAMES_HE },
         { NULL, NULL },
      },
      "disabled"
   },
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

/* RETRO_LANGUAGE_HR */

#define HANDY_REFRESH_RATE_LABEL_HR NULL
#define HANDY_REFRESH_RATE_INFO_0_HR NULL
#define OPTION_VAL_50_HR NULL
#define OPTION_VAL_60_HR NULL
#define OPTION_VAL_75_HR NULL
#define OPTION_VAL_100_HR NULL
#define OPTION_VAL_120_HR NULL
#define HANDY_ROT_LABEL_HR NULL
#define HANDY_ROT_INFO_0_HR NULL
#define OPTION_VAL_270_HR NULL
#define OPTION_VAL_90_HR NULL
#define HANDY_GFX_COLORS_LABEL_HR NULL
#define HANDY_GFX_COLORS_INFO_0_HR NULL
#define OPTION_VAL_16BIT_HR NULL
#define OPTION_VAL_24BIT_HR NULL
#define HANDY_LCD_GHOSTING_LABEL_HR NULL
#define HANDY_LCD_GHOSTING_INFO_0_HR NULL
#define OPTION_VAL_2FRAMES_HR NULL
#define OPTION_VAL_3FRAMES_HR NULL
#define OPTION_VAL_4FRAMES_HR NULL
#define HANDY_FRAMESKIP_LABEL_HR NULL
#define HANDY_FRAMESKIP_INFO_0_HR NULL
#define OPTION_VAL_AUTO_HR NULL
#define OPTION_VAL_MANUAL_HR NULL
#define HANDY_FRAMESKIP_THRESHOLD_LABEL_HR NULL
#define HANDY_FRAMESKIP_THRESHOLD_INFO_0_HR NULL

struct retro_core_option_v2_category option_cats_hr[] = {
   { NULL, NULL, NULL },
};
struct retro_core_option_v2_definition option_defs_hr[] = {
   {
      "handy_refresh_rate",
      HANDY_REFRESH_RATE_LABEL_HR,
      NULL,
      HANDY_REFRESH_RATE_INFO_0_HR,
      NULL,
      NULL,
      {
         { "50",  OPTION_VAL_50_HR },
         { "60",  OPTION_VAL_60_HR },
         { "75",  OPTION_VAL_75_HR },
         { "100", OPTION_VAL_100_HR },
         { "120", OPTION_VAL_120_HR },
         { NULL, NULL },
      },
      "60"
   },
   {
      "handy_rot",
      HANDY_ROT_LABEL_HR,
      NULL,
      HANDY_ROT_INFO_0_HR,
      NULL,
      NULL,
      {
         { "None", "disabled" },
         { "270",  OPTION_VAL_270_HR },
         { "90",   OPTION_VAL_90_HR },
         { NULL, NULL },
      },
      "None"
   },
#if defined(FRONTEND_SUPPORTS_XRGB8888)
   {
      "handy_gfx_colors",
      HANDY_GFX_COLORS_LABEL_HR,
      NULL,
      HANDY_GFX_COLORS_INFO_0_HR,
      NULL,
      NULL,
      {
         { "16bit", OPTION_VAL_16BIT_HR },
         { "24bit", OPTION_VAL_24BIT_HR },
         { NULL,    NULL },
      },
      "16bit"
   },
#endif
   {
      "handy_lcd_ghosting",
      HANDY_LCD_GHOSTING_LABEL_HR,
      NULL,
      HANDY_LCD_GHOSTING_INFO_0_HR,
      NULL,
      NULL,
      {
         { "disabled", NULL },
         { "2frames",  OPTION_VAL_2FRAMES_HR },
         { "3frames",  OPTION_VAL_3FRAMES_HR },
         { "4frames",  OPTION_VAL_4FRAMES_HR },
         { NULL, NULL },
      },
      "disabled"
   },
   {
      "handy_frameskip",
      HANDY_FRAMESKIP_LABEL_HR,
      NULL,
      HANDY_FRAMESKIP_INFO_0_HR,
      NULL,
      NULL,
      {
         { "disabled", NULL },
         { "auto",     OPTION_VAL_AUTO_HR },
         { "manual",   OPTION_VAL_MANUAL_HR },
         { NULL, NULL },
      },
      "disabled"
   },
   {
      "handy_frameskip_threshold",
      HANDY_FRAMESKIP_THRESHOLD_LABEL_HR,
      NULL,
      HANDY_FRAMESKIP_THRESHOLD_INFO_0_HR,
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
struct retro_core_options_v2 options_hr = {
   option_cats_hr,
   option_defs_hr
};

/* RETRO_LANGUAGE_HU */

#define HANDY_REFRESH_RATE_LABEL_HU NULL
#define HANDY_REFRESH_RATE_INFO_0_HU NULL
#define OPTION_VAL_50_HU NULL
#define OPTION_VAL_60_HU NULL
#define OPTION_VAL_75_HU NULL
#define OPTION_VAL_100_HU NULL
#define OPTION_VAL_120_HU NULL
#define HANDY_ROT_LABEL_HU "Kijelző elforgatás"
#define HANDY_ROT_INFO_0_HU "A virtuális konzol képernyőjének elforgatása, hogy az álló formátumú játékok elrendezése megfelelő legyen egy hagyományos (fekvő) kijelzőn."
#define OPTION_VAL_270_HU "Óramutató járásával megegyező irányban"
#define OPTION_VAL_90_HU "Óramutató járásával ellentétesen"
#define HANDY_GFX_COLORS_LABEL_HU "Színmélység (újraindítás szükséges)"
#define HANDY_GFX_COLORS_INFO_0_HU "A képernyőn megjeleníthető színek száma. A 24 bitnek jelentős teljesítményigénye van és nem elérhető minden platformon."
#define OPTION_VAL_16BIT_HU "Több ezer (16 bites)"
#define OPTION_VAL_24BIT_HU "Több millió (24 bites)"
#define HANDY_LCD_GHOSTING_LABEL_HU "LCD szellemkép szűrő"
#define HANDY_LCD_GHOSTING_INFO_0_HU NULL
#define OPTION_VAL_2FRAMES_HU NULL
#define OPTION_VAL_3FRAMES_HU NULL
#define OPTION_VAL_4FRAMES_HU NULL
#define HANDY_FRAMESKIP_LABEL_HU "Képkocka kihagyás"
#define HANDY_FRAMESKIP_INFO_0_HU "A hangbuffer kiürülése (recsegés) elkerülésére képkockák eldobása. Javít a teljesítményen a vizuális folyamatosság kárára. Az \"Automatikus\" beállítás akkor dob képkockát, ha a frontend azt javasolja. A \"Kézi\" a \"Képkocka kihagyás határértéke (%)\" beállítást használja."
#define OPTION_VAL_AUTO_HU "Automatikus"
#define OPTION_VAL_MANUAL_HU "Kézi"
#define HANDY_FRAMESKIP_THRESHOLD_LABEL_HU "Képkocka kihagyás határértéke (%)"
#define HANDY_FRAMESKIP_THRESHOLD_INFO_0_HU "Ha a \"Képkocka kihagyás\" \"Kézi\" értékre van állítva, ez határozza meg a hangpuffer telítettségi határát (százalékban), amely alatt képkockákat dob el. Nagyobb érték csökkenti a recsegés kockázatát azáltal, hogy gyakrabban dob el képkockát."

struct retro_core_option_v2_category option_cats_hu[] = {
   { NULL, NULL, NULL },
};
struct retro_core_option_v2_definition option_defs_hu[] = {
   {
      "handy_refresh_rate",
      HANDY_REFRESH_RATE_LABEL_HU,
      NULL,
      HANDY_REFRESH_RATE_INFO_0_HU,
      NULL,
      NULL,
      {
         { "50",  OPTION_VAL_50_HU },
         { "60",  OPTION_VAL_60_HU },
         { "75",  OPTION_VAL_75_HU },
         { "100", OPTION_VAL_100_HU },
         { "120", OPTION_VAL_120_HU },
         { NULL, NULL },
      },
      "60"
   },
   {
      "handy_rot",
      HANDY_ROT_LABEL_HU,
      NULL,
      HANDY_ROT_INFO_0_HU,
      NULL,
      NULL,
      {
         { "None", "disabled" },
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
      "handy_lcd_ghosting",
      HANDY_LCD_GHOSTING_LABEL_HU,
      NULL,
      HANDY_LCD_GHOSTING_INFO_0_HU,
      NULL,
      NULL,
      {
         { "disabled", NULL },
         { "2frames",  OPTION_VAL_2FRAMES_HU },
         { "3frames",  OPTION_VAL_3FRAMES_HU },
         { "4frames",  OPTION_VAL_4FRAMES_HU },
         { NULL, NULL },
      },
      "disabled"
   },
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

#define HANDY_REFRESH_RATE_LABEL_ID NULL
#define HANDY_REFRESH_RATE_INFO_0_ID NULL
#define OPTION_VAL_50_ID NULL
#define OPTION_VAL_60_ID NULL
#define OPTION_VAL_75_ID NULL
#define OPTION_VAL_100_ID NULL
#define OPTION_VAL_120_ID NULL
#define HANDY_ROT_LABEL_ID NULL
#define HANDY_ROT_INFO_0_ID "Putar orientasi layar untuk mendapat tata letak yang betul pada permainan berlayar 'menegak' pada tampilan layar mendatar (landscape)."
#define OPTION_VAL_270_ID NULL
#define OPTION_VAL_90_ID NULL
#define HANDY_GFX_COLORS_LABEL_ID NULL
#define HANDY_GFX_COLORS_INFO_0_ID "Pilih kedalaman warna untuk ditampilkan di layar. Kedalaman warna 24-bit meningkatkan kinerja secara signifikan dan tidak tersedia di semua pelantar."
#define OPTION_VAL_16BIT_ID NULL
#define OPTION_VAL_24BIT_ID NULL
#define HANDY_LCD_GHOSTING_LABEL_ID NULL
#define HANDY_LCD_GHOSTING_INFO_0_ID NULL
#define OPTION_VAL_2FRAMES_ID NULL
#define OPTION_VAL_3FRAMES_ID NULL
#define OPTION_VAL_4FRAMES_ID NULL
#define HANDY_FRAMESKIP_LABEL_ID NULL
#define HANDY_FRAMESKIP_INFO_0_ID NULL
#define OPTION_VAL_AUTO_ID "Otomatis"
#define OPTION_VAL_MANUAL_ID NULL
#define HANDY_FRAMESKIP_THRESHOLD_LABEL_ID NULL
#define HANDY_FRAMESKIP_THRESHOLD_INFO_0_ID "Saat 'Lewati Bingkai' diatur ke 'Manual', tentukan (persentase) ambang batas hunian penyangga audio di bawah untuk bingkai mana yang dilewati. Nilai yang lebih tinggi mengurangi risiko keretakan dengan cara membuat laju bingkai sering anjlok."

struct retro_core_option_v2_category option_cats_id[] = {
   { NULL, NULL, NULL },
};
struct retro_core_option_v2_definition option_defs_id[] = {
   {
      "handy_refresh_rate",
      HANDY_REFRESH_RATE_LABEL_ID,
      NULL,
      HANDY_REFRESH_RATE_INFO_0_ID,
      NULL,
      NULL,
      {
         { "50",  OPTION_VAL_50_ID },
         { "60",  OPTION_VAL_60_ID },
         { "75",  OPTION_VAL_75_ID },
         { "100", OPTION_VAL_100_ID },
         { "120", OPTION_VAL_120_ID },
         { NULL, NULL },
      },
      "60"
   },
   {
      "handy_rot",
      HANDY_ROT_LABEL_ID,
      NULL,
      HANDY_ROT_INFO_0_ID,
      NULL,
      NULL,
      {
         { "None", "disabled" },
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
      "handy_lcd_ghosting",
      HANDY_LCD_GHOSTING_LABEL_ID,
      NULL,
      HANDY_LCD_GHOSTING_INFO_0_ID,
      NULL,
      NULL,
      {
         { "disabled", NULL },
         { "2frames",  OPTION_VAL_2FRAMES_ID },
         { "3frames",  OPTION_VAL_3FRAMES_ID },
         { "4frames",  OPTION_VAL_4FRAMES_ID },
         { NULL, NULL },
      },
      "disabled"
   },
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

#define HANDY_REFRESH_RATE_LABEL_IT NULL
#define HANDY_REFRESH_RATE_INFO_0_IT NULL
#define OPTION_VAL_50_IT NULL
#define OPTION_VAL_60_IT NULL
#define OPTION_VAL_75_IT NULL
#define OPTION_VAL_100_IT NULL
#define OPTION_VAL_120_IT NULL
#define HANDY_ROT_LABEL_IT "Rotazione Display"
#define HANDY_ROT_INFO_0_IT "Ruota lo schermo della console virtuale per ottenere il corretto layout dei giochi orientati al 'ritratto' su uno schermo convenzionale (orizzontale)."
#define OPTION_VAL_270_IT "Orario"
#define OPTION_VAL_90_IT "Anticorveglianza"
#define HANDY_GFX_COLORS_LABEL_IT "Profondità Colore (Restart Richiesto)"
#define HANDY_GFX_COLORS_INFO_0_IT "Specifica il numero di colori da visualizzare sullo schermo. 24-bit aumenta significativamente le prestazioni generali e non è disponibile su tutte le piattaforme."
#define OPTION_VAL_16BIT_IT "Migliaia (16-bit)"
#define OPTION_VAL_24BIT_IT "Milioni (24-bit)"
#define HANDY_LCD_GHOSTING_LABEL_IT "Filtro Lcd Ghosting"
#define HANDY_LCD_GHOSTING_INFO_0_IT NULL
#define OPTION_VAL_2FRAMES_IT NULL
#define OPTION_VAL_3FRAMES_IT NULL
#define OPTION_VAL_4FRAMES_IT NULL
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
      "handy_refresh_rate",
      HANDY_REFRESH_RATE_LABEL_IT,
      NULL,
      HANDY_REFRESH_RATE_INFO_0_IT,
      NULL,
      NULL,
      {
         { "50",  OPTION_VAL_50_IT },
         { "60",  OPTION_VAL_60_IT },
         { "75",  OPTION_VAL_75_IT },
         { "100", OPTION_VAL_100_IT },
         { "120", OPTION_VAL_120_IT },
         { NULL, NULL },
      },
      "60"
   },
   {
      "handy_rot",
      HANDY_ROT_LABEL_IT,
      NULL,
      HANDY_ROT_INFO_0_IT,
      NULL,
      NULL,
      {
         { "None", "disabled" },
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
      "handy_lcd_ghosting",
      HANDY_LCD_GHOSTING_LABEL_IT,
      NULL,
      HANDY_LCD_GHOSTING_INFO_0_IT,
      NULL,
      NULL,
      {
         { "disabled", NULL },
         { "2frames",  OPTION_VAL_2FRAMES_IT },
         { "3frames",  OPTION_VAL_3FRAMES_IT },
         { "4frames",  OPTION_VAL_4FRAMES_IT },
         { NULL, NULL },
      },
      "disabled"
   },
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

#define HANDY_REFRESH_RATE_LABEL_JA NULL
#define HANDY_REFRESH_RATE_INFO_0_JA NULL
#define OPTION_VAL_50_JA NULL
#define OPTION_VAL_60_JA NULL
#define OPTION_VAL_75_JA NULL
#define OPTION_VAL_100_JA NULL
#define OPTION_VAL_120_JA NULL
#define HANDY_ROT_LABEL_JA "ディスプレイの回転"
#define HANDY_ROT_INFO_0_JA "仮想コンソール画面を回転させ, 従来の(横長画面) ディスプレイ上で縦長画面のゲームの正しいレイアウトを実現します."
#define OPTION_VAL_270_JA "時計回り"
#define OPTION_VAL_90_JA "反時計回り"
#define HANDY_GFX_COLORS_LABEL_JA "色深度 (再起動が必要)"
#define HANDY_GFX_COLORS_INFO_0_JA "画面上に表示色数を指定します. 24ビットは負荷が大幅に増加するため, 利用できないプラットフォームもあります."
#define OPTION_VAL_16BIT_JA "数千 (16ビット)"
#define OPTION_VAL_24BIT_JA "数百万 (24ビット)"
#define HANDY_LCD_GHOSTING_LABEL_JA NULL
#define HANDY_LCD_GHOSTING_INFO_0_JA NULL
#define OPTION_VAL_2FRAMES_JA NULL
#define OPTION_VAL_3FRAMES_JA NULL
#define OPTION_VAL_4FRAMES_JA NULL
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
      "handy_refresh_rate",
      HANDY_REFRESH_RATE_LABEL_JA,
      NULL,
      HANDY_REFRESH_RATE_INFO_0_JA,
      NULL,
      NULL,
      {
         { "50",  OPTION_VAL_50_JA },
         { "60",  OPTION_VAL_60_JA },
         { "75",  OPTION_VAL_75_JA },
         { "100", OPTION_VAL_100_JA },
         { "120", OPTION_VAL_120_JA },
         { NULL, NULL },
      },
      "60"
   },
   {
      "handy_rot",
      HANDY_ROT_LABEL_JA,
      NULL,
      HANDY_ROT_INFO_0_JA,
      NULL,
      NULL,
      {
         { "None", "disabled" },
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
      "handy_lcd_ghosting",
      HANDY_LCD_GHOSTING_LABEL_JA,
      NULL,
      HANDY_LCD_GHOSTING_INFO_0_JA,
      NULL,
      NULL,
      {
         { "disabled", NULL },
         { "2frames",  OPTION_VAL_2FRAMES_JA },
         { "3frames",  OPTION_VAL_3FRAMES_JA },
         { "4frames",  OPTION_VAL_4FRAMES_JA },
         { NULL, NULL },
      },
      "disabled"
   },
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

#define HANDY_REFRESH_RATE_LABEL_KO NULL
#define HANDY_REFRESH_RATE_INFO_0_KO NULL
#define OPTION_VAL_50_KO NULL
#define OPTION_VAL_60_KO NULL
#define OPTION_VAL_75_KO NULL
#define OPTION_VAL_100_KO NULL
#define OPTION_VAL_120_KO NULL
#define HANDY_ROT_LABEL_KO "화면 회전"
#define HANDY_ROT_INFO_0_KO "가상 콘솔 화면을 회전시켜 '세로' 화면을 사용하는 게임들이 일반적인 가로 화면에서도 올바르게 표시되도록 합니다."
#define OPTION_VAL_270_KO "시계방향"
#define OPTION_VAL_90_KO "반시계방향"
#define HANDY_GFX_COLORS_LABEL_KO "색 깊이 (재시작 필요)"
#define HANDY_GFX_COLORS_INFO_0_KO "화면에 표시할 색상 수를 지정합니다. 24비트는 성능에 큰 영향을 끼치며 일부 기기에서는 사용할 수 없습니다."
#define OPTION_VAL_16BIT_KO "수천가지 (16비트)"
#define OPTION_VAL_24BIT_KO "수백만가지 (24비트)"
#define HANDY_LCD_GHOSTING_LABEL_KO "LCD 고스팅 필터"
#define HANDY_LCD_GHOSTING_INFO_0_KO NULL
#define OPTION_VAL_2FRAMES_KO NULL
#define OPTION_VAL_3FRAMES_KO NULL
#define OPTION_VAL_4FRAMES_KO NULL
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
      "handy_refresh_rate",
      HANDY_REFRESH_RATE_LABEL_KO,
      NULL,
      HANDY_REFRESH_RATE_INFO_0_KO,
      NULL,
      NULL,
      {
         { "50",  OPTION_VAL_50_KO },
         { "60",  OPTION_VAL_60_KO },
         { "75",  OPTION_VAL_75_KO },
         { "100", OPTION_VAL_100_KO },
         { "120", OPTION_VAL_120_KO },
         { NULL, NULL },
      },
      "60"
   },
   {
      "handy_rot",
      HANDY_ROT_LABEL_KO,
      NULL,
      HANDY_ROT_INFO_0_KO,
      NULL,
      NULL,
      {
         { "None", "disabled" },
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
      "handy_lcd_ghosting",
      HANDY_LCD_GHOSTING_LABEL_KO,
      NULL,
      HANDY_LCD_GHOSTING_INFO_0_KO,
      NULL,
      NULL,
      {
         { "disabled", NULL },
         { "2frames",  OPTION_VAL_2FRAMES_KO },
         { "3frames",  OPTION_VAL_3FRAMES_KO },
         { "4frames",  OPTION_VAL_4FRAMES_KO },
         { NULL, NULL },
      },
      "disabled"
   },
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

#define HANDY_REFRESH_RATE_LABEL_MT NULL
#define HANDY_REFRESH_RATE_INFO_0_MT NULL
#define OPTION_VAL_50_MT NULL
#define OPTION_VAL_60_MT NULL
#define OPTION_VAL_75_MT NULL
#define OPTION_VAL_100_MT NULL
#define OPTION_VAL_120_MT NULL
#define HANDY_ROT_LABEL_MT NULL
#define HANDY_ROT_INFO_0_MT NULL
#define OPTION_VAL_270_MT NULL
#define OPTION_VAL_90_MT NULL
#define HANDY_GFX_COLORS_LABEL_MT NULL
#define HANDY_GFX_COLORS_INFO_0_MT NULL
#define OPTION_VAL_16BIT_MT NULL
#define OPTION_VAL_24BIT_MT NULL
#define HANDY_LCD_GHOSTING_LABEL_MT NULL
#define HANDY_LCD_GHOSTING_INFO_0_MT NULL
#define OPTION_VAL_2FRAMES_MT NULL
#define OPTION_VAL_3FRAMES_MT NULL
#define OPTION_VAL_4FRAMES_MT NULL
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
      "handy_refresh_rate",
      HANDY_REFRESH_RATE_LABEL_MT,
      NULL,
      HANDY_REFRESH_RATE_INFO_0_MT,
      NULL,
      NULL,
      {
         { "50",  OPTION_VAL_50_MT },
         { "60",  OPTION_VAL_60_MT },
         { "75",  OPTION_VAL_75_MT },
         { "100", OPTION_VAL_100_MT },
         { "120", OPTION_VAL_120_MT },
         { NULL, NULL },
      },
      "60"
   },
   {
      "handy_rot",
      HANDY_ROT_LABEL_MT,
      NULL,
      HANDY_ROT_INFO_0_MT,
      NULL,
      NULL,
      {
         { "None", "disabled" },
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
      "handy_lcd_ghosting",
      HANDY_LCD_GHOSTING_LABEL_MT,
      NULL,
      HANDY_LCD_GHOSTING_INFO_0_MT,
      NULL,
      NULL,
      {
         { "disabled", NULL },
         { "2frames",  OPTION_VAL_2FRAMES_MT },
         { "3frames",  OPTION_VAL_3FRAMES_MT },
         { "4frames",  OPTION_VAL_4FRAMES_MT },
         { NULL, NULL },
      },
      "disabled"
   },
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

#define HANDY_REFRESH_RATE_LABEL_NL NULL
#define HANDY_REFRESH_RATE_INFO_0_NL NULL
#define OPTION_VAL_50_NL NULL
#define OPTION_VAL_60_NL NULL
#define OPTION_VAL_75_NL NULL
#define OPTION_VAL_100_NL NULL
#define OPTION_VAL_120_NL NULL
#define HANDY_ROT_LABEL_NL NULL
#define HANDY_ROT_INFO_0_NL NULL
#define OPTION_VAL_270_NL NULL
#define OPTION_VAL_90_NL NULL
#define HANDY_GFX_COLORS_LABEL_NL NULL
#define HANDY_GFX_COLORS_INFO_0_NL NULL
#define OPTION_VAL_16BIT_NL NULL
#define OPTION_VAL_24BIT_NL NULL
#define HANDY_LCD_GHOSTING_LABEL_NL NULL
#define HANDY_LCD_GHOSTING_INFO_0_NL NULL
#define OPTION_VAL_2FRAMES_NL NULL
#define OPTION_VAL_3FRAMES_NL NULL
#define OPTION_VAL_4FRAMES_NL NULL
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
      "handy_refresh_rate",
      HANDY_REFRESH_RATE_LABEL_NL,
      NULL,
      HANDY_REFRESH_RATE_INFO_0_NL,
      NULL,
      NULL,
      {
         { "50",  OPTION_VAL_50_NL },
         { "60",  OPTION_VAL_60_NL },
         { "75",  OPTION_VAL_75_NL },
         { "100", OPTION_VAL_100_NL },
         { "120", OPTION_VAL_120_NL },
         { NULL, NULL },
      },
      "60"
   },
   {
      "handy_rot",
      HANDY_ROT_LABEL_NL,
      NULL,
      HANDY_ROT_INFO_0_NL,
      NULL,
      NULL,
      {
         { "None", "disabled" },
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
      "handy_lcd_ghosting",
      HANDY_LCD_GHOSTING_LABEL_NL,
      NULL,
      HANDY_LCD_GHOSTING_INFO_0_NL,
      NULL,
      NULL,
      {
         { "disabled", NULL },
         { "2frames",  OPTION_VAL_2FRAMES_NL },
         { "3frames",  OPTION_VAL_3FRAMES_NL },
         { "4frames",  OPTION_VAL_4FRAMES_NL },
         { NULL, NULL },
      },
      "disabled"
   },
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

/* RETRO_LANGUAGE_NO */

#define HANDY_REFRESH_RATE_LABEL_NO NULL
#define HANDY_REFRESH_RATE_INFO_0_NO NULL
#define OPTION_VAL_50_NO NULL
#define OPTION_VAL_60_NO NULL
#define OPTION_VAL_75_NO NULL
#define OPTION_VAL_100_NO NULL
#define OPTION_VAL_120_NO NULL
#define HANDY_ROT_LABEL_NO NULL
#define HANDY_ROT_INFO_0_NO NULL
#define OPTION_VAL_270_NO NULL
#define OPTION_VAL_90_NO NULL
#define HANDY_GFX_COLORS_LABEL_NO NULL
#define HANDY_GFX_COLORS_INFO_0_NO NULL
#define OPTION_VAL_16BIT_NO NULL
#define OPTION_VAL_24BIT_NO NULL
#define HANDY_LCD_GHOSTING_LABEL_NO NULL
#define HANDY_LCD_GHOSTING_INFO_0_NO NULL
#define OPTION_VAL_2FRAMES_NO NULL
#define OPTION_VAL_3FRAMES_NO NULL
#define OPTION_VAL_4FRAMES_NO NULL
#define HANDY_FRAMESKIP_LABEL_NO NULL
#define HANDY_FRAMESKIP_INFO_0_NO NULL
#define OPTION_VAL_AUTO_NO NULL
#define OPTION_VAL_MANUAL_NO NULL
#define HANDY_FRAMESKIP_THRESHOLD_LABEL_NO NULL
#define HANDY_FRAMESKIP_THRESHOLD_INFO_0_NO NULL

struct retro_core_option_v2_category option_cats_no[] = {
   { NULL, NULL, NULL },
};
struct retro_core_option_v2_definition option_defs_no[] = {
   {
      "handy_refresh_rate",
      HANDY_REFRESH_RATE_LABEL_NO,
      NULL,
      HANDY_REFRESH_RATE_INFO_0_NO,
      NULL,
      NULL,
      {
         { "50",  OPTION_VAL_50_NO },
         { "60",  OPTION_VAL_60_NO },
         { "75",  OPTION_VAL_75_NO },
         { "100", OPTION_VAL_100_NO },
         { "120", OPTION_VAL_120_NO },
         { NULL, NULL },
      },
      "60"
   },
   {
      "handy_rot",
      HANDY_ROT_LABEL_NO,
      NULL,
      HANDY_ROT_INFO_0_NO,
      NULL,
      NULL,
      {
         { "None", "disabled" },
         { "270",  OPTION_VAL_270_NO },
         { "90",   OPTION_VAL_90_NO },
         { NULL, NULL },
      },
      "None"
   },
#if defined(FRONTEND_SUPPORTS_XRGB8888)
   {
      "handy_gfx_colors",
      HANDY_GFX_COLORS_LABEL_NO,
      NULL,
      HANDY_GFX_COLORS_INFO_0_NO,
      NULL,
      NULL,
      {
         { "16bit", OPTION_VAL_16BIT_NO },
         { "24bit", OPTION_VAL_24BIT_NO },
         { NULL,    NULL },
      },
      "16bit"
   },
#endif
   {
      "handy_lcd_ghosting",
      HANDY_LCD_GHOSTING_LABEL_NO,
      NULL,
      HANDY_LCD_GHOSTING_INFO_0_NO,
      NULL,
      NULL,
      {
         { "disabled", NULL },
         { "2frames",  OPTION_VAL_2FRAMES_NO },
         { "3frames",  OPTION_VAL_3FRAMES_NO },
         { "4frames",  OPTION_VAL_4FRAMES_NO },
         { NULL, NULL },
      },
      "disabled"
   },
   {
      "handy_frameskip",
      HANDY_FRAMESKIP_LABEL_NO,
      NULL,
      HANDY_FRAMESKIP_INFO_0_NO,
      NULL,
      NULL,
      {
         { "disabled", NULL },
         { "auto",     OPTION_VAL_AUTO_NO },
         { "manual",   OPTION_VAL_MANUAL_NO },
         { NULL, NULL },
      },
      "disabled"
   },
   {
      "handy_frameskip_threshold",
      HANDY_FRAMESKIP_THRESHOLD_LABEL_NO,
      NULL,
      HANDY_FRAMESKIP_THRESHOLD_INFO_0_NO,
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
struct retro_core_options_v2 options_no = {
   option_cats_no,
   option_defs_no
};

/* RETRO_LANGUAGE_OC */

#define HANDY_REFRESH_RATE_LABEL_OC NULL
#define HANDY_REFRESH_RATE_INFO_0_OC NULL
#define OPTION_VAL_50_OC NULL
#define OPTION_VAL_60_OC NULL
#define OPTION_VAL_75_OC NULL
#define OPTION_VAL_100_OC NULL
#define OPTION_VAL_120_OC NULL
#define HANDY_ROT_LABEL_OC NULL
#define HANDY_ROT_INFO_0_OC NULL
#define OPTION_VAL_270_OC NULL
#define OPTION_VAL_90_OC NULL
#define HANDY_GFX_COLORS_LABEL_OC NULL
#define HANDY_GFX_COLORS_INFO_0_OC NULL
#define OPTION_VAL_16BIT_OC NULL
#define OPTION_VAL_24BIT_OC NULL
#define HANDY_LCD_GHOSTING_LABEL_OC NULL
#define HANDY_LCD_GHOSTING_INFO_0_OC NULL
#define OPTION_VAL_2FRAMES_OC NULL
#define OPTION_VAL_3FRAMES_OC NULL
#define OPTION_VAL_4FRAMES_OC NULL
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
      "handy_refresh_rate",
      HANDY_REFRESH_RATE_LABEL_OC,
      NULL,
      HANDY_REFRESH_RATE_INFO_0_OC,
      NULL,
      NULL,
      {
         { "50",  OPTION_VAL_50_OC },
         { "60",  OPTION_VAL_60_OC },
         { "75",  OPTION_VAL_75_OC },
         { "100", OPTION_VAL_100_OC },
         { "120", OPTION_VAL_120_OC },
         { NULL, NULL },
      },
      "60"
   },
   {
      "handy_rot",
      HANDY_ROT_LABEL_OC,
      NULL,
      HANDY_ROT_INFO_0_OC,
      NULL,
      NULL,
      {
         { "None", "disabled" },
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
      "handy_lcd_ghosting",
      HANDY_LCD_GHOSTING_LABEL_OC,
      NULL,
      HANDY_LCD_GHOSTING_INFO_0_OC,
      NULL,
      NULL,
      {
         { "disabled", NULL },
         { "2frames",  OPTION_VAL_2FRAMES_OC },
         { "3frames",  OPTION_VAL_3FRAMES_OC },
         { "4frames",  OPTION_VAL_4FRAMES_OC },
         { NULL, NULL },
      },
      "disabled"
   },
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

#define HANDY_REFRESH_RATE_LABEL_PL NULL
#define HANDY_REFRESH_RATE_INFO_0_PL NULL
#define OPTION_VAL_50_PL NULL
#define OPTION_VAL_60_PL NULL
#define OPTION_VAL_75_PL NULL
#define OPTION_VAL_100_PL NULL
#define OPTION_VAL_120_PL NULL
#define HANDY_ROT_LABEL_PL "Obrót ekranu"
#define HANDY_ROT_INFO_0_PL "Obróć wirtualny ekran konsoli, aby osiągnąć prawidłowy układ gier zorientowanych pionowo na konwencjonalnym wyświetlaczu (pejzaż)."
#define OPTION_VAL_270_PL NULL
#define OPTION_VAL_90_PL NULL
#define HANDY_GFX_COLORS_LABEL_PL NULL
#define HANDY_GFX_COLORS_INFO_0_PL "Określ liczbę kolorów wyświetlanych na ekranie. 24-bitowe znacznie zwiększają zapotrzebowanie na moc obliczeniową i nie jest dostępne na wszystkich platformach."
#define OPTION_VAL_16BIT_PL NULL
#define OPTION_VAL_24BIT_PL NULL
#define HANDY_LCD_GHOSTING_LABEL_PL NULL
#define HANDY_LCD_GHOSTING_INFO_0_PL NULL
#define OPTION_VAL_2FRAMES_PL NULL
#define OPTION_VAL_3FRAMES_PL NULL
#define OPTION_VAL_4FRAMES_PL NULL
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
      "handy_refresh_rate",
      HANDY_REFRESH_RATE_LABEL_PL,
      NULL,
      HANDY_REFRESH_RATE_INFO_0_PL,
      NULL,
      NULL,
      {
         { "50",  OPTION_VAL_50_PL },
         { "60",  OPTION_VAL_60_PL },
         { "75",  OPTION_VAL_75_PL },
         { "100", OPTION_VAL_100_PL },
         { "120", OPTION_VAL_120_PL },
         { NULL, NULL },
      },
      "60"
   },
   {
      "handy_rot",
      HANDY_ROT_LABEL_PL,
      NULL,
      HANDY_ROT_INFO_0_PL,
      NULL,
      NULL,
      {
         { "None", "disabled" },
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
      "handy_lcd_ghosting",
      HANDY_LCD_GHOSTING_LABEL_PL,
      NULL,
      HANDY_LCD_GHOSTING_INFO_0_PL,
      NULL,
      NULL,
      {
         { "disabled", NULL },
         { "2frames",  OPTION_VAL_2FRAMES_PL },
         { "3frames",  OPTION_VAL_3FRAMES_PL },
         { "4frames",  OPTION_VAL_4FRAMES_PL },
         { NULL, NULL },
      },
      "disabled"
   },
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

#define HANDY_REFRESH_RATE_LABEL_PT_BR NULL
#define HANDY_REFRESH_RATE_INFO_0_PT_BR NULL
#define OPTION_VAL_50_PT_BR NULL
#define OPTION_VAL_60_PT_BR NULL
#define OPTION_VAL_75_PT_BR NULL
#define OPTION_VAL_100_PT_BR NULL
#define OPTION_VAL_120_PT_BR NULL
#define HANDY_ROT_LABEL_PT_BR "Rotação de tela"
#define HANDY_ROT_INFO_0_PT_BR "Gire a tela do console virtual para alcançar o formato correto de jogos com orientação de 'retrato' para uma exibição convencional (modo retrato)."
#define OPTION_VAL_270_PT_BR "Sentido horário"
#define OPTION_VAL_90_PT_BR "Sentido anti-horário"
#define HANDY_GFX_COLORS_LABEL_PT_BR "Profundidade de cor (requer reinício)"
#define HANDY_GFX_COLORS_INFO_0_PT_BR "Determina a quantidade de cores que será exibida na tela. 24 bits aumentam significativamente a sobrecarga do desempenho e não estão disponíveis em todas as plataformas."
#define OPTION_VAL_16BIT_PT_BR "Milhares (16 bits)"
#define OPTION_VAL_24BIT_PT_BR "Milhões (24 bits)"
#define HANDY_LCD_GHOSTING_LABEL_PT_BR "Filtro fantasma LCD"
#define HANDY_LCD_GHOSTING_INFO_0_PT_BR NULL
#define OPTION_VAL_2FRAMES_PT_BR NULL
#define OPTION_VAL_3FRAMES_PT_BR NULL
#define OPTION_VAL_4FRAMES_PT_BR NULL
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
      "handy_refresh_rate",
      HANDY_REFRESH_RATE_LABEL_PT_BR,
      NULL,
      HANDY_REFRESH_RATE_INFO_0_PT_BR,
      NULL,
      NULL,
      {
         { "50",  OPTION_VAL_50_PT_BR },
         { "60",  OPTION_VAL_60_PT_BR },
         { "75",  OPTION_VAL_75_PT_BR },
         { "100", OPTION_VAL_100_PT_BR },
         { "120", OPTION_VAL_120_PT_BR },
         { NULL, NULL },
      },
      "60"
   },
   {
      "handy_rot",
      HANDY_ROT_LABEL_PT_BR,
      NULL,
      HANDY_ROT_INFO_0_PT_BR,
      NULL,
      NULL,
      {
         { "None", "disabled" },
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
      "handy_lcd_ghosting",
      HANDY_LCD_GHOSTING_LABEL_PT_BR,
      NULL,
      HANDY_LCD_GHOSTING_INFO_0_PT_BR,
      NULL,
      NULL,
      {
         { "disabled", NULL },
         { "2frames",  OPTION_VAL_2FRAMES_PT_BR },
         { "3frames",  OPTION_VAL_3FRAMES_PT_BR },
         { "4frames",  OPTION_VAL_4FRAMES_PT_BR },
         { NULL, NULL },
      },
      "disabled"
   },
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

#define HANDY_REFRESH_RATE_LABEL_PT_PT NULL
#define HANDY_REFRESH_RATE_INFO_0_PT_PT NULL
#define OPTION_VAL_50_PT_PT NULL
#define OPTION_VAL_60_PT_PT NULL
#define OPTION_VAL_75_PT_PT NULL
#define OPTION_VAL_100_PT_PT NULL
#define OPTION_VAL_120_PT_PT NULL
#define HANDY_ROT_LABEL_PT_PT NULL
#define HANDY_ROT_INFO_0_PT_PT NULL
#define OPTION_VAL_270_PT_PT NULL
#define OPTION_VAL_90_PT_PT NULL
#define HANDY_GFX_COLORS_LABEL_PT_PT NULL
#define HANDY_GFX_COLORS_INFO_0_PT_PT NULL
#define OPTION_VAL_16BIT_PT_PT NULL
#define OPTION_VAL_24BIT_PT_PT NULL
#define HANDY_LCD_GHOSTING_LABEL_PT_PT NULL
#define HANDY_LCD_GHOSTING_INFO_0_PT_PT NULL
#define OPTION_VAL_2FRAMES_PT_PT NULL
#define OPTION_VAL_3FRAMES_PT_PT NULL
#define OPTION_VAL_4FRAMES_PT_PT NULL
#define HANDY_FRAMESKIP_LABEL_PT_PT NULL
#define HANDY_FRAMESKIP_INFO_0_PT_PT NULL
#define OPTION_VAL_AUTO_PT_PT "Automático"
#define OPTION_VAL_MANUAL_PT_PT NULL
#define HANDY_FRAMESKIP_THRESHOLD_LABEL_PT_PT NULL
#define HANDY_FRAMESKIP_THRESHOLD_INFO_0_PT_PT NULL

struct retro_core_option_v2_category option_cats_pt_pt[] = {
   { NULL, NULL, NULL },
};
struct retro_core_option_v2_definition option_defs_pt_pt[] = {
   {
      "handy_refresh_rate",
      HANDY_REFRESH_RATE_LABEL_PT_PT,
      NULL,
      HANDY_REFRESH_RATE_INFO_0_PT_PT,
      NULL,
      NULL,
      {
         { "50",  OPTION_VAL_50_PT_PT },
         { "60",  OPTION_VAL_60_PT_PT },
         { "75",  OPTION_VAL_75_PT_PT },
         { "100", OPTION_VAL_100_PT_PT },
         { "120", OPTION_VAL_120_PT_PT },
         { NULL, NULL },
      },
      "60"
   },
   {
      "handy_rot",
      HANDY_ROT_LABEL_PT_PT,
      NULL,
      HANDY_ROT_INFO_0_PT_PT,
      NULL,
      NULL,
      {
         { "None", "disabled" },
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
      "handy_lcd_ghosting",
      HANDY_LCD_GHOSTING_LABEL_PT_PT,
      NULL,
      HANDY_LCD_GHOSTING_INFO_0_PT_PT,
      NULL,
      NULL,
      {
         { "disabled", NULL },
         { "2frames",  OPTION_VAL_2FRAMES_PT_PT },
         { "3frames",  OPTION_VAL_3FRAMES_PT_PT },
         { "4frames",  OPTION_VAL_4FRAMES_PT_PT },
         { NULL, NULL },
      },
      "disabled"
   },
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

#define HANDY_REFRESH_RATE_LABEL_RO NULL
#define HANDY_REFRESH_RATE_INFO_0_RO NULL
#define OPTION_VAL_50_RO NULL
#define OPTION_VAL_60_RO NULL
#define OPTION_VAL_75_RO NULL
#define OPTION_VAL_100_RO NULL
#define OPTION_VAL_120_RO NULL
#define HANDY_ROT_LABEL_RO NULL
#define HANDY_ROT_INFO_0_RO NULL
#define OPTION_VAL_270_RO NULL
#define OPTION_VAL_90_RO NULL
#define HANDY_GFX_COLORS_LABEL_RO NULL
#define HANDY_GFX_COLORS_INFO_0_RO NULL
#define OPTION_VAL_16BIT_RO NULL
#define OPTION_VAL_24BIT_RO NULL
#define HANDY_LCD_GHOSTING_LABEL_RO NULL
#define HANDY_LCD_GHOSTING_INFO_0_RO NULL
#define OPTION_VAL_2FRAMES_RO NULL
#define OPTION_VAL_3FRAMES_RO NULL
#define OPTION_VAL_4FRAMES_RO NULL
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
      "handy_refresh_rate",
      HANDY_REFRESH_RATE_LABEL_RO,
      NULL,
      HANDY_REFRESH_RATE_INFO_0_RO,
      NULL,
      NULL,
      {
         { "50",  OPTION_VAL_50_RO },
         { "60",  OPTION_VAL_60_RO },
         { "75",  OPTION_VAL_75_RO },
         { "100", OPTION_VAL_100_RO },
         { "120", OPTION_VAL_120_RO },
         { NULL, NULL },
      },
      "60"
   },
   {
      "handy_rot",
      HANDY_ROT_LABEL_RO,
      NULL,
      HANDY_ROT_INFO_0_RO,
      NULL,
      NULL,
      {
         { "None", "disabled" },
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
      "handy_lcd_ghosting",
      HANDY_LCD_GHOSTING_LABEL_RO,
      NULL,
      HANDY_LCD_GHOSTING_INFO_0_RO,
      NULL,
      NULL,
      {
         { "disabled", NULL },
         { "2frames",  OPTION_VAL_2FRAMES_RO },
         { "3frames",  OPTION_VAL_3FRAMES_RO },
         { "4frames",  OPTION_VAL_4FRAMES_RO },
         { NULL, NULL },
      },
      "disabled"
   },
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

#define HANDY_REFRESH_RATE_LABEL_RU NULL
#define HANDY_REFRESH_RATE_INFO_0_RU NULL
#define OPTION_VAL_50_RU NULL
#define OPTION_VAL_60_RU NULL
#define OPTION_VAL_75_RU NULL
#define OPTION_VAL_100_RU NULL
#define OPTION_VAL_120_RU NULL
#define HANDY_ROT_LABEL_RU "Вращение экрана"
#define HANDY_ROT_INFO_0_RU "Поворачивает виртуальный экран консоли для правильного расположения портретно-ориентированных игр при использовании ландшафтной ориентации."
#define OPTION_VAL_270_RU "По часовой стрелке"
#define OPTION_VAL_90_RU "Против часовой стрелки"
#define HANDY_GFX_COLORS_LABEL_RU "Глубина цвета (перезапуск)"
#define HANDY_GFX_COLORS_INFO_0_RU "Выбор количества цветов для отображения на экране. 24-битная палитра существенно повышает нагрузку на устройство и недоступна для всех платформ."
#define OPTION_VAL_16BIT_RU "Тысячи (16 бит)"
#define OPTION_VAL_24BIT_RU "Миллионы (24 бита)"
#define HANDY_LCD_GHOSTING_LABEL_RU "Ghosting-фильтр LCD"
#define HANDY_LCD_GHOSTING_INFO_0_RU NULL
#define OPTION_VAL_2FRAMES_RU NULL
#define OPTION_VAL_3FRAMES_RU NULL
#define OPTION_VAL_4FRAMES_RU NULL
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
      "handy_refresh_rate",
      HANDY_REFRESH_RATE_LABEL_RU,
      NULL,
      HANDY_REFRESH_RATE_INFO_0_RU,
      NULL,
      NULL,
      {
         { "50",  OPTION_VAL_50_RU },
         { "60",  OPTION_VAL_60_RU },
         { "75",  OPTION_VAL_75_RU },
         { "100", OPTION_VAL_100_RU },
         { "120", OPTION_VAL_120_RU },
         { NULL, NULL },
      },
      "60"
   },
   {
      "handy_rot",
      HANDY_ROT_LABEL_RU,
      NULL,
      HANDY_ROT_INFO_0_RU,
      NULL,
      NULL,
      {
         { "None", "disabled" },
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
      "handy_lcd_ghosting",
      HANDY_LCD_GHOSTING_LABEL_RU,
      NULL,
      HANDY_LCD_GHOSTING_INFO_0_RU,
      NULL,
      NULL,
      {
         { "disabled", NULL },
         { "2frames",  OPTION_VAL_2FRAMES_RU },
         { "3frames",  OPTION_VAL_3FRAMES_RU },
         { "4frames",  OPTION_VAL_4FRAMES_RU },
         { NULL, NULL },
      },
      "disabled"
   },
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

#define HANDY_REFRESH_RATE_LABEL_SI NULL
#define HANDY_REFRESH_RATE_INFO_0_SI NULL
#define OPTION_VAL_50_SI NULL
#define OPTION_VAL_60_SI NULL
#define OPTION_VAL_75_SI NULL
#define OPTION_VAL_100_SI NULL
#define OPTION_VAL_120_SI NULL
#define HANDY_ROT_LABEL_SI NULL
#define HANDY_ROT_INFO_0_SI NULL
#define OPTION_VAL_270_SI NULL
#define OPTION_VAL_90_SI NULL
#define HANDY_GFX_COLORS_LABEL_SI NULL
#define HANDY_GFX_COLORS_INFO_0_SI NULL
#define OPTION_VAL_16BIT_SI NULL
#define OPTION_VAL_24BIT_SI NULL
#define HANDY_LCD_GHOSTING_LABEL_SI NULL
#define HANDY_LCD_GHOSTING_INFO_0_SI NULL
#define OPTION_VAL_2FRAMES_SI NULL
#define OPTION_VAL_3FRAMES_SI NULL
#define OPTION_VAL_4FRAMES_SI NULL
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
      "handy_refresh_rate",
      HANDY_REFRESH_RATE_LABEL_SI,
      NULL,
      HANDY_REFRESH_RATE_INFO_0_SI,
      NULL,
      NULL,
      {
         { "50",  OPTION_VAL_50_SI },
         { "60",  OPTION_VAL_60_SI },
         { "75",  OPTION_VAL_75_SI },
         { "100", OPTION_VAL_100_SI },
         { "120", OPTION_VAL_120_SI },
         { NULL, NULL },
      },
      "60"
   },
   {
      "handy_rot",
      HANDY_ROT_LABEL_SI,
      NULL,
      HANDY_ROT_INFO_0_SI,
      NULL,
      NULL,
      {
         { "None", "disabled" },
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
      "handy_lcd_ghosting",
      HANDY_LCD_GHOSTING_LABEL_SI,
      NULL,
      HANDY_LCD_GHOSTING_INFO_0_SI,
      NULL,
      NULL,
      {
         { "disabled", NULL },
         { "2frames",  OPTION_VAL_2FRAMES_SI },
         { "3frames",  OPTION_VAL_3FRAMES_SI },
         { "4frames",  OPTION_VAL_4FRAMES_SI },
         { NULL, NULL },
      },
      "disabled"
   },
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

#define HANDY_REFRESH_RATE_LABEL_SK NULL
#define HANDY_REFRESH_RATE_INFO_0_SK NULL
#define OPTION_VAL_50_SK NULL
#define OPTION_VAL_60_SK NULL
#define OPTION_VAL_75_SK NULL
#define OPTION_VAL_100_SK NULL
#define OPTION_VAL_120_SK NULL
#define HANDY_ROT_LABEL_SK "Rotácia displeja"
#define HANDY_ROT_INFO_0_SK "Otočiť virtuálnu obrazovku konzoly a dosiahnuť tak správne rozloženie hier orientovaných na výšku na bežnej obrazovke orientovanej na šírku."
#define OPTION_VAL_270_SK NULL
#define OPTION_VAL_90_SK NULL
#define HANDY_GFX_COLORS_LABEL_SK NULL
#define HANDY_GFX_COLORS_INFO_0_SK "Zvoliť farebnú hĺbku. 24 bitov značne zvýši výkonnostné réžie a nie je dostupná na všetky platformách."
#define OPTION_VAL_16BIT_SK NULL
#define OPTION_VAL_24BIT_SK NULL
#define HANDY_LCD_GHOSTING_LABEL_SK NULL
#define HANDY_LCD_GHOSTING_INFO_0_SK NULL
#define OPTION_VAL_2FRAMES_SK NULL
#define OPTION_VAL_3FRAMES_SK NULL
#define OPTION_VAL_4FRAMES_SK NULL
#define HANDY_FRAMESKIP_LABEL_SK "Preskočenie snímky"
#define HANDY_FRAMESKIP_INFO_0_SK NULL
#define OPTION_VAL_AUTO_SK NULL
#define OPTION_VAL_MANUAL_SK "Ručne"
#define HANDY_FRAMESKIP_THRESHOLD_LABEL_SK "Prah preskočenia snímky (%)"
#define HANDY_FRAMESKIP_THRESHOLD_INFO_0_SK "Ak je 'Preskočenie snímkov' nastavené na 'Ručne', určuje obsadenosť zvukového zásobníka (v percentách) pod ktorou budú snímky preskočené. Vyššie hodnoty znižujú riziko praskania za cenu zahodenia snímkov častejšie."

struct retro_core_option_v2_category option_cats_sk[] = {
   { NULL, NULL, NULL },
};
struct retro_core_option_v2_definition option_defs_sk[] = {
   {
      "handy_refresh_rate",
      HANDY_REFRESH_RATE_LABEL_SK,
      NULL,
      HANDY_REFRESH_RATE_INFO_0_SK,
      NULL,
      NULL,
      {
         { "50",  OPTION_VAL_50_SK },
         { "60",  OPTION_VAL_60_SK },
         { "75",  OPTION_VAL_75_SK },
         { "100", OPTION_VAL_100_SK },
         { "120", OPTION_VAL_120_SK },
         { NULL, NULL },
      },
      "60"
   },
   {
      "handy_rot",
      HANDY_ROT_LABEL_SK,
      NULL,
      HANDY_ROT_INFO_0_SK,
      NULL,
      NULL,
      {
         { "None", "disabled" },
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
      "handy_lcd_ghosting",
      HANDY_LCD_GHOSTING_LABEL_SK,
      NULL,
      HANDY_LCD_GHOSTING_INFO_0_SK,
      NULL,
      NULL,
      {
         { "disabled", NULL },
         { "2frames",  OPTION_VAL_2FRAMES_SK },
         { "3frames",  OPTION_VAL_3FRAMES_SK },
         { "4frames",  OPTION_VAL_4FRAMES_SK },
         { NULL, NULL },
      },
      "disabled"
   },
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

#define HANDY_REFRESH_RATE_LABEL_SR NULL
#define HANDY_REFRESH_RATE_INFO_0_SR NULL
#define OPTION_VAL_50_SR NULL
#define OPTION_VAL_60_SR NULL
#define OPTION_VAL_75_SR NULL
#define OPTION_VAL_100_SR NULL
#define OPTION_VAL_120_SR NULL
#define HANDY_ROT_LABEL_SR NULL
#define HANDY_ROT_INFO_0_SR NULL
#define OPTION_VAL_270_SR NULL
#define OPTION_VAL_90_SR NULL
#define HANDY_GFX_COLORS_LABEL_SR NULL
#define HANDY_GFX_COLORS_INFO_0_SR NULL
#define OPTION_VAL_16BIT_SR NULL
#define OPTION_VAL_24BIT_SR NULL
#define HANDY_LCD_GHOSTING_LABEL_SR NULL
#define HANDY_LCD_GHOSTING_INFO_0_SR NULL
#define OPTION_VAL_2FRAMES_SR NULL
#define OPTION_VAL_3FRAMES_SR NULL
#define OPTION_VAL_4FRAMES_SR NULL
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
      "handy_refresh_rate",
      HANDY_REFRESH_RATE_LABEL_SR,
      NULL,
      HANDY_REFRESH_RATE_INFO_0_SR,
      NULL,
      NULL,
      {
         { "50",  OPTION_VAL_50_SR },
         { "60",  OPTION_VAL_60_SR },
         { "75",  OPTION_VAL_75_SR },
         { "100", OPTION_VAL_100_SR },
         { "120", OPTION_VAL_120_SR },
         { NULL, NULL },
      },
      "60"
   },
   {
      "handy_rot",
      HANDY_ROT_LABEL_SR,
      NULL,
      HANDY_ROT_INFO_0_SR,
      NULL,
      NULL,
      {
         { "None", "disabled" },
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
      "handy_lcd_ghosting",
      HANDY_LCD_GHOSTING_LABEL_SR,
      NULL,
      HANDY_LCD_GHOSTING_INFO_0_SR,
      NULL,
      NULL,
      {
         { "disabled", NULL },
         { "2frames",  OPTION_VAL_2FRAMES_SR },
         { "3frames",  OPTION_VAL_3FRAMES_SR },
         { "4frames",  OPTION_VAL_4FRAMES_SR },
         { NULL, NULL },
      },
      "disabled"
   },
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

#define HANDY_REFRESH_RATE_LABEL_SV NULL
#define HANDY_REFRESH_RATE_INFO_0_SV NULL
#define OPTION_VAL_50_SV NULL
#define OPTION_VAL_60_SV NULL
#define OPTION_VAL_75_SV NULL
#define OPTION_VAL_100_SV NULL
#define OPTION_VAL_120_SV NULL
#define HANDY_ROT_LABEL_SV NULL
#define HANDY_ROT_INFO_0_SV "Rotera den virtuella konsolskärmen för att uppnå rätt layout av \"porträtt\" orienterade spel på en konventionell (landskap) skärm."
#define OPTION_VAL_270_SV "Medurs"
#define OPTION_VAL_90_SV NULL
#define HANDY_GFX_COLORS_LABEL_SV NULL
#define HANDY_GFX_COLORS_INFO_0_SV "Ange antal färger att visa på skärmen. 24-bitars ökar prestandakraven och finns inte på alla plattformar."
#define OPTION_VAL_16BIT_SV NULL
#define OPTION_VAL_24BIT_SV NULL
#define HANDY_LCD_GHOSTING_LABEL_SV NULL
#define HANDY_LCD_GHOSTING_INFO_0_SV NULL
#define OPTION_VAL_2FRAMES_SV NULL
#define OPTION_VAL_3FRAMES_SV NULL
#define OPTION_VAL_4FRAMES_SV NULL
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
      "handy_refresh_rate",
      HANDY_REFRESH_RATE_LABEL_SV,
      NULL,
      HANDY_REFRESH_RATE_INFO_0_SV,
      NULL,
      NULL,
      {
         { "50",  OPTION_VAL_50_SV },
         { "60",  OPTION_VAL_60_SV },
         { "75",  OPTION_VAL_75_SV },
         { "100", OPTION_VAL_100_SV },
         { "120", OPTION_VAL_120_SV },
         { NULL, NULL },
      },
      "60"
   },
   {
      "handy_rot",
      HANDY_ROT_LABEL_SV,
      NULL,
      HANDY_ROT_INFO_0_SV,
      NULL,
      NULL,
      {
         { "None", "disabled" },
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
      "handy_lcd_ghosting",
      HANDY_LCD_GHOSTING_LABEL_SV,
      NULL,
      HANDY_LCD_GHOSTING_INFO_0_SV,
      NULL,
      NULL,
      {
         { "disabled", NULL },
         { "2frames",  OPTION_VAL_2FRAMES_SV },
         { "3frames",  OPTION_VAL_3FRAMES_SV },
         { "4frames",  OPTION_VAL_4FRAMES_SV },
         { NULL, NULL },
      },
      "disabled"
   },
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

#define HANDY_REFRESH_RATE_LABEL_TR NULL
#define HANDY_REFRESH_RATE_INFO_0_TR NULL
#define OPTION_VAL_50_TR NULL
#define OPTION_VAL_60_TR NULL
#define OPTION_VAL_75_TR NULL
#define OPTION_VAL_100_TR NULL
#define OPTION_VAL_120_TR NULL
#define HANDY_ROT_LABEL_TR "Ekran Döndürme"
#define HANDY_ROT_INFO_0_TR "Geleneksel (yatay) bir ekranda 'portre' odaklı oyunların doğru düzenini elde etmek için sanal konsol ekranını döndürün."
#define OPTION_VAL_270_TR "Saat yönünde"
#define OPTION_VAL_90_TR "Saat yönünün tersi"
#define HANDY_GFX_COLORS_LABEL_TR "Renk Derinliği (Yeniden Başlatılmalı)"
#define HANDY_GFX_COLORS_INFO_0_TR "Ekranda görüntülenecek renk sayısını belirtin. 24 bit, genel performansı önemli ölçüde artırır ve tüm platformlarda kullanılamaz."
#define OPTION_VAL_16BIT_TR "Binlerce (16-bit)"
#define OPTION_VAL_24BIT_TR "Milyonlarca (24-bit)"
#define HANDY_LCD_GHOSTING_LABEL_TR "LCD Gölgelenme Filtresi"
#define HANDY_LCD_GHOSTING_INFO_0_TR NULL
#define OPTION_VAL_2FRAMES_TR NULL
#define OPTION_VAL_3FRAMES_TR NULL
#define OPTION_VAL_4FRAMES_TR NULL
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
      "handy_refresh_rate",
      HANDY_REFRESH_RATE_LABEL_TR,
      NULL,
      HANDY_REFRESH_RATE_INFO_0_TR,
      NULL,
      NULL,
      {
         { "50",  OPTION_VAL_50_TR },
         { "60",  OPTION_VAL_60_TR },
         { "75",  OPTION_VAL_75_TR },
         { "100", OPTION_VAL_100_TR },
         { "120", OPTION_VAL_120_TR },
         { NULL, NULL },
      },
      "60"
   },
   {
      "handy_rot",
      HANDY_ROT_LABEL_TR,
      NULL,
      HANDY_ROT_INFO_0_TR,
      NULL,
      NULL,
      {
         { "None", "disabled" },
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
      "handy_lcd_ghosting",
      HANDY_LCD_GHOSTING_LABEL_TR,
      NULL,
      HANDY_LCD_GHOSTING_INFO_0_TR,
      NULL,
      NULL,
      {
         { "disabled", NULL },
         { "2frames",  OPTION_VAL_2FRAMES_TR },
         { "3frames",  OPTION_VAL_3FRAMES_TR },
         { "4frames",  OPTION_VAL_4FRAMES_TR },
         { NULL, NULL },
      },
      "disabled"
   },
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

#define HANDY_REFRESH_RATE_LABEL_UK NULL
#define HANDY_REFRESH_RATE_INFO_0_UK NULL
#define OPTION_VAL_50_UK NULL
#define OPTION_VAL_60_UK NULL
#define OPTION_VAL_75_UK NULL
#define OPTION_VAL_100_UK NULL
#define OPTION_VAL_120_UK NULL
#define HANDY_ROT_LABEL_UK "Обертання екрану"
#define HANDY_ROT_INFO_0_UK "Повертає екран віртуальної консолі, для вірного відображення портретно-орієнтованих ігор на дисплеї з альбомною орієнтацією."
#define OPTION_VAL_270_UK "За годин. стрілкою"
#define OPTION_VAL_90_UK "Проти годин. стрілки"
#define HANDY_GFX_COLORS_LABEL_UK "Глибина кольору (потрібен перезапуск)"
#define HANDY_GFX_COLORS_INFO_0_UK "Вказує кількість кольорів, які будуть відображатись на екрані. 24-бітна палітра суттєво впливає на продуктивність та доступна не на всіх платформах."
#define OPTION_VAL_16BIT_UK NULL
#define OPTION_VAL_24BIT_UK NULL
#define HANDY_LCD_GHOSTING_LABEL_UK NULL
#define HANDY_LCD_GHOSTING_INFO_0_UK NULL
#define OPTION_VAL_2FRAMES_UK NULL
#define OPTION_VAL_3FRAMES_UK NULL
#define OPTION_VAL_4FRAMES_UK NULL
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
      "handy_refresh_rate",
      HANDY_REFRESH_RATE_LABEL_UK,
      NULL,
      HANDY_REFRESH_RATE_INFO_0_UK,
      NULL,
      NULL,
      {
         { "50",  OPTION_VAL_50_UK },
         { "60",  OPTION_VAL_60_UK },
         { "75",  OPTION_VAL_75_UK },
         { "100", OPTION_VAL_100_UK },
         { "120", OPTION_VAL_120_UK },
         { NULL, NULL },
      },
      "60"
   },
   {
      "handy_rot",
      HANDY_ROT_LABEL_UK,
      NULL,
      HANDY_ROT_INFO_0_UK,
      NULL,
      NULL,
      {
         { "None", "disabled" },
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
      "handy_lcd_ghosting",
      HANDY_LCD_GHOSTING_LABEL_UK,
      NULL,
      HANDY_LCD_GHOSTING_INFO_0_UK,
      NULL,
      NULL,
      {
         { "disabled", NULL },
         { "2frames",  OPTION_VAL_2FRAMES_UK },
         { "3frames",  OPTION_VAL_3FRAMES_UK },
         { "4frames",  OPTION_VAL_4FRAMES_UK },
         { NULL, NULL },
      },
      "disabled"
   },
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

/* RETRO_LANGUAGE_VAL */

#define HANDY_REFRESH_RATE_LABEL_VAL NULL
#define HANDY_REFRESH_RATE_INFO_0_VAL NULL
#define OPTION_VAL_50_VAL NULL
#define OPTION_VAL_60_VAL NULL
#define OPTION_VAL_75_VAL NULL
#define OPTION_VAL_100_VAL NULL
#define OPTION_VAL_120_VAL NULL
#define HANDY_ROT_LABEL_VAL NULL
#define HANDY_ROT_INFO_0_VAL NULL
#define OPTION_VAL_270_VAL NULL
#define OPTION_VAL_90_VAL NULL
#define HANDY_GFX_COLORS_LABEL_VAL NULL
#define HANDY_GFX_COLORS_INFO_0_VAL NULL
#define OPTION_VAL_16BIT_VAL NULL
#define OPTION_VAL_24BIT_VAL NULL
#define HANDY_LCD_GHOSTING_LABEL_VAL NULL
#define HANDY_LCD_GHOSTING_INFO_0_VAL NULL
#define OPTION_VAL_2FRAMES_VAL NULL
#define OPTION_VAL_3FRAMES_VAL NULL
#define OPTION_VAL_4FRAMES_VAL NULL
#define HANDY_FRAMESKIP_LABEL_VAL NULL
#define HANDY_FRAMESKIP_INFO_0_VAL NULL
#define OPTION_VAL_AUTO_VAL "Selecció automàtica"
#define OPTION_VAL_MANUAL_VAL "Selecció manual"
#define HANDY_FRAMESKIP_THRESHOLD_LABEL_VAL NULL
#define HANDY_FRAMESKIP_THRESHOLD_INFO_0_VAL NULL

struct retro_core_option_v2_category option_cats_val[] = {
   { NULL, NULL, NULL },
};
struct retro_core_option_v2_definition option_defs_val[] = {
   {
      "handy_refresh_rate",
      HANDY_REFRESH_RATE_LABEL_VAL,
      NULL,
      HANDY_REFRESH_RATE_INFO_0_VAL,
      NULL,
      NULL,
      {
         { "50",  OPTION_VAL_50_VAL },
         { "60",  OPTION_VAL_60_VAL },
         { "75",  OPTION_VAL_75_VAL },
         { "100", OPTION_VAL_100_VAL },
         { "120", OPTION_VAL_120_VAL },
         { NULL, NULL },
      },
      "60"
   },
   {
      "handy_rot",
      HANDY_ROT_LABEL_VAL,
      NULL,
      HANDY_ROT_INFO_0_VAL,
      NULL,
      NULL,
      {
         { "None", "disabled" },
         { "270",  OPTION_VAL_270_VAL },
         { "90",   OPTION_VAL_90_VAL },
         { NULL, NULL },
      },
      "None"
   },
#if defined(FRONTEND_SUPPORTS_XRGB8888)
   {
      "handy_gfx_colors",
      HANDY_GFX_COLORS_LABEL_VAL,
      NULL,
      HANDY_GFX_COLORS_INFO_0_VAL,
      NULL,
      NULL,
      {
         { "16bit", OPTION_VAL_16BIT_VAL },
         { "24bit", OPTION_VAL_24BIT_VAL },
         { NULL,    NULL },
      },
      "16bit"
   },
#endif
   {
      "handy_lcd_ghosting",
      HANDY_LCD_GHOSTING_LABEL_VAL,
      NULL,
      HANDY_LCD_GHOSTING_INFO_0_VAL,
      NULL,
      NULL,
      {
         { "disabled", NULL },
         { "2frames",  OPTION_VAL_2FRAMES_VAL },
         { "3frames",  OPTION_VAL_3FRAMES_VAL },
         { "4frames",  OPTION_VAL_4FRAMES_VAL },
         { NULL, NULL },
      },
      "disabled"
   },
   {
      "handy_frameskip",
      HANDY_FRAMESKIP_LABEL_VAL,
      NULL,
      HANDY_FRAMESKIP_INFO_0_VAL,
      NULL,
      NULL,
      {
         { "disabled", NULL },
         { "auto",     OPTION_VAL_AUTO_VAL },
         { "manual",   OPTION_VAL_MANUAL_VAL },
         { NULL, NULL },
      },
      "disabled"
   },
   {
      "handy_frameskip_threshold",
      HANDY_FRAMESKIP_THRESHOLD_LABEL_VAL,
      NULL,
      HANDY_FRAMESKIP_THRESHOLD_INFO_0_VAL,
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
struct retro_core_options_v2 options_val = {
   option_cats_val,
   option_defs_val
};

/* RETRO_LANGUAGE_VN */

#define HANDY_REFRESH_RATE_LABEL_VN NULL
#define HANDY_REFRESH_RATE_INFO_0_VN NULL
#define OPTION_VAL_50_VN NULL
#define OPTION_VAL_60_VN NULL
#define OPTION_VAL_75_VN NULL
#define OPTION_VAL_100_VN NULL
#define OPTION_VAL_120_VN NULL
#define HANDY_ROT_LABEL_VN NULL
#define HANDY_ROT_INFO_0_VN "Xoay màn hình để hiển thị chính xác trò chơi màn hình dọc ở chế độ hiển thị thông thường (ngang)."
#define OPTION_VAL_270_VN NULL
#define OPTION_VAL_90_VN NULL
#define HANDY_GFX_COLORS_LABEL_VN NULL
#define HANDY_GFX_COLORS_INFO_0_VN "Chọn chế độ hiển thị màu trên màn hình. 24-bit làm tăng đáng kể hiệu suất và không hẳn có sẵn trên mọi nền tảng."
#define OPTION_VAL_16BIT_VN NULL
#define OPTION_VAL_24BIT_VN NULL
#define HANDY_LCD_GHOSTING_LABEL_VN NULL
#define HANDY_LCD_GHOSTING_INFO_0_VN NULL
#define OPTION_VAL_2FRAMES_VN NULL
#define OPTION_VAL_3FRAMES_VN NULL
#define OPTION_VAL_4FRAMES_VN NULL
#define HANDY_FRAMESKIP_LABEL_VN "Bỏ qua khung hình"
#define HANDY_FRAMESKIP_INFO_0_VN "Bỏ qua khung hình để tránh bộ đệm âm thanh chạy dưới mức (tiếng kêu lách tách). Cải thiện hiệu suất với độ mượt mà của hình ảnh. 'Tự động' bỏ qua khung khi giao diện người dùng thông báo. 'Thủ công' sử dụng cài đặt 'Ngưỡng khung hình (%)'."
#define OPTION_VAL_AUTO_VN "Tự động"
#define OPTION_VAL_MANUAL_VN "Thủ công"
#define HANDY_FRAMESKIP_THRESHOLD_LABEL_VN "Ngưỡng bỏ qua khung hình (%)"
#define HANDY_FRAMESKIP_THRESHOLD_INFO_0_VN "Khi 'Frameskip' được đặt thành 'Thủ công', chỉ định ngưỡng chiếm dụng bộ đệm âm thanh (tỷ lệ phần trăm) dưới khung hình nào sẽ bị bỏ qua. Giá trị cao hơn làm giảm nguy cơ giật lag do làm rơi khung thường xuyên hơn."

struct retro_core_option_v2_category option_cats_vn[] = {
   { NULL, NULL, NULL },
};
struct retro_core_option_v2_definition option_defs_vn[] = {
   {
      "handy_refresh_rate",
      HANDY_REFRESH_RATE_LABEL_VN,
      NULL,
      HANDY_REFRESH_RATE_INFO_0_VN,
      NULL,
      NULL,
      {
         { "50",  OPTION_VAL_50_VN },
         { "60",  OPTION_VAL_60_VN },
         { "75",  OPTION_VAL_75_VN },
         { "100", OPTION_VAL_100_VN },
         { "120", OPTION_VAL_120_VN },
         { NULL, NULL },
      },
      "60"
   },
   {
      "handy_rot",
      HANDY_ROT_LABEL_VN,
      NULL,
      HANDY_ROT_INFO_0_VN,
      NULL,
      NULL,
      {
         { "None", "disabled" },
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
      "handy_lcd_ghosting",
      HANDY_LCD_GHOSTING_LABEL_VN,
      NULL,
      HANDY_LCD_GHOSTING_INFO_0_VN,
      NULL,
      NULL,
      {
         { "disabled", NULL },
         { "2frames",  OPTION_VAL_2FRAMES_VN },
         { "3frames",  OPTION_VAL_3FRAMES_VN },
         { "4frames",  OPTION_VAL_4FRAMES_VN },
         { NULL, NULL },
      },
      "disabled"
   },
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