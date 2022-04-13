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
// System object class                                                      //
//////////////////////////////////////////////////////////////////////////////
//                                                                          //
// This class provides the glue to bind of of the emulation objects         //
// together via peek/poke handlers and pass thru interfaces to lower        //
// objects, all control of the emulator is done via this class. Update()    //
// does most of the work and each call emulates one CPU instruction and     //
// updates all of the relevant hardware if required. It must be remembered  //
// that if that instruction involves setting SPRGO then, it will cause a    //
// sprite painting operation and then a corresponding update of all of the  //
// hardware which will usually involve recursive calls to Update, see       //
// Mikey SPRGO code for more details.                                       //
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

#define SYSTEM_CPP

#include <stdlib.h>
#include <string.h>

#include <string/stdstring.h>
#include <file/file_path.h>
#include <streams/file_stream.h>

#include "system.h"
#include "handy.h"

extern void lynx_decrypt(unsigned char * result, const unsigned char * encrypted, const int length);

int lss_read(void* dest, int varsize, int varcount, LSS_FILE *fp)
{
   ULONG copysize=varsize*varcount;
   if((fp->index + copysize) > fp->index_limit)
      copysize=fp->index_limit - fp->index;
   memcpy(dest,fp->memptr+fp->index,copysize);
   fp->index+=copysize;
   return copysize;
}

int lss_write(void* src, int varsize, int varcount, LSS_FILE *fp)
{
   ULONG copysize=varsize*varcount;
   memcpy(fp->memptr+fp->index,src,copysize);
   fp->index+=copysize;
   return copysize;
}

int lss_printf(LSS_FILE *fp, const char *str)
{
   ULONG copysize=strlen(str);
   memcpy(fp->memptr+fp->index,str,copysize);
   fp->index+=copysize;
   return copysize;
}

