//
// Copyright (c) 2004 K. Wilkins
//
// This software is provided 'as-is', without any express or implied warranty.
// In no event will the authors be held liable for any damages arising from
// the use of this software.
//
// Permission is granted to anyone to use this software for any purpose,
// including commercial applications, and to alter it and redistribute it
// freely, subject to the following restrictions:
//
// 1. The origin of this software must not be misrepresented; you must not
//    claim that you wrote the original software. If you use this software
//    in a product, an acknowledgment in the product documentation would be
//    appreciated but is not required.
//
// 2. Altered source versions must be plainly marked as such, and must not
//    be misrepresented as being the original software.
//
// 3. This notice may not be removed or altered from any source distribution.
//

//////////////////////////////////////////////////////////////////////////////
//                       Handy - An Atari Lynx Emulator                     //
//                          Copyright (c) 1996,1997                         //
//                                 K. Wilkins                               //
//////////////////////////////////////////////////////////////////////////////
// ROM emulation class                                                      //
//////////////////////////////////////////////////////////////////////////////
//                                                                          //
// This class emulates the system ROM (512B), the interface is pretty       //
// simple: constructor, reset, peek, poke.                                  //
//                                                                          //
//    K. Wilkins                                                            //
// August 1997                                                              //
//                                                                          //
//////////////////////////////////////////////////////////////////////////////
// Revision History:                                                        //
// -----------------                                                        //
//                                                                          //
// 01Aug1997 KW Document header added & class documented.                   //
//                                                                          //
//////////////////////////////////////////////////////////////////////////////

#define ROM_CPP

#include <stdlib.h>
#include <string.h>
#include "system.h"
#include "scrc32.h"
#include <string/stdstring.h>
#include <streams/file_stream.h>
#include "rom.h"
#include "handy.h"

static void initialise_rom_data(UBYTE *rom_data)
{
   unsigned i;

   // Initialise ROM
   for(i = 0; i < ROM_SIZE; i++)
      rom_data[i] = DEFAULT_ROM_CONTENTS;

   // actually not part of Boot ROM but uninitialized otherwise
   // Reset Vector etc
   rom_data[0x1F8] = 0x00;
   rom_data[0x1F9] = 0x80;
   rom_data[0x1FA] = 0x00;
   rom_data[0x1FB] = 0x30;
   rom_data[0x1FC] = 0x80;
   rom_data[0x1FD] = 0xFF;
   rom_data[0x1FE] = 0x80;
   rom_data[0x1FF] = 0xFF;
}

CRom::CRom(const char *romfile, bool useEmu)
{
   ULONG crc    = 0;
   mWriteEnable = FALSE;
   mValid       = TRUE;
   Reset();

   initialise_rom_data(mRomData);

   if (useEmu)
      mValid = FALSE;
   else
   {
      RFILE *fp = NULL;

      /* Load up the file */
      if (!string_is_empty(romfile))
         fp = filestream_open(romfile, RETRO_VFS_FILE_ACCESS_READ,
               RETRO_VFS_FILE_ACCESS_HINT_NONE);

      if (fp)
      {
         /* Read in the 512 bytes */
         if (filestream_read(fp, mRomData, ROM_SIZE) != ROM_SIZE)
            mValid = FALSE;

         filestream_close(fp);
      }
      else
         mValid = FALSE;

      /* Check the code that has been loaded and report an error if its a
       * fake version (from handy distribution) of the bootrom */
      crc = crc32(crc, mRomData, ROM_SIZE);

      if (crc != ROM_CRC32)
      {
         handy_log(RETRO_LOG_ERROR,
               "Invalid BIOS detected - CRC: 0x%08x (expected 0x%08x)\n", crc, ROM_CRC32);
         mValid = FALSE;
      }

      /* If we failed to load the correct bios,
       * reset the rom data to the default */
      if (!mValid)
      {
         handy_log(RETRO_LOG_ERROR,
               "Failed to load BIOS - Using internal fallback...\n", crc, ROM_CRC32);
         initialise_rom_data(mRomData);
      }
      else
         handy_log(RETRO_LOG_INFO, "BIOS loaded: %s\n", romfile);
   }
}

// Nothing to do here
void CRom::Reset(void) { }

bool CRom::ContextLoad(LSS_FILE *fp)
{
   char teststr[100]="XXXXXXXXXXXXXXXXX";
   if(!lss_read(teststr,sizeof(char),17,fp))
      return 0;
   if(strcmp(teststr,"CRom::ContextSave")!=0)
      return 0;
   if(!lss_read(mRomData,sizeof(UBYTE),ROM_SIZE,fp))
      return 0;
   return 1;
}


//END OF FILE
