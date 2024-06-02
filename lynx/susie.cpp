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
// Suzy emulation class                                                     //
//////////////////////////////////////////////////////////////////////////////
//                                                                          //
// This class emulates the Suzy chip within the lynx. This provides math    //
// and sprite painting facilities. SpritePaint() is called from within      //
// the Mikey POKE functions when SPRGO is set and is called via the system  //
// object to keep the interface clean.                                      //
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

#define SUSIE_CPP

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "system.h"
#include "susie.h"
#include "lynxdef.h"

//
// As the Susie sprite engine only ever sees system RAM
// wa can access this directly without the hassle of
// going through the system object, much faster
//
//#define RAM_PEEK(m)			(mSystem.Peek_RAM((m)))
//#define RAM_POKE(m1,m2)		(mSystem.Poke_RAM((m1),(m2)))
//#define RAM_PEEKW(m)			(mSystem.PeekW_RAM((m)))

#define RAM_PEEK(m)				(mRamPointer[(m)])
#define RAM_PEEKW(m)			(mRamPointer[(m)]+(mRamPointer[(m)+1]<<8))
#define RAM_POKE(m1,m2)			{mRamPointer[(m1)]=(m2);}

ULONG cycles_used=0;

CSusie::CSusie(CSystem& parent)
   :mSystem(parent)
{
   Reset();
}

CSusie::~CSusie()
{
}

void CSusie::Reset(void)
{
   // Fetch pointer to system RAM, faster than object access
   // and seeing as Susie only ever sees RAM.

   mRamPointer=mSystem.GetRamPointer();

   // Reset ALL variables

   mTMPADR.Word=0;
   mTILTACUM.Word=0;
   mHOFF.Word=0;
   mVOFF.Word=0;
   mVIDBAS.Word=0;
   mCOLLBAS.Word=0;
   mVIDADR.Word=0;
   mCOLLADR.Word=0;
   mSCBNEXT.Word=0;
   mSPRDLINE.Word=0;
   mHPOSSTRT.Word=0;
   mVPOSSTRT.Word=0;
   mSPRHSIZ.Word=0;
   mSPRVSIZ.Word=0;
   mSTRETCH.Word=0;
   mTILT.Word=0;
   mSPRDOFF.Word=0;
   mSPRVPOS.Word=0;
   mCOLLOFF.Word=0;
   mVSIZACUM.Word=0;
   mHSIZACUM.Word=0;
   mHSIZOFF.Word=0x007f;
   mVSIZOFF.Word=0x007f;
   mSCBADR.Word=0;
   mPROCADR.Word=0;

   // Must be initialised to this due to
   // stun runner math initialisation bug
   // see whatsnew for 0.7
   mMATHABCD.Long=0xffffffff;
   mMATHEFGH.Long=0xffffffff;
   mMATHJKLM.Long=0xffffffff;
   mMATHNP.Long=0xffff;

   mMATHAB_sign=1;
   mMATHCD_sign=1;
   mMATHEFGH_sign=1;

   mSPRCTL0_Type=0;
   mSPRCTL0_Vflip=0;
   mSPRCTL0_Hflip=0;
   mSPRCTL0_PixelBits=0;

   mSPRCTL1_StartLeft=0;
   mSPRCTL1_StartUp=0;
   mSPRCTL1_SkipSprite=0;
   mSPRCTL1_ReloadPalette=0;
   mSPRCTL1_ReloadDepth=0;
   mSPRCTL1_Sizing=0;
   mSPRCTL1_Literal=0;

   mSPRCOLL_Number=0;
   mSPRCOLL_Collide=0;

   mSPRSYS_StopOnCurrent=0;
   mSPRSYS_LeftHand=0;
   mSPRSYS_VStretch=0;
   mSPRSYS_NoCollide=0;
   mSPRSYS_Accumulate=0;
   mSPRSYS_SignedMath=0;
   mSPRSYS_Status=0;
   mSPRSYS_UnsafeAccess=0;
   mSPRSYS_LastCarry=0;
   mSPRSYS_Mathbit=0;
   mSPRSYS_MathInProgress=0;

   mSUZYBUSEN=FALSE;

   mSPRINIT.Byte=0;

   mSPRGO=FALSE;
   mEVERON=FALSE;

   for(int loop=0;loop<16;loop++) mPenIndex[loop]=loop;

   mJOYSTICK.Byte=0;
   mSWITCHES.Byte=0;
}

bool CSusie::ContextSave(LSS_FILE *fp)
{
   if(!lss_printf(fp,"CSusie::ContextSave")) return 0;

   if(!lss_write(&mTMPADR,sizeof(UUWORD),1,fp)) return 0;
   if(!lss_write(&mTILTACUM,sizeof(UUWORD),1,fp)) return 0;
   if(!lss_write(&mHOFF,sizeof(UUWORD),1,fp)) return 0;
   if(!lss_write(&mVOFF,sizeof(UUWORD),1,fp)) return 0;
   if(!lss_write(&mVIDBAS,sizeof(UUWORD),1,fp)) return 0;
   if(!lss_write(&mCOLLBAS,sizeof(UUWORD),1,fp)) return 0;
   if(!lss_write(&mVIDADR,sizeof(UUWORD),1,fp)) return 0;
   if(!lss_write(&mCOLLADR,sizeof(UUWORD),1,fp)) return 0;
   if(!lss_write(&mSCBNEXT,sizeof(UUWORD),1,fp)) return 0;
   if(!lss_write(&mSPRDLINE,sizeof(UUWORD),1,fp)) return 0;
   if(!lss_write(&mHPOSSTRT,sizeof(UUWORD),1,fp)) return 0;
   if(!lss_write(&mVPOSSTRT,sizeof(UUWORD),1,fp)) return 0;
   if(!lss_write(&mSPRHSIZ,sizeof(UUWORD),1,fp)) return 0;
   if(!lss_write(&mSPRVSIZ,sizeof(UUWORD),1,fp)) return 0;
   if(!lss_write(&mSTRETCH,sizeof(UUWORD),1,fp)) return 0;
   if(!lss_write(&mTILT,sizeof(UUWORD),1,fp)) return 0;
   if(!lss_write(&mSPRDOFF,sizeof(UUWORD),1,fp)) return 0;
   if(!lss_write(&mSPRVPOS,sizeof(UUWORD),1,fp)) return 0;
   if(!lss_write(&mCOLLOFF,sizeof(UUWORD),1,fp)) return 0;
   if(!lss_write(&mVSIZACUM,sizeof(UUWORD),1,fp)) return 0;
   if(!lss_write(&mHSIZACUM,sizeof(UUWORD),1,fp)) return 0;
   if(!lss_write(&mHSIZOFF,sizeof(UUWORD),1,fp)) return 0;
   if(!lss_write(&mVSIZOFF,sizeof(UUWORD),1,fp)) return 0;
   if(!lss_write(&mSCBADR,sizeof(UUWORD),1,fp)) return 0;
   if(!lss_write(&mPROCADR,sizeof(UUWORD),1,fp)) return 0;

   if(!lss_write(&mMATHABCD,sizeof(TMATHABCD),1,fp)) return 0;
   if(!lss_write(&mMATHEFGH,sizeof(TMATHEFGH),1,fp)) return 0;
   if(!lss_write(&mMATHJKLM,sizeof(TMATHJKLM),1,fp)) return 0;
   if(!lss_write(&mMATHNP,sizeof(TMATHNP),1,fp)) return 0;

   if(!lss_write(&mSPRCTL0_Type,sizeof(ULONG),1,fp)) return 0;
   if(!lss_write(&mSPRCTL0_Vflip,sizeof(ULONG),1,fp)) return 0;
   if(!lss_write(&mSPRCTL0_Hflip,sizeof(ULONG),1,fp)) return 0;
   if(!lss_write(&mSPRCTL0_PixelBits,sizeof(ULONG),1,fp)) return 0;

   if(!lss_write(&mSPRCTL1_StartLeft,sizeof(ULONG),1,fp)) return 0;
   if(!lss_write(&mSPRCTL1_StartUp,sizeof(ULONG),1,fp)) return 0;
   if(!lss_write(&mSPRCTL1_SkipSprite,sizeof(ULONG),1,fp)) return 0;
   if(!lss_write(&mSPRCTL1_ReloadPalette,sizeof(ULONG),1,fp)) return 0;
   if(!lss_write(&mSPRCTL1_ReloadDepth,sizeof(ULONG),1,fp)) return 0;
   if(!lss_write(&mSPRCTL1_Sizing,sizeof(ULONG),1,fp)) return 0;
   if(!lss_write(&mSPRCTL1_Literal,sizeof(ULONG),1,fp)) return 0;

   if(!lss_write(&mSPRCOLL_Number,sizeof(ULONG),1,fp)) return 0;
   if(!lss_write(&mSPRCOLL_Collide,sizeof(ULONG),1,fp)) return 0;

   if(!lss_write(&mSPRSYS_StopOnCurrent,sizeof(ULONG),1,fp)) return 0;
   if(!lss_write(&mSPRSYS_LeftHand,sizeof(ULONG),1,fp)) return 0;
   if(!lss_write(&mSPRSYS_VStretch,sizeof(ULONG),1,fp)) return 0;
   if(!lss_write(&mSPRSYS_NoCollide,sizeof(ULONG),1,fp)) return 0;
   if(!lss_write(&mSPRSYS_Accumulate,sizeof(ULONG),1,fp)) return 0;
   if(!lss_write(&mSPRSYS_SignedMath,sizeof(ULONG),1,fp)) return 0;
   if(!lss_write(&mSPRSYS_Status,sizeof(ULONG),1,fp)) return 0;
   if(!lss_write(&mSPRSYS_UnsafeAccess,sizeof(ULONG),1,fp)) return 0;
   if(!lss_write(&mSPRSYS_LastCarry,sizeof(ULONG),1,fp)) return 0;
   if(!lss_write(&mSPRSYS_Mathbit,sizeof(ULONG),1,fp)) return 0;
   if(!lss_write(&mSPRSYS_MathInProgress,sizeof(ULONG),1,fp)) return 0;

   if(!lss_write(&mSUZYBUSEN,sizeof(ULONG),1,fp)) return 0;

   if(!lss_write(&mSPRINIT,sizeof(TSPRINIT),1,fp)) return 0;

   if(!lss_write(&mSPRGO,sizeof(ULONG),1,fp)) return 0;
   if(!lss_write(&mEVERON,sizeof(ULONG),1,fp)) return 0;

   if(!lss_write(mPenIndex,sizeof(UBYTE),16,fp)) return 0;

   if(!lss_write(&mLineType,sizeof(ULONG),1,fp)) return 0;
   if(!lss_write(&mLineShiftRegCount,sizeof(ULONG),1,fp)) return 0;
   if(!lss_write(&mLineShiftReg,sizeof(ULONG),1,fp)) return 0;
   if(!lss_write(&mLineRepeatCount,sizeof(ULONG),1,fp)) return 0;
   if(!lss_write(&mLinePixel,sizeof(ULONG),1,fp)) return 0;
   if(!lss_write(&mLinePacketBitsLeft,sizeof(ULONG),1,fp)) return 0;

   if(!lss_write(&mCollision,sizeof(ULONG),1,fp)) return 0;

   if(!lss_write(&mLineBaseAddress,sizeof(ULONG),1,fp)) return 0;
   if(!lss_write(&mLineCollisionAddress,sizeof(ULONG),1,fp)) return 0;

   if(!lss_write(&mJOYSTICK,sizeof(TJOYSTICK),1,fp)) return 0;
   if(!lss_write(&mSWITCHES,sizeof(TSWITCHES),1,fp)) return 0;

   return 1;
}

