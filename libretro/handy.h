#include <stdlib.h>
#include <stdio.h>

#include "system.h"
#include "lynxdef.h"

#define HANDYVER    "0.95"
#define ROM_FILE    "lynxboot.img"

#if defined(_WIN32)
#define SLASH_STR  '\\'
#else
#define SLASH_STR  '/'
#endif