CSystem::CSystem(const char *gamefile,
                 const UBYTE *gamedata,
                 ULONG gamesize,
                 const char *romfile,
                 bool useEmu,
                 const char *eepromfile)
 : mCart(NULL),
   mRom(NULL),
   mMemMap(NULL),
   mRam(NULL),
   mCpu(NULL),
   mMikie(NULL),
   mSusie(NULL),
   mEEPROM(NULL)
{
   const UBYTE *game_memory = NULL;
   UBYTE *game_memory_buf   = NULL;
   ULONG game_memory_size   = 0;
   UBYTE *howard_memory     = NULL;
   ULONG howard_memory_size = 0;

   // Select the default filetype
   mFileType=HANDY_FILETYPE_ILLEGAL;

   // Check whether a data buffer is provided
   if (gamedata && (gamesize != 0)) {
      game_memory      = gamedata;
      game_memory_size = gamesize;
   }
   // Otherwise load data from file
   else if (!string_is_empty(gamefile)) {
      RFILE *fp = NULL;

      // Open the cartridge file for reading
      fp = filestream_open(gamefile, RETRO_VFS_FILE_ACCESS_READ,
            RETRO_VFS_FILE_ACCESS_HINT_NONE);

      if (fp) {
         // How big is the file?
         filestream_seek(fp, 0, RETRO_VFS_SEEK_POSITION_END);
         game_memory_size = filestream_tell(fp);
         filestream_seek(fp, 0, RETRO_VFS_SEEK_POSITION_START);

         game_memory_buf = (UBYTE*) new UBYTE[game_memory_size];

         if (filestream_read(fp, game_memory_buf, game_memory_size) == game_memory_size)
         {
            handy_log(RETRO_LOG_INFO, "Read Cart file: %s\n", gamefile);
            game_memory = game_memory_buf;
         }
         else {
            handy_log(RETRO_LOG_ERROR, "Failed to read Cart file: %s\n", gamefile);
            game_memory_size = 0;
         }

         filestream_close(fp);
      }
      else
         handy_log(RETRO_LOG_ERROR, "Failed to open Cart file: %s\n", gamefile);
   }

   // Try to determine the game (cartridge) type
   if (game_memory && (game_memory_size > 0)) {
      char clip[11];
      memcpy(clip,game_memory,11);
      clip[4]=0;
      clip[10]=0;

      if(!strcmp(&clip[6],"BS93")) mFileType=HANDY_FILETYPE_HOMEBREW;
      else if(!strcmp(&clip[0],"LYNX")) mFileType=HANDY_FILETYPE_LNX;
      else if(!strcmp(&clip[0],LSS_VERSION_OLD)) mFileType=HANDY_FILETYPE_SNAPSHOT;
      else if(game_memory_size==128*1024 || game_memory_size==256*1024 || game_memory_size==512*1024) {
         handy_log(RETRO_LOG_ERROR, "Invalid Cart (type). but 128/256/512k size -> set to RAW and try to load raw rom image\n");
         mFileType=HANDY_FILETYPE_RAW;
      } else {
         handy_log(RETRO_LOG_ERROR, "Invalid Cart (type). -> set to RAW and try to load raw rom image\n");
         mFileType=HANDY_FILETYPE_RAW;
      }
   }

   mCycleCountBreakpoint=0xffffffff;

   // Create the system objects that we'll use

   // Attempt to load the cartridge errors caught above here...

   mRom = new CRom(romfile,useEmu);

   // An exception from this will be caught by the level above
   mEEPROM = new CEEPROM();

   switch(mFileType) {
      case HANDY_FILETYPE_RAW:
      case HANDY_FILETYPE_LNX:
         mCart = new CCart(game_memory,game_memory_size);
         if(mCart->CartHeaderLess()) {
            // Very strange Howard Check CANNOT work, as there are two
            // different loader-less card types...
            // unclear HOW this should do anything useful...
            mFileType = HANDY_FILETYPE_HOMEBREW;

            if (!string_is_empty(romfile)) {
               RFILE *fp = NULL;
               char cartgo[PATH_MAX_LENGTH];
               cartgo[0] = '\0';

               fill_pathname_resolve_relative(cartgo,
                     romfile, "howard.o", sizeof(cartgo));

               // Open the howard file for reading
               if (!string_is_empty(cartgo) &&
                   path_is_valid(cartgo))
                  fp = filestream_open(cartgo, RETRO_VFS_FILE_ACCESS_READ,
                        RETRO_VFS_FILE_ACCESS_HINT_NONE);

               if (fp) {
                  // How big is the file?
                  filestream_seek(fp, 0, RETRO_VFS_SEEK_POSITION_END);
                  howard_memory_size = filestream_tell(fp);
                  filestream_seek(fp, 0, RETRO_VFS_SEEK_POSITION_START);

                  howard_memory = (UBYTE*) new UBYTE[howard_memory_size];

                  if (filestream_read(fp, howard_memory, howard_memory_size) != howard_memory_size) {
                     handy_log(RETRO_LOG_ERROR, "Failed to read howard file: %s\n", cartgo);
                     howard_memory_size = 0;
                  }

                  filestream_close(fp);
               }
               else
                  handy_log(RETRO_LOG_ERROR, "Failed to open howard file: %s\n",
                        string_is_empty(cartgo) ? "NULL" : cartgo);
            }

            // Pass it to RAM to load
            mRam = new CRam(howard_memory,howard_memory_size);
         } else {
            mRam = new CRam(0,0);
         }
         break;
      case HANDY_FILETYPE_HOMEBREW:
         mCart = new CCart(0,0);
         mRam = new CRam(game_memory,game_memory_size);
         break;
      case HANDY_FILETYPE_SNAPSHOT:
      case HANDY_FILETYPE_ILLEGAL:
      default:
         mCart = new CCart(0,0);
         mRam = new CRam(0,0);
         break;
   }

   // These can generate exceptions

   mMikie = new CMikie(*this);
   mSusie = new CSusie(*this);

   // Instantiate the memory map handler

   mMemMap = new CMemMap(*this);

   // Now the handlers are set we can instantiate the CPU as is will use handlers on reset

   mCpu = new C65C02(*this);

   // Now init is complete do a reset, this will cause many things to be reset twice
   // but what the hell, who cares, I don't.....

   Reset();

   if (game_memory_buf)
      delete[] game_memory_buf;

   if (howard_memory)
      delete[] howard_memory;

   mEEPROM->SetEEPROMType(mCart->mEEPROMType);
   mEEPROM->SetFilename(eepromfile);
   mEEPROM->Load();
}