bool CSusie::ContextLoad(LSS_FILE *fp)
{
   char teststr[100]="XXXXXXXXXXXXXXXXXXX";
   if(!lss_read(teststr,sizeof(char),19,fp)) return 0;
   if(strcmp(teststr,"CSusie::ContextSave")!=0) return 0;

   if(!lss_read(&mTMPADR,sizeof(UUWORD),1,fp)) return 0;
   if(!lss_read(&mTILTACUM,sizeof(UUWORD),1,fp)) return 0;
   if(!lss_read(&mHOFF,sizeof(UUWORD),1,fp)) return 0;
   if(!lss_read(&mVOFF,sizeof(UUWORD),1,fp)) return 0;
   if(!lss_read(&mVIDBAS,sizeof(UUWORD),1,fp)) return 0;
   if(!lss_read(&mCOLLBAS,sizeof(UUWORD),1,fp)) return 0;
   if(!lss_read(&mVIDADR,sizeof(UUWORD),1,fp)) return 0;
   if(!lss_read(&mCOLLADR,sizeof(UUWORD),1,fp)) return 0;
   if(!lss_read(&mSCBNEXT,sizeof(UUWORD),1,fp)) return 0;
   if(!lss_read(&mSPRDLINE,sizeof(UUWORD),1,fp)) return 0;
   if(!lss_read(&mHPOSSTRT,sizeof(UUWORD),1,fp)) return 0;
   if(!lss_read(&mVPOSSTRT,sizeof(UUWORD),1,fp)) return 0;
   if(!lss_read(&mSPRHSIZ,sizeof(UUWORD),1,fp)) return 0;
   if(!lss_read(&mSPRVSIZ,sizeof(UUWORD),1,fp)) return 0;
   if(!lss_read(&mSTRETCH,sizeof(UUWORD),1,fp)) return 0;
   if(!lss_read(&mTILT,sizeof(UUWORD),1,fp)) return 0;
   if(!lss_read(&mSPRDOFF,sizeof(UUWORD),1,fp)) return 0;
   if(!lss_read(&mSPRVPOS,sizeof(UUWORD),1,fp)) return 0;
   if(!lss_read(&mCOLLOFF,sizeof(UUWORD),1,fp)) return 0;
   if(!lss_read(&mVSIZACUM,sizeof(UUWORD),1,fp)) return 0;
   if(!lss_read(&mHSIZACUM,sizeof(UUWORD),1,fp)) return 0;
   if(!lss_read(&mHSIZOFF,sizeof(UUWORD),1,fp)) return 0;
   if(!lss_read(&mVSIZOFF,sizeof(UUWORD),1,fp)) return 0;
   if(!lss_read(&mSCBADR,sizeof(UUWORD),1,fp)) return 0;
   if(!lss_read(&mPROCADR,sizeof(UUWORD),1,fp)) return 0;

   if(!lss_read(&mMATHABCD,sizeof(TMATHABCD),1,fp)) return 0;
   if(!lss_read(&mMATHEFGH,sizeof(TMATHEFGH),1,fp)) return 0;
   if(!lss_read(&mMATHJKLM,sizeof(TMATHJKLM),1,fp)) return 0;
   if(!lss_read(&mMATHNP,sizeof(TMATHNP),1,fp)) return 0;

   if(!lss_read(&mSPRCTL0_Type,sizeof(ULONG),1,fp)) return 0;
   if(!lss_read(&mSPRCTL0_Vflip,sizeof(ULONG),1,fp)) return 0;
   if(!lss_read(&mSPRCTL0_Hflip,sizeof(ULONG),1,fp)) return 0;
   if(!lss_read(&mSPRCTL0_PixelBits,sizeof(ULONG),1,fp)) return 0;

   if(!lss_read(&mSPRCTL1_StartLeft,sizeof(ULONG),1,fp)) return 0;
   if(!lss_read(&mSPRCTL1_StartUp,sizeof(ULONG),1,fp)) return 0;
   if(!lss_read(&mSPRCTL1_SkipSprite,sizeof(ULONG),1,fp)) return 0;
   if(!lss_read(&mSPRCTL1_ReloadPalette,sizeof(ULONG),1,fp)) return 0;
   if(!lss_read(&mSPRCTL1_ReloadDepth,sizeof(ULONG),1,fp)) return 0;
   if(!lss_read(&mSPRCTL1_Sizing,sizeof(ULONG),1,fp)) return 0;
   if(!lss_read(&mSPRCTL1_Literal,sizeof(ULONG),1,fp)) return 0;

   if(!lss_read(&mSPRCOLL_Number,sizeof(ULONG),1,fp)) return 0;
   if(!lss_read(&mSPRCOLL_Collide,sizeof(ULONG),1,fp)) return 0;

   if(!lss_read(&mSPRSYS_StopOnCurrent,sizeof(ULONG),1,fp)) return 0;
   if(!lss_read(&mSPRSYS_LeftHand,sizeof(ULONG),1,fp)) return 0;
   if(!lss_read(&mSPRSYS_VStretch,sizeof(ULONG),1,fp)) return 0;
   if(!lss_read(&mSPRSYS_NoCollide,sizeof(ULONG),1,fp)) return 0;
   if(!lss_read(&mSPRSYS_Accumulate,sizeof(ULONG),1,fp)) return 0;
   if(!lss_read(&mSPRSYS_SignedMath,sizeof(ULONG),1,fp)) return 0;
   if(!lss_read(&mSPRSYS_Status,sizeof(ULONG),1,fp)) return 0;
   if(!lss_read(&mSPRSYS_UnsafeAccess,sizeof(ULONG),1,fp)) return 0;
   if(!lss_read(&mSPRSYS_LastCarry,sizeof(ULONG),1,fp)) return 0;
   if(!lss_read(&mSPRSYS_Mathbit,sizeof(ULONG),1,fp)) return 0;
   if(!lss_read(&mSPRSYS_MathInProgress,sizeof(ULONG),1,fp)) return 0;

   if(!lss_read(&mSUZYBUSEN,sizeof(ULONG),1,fp)) return 0;

   if(!lss_read(&mSPRINIT,sizeof(TSPRINIT),1,fp)) return 0;

   if(!lss_read(&mSPRGO,sizeof(ULONG),1,fp)) return 0;
   if(!lss_read(&mEVERON,sizeof(ULONG),1,fp)) return 0;

   if(!lss_read(mPenIndex,sizeof(UBYTE),16,fp)) return 0;

   if(!lss_read(&mLineType,sizeof(ULONG),1,fp)) return 0;
   if(!lss_read(&mLineShiftRegCount,sizeof(ULONG),1,fp)) return 0;
   if(!lss_read(&mLineShiftReg,sizeof(ULONG),1,fp)) return 0;
   if(!lss_read(&mLineRepeatCount,sizeof(ULONG),1,fp)) return 0;
   if(!lss_read(&mLinePixel,sizeof(ULONG),1,fp)) return 0;
   if(!lss_read(&mLinePacketBitsLeft,sizeof(ULONG),1,fp)) return 0;

   if(!lss_read(&mCollision,sizeof(ULONG),1,fp)) return 0;

   if(!lss_read(&mLineBaseAddress,sizeof(ULONG),1,fp)) return 0;
   if(!lss_read(&mLineCollisionAddress,sizeof(ULONG),1,fp)) return 0;

   if(!lss_read(&mJOYSTICK,sizeof(TJOYSTICK),1,fp)) return 0;
   if(!lss_read(&mSWITCHES,sizeof(TSWITCHES),1,fp)) return 0;

   return 1;
}