void CSystem::SaveEEPROM(void)
{
   if(mEEPROM!=NULL) mEEPROM->Save();
}

CSystem::~CSystem()
{
   // Cleanup all our objects

   if(mEEPROM!=NULL) delete mEEPROM;
   if(mCart!=NULL) delete mCart;
   if(mRom!=NULL) delete mRom;
   if(mRam!=NULL) delete mRam;
   if(mCpu!=NULL) delete mCpu;
   if(mMikie!=NULL) delete mMikie;
   if(mSusie!=NULL) delete mSusie;
   if(mMemMap!=NULL) delete mMemMap;
}

void CSystem::HLE_BIOS_FE00(void)
{
    // Select Block in A
    C6502_REGS regs;
    mCpu->GetRegs(regs);
    mCart->SetShifterValue(regs.A);
    // we just put an RTS behind in fake ROM!
}

void CSystem::HLE_BIOS_FE19(void)
{
   // (not) initial jump from reset vector
   // Clear full 64k memory!
   mRam->Clear();

   // Set Load adresse to $200 ($05,$06)
   mRam->Poke(0x0005,0x00);
   mRam->Poke(0x0006,0x02);
   // Call to $FE00
   mCart->SetShifterValue(0);
   // Fallthrou $FE4A
   HLE_BIOS_FE4A();
}

void CSystem::HLE_BIOS_FE4A(void)
{
   UWORD addr=mRam->Peek(0x0005) | (mRam->Peek(0x0006)<<8);

   // Load from Cart (loader blocks)
   unsigned char buff[256];// maximum 5 blocks
   unsigned char res[256];

   buff[0]=mCart->Peek0();
   int blockcount = 0x100 -  buff[0];

   for (int i = 1; i < 1+51*blockcount; ++i) { // first encrypted loader
      buff[i] = mCart->Peek0();
   }

   lynx_decrypt(res, buff, 51);

   for (int i = 0; i < 50*blockcount; ++i) {
      Poke_CPU(addr++, res[i]);
   }

   // Load Block(s), decode to ($05,$06)
   // jmp $200

   C6502_REGS regs;
   mCpu->GetRegs(regs);
   regs.PC=0x0200;
   mCpu->SetRegs(regs);
}

void CSystem::HLE_BIOS_FF80(void)
{
    // initial jump from reset vector ... calls FE19
    HLE_BIOS_FE19();
}

void CSystem::Reset(void)
{
   gSystemCycleCount=0;
   gLastRunCycleCount=0;
   gNextTimerEvent=0;
   gCPUBootAddress=0;
   gBreakpointHit=FALSE;
   gSingleStepMode=FALSE;
   gSingleStepModeSprites=FALSE;
   gSystemIRQ=FALSE;
   gSystemNMI=FALSE;
   gSystemCPUSleep=FALSE;
   gSystemHalt=FALSE;

   gThrottleLastTimerCount=0;
   gThrottleNextCycleCheckpoint=0;

   gTimerCount=0;

   gAudioBufferPointer=0;
   gAudioLastUpdateCycle=0;
//	memset(gAudioBuffer,128,HANDY_AUDIO_BUFFER_SIZE); // only for unsigned 8bit
	memset(gAudioBuffer,0,HANDY_AUDIO_BUFFER_SIZE); // for unsigned 8/16 bit

   mMemMap->Reset();
   mCart->Reset();
   mEEPROM->Reset();
   mRom->Reset();
   mRam->Reset();
   mMikie->Reset();
   mSusie->Reset();
   mCpu->Reset();

   // Homebrew hashup

   if(mFileType==HANDY_FILETYPE_HOMEBREW) {
      mMikie->PresetForHomebrew();

      C6502_REGS regs;
      mCpu->GetRegs(regs);
      regs.PC=(UWORD)gCPUBootAddress;
      mCpu->SetRegs(regs);
   } else {
      if(!mRom->mValid) {
	     mMikie->PresetForHomebrew();
         mRom->mWriteEnable=true;

         mRom->Poke(0xFE00+0,0x8d);
         mRom->Poke(0xFE00+1,0x97);
         mRom->Poke(0xFE00+2,0xfd);
         mRom->Poke(0xFE00+3,0x60);// RTS

         mRom->Poke(0xFE19+0,0x8d);
         mRom->Poke(0xFE19+1,0x97);
         mRom->Poke(0xFE19+2,0xfd);
          
         mRom->Poke(0xFE4A+0,0x8d);
         mRom->Poke(0xFE4A+1,0x97);
         mRom->Poke(0xFE4A+2,0xfd);          

         mRom->Poke(0xFF80+0,0x8d);
         mRom->Poke(0xFF80+1,0x97);
         mRom->Poke(0xFF80+2,0xfd);          

         mRom->mWriteEnable=false;
      }
   }
}

size_t CSystem::ContextSize()
{
   LSS_FILE fp;
   const int max_size = 0x40000 + HANDY_AUDIO_BUFFER_SIZE;

   fp.memptr = (UBYTE *) malloc(max_size);
   fp.index = 0;
   fp.index_limit = max_size;

   ContextSave(&fp);

   free(fp.memptr);
   return fp.index;
}

bool CSystem::ContextSave(LSS_FILE *fp)
{
   bool status=1;

   fp->index = 0;
   if(!lss_printf(fp, LSS_VERSION)) status=0;

   // Save ROM CRC
   ULONG checksum=mCart->CRC32();
   if(!lss_write(&checksum,sizeof(ULONG),1,fp)) status=0;

   if(!lss_printf(fp, "CSystem::ContextSave")) status=0;

   if(!lss_write(&mCycleCountBreakpoint,sizeof(ULONG),1,fp)) status=0;
   if(!lss_write(&gSystemCycleCount,sizeof(ULONG),1,fp)) status=0;
   if(!lss_write(&gNextTimerEvent,sizeof(ULONG),1,fp)) status=0;
   if(!lss_write(&gCPUWakeupTime,sizeof(ULONG),1,fp)) status=0;
   if(!lss_write(&gCPUBootAddress,sizeof(ULONG),1,fp)) status=0;
   if(!lss_write(&gIRQEntryCycle,sizeof(ULONG),1,fp)) status=0;
   if(!lss_write(&gBreakpointHit,sizeof(ULONG),1,fp)) status=0;
   if(!lss_write(&gSingleStepMode,sizeof(ULONG),1,fp)) status=0;
   if(!lss_write(&gSystemIRQ,sizeof(ULONG),1,fp)) status=0;
   if(!lss_write(&gSystemNMI,sizeof(ULONG),1,fp)) status=0;
   if(!lss_write(&gSystemCPUSleep,sizeof(ULONG),1,fp)) status=0;
   if(!lss_write(&gSystemCPUSleep_Saved,sizeof(ULONG),1,fp)) status=0;
   if(!lss_write(&gSystemHalt,sizeof(ULONG),1,fp)) status=0;
   if(!lss_write(&gThrottleMaxPercentage,sizeof(ULONG),1,fp)) status=0;
   if(!lss_write(&gThrottleLastTimerCount,sizeof(ULONG),1,fp)) status=0;
   if(!lss_write(&gThrottleNextCycleCheckpoint,sizeof(ULONG),1,fp)) status=0;

   ULONG tmp=gTimerCount;
   if(!lss_write(&tmp,sizeof(ULONG),1,fp)) status=0;

   if(!lss_write(&gAudioLastUpdateCycle,sizeof(ULONG),1,fp)) status=0;

   // Save other device contexts
   if(!mMemMap->ContextSave(fp)) status=0;
   if(!mCart->ContextSave(fp)) status=0;
   //if(!mRom->ContextSave(fp)) status=0; We no longer save the system ROM
   if(!mRam->ContextSave(fp)) status=0;
   if(!mMikie->ContextSave(fp)) status=0;
   if(!mSusie->ContextSave(fp)) status=0;
   if(!mCpu->ContextSave(fp)) status=0;
   if(!mEEPROM->ContextSave(fp)) status=0;

   return status;
}