void CSusie::DoMathMultiply(void)
{
   mSPRSYS_Mathbit=FALSE;

   // Multiplies with out sign or accumulate take 44 ticks to complete.
   // Multiplies with sign and accumulate take 54 ticks to complete.
   //
   //    AB                                    EFGH
   //  * CD                                  /   NP
   // -------                            -----------
   //  EFGH                                    ABCD
   // Accumulate in JKLM         Remainder in (JK)LM
   //


   ULONG result;

   // Basic multiply is ALWAYS unsigned, sign conversion is done later
   result=(ULONG)mMATHABCD.Words.AB*(ULONG)mMATHABCD.Words.CD;
   mMATHEFGH.Long=result;

   if(mSPRSYS_SignedMath)
   {
      // Add the sign bits, only >0 is +ve result
      mMATHEFGH_sign=mMATHAB_sign+mMATHCD_sign;
      if(!mMATHEFGH_sign) {
         mMATHEFGH.Long^=0xffffffff;
         mMATHEFGH.Long++;
      }
   }

   // Check overflow, if B31 has changed from 1->0 then its overflow time
   if(mSPRSYS_Accumulate) {
      ULONG tmp=mMATHJKLM.Long+mMATHEFGH.Long;

      // Save accumulated result
      mMATHJKLM.Long=tmp;
   }
}

void CSusie::DoMathDivide(void)
{
   mSPRSYS_Mathbit=FALSE;

   //
   // Divides take 176 + 14*N ticks
   // (N is the number of most significant zeros in the divisor.)
   //
   //    AB                                    EFGH
   //  * CD                                  /   NP
   // -------                            -----------
   //  EFGH                                    ABCD
   // Accumulate in JKLM         Remainder in (JK)LM
   //

   // Divide is ALWAYS unsigned arithmetic...
   if(mMATHNP.Long) {
      mMATHABCD.Long=mMATHEFGH.Long/mMATHNP.Long;
      mMATHJKLM.Long=mMATHEFGH.Long%mMATHNP.Long;
   } else {
      mMATHABCD.Long=0xffffffff;
      mMATHJKLM.Long=0;
      mSPRSYS_Mathbit=TRUE;
   }
}