bool CSystem::ContextLoad(LSS_FILE *fp)
{
   bool status=1;

   fp->index=0;

   char teststr[100];
   // Check identifier
   if(!lss_read(teststr,sizeof(char),4,fp)) status=0;
   teststr[4]=0;

   if(strcmp(teststr,LSS_VERSION)==0 || strcmp(teststr,LSS_VERSION_OLD)==0) {
      bool legacy=FALSE;
      if(strcmp(teststr,LSS_VERSION_OLD)==0) {
         legacy=TRUE;
      } else {
         ULONG checksum;
         // Read CRC32 and check against the CART for a match
         lss_read(&checksum,sizeof(ULONG),1,fp);
         if(mCart->CRC32()!=checksum) {
            handy_log(RETRO_LOG_ERROR, "LSS Snapshot CRC does not match the loaded cartridge image, aborting load.\n");
            return 0;
         }
      }

      // Check our block header
      if(!lss_read(teststr,sizeof(char),20,fp)) status=0;
      teststr[20]=0;
      if(strcmp(teststr,"CSystem::ContextSave")!=0) status=0;

      if(!lss_read(&mCycleCountBreakpoint,sizeof(ULONG),1,fp)) status=0;
      if(!lss_read(&gSystemCycleCount,sizeof(ULONG),1,fp)) status=0;
      if(!lss_read(&gNextTimerEvent,sizeof(ULONG),1,fp)) status=0;
      if(!lss_read(&gCPUWakeupTime,sizeof(ULONG),1,fp)) status=0;
      if(!lss_read(&gCPUBootAddress,sizeof(ULONG),1,fp)) status=0;
      if(!lss_read(&gIRQEntryCycle,sizeof(ULONG),1,fp)) status=0;
      if(!lss_read(&gBreakpointHit,sizeof(ULONG),1,fp)) status=0;
      if(!lss_read(&gSingleStepMode,sizeof(ULONG),1,fp)) status=0;
      if(!lss_read(&gSystemIRQ,sizeof(ULONG),1,fp)) status=0;
      if(!lss_read(&gSystemNMI,sizeof(ULONG),1,fp)) status=0;
      if(!lss_read(&gSystemCPUSleep,sizeof(ULONG),1,fp)) status=0;
      if(!lss_read(&gSystemCPUSleep_Saved,sizeof(ULONG),1,fp)) status=0;
      if(!lss_read(&gSystemHalt,sizeof(ULONG),1,fp)) status=0;
      if(!lss_read(&gThrottleMaxPercentage,sizeof(ULONG),1,fp)) status=0;
      if(!lss_read(&gThrottleLastTimerCount,sizeof(ULONG),1,fp)) status=0;
      if(!lss_read(&gThrottleNextCycleCheckpoint,sizeof(ULONG),1,fp)) status=0;

      ULONG tmp;
      if(!lss_read(&tmp,sizeof(ULONG),1,fp)) status=0;
      gTimerCount=tmp;

      if(!lss_read(&gAudioLastUpdateCycle,sizeof(ULONG),1,fp)) status=0;

      if(!mMemMap->ContextLoad(fp)) status=0;
      // Legacy support
      if(legacy) {
         if(!mCart->ContextLoadLegacy(fp)) status=0;
         if(!mRom->ContextLoad(fp)) status=0;
      } else {
         if(!mCart->ContextLoad(fp)) status=0;
      }
      if(!mRam->ContextLoad(fp)) status=0;
      if(!mMikie->ContextLoad(fp)) status=0;
      if(!mSusie->ContextLoad(fp)) status=0;
      if(!mCpu->ContextLoad(fp)) status=0;
      if(!mEEPROM->ContextLoad(fp)) status=0;

      gAudioBufferPointer = 0;
   } else {
      handy_log(RETRO_LOG_ERROR, "Not a recognised LSS file\n");
   }

   return status;
}