ULONG CSusie::PaintSprites(void)
{
   int	sprcount=0;
   int data=0;
   int everonscreen=0;

   if(!mSUZYBUSEN || !mSPRGO) {
      return 0;
   }

   cycles_used=0;

   do {
      everonscreen=0;// everon has to be reset for every sprite, thus line was moved inside this loop

      // Step 1 load up the SCB params into Susie

      // And thus it is documented that only the top byte of SCBNEXT is used.
      // Its mentioned under the bits that are broke section in the bluebook
      if(!(mSCBNEXT.Word&0xff00)) {
         mSPRSYS_Status=0;	// Engine has finished
         mSPRGO=FALSE;
         break;
      } else {
         mSPRSYS_Status=1;
      }

      mTMPADR.Word=mSCBNEXT.Word;	// Copy SCB pointer
      mSCBADR.Word=mSCBNEXT.Word;	// Copy SCB pointer

      data=RAM_PEEK(mTMPADR.Word);			// Fetch control 0
      mSPRCTL0_Type=data&0x0007;
      mSPRCTL0_Vflip=data&0x0010;
      mSPRCTL0_Hflip=data&0x0020;
      mSPRCTL0_PixelBits=((data&0x00c0)>>6)+1;
      mTMPADR.Word+=1;

      data=RAM_PEEK(mTMPADR.Word);			// Fetch control 1
      mSPRCTL1_StartLeft=data&0x0001;
      mSPRCTL1_StartUp=data&0x0002;
      mSPRCTL1_SkipSprite=data&0x0004;
      mSPRCTL1_ReloadPalette=data&0x0008;
      mSPRCTL1_ReloadDepth=(data&0x0030)>>4;
      mSPRCTL1_Sizing=data&0x0040;
      mSPRCTL1_Literal=data&0x0080;
      mTMPADR.Word+=1;

      data=RAM_PEEK(mTMPADR.Word);			// Collision num
      mSPRCOLL_Number=data&0x000f;
      mSPRCOLL_Collide=data&0x0020;
      mTMPADR.Word+=1;

      mSCBNEXT.Word=RAM_PEEKW(mTMPADR.Word);	// Next SCB
      mTMPADR.Word+=2;

      cycles_used+=5*SPR_RDWR_CYC;

      // Initialise the collision depositary

      // Although Tom Schenck says this is correct, it doesnt appear to be
      //		if(!mSPRCOLL_Collide && !mSPRSYS_NoCollide)
      //		{
      //			mCollision=RAM_PEEK((mSCBADR.Word+mCOLLOFF.Word)&0xffff);
      //			mCollision&=0x0f;
      //		}
      mCollision=0;

      // Check if this is a skip sprite

      if(!mSPRCTL1_SkipSprite)
      {
         mSPRDLINE.Word=RAM_PEEKW(mTMPADR.Word);	// Sprite pack data
         mTMPADR.Word+=2;

         mHPOSSTRT.Word=RAM_PEEKW(mTMPADR.Word);	// Sprite horizontal start position
         mTMPADR.Word+=2;

         mVPOSSTRT.Word=RAM_PEEKW(mTMPADR.Word);	// Sprite vertical start position
         mTMPADR.Word+=2;

         cycles_used+=6*SPR_RDWR_CYC;

         bool enable_sizing  = FALSE;
         bool enable_stretch = FALSE;
         bool enable_tilt    = FALSE;

         // Optional section defined by reload type in Control 1

         switch(mSPRCTL1_ReloadDepth) {
            case 1:
               enable_sizing=TRUE;

               mSPRHSIZ.Word=RAM_PEEKW(mTMPADR.Word);	// Sprite Horizontal size
               mTMPADR.Word+=2;

               mSPRVSIZ.Word=RAM_PEEKW(mTMPADR.Word);	// Sprite Verticalal size
               mTMPADR.Word+=2;

               cycles_used+=4*SPR_RDWR_CYC;
               break;

            case 2:
               enable_sizing=TRUE;
               enable_stretch=TRUE;

               mSPRHSIZ.Word=RAM_PEEKW(mTMPADR.Word);	// Sprite Horizontal size
               mTMPADR.Word+=2;

               mSPRVSIZ.Word=RAM_PEEKW(mTMPADR.Word);	// Sprite Verticalal size
               mTMPADR.Word+=2;

               mSTRETCH.Word=RAM_PEEKW(mTMPADR.Word);	// Sprite stretch
               mTMPADR.Word+=2;

               cycles_used+=6*SPR_RDWR_CYC;
               break;

            case 3:
               enable_sizing=TRUE;
               enable_stretch=TRUE;
               enable_tilt=TRUE;

               mSPRHSIZ.Word=RAM_PEEKW(mTMPADR.Word);	// Sprite Horizontal size
               mTMPADR.Word+=2;

               mSPRVSIZ.Word=RAM_PEEKW(mTMPADR.Word);	// Sprite Verticalal size
               mTMPADR.Word+=2;

               mSTRETCH.Word=RAM_PEEKW(mTMPADR.Word);	// Sprite stretch
               mTMPADR.Word+=2;

               mTILT.Word=RAM_PEEKW(mTMPADR.Word);		// Sprite tilt
               mTMPADR.Word+=2;

               cycles_used+=8*SPR_RDWR_CYC;
               break;

            default:
               break;
         }

         // Optional Palette reload

         if(!mSPRCTL1_ReloadPalette) {
            for(int loop=0;loop<8;loop++) {
               UBYTE data_tmp=RAM_PEEK(mTMPADR.Word++);
               mPenIndex[loop*2]=(data_tmp>>4)&0x0f;
               mPenIndex[(loop*2)+1]=data_tmp&0x0f;
            }
            // Increment cycle count for the reads
            cycles_used+=8*SPR_RDWR_CYC;
         }

         // Now we can start painting

         // Quadrant drawing order is: SE,NE,NW,SW
         // start quadrant is given by sprite_control1:0 & 1

         // Setup screen start end variables

         int screen_h_start=(int16_t)mHOFF.Word;
         int screen_h_end=(int16_t)mHOFF.Word+SCREEN_WIDTH;
         int screen_v_start=(int16_t)mVOFF.Word;
         int screen_v_end=(int16_t)mVOFF.Word+SCREEN_HEIGHT;

         int world_h_mid=screen_h_start+(SCREEN_WIDTH/2);
         int world_v_mid=screen_v_start+(SCREEN_HEIGHT/2);

         bool superclip=FALSE;
         int quadrant=0;
         int hsign,vsign;

         if(mSPRCTL1_StartLeft) {
            if(mSPRCTL1_StartUp) quadrant=2;
			else quadrant=3;
         } else {
            if(mSPRCTL1_StartUp) quadrant=1;
			else quadrant=0;
         }

         // Check ref is inside screen area

         if((int16_t)mHPOSSTRT.Word<screen_h_start || (int16_t)mHPOSSTRT.Word>=screen_h_end ||
            (int16_t)mVPOSSTRT.Word<screen_v_start || (int16_t)mVPOSSTRT.Word>=screen_v_end) superclip=TRUE;

         // Quadrant mapping is:	SE	NE	NW	SW
         //						0	1	2	3
         // hsign				+1	+1	-1	-1
         // vsign				+1	-1	-1	+1
         //
         //
         //		2 | 1
         //     -------
         //      3 | 0
         //

         // Loop for 4 quadrants

         for(int loop=0;loop<4;loop++) {
            int sprite_v=mVPOSSTRT.Word;
            int sprite_h=mHPOSSTRT.Word;

            bool render=FALSE;

            // Set quadrand multipliers
            hsign=(quadrant==0 || quadrant==1)?1:-1;
            vsign=(quadrant==0 || quadrant==3)?1:-1;

            // Preflip		

            //Use h/v flip to invert v/hsign

            if(mSPRCTL0_Vflip) vsign=-vsign;
            if(mSPRCTL0_Hflip) hsign=-hsign;

            // Two different rendering algorithms used, on-screen & superclip
            // when on screen we draw in x until off screen then skip to next
            // line, BUT on superclip we draw all the way to the end of any
            // given line checking each pixel is on screen.

            if(superclip) {
               // Check on the basis of each quad, we only render the quad
               // IF the screen is in the quad, relative to the centre of
               // the screen which is calculated below.

               // Quadrant mapping is:	SE	NE	NW	SW
               //						0	1	2	3
               // hsign				+1	+1	-1	-1
               // vsign				+1	-1	-1	+1
               //
               //
               //		2 | 1
               //     -------
               //      3 | 0
               //
               // Quadrant mapping for superclipping must also take into account
               // the hflip, vflip bits & negative tilt to be able to work correctly
               //
               int	modquad=quadrant;
               static const int vquadflip[4]={1,0,3,2};
               static const int hquadflip[4]={3,2,1,0};

               if(mSPRCTL0_Vflip) modquad=vquadflip[modquad];
               if(mSPRCTL0_Hflip) modquad=hquadflip[modquad];

               // This is causing Eurosoccer to fail!!
               //					if(enable_tilt && mTILT.Word&0x8000) modquad=hquadflip[modquad];

               switch(modquad) {
                  case 3:
                     if((sprite_h>=screen_h_start || sprite_h<=world_h_mid) && (sprite_v<screen_v_end    || sprite_v>=world_v_mid)) render=TRUE;
                     break;
                  case 2:
                     if((sprite_h>=screen_h_start || sprite_h<=world_h_mid) && (sprite_v>=screen_v_start || sprite_v<=world_v_mid)) render=TRUE;
                     break;
                  case 1:
                     if((sprite_h<screen_h_end    || sprite_h>=world_h_mid) && (sprite_v>=screen_v_start || sprite_v<=world_v_mid)) render=TRUE;
                     break;
                  default:
                     if((sprite_h<screen_h_end    || sprite_h>=world_h_mid) && (sprite_v<screen_v_end    || sprite_v>=world_v_mid)) render=TRUE;
                     break;
               }
            } else {
               render=TRUE;
            }

            // Is this quad to be rendered ??

            static int pixel_height=0;
            static int pixel_width=0;
            static int pixel=0;
            static int hoff=0,voff=0;
            static int hloop=0,vloop=0;
            static bool onscreen=0;
            static int vquadoff=0;
            static int hquadoff=0;

            if(render)
            {
               // Set the vertical position & offset
               voff=(int16_t)mVPOSSTRT.Word-screen_v_start;

               // Zero the stretch,tilt & acum values
               mTILTACUM.Word=0;

               // Perform the SIZOFF
               if(vsign==1) mVSIZACUM.Word=mVSIZOFF.Word;
               else mVSIZACUM.Word=0;

               // Take the sign of the first quad (0) as the basic
               // sign, all other quads drawing in the other direction
               // get offset by 1 pixel in the other direction, this
               // fixes the squashed look on the multi-quad sprites.
               //					if(vsign==-1 && loop>0) voff+=vsign;
               if(loop==0)	vquadoff=vsign;
               if(vsign!=vquadoff) voff+=vsign;

               for(;;) {
                  // Vertical scaling is done here
                  mVSIZACUM.Word+=mSPRVSIZ.Word;
                  pixel_height=mVSIZACUM.Byte.High;
                  mVSIZACUM.Byte.High=0;

                  // Update the next data line pointer and initialise our line
                  mSPRDOFF.Word=(UWORD)LineInit(0);

                  // If 1 == next quad, ==0 end of sprite, anyways its END OF LINE
                  if(mSPRDOFF.Word==1) {		// End of quad
                     mSPRDLINE.Word+=mSPRDOFF.Word;
                     break;
                  }

                  if(mSPRDOFF.Word==0) {		// End of sprite
                     loop=4;		// Halt the quad loop
                     break;
                  }

                  // Draw one horizontal line of the sprite
                  for(vloop=0;vloop<pixel_height;vloop++) {
                     // Early bailout if the sprite has moved off screen, terminate quad
                     if(vsign==1 && voff>=SCREEN_HEIGHT)	break;
                     if(vsign==-1 && voff<0)	break;

                     // Only allow the draw to take place if the line is visible
                     if(voff>=0 && voff<SCREEN_HEIGHT) {
                        // Work out the horizontal pixel start position, start + tilt
                        mHPOSSTRT.Word+=((int16_t)mTILTACUM.Word>>8);
                        mTILTACUM.Byte.High=0;
                        hoff=(int)((int16_t)mHPOSSTRT.Word)-screen_h_start;

                        // Force the horizontal scaling accumulator (Alpine Games protection)
                        mHSIZACUM.Word=mHSIZOFF.Word;

                        // Take the sign of the first quad (0) as the basic
                        // sign, all other quads drawing in the other direction
                        // get offset by 1 pixel in the other direction, this
                        // fixes the squashed look on the multi-quad sprites.
                        //								if(hsign==-1 && loop>0) hoff+=hsign;
                        if(loop==0)	hquadoff=hsign;
                        if(hsign!=hquadoff) hoff+=hsign;

                        // Initialise our line
                        LineInit(voff);
                        onscreen=FALSE;

                        // Now render an individual destination line
                        while((pixel=LineGetPixel())!=LINE_END) {
                           // This is allowed to update every pixel
                           mHSIZACUM.Word+=mSPRHSIZ.Word;
                           pixel_width=mHSIZACUM.Byte.High;
                           mHSIZACUM.Byte.High=0;

                           for(hloop=0; hloop<pixel_width; hloop++) {
                              // Draw if onscreen but break loop on transition to offscreen
                              if(hoff>=0 && hoff<SCREEN_WIDTH) {
                                 ProcessPixel(hoff,pixel);
                                 onscreen = TRUE;
                                 everonscreen=TRUE;
                              } else {
                                 if(onscreen) break;
                              }
                              hoff+=hsign;
                           }
                        }
                     }
                     voff+=vsign;

                     // For every destination line we can modify SPRHSIZ & SPRVSIZ & TILTACUM
                     if(enable_stretch) {
                        mSPRHSIZ.Word+=mSTRETCH.Word;
                        //								if(mSPRSYS_VStretch) mSPRVSIZ.Word+=mSTRETCH.Word;
                     }
                     if(enable_tilt) {
                        // Manipulate the tilt stuff
                        mTILTACUM.Word+=mTILT.Word;
                     }
                  }
                  // According to the docs this increments per dest line
                  // but only gets set when the source line is read
                  if(mSPRSYS_VStretch) mSPRVSIZ.Word+=mSTRETCH.Word*pixel_height;

                  // Update the line start for our next run thru the loop
                  mSPRDLINE.Word+=mSPRDOFF.Word;
               }
            }
            else
            {
               // Skip thru data to next quad
               for(;;)
               {
                  // Read the start of line offset

                  mSPRDOFF.Word=(UWORD)LineInit(0);

                  // We dont want to process data so mSPRDLINE is useless to us
                  mSPRDLINE.Word+=mSPRDOFF.Word;

                  // If 1 == next quad, ==0 end of sprite, anyways its END OF LINE

                  if(mSPRDOFF.Word==1) break;	// End of quad
                  if(mSPRDOFF.Word==0) {		// End of sprite
                     loop=4;		// Halt the quad loop
                     break;
                  }

               }
            }

            // Increment quadrant and mask to 2 bit value (0-3)
            quadrant++;
            quadrant&=0x03;
         }

         // Write the collision depositary if required

         if(!mSPRCOLL_Collide && !mSPRSYS_NoCollide) {
            switch(mSPRCTL0_Type) {
               case sprite_xor_shadow:
               case sprite_boundary:
               case sprite_normal:
               case sprite_boundary_shadow:
               case sprite_shadow: {
                     UWORD coldep=mSCBADR.Word+mCOLLOFF.Word;
                     RAM_POKE(coldep,(UBYTE)mCollision);
                  }
                  break;
               default:
                  break;
            }
         }

         if(mEVERON) {
            UWORD coldep=mSCBADR.Word+mCOLLOFF.Word;
            UBYTE coldat=RAM_PEEK(coldep);
            if(!everonscreen) coldat|=0x80;
			else coldat&=0x7f;
            RAM_POKE(coldep,coldat);
         }

         // Perform Sprite debugging if required, single step on sprite draw
         if(gSingleStepModeSprites) {
            char message[256];
            sprintf(message,"CSusie:PaintSprites() - Rendered Sprite %03d",sprcount);
            if(!gError->Warning(message)) gSingleStepModeSprites=0;
         }
      }

      // Increase sprite number
      sprcount++;

      // Check if we abort after 1st sprite is complete

      //		if(mSPRSYS.Read.StopOnCurrent)
      //		{
      //			mSPRSYS.Read.Status=0;	// Engine has finished
      //			mSPRGO=FALSE;
      //			break;
      //		}

      // Check sprcount for looping SCB, random large number chosen
      if(sprcount>4096) {
         // Stop the system, otherwise we may just come straight back in.....
         gSystemHalt=TRUE;
         // Display warning message
         gError->Warning("CSusie:PaintSprites(): Single draw sprite limit exceeded (>4096). The SCB is most likely looped back on itself. Reset/Exit is recommended");
         // Signal error to the caller
         return 0;
      }
   } while(1);

   // Fudge factor to fix many flickering issues, also the keypress
   // problem with Hard Drivin and the strange pause in Dirty Larry.
   //	cycles_used>>=2;

   return cycles_used;
}

//
// Collision code modified by KW 22/11/98
// Collision buffer cler added if there is no
// apparent collision, I have a gut feeling this
// is the wrong solution to the inv07.com bug but
// it seems to work OK.
//
// Shadow-------------------------------|
// Boundary-Shadow--------------------| |
// Normal---------------------------| | |
// Boundary-----------------------| | | |
// Background-Shadow------------| | | | |
// Background-No Collision----| | | | | |
// Non-Collideable----------| | | | | | |
// Exclusive-or-Shadow----| | | | | | | |
//                        | | | | | | | |
//                        1 1 1 1 0 1 0 1   F is opaque
//                        0 0 0 0 1 1 0 0   E is collideable
//                        0 0 1 1 0 0 0 0   0 is opaque and collideable
//                        1 0 0 0 1 1 1 1   allow collision detect
//                        1 0 0 1 1 1 1 1   allow coll. buffer access
//                        1 0 0 0 0 0 0 0   exclusive-or the data
//

inline void CSusie::ProcessPixel(ULONG hoff,ULONG pixel)
{
   switch(mSPRCTL0_Type) {
      // BACKGROUND SHADOW
      // 1   F is opaque
      // 0   E is collideable
      // 1   0 is opaque and collideable
      // 0   allow collision detect
      // 1   allow coll. buffer access
      // 0   exclusive-or the data
      case sprite_background_shadow:
         WritePixel(hoff,pixel);
         if(!mSPRCOLL_Collide && !mSPRSYS_NoCollide && pixel!=0x0e) {
            WriteCollision(hoff,mSPRCOLL_Number);
         }
         break;

         // BACKGROUND NOCOLLIDE
         // 1   F is opaque
         // 0   E is collideable
         // 1   0 is opaque and collideable
         // 0   allow collision detect
         // 0   allow coll. buffer access
         // 0   exclusive-or the data
      case sprite_background_noncollide:
         WritePixel(hoff,pixel);
         break;

         // NOCOLLIDE
         // 1   F is opaque
         // 0   E is collideable
         // 0   0 is opaque and collideable
         // 0   allow collision detect
         // 0   allow coll. buffer access
         // 0   exclusive-or the data
      case sprite_noncollide:
         if(pixel!=0x00) WritePixel(hoff,pixel);
         break;

         // BOUNDARY
         // 0   F is opaque
         // 1   E is collideable
         // 0   0 is opaque and collideable
         // 1   allow collision detect
         // 1   allow coll. buffer access
         // 0   exclusive-or the data
      case sprite_boundary:
         if(pixel!=0x00 && pixel!=0x0f) {
            WritePixel(hoff,pixel);
         }
         if(pixel!=0x00) {
            if(!mSPRCOLL_Collide && !mSPRSYS_NoCollide) {
               int collision=ReadCollision(hoff);
               if(collision>mCollision) {
                  mCollision=collision;
               }
               // 01/05/00 V0.7	if(mSPRCOLL_Number>collision)
               {
                  WriteCollision(hoff,mSPRCOLL_Number);
               }
            }
         }
         break;

         // NORMAL
         // 1   F is opaque
         // 1   E is collideable
         // 0   0 is opaque and collideable
         // 1   allow collision detect
         // 1   allow coll. buffer access
         // 0   exclusive-or the data
      case sprite_normal:
         if(pixel!=0x00) {
            WritePixel(hoff,pixel);
            if(!mSPRCOLL_Collide && !mSPRSYS_NoCollide) {
               int collision=ReadCollision(hoff);
               if(collision>mCollision) {
                  mCollision=collision;
               }
               // 01/05/00 V0.7	if(mSPRCOLL_Number>collision)
               {
                  WriteCollision(hoff,mSPRCOLL_Number);
               }
            }
         }
         break;

         // BOUNDARY_SHADOW
         // 0   F is opaque
         // 0   E is collideable
         // 0   0 is opaque and collideable
         // 1   allow collision detect
         // 1   allow coll. buffer access
         // 0   exclusive-or the data
      case sprite_boundary_shadow:
         if(pixel!=0x00 && pixel!=0x0e && pixel!=0x0f) {
            WritePixel(hoff,pixel);
         }
         if(pixel!=0x00 && pixel!=0x0e) {
            if(!mSPRCOLL_Collide && !mSPRSYS_NoCollide) {
               int collision=ReadCollision(hoff);
               if(collision>mCollision) {
                  mCollision=collision;
               }
               // 01/05/00 V0.7	if(mSPRCOLL_Number>collision)
               {
                  WriteCollision(hoff,mSPRCOLL_Number);
               }
            }
         }
         break;

         // SHADOW
         // 1   F is opaque
         // 0   E is collideable
         // 0   0 is opaque and collideable
         // 1   allow collision detect
         // 1   allow coll. buffer access
         // 0   exclusive-or the data
      case sprite_shadow:
         if(pixel!=0x00) {
            WritePixel(hoff,pixel);
         }
         if(pixel!=0x00 && pixel!=0x0e) {
            if(!mSPRCOLL_Collide && !mSPRSYS_NoCollide) {
               int collision=ReadCollision(hoff);
               if(collision>mCollision) {
                  mCollision=collision;
               }
               // 01/05/00 V0.7	if(mSPRCOLL_Number>collision)
               {
                  WriteCollision(hoff,mSPRCOLL_Number);
               }
            }
         }
         break;

         // XOR SHADOW
         // 1   F is opaque
         // 0   E is collideable
         // 0   0 is opaque and collideable
         // 1   allow collision detect
         // 1   allow coll. buffer access
         // 1   exclusive-or the data
      case sprite_xor_shadow:
         if(pixel!=0x00) {
            WritePixel(hoff,ReadPixel(hoff)^pixel);
         }
         if(pixel!=0x00 && pixel!=0x0e) {
            if(!mSPRCOLL_Collide && !mSPRSYS_NoCollide && pixel!=0x0e) {
               int collision=ReadCollision(hoff);
               if(collision>mCollision) {
                  mCollision=collision;
               }
               // 01/05/00 V0.7	if(mSPRCOLL_Number>collision)
               {
                  WriteCollision(hoff,mSPRCOLL_Number);
               }
            }
         }
         break;
      default:
         //			_asm int 3;
         break;
   }
}

inline void CSusie::WritePixel(ULONG hoff,ULONG pixel)
{
   ULONG scr_addr=mLineBaseAddress+(hoff/2);

   UBYTE dest=RAM_PEEK(scr_addr);
   if(!(hoff&0x01)) {
      // Upper nibble screen write
      dest&=0x0f;
      dest|=pixel<<4;
   } else {
      // Lower nibble screen write
      dest&=0xf0;
      dest|=pixel;
   }
   RAM_POKE(scr_addr,dest);

   // Increment cycle count for the read/modify/write
   cycles_used+=2*SPR_RDWR_CYC;
}

inline ULONG CSusie::ReadPixel(ULONG hoff)
{
   ULONG scr_addr=mLineBaseAddress+(hoff/2);

   ULONG data=RAM_PEEK(scr_addr);
   if(!(hoff&0x01)) {
      // Upper nibble read
      data>>=4;
   } else {
      // Lower nibble read
      data&=0x0f;
   }

   // Increment cycle count for the read/modify/write
   cycles_used+=SPR_RDWR_CYC;

   return data;
}

inline void CSusie::WriteCollision(ULONG hoff,ULONG pixel)
{
   ULONG col_addr=mLineCollisionAddress+(hoff/2);

   UBYTE dest=RAM_PEEK(col_addr);
   if(!(hoff&0x01)) {
      // Upper nibble screen write
      dest&=0x0f;
      dest|=pixel<<4;
   } else {
      // Lower nibble screen write
      dest&=0xf0;
      dest|=pixel;
   }
   RAM_POKE(col_addr,dest);

   // Increment cycle count for the read/modify/write
   cycles_used+=2*SPR_RDWR_CYC;
}

inline ULONG CSusie::ReadCollision(ULONG hoff)
{
   ULONG col_addr=mLineCollisionAddress+(hoff/2);

   ULONG data=RAM_PEEK(col_addr);
   if(!(hoff&0x01)) {
      // Upper nibble read
      data>>=4;
   } else {
      // Lower nibble read
      data&=0x0f;
   }

   // Increment cycle count for the read/modify/write
   cycles_used+=SPR_RDWR_CYC;

   return data;
}


inline ULONG CSusie::LineInit(ULONG voff)
{
   mLineShiftReg=0;
   mLineShiftRegCount=0;
   mLineRepeatCount=0;
   mLinePixel=0;
   mLineType=line_error;
   mLinePacketBitsLeft=0xffff;

   // Initialise the temporary pointer

   mTMPADR=mSPRDLINE;

   // First read the Offset to the next line

   ULONG offset=LineGetBits(8);

   // Specify the MAXIMUM number of bits in this packet, it
   // can terminate early but can never use more than this
   // without ending the current packet, we count down in LineGetBits()

   mLinePacketBitsLeft=(offset-1)*8;

   // Literals are a special case and get their count set on a line basis

   if(mSPRCTL1_Literal) {
      mLineType=line_abs_literal;
      mLineRepeatCount=((offset-1)*8)/mSPRCTL0_PixelBits;
      // Why is this necessary, is this compensating for the 1,1 offset bug
      //		mLineRepeatCount--;
   }

   // Set the line base address for use in the calls to pixel painting

   if(voff>101) {
      gError->Warning("CSusie::LineInit() Out of bounds (voff)");
      voff=0;
   }

   mLineBaseAddress=mVIDBAS.Word+(voff*(SCREEN_WIDTH/2));
   mLineCollisionAddress=mCOLLBAS.Word+(voff*(SCREEN_WIDTH/2));

   // Return the offset to the next line

   return offset;
}

inline ULONG CSusie::LineGetPixel()
{
   if(!mLineRepeatCount) {
      // Normal sprites fetch their counts on a packet basis
      if(mLineType!=line_abs_literal) {
         ULONG literal=LineGetBits(1);
         if(literal) mLineType=line_literal;
		 else mLineType=line_packed;
      }

      // Pixel store is empty what should we do
      switch(mLineType) {
         case line_abs_literal:
            // This means end of line for us
            mLinePixel=LINE_END;
            return mLinePixel;		// SPEEDUP
         case line_literal:
            mLineRepeatCount=LineGetBits(4);
            mLineRepeatCount++;
            break;
         case line_packed:
            //
            // From reading in between the lines only a packed line with
            // a zero size i.e 0b00000 as a header is allowable as a packet end
            //
            mLineRepeatCount=LineGetBits(4);
            if(!mLineRepeatCount) {
               mLinePixel=LINE_END;
            } else {
               mLinePixel=mPenIndex[LineGetBits(mSPRCTL0_PixelBits)];
            }
            mLineRepeatCount++;
            break;
         default:
            return 0;
      }

   }

   if(mLinePixel!=LINE_END) {
      mLineRepeatCount--;

      switch(mLineType) {
         case line_abs_literal:
            mLinePixel=LineGetBits(mSPRCTL0_PixelBits);
            // Check the special case of a zero in the last pixel
            if(!mLineRepeatCount && !mLinePixel)
               mLinePixel=LINE_END;
            else
               mLinePixel=mPenIndex[mLinePixel];
            break;
         case line_literal:
            mLinePixel=mPenIndex[LineGetBits(mSPRCTL0_PixelBits)];
            break;
         case line_packed:
            break;
         default:
            return 0;
      }
   }

   return mLinePixel;
}

inline ULONG CSusie::LineGetBits(ULONG bits)
{
   ULONG retval;

   // Sanity, not really needed
   // if(bits>32) return 0;

   // Only return data IF there is enought bits left in the packet

   if(mLinePacketBitsLeft<=bits) return 0;// <= fixes issues with polygones "demo006"

   // Make sure shift reg has enough bits to fulfil the request

   if(mLineShiftRegCount<bits) {
      // This assumes data comes into LSB and out of MSB
      //		mLineShiftReg&=0x000000ff;	// Has no effect
      mLineShiftReg<<=24;
      mLineShiftReg|=RAM_PEEK(mTMPADR.Word++)<<16;
      mLineShiftReg|=RAM_PEEK(mTMPADR.Word++)<<8;
      mLineShiftReg|=RAM_PEEK(mTMPADR.Word++);

      mLineShiftRegCount+=24;

      // Increment cycle count for the read
      cycles_used+=3*SPR_RDWR_CYC;
   }

   // Extract the return value
   retval=mLineShiftReg>>(mLineShiftRegCount-bits);
   retval&=(1<<bits)-1;

   // Update internal vars;
   mLineShiftRegCount-=bits;
   mLinePacketBitsLeft-=bits;

   return retval;
}


void CSusie::Poke(ULONG addr,UBYTE data)
{
   switch(addr&0xff) {
      case (TMPADRL&0xff):
         mTMPADR.Byte.Low=data;
         mTMPADR.Byte.High=0;
         break;
      case (TMPADRH&0xff):
         mTMPADR.Byte.High=data;
         break;
      case (TILTACUML&0xff):
         mTILTACUM.Byte.Low=data;
         mTILTACUM.Byte.High=0;
         break;
      case (TILTACUMH&0xff):
         mTILTACUM.Byte.High=data;
         break;
      case (HOFFL&0xff):
         mHOFF.Byte.Low=data;
         mHOFF.Byte.High=0;
         break;
      case (HOFFH&0xff):
         mHOFF.Byte.High=data;
         break;
      case (VOFFL&0xff):
         mVOFF.Byte.Low=data;
         mVOFF.Byte.High=0;
         break;
      case (VOFFH&0xff):
         mVOFF.Byte.High=data;
         break;
      case (VIDBASL&0xff):
         mVIDBAS.Byte.Low=data;
         mVIDBAS.Byte.High=0;
         break;
      case (VIDBASH&0xff):
         mVIDBAS.Byte.High=data;
         break;
      case (COLLBASL&0xff):
         mCOLLBAS.Byte.Low=data;
         mCOLLBAS.Byte.High=0;
         break;
      case (COLLBASH&0xff):
         mCOLLBAS.Byte.High=data;
         break;
      case (VIDADRL&0xff):
         mVIDADR.Byte.Low=data;
         mVIDADR.Byte.High=0;
         break;
      case (VIDADRH&0xff):
         mVIDADR.Byte.High=data;
         break;
      case (COLLADRL&0xff):
         mCOLLADR.Byte.Low=data;
         mCOLLADR.Byte.High=0;
         break;
      case (COLLADRH&0xff):
         mCOLLADR.Byte.High=data;
         break;
      case (SCBNEXTL&0xff):
         mSCBNEXT.Byte.Low=data;
         mSCBNEXT.Byte.High=0;
         break;
      case (SCBNEXTH&0xff):
         mSCBNEXT.Byte.High=data;
         break;
      case (SPRDLINEL&0xff):
         mSPRDLINE.Byte.Low=data;
         mSPRDLINE.Byte.High=0;
         break;
      case (SPRDLINEH&0xff):
         mSPRDLINE.Byte.High=data;
         break;
      case (HPOSSTRTL&0xff):
         mHPOSSTRT.Byte.Low=data;
         mHPOSSTRT.Byte.High=0;
         break;
      case (HPOSSTRTH&0xff):
         mHPOSSTRT.Byte.High=data;
         break;
      case (VPOSSTRTL&0xff):
         mVPOSSTRT.Byte.Low=data;
         mVPOSSTRT.Byte.High=0;
         break;
      case (VPOSSTRTH&0xff):
         mVPOSSTRT.Byte.High=data;
         break;
      case (SPRHSIZL&0xff):
         mSPRHSIZ.Byte.Low=data;
         mSPRHSIZ.Byte.High=0;
         break;
      case (SPRHSIZH&0xff):
         mSPRHSIZ.Byte.High=data;
         break;
      case (SPRVSIZL&0xff):
         mSPRVSIZ.Byte.Low=data;
         mSPRVSIZ.Byte.High=0;
         break;
      case (SPRVSIZH&0xff):
         mSPRVSIZ.Byte.High=data;
         break;
      case (STRETCHL&0xff):
         mSTRETCH.Byte.Low=data;
         mSTRETCH.Byte.High=0;
         break;
      case (STRETCHH&0xff):
         mSTRETCH.Byte.High=data;
         break;
      case (TILTL&0xff):
         mTILT.Byte.Low=data;
         mTILT.Byte.High=0;
         break;
      case (TILTH&0xff):
         mTILT.Byte.High=data;
         break;
      case (SPRDOFFL&0xff):
         mSPRDOFF.Byte.Low=data;
         mSPRDOFF.Byte.High=0;
         break;
      case (SPRDOFFH&0xff):
         mSPRDOFF.Byte.High=data;
         break;
      case (SPRVPOSL&0xff):
         mSPRVPOS.Byte.Low=data;
         mSPRVPOS.Byte.High=0;
         break;
      case (SPRVPOSH&0xff):
         mSPRVPOS.Byte.High=data;
         break;
      case (COLLOFFL&0xff):
         mCOLLOFF.Byte.Low=data;
         mCOLLOFF.Byte.High=0;
         break;
      case (COLLOFFH&0xff):
         mCOLLOFF.Byte.High=data;
         break;
      case (VSIZACUML&0xff):
         mVSIZACUM.Byte.Low=data;
         mVSIZACUM.Byte.High=0;
         break;
      case (VSIZACUMH&0xff):
         mVSIZACUM.Byte.High=data;
         break;
      case (HSIZOFFL&0xff):
         mHSIZOFF.Byte.Low=data;
         mHSIZOFF.Byte.High=0;
         break;
      case (HSIZOFFH&0xff):
         mHSIZOFF.Byte.High=data;
         break;
      case (VSIZOFFL&0xff):
         mVSIZOFF.Byte.Low=data;
         mVSIZOFF.Byte.High=0;
         break;
      case (VSIZOFFH&0xff):
         mVSIZOFF.Byte.High=data;
         break;
      case (SCBADRL&0xff):
         mSCBADR.Byte.Low=data;
         mSCBADR.Byte.High=0;
         break;
      case (SCBADRH&0xff):
         mSCBADR.Byte.High=data;
         break;
      case (PROCADRL&0xff):
         mPROCADR.Byte.Low=data;
         mPROCADR.Byte.High=0;
         break;
      case (PROCADRH&0xff):
         mPROCADR.Byte.High=data;
         break;

      case (MATHD&0xff):
         mMATHABCD.Bytes.D=data;
         //			mMATHABCD.Bytes.C=0;
         // The hardware manual says that the sign shouldnt change
         // but if I dont do this then stun runner will hang as it
         // does the init in the wrong order and if the previous
         // calc left a zero there then we'll get a sign error
         Poke(MATHC,0);
         break;
      case (MATHC&0xff):
         mMATHABCD.Bytes.C=data;
         // Perform sign conversion if required
         if(mSPRSYS_SignedMath) {
            // Account for the math bug that 0x8000 is +ve & 0x0000 is -ve by subracting 1
            if((mMATHABCD.Words.CD-1)&0x8000) {
               UWORD conv;
               conv=mMATHABCD.Words.CD^0xffff;
               conv++;
               mMATHCD_sign=-1;
               mMATHABCD.Words.CD=conv;
            } else {
               mMATHCD_sign=1;
            }
         }
         break;
      case (MATHB&0xff):
         mMATHABCD.Bytes.B=data;
         mMATHABCD.Bytes.A=0;
         break;
      case (MATHA&0xff):
         mMATHABCD.Bytes.A=data;
         // Perform sign conversion if required
         if(mSPRSYS_SignedMath) {
            // Account for the math bug that 0x8000 is +ve & 0x0000 is -ve by subracting 1
            if((mMATHABCD.Words.AB-1)&0x8000) {
               UWORD conv;
               conv=mMATHABCD.Words.AB^0xffff;
               conv++;
               mMATHAB_sign=-1;
               mMATHABCD.Words.AB=conv;
            } else {
               mMATHAB_sign=1;
            }
         }
         DoMathMultiply();
         break;

      case (MATHP&0xff):
         mMATHNP.Bytes.P=data;
         mMATHNP.Bytes.N=0;
         break;
      case (MATHN&0xff):
         mMATHNP.Bytes.N=data;
         break;

      case (MATHH&0xff):
         mMATHEFGH.Bytes.H=data;
         mMATHEFGH.Bytes.G=0;
         break;
      case (MATHG&0xff):
         mMATHEFGH.Bytes.G=data;
         break;
      case (MATHF&0xff):
         mMATHEFGH.Bytes.F=data;
         mMATHEFGH.Bytes.E=0;
         break;
      case (MATHE&0xff):
         mMATHEFGH.Bytes.E=data;
         DoMathDivide();
         break;

      case (MATHM&0xff):
         mMATHJKLM.Bytes.M=data;
         mMATHJKLM.Bytes.L=0;
         mSPRSYS_Mathbit=FALSE;
         break;
      case (MATHL&0xff):
         mMATHJKLM.Bytes.L=data;
         break;
      case (MATHK&0xff):
         mMATHJKLM.Bytes.K=data;
         mMATHJKLM.Bytes.J=0;
         break;
      case (MATHJ&0xff):
         mMATHJKLM.Bytes.J=data;
         break;

      case (SPRCTL0&0xff):
         mSPRCTL0_Type=data&0x0007;
         mSPRCTL0_Vflip=data&0x0010;
         mSPRCTL0_Hflip=data&0x0020;
         mSPRCTL0_PixelBits=((data&0x00c0)>>6)+1;
         break;
      case (SPRCTL1&0xff):
         mSPRCTL1_StartLeft=data&0x0001;
         mSPRCTL1_StartUp=data&0x0002;
         mSPRCTL1_SkipSprite=data&0x0004;
         mSPRCTL1_ReloadPalette=data&0x0008;
         mSPRCTL1_ReloadDepth=(data&0x0030)>>4;
         mSPRCTL1_Sizing=data&0x0040;
         mSPRCTL1_Literal=data&0x0080;
         break;
      case (SPRCOLL&0xff):
         mSPRCOLL_Number=data&0x000f;
         mSPRCOLL_Collide=data&0x0020;
         break;
      case (SPRINIT&0xff):
         mSPRINIT.Byte=data;
         break;
      case (SUZYBUSEN&0xff):
         mSUZYBUSEN=data&0x01;
         break;
      case (SPRGO&0xff):
         mSPRGO=data&0x01;
         mEVERON=data&0x04;
         break;
      case (SPRSYS&0xff):
         mSPRSYS_StopOnCurrent=data&0x0002;
         if(data&0x0004) mSPRSYS_UnsafeAccess=0;
         mSPRSYS_LeftHand=data&0x0008;
         mSPRSYS_VStretch=data&0x0010;
         mSPRSYS_NoCollide=data&0x0020;
         mSPRSYS_Accumulate=data&0x0040;
         mSPRSYS_SignedMath=data&0x0080;
         break;

         // Cartridge writing ports

      case (RCART0&0xff):
         if(mSystem.mCart->CartGetAudin() && mSystem.mMikie->SwitchAudInValue()){
           mSystem.Poke_CARTB0A(data);
         }else{
           mSystem.Poke_CARTB0(data);
         }
         mSystem.mEEPROM->ProcessEepromCounter(mSystem.mCart->GetCounterValue());
         break;
      case (RCART1&0xff):
        if(mSystem.mCart->CartGetAudin() && mSystem.mMikie->SwitchAudInValue()){
           mSystem.Poke_CARTB1A(data);
        }else{
            mSystem.Poke_CARTB1(data);
         }
         mSystem.mEEPROM->ProcessEepromCounter(mSystem.mCart->GetCounterValue());
         break;

         // These are not so important, so lets ignore them for the moment

      case (LEDS&0xff):
      case (PPORTSTAT&0xff):
      case (PPORTDATA&0xff):
      case (HOWIE&0xff):
         break;

         // Errors on read only register accesses

      case (SUZYHREV&0xff):
      case (JOYSTICK&0xff):
      case (SWITCHES&0xff):
         break;

         // Errors on illegal location accesses

      default:
         break;
   }
}

UBYTE CSusie::Peek(ULONG addr)
{
   UBYTE	retval=0;
   switch(addr&0xff) {
      case (TMPADRL&0xff):
         retval=mTMPADR.Byte.Low;
         return retval;
      case (TMPADRH&0xff):
         retval=mTMPADR.Byte.High;
         return retval;
      case (TILTACUML&0xff):
         retval=mTILTACUM.Byte.Low;
         return retval;
      case (TILTACUMH&0xff):
         retval=mTILTACUM.Byte.High;
         return retval;
      case (HOFFL&0xff):
         retval=mHOFF.Byte.Low;
         return retval;
      case (HOFFH&0xff):
         retval=mHOFF.Byte.High;
         return retval;
      case (VOFFL&0xff):
         retval=mVOFF.Byte.Low;
         return retval;
      case (VOFFH&0xff):
         retval=mVOFF.Byte.High;
         return retval;
      case (VIDBASL&0xff):
         retval=mVIDBAS.Byte.Low;
         return retval;
      case (VIDBASH&0xff):
         retval=mVIDBAS.Byte.High;
         return retval;
      case (COLLBASL&0xff):
         retval=mCOLLBAS.Byte.Low;
         return retval;
      case (COLLBASH&0xff):
         retval=mCOLLBAS.Byte.High;
         return retval;
      case (VIDADRL&0xff):
         retval=mVIDADR.Byte.Low;
         return retval;
      case (VIDADRH&0xff):
         retval=mVIDADR.Byte.High;
         return retval;
      case (COLLADRL&0xff):
         retval=mCOLLADR.Byte.Low;
         return retval;
      case (COLLADRH&0xff):
         retval=mCOLLADR.Byte.High;
         return retval;
      case (SCBNEXTL&0xff):
         retval=mSCBNEXT.Byte.Low;
         return retval;
      case (SCBNEXTH&0xff):
         retval=mSCBNEXT.Byte.High;
         return retval;
      case (SPRDLINEL&0xff):
         retval=mSPRDLINE.Byte.Low;
         return retval;
      case (SPRDLINEH&0xff):
         retval=mSPRDLINE.Byte.High;
         return retval;
      case (HPOSSTRTL&0xff):
         retval=mHPOSSTRT.Byte.Low;
         return retval;
      case (HPOSSTRTH&0xff):
         retval=mHPOSSTRT.Byte.High;
         return retval;
      case (VPOSSTRTL&0xff):
         retval=mVPOSSTRT.Byte.Low;
         return retval;
      case (VPOSSTRTH&0xff):
         retval=mVPOSSTRT.Byte.High;
         return retval;
      case (SPRHSIZL&0xff):
         retval=mSPRHSIZ.Byte.Low;
         return retval;
      case (SPRHSIZH&0xff):
         retval=mSPRHSIZ.Byte.High;
         return retval;
      case (SPRVSIZL&0xff):
         retval=mSPRVSIZ.Byte.Low;
         return retval;
      case (SPRVSIZH&0xff):
         retval=mSPRVSIZ.Byte.High;
         return retval;
      case (STRETCHL&0xff):
         retval=mSTRETCH.Byte.Low;
         return retval;
      case (STRETCHH&0xff):
         retval=mSTRETCH.Byte.High;
         return retval;
      case (TILTL&0xff):
         retval=mTILT.Byte.Low;
         return retval;
      case (TILTH&0xff):
         retval=mTILT.Byte.High;
         return retval;
      case (SPRDOFFL&0xff):
         retval=mSPRDOFF.Byte.Low;
         return retval;
      case (SPRDOFFH&0xff):
         retval=mSPRDOFF.Byte.High;
         return retval;
      case (SPRVPOSL&0xff):
         retval=mSPRVPOS.Byte.Low;
         return retval;
      case (SPRVPOSH&0xff):
         retval=mSPRVPOS.Byte.High;
         return retval;
      case (COLLOFFL&0xff):
         retval=mCOLLOFF.Byte.Low;
         return retval;
      case (COLLOFFH&0xff):
         retval=mCOLLOFF.Byte.High;
         return retval;
      case (VSIZACUML&0xff):
         retval=mVSIZACUM.Byte.Low;
         return retval;
      case (VSIZACUMH&0xff):
         retval=mVSIZACUM.Byte.High;
         return retval;
      case (HSIZOFFL&0xff):
         retval=mHSIZOFF.Byte.Low;
         return retval;
      case (HSIZOFFH&0xff):
         retval=mHSIZOFF.Byte.High;
         return retval;
      case (VSIZOFFL&0xff):
         retval=mVSIZOFF.Byte.Low;
         return retval;
      case (VSIZOFFH&0xff):
         retval=mVSIZOFF.Byte.High;
         return retval;
      case (SCBADRL&0xff):
         retval=mSCBADR.Byte.Low;
         return retval;
      case (SCBADRH&0xff):
         retval=mSCBADR.Byte.High;
         return retval;
      case (PROCADRL&0xff):
         retval=mPROCADR.Byte.Low;
         return retval;
      case (PROCADRH&0xff):
         retval=mPROCADR.Byte.High;
         return retval;
      case (MATHD&0xff):
         retval=mMATHABCD.Bytes.D;
         return retval;
      case (MATHC&0xff):
         retval=mMATHABCD.Bytes.C;
         return retval;
      case (MATHB&0xff):
         retval=mMATHABCD.Bytes.B;
         return retval;
      case (MATHA&0xff):
         retval=mMATHABCD.Bytes.A;
         return retval;

      case (MATHP&0xff):
         retval=mMATHNP.Bytes.P;
         return retval;
      case (MATHN&0xff):
         retval=mMATHNP.Bytes.N;
         return retval;

      case (MATHH&0xff):
         retval=mMATHEFGH.Bytes.H;
         return retval;
      case (MATHG&0xff):
         retval=mMATHEFGH.Bytes.G;
         return retval;
      case (MATHF&0xff):
         retval=mMATHEFGH.Bytes.F;
         return retval;
      case (MATHE&0xff):
         retval=mMATHEFGH.Bytes.E;
         return retval;
      case (MATHM&0xff):
         retval=mMATHJKLM.Bytes.M;
         return retval;
      case (MATHL&0xff):
         retval=mMATHJKLM.Bytes.L;
         return retval;
      case (MATHK&0xff):
         retval=mMATHJKLM.Bytes.K;
         return retval;
      case (MATHJ&0xff):
         retval=mMATHJKLM.Bytes.J;
         return retval;
      case (SUZYHREV&0xff):
         retval=0x01;
         return retval;

      case (SPRSYS&0xff):
         retval=0x0000;
         //	retval+=(mSPRSYS_Status)?0x0001:0x0000;
         // Use gSystemCPUSleep to signal the status instead, if we are asleep then
         // we must be rendering sprites
         retval+=(gSystemCPUSleep)?0x0001:0x0000;
         retval+=(mSPRSYS_StopOnCurrent)?0x0002:0x0000;
         retval+=(mSPRSYS_UnsafeAccess)?0x0004:0x0000;
         retval+=(mSPRSYS_LeftHand)?0x0008:0x0000;
         retval+=(mSPRSYS_VStretch)?0x0010:0x0000;
         retval+=(mSPRSYS_LastCarry)?0x0020:0x0000;
         retval+=(mSPRSYS_Mathbit)?0x0040:0x0000;
         retval+=(mSPRSYS_MathInProgress)?0x0080:0x0000;
         return retval;

      case (JOYSTICK&0xff):
         if(mSPRSYS_LeftHand) {
            retval= mJOYSTICK.Byte;
         } else {
            TJOYSTICK Modified=mJOYSTICK;
            Modified.Bits.Left=mJOYSTICK.Bits.Right;
            Modified.Bits.Right=mJOYSTICK.Bits.Left;
            Modified.Bits.Down=mJOYSTICK.Bits.Up;
            Modified.Bits.Up=mJOYSTICK.Bits.Down;
            retval= Modified.Byte;
         }
         return retval;

      case (SWITCHES&0xff):
         retval=mSWITCHES.Byte;
         return retval;

         // Cartridge reading ports

      case (RCART0&0xff):
         if(mSystem.mCart->CartGetAudin() && mSystem.mMikie->SwitchAudInValue()){
            retval=mSystem.Peek_CARTB0A();
         }else{
            retval=mSystem.Peek_CARTB0();
         }
         mSystem.mEEPROM->ProcessEepromCounter(mSystem.mCart->GetCounterValue());
         return retval;
      case (RCART1&0xff):
         if(mSystem.mCart->CartGetAudin() && mSystem.mMikie->SwitchAudInValue()){
            retval=mSystem.Peek_CARTB1A();
         }else{
           retval=mSystem.Peek_CARTB1();
         }
         mSystem.mEEPROM->ProcessEepromCounter(mSystem.mCart->GetCounterValue());
         return retval;

         // These are no so important so lets ignore them for the moment

      case (LEDS&0xff):
      case (PPORTSTAT&0xff):
      case (PPORTDATA&0xff):
      case (HOWIE&0xff):
         break;

         // Errors on write only register accesses

      case (SPRCTL0&0xff):
      case (SPRCTL1&0xff):
      case (SPRCOLL&0xff):
      case (SPRINIT&0xff):
      case (SUZYBUSEN&0xff):
      case (SPRGO&0xff):
         break;

         // Errors on illegal location accesses

      default:
         break;
   }

   return 0xff;
}
