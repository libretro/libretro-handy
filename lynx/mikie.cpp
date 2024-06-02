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
// Mikey chip emulation class                                               //
//////////////////////////////////////////////////////////////////////////////
//                                                                          //
// This class emulates all of the Mikey hardware with the exception of the  //
// CPU and memory selector. Update() does most of the work and does screen  //
// DMA and counter updates, it also schecules in which cycle the next timer //
// update will occur so that the CSystem->Update() doesnt have to call it   //
// every cycle, massive speedup but big complexity headache.                //
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

#define MIKIE_CPP

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "system.h"
#include "mikie.h"
#include "lynxdef.h"
#include "handy.h"

void CMikie::BlowOut(void)
{
   char addr[100];
   C6502_REGS regs;
   mSystem.GetRegs(regs);
   sprintf(addr,"Runtime Error - System Halted\nCMikie::Poke() - Read/Write to counter clocks at PC=$%04x.",regs.PC);
   if(gError) gError->Warning(addr);
   gSystemHalt=TRUE;
}


   CMikie::CMikie(CSystem& parent)
:mSystem(parent)
{

   mpDisplayBits=NULL;
   mpDisplayCurrent=NULL;
   mpRamPointer=NULL;

   mDisplayRotate=MIKIE_BAD_MODE;
   mDisplayFormat=MIKIE_PIXEL_FORMAT_16BPP_555;
   mpDisplayCallback=NULL;
   mDisplayCallbackObject=0;

   mUART_CABLE_PRESENT=FALSE;
   mpUART_TX_CALLBACK=NULL;

   int loop;
   for(loop=0;loop<16;loop++) mPalette[loop].Index=loop;
   for(loop=0;loop<4096;loop++) mColourMap[loop]=0;

   mikbuf.set_sample_rate(HANDY_AUDIO_SAMPLE_FREQ, 60);
   mikbuf.clock_rate(HANDY_SYSTEM_FREQ / 4);
   mikbuf.bass_freq(60);
   miksynth.volume(0.50);
   miksynth.treble_eq(0);
	
   Reset();
}

CMikie::~CMikie()
{
}


void CMikie::Reset(void)
{
   mAudioInputComparator=FALSE;	// Initialises to unknown
   mDisplayAddress=0x00;			// Initialises to unknown
   mLynxLine=0;
   mLynxLineDMACounter=0;
   mLynxAddr=0;

   mTimerStatusFlags=0x00;		// Initialises to ZERO, i.e No IRQ's
   mTimerInterruptMask=0x00;

   mpRamPointer=mSystem.GetRamPointer();	// Fetch pointer to system RAM

   mTIM_0_BKUP=0;
   mTIM_0_ENABLE_RELOAD=0;
   mTIM_0_ENABLE_COUNT=0;
   mTIM_0_LINKING=0;
   mTIM_0_CURRENT=0;
   mTIM_0_TIMER_DONE=0;
   mTIM_0_LAST_CLOCK=0;
   mTIM_0_BORROW_IN=0;
   mTIM_0_BORROW_OUT=0;
   mTIM_0_LAST_LINK_CARRY=0;
   mTIM_0_LAST_COUNT=0;

   mTIM_1_BKUP=0;
   mTIM_1_ENABLE_RELOAD=0;
   mTIM_1_ENABLE_COUNT=0;
   mTIM_1_LINKING=0;
   mTIM_1_CURRENT=0;
   mTIM_1_TIMER_DONE=0;
   mTIM_1_LAST_CLOCK=0;
   mTIM_1_BORROW_IN=0;
   mTIM_1_BORROW_OUT=0;
   mTIM_1_LAST_LINK_CARRY=0;
   mTIM_1_LAST_COUNT=0;

   mTIM_2_BKUP=0;
   mTIM_2_ENABLE_RELOAD=0;
   mTIM_2_ENABLE_COUNT=0;
   mTIM_2_LINKING=0;
   mTIM_2_CURRENT=0;
   mTIM_2_TIMER_DONE=0;
   mTIM_2_LAST_CLOCK=0;
   mTIM_2_BORROW_IN=0;
   mTIM_2_BORROW_OUT=0;
   mTIM_2_LAST_LINK_CARRY=0;
   mTIM_2_LAST_COUNT=0;

   mTIM_3_BKUP=0;
   mTIM_3_ENABLE_RELOAD=0;
   mTIM_3_ENABLE_COUNT=0;
   mTIM_3_LINKING=0;
   mTIM_3_CURRENT=0;
   mTIM_3_TIMER_DONE=0;
   mTIM_3_LAST_CLOCK=0;
   mTIM_3_BORROW_IN=0;
   mTIM_3_BORROW_OUT=0;
   mTIM_3_LAST_LINK_CARRY=0;
   mTIM_3_LAST_COUNT=0;

   mTIM_4_BKUP=0;
   mTIM_4_ENABLE_RELOAD=0;
   mTIM_4_ENABLE_COUNT=0;
   mTIM_4_LINKING=0;
   mTIM_4_CURRENT=0;
   mTIM_4_TIMER_DONE=0;
   mTIM_4_LAST_CLOCK=0;
   mTIM_4_BORROW_IN=0;
   mTIM_4_BORROW_OUT=0;
   mTIM_4_LAST_LINK_CARRY=0;
   mTIM_4_LAST_COUNT=0;

   mTIM_5_BKUP=0;
   mTIM_5_ENABLE_RELOAD=0;
   mTIM_5_ENABLE_COUNT=0;
   mTIM_5_LINKING=0;
   mTIM_5_CURRENT=0;
   mTIM_5_TIMER_DONE=0;
   mTIM_5_LAST_CLOCK=0;
   mTIM_5_BORROW_IN=0;
   mTIM_5_BORROW_OUT=0;
   mTIM_5_LAST_LINK_CARRY=0;
   mTIM_5_LAST_COUNT=0;

   mTIM_6_BKUP=0;
   mTIM_6_ENABLE_RELOAD=0;
   mTIM_6_ENABLE_COUNT=0;
   mTIM_6_LINKING=0;
   mTIM_6_CURRENT=0;
   mTIM_6_TIMER_DONE=0;
   mTIM_6_LAST_CLOCK=0;
   mTIM_6_BORROW_IN=0;
   mTIM_6_BORROW_OUT=0;
   mTIM_6_LAST_LINK_CARRY=0;
   mTIM_6_LAST_COUNT=0;

   mTIM_7_BKUP=0;
   mTIM_7_ENABLE_RELOAD=0;
   mTIM_7_ENABLE_COUNT=0;
   mTIM_7_LINKING=0;
   mTIM_7_CURRENT=0;
   mTIM_7_TIMER_DONE=0;
   mTIM_7_LAST_CLOCK=0;
   mTIM_7_BORROW_IN=0;
   mTIM_7_BORROW_OUT=0;
   mTIM_7_LAST_LINK_CARRY=0;
   mTIM_7_LAST_COUNT=0;

   mAUDIO_0_BKUP=0;
   mAUDIO_0_ENABLE_RELOAD=0;
   mAUDIO_0_ENABLE_COUNT=0;
   mAUDIO_0_LINKING=0;
   mAUDIO_0_CURRENT=0;
   mAUDIO_0_TIMER_DONE=0;
   mAUDIO_0_LAST_CLOCK=0;
   mAUDIO_0_BORROW_IN=0;
   mAUDIO_0_BORROW_OUT=0;
   mAUDIO_0_LAST_LINK_CARRY=0;
   mAUDIO_0_LAST_COUNT=0;
   mAUDIO_0_VOLUME=0;
   mAUDIO_OUTPUT[0]=0;
   mAUDIO_0_INTEGRATE_ENABLE=0;
   mAUDIO_0_WAVESHAPER=0;

   mAUDIO_1_BKUP=0;
   mAUDIO_1_ENABLE_RELOAD=0;
   mAUDIO_1_ENABLE_COUNT=0;
   mAUDIO_1_LINKING=0;
   mAUDIO_1_CURRENT=0;
   mAUDIO_1_TIMER_DONE=0;
   mAUDIO_1_LAST_CLOCK=0;
   mAUDIO_1_BORROW_IN=0;
   mAUDIO_1_BORROW_OUT=0;
   mAUDIO_1_LAST_LINK_CARRY=0;
   mAUDIO_1_LAST_COUNT=0;
   mAUDIO_1_VOLUME=0;
   mAUDIO_OUTPUT[1]=0;
   mAUDIO_1_INTEGRATE_ENABLE=0;
   mAUDIO_1_WAVESHAPER=0;

   mAUDIO_2_BKUP=0;
   mAUDIO_2_ENABLE_RELOAD=0;
   mAUDIO_2_ENABLE_COUNT=0;
   mAUDIO_2_LINKING=0;
   mAUDIO_2_CURRENT=0;
   mAUDIO_2_TIMER_DONE=0;
   mAUDIO_2_LAST_CLOCK=0;
   mAUDIO_2_BORROW_IN=0;
   mAUDIO_2_BORROW_OUT=0;
   mAUDIO_2_LAST_LINK_CARRY=0;
   mAUDIO_2_LAST_COUNT=0;
   mAUDIO_2_VOLUME=0;
   mAUDIO_OUTPUT[2]=0;
   mAUDIO_2_INTEGRATE_ENABLE=0;
   mAUDIO_2_WAVESHAPER=0;

   mAUDIO_3_BKUP=0;
   mAUDIO_3_ENABLE_RELOAD=0;
   mAUDIO_3_ENABLE_COUNT=0;
   mAUDIO_3_LINKING=0;
   mAUDIO_3_CURRENT=0;
   mAUDIO_3_TIMER_DONE=0;
   mAUDIO_3_LAST_CLOCK=0;
   mAUDIO_3_BORROW_IN=0;
   mAUDIO_3_BORROW_OUT=0;
   mAUDIO_3_LAST_LINK_CARRY=0;
   mAUDIO_3_LAST_COUNT=0;
   mAUDIO_3_VOLUME=0;
   mAUDIO_OUTPUT[3]=0;
   mAUDIO_3_INTEGRATE_ENABLE=0;
   mAUDIO_3_WAVESHAPER=0;

   mSTEREO=0x00;	// xored! All channels enabled
   mPAN=0x00;      // all channels panning OFF
   mAUDIO_ATTEN[0]=0xff; // Full volume
   mAUDIO_ATTEN[1]=0xff;
   mAUDIO_ATTEN[2]=0xff;
   mAUDIO_ATTEN[3]=0xff;

   // Start with an empty palette

   for(int loop=0;loop<16;loop++) {
      mPalette[loop].Index=loop;
   }

   // Initialise IODAT register

   mIODAT=0x00;
   mIODIR=0x00;
   mIODAT_REST_SIGNAL=0x00;

   //
   // Initialise display control register vars
   //
   mDISPCTL_DMAEnable=FALSE;
   mDISPCTL_Flip=FALSE;
   mDISPCTL_FourColour=0;
   mDISPCTL_Colour=0;

   //
   // Initialise the UART variables
   //
   mUART_RX_IRQ_ENABLE=0;
   mUART_TX_IRQ_ENABLE=0;

   mUART_TX_COUNTDOWN=UART_TX_INACTIVE;
   mUART_RX_COUNTDOWN=UART_RX_INACTIVE;

   mUART_Rx_input_ptr=0;
   mUART_Rx_output_ptr=0;
   mUART_Rx_waiting=0;
   mUART_Rx_framing_error=0;
   mUART_Rx_overun_error=0;

   mUART_SENDBREAK=0;
   mUART_TX_DATA=0;
   mUART_RX_DATA=0;
   mUART_RX_READY=0;

   mUART_PARITY_ENABLE=0;
   mUART_PARITY_EVEN=0;
}

ULONG CMikie::GetLfsrNext(ULONG current)
{
   // The table is built thus:
   //	Bits 0-11  LFSR					(12 Bits)
   //  Bits 12-20 Feedback switches	(9 Bits)
   //     (Order = 7,0,1,2,3,4,5,10,11)
   //  Order is mangled to make peek/poke easier as
   //  bit 7 is in a seperate register
   //
   // Total 21 bits = 2MWords @ 4 Bytes/Word = 8MB !!!!!
   //
   // If the index is a combination of Current LFSR+Feedback the
   // table will give the next value.

   static ULONG switches,lfsr,next,swloop,result;
   static const ULONG switchbits[9]={7,0,1,2,3,4,5,10,11};

   switches=current>>12;
   lfsr=current&0xfff;
   result=0;
   for(swloop=0;swloop<9;swloop++) {
      if((switches>>swloop)&0x001) result^=(lfsr>>switchbits[swloop])&0x001;
   }
   result=(result)?0:1;
   next=(switches<<12)|((lfsr<<1)&0xffe)|result;
   return next;
}

bool CMikie::ContextSave(LSS_FILE *fp)
{
   if(!lss_printf(fp,"CMikie::ContextSave")) return 0;

   if(!lss_write(&mDisplayAddress,sizeof(ULONG),1,fp)) return 0;
   if(!lss_write(&mAudioInputComparator,sizeof(ULONG),1,fp)) return 0;
   if(!lss_write(&mTimerStatusFlags,sizeof(ULONG),1,fp)) return 0;
   if(!lss_write(&mTimerInterruptMask,sizeof(ULONG),1,fp)) return 0;
   
   if(!lss_write(mPalette,sizeof(TPALETTE),16,fp)) return 0;
   
   if(!lss_write(&mIODAT,sizeof(ULONG),1,fp)) return 0;
   if(!lss_write(&mIODAT_REST_SIGNAL,sizeof(ULONG),1,fp)) return 0;
   if(!lss_write(&mIODIR,sizeof(ULONG),1,fp)) return 0;
   
   if(!lss_write(&mDISPCTL_DMAEnable,sizeof(ULONG),1,fp)) return 0;
   if(!lss_write(&mDISPCTL_Flip,sizeof(ULONG),1,fp)) return 0;
   if(!lss_write(&mDISPCTL_FourColour,sizeof(ULONG),1,fp)) return 0;
   if(!lss_write(&mDISPCTL_Colour,sizeof(ULONG),1,fp)) return 0;

   if(!lss_write(&mTIM_0_BKUP,sizeof(ULONG),1,fp)) return 0;
   if(!lss_write(&mTIM_0_ENABLE_RELOAD,sizeof(ULONG),1,fp)) return 0;
   if(!lss_write(&mTIM_0_ENABLE_COUNT,sizeof(ULONG),1,fp)) return 0;
   if(!lss_write(&mTIM_0_LINKING,sizeof(ULONG),1,fp)) return 0;
   if(!lss_write(&mTIM_0_CURRENT,sizeof(ULONG),1,fp)) return 0;
   if(!lss_write(&mTIM_0_TIMER_DONE,sizeof(ULONG),1,fp)) return 0;
   if(!lss_write(&mTIM_0_LAST_CLOCK,sizeof(ULONG),1,fp)) return 0;
   if(!lss_write(&mTIM_0_BORROW_IN,sizeof(ULONG),1,fp)) return 0;
   if(!lss_write(&mTIM_0_BORROW_OUT,sizeof(ULONG),1,fp)) return 0;
   if(!lss_write(&mTIM_0_LAST_LINK_CARRY,sizeof(ULONG),1,fp)) return 0;
   if(!lss_write(&mTIM_0_LAST_COUNT,sizeof(ULONG),1,fp)) return 0;

   if(!lss_write(&mTIM_1_BKUP,sizeof(ULONG),1,fp)) return 0;
   if(!lss_write(&mTIM_1_ENABLE_RELOAD,sizeof(ULONG),1,fp)) return 0;
   if(!lss_write(&mTIM_1_ENABLE_COUNT,sizeof(ULONG),1,fp)) return 0;
   if(!lss_write(&mTIM_1_LINKING,sizeof(ULONG),1,fp)) return 0;
   if(!lss_write(&mTIM_1_CURRENT,sizeof(ULONG),1,fp)) return 0;
   if(!lss_write(&mTIM_1_TIMER_DONE,sizeof(ULONG),1,fp)) return 0;
   if(!lss_write(&mTIM_1_LAST_CLOCK,sizeof(ULONG),1,fp)) return 0;
   if(!lss_write(&mTIM_1_BORROW_IN,sizeof(ULONG),1,fp)) return 0;
   if(!lss_write(&mTIM_1_BORROW_OUT,sizeof(ULONG),1,fp)) return 0;
   if(!lss_write(&mTIM_1_LAST_LINK_CARRY,sizeof(ULONG),1,fp)) return 0;
   if(!lss_write(&mTIM_1_LAST_COUNT,sizeof(ULONG),1,fp)) return 0;

   if(!lss_write(&mTIM_2_BKUP,sizeof(ULONG),1,fp)) return 0;
   if(!lss_write(&mTIM_2_ENABLE_RELOAD,sizeof(ULONG),1,fp)) return 0;
   if(!lss_write(&mTIM_2_ENABLE_COUNT,sizeof(ULONG),1,fp)) return 0;
   if(!lss_write(&mTIM_2_LINKING,sizeof(ULONG),1,fp)) return 0;
   if(!lss_write(&mTIM_2_CURRENT,sizeof(ULONG),1,fp)) return 0;
   if(!lss_write(&mTIM_2_TIMER_DONE,sizeof(ULONG),1,fp)) return 0;
   if(!lss_write(&mTIM_2_LAST_CLOCK,sizeof(ULONG),1,fp)) return 0;
   if(!lss_write(&mTIM_2_BORROW_IN,sizeof(ULONG),1,fp)) return 0;
   if(!lss_write(&mTIM_2_BORROW_OUT,sizeof(ULONG),1,fp)) return 0;
   if(!lss_write(&mTIM_2_LAST_LINK_CARRY,sizeof(ULONG),1,fp)) return 0;
   if(!lss_write(&mTIM_2_LAST_COUNT,sizeof(ULONG),1,fp)) return 0;

   if(!lss_write(&mTIM_3_BKUP,sizeof(ULONG),1,fp)) return 0;
   if(!lss_write(&mTIM_3_ENABLE_RELOAD,sizeof(ULONG),1,fp)) return 0;
   if(!lss_write(&mTIM_3_ENABLE_COUNT,sizeof(ULONG),1,fp)) return 0;
   if(!lss_write(&mTIM_3_LINKING,sizeof(ULONG),1,fp)) return 0;
   if(!lss_write(&mTIM_3_CURRENT,sizeof(ULONG),1,fp)) return 0;
   if(!lss_write(&mTIM_3_TIMER_DONE,sizeof(ULONG),1,fp)) return 0;
   if(!lss_write(&mTIM_3_LAST_CLOCK,sizeof(ULONG),1,fp)) return 0;
   if(!lss_write(&mTIM_3_BORROW_IN,sizeof(ULONG),1,fp)) return 0;
   if(!lss_write(&mTIM_3_BORROW_OUT,sizeof(ULONG),1,fp)) return 0;
   if(!lss_write(&mTIM_3_LAST_LINK_CARRY,sizeof(ULONG),1,fp)) return 0;
   if(!lss_write(&mTIM_3_LAST_COUNT,sizeof(ULONG),1,fp)) return 0;

   if(!lss_write(&mTIM_4_BKUP,sizeof(ULONG),1,fp)) return 0;
   if(!lss_write(&mTIM_4_ENABLE_RELOAD,sizeof(ULONG),1,fp)) return 0;
   if(!lss_write(&mTIM_4_ENABLE_COUNT,sizeof(ULONG),1,fp)) return 0;
   if(!lss_write(&mTIM_4_LINKING,sizeof(ULONG),1,fp)) return 0;
   if(!lss_write(&mTIM_4_CURRENT,sizeof(ULONG),1,fp)) return 0;
   if(!lss_write(&mTIM_4_TIMER_DONE,sizeof(ULONG),1,fp)) return 0;
   if(!lss_write(&mTIM_4_LAST_CLOCK,sizeof(ULONG),1,fp)) return 0;
   if(!lss_write(&mTIM_4_BORROW_IN,sizeof(ULONG),1,fp)) return 0;
   if(!lss_write(&mTIM_4_BORROW_OUT,sizeof(ULONG),1,fp)) return 0;
   if(!lss_write(&mTIM_4_LAST_LINK_CARRY,sizeof(ULONG),1,fp)) return 0;
   if(!lss_write(&mTIM_4_LAST_COUNT,sizeof(ULONG),1,fp)) return 0;

   if(!lss_write(&mTIM_5_BKUP,sizeof(ULONG),1,fp)) return 0;
   if(!lss_write(&mTIM_5_ENABLE_RELOAD,sizeof(ULONG),1,fp)) return 0;
   if(!lss_write(&mTIM_5_ENABLE_COUNT,sizeof(ULONG),1,fp)) return 0;
   if(!lss_write(&mTIM_5_LINKING,sizeof(ULONG),1,fp)) return 0;
   if(!lss_write(&mTIM_5_CURRENT,sizeof(ULONG),1,fp)) return 0;
   if(!lss_write(&mTIM_5_TIMER_DONE,sizeof(ULONG),1,fp)) return 0;
   if(!lss_write(&mTIM_5_LAST_CLOCK,sizeof(ULONG),1,fp)) return 0;
   if(!lss_write(&mTIM_5_BORROW_IN,sizeof(ULONG),1,fp)) return 0;
   if(!lss_write(&mTIM_5_BORROW_OUT,sizeof(ULONG),1,fp)) return 0;
   if(!lss_write(&mTIM_5_LAST_LINK_CARRY,sizeof(ULONG),1,fp)) return 0;
   if(!lss_write(&mTIM_5_LAST_COUNT,sizeof(ULONG),1,fp)) return 0;

   if(!lss_write(&mTIM_6_BKUP,sizeof(ULONG),1,fp)) return 0;
   if(!lss_write(&mTIM_6_ENABLE_RELOAD,sizeof(ULONG),1,fp)) return 0;
   if(!lss_write(&mTIM_6_ENABLE_COUNT,sizeof(ULONG),1,fp)) return 0;
   if(!lss_write(&mTIM_6_LINKING,sizeof(ULONG),1,fp)) return 0;
   if(!lss_write(&mTIM_6_CURRENT,sizeof(ULONG),1,fp)) return 0;
   if(!lss_write(&mTIM_6_TIMER_DONE,sizeof(ULONG),1,fp)) return 0;
   if(!lss_write(&mTIM_6_LAST_CLOCK,sizeof(ULONG),1,fp)) return 0;
   if(!lss_write(&mTIM_6_BORROW_IN,sizeof(ULONG),1,fp)) return 0;
   if(!lss_write(&mTIM_6_BORROW_OUT,sizeof(ULONG),1,fp)) return 0;
   if(!lss_write(&mTIM_6_LAST_LINK_CARRY,sizeof(ULONG),1,fp)) return 0;
   if(!lss_write(&mTIM_6_LAST_COUNT,sizeof(ULONG),1,fp)) return 0;

   if(!lss_write(&mTIM_7_BKUP,sizeof(ULONG),1,fp)) return 0;
   if(!lss_write(&mTIM_7_ENABLE_RELOAD,sizeof(ULONG),1,fp)) return 0;
   if(!lss_write(&mTIM_7_ENABLE_COUNT,sizeof(ULONG),1,fp)) return 0;
   if(!lss_write(&mTIM_7_LINKING,sizeof(ULONG),1,fp)) return 0;
   if(!lss_write(&mTIM_7_CURRENT,sizeof(ULONG),1,fp)) return 0;
   if(!lss_write(&mTIM_7_TIMER_DONE,sizeof(ULONG),1,fp)) return 0;
   if(!lss_write(&mTIM_7_LAST_CLOCK,sizeof(ULONG),1,fp)) return 0;
   if(!lss_write(&mTIM_7_BORROW_IN,sizeof(ULONG),1,fp)) return 0;
   if(!lss_write(&mTIM_7_BORROW_OUT,sizeof(ULONG),1,fp)) return 0;
   if(!lss_write(&mTIM_7_LAST_LINK_CARRY,sizeof(ULONG),1,fp)) return 0;
   if(!lss_write(&mTIM_7_LAST_COUNT,sizeof(ULONG),1,fp)) return 0;

   if(!lss_write(&mAUDIO_0_BKUP,sizeof(ULONG),1,fp)) return 0;
   if(!lss_write(&mAUDIO_0_ENABLE_RELOAD,sizeof(ULONG),1,fp)) return 0;
   if(!lss_write(&mAUDIO_0_ENABLE_COUNT,sizeof(ULONG),1,fp)) return 0;
   if(!lss_write(&mAUDIO_0_LINKING,sizeof(ULONG),1,fp)) return 0;
   if(!lss_write(&mAUDIO_0_CURRENT,sizeof(ULONG),1,fp)) return 0;
   if(!lss_write(&mAUDIO_0_TIMER_DONE,sizeof(ULONG),1,fp)) return 0;
   if(!lss_write(&mAUDIO_0_LAST_CLOCK,sizeof(ULONG),1,fp)) return 0;
   if(!lss_write(&mAUDIO_0_BORROW_IN,sizeof(ULONG),1,fp)) return 0;
   if(!lss_write(&mAUDIO_0_BORROW_OUT,sizeof(ULONG),1,fp)) return 0;
   if(!lss_write(&mAUDIO_0_LAST_LINK_CARRY,sizeof(ULONG),1,fp)) return 0;
   if(!lss_write(&mAUDIO_0_LAST_COUNT,sizeof(ULONG),1,fp)) return 0;
   if(!lss_write(&mAUDIO_0_VOLUME,sizeof(int8_t),1,fp)) return 0;
   if(!lss_write(&mAUDIO_OUTPUT[0],sizeof(int8_t),1,fp)) return 0;
   if(!lss_write(&mAUDIO_0_INTEGRATE_ENABLE,sizeof(ULONG),1,fp)) return 0;
   if(!lss_write(&mAUDIO_0_WAVESHAPER,sizeof(ULONG),1,fp)) return 0;

   if(!lss_write(&mAUDIO_1_BKUP,sizeof(ULONG),1,fp)) return 0;
   if(!lss_write(&mAUDIO_1_ENABLE_RELOAD,sizeof(ULONG),1,fp)) return 0;
   if(!lss_write(&mAUDIO_1_ENABLE_COUNT,sizeof(ULONG),1,fp)) return 0;
   if(!lss_write(&mAUDIO_1_LINKING,sizeof(ULONG),1,fp)) return 0;
   if(!lss_write(&mAUDIO_1_CURRENT,sizeof(ULONG),1,fp)) return 0;
   if(!lss_write(&mAUDIO_1_TIMER_DONE,sizeof(ULONG),1,fp)) return 0;
   if(!lss_write(&mAUDIO_1_LAST_CLOCK,sizeof(ULONG),1,fp)) return 0;
   if(!lss_write(&mAUDIO_1_BORROW_IN,sizeof(ULONG),1,fp)) return 0;
   if(!lss_write(&mAUDIO_1_BORROW_OUT,sizeof(ULONG),1,fp)) return 0;
   if(!lss_write(&mAUDIO_1_LAST_LINK_CARRY,sizeof(ULONG),1,fp)) return 0;
   if(!lss_write(&mAUDIO_1_LAST_COUNT,sizeof(ULONG),1,fp)) return 0;
   if(!lss_write(&mAUDIO_1_VOLUME,sizeof(int8_t),1,fp)) return 0;
   if(!lss_write(&mAUDIO_OUTPUT[1],sizeof(int8_t),1,fp)) return 0;
   if(!lss_write(&mAUDIO_1_INTEGRATE_ENABLE,sizeof(ULONG),1,fp)) return 0;
   if(!lss_write(&mAUDIO_1_WAVESHAPER,sizeof(ULONG),1,fp)) return 0;

   if(!lss_write(&mAUDIO_2_BKUP,sizeof(ULONG),1,fp)) return 0;
   if(!lss_write(&mAUDIO_2_ENABLE_RELOAD,sizeof(ULONG),1,fp)) return 0;
   if(!lss_write(&mAUDIO_2_ENABLE_COUNT,sizeof(ULONG),1,fp)) return 0;
   if(!lss_write(&mAUDIO_2_LINKING,sizeof(ULONG),1,fp)) return 0;
   if(!lss_write(&mAUDIO_2_CURRENT,sizeof(ULONG),1,fp)) return 0;
   if(!lss_write(&mAUDIO_2_TIMER_DONE,sizeof(ULONG),1,fp)) return 0;
   if(!lss_write(&mAUDIO_2_LAST_CLOCK,sizeof(ULONG),1,fp)) return 0;
   if(!lss_write(&mAUDIO_2_BORROW_IN,sizeof(ULONG),1,fp)) return 0;
   if(!lss_write(&mAUDIO_2_BORROW_OUT,sizeof(ULONG),1,fp)) return 0;
   if(!lss_write(&mAUDIO_2_LAST_LINK_CARRY,sizeof(ULONG),1,fp)) return 0;
   if(!lss_write(&mAUDIO_2_LAST_COUNT,sizeof(ULONG),1,fp)) return 0;
   if(!lss_write(&mAUDIO_2_VOLUME,sizeof(int8_t),1,fp)) return 0;
   if(!lss_write(&mAUDIO_OUTPUT[2],sizeof(int8_t),1,fp)) return 0;
   if(!lss_write(&mAUDIO_2_INTEGRATE_ENABLE,sizeof(ULONG),1,fp)) return 0;
   if(!lss_write(&mAUDIO_2_WAVESHAPER,sizeof(ULONG),1,fp)) return 0;

   if(!lss_write(&mAUDIO_3_BKUP,sizeof(ULONG),1,fp)) return 0;
   if(!lss_write(&mAUDIO_3_ENABLE_RELOAD,sizeof(ULONG),1,fp)) return 0;
   if(!lss_write(&mAUDIO_3_ENABLE_COUNT,sizeof(ULONG),1,fp)) return 0;
   if(!lss_write(&mAUDIO_3_LINKING,sizeof(ULONG),1,fp)) return 0;
   if(!lss_write(&mAUDIO_3_CURRENT,sizeof(ULONG),1,fp)) return 0;
   if(!lss_write(&mAUDIO_3_TIMER_DONE,sizeof(ULONG),1,fp)) return 0;
   if(!lss_write(&mAUDIO_3_LAST_CLOCK,sizeof(ULONG),1,fp)) return 0;
   if(!lss_write(&mAUDIO_3_BORROW_IN,sizeof(ULONG),1,fp)) return 0;
   if(!lss_write(&mAUDIO_3_BORROW_OUT,sizeof(ULONG),1,fp)) return 0;
   if(!lss_write(&mAUDIO_3_LAST_LINK_CARRY,sizeof(ULONG),1,fp)) return 0;
   if(!lss_write(&mAUDIO_3_LAST_COUNT,sizeof(ULONG),1,fp)) return 0;
   if(!lss_write(&mAUDIO_3_VOLUME,sizeof(int8_t),1,fp)) return 0;
   if(!lss_write(&mAUDIO_OUTPUT[3],sizeof(int8_t),1,fp)) return 0;
   if(!lss_write(&mAUDIO_3_INTEGRATE_ENABLE,sizeof(ULONG),1,fp)) return 0;
   if(!lss_write(&mAUDIO_3_WAVESHAPER,sizeof(ULONG),1,fp)) return 0;

   if(!lss_write(&mSTEREO,sizeof(ULONG),1,fp)) return 0;

   //
   // Serial related variables
   //
   if(!lss_write(&mUART_RX_IRQ_ENABLE,sizeof(ULONG),1,fp)) return 0;
   if(!lss_write(&mUART_TX_IRQ_ENABLE,sizeof(ULONG),1,fp)) return 0;

   if(!lss_write(&mUART_TX_COUNTDOWN,sizeof(ULONG),1,fp)) return 0;
   if(!lss_write(&mUART_RX_COUNTDOWN,sizeof(ULONG),1,fp)) return 0;

   if(!lss_write(&mUART_SENDBREAK,sizeof(ULONG),1,fp)) return 0;
   if(!lss_write(&mUART_TX_DATA,sizeof(ULONG),1,fp)) return 0;
   if(!lss_write(&mUART_RX_DATA,sizeof(ULONG),1,fp)) return 0;
   if(!lss_write(&mUART_RX_READY,sizeof(ULONG),1,fp)) return 0;

   if(!lss_write(&mUART_PARITY_ENABLE,sizeof(ULONG),1,fp)) return 0;
   if(!lss_write(&mUART_PARITY_EVEN,sizeof(ULONG),1,fp)) return 0;

   return 1;
}

bool CMikie::ContextLoad(LSS_FILE *fp)
{
   char teststr[100]="XXXXXXXXXXXXXXXXXXX";
   if(!lss_read(teststr,sizeof(char),19,fp)) return 0;
   if(strcmp(teststr,"CMikie::ContextSave")!=0) return 0;

   if(!lss_read(&mDisplayAddress,sizeof(ULONG),1,fp)) return 0;
   if(!lss_read(&mAudioInputComparator,sizeof(ULONG),1,fp)) return 0;
   if(!lss_read(&mTimerStatusFlags,sizeof(ULONG),1,fp)) return 0;
   if(!lss_read(&mTimerInterruptMask,sizeof(ULONG),1,fp)) return 0;

   if(!lss_read(mPalette,sizeof(TPALETTE),16,fp)) return 0;

   if(!lss_read(&mIODAT,sizeof(ULONG),1,fp)) return 0;
   if(!lss_read(&mIODAT_REST_SIGNAL,sizeof(ULONG),1,fp)) return 0;
   if(!lss_read(&mIODIR,sizeof(ULONG),1,fp)) return 0;

   if(!lss_read(&mDISPCTL_DMAEnable,sizeof(ULONG),1,fp)) return 0;
   if(!lss_read(&mDISPCTL_Flip,sizeof(ULONG),1,fp)) return 0;
   if(!lss_read(&mDISPCTL_FourColour,sizeof(ULONG),1,fp)) return 0;
   if(!lss_read(&mDISPCTL_Colour,sizeof(ULONG),1,fp)) return 0;

   if(!lss_read(&mTIM_0_BKUP,sizeof(ULONG),1,fp)) return 0;
   if(!lss_read(&mTIM_0_ENABLE_RELOAD,sizeof(ULONG),1,fp)) return 0;
   if(!lss_read(&mTIM_0_ENABLE_COUNT,sizeof(ULONG),1,fp)) return 0;
   if(!lss_read(&mTIM_0_LINKING,sizeof(ULONG),1,fp)) return 0;
   if(!lss_read(&mTIM_0_CURRENT,sizeof(ULONG),1,fp)) return 0;
   if(!lss_read(&mTIM_0_TIMER_DONE,sizeof(ULONG),1,fp)) return 0;
   if(!lss_read(&mTIM_0_LAST_CLOCK,sizeof(ULONG),1,fp)) return 0;
   if(!lss_read(&mTIM_0_BORROW_IN,sizeof(ULONG),1,fp)) return 0;
   if(!lss_read(&mTIM_0_BORROW_OUT,sizeof(ULONG),1,fp)) return 0;
   if(!lss_read(&mTIM_0_LAST_LINK_CARRY,sizeof(ULONG),1,fp)) return 0;
   if(!lss_read(&mTIM_0_LAST_COUNT,sizeof(ULONG),1,fp)) return 0;

   if(!lss_read(&mTIM_1_BKUP,sizeof(ULONG),1,fp)) return 0;
   if(!lss_read(&mTIM_1_ENABLE_RELOAD,sizeof(ULONG),1,fp)) return 0;
   if(!lss_read(&mTIM_1_ENABLE_COUNT,sizeof(ULONG),1,fp)) return 0;
   if(!lss_read(&mTIM_1_LINKING,sizeof(ULONG),1,fp)) return 0;
   if(!lss_read(&mTIM_1_CURRENT,sizeof(ULONG),1,fp)) return 0;
   if(!lss_read(&mTIM_1_TIMER_DONE,sizeof(ULONG),1,fp)) return 0;
   if(!lss_read(&mTIM_1_LAST_CLOCK,sizeof(ULONG),1,fp)) return 0;
   if(!lss_read(&mTIM_1_BORROW_IN,sizeof(ULONG),1,fp)) return 0;
   if(!lss_read(&mTIM_1_BORROW_OUT,sizeof(ULONG),1,fp)) return 0;
   if(!lss_read(&mTIM_1_LAST_LINK_CARRY,sizeof(ULONG),1,fp)) return 0;
   if(!lss_read(&mTIM_1_LAST_COUNT,sizeof(ULONG),1,fp)) return 0;

   if(!lss_read(&mTIM_2_BKUP,sizeof(ULONG),1,fp)) return 0;
   if(!lss_read(&mTIM_2_ENABLE_RELOAD,sizeof(ULONG),1,fp)) return 0;
   if(!lss_read(&mTIM_2_ENABLE_COUNT,sizeof(ULONG),1,fp)) return 0;
   if(!lss_read(&mTIM_2_LINKING,sizeof(ULONG),1,fp)) return 0;
   if(!lss_read(&mTIM_2_CURRENT,sizeof(ULONG),1,fp)) return 0;
   if(!lss_read(&mTIM_2_TIMER_DONE,sizeof(ULONG),1,fp)) return 0;
   if(!lss_read(&mTIM_2_LAST_CLOCK,sizeof(ULONG),1,fp)) return 0;
   if(!lss_read(&mTIM_2_BORROW_IN,sizeof(ULONG),1,fp)) return 0;
   if(!lss_read(&mTIM_2_BORROW_OUT,sizeof(ULONG),1,fp)) return 0;
   if(!lss_read(&mTIM_2_LAST_LINK_CARRY,sizeof(ULONG),1,fp)) return 0;
   if(!lss_read(&mTIM_2_LAST_COUNT,sizeof(ULONG),1,fp)) return 0;

   if(!lss_read(&mTIM_3_BKUP,sizeof(ULONG),1,fp)) return 0;
   if(!lss_read(&mTIM_3_ENABLE_RELOAD,sizeof(ULONG),1,fp)) return 0;
   if(!lss_read(&mTIM_3_ENABLE_COUNT,sizeof(ULONG),1,fp)) return 0;
   if(!lss_read(&mTIM_3_LINKING,sizeof(ULONG),1,fp)) return 0;
   if(!lss_read(&mTIM_3_CURRENT,sizeof(ULONG),1,fp)) return 0;
   if(!lss_read(&mTIM_3_TIMER_DONE,sizeof(ULONG),1,fp)) return 0;
   if(!lss_read(&mTIM_3_LAST_CLOCK,sizeof(ULONG),1,fp)) return 0;
   if(!lss_read(&mTIM_3_BORROW_IN,sizeof(ULONG),1,fp)) return 0;
   if(!lss_read(&mTIM_3_BORROW_OUT,sizeof(ULONG),1,fp)) return 0;
   if(!lss_read(&mTIM_3_LAST_LINK_CARRY,sizeof(ULONG),1,fp)) return 0;
   if(!lss_read(&mTIM_3_LAST_COUNT,sizeof(ULONG),1,fp)) return 0;

   if(!lss_read(&mTIM_4_BKUP,sizeof(ULONG),1,fp)) return 0;
   if(!lss_read(&mTIM_4_ENABLE_RELOAD,sizeof(ULONG),1,fp)) return 0;
   if(!lss_read(&mTIM_4_ENABLE_COUNT,sizeof(ULONG),1,fp)) return 0;
   if(!lss_read(&mTIM_4_LINKING,sizeof(ULONG),1,fp)) return 0;
   if(!lss_read(&mTIM_4_CURRENT,sizeof(ULONG),1,fp)) return 0;
   if(!lss_read(&mTIM_4_TIMER_DONE,sizeof(ULONG),1,fp)) return 0;
   if(!lss_read(&mTIM_4_LAST_CLOCK,sizeof(ULONG),1,fp)) return 0;
   if(!lss_read(&mTIM_4_BORROW_IN,sizeof(ULONG),1,fp)) return 0;
   if(!lss_read(&mTIM_4_BORROW_OUT,sizeof(ULONG),1,fp)) return 0;
   if(!lss_read(&mTIM_4_LAST_LINK_CARRY,sizeof(ULONG),1,fp)) return 0;
   if(!lss_read(&mTIM_4_LAST_COUNT,sizeof(ULONG),1,fp)) return 0;

   if(!lss_read(&mTIM_5_BKUP,sizeof(ULONG),1,fp)) return 0;
   if(!lss_read(&mTIM_5_ENABLE_RELOAD,sizeof(ULONG),1,fp)) return 0;
   if(!lss_read(&mTIM_5_ENABLE_COUNT,sizeof(ULONG),1,fp)) return 0;
   if(!lss_read(&mTIM_5_LINKING,sizeof(ULONG),1,fp)) return 0;
   if(!lss_read(&mTIM_5_CURRENT,sizeof(ULONG),1,fp)) return 0;
   if(!lss_read(&mTIM_5_TIMER_DONE,sizeof(ULONG),1,fp)) return 0;
   if(!lss_read(&mTIM_5_LAST_CLOCK,sizeof(ULONG),1,fp)) return 0;
   if(!lss_read(&mTIM_5_BORROW_IN,sizeof(ULONG),1,fp)) return 0;
   if(!lss_read(&mTIM_5_BORROW_OUT,sizeof(ULONG),1,fp)) return 0;
   if(!lss_read(&mTIM_5_LAST_LINK_CARRY,sizeof(ULONG),1,fp)) return 0;
   if(!lss_read(&mTIM_5_LAST_COUNT,sizeof(ULONG),1,fp)) return 0;

   if(!lss_read(&mTIM_6_BKUP,sizeof(ULONG),1,fp)) return 0;
   if(!lss_read(&mTIM_6_ENABLE_RELOAD,sizeof(ULONG),1,fp)) return 0;
   if(!lss_read(&mTIM_6_ENABLE_COUNT,sizeof(ULONG),1,fp)) return 0;
   if(!lss_read(&mTIM_6_LINKING,sizeof(ULONG),1,fp)) return 0;
   if(!lss_read(&mTIM_6_CURRENT,sizeof(ULONG),1,fp)) return 0;
   if(!lss_read(&mTIM_6_TIMER_DONE,sizeof(ULONG),1,fp)) return 0;
   if(!lss_read(&mTIM_6_LAST_CLOCK,sizeof(ULONG),1,fp)) return 0;
   if(!lss_read(&mTIM_6_BORROW_IN,sizeof(ULONG),1,fp)) return 0;
   if(!lss_read(&mTIM_6_BORROW_OUT,sizeof(ULONG),1,fp)) return 0;
   if(!lss_read(&mTIM_6_LAST_LINK_CARRY,sizeof(ULONG),1,fp)) return 0;
   if(!lss_read(&mTIM_6_LAST_COUNT,sizeof(ULONG),1,fp)) return 0;

   if(!lss_read(&mTIM_7_BKUP,sizeof(ULONG),1,fp)) return 0;
   if(!lss_read(&mTIM_7_ENABLE_RELOAD,sizeof(ULONG),1,fp)) return 0;
   if(!lss_read(&mTIM_7_ENABLE_COUNT,sizeof(ULONG),1,fp)) return 0;
   if(!lss_read(&mTIM_7_LINKING,sizeof(ULONG),1,fp)) return 0;
   if(!lss_read(&mTIM_7_CURRENT,sizeof(ULONG),1,fp)) return 0;
   if(!lss_read(&mTIM_7_TIMER_DONE,sizeof(ULONG),1,fp)) return 0;
   if(!lss_read(&mTIM_7_LAST_CLOCK,sizeof(ULONG),1,fp)) return 0;
   if(!lss_read(&mTIM_7_BORROW_IN,sizeof(ULONG),1,fp)) return 0;
   if(!lss_read(&mTIM_7_BORROW_OUT,sizeof(ULONG),1,fp)) return 0;
   if(!lss_read(&mTIM_7_LAST_LINK_CARRY,sizeof(ULONG),1,fp)) return 0;
   if(!lss_read(&mTIM_7_LAST_COUNT,sizeof(ULONG),1,fp)) return 0;

   if(!lss_read(&mAUDIO_0_BKUP,sizeof(ULONG),1,fp)) return 0;
   if(!lss_read(&mAUDIO_0_ENABLE_RELOAD,sizeof(ULONG),1,fp)) return 0;
   if(!lss_read(&mAUDIO_0_ENABLE_COUNT,sizeof(ULONG),1,fp)) return 0;
   if(!lss_read(&mAUDIO_0_LINKING,sizeof(ULONG),1,fp)) return 0;
   if(!lss_read(&mAUDIO_0_CURRENT,sizeof(ULONG),1,fp)) return 0;
   if(!lss_read(&mAUDIO_0_TIMER_DONE,sizeof(ULONG),1,fp)) return 0;
   if(!lss_read(&mAUDIO_0_LAST_CLOCK,sizeof(ULONG),1,fp)) return 0;
   if(!lss_read(&mAUDIO_0_BORROW_IN,sizeof(ULONG),1,fp)) return 0;
   if(!lss_read(&mAUDIO_0_BORROW_OUT,sizeof(ULONG),1,fp)) return 0;
   if(!lss_read(&mAUDIO_0_LAST_LINK_CARRY,sizeof(ULONG),1,fp)) return 0;
   if(!lss_read(&mAUDIO_0_LAST_COUNT,sizeof(ULONG),1,fp)) return 0;
   if(!lss_read(&mAUDIO_0_VOLUME,sizeof(int8_t),1,fp)) return 0;
   if(!lss_read(&mAUDIO_OUTPUT[0],sizeof(int8_t),1,fp)) return 0;
   if(!lss_read(&mAUDIO_0_INTEGRATE_ENABLE,sizeof(ULONG),1,fp)) return 0;
   if(!lss_read(&mAUDIO_0_WAVESHAPER,sizeof(ULONG),1,fp)) return 0;

   if(!lss_read(&mAUDIO_1_BKUP,sizeof(ULONG),1,fp)) return 0;
   if(!lss_read(&mAUDIO_1_ENABLE_RELOAD,sizeof(ULONG),1,fp)) return 0;
   if(!lss_read(&mAUDIO_1_ENABLE_COUNT,sizeof(ULONG),1,fp)) return 0;
   if(!lss_read(&mAUDIO_1_LINKING,sizeof(ULONG),1,fp)) return 0;
   if(!lss_read(&mAUDIO_1_CURRENT,sizeof(ULONG),1,fp)) return 0;
   if(!lss_read(&mAUDIO_1_TIMER_DONE,sizeof(ULONG),1,fp)) return 0;
   if(!lss_read(&mAUDIO_1_LAST_CLOCK,sizeof(ULONG),1,fp)) return 0;
   if(!lss_read(&mAUDIO_1_BORROW_IN,sizeof(ULONG),1,fp)) return 0;
   if(!lss_read(&mAUDIO_1_BORROW_OUT,sizeof(ULONG),1,fp)) return 0;
   if(!lss_read(&mAUDIO_1_LAST_LINK_CARRY,sizeof(ULONG),1,fp)) return 0;
   if(!lss_read(&mAUDIO_1_LAST_COUNT,sizeof(ULONG),1,fp)) return 0;
   if(!lss_read(&mAUDIO_1_VOLUME,sizeof(int8_t),1,fp)) return 0;
   if(!lss_read(&mAUDIO_OUTPUT[1],sizeof(int8_t),1,fp)) return 0;
   if(!lss_read(&mAUDIO_1_INTEGRATE_ENABLE,sizeof(ULONG),1,fp)) return 0;
   if(!lss_read(&mAUDIO_1_WAVESHAPER,sizeof(ULONG),1,fp)) return 0;

   if(!lss_read(&mAUDIO_2_BKUP,sizeof(ULONG),1,fp)) return 0;
   if(!lss_read(&mAUDIO_2_ENABLE_RELOAD,sizeof(ULONG),1,fp)) return 0;
   if(!lss_read(&mAUDIO_2_ENABLE_COUNT,sizeof(ULONG),1,fp)) return 0;
   if(!lss_read(&mAUDIO_2_LINKING,sizeof(ULONG),1,fp)) return 0;
   if(!lss_read(&mAUDIO_2_CURRENT,sizeof(ULONG),1,fp)) return 0;
   if(!lss_read(&mAUDIO_2_TIMER_DONE,sizeof(ULONG),1,fp)) return 0;
   if(!lss_read(&mAUDIO_2_LAST_CLOCK,sizeof(ULONG),1,fp)) return 0;
   if(!lss_read(&mAUDIO_2_BORROW_IN,sizeof(ULONG),1,fp)) return 0;
   if(!lss_read(&mAUDIO_2_BORROW_OUT,sizeof(ULONG),1,fp)) return 0;
   if(!lss_read(&mAUDIO_2_LAST_LINK_CARRY,sizeof(ULONG),1,fp)) return 0;
   if(!lss_read(&mAUDIO_2_LAST_COUNT,sizeof(ULONG),1,fp)) return 0;
   if(!lss_read(&mAUDIO_2_VOLUME,sizeof(int8_t),1,fp)) return 0;
   if(!lss_read(&mAUDIO_OUTPUT[2],sizeof(int8_t),1,fp)) return 0;
   if(!lss_read(&mAUDIO_2_INTEGRATE_ENABLE,sizeof(ULONG),1,fp)) return 0;
   if(!lss_read(&mAUDIO_2_WAVESHAPER,sizeof(ULONG),1,fp)) return 0;

   if(!lss_read(&mAUDIO_3_BKUP,sizeof(ULONG),1,fp)) return 0;
   if(!lss_read(&mAUDIO_3_ENABLE_RELOAD,sizeof(ULONG),1,fp)) return 0;
   if(!lss_read(&mAUDIO_3_ENABLE_COUNT,sizeof(ULONG),1,fp)) return 0;
   if(!lss_read(&mAUDIO_3_LINKING,sizeof(ULONG),1,fp)) return 0;
   if(!lss_read(&mAUDIO_3_CURRENT,sizeof(ULONG),1,fp)) return 0;
   if(!lss_read(&mAUDIO_3_TIMER_DONE,sizeof(ULONG),1,fp)) return 0;
   if(!lss_read(&mAUDIO_3_LAST_CLOCK,sizeof(ULONG),1,fp)) return 0;
   if(!lss_read(&mAUDIO_3_BORROW_IN,sizeof(ULONG),1,fp)) return 0;
   if(!lss_read(&mAUDIO_3_BORROW_OUT,sizeof(ULONG),1,fp)) return 0;
   if(!lss_read(&mAUDIO_3_LAST_LINK_CARRY,sizeof(ULONG),1,fp)) return 0;
   if(!lss_read(&mAUDIO_3_LAST_COUNT,sizeof(ULONG),1,fp)) return 0;
   if(!lss_read(&mAUDIO_3_VOLUME,sizeof(int8_t),1,fp)) return 0;
   if(!lss_read(&mAUDIO_OUTPUT[3],sizeof(int8_t),1,fp)) return 0;
   if(!lss_read(&mAUDIO_3_INTEGRATE_ENABLE,sizeof(ULONG),1,fp)) return 0;
   if(!lss_read(&mAUDIO_3_WAVESHAPER,sizeof(ULONG),1,fp)) return 0;

   if(!lss_read(&mSTEREO,sizeof(ULONG),1,fp)) return 0;

   //
   // Serial related variables
   //
   if(!lss_read(&mUART_RX_IRQ_ENABLE,sizeof(ULONG),1,fp)) return 0;
   if(!lss_read(&mUART_TX_IRQ_ENABLE,sizeof(ULONG),1,fp)) return 0;

   if(!lss_read(&mUART_TX_COUNTDOWN,sizeof(ULONG),1,fp)) return 0;
   if(!lss_read(&mUART_RX_COUNTDOWN,sizeof(ULONG),1,fp)) return 0;

   if(!lss_read(&mUART_SENDBREAK,sizeof(ULONG),1,fp)) return 0;
   if(!lss_read(&mUART_TX_DATA,sizeof(ULONG),1,fp)) return 0;
   if(!lss_read(&mUART_RX_DATA,sizeof(ULONG),1,fp)) return 0;
   if(!lss_read(&mUART_RX_READY,sizeof(ULONG),1,fp)) return 0;

   if(!lss_read(&mUART_PARITY_ENABLE,sizeof(ULONG),1,fp)) return 0;
   if(!lss_read(&mUART_PARITY_EVEN,sizeof(ULONG),1,fp)) return 0;

   mikbuf.clear();
   return 1;
}

void CMikie::PresetForHomebrew(void)
{
   //
   // After all of that nice timer init we'll start timers running as some homebrew
   // i.e LR.O doesn't bother to setup the timers

   mTIM_0_BKUP=0x9e;
   mTIM_0_ENABLE_RELOAD=TRUE;
   mTIM_0_ENABLE_COUNT=TRUE;

   mTIM_2_BKUP=0x68;
   mTIM_2_ENABLE_RELOAD=TRUE;
   mTIM_2_ENABLE_COUNT=TRUE;
   mTIM_2_LINKING=7;

   mDISPCTL_DMAEnable=TRUE;
   mDISPCTL_Flip=FALSE;
   mDISPCTL_FourColour=0;
   mDISPCTL_Colour=TRUE;
}

void CMikie::ComLynxCable(int status)
{
   mUART_CABLE_PRESENT=status;
}

void CMikie::ComLynxRxData(int data)
{
   // Copy over the data
   if(mUART_Rx_waiting<UART_MAX_RX_QUEUE)
   {
      // Trigger incoming receive IF none waiting otherwise
      // we NEVER get to receive it!!!
      if(!mUART_Rx_waiting) mUART_RX_COUNTDOWN=UART_RX_TIME_PERIOD;

      // Receive the byte
      mUART_Rx_input_queue[mUART_Rx_input_ptr]=data;
      mUART_Rx_input_ptr=(++mUART_Rx_input_ptr)%UART_MAX_RX_QUEUE;
      mUART_Rx_waiting++;
   }
}

void CMikie::ComLynxTxLoopback(int data)
{
   if(mUART_Rx_waiting<UART_MAX_RX_QUEUE)
   {
      // Trigger incoming receive IF none waiting otherwise
      // we NEVER get to receive it!!!
      if(!mUART_Rx_waiting) mUART_RX_COUNTDOWN=UART_RX_TIME_PERIOD;

      // Receive the byte - INSERT into front of queue
      mUART_Rx_output_ptr=(--mUART_Rx_output_ptr)%UART_MAX_RX_QUEUE;
      mUART_Rx_input_queue[mUART_Rx_output_ptr]=data;
      mUART_Rx_waiting++;
   }
}

void CMikie::ComLynxTxCallback(void (*function)(int data,ULONG objref),ULONG objref)
{
   mpUART_TX_CALLBACK=function;
   mUART_TX_CALLBACK_OBJECT=objref;
}


void CMikie::DisplaySetAttributes(ULONG Rotate,ULONG Format,ULONG Pitch,UBYTE* (*RenderCallback)(ULONG objref),ULONG objref)
{
   mDisplayRotate=Rotate;
   mDisplayFormat=Format;
   mDisplayPitch=Pitch;
   mpDisplayCallback=RenderCallback;
   mDisplayCallbackObject=objref;

   mpDisplayCurrent=NULL;

   if(mpDisplayCallback) {
      mpDisplayBits=(*mpDisplayCallback)(mDisplayCallbackObject);
   } else {
      mpDisplayBits=NULL;
   }

   //
   // Calculate the colour lookup tabes for the relevant mode
   //
   TPALETTE Spot;

   switch(mDisplayFormat) {
      case MIKIE_PIXEL_FORMAT_8BPP:
         for(Spot.Index=0;Spot.Index<4096;Spot.Index++) {
            mColourMap[Spot.Index]=(Spot.Colours.Red<<4)&0xe0;
            mColourMap[Spot.Index]|=(Spot.Colours.Green<<1)&0x1c;
            mColourMap[Spot.Index]|=(Spot.Colours.Blue>>2)&0x03;
         }
         break;
      case MIKIE_PIXEL_FORMAT_16BPP_BGR555:
         for(Spot.Index=0;Spot.Index<4096;Spot.Index++) {
            mColourMap[Spot.Index]=((Spot.Colours.Blue<<11)&0x7800) | (Spot.Colours.Blue<<7)&0x0400;
            mColourMap[Spot.Index]|=((Spot.Colours.Green<<6)&0x03c0) | ((Spot.Colours.Green<<2)&0x0020);
            mColourMap[Spot.Index]|=((Spot.Colours.Red<<1)&0x001e) | ((Spot.Colours.Red>>3)&0x0001);
         }
         break;
      case MIKIE_PIXEL_FORMAT_16BPP_555:
         for(Spot.Index=0;Spot.Index<4096;Spot.Index++) {
            mColourMap[Spot.Index]=((Spot.Colours.Red<<11)&0x7800) | (Spot.Colours.Red<<7)&0x0400;
            mColourMap[Spot.Index]|=((Spot.Colours.Green<<6)&0x03c0) | ((Spot.Colours.Green<<2)&0x0020);
            mColourMap[Spot.Index]|=((Spot.Colours.Blue<<1)&0x001e) | ((Spot.Colours.Blue>>3)&0x0001);
         }
         break;
      case MIKIE_PIXEL_FORMAT_16BPP_565:
         for(Spot.Index=0;Spot.Index<4096;Spot.Index++) {
            mColourMap[Spot.Index]=((Spot.Colours.Red<<12)&0xf000) | (Spot.Colours.Red<<8)&0x0800;
            mColourMap[Spot.Index]|=((Spot.Colours.Green<<7)&0x0780) | ((Spot.Colours.Green<<3)&0x0060);
            mColourMap[Spot.Index]|=((Spot.Colours.Blue<<1)&0x001e) | ((Spot.Colours.Blue>>3)&0x0001);
         }
         break;
      case MIKIE_PIXEL_FORMAT_24BPP:
      case MIKIE_PIXEL_FORMAT_32BPP:
         for(Spot.Index=0;Spot.Index<4096;Spot.Index++) {
            mColourMap[Spot.Index]=((Spot.Colours.Red<<20)&0x00f00000) | ((Spot.Colours.Red<<16)&0x000f0000);
            mColourMap[Spot.Index]|=((Spot.Colours.Green<<12)&0x0000f000) | ((Spot.Colours.Green<<8)&0x00000f00);
            mColourMap[Spot.Index]|=((Spot.Colours.Blue<<4)&0x000000f0) | ((Spot.Colours.Blue<<0)&0x0000000f);
         }
         break;
      default:
         if(gError) gError->Warning("CMikie::SetScreenAttributes() - Unrecognised display format");
         for(Spot.Index=0;Spot.Index<4096;Spot.Index++) mColourMap[Spot.Index]=0;
         break;
   }

   // Reset screen related counters/vars
   mTIM_0_CURRENT=0;
   mTIM_2_CURRENT=0;

   // Fix lastcount so that timer update will definately occur
   mTIM_0_LAST_COUNT-=(1<<(4+mTIM_0_LINKING))+1;
   mTIM_2_LAST_COUNT-=(1<<(4+mTIM_2_LINKING))+1;

   // Force immediate timer update
   gNextTimerEvent=gSystemCycleCount;
}


ULONG CMikie::DisplayRenderLine(void)
{
   UBYTE *bitmap_tmp=NULL;
   ULONG source,loop;
   ULONG work_done=0;

   if(!mpDisplayBits) return 0;
   if(!mpDisplayCurrent) return 0;
   if(!mDISPCTL_DMAEnable) return 0;

   //	if(mLynxLine&0x80000000) return 0;

   // Set the timer interrupt flag
   if(mTimerInterruptMask&0x01) {
      mTimerStatusFlags|=0x01;
      gSystemIRQ=TRUE;	// Added 19/09/06 fix for IRQ issue
   }

   // Logic says it should be 101 but testing on an actual lynx shows the rest
   // persiod is between lines 102,101,100 with the new line being latched at
   // the beginning of count==99 hence the code below !!

   // Emulate REST signal
   if(mLynxLine==mTIM_2_BKUP-2 || mLynxLine==mTIM_2_BKUP-3 || mLynxLine==mTIM_2_BKUP-4) mIODAT_REST_SIGNAL=TRUE;
   else mIODAT_REST_SIGNAL=FALSE;

   if(mLynxLine==(mTIM_2_BKUP-3)) {
      if(mDISPCTL_Flip) {
         mLynxAddr=mDisplayAddress&0xfffc;
         mLynxAddr+=3;
      } else {
         mLynxAddr=mDisplayAddress&0xfffc;
      }
      // Trigger line rending to start
      mLynxLineDMACounter=102;
   }

   // Decrement line counter logic
   if(mLynxLine) mLynxLine--;

   // Do 102 lines, nothing more, less is OK.
   if(mLynxLineDMACounter) {
      mLynxLineDMACounter--;

      // Cycle hit for a 80 RAM access in rendering a line
      work_done+=(80+100)*DMA_RDWR_CYC;

      // If we are skipping this frame, return now
      if(gSkipFrame)
         return work_done;

      // Mikie screen DMA can only see the system RAM....
      // (Step through bitmap, line at a time)

      // Assign the temporary pointer;
      bitmap_tmp=mpDisplayCurrent;

      switch(mDisplayRotate) {
         case MIKIE_NO_ROTATE:
            if(mDisplayFormat==MIKIE_PIXEL_FORMAT_8BPP) {
               for(loop=0;loop<SCREEN_WIDTH/2;loop++) {
                  source=mpRamPointer[mLynxAddr];
                  if(mDISPCTL_Flip) {
                     mLynxAddr--;
                     *(bitmap_tmp)=(UBYTE)mColourMap[mPalette[source&0x0f].Index];
                     bitmap_tmp+=sizeof(UBYTE);
                     *(bitmap_tmp)=(UBYTE)mColourMap[mPalette[source>>4].Index];
                     bitmap_tmp+=sizeof(UBYTE);
                  } else {
                     mLynxAddr++;
                     *(bitmap_tmp)=(UBYTE)mColourMap[mPalette[source>>4].Index];
                     bitmap_tmp+=sizeof(UBYTE);
                     *(bitmap_tmp)=(UBYTE)mColourMap[mPalette[source&0x0f].Index];
                     bitmap_tmp+=sizeof(UBYTE);
                  }
               }
            } else if(mDisplayFormat==MIKIE_PIXEL_FORMAT_16BPP_BGR555 || mDisplayFormat==MIKIE_PIXEL_FORMAT_16BPP_555 || mDisplayFormat==MIKIE_PIXEL_FORMAT_16BPP_565) {
               for(loop=0;loop<SCREEN_WIDTH/2;loop++) {
                  source=mpRamPointer[mLynxAddr];
                  if(mDISPCTL_Flip) {
                     mLynxAddr--;
                     *((UWORD*)(bitmap_tmp))=(UWORD)mColourMap[mPalette[source&0x0f].Index];
                     bitmap_tmp+=sizeof(UWORD);
                     *((UWORD*)(bitmap_tmp))=(UWORD)mColourMap[mPalette[source>>4].Index];
                     bitmap_tmp+=sizeof(UWORD);
                  } else {
                     mLynxAddr++;
                     *((UWORD*)(bitmap_tmp))=(UWORD)mColourMap[mPalette[source>>4].Index];
                     bitmap_tmp+=sizeof(UWORD);
                     *((UWORD*)(bitmap_tmp))=(UWORD)mColourMap[mPalette[source&0x0f].Index];
                     bitmap_tmp+=sizeof(UWORD);
                  }
               }
            } else if(mDisplayFormat==MIKIE_PIXEL_FORMAT_24BPP) {
               ULONG pixel;
               for(loop=0;loop<SCREEN_WIDTH/2;loop++) {
                  source=mpRamPointer[mLynxAddr];
                  if(mDISPCTL_Flip) {
                     mLynxAddr--;
                     pixel=mColourMap[mPalette[source&0x0f].Index];
                     *bitmap_tmp++=(UBYTE)pixel;
                     pixel>>=8;
                     *bitmap_tmp++=(UBYTE)pixel;
                     pixel>>=8;
                     *bitmap_tmp++=(UBYTE)pixel;
                     pixel=mColourMap[mPalette[source>>4].Index];
                     *bitmap_tmp++=(UBYTE)pixel;
                     pixel>>=8;
                     *bitmap_tmp++=(UBYTE)pixel;
                     pixel>>=8;
                     *bitmap_tmp++=(UBYTE)pixel;
                  } else {
                     mLynxAddr++;
                     pixel=mColourMap[mPalette[source>>4].Index];
                     *bitmap_tmp++=(UBYTE)pixel;
                     pixel>>=8;
                     *bitmap_tmp++=(UBYTE)pixel;
                     pixel>>=8;
                     *bitmap_tmp++=(UBYTE)pixel;
                     pixel=mColourMap[mPalette[source&0x0f].Index];
                     *bitmap_tmp++=(UBYTE)pixel;
                     pixel>>=8;
                     *bitmap_tmp++=(UBYTE)pixel;
                     pixel>>=8;
                     *bitmap_tmp++=(UBYTE)pixel;
                  }
               }
            } else if(mDisplayFormat==MIKIE_PIXEL_FORMAT_32BPP) {
               for(loop=0;loop<SCREEN_WIDTH/2;loop++) {
                  source=mpRamPointer[mLynxAddr];
                  if(mDISPCTL_Flip) {
                     mLynxAddr--;
                     *((ULONG*)(bitmap_tmp))=mColourMap[mPalette[source&0x0f].Index];
                     bitmap_tmp+=sizeof(ULONG);
                     *((ULONG*)(bitmap_tmp))=mColourMap[mPalette[source>>4].Index];
                     bitmap_tmp+=sizeof(ULONG);
                  } else {
                     mLynxAddr++;
                     *((ULONG*)(bitmap_tmp))=mColourMap[mPalette[source>>4].Index];
                     bitmap_tmp+=sizeof(ULONG);
                     *((ULONG*)(bitmap_tmp))=mColourMap[mPalette[source&0x0f].Index];
                     bitmap_tmp+=sizeof(ULONG);
                  }
               }
            }
            mpDisplayCurrent+=mDisplayPitch;
            break;
         case MIKIE_ROTATE_L:
            if(mDisplayFormat==MIKIE_PIXEL_FORMAT_8BPP) {
               for(loop=0;loop<SCREEN_WIDTH/2;loop++) {
                  source=mpRamPointer[mLynxAddr];
                  if(mDISPCTL_Flip) {
                     mLynxAddr--;
                     *(bitmap_tmp)=(UBYTE)mColourMap[mPalette[source&0x0f].Index];
                     bitmap_tmp+=mDisplayPitch;
                     *(bitmap_tmp)=(UBYTE)mColourMap[mPalette[source>>4].Index];
                     bitmap_tmp+=mDisplayPitch;
                  } else {
                     mLynxAddr++;
                     *(bitmap_tmp)=(UBYTE)mColourMap[mPalette[source>>4].Index];
                     bitmap_tmp+=mDisplayPitch;
                     *(bitmap_tmp)=(UBYTE)mColourMap[mPalette[source&0x0f].Index];
                     bitmap_tmp+=mDisplayPitch;
                  }
               }
               mpDisplayCurrent-=sizeof(UBYTE);
            } else if(mDisplayFormat==MIKIE_PIXEL_FORMAT_16BPP_BGR555 || mDisplayFormat==MIKIE_PIXEL_FORMAT_16BPP_555 || mDisplayFormat==MIKIE_PIXEL_FORMAT_16BPP_565) {
               for(loop=0;loop<SCREEN_WIDTH/2;loop++) {
                  source=mpRamPointer[mLynxAddr];
                  if(mDISPCTL_Flip) {
                     mLynxAddr--;
                     *((UWORD*)(bitmap_tmp))=(UWORD)mColourMap[mPalette[source&0x0f].Index];
                     bitmap_tmp+=mDisplayPitch;
                     *((UWORD*)(bitmap_tmp))=(UWORD)mColourMap[mPalette[source>>4].Index];
                     bitmap_tmp+=mDisplayPitch;
                  } else {
                     mLynxAddr++;
                     *((UWORD*)(bitmap_tmp))=(UWORD)mColourMap[mPalette[source>>4].Index];
                     bitmap_tmp+=mDisplayPitch;
                     *((UWORD*)(bitmap_tmp))=(UWORD)mColourMap[mPalette[source&0x0f].Index];
                     bitmap_tmp+=mDisplayPitch;
                  }
               }
               mpDisplayCurrent-=sizeof(UWORD);
            } else if(mDisplayFormat==MIKIE_PIXEL_FORMAT_24BPP) {
               ULONG pixel;
               for(loop=0;loop<SCREEN_WIDTH/2;loop++) {
                  source=mpRamPointer[mLynxAddr];
                  if(mDISPCTL_Flip) {
                     mLynxAddr--;
                     pixel=mColourMap[mPalette[source&0x0f].Index];
                     *(bitmap_tmp)=(UBYTE)pixel;
                     pixel>>=8;
                     *(bitmap_tmp+1)=(UBYTE)pixel;
                     pixel>>=8;
                     *(bitmap_tmp+2)=(UBYTE)pixel;
                     bitmap_tmp+=mDisplayPitch;
                     pixel=mColourMap[mPalette[source>>4].Index];
                     *(bitmap_tmp)=(UBYTE)pixel;
                     pixel>>=8;
                     *(bitmap_tmp+1)=(UBYTE)pixel;
                     pixel>>=8;
                     *(bitmap_tmp+2)=(UBYTE)pixel;
                     bitmap_tmp+=mDisplayPitch;
                  } else {
                     mLynxAddr++;
                     pixel=mColourMap[mPalette[source>>4].Index];
                     *(bitmap_tmp)=(UBYTE)pixel;
                     pixel>>=8;
                     *(bitmap_tmp+1)=(UBYTE)pixel;
                     pixel>>=8;
                     *(bitmap_tmp+2)=(UBYTE)pixel;
                     bitmap_tmp+=mDisplayPitch;
                     pixel=mColourMap[mPalette[source&0x0f].Index];
                     *(bitmap_tmp)=(UBYTE)pixel;
                     pixel>>=8;
                     *(bitmap_tmp+1)=(UBYTE)pixel;
                     pixel>>=8;
                     *(bitmap_tmp+2)=(UBYTE)pixel;
                     bitmap_tmp+=mDisplayPitch;
                  }
               }
               mpDisplayCurrent-=3;
            } else if(mDisplayFormat==MIKIE_PIXEL_FORMAT_32BPP) {
               for(loop=0;loop<SCREEN_WIDTH/2;loop++) {
                  source=mpRamPointer[mLynxAddr];
                  if(mDISPCTL_Flip) {
                     mLynxAddr--;
                     *((ULONG*)(bitmap_tmp))=mColourMap[mPalette[source&0x0f].Index];
                     bitmap_tmp+=mDisplayPitch;
                     *((ULONG*)(bitmap_tmp))=mColourMap[mPalette[source>>4].Index];
                     bitmap_tmp+=mDisplayPitch;
                  } else {
                     mLynxAddr++;
                     *((ULONG*)(bitmap_tmp))=mColourMap[mPalette[source>>4].Index];
                     bitmap_tmp+=mDisplayPitch;
                     *((ULONG*)(bitmap_tmp))=mColourMap[mPalette[source&0x0f].Index];
                     bitmap_tmp+=mDisplayPitch;
                  }
               }
               mpDisplayCurrent-=sizeof(ULONG);
            }
            break;
         case MIKIE_ROTATE_B:
            if(mDisplayFormat==MIKIE_PIXEL_FORMAT_8BPP) {
               for(loop=0;loop<SCREEN_WIDTH/2;loop++) {
                  source=mpRamPointer[mLynxAddr];
                  if(mDISPCTL_Flip) {
                     mLynxAddr--;
                     *(bitmap_tmp)=(UBYTE)mColourMap[mPalette[source&0x0f].Index];
                     bitmap_tmp-=sizeof(UBYTE);
                     *(bitmap_tmp)=(UBYTE)mColourMap[mPalette[source>>4].Index];
                     bitmap_tmp-=sizeof(UBYTE);
                  } else {
                     mLynxAddr++;
                     *(bitmap_tmp)=(UBYTE)mColourMap[mPalette[source>>4].Index];
                     bitmap_tmp-=sizeof(UBYTE);
                     *(bitmap_tmp)=(UBYTE)mColourMap[mPalette[source&0x0f].Index];
                     bitmap_tmp-=sizeof(UBYTE);
                  }
               }
            } else if(mDisplayFormat==MIKIE_PIXEL_FORMAT_16BPP_BGR555 || mDisplayFormat==MIKIE_PIXEL_FORMAT_16BPP_555 || mDisplayFormat==MIKIE_PIXEL_FORMAT_16BPP_565) {
               for(loop=0;loop<SCREEN_WIDTH/2;loop++) {
                  source=mpRamPointer[mLynxAddr];
                  if(mDISPCTL_Flip) {
                     mLynxAddr--;
                     *((UWORD*)(bitmap_tmp))=(UWORD)mColourMap[mPalette[source&0x0f].Index];
                     bitmap_tmp-=sizeof(UWORD);
                     *((UWORD*)(bitmap_tmp))=(UWORD)mColourMap[mPalette[source>>4].Index];
                     bitmap_tmp-=sizeof(UWORD);
                  } else {
                     mLynxAddr++;
                     *((UWORD*)(bitmap_tmp))=(UWORD)mColourMap[mPalette[source>>4].Index];
                     bitmap_tmp-=sizeof(UWORD);
                     *((UWORD*)(bitmap_tmp))=(UWORD)mColourMap[mPalette[source&0x0f].Index];
                     bitmap_tmp-=sizeof(UWORD);
                  }
               }
            } else if(mDisplayFormat==MIKIE_PIXEL_FORMAT_24BPP) {
               ULONG pixel;
               for(loop=0;loop<SCREEN_WIDTH/2;loop++) {
                  source=mpRamPointer[mLynxAddr];
                  if(mDISPCTL_Flip) {
                     mLynxAddr--;
                     pixel=mColourMap[mPalette[source&0x0f].Index];
                     *bitmap_tmp--=(UBYTE)pixel;
                     pixel>>=8;
                     *bitmap_tmp--=(UBYTE)pixel;
                     pixel>>=8;
                     *bitmap_tmp--=(UBYTE)pixel;
                     pixel=mColourMap[mPalette[source>>4].Index];
                     *bitmap_tmp--=(UBYTE)pixel;
                     pixel>>=8;
                     *bitmap_tmp--=(UBYTE)pixel;
                     pixel>>=8;
                     *bitmap_tmp--=(UBYTE)pixel;
                  } else {
                     mLynxAddr++;
                     pixel=mColourMap[mPalette[source>>4].Index];
                     *bitmap_tmp--=(UBYTE)pixel;
                     pixel>>=8;
                     *bitmap_tmp--=(UBYTE)pixel;
                     pixel>>=8;
                     *bitmap_tmp--=(UBYTE)pixel;
                     pixel=mColourMap[mPalette[source&0x0f].Index];
                     *bitmap_tmp--=(UBYTE)pixel;
                     pixel>>=8;
                     *bitmap_tmp--=(UBYTE)pixel;
                     pixel>>=8;
                     *bitmap_tmp--=(UBYTE)pixel;
                  }
               }
            } else if(mDisplayFormat==MIKIE_PIXEL_FORMAT_32BPP) {
               for(loop=0;loop<SCREEN_WIDTH/2;loop++) {
                  source=mpRamPointer[mLynxAddr];
                  if(mDISPCTL_Flip) {
                     mLynxAddr--;
                     *((ULONG*)(bitmap_tmp))=mColourMap[mPalette[source&0x0f].Index];
                     bitmap_tmp-=sizeof(ULONG);
                     *((ULONG*)(bitmap_tmp))=mColourMap[mPalette[source>>4].Index];
                     bitmap_tmp-=sizeof(ULONG);
                  } else {
                     mLynxAddr++;
                     *((ULONG*)(bitmap_tmp))=mColourMap[mPalette[source>>4].Index];
                     bitmap_tmp-=sizeof(ULONG);
                     *((ULONG*)(bitmap_tmp))=mColourMap[mPalette[source&0x0f].Index];
                     bitmap_tmp-=sizeof(ULONG);
                  }
               }
            }
            mpDisplayCurrent-=mDisplayPitch;
            break;
         case MIKIE_ROTATE_R:
            if(mDisplayFormat==MIKIE_PIXEL_FORMAT_8BPP) {
               for(loop=0;loop<SCREEN_WIDTH/2;loop++) {
                  source=mpRamPointer[mLynxAddr];
                  if(mDISPCTL_Flip) {
                     mLynxAddr--;
                     *(bitmap_tmp)=(UBYTE)mColourMap[mPalette[source&0x0f].Index];
                     bitmap_tmp-=mDisplayPitch;
                     *(bitmap_tmp)=(UBYTE)mColourMap[mPalette[source>>4].Index];
                     bitmap_tmp-=mDisplayPitch;
                  } else {
                     mLynxAddr++;
                     *(bitmap_tmp)=(UBYTE)mColourMap[mPalette[source>>4].Index];
                     bitmap_tmp-=mDisplayPitch;
                     *(bitmap_tmp)=(UBYTE)mColourMap[mPalette[source&0x0f].Index];
                     bitmap_tmp-=mDisplayPitch;
                  }
               }
               mpDisplayCurrent+=sizeof(UBYTE);
            } else if(mDisplayFormat==MIKIE_PIXEL_FORMAT_16BPP_BGR555 || mDisplayFormat==MIKIE_PIXEL_FORMAT_16BPP_555 || mDisplayFormat==MIKIE_PIXEL_FORMAT_16BPP_565) {
               for(loop=0;loop<SCREEN_WIDTH/2;loop++) {
                  source=mpRamPointer[mLynxAddr];
                  if(mDISPCTL_Flip) {
                     mLynxAddr--;
                     *((UWORD*)(bitmap_tmp))=(UWORD)mColourMap[mPalette[source&0x0f].Index];
                     bitmap_tmp-=mDisplayPitch;
                     *((UWORD*)(bitmap_tmp))=(UWORD)mColourMap[mPalette[source>>4].Index];
                     bitmap_tmp-=mDisplayPitch;
                  } else {
                     mLynxAddr++;
                     *((UWORD*)(bitmap_tmp))=(UWORD)mColourMap[mPalette[source>>4].Index];
                     bitmap_tmp-=mDisplayPitch;
                     *((UWORD*)(bitmap_tmp))=(UWORD)mColourMap[mPalette[source&0x0f].Index];
                     bitmap_tmp-=mDisplayPitch;
                  }
               }
               mpDisplayCurrent+=sizeof(UWORD);
            } else if(mDisplayFormat==MIKIE_PIXEL_FORMAT_24BPP) {
               ULONG pixel;
               for(loop=0;loop<SCREEN_WIDTH/2;loop++) {
                  source=mpRamPointer[mLynxAddr];
                  if(mDISPCTL_Flip) {
                     mLynxAddr--;
                     pixel=mColourMap[mPalette[source&0x0f].Index];
                     *(bitmap_tmp)=(UBYTE)pixel;
                     pixel>>=8;
                     *(bitmap_tmp+1)=(UBYTE)pixel;
                     pixel>>=8;
                     *(bitmap_tmp+2)=(UBYTE)pixel;
                     bitmap_tmp-=mDisplayPitch;
                     pixel=mColourMap[mPalette[source>>4].Index];
                     *(bitmap_tmp)=(UBYTE)pixel;
                     pixel>>=8;
                     *(bitmap_tmp+1)=(UBYTE)pixel;
                     pixel>>=8;
                     *(bitmap_tmp+2)=(UBYTE)pixel;
                     bitmap_tmp-=mDisplayPitch;
                  } else {
                     mLynxAddr++;
                     pixel=mColourMap[mPalette[source>>4].Index];
                     *(bitmap_tmp)=(UBYTE)pixel;
                     pixel>>=8;
                     *(bitmap_tmp+1)=(UBYTE)pixel;
                     pixel>>=8;
                     *(bitmap_tmp+2)=(UBYTE)pixel;
                     bitmap_tmp-=mDisplayPitch;
                     pixel=mColourMap[mPalette[source&0x0f].Index];
                     *(bitmap_tmp)=(UBYTE)pixel;
                     pixel>>=8;
                     *(bitmap_tmp+1)=(UBYTE)pixel;
                     pixel>>=8;
                     *(bitmap_tmp+2)=(UBYTE)pixel;
                     bitmap_tmp-=mDisplayPitch;
                  }
               }
               mpDisplayCurrent+=3;
            } else if(mDisplayFormat==MIKIE_PIXEL_FORMAT_32BPP) {
               for(loop=0;loop<SCREEN_WIDTH/2;loop++) {
                  source=mpRamPointer[mLynxAddr];
                  if(mDISPCTL_Flip) {
                     mLynxAddr--;
                     *((ULONG*)(bitmap_tmp))=mColourMap[mPalette[source&0x0f].Index];
                     bitmap_tmp-=mDisplayPitch;
                     *((ULONG*)(bitmap_tmp))=mColourMap[mPalette[source>>4].Index];
                     bitmap_tmp-=mDisplayPitch;
                  } else {
                     mLynxAddr++;
                     *((ULONG*)(bitmap_tmp))=mColourMap[mPalette[source>>4].Index];
                     bitmap_tmp-=mDisplayPitch;
                     *((ULONG*)(bitmap_tmp))=mColourMap[mPalette[source&0x0f].Index];
                     bitmap_tmp-=mDisplayPitch;
                  }
               }
               mpDisplayCurrent+=sizeof(ULONG);
            }
            break;
         default:
            break;
      }
   }
   return work_done;
}

ULONG CMikie::DisplayEndOfFrame(void)
{
   // Stop any further line rendering
   mLynxLineDMACounter=0;
   mLynxLine=mTIM_2_BKUP;

   if(gCPUWakeupTime) {
      gCPUWakeupTime = 0;
      ClearCPUSleep();   
   }
	
   // Set the timer status flag
   if(mTimerInterruptMask&0x04) {
      mTimerStatusFlags|=0x04;
      gSystemIRQ=TRUE;	// Added 19/09/06 fix for IRQ issue
   }

   //	("Update() - Frame end");
   // Trigger the callback to the display sub-system to render the
   // display and fetch the new pointer to be used for the lynx
   // display buffer for the forthcoming frame
   if(mpDisplayCallback) mpDisplayBits=(*mpDisplayCallback)(mDisplayCallbackObject);

   // Reinitialise the screen buffer pointer
   // Make any necessary adjustment for rotation
   switch(mDisplayRotate) {
      case MIKIE_ROTATE_L:
         mpDisplayCurrent=mpDisplayBits;
         switch(mDisplayFormat) {
            case MIKIE_PIXEL_FORMAT_8BPP:
               mpDisplayCurrent+=1*(HANDY_SCREEN_HEIGHT-1);
               break;
            case MIKIE_PIXEL_FORMAT_16BPP_BGR555:
            case MIKIE_PIXEL_FORMAT_16BPP_555:
            case MIKIE_PIXEL_FORMAT_16BPP_565:
               mpDisplayCurrent+=2*(HANDY_SCREEN_HEIGHT-1);
               break;
            case MIKIE_PIXEL_FORMAT_24BPP:
               mpDisplayCurrent+=3*(HANDY_SCREEN_HEIGHT-1);
               break;
            case MIKIE_PIXEL_FORMAT_32BPP:
               mpDisplayCurrent+=4*(HANDY_SCREEN_HEIGHT-1);
               break;
            default:
               break;
         }
         break;
      case MIKIE_ROTATE_B:
         mpDisplayCurrent=mpDisplayBits;
         switch(mDisplayFormat) {
            case MIKIE_PIXEL_FORMAT_8BPP:
               mpDisplayCurrent+=1*(HANDY_SCREEN_HEIGHT*HANDY_SCREEN_WIDTH-1);
               break;
            case MIKIE_PIXEL_FORMAT_16BPP_BGR555:
            case MIKIE_PIXEL_FORMAT_16BPP_555:
            case MIKIE_PIXEL_FORMAT_16BPP_565:
               mpDisplayCurrent+=2*(HANDY_SCREEN_HEIGHT*HANDY_SCREEN_WIDTH-1);
               break;
            case MIKIE_PIXEL_FORMAT_24BPP:
               mpDisplayCurrent+=3*(HANDY_SCREEN_HEIGHT*HANDY_SCREEN_WIDTH-1);
               break;
            case MIKIE_PIXEL_FORMAT_32BPP:
               mpDisplayCurrent+=4*(HANDY_SCREEN_HEIGHT*HANDY_SCREEN_WIDTH-1);
               break;
            default:
               break;
         }
         break;
      case MIKIE_ROTATE_R:
         mpDisplayCurrent=mpDisplayBits+(mDisplayPitch*(HANDY_SCREEN_WIDTH-1));
         break;
      case MIKIE_NO_ROTATE:
      default:
         mpDisplayCurrent=mpDisplayBits;
         break;
   }

   return 0;
}

void	CMikie::AudioEndOfFrame(void)
{
   mikbuf.end_frame((gSystemCycleCount - gAudioLastUpdateCycle) / 4);
   gAudioBufferPointer = mikbuf.read_samples((blip_sample_t*) gAudioBuffer, HANDY_AUDIO_BUFFER_SIZE / 2);
   gAudioLastUpdateCycle = gSystemCycleCount;
}

// Peek/Poke memory handlers

void CMikie::Poke(ULONG addr,UBYTE data)
{
   switch(addr&0xff) {
      case (TIM0BKUP&0xff):
         mTIM_0_BKUP=data;
         break;
      case (TIM1BKUP&0xff):
         mTIM_1_BKUP=data;
         break;
      case (TIM2BKUP&0xff):
         mTIM_2_BKUP=data;
         break;
      case (TIM3BKUP&0xff):
         mTIM_3_BKUP=data;
         break;
      case (TIM4BKUP&0xff):
         mTIM_4_BKUP=data;
         break;
      case (TIM5BKUP&0xff):
         mTIM_5_BKUP=data;
         break;
      case (TIM6BKUP&0xff):
         mTIM_6_BKUP=data;
         break;
      case (TIM7BKUP&0xff):
         mTIM_7_BKUP=data;
         break;


      case (TIM0CTLA&0xff):
         mTimerInterruptMask&=(0x01^0xff);
         mTimerInterruptMask|=(data&0x80)?0x01:0x00;
         mTIM_0_ENABLE_RELOAD=data&0x10;
         mTIM_0_ENABLE_COUNT=data&0x08;
         mTIM_0_LINKING=data&0x07;
         if(data&0x40) mTIM_0_TIMER_DONE=0;
         if(data&0x48) {
            mTIM_0_LAST_COUNT=gSystemCycleCount;
            gNextTimerEvent=gSystemCycleCount;
         }
         break;
      case (TIM1CTLA&0xff):
         mTimerInterruptMask&=(0x02^0xff);
         mTimerInterruptMask|=(data&0x80)?0x02:0x00;
         mTIM_1_ENABLE_RELOAD=data&0x10;
         mTIM_1_ENABLE_COUNT=data&0x08;
         mTIM_1_LINKING=data&0x07;
         if(data&0x40) mTIM_1_TIMER_DONE=0;
         if(data&0x48) {
            mTIM_1_LAST_COUNT=gSystemCycleCount;
            gNextTimerEvent=gSystemCycleCount;
         }
         break;
      case (TIM2CTLA&0xff):
         mTimerInterruptMask&=(0x04^0xff);
         mTimerInterruptMask|=(data&0x80)?0x04:0x00;
         mTIM_2_ENABLE_RELOAD=data&0x10;
         mTIM_2_ENABLE_COUNT=data&0x08;
         mTIM_2_LINKING=data&0x07;
         if(data&0x40) mTIM_2_TIMER_DONE=0;
         if(data&0x48) {
            mTIM_2_LAST_COUNT=gSystemCycleCount;
            gNextTimerEvent=gSystemCycleCount;
         }
         break;
      case (TIM3CTLA&0xff):
         mTimerInterruptMask&=(0x08^0xff);
         mTimerInterruptMask|=(data&0x80)?0x08:0x00;
         mTIM_3_ENABLE_RELOAD=data&0x10;
         mTIM_3_ENABLE_COUNT=data&0x08;
         mTIM_3_LINKING=data&0x07;
         if(data&0x40) mTIM_3_TIMER_DONE=0;
         if(data&0x48) {
            mTIM_3_LAST_COUNT=gSystemCycleCount;
            gNextTimerEvent=gSystemCycleCount;
         }
         break;
      case (TIM4CTLA&0xff):
         // Timer 4 can never generate interrupts as its timer output is used
         // to drive the UART clock generator
         mTIM_4_ENABLE_RELOAD=data&0x10;
         mTIM_4_ENABLE_COUNT=data&0x08;
         mTIM_4_LINKING=data&0x07;
         if(data&0x40) mTIM_4_TIMER_DONE=0;
         if(data&0x48) {
            mTIM_4_LAST_COUNT=gSystemCycleCount;
            gNextTimerEvent=gSystemCycleCount;
         }
         break;
      case (TIM5CTLA&0xff):
         mTimerInterruptMask&=(0x20^0xff);
         mTimerInterruptMask|=(data&0x80)?0x20:0x00;
         mTIM_5_ENABLE_RELOAD=data&0x10;
         mTIM_5_ENABLE_COUNT=data&0x08;
         mTIM_5_LINKING=data&0x07;
         if(data&0x40) mTIM_5_TIMER_DONE=0;
         if(data&0x48) {
            mTIM_5_LAST_COUNT=gSystemCycleCount;
            gNextTimerEvent=gSystemCycleCount;
         }
         break;
      case (TIM6CTLA&0xff):
         mTimerInterruptMask&=(0x40^0xff);
         mTimerInterruptMask|=(data&0x80)?0x40:0x00;
         mTIM_6_ENABLE_RELOAD=data&0x10;
         mTIM_6_ENABLE_COUNT=data&0x08;
         mTIM_6_LINKING=data&0x07;
         if(data&0x40) mTIM_6_TIMER_DONE=0;
         if(data&0x48) {
            mTIM_6_LAST_COUNT=gSystemCycleCount;
            gNextTimerEvent=gSystemCycleCount;
         }
         break;
      case (TIM7CTLA&0xff):
         mTimerInterruptMask&=(0x80^0xff);
         mTimerInterruptMask|=(data&0x80)?0x80:0x00;
         mTIM_7_ENABLE_RELOAD=data&0x10;
         mTIM_7_ENABLE_COUNT=data&0x08;
         mTIM_7_LINKING=data&0x07;
         if(data&0x40) mTIM_7_TIMER_DONE=0;
         if(data&0x48) {
            mTIM_7_LAST_COUNT=gSystemCycleCount;
            gNextTimerEvent=gSystemCycleCount;
         }
         break;


      case (TIM0CNT&0xff):
         mTIM_0_CURRENT=data;
         gNextTimerEvent=gSystemCycleCount;
         break;
      case (TIM1CNT&0xff):
         mTIM_1_CURRENT=data;
         gNextTimerEvent=gSystemCycleCount;
         break;
      case (TIM2CNT&0xff):
         mTIM_2_CURRENT=data;
         gNextTimerEvent=gSystemCycleCount;
         break;
      case (TIM3CNT&0xff):
         mTIM_3_CURRENT=data;
         gNextTimerEvent=gSystemCycleCount;
         break;
      case (TIM4CNT&0xff):
         mTIM_4_CURRENT=data;
         gNextTimerEvent=gSystemCycleCount;
         break;
      case (TIM5CNT&0xff):
         mTIM_5_CURRENT=data;
         gNextTimerEvent=gSystemCycleCount;
         break;
      case (TIM6CNT&0xff):
         mTIM_6_CURRENT=data;
         gNextTimerEvent=gSystemCycleCount;
         break;
      case (TIM7CNT&0xff):
         mTIM_7_CURRENT=data;
         gNextTimerEvent=gSystemCycleCount;
         break;

      case (TIM0CTLB&0xff):
         mTIM_0_TIMER_DONE=data&0x08;
         mTIM_0_LAST_CLOCK=data&0x04;
         mTIM_0_BORROW_IN=data&0x02;
         mTIM_0_BORROW_OUT=data&0x01;
         //			BlowOut();
         break;
      case (TIM1CTLB&0xff):
         mTIM_1_TIMER_DONE=data&0x08;
         mTIM_1_LAST_CLOCK=data&0x04;
         mTIM_1_BORROW_IN=data&0x02;
         mTIM_1_BORROW_OUT=data&0x01;
         //			BlowOut();
         break;
      case (TIM2CTLB&0xff):
         mTIM_2_TIMER_DONE=data&0x08;
         mTIM_2_LAST_CLOCK=data&0x04;
         mTIM_2_BORROW_IN=data&0x02;
         mTIM_2_BORROW_OUT=data&0x01;
         //			BlowOut();
         break;
      case (TIM3CTLB&0xff):
         mTIM_3_TIMER_DONE=data&0x08;
         mTIM_3_LAST_CLOCK=data&0x04;
         mTIM_3_BORROW_IN=data&0x02;
         mTIM_3_BORROW_OUT=data&0x01;
         //			BlowOut();
         break;
      case (TIM4CTLB&0xff):
         mTIM_4_TIMER_DONE=data&0x08;
         mTIM_4_LAST_CLOCK=data&0x04;
         mTIM_4_BORROW_IN=data&0x02;
         mTIM_4_BORROW_OUT=data&0x01;
         //			BlowOut();
         break;
      case (TIM5CTLB&0xff):
         mTIM_5_TIMER_DONE=data&0x08;
         mTIM_5_LAST_CLOCK=data&0x04;
         mTIM_5_BORROW_IN=data&0x02;
         mTIM_5_BORROW_OUT=data&0x01;
         //			BlowOut();
         break;
      case (TIM6CTLB&0xff):
         mTIM_6_TIMER_DONE=data&0x08;
         mTIM_6_LAST_CLOCK=data&0x04;
         mTIM_6_BORROW_IN=data&0x02;
         mTIM_6_BORROW_OUT=data&0x01;
         //			BlowOut();
         break;
      case (TIM7CTLB&0xff):
         mTIM_7_TIMER_DONE=data&0x08;
         mTIM_7_LAST_CLOCK=data&0x04;
         mTIM_7_BORROW_IN=data&0x02;
         mTIM_7_BORROW_OUT=data&0x01;
         //			BlowOut();
         break;

      case (AUD0VOL&0xff):
         mAUDIO_0_VOLUME=(int8_t)data;
         break;
      case (AUD0SHFTFB&0xff):
         mAUDIO_0_WAVESHAPER&=0x001fff;
         mAUDIO_0_WAVESHAPER|=(ULONG)data<<13;
         break;
      case (AUD0OUTVAL&0xff):
         mAUDIO_OUTPUT[0]=data;
         break;
      case (AUD0L8SHFT&0xff):
         mAUDIO_0_WAVESHAPER&=0x1fff00;
         mAUDIO_0_WAVESHAPER|=data;
         break;
      case (AUD0TBACK&0xff):
         // Counter is disabled when backup is zero for optimisation
         // due to the fact that the output frequency will be above audio
         // range, we must update the last use position to stop problems
         if(!mAUDIO_0_BKUP && data) {
            mAUDIO_0_LAST_COUNT=gSystemCycleCount;
            gNextTimerEvent=gSystemCycleCount;
         }
         mAUDIO_0_BKUP=data;
         break;
      case (AUD0CTL&0xff):
         mAUDIO_0_ENABLE_RELOAD=data&0x10;
         mAUDIO_0_ENABLE_COUNT=data&0x08;
         mAUDIO_0_LINKING=data&0x07;
         mAUDIO_0_INTEGRATE_ENABLE=data&0x20;
         if(data&0x40) mAUDIO_0_TIMER_DONE=0;
         mAUDIO_0_WAVESHAPER&=0x1fefff;
         mAUDIO_0_WAVESHAPER|=(data&0x80)?0x001000:0x000000;
         if(data&0x48) {
            mAUDIO_0_LAST_COUNT=gSystemCycleCount;
            gNextTimerEvent=gSystemCycleCount;
         }
         break;
      case (AUD0COUNT&0xff):
         mAUDIO_0_CURRENT=data;
         break;
      case (AUD0MISC&0xff):
         mAUDIO_0_WAVESHAPER&=0x1ff0ff;
         mAUDIO_0_WAVESHAPER|=(data&0xf0)<<4;
         mAUDIO_0_BORROW_IN=data&0x02;
         mAUDIO_0_BORROW_OUT=data&0x01;
         mAUDIO_0_LAST_CLOCK=data&0x04;
         break;

      case (AUD1VOL&0xff):
         mAUDIO_1_VOLUME=(int8_t)data;
         break;
      case (AUD1SHFTFB&0xff):
         mAUDIO_1_WAVESHAPER&=0x001fff;
         mAUDIO_1_WAVESHAPER|=(ULONG)data<<13;
         break;
      case (AUD1OUTVAL&0xff):
         mAUDIO_OUTPUT[1]=data;
         break;
      case (AUD1L8SHFT&0xff):
         mAUDIO_1_WAVESHAPER&=0x1fff00;
         mAUDIO_1_WAVESHAPER|=data;
         break;
      case (AUD1TBACK&0xff):
         // Counter is disabled when backup is zero for optimisation
         // due to the fact that the output frequency will be above audio
         // range, we must update the last use position to stop problems
         if(!mAUDIO_1_BKUP && data) {
            mAUDIO_1_LAST_COUNT=gSystemCycleCount;
            gNextTimerEvent=gSystemCycleCount;
         }
         mAUDIO_1_BKUP=data;
         break;
      case (AUD1CTL&0xff):
         mAUDIO_1_ENABLE_RELOAD=data&0x10;
         mAUDIO_1_ENABLE_COUNT=data&0x08;
         mAUDIO_1_LINKING=data&0x07;
         mAUDIO_1_INTEGRATE_ENABLE=data&0x20;
         if(data&0x40) mAUDIO_1_TIMER_DONE=0;
         mAUDIO_1_WAVESHAPER&=0x1fefff;
         mAUDIO_1_WAVESHAPER|=(data&0x80)?0x001000:0x000000;
         if(data&0x48) {
            mAUDIO_1_LAST_COUNT=gSystemCycleCount;
            gNextTimerEvent=gSystemCycleCount;
         }
         break;
      case (AUD1COUNT&0xff):
         mAUDIO_1_CURRENT=data;
         break;
      case (AUD1MISC&0xff):
         mAUDIO_1_WAVESHAPER&=0x1ff0ff;
         mAUDIO_1_WAVESHAPER|=(data&0xf0)<<4;
         mAUDIO_1_BORROW_IN=data&0x02;
         mAUDIO_1_BORROW_OUT=data&0x01;
         mAUDIO_1_LAST_CLOCK=data&0x04;
         break;

      case (AUD2VOL&0xff):
         mAUDIO_2_VOLUME=(int8_t)data;
         break;
      case (AUD2SHFTFB&0xff):
         mAUDIO_2_WAVESHAPER&=0x001fff;
         mAUDIO_2_WAVESHAPER|=(ULONG)data<<13;
         break;
      case (AUD2OUTVAL&0xff):
         mAUDIO_OUTPUT[2]=data;
         break;
      case (AUD2L8SHFT&0xff):
         mAUDIO_2_WAVESHAPER&=0x1fff00;
         mAUDIO_2_WAVESHAPER|=data;
         break;
      case (AUD2TBACK&0xff):
         // Counter is disabled when backup is zero for optimisation
         // due to the fact that the output frequency will be above audio
         // range, we must update the last use position to stop problems
         if(!mAUDIO_2_BKUP && data) {
            mAUDIO_2_LAST_COUNT=gSystemCycleCount;
            gNextTimerEvent=gSystemCycleCount;
         }
         mAUDIO_2_BKUP=data;
         break;
      case (AUD2CTL&0xff):
         mAUDIO_2_ENABLE_RELOAD=data&0x10;
         mAUDIO_2_ENABLE_COUNT=data&0x08;
         mAUDIO_2_LINKING=data&0x07;
         mAUDIO_2_INTEGRATE_ENABLE=data&0x20;
         if(data&0x40) mAUDIO_2_TIMER_DONE=0;
         mAUDIO_2_WAVESHAPER&=0x1fefff;
         mAUDIO_2_WAVESHAPER|=(data&0x80)?0x001000:0x000000;
         if(data&0x48) {
            mAUDIO_2_LAST_COUNT=gSystemCycleCount;
            gNextTimerEvent=gSystemCycleCount;
         }
         break;
      case (AUD2COUNT&0xff):
         mAUDIO_2_CURRENT=data;
         break;
      case (AUD2MISC&0xff):
         mAUDIO_2_WAVESHAPER&=0x1ff0ff;
         mAUDIO_2_WAVESHAPER|=(data&0xf0)<<4;
         mAUDIO_2_BORROW_IN=data&0x02;
         mAUDIO_2_BORROW_OUT=data&0x01;
         mAUDIO_2_LAST_CLOCK=data&0x04;
         break;

      case (AUD3VOL&0xff):
         mAUDIO_3_VOLUME=(int8_t)data;
         break;
      case (AUD3SHFTFB&0xff):
         mAUDIO_3_WAVESHAPER&=0x001fff;
         mAUDIO_3_WAVESHAPER|=(ULONG)data<<13;
         break;
      case (AUD3OUTVAL&0xff):
         mAUDIO_OUTPUT[3]=data;
         break;
      case (AUD3L8SHFT&0xff):
         mAUDIO_3_WAVESHAPER&=0x1fff00;
         mAUDIO_3_WAVESHAPER|=data;
         break;
      case (AUD3TBACK&0xff):
         // Counter is disabled when backup is zero for optimisation
         // due to the fact that the output frequency will be above audio
         // range, we must update the last use position to stop problems
         if(!mAUDIO_3_BKUP && data) {
            mAUDIO_3_LAST_COUNT=gSystemCycleCount;
            gNextTimerEvent=gSystemCycleCount;
         }
         mAUDIO_3_BKUP=data;
         break;
      case (AUD3CTL&0xff):
         mAUDIO_3_ENABLE_RELOAD=data&0x10;
         mAUDIO_3_ENABLE_COUNT=data&0x08;
         mAUDIO_3_LINKING=data&0x07;
         mAUDIO_3_INTEGRATE_ENABLE=data&0x20;
         if(data&0x40) mAUDIO_3_TIMER_DONE=0;
         mAUDIO_3_WAVESHAPER&=0x1fefff;
         mAUDIO_3_WAVESHAPER|=(data&0x80)?0x001000:0x000000;
         if(data&0x48) {
            mAUDIO_3_LAST_COUNT=gSystemCycleCount;
            gNextTimerEvent=gSystemCycleCount;
         }
         break;
      case (AUD3COUNT&0xff):
         mAUDIO_3_CURRENT=data;
         break;
      case (AUD3MISC&0xff):
         mAUDIO_3_WAVESHAPER&=0x1ff0ff;
         mAUDIO_3_WAVESHAPER|=(data&0xf0)<<4;
         mAUDIO_3_BORROW_IN=data&0x02;
         mAUDIO_3_BORROW_OUT=data&0x01;
         mAUDIO_3_LAST_CLOCK=data&0x04;
         break;

      case (ATTEN_A&0xff):
         mAUDIO_ATTEN[0] = data;
         break;
      case (ATTEN_B&0xff):
         mAUDIO_ATTEN[1] = data;
         break;
      case (ATTEN_C&0xff):
         mAUDIO_ATTEN[2] = data;
         break;
      case (ATTEN_D&0xff):
         mAUDIO_ATTEN[3] = data;
         break;
      case (MPAN&0xff):
         mPAN = data;
         break;

      case (MSTEREO&0xff):
         mSTEREO=data;
         //			if(!(mSTEREO&0x11) && (data&0x11))
         //			{
         //				mAUDIO_0_LAST_COUNT=gSystemCycleCount;
         //				gNextTimerEvent=gSystemCycleCount;
         //			}
         //			if(!(mSTEREO&0x22) && (data&0x22))
         //			{
         //				mAUDIO_1_LAST_COUNT=gSystemCycleCount;
         //				gNextTimerEvent=gSystemCycleCount;
         //			}
         //			if(!(mSTEREO&0x44) && (data&0x44))
         //			{
         //				mAUDIO_2_LAST_COUNT=gSystemCycleCount;
         //				gNextTimerEvent=gSystemCycleCount;
         //			}
         //			if(!(mSTEREO&0x88) && (data&0x88))
         //			{
         //				mAUDIO_3_LAST_COUNT=gSystemCycleCount;
         //				gNextTimerEvent=gSystemCycleCount;
         //			}
         break;

      case (INTRST&0xff):
         data^=0xff;
         mTimerStatusFlags&=data;
         gNextTimerEvent=gSystemCycleCount;
         // 22/09/06 Fix to championship rally, IRQ not getting cleared with edge triggered system
         gSystemIRQ=(mTimerStatusFlags&mTimerInterruptMask)?TRUE:FALSE;
         // 22/09/06 Fix to championship rally, IRQ not getting cleared with edge triggered system
         break;

      case (INTSET&0xff):
         mTimerStatusFlags|=data;
         // 22/09/06 Fix to championship rally, IRQ not getting cleared with edge triggered system
         gSystemIRQ=(mTimerStatusFlags&mTimerInterruptMask)?TRUE:FALSE;
         // 22/09/06 Fix to championship rally, IRQ not getting cleared with edge triggered system
         gNextTimerEvent=gSystemCycleCount;
         break;

      case (SYSCTL1&0xff):
         if(!(data&0x02)) {
            char addr[256];
            C6502_REGS regs;
            mSystem.GetRegs(regs);
            sprintf(addr,"Runtime Alert - System Halted\nCMikie::Poke(SYSCTL1) - Lynx power down occured at PC=$%04x.\nResetting system.",regs.PC);
            if(gError) gError->Warning(addr);
            mSystem.Reset();
            gSystemHalt=TRUE;
         }
         mSystem.CartAddressStrobe((data&0x01)?TRUE:FALSE);
         if(mSystem.mEEPROM->Available()) mSystem.mEEPROM->ProcessEepromCounter(mSystem.mCart->GetCounterValue());
         break;

      case (MIKEYSREV&0xff):
         break;

      case (IODIR&0xff):
         mIODIR=data;
         if(mSystem.mEEPROM->Available()) mSystem.mEEPROM->ProcessEepromIO(mIODIR,mIODAT);
         break;

      case (IODAT&0xff):
         mIODAT=data;
         mSystem.CartAddressData((mIODAT&0x02)?TRUE:FALSE);
         // Enable cart writes to BANK1 on AUDIN if AUDIN is set to output
         if(mIODIR&0x10) mSystem.mCart->mWriteEnableBank1=(mIODAT&0x10)?TRUE:FALSE;// there is no reason to use AUDIN as Write Enable or latch. private patch??? TODO
         if(mSystem.mEEPROM->Available()) mSystem.mEEPROM->ProcessEepromIO(mIODIR,mIODAT);
         break;

      case (SERCTL&0xff):
         mUART_TX_IRQ_ENABLE=(data&0x80)?true:false;
         mUART_RX_IRQ_ENABLE=(data&0x40)?true:false;
         mUART_PARITY_ENABLE=(data&0x10)?true:false;
         mUART_SENDBREAK=data&0x02;
         mUART_PARITY_EVEN=data&0x01;

         // Reset all errors if required
         if(data&0x08) {
            mUART_Rx_overun_error=0;
            mUART_Rx_framing_error=0;
         }

         if(mUART_SENDBREAK) {
            // Trigger send break, it will self sustain as long as sendbreak is set
            mUART_TX_COUNTDOWN=UART_TX_TIME_PERIOD;
            // Loop back what we transmitted
            ComLynxTxLoopback(UART_BREAK_CODE);
         }
         break;

      case (SERDAT&0xff):
         //
         // Fake transmission, set counter to be decremented by Timer 4
         //
         // ComLynx only has one output pin, hence Rx & Tx are shorted
         // therefore any transmitted data will loopback
         //
         mUART_TX_DATA=data;
         // Calculate Parity data
         if(mUART_PARITY_ENABLE) {
            // Calc parity value
            // Leave at zero !!
         } else {
            // If disabled then the PAREVEN bit is sent
            if(mUART_PARITY_EVEN) data|=0x0100;
         }
         // Set countdown to transmission
         mUART_TX_COUNTDOWN=UART_TX_TIME_PERIOD;
         // Loop back what we transmitted
         ComLynxTxLoopback(mUART_TX_DATA);
         break;

      case (SDONEACK&0xff):
         break;
      case (CPUSLEEP&0xff):
         //
         // We must do "cycles_used" cycles of the system with the CPU sleeping
         // to compensate for the sprite painting, Mikie update will autowake the
         // CPU at the right time.
         //
         {
            int32_t cycles_used=(int32_t)mSystem.PaintSprites();
            gCPUWakeupTime=gSystemCycleCount+cycles_used;
            SetCPUSleep();
         }
         break;

      case (DISPCTL&0xff):
         {
            TDISPCTL tmp;
            tmp.Byte=data;
            mDISPCTL_DMAEnable=tmp.Bits.DMAEnable;
            mDISPCTL_Flip=tmp.Bits.Flip;
            mDISPCTL_FourColour=tmp.Bits.FourColour;
            mDISPCTL_Colour=tmp.Bits.Colour;
         }
         break;
      case (PBKUP&0xff):
         break;

      case (DISPADRL&0xff):
         mDisplayAddress&=0xff00;
         mDisplayAddress+=data;
         break;

      case (DISPADRH&0xff):
         mDisplayAddress&=0x00ff;
         mDisplayAddress+=(data<<8);
         break;

      case (Mtest0&0xff):
      case (Mtest1&0xff):
         // Test registers are unimplemented
         // lets hope no programs use them.
      case (Mtest2&0xff):
         // Test registers are unimplemented
         // lets hope no programs use them.
         if(gError) gError->Warning("CMikie::Poke() - Write to MTEST2");
         break;

      case (0xfd97&0xff): {
         // This code is to intercept calls to the fake ROM
         int mPC = mSystem.mCpu->GetPC();
         if(mPC>=0xFE00 && mPC<0xFFF0) {
            switch(mPC) {
               case 0xFE00+3:
                  mSystem.HLE_BIOS_FE00();
                  break;
               case 0xFE19+3:
                  mSystem.HLE_BIOS_FE19();
                  break;
               case 0xFE4A+3:
                  mSystem.HLE_BIOS_FE4A();
                  break;
               case 0xFF80+3:
                  mSystem.HLE_BIOS_FF80();
                  break;
               default:
                  handy_log(RETRO_LOG_ERROR, "ROM code missing...\n");
                  break;
               }
            }
         };
         break;
      case (GREEN0&0xff):
      case (GREEN1&0xff):
      case (GREEN2&0xff):
      case (GREEN3&0xff):
      case (GREEN4&0xff):
      case (GREEN5&0xff):
      case (GREEN6&0xff):
      case (GREEN7&0xff):
      case (GREEN8&0xff):
      case (GREEN9&0xff):
      case (GREENA&0xff):
      case (GREENB&0xff):
      case (GREENC&0xff):
      case (GREEND&0xff):
      case (GREENE&0xff):
      case (GREENF&0xff):
         mPalette[addr&0x0f].Colours.Green=data&0x0f;
         break;

      case (BLUERED0&0xff):
      case (BLUERED1&0xff):
      case (BLUERED2&0xff):
      case (BLUERED3&0xff):
      case (BLUERED4&0xff):
      case (BLUERED5&0xff):
      case (BLUERED6&0xff):
      case (BLUERED7&0xff):
      case (BLUERED8&0xff):
      case (BLUERED9&0xff):
      case (BLUEREDA&0xff):
      case (BLUEREDB&0xff):
      case (BLUEREDC&0xff):
      case (BLUEREDD&0xff):
      case (BLUEREDE&0xff):
      case (BLUEREDF&0xff):
         mPalette[addr&0x0f].Colours.Blue=(data&0xf0)>>4;
         mPalette[addr&0x0f].Colours.Red=data&0x0f;
         break;

         // Errors on read only register accesses

      case (MAGRDY0&0xff):
      case (MAGRDY1&0xff):
      case (AUDIN&0xff):
      case (MIKEYHREV&0xff):
         break;

         // Errors on illegal location accesses

      default:
         break;
   }

   if(addr >= AUD0VOL && addr <= MSTEREO)
	  UpdateSound();
}



UBYTE CMikie::Peek(ULONG addr)
{
   switch(addr & 0xff) {
   // Timer control registers
      case (TIM0BKUP&0xff):
         return (UBYTE)mTIM_0_BKUP;
      case (TIM1BKUP&0xff):
         return (UBYTE)mTIM_1_BKUP;
      case (TIM2BKUP&0xff):
         return (UBYTE)mTIM_2_BKUP;
      case (TIM3BKUP&0xff):
         return (UBYTE)mTIM_3_BKUP;
      case (TIM4BKUP&0xff):
         return (UBYTE)mTIM_4_BKUP;
      case (TIM5BKUP&0xff):
         return (UBYTE)mTIM_5_BKUP;
      case (TIM6BKUP&0xff):
         return (UBYTE)mTIM_6_BKUP;
      case (TIM7BKUP&0xff):
         return (UBYTE)mTIM_7_BKUP;
      case (TIM0CTLA&0xff): {
         UBYTE retval=0;
         retval|=(mTimerInterruptMask&0x01)?0x80:0x00;
         retval|=(mTIM_0_ENABLE_RELOAD)?0x10:0x00;
         retval|=(mTIM_0_ENABLE_COUNT)?0x08:0x00;
         retval|=mTIM_0_LINKING;
         return retval;
      }
      case (TIM1CTLA&0xff): {
         UBYTE retval=0;
         retval|=(mTimerInterruptMask&0x02)?0x80:0x00;
         retval|=(mTIM_1_ENABLE_RELOAD)?0x10:0x00;
         retval|=(mTIM_1_ENABLE_COUNT)?0x08:0x00;
         retval|=mTIM_1_LINKING;
         return retval;
      }
      case (TIM2CTLA&0xff): {
         UBYTE retval=0;
         retval|=(mTimerInterruptMask&0x04)?0x80:0x00;
         retval|=(mTIM_2_ENABLE_RELOAD)?0x10:0x00;
         retval|=(mTIM_2_ENABLE_COUNT)?0x08:0x00;
         retval|=mTIM_2_LINKING;
         return retval;
      }
      case (TIM3CTLA&0xff): {
         UBYTE retval=0;
         retval|=(mTimerInterruptMask&0x08)?0x80:0x00;
         retval|=(mTIM_3_ENABLE_RELOAD)?0x10:0x00;
         retval|=(mTIM_3_ENABLE_COUNT)?0x08:0x00;
         retval|=mTIM_3_LINKING;
         return retval;
      }
      case (TIM4CTLA&0xff): {
         UBYTE retval=0;
         retval|=(mTimerInterruptMask&0x10)?0x80:0x00;
         retval|=(mTIM_4_ENABLE_RELOAD)?0x10:0x00;
         retval|=(mTIM_4_ENABLE_COUNT)?0x08:0x00;
         retval|=mTIM_4_LINKING;
         return retval;
      }
      case (TIM5CTLA&0xff): {
         UBYTE retval=0;
         retval|=(mTimerInterruptMask&0x20)?0x80:0x00;
         retval|=(mTIM_5_ENABLE_RELOAD)?0x10:0x00;
         retval|=(mTIM_5_ENABLE_COUNT)?0x08:0x00;
         retval|=mTIM_5_LINKING;
         return retval;
      }
      case (TIM6CTLA&0xff): {
         UBYTE retval=0;
         retval|=(mTimerInterruptMask&0x40)?0x80:0x00;
         retval|=(mTIM_6_ENABLE_RELOAD)?0x10:0x00;
         retval|=(mTIM_6_ENABLE_COUNT)?0x08:0x00;
         retval|=mTIM_6_LINKING;
         return retval;
      }
      case (TIM7CTLA&0xff): {
         UBYTE retval=0;
         retval|=(mTimerInterruptMask&0x80)?0x80:0x00;
         retval|=(mTIM_7_ENABLE_RELOAD)?0x10:0x00;
         retval|=(mTIM_7_ENABLE_COUNT)?0x08:0x00;
         retval|=mTIM_7_LINKING;
         return retval;
      }
      case (TIM0CNT&0xff):
         Update();
         return (UBYTE)mTIM_0_CURRENT;
      case (TIM1CNT&0xff):
         Update();
         return (UBYTE)mTIM_1_CURRENT;
      case (TIM2CNT&0xff):
         Update();
         return (UBYTE)mTIM_2_CURRENT;
      case (TIM3CNT&0xff):
         Update();
         return (UBYTE)mTIM_3_CURRENT;
      case (TIM4CNT&0xff):
         Update();
         return (UBYTE)mTIM_4_CURRENT;
      case (TIM5CNT&0xff):
         Update();
         return (UBYTE)mTIM_5_CURRENT;
      case (TIM6CNT&0xff):
         Update();
         return (UBYTE)mTIM_6_CURRENT;
      case (TIM7CNT&0xff):
         Update();
         return (UBYTE)mTIM_7_CURRENT;

      case (TIM0CTLB&0xff): {
         UBYTE retval=0;
         retval|=(mTIM_0_TIMER_DONE)?0x08:0x00;
         retval|=(mTIM_0_LAST_CLOCK)?0x04:0x00;
         retval|=(mTIM_0_BORROW_IN)?0x02:0x00;
         retval|=(mTIM_0_BORROW_OUT)?0x01:0x00;
         return retval;
      }
      case (TIM1CTLB&0xff): {
         UBYTE retval=0;
         retval|=(mTIM_1_TIMER_DONE)?0x08:0x00;
         retval|=(mTIM_1_LAST_CLOCK)?0x04:0x00;
         retval|=(mTIM_1_BORROW_IN)?0x02:0x00;
         retval|=(mTIM_1_BORROW_OUT)?0x01:0x00;
         return retval;
      }
      case (TIM2CTLB&0xff): {
         UBYTE retval=0;
         retval|=(mTIM_2_TIMER_DONE)?0x08:0x00;
         retval|=(mTIM_2_LAST_CLOCK)?0x04:0x00;
         retval|=(mTIM_2_BORROW_IN)?0x02:0x00;
         retval|=(mTIM_2_BORROW_OUT)?0x01:0x00;
         return retval;
      }
      case (TIM3CTLB&0xff): {
         UBYTE retval=0;
         retval|=(mTIM_3_TIMER_DONE)?0x08:0x00;
         retval|=(mTIM_3_LAST_CLOCK)?0x04:0x00;
         retval|=(mTIM_3_BORROW_IN)?0x02:0x00;
         retval|=(mTIM_3_BORROW_OUT)?0x01:0x00;
         return retval;
      }
      case (TIM4CTLB&0xff): {
         UBYTE retval=0;
         retval|=(mTIM_4_TIMER_DONE)?0x08:0x00;
         retval|=(mTIM_4_LAST_CLOCK)?0x04:0x00;
         retval|=(mTIM_4_BORROW_IN)?0x02:0x00;
         retval|=(mTIM_4_BORROW_OUT)?0x01:0x00;
         return retval;
      }
      case (TIM5CTLB&0xff): {
         UBYTE retval=0;
         retval|=(mTIM_5_TIMER_DONE)?0x08:0x00;
         retval|=(mTIM_5_LAST_CLOCK)?0x04:0x00;
         retval|=(mTIM_5_BORROW_IN)?0x02:0x00;
         retval|=(mTIM_5_BORROW_OUT)?0x01:0x00;
         return retval;
      }
      case (TIM6CTLB&0xff): {
         UBYTE retval=0;
         retval|=(mTIM_6_TIMER_DONE)?0x08:0x00;
         retval|=(mTIM_6_LAST_CLOCK)?0x04:0x00;
         retval|=(mTIM_6_BORROW_IN)?0x02:0x00;
         retval|=(mTIM_6_BORROW_OUT)?0x01:0x00;
         return retval;
      }
      case (TIM7CTLB&0xff): {
         UBYTE retval=0;
         retval|=(mTIM_7_TIMER_DONE)?0x08:0x00;
         retval|=(mTIM_7_LAST_CLOCK)?0x04:0x00;
         retval|=(mTIM_7_BORROW_IN)?0x02:0x00;
         retval|=(mTIM_7_BORROW_OUT)?0x01:0x00;
         return retval;
      }

      // Audio control registers

      case (AUD0VOL&0xff):
         return (UBYTE)mAUDIO_0_VOLUME;
      case (AUD0SHFTFB&0xff):
         return (UBYTE)((mAUDIO_0_WAVESHAPER>>13)&0xff);
      case (AUD0OUTVAL&0xff):
         return (UBYTE)mAUDIO_OUTPUT[0];
      case (AUD0L8SHFT&0xff):
         return (UBYTE)(mAUDIO_0_WAVESHAPER&0xff);
      case (AUD0TBACK&0xff):
         return (UBYTE)mAUDIO_0_BKUP;
      case (AUD0CTL&0xff): {
         UBYTE retval=0;
         retval|=(mAUDIO_0_INTEGRATE_ENABLE)?0x20:0x00;
         retval|=(mAUDIO_0_ENABLE_RELOAD)?0x10:0x00;
         retval|=(mAUDIO_0_ENABLE_COUNT)?0x08:0x00;
         retval|=(mAUDIO_0_WAVESHAPER&0x001000)?0x80:0x00;
         retval|=mAUDIO_0_LINKING;
         return retval;
      }
      case (AUD0COUNT&0xff):
         return (UBYTE)mAUDIO_0_CURRENT;
      case (AUD0MISC&0xff): {
         UBYTE retval=0;
         retval|=(mAUDIO_0_BORROW_OUT)?0x01:0x00;
         retval|=(mAUDIO_0_BORROW_IN)?0x02:0x00;
         retval|=(mAUDIO_0_LAST_CLOCK)?0x08:0x00;
         retval|=(mAUDIO_0_WAVESHAPER>>4)&0xf0;
         return retval;
      }

      case (AUD1VOL&0xff):
         return (UBYTE)mAUDIO_1_VOLUME;
      case (AUD1SHFTFB&0xff):
         return (UBYTE)((mAUDIO_1_WAVESHAPER>>13)&0xff);
      case (AUD1OUTVAL&0xff):
         return (UBYTE)mAUDIO_OUTPUT[1];
      case (AUD1L8SHFT&0xff):
         return (UBYTE)(mAUDIO_1_WAVESHAPER&0xff);
      case (AUD1TBACK&0xff):
         return (UBYTE)mAUDIO_1_BKUP;
      case (AUD1CTL&0xff): {
         UBYTE retval=0;
         retval|=(mAUDIO_1_INTEGRATE_ENABLE)?0x20:0x00;
         retval|=(mAUDIO_1_ENABLE_RELOAD)?0x10:0x00;
         retval|=(mAUDIO_1_ENABLE_COUNT)?0x08:0x00;
         retval|=(mAUDIO_1_WAVESHAPER&0x001000)?0x80:0x00;
         retval|=mAUDIO_1_LINKING;
         return retval;
      }
      case (AUD1COUNT&0xff):
         return (UBYTE)mAUDIO_1_CURRENT;
      case (AUD1MISC&0xff): {
         UBYTE retval=0;
         retval|=(mAUDIO_1_BORROW_OUT)?0x01:0x00;
         retval|=(mAUDIO_1_BORROW_IN)?0x02:0x00;
         retval|=(mAUDIO_1_LAST_CLOCK)?0x08:0x00;
         retval|=(mAUDIO_1_WAVESHAPER>>4)&0xf0;
         return retval;
      }

      case (AUD2VOL&0xff):
         return (UBYTE)mAUDIO_2_VOLUME;
      case (AUD2SHFTFB&0xff):
         return (UBYTE)((mAUDIO_2_WAVESHAPER>>13)&0xff);
      case (AUD2OUTVAL&0xff):
         return (UBYTE)mAUDIO_OUTPUT[2];
      case (AUD2L8SHFT&0xff):
         return (UBYTE)(mAUDIO_2_WAVESHAPER&0xff);
      case (AUD2TBACK&0xff):
         return (UBYTE)mAUDIO_2_BKUP;
      case (AUD2CTL&0xff): {
         UBYTE retval=0;
         retval|=(mAUDIO_2_INTEGRATE_ENABLE)?0x20:0x00;
         retval|=(mAUDIO_2_ENABLE_RELOAD)?0x10:0x00;
         retval|=(mAUDIO_2_ENABLE_COUNT)?0x08:0x00;
         retval|=(mAUDIO_2_WAVESHAPER&0x001000)?0x80:0x00;
         retval|=mAUDIO_2_LINKING;
         return retval;
      }
      case (AUD2COUNT&0xff):
         return (UBYTE)mAUDIO_2_CURRENT;
      case (AUD2MISC&0xff): {
         UBYTE retval=0;
         retval|=(mAUDIO_2_BORROW_OUT)?0x01:0x00;
         retval|=(mAUDIO_2_BORROW_IN)?0x02:0x00;
         retval|=(mAUDIO_2_LAST_CLOCK)?0x08:0x00;
         retval|=(mAUDIO_2_WAVESHAPER>>4)&0xf0;
         return retval;
      }

      case (AUD3VOL&0xff):
         return (UBYTE)mAUDIO_3_VOLUME;
      case (AUD3SHFTFB&0xff):
         return (UBYTE)((mAUDIO_3_WAVESHAPER>>13)&0xff);
      case (AUD3OUTVAL&0xff):
         return (UBYTE)mAUDIO_OUTPUT[3];
      case (AUD3L8SHFT&0xff):
         return (UBYTE)(mAUDIO_3_WAVESHAPER&0xff);
      case (AUD3TBACK&0xff):
         return (UBYTE)mAUDIO_3_BKUP;
      case (AUD3CTL&0xff): {
         UBYTE retval=0;
         retval|=(mAUDIO_3_INTEGRATE_ENABLE)?0x20:0x00;
         retval|=(mAUDIO_3_ENABLE_RELOAD)?0x10:0x00;
         retval|=(mAUDIO_3_ENABLE_COUNT)?0x08:0x00;
         retval|=(mAUDIO_3_WAVESHAPER&0x001000)?0x80:0x00;
         retval|=mAUDIO_3_LINKING;
         return retval;
      }
      case (AUD3COUNT&0xff):
         return (UBYTE)mAUDIO_3_CURRENT;
      case (AUD3MISC&0xff): {
         UBYTE retval=0;
         retval|=(mAUDIO_3_BORROW_OUT)?0x01:0x00;
         retval|=(mAUDIO_3_BORROW_IN)?0x02:0x00;
         retval|=(mAUDIO_3_LAST_CLOCK)?0x08:0x00;
         retval|=(mAUDIO_3_WAVESHAPER>>4)&0xf0;
         return retval;
      }

      case (ATTEN_A&0xff):
         return (UBYTE) mAUDIO_ATTEN[0];
      case (ATTEN_B&0xff):
         return (UBYTE) mAUDIO_ATTEN[1];
      case (ATTEN_C&0xff):
         return (UBYTE) mAUDIO_ATTEN[2];
      case (ATTEN_D&0xff):
         return (UBYTE) mAUDIO_ATTEN[3];
      case (MPAN&0xff):
         return (UBYTE) mPAN;

      case (MSTEREO&0xff):
         return (UBYTE) mSTEREO;

         // Miscellaneous registers

      case (SERCTL&0xff): {
         ULONG retval=0;
         retval|=(mUART_TX_COUNTDOWN&UART_TX_INACTIVE)?0xA0:0x00;	// Indicate TxDone & TxAllDone
         retval|=(mUART_RX_READY)?0x40:0x00;							// Indicate Rx data ready
         retval|=(mUART_Rx_overun_error)?0x08:0x0;					// Framing error
         retval|=(mUART_Rx_framing_error)?0x04:0x00;					// Rx overrun
         retval|=(mUART_RX_DATA&UART_BREAK_CODE)?0x02:0x00;			// Indicate break received
         retval|=(mUART_RX_DATA&0x0100)?0x01:0x00;					// Add parity bit
         return (UBYTE)retval;
      }

      case (SERDAT&0xff):
         mUART_RX_READY=0;
         return (UBYTE)(mUART_RX_DATA&0xff);

      case (IODAT&0xff): {
         ULONG retval=0;
         // IODIR  = output bit : input high (eeprom write done)
         if(mSystem.mEEPROM->Available()) {
            mSystem.mEEPROM->ProcessEepromBusy();
            retval|=(mIODIR&0x10)?mIODAT&0x10:(mSystem.mEEPROM->OutputBit()?0x10:0x00);
         } else {
            retval|=mIODAT&0x10;
         }
         retval|=(mIODIR&0x08)?(((mIODAT&0x08)&&mIODAT_REST_SIGNAL)?0x00:0x08):0x00;									// REST   = output bit : input low
         retval|=(mIODIR&0x04)?mIODAT&0x04:((mUART_CABLE_PRESENT)?0x04:0x00);	// NOEXP  = output bit : input low
         retval|=(mIODIR&0x02)?mIODAT&0x02:0x00;									// CARTAD = output bit : input low
         retval|=(mIODIR&0x01)?mIODAT&0x01:0x01;									// EXTPW  = output bit : input high (Power connected)
         return (UBYTE)retval;
      }

      case (INTRST&0xff):
      case (INTSET&0xff):
         return (UBYTE)mTimerStatusFlags;
      case (MAGRDY0&0xff):
      case (MAGRDY1&0xff):
         return 0x00;
      case (AUDIN&0xff):
         //			if(mAudioInputComparator) return 0x80; else return 0x00;
         return 0x80;
      case (MIKEYHREV&0xff):
         return 0x01;

      // Pallette registers

      case (GREEN0&0xff):
      case (GREEN1&0xff):
      case (GREEN2&0xff):
      case (GREEN3&0xff):
      case (GREEN4&0xff):
      case (GREEN5&0xff):
      case (GREEN6&0xff):
      case (GREEN7&0xff):
      case (GREEN8&0xff):
      case (GREEN9&0xff):
      case (GREENA&0xff):
      case (GREENB&0xff):
      case (GREENC&0xff):
      case (GREEND&0xff):
      case (GREENE&0xff):
      case (GREENF&0xff):
         return mPalette[addr&0x0f].Colours.Green;
      case (BLUERED0&0xff):
      case (BLUERED1&0xff):
      case (BLUERED2&0xff):
      case (BLUERED3&0xff):
      case (BLUERED4&0xff):
      case (BLUERED5&0xff):
      case (BLUERED6&0xff):
      case (BLUERED7&0xff):
      case (BLUERED8&0xff):
      case (BLUERED9&0xff):
      case (BLUEREDA&0xff):
      case (BLUEREDB&0xff):
      case (BLUEREDC&0xff):
      case (BLUEREDD&0xff):
      case (BLUEREDE&0xff):
      case (BLUEREDF&0xff):
         return (mPalette[addr&0x0f].Colours.Red | (mPalette[addr&0x0f].Colours.Blue<<4));
         // Errors on write only register accesses

      // For easier debugging

      case (DISPADRL&0xff):
         return (UBYTE)(mDisplayAddress&0xff);
      case (DISPADRH&0xff):
         return (UBYTE)(mDisplayAddress>>8)&0xff;

      case (DISPCTL&0xff):
      case (SYSCTL1&0xff):
      case (MIKEYSREV&0xff):
      case (IODIR&0xff):
      case (SDONEACK&0xff):
      case (CPUSLEEP&0xff):
      case (PBKUP&0xff):
      case (Mtest0&0xff):
      case (Mtest1&0xff):
      case (Mtest2&0xff):
         break;

      // Register to let programs know handy is running

      case (0xfd97&0xff):
         //			gError->Warning("EMULATOR DETECT REGISTER HAS BEEN READ");
         break;
         //return 0x42;
         // Errors on illegal location accesses

      default:
         break;
   }
   return 0xff;
}

inline void CMikie::Update(void)
{
   int32_t divide;
   int32_t decval;
   ULONG tmp;
   ULONG mikie_work_done=0;

   //
   // To stop problems with cycle count wrap we will check and then correct the
   // cycle counter.
   //

   //			("Update()");

   if(gSystemCycleCount>0xf0000000) {
      gSystemCycleCount-=0x80000000;
      gLastRunCycleCount-=0x80000000;
      gThrottleNextCycleCheckpoint-=0x80000000;
      gAudioLastUpdateCycle-=0x80000000;
      mTIM_0_LAST_COUNT-=0x80000000;
      mTIM_1_LAST_COUNT-=0x80000000;
      mTIM_2_LAST_COUNT-=0x80000000;
      mTIM_3_LAST_COUNT-=0x80000000;
      mTIM_4_LAST_COUNT-=0x80000000;
      mTIM_5_LAST_COUNT-=0x80000000;
      mTIM_6_LAST_COUNT-=0x80000000;
      mTIM_7_LAST_COUNT-=0x80000000;
      mAUDIO_0_LAST_COUNT-=0x80000000;
      mAUDIO_1_LAST_COUNT-=0x80000000;
      mAUDIO_2_LAST_COUNT-=0x80000000;
      mAUDIO_3_LAST_COUNT-=0x80000000;
      // Only correct if sleep is active
      if(gCPUWakeupTime) {
         gCPUWakeupTime-=0x80000000;
         gIRQEntryCycle-=0x80000000;
      }
   }

   gNextTimerEvent=0xffffffff;

   //
   // Check if the CPU needs to be woken up from sleep mode
   //
   if(gCPUWakeupTime)
   {
      if(gSystemCycleCount>=gCPUWakeupTime)
      {
         ClearCPUSleep();
         gCPUWakeupTime=0;
      }
      else
      {
         if(gCPUWakeupTime>gSystemCycleCount) gNextTimerEvent=gCPUWakeupTime;
      }
   }

   //	Timer updates, rolled out flat in group order
   //
   //	Group A:
   //	Timer 0 -> Timer 2 -> Timer 4.
   //
   //	Group B:
   //	Timer 1 -> Timer 3 -> Timer 5 -> Timer 7 -> Audio 0 -> Audio 1-> Audio 2 -> Audio 3 -> Timer 1.
   //

   //
   // Within each timer code block we will predict the cycle count number of
   // the next timer event
   //
   // We don't need to count linked timers as the timer they are linked
   // from will always generate earlier events.
   //
   // As Timer 4 (UART) will generate many events we will ignore it
   //
   // We set the next event to the end of time at first and let the timers
   // overload it. Any writes to timer controls will force next event to
   // be immediate and hence a new preidction will be done. The prediction
   // causes overflow as opposed to zero i.e. current+1
   // (In reality T0 line counter should always be running.)
   //


   //
   // Timer 0 of Group A
   //

   //
   // Optimisation, assume T0 (Line timer) is never in one-shot,
   // never placed in link mode
   //

   // KW bugfix 13/4/99 added (mTIM_x_ENABLE_RELOAD ||  ..)
   //			if(mTIM_0_ENABLE_COUNT && (mTIM_0_ENABLE_RELOAD || !mTIM_0_TIMER_DONE))
   if(mTIM_0_ENABLE_COUNT) {
      // Timer 0 has no linking
      //				if(mTIM_0_LINKING!=0x07)
      {
         // Ordinary clocked mode as opposed to linked mode
         // 16MHz clock downto 1us == cyclecount >> 4
         divide=(4+mTIM_0_LINKING);
         decval=(gSystemCycleCount-mTIM_0_LAST_COUNT)>>divide;

         if(decval) {
            mTIM_0_LAST_COUNT+=decval<<divide;
            mTIM_0_CURRENT-=decval;

            if(mTIM_0_CURRENT&0x80000000) {
               // Set carry out
               mTIM_0_BORROW_OUT=TRUE;

               //							// Reload if neccessary
               //							if(mTIM_0_ENABLE_RELOAD)
               //							{
               mTIM_0_CURRENT+=mTIM_0_BKUP+1;
               //							}
               //							else
               //							{
               //								mTIM_0_CURRENT=0;
               //							}

               mTIM_0_TIMER_DONE=TRUE;

               // Interupt flag setting code moved into DisplayRenderLine()

               // Line timer has expired, render a line, we cannot incrememnt
               // the global counter at this point as it will screw the other timers
               // so we save under work done and inc at the end.
               mikie_work_done+=DisplayRenderLine();

            } else {
               mTIM_0_BORROW_OUT=FALSE;
            }
            // Set carry in as we did a count
            mTIM_0_BORROW_IN=TRUE;
         } else {
            // Clear carry in as we didn't count
            mTIM_0_BORROW_IN=FALSE;
            // Clear carry out
            mTIM_0_BORROW_OUT=FALSE;
         }
      }

      // Prediction for next timer event cycle number

      //				if(mTIM_0_LINKING!=7)
      {
         // Sometimes timeupdates can be >2x rollover in which case
         // then CURRENT may still be negative and we can use it to
         // calc the next timer value, we just want another update ASAP
         tmp=(mTIM_0_CURRENT&0x80000000)?1:((mTIM_0_CURRENT+1)<<divide);
         tmp+=gSystemCycleCount;
         if(tmp<gNextTimerEvent) {
            gNextTimerEvent=tmp;
         }
      }
   }

   //
   // Timer 2 of Group A
   //

   //
   // Optimisation, assume T2 (Frame timer) is never in one-shot
   // always in linked mode i.e clocked by Line Timer
   //

   // KW bugfix 13/4/99 added (mTIM_x_ENABLE_RELOAD ||  ..)
   //			if(mTIM_2_ENABLE_COUNT && (mTIM_2_ENABLE_RELOAD || !mTIM_2_TIMER_DONE))
   if(mTIM_2_ENABLE_COUNT) {
      decval=0;

      //				if(mTIM_2_LINKING==0x07)
      {
         if(mTIM_0_BORROW_OUT) decval=1;
         mTIM_2_LAST_LINK_CARRY=mTIM_0_BORROW_OUT;
      }
      //				else
      //				{
      //					// Ordinary clocked mode as opposed to linked mode
      //					// 16MHz clock downto 1us == cyclecount >> 4
      //					divide=(4+mTIM_2_LINKING);
      //					decval=(gSystemCycleCount-mTIM_2_LAST_COUNT)>>divide;
      //				}

      if(decval) {
         //					mTIM_2_LAST_COUNT+=decval<<divide;
         mTIM_2_CURRENT-=decval;
         if(mTIM_2_CURRENT&0x80000000) {
            // Set carry out
            mTIM_2_BORROW_OUT=TRUE;

            //						// Reload if neccessary
            //						if(mTIM_2_ENABLE_RELOAD)
            //						{
            mTIM_2_CURRENT+=mTIM_2_BKUP+1;
            //						}
            //						else
            //						{
            //							mTIM_2_CURRENT=0;
            //						}
            mTIM_2_TIMER_DONE=TRUE;

            // Interupt flag setting code moved into DisplayEndOfFrame(), also
            // park any CPU cycles lost for later inclusion
            mikie_work_done+=DisplayEndOfFrame();
         } else {
            mTIM_2_BORROW_OUT=FALSE;
         }
         // Set carry in as we did a count
         mTIM_2_BORROW_IN=TRUE;
      } else {
         // Clear carry in as we didn't count
         mTIM_2_BORROW_IN=FALSE;
         // Clear carry out
         mTIM_2_BORROW_OUT=FALSE;
      }

      // Prediction for next timer event cycle number
      // We dont need to predict this as its the frame timer and will always
      // be beaten by the line timer on Timer 0
      //				if(mTIM_2_LINKING!=7)
      //				{
      //					tmp=gSystemCycleCount+((mTIM_2_CURRENT+1)<<divide);
      //					if(tmp<gNextTimerEvent)	gNextTimerEvent=tmp;
      //				}
   }

   //
   // Timer 4 of Group A
   //
   // For the sake of speed it is assumed that Timer 4 (UART timer)
   // never uses one-shot mode, never uses linking, hence the code
   // is commented out. Timer 4 is at the end of a chain and seems
   // no reason to update its carry in-out variables
   //

   // KW bugfix 13/4/99 added (mTIM_x_ENABLE_RELOAD ||  ..)
   //			if(mTIM_4_ENABLE_COUNT && (mTIM_4_ENABLE_RELOAD || !mTIM_4_TIMER_DONE))
   if(mTIM_4_ENABLE_COUNT) {
      decval=0;

      //				if(mTIM_4_LINKING==0x07)
      //				{
      ////				if(mTIM_2_BORROW_OUT && !mTIM_4_LAST_LINK_CARRY) decval=1;
      //					if(mTIM_2_BORROW_OUT) decval=1;
      //					mTIM_4_LAST_LINK_CARRY=mTIM_2_BORROW_OUT;
      //				}
      //				else
      {
         // Ordinary clocked mode as opposed to linked mode
         // 16MHz clock downto 1us == cyclecount >> 4
         // Additional /8 (+3) for 8 clocks per bit transmit
         divide=4+3+mTIM_4_LINKING;
         decval=(gSystemCycleCount-mTIM_4_LAST_COUNT)>>divide;
      }

      if(decval) {
         mTIM_4_LAST_COUNT+=decval<<divide;
         mTIM_4_CURRENT-=decval;
         if(mTIM_4_CURRENT&0x80000000) {
            // Set carry out
            mTIM_4_BORROW_OUT=TRUE;

            //
            // Update the UART counter models for Rx & Tx
            //

            //
            // According to the docs IRQ's are level triggered and hence will always assert
            // what a pain in the arse
            //
            // Rx & Tx are loopedback due to comlynx structure

            //
            // Receive
            //
            if(!mUART_RX_COUNTDOWN) {
               // Fetch a byte from the input queue
               if(mUART_Rx_waiting>0) {
                  mUART_RX_DATA=mUART_Rx_input_queue[mUART_Rx_output_ptr];
                  mUART_Rx_output_ptr=(++mUART_Rx_output_ptr)%UART_MAX_RX_QUEUE;
                  mUART_Rx_waiting--;
               }

               // Retrigger input if more bytes waiting
               if(mUART_Rx_waiting>0)
                  mUART_RX_COUNTDOWN=UART_RX_TIME_PERIOD+UART_RX_NEXT_DELAY;
               else
                  mUART_RX_COUNTDOWN=UART_RX_INACTIVE;

               // If RX_READY already set then we have an overrun
               // as previous byte hasnt been read
               if(mUART_RX_READY) mUART_Rx_overun_error=1;

               // Flag byte as being recvd
               mUART_RX_READY=1;
            } else if(!(mUART_RX_COUNTDOWN&UART_RX_INACTIVE)) {
               mUART_RX_COUNTDOWN--;
            }

            if(!mUART_TX_COUNTDOWN) {
               if(mUART_SENDBREAK) {
                  mUART_TX_DATA=UART_BREAK_CODE;
                  // Auto-Respawn new transmit
                  mUART_TX_COUNTDOWN=UART_TX_TIME_PERIOD;
                  // Loop back what we transmitted
                  ComLynxTxLoopback(mUART_TX_DATA);
               } else {
                  // Serial activity finished
                  mUART_TX_COUNTDOWN=UART_TX_INACTIVE;
               }

               // If a networking object is attached then use its callback to send the data byte.
               if(mpUART_TX_CALLBACK)
                  (*mpUART_TX_CALLBACK)(mUART_TX_DATA,mUART_TX_CALLBACK_OBJECT);

            } else if(!(mUART_TX_COUNTDOWN&UART_TX_INACTIVE)) {
               mUART_TX_COUNTDOWN--;
            }

            // Set the timer status flag
            // Timer 4 is the uart timer and doesn't generate IRQ's using this method

            // 16 Clocks = 1 bit transmission. Hold separate Rx & Tx counters

            // Reload if neccessary
            //						if(mTIM_4_ENABLE_RELOAD)
            //						{
            mTIM_4_CURRENT+=mTIM_4_BKUP+1;
            // The low reload values on TIM4 coupled with a longer
            // timer service delay can sometimes cause
            // an underun, check and fix
            if(mTIM_4_CURRENT&0x80000000) {
               mTIM_4_CURRENT=mTIM_4_BKUP;
               mTIM_4_LAST_COUNT=gSystemCycleCount;
            }
            //						}
            //						else
            //						{
            //							mTIM_4_CURRENT=0;
            //						}
            //						mTIM_4_TIMER_DONE=TRUE;
         }
         //					else
         //					{
         //						mTIM_4_BORROW_OUT=FALSE;
         //					}
         //					// Set carry in as we did a count
         //					mTIM_4_BORROW_IN=TRUE;
      }
      //				else
      //				{
      //					// Clear carry in as we didn't count
      //					mTIM_4_BORROW_IN=FALSE;
      //					// Clear carry out
      //					mTIM_4_BORROW_OUT=FALSE;
      //				}
      //
      //				// Prediction for next timer event cycle number
      //
      //				if(mTIM_4_LINKING!=7)
      //				{
      // Sometimes timeupdates can be >2x rollover in which case
      // then CURRENT may still be negative and we can use it to
      // calc the next timer value, we just want another update ASAP
      tmp=(mTIM_4_CURRENT&0x80000000)?1:((mTIM_4_CURRENT+1)<<divide);
      tmp+=gSystemCycleCount;
      if(tmp<gNextTimerEvent) {
         gNextTimerEvent=tmp;
      }
      //				}
   }

   // Emulate the UART bug where UART IRQ is level sensitive
   // in that it will continue to generate interrupts as long
   // as they are enabled and the interrupt condition is true

   // If Tx is inactive i.e ready for a byte to eat and the
   // IRQ is enabled then generate it always
   if((mUART_TX_COUNTDOWN&UART_TX_INACTIVE) && mUART_TX_IRQ_ENABLE) {
      mTimerStatusFlags|=0x10;
      gSystemIRQ=TRUE;	// Added 19/09/06 fix for IRQ issue
   }
   // Is data waiting and the interrupt enabled, if so then
   // what are we waiting for....
   if(mUART_RX_READY && mUART_RX_IRQ_ENABLE) {
      mTimerStatusFlags|=0x10;
      gSystemIRQ=TRUE;	// Added 19/09/06 fix for IRQ issue
   }

   //
   // Timer 1 of Group B
   //
   // KW bugfix 13/4/99 added (mTIM_x_ENABLE_RELOAD ||  ..)
   if(mTIM_1_ENABLE_COUNT && (mTIM_1_ENABLE_RELOAD || !mTIM_1_TIMER_DONE)) {
      if(mTIM_1_LINKING!=0x07) {
         // Ordinary clocked mode as opposed to linked mode
         // 16MHz clock downto 1us == cyclecount >> 4
         divide=(4+mTIM_1_LINKING);
         decval=(gSystemCycleCount-mTIM_1_LAST_COUNT)>>divide;

         if(decval) {
            mTIM_1_LAST_COUNT+=decval<<divide;
            mTIM_1_CURRENT-=decval;
            if(mTIM_1_CURRENT&0x80000000) {
               // Set carry out
               mTIM_1_BORROW_OUT=TRUE;

               // Set the timer status flag
               if(mTimerInterruptMask&0x02) {
                  mTimerStatusFlags|=0x02;
                  gSystemIRQ=TRUE;	// Added 19/09/06 fix for IRQ issue
               }

               // Reload if neccessary
               if(mTIM_1_ENABLE_RELOAD) {
                  mTIM_1_CURRENT+=mTIM_1_BKUP+1;
               } else {
                  mTIM_1_CURRENT=0;
               }
               mTIM_1_TIMER_DONE=TRUE;
            } else {
               mTIM_1_BORROW_OUT=FALSE;
            }
            // Set carry in as we did a count
            mTIM_1_BORROW_IN=TRUE;
         } else {
            // Clear carry in as we didn't count
            mTIM_1_BORROW_IN=FALSE;
            // Clear carry out
            mTIM_1_BORROW_OUT=FALSE;
         }
      }

      // Prediction for next timer event cycle number

      if(mTIM_1_LINKING!=7) {
         // Sometimes timeupdates can be >2x rollover in which case
         // then CURRENT may still be negative and we can use it to
         // calc the next timer value, we just want another update ASAP
         tmp=(mTIM_1_CURRENT&0x80000000)?1:((mTIM_1_CURRENT+1)<<divide);
         tmp+=gSystemCycleCount;
         if(tmp<gNextTimerEvent)
            gNextTimerEvent=tmp;
      }
   }

   //
   // Timer 3 of Group A
   //
   // KW bugfix 13/4/99 added (mTIM_x_ENABLE_RELOAD ||  ..)
   if(mTIM_3_ENABLE_COUNT && (mTIM_3_ENABLE_RELOAD || !mTIM_3_TIMER_DONE)) {
      decval=0;

      if(mTIM_3_LINKING==0x07) {
         if(mTIM_1_BORROW_OUT) decval=1;
            mTIM_3_LAST_LINK_CARRY=mTIM_1_BORROW_OUT;
      } else {
         // Ordinary clocked mode as opposed to linked mode
         // 16MHz clock downto 1us == cyclecount >> 4
         divide=(4+mTIM_3_LINKING);
         decval=(gSystemCycleCount-mTIM_3_LAST_COUNT)>>divide;
      }

      if(decval) {
         mTIM_3_LAST_COUNT+=decval<<divide;
         mTIM_3_CURRENT-=decval;
         if(mTIM_3_CURRENT&0x80000000) {
            // Set carry out
            mTIM_3_BORROW_OUT=TRUE;

            // Set the timer status flag
            if(mTimerInterruptMask&0x08) {
               mTimerStatusFlags|=0x08;
               gSystemIRQ=TRUE;	// Added 19/09/06 fix for IRQ issue
            }

            // Reload if neccessary
            if(mTIM_3_ENABLE_RELOAD) {
               mTIM_3_CURRENT+=mTIM_3_BKUP+1;
            } else {
               mTIM_3_CURRENT=0;
            }
            mTIM_3_TIMER_DONE=TRUE;
         } else {
            mTIM_3_BORROW_OUT=FALSE;
         }
         // Set carry in as we did a count
         mTIM_3_BORROW_IN=TRUE;
      } else {
         // Clear carry in as we didn't count
         mTIM_3_BORROW_IN=FALSE;
         // Clear carry out
         mTIM_3_BORROW_OUT=FALSE;
      }

      // Prediction for next timer event cycle number

      if(mTIM_3_LINKING!=7) {
         // Sometimes timeupdates can be >2x rollover in which case
         // then CURRENT may still be negative and we can use it to
         // calc the next timer value, we just want another update ASAP
         tmp=(mTIM_3_CURRENT&0x80000000)?1:((mTIM_3_CURRENT+1)<<divide);
         tmp+=gSystemCycleCount;
         if(tmp<gNextTimerEvent) {
            gNextTimerEvent=tmp;
         }
      }
   }

   //
   // Timer 5 of Group A
   //
   // KW bugfix 13/4/99 added (mTIM_x_ENABLE_RELOAD ||  ..)
   if(mTIM_5_ENABLE_COUNT && (mTIM_5_ENABLE_RELOAD || !mTIM_5_TIMER_DONE)) {
      decval=0;

      if(mTIM_5_LINKING==0x07) {
         if(mTIM_3_BORROW_OUT) decval=1;
            mTIM_5_LAST_LINK_CARRY=mTIM_3_BORROW_OUT;
      } else {
         // Ordinary clocked mode as opposed to linked mode
         // 16MHz clock downto 1us == cyclecount >> 4
         divide=(4+mTIM_5_LINKING);
         decval=(gSystemCycleCount-mTIM_5_LAST_COUNT)>>divide;
      }

      if(decval) {
         mTIM_5_LAST_COUNT+=decval<<divide;
         mTIM_5_CURRENT-=decval;
         if(mTIM_5_CURRENT&0x80000000) {
            // Set carry out
            mTIM_5_BORROW_OUT=TRUE;

            // Set the timer status flag
            if(mTimerInterruptMask&0x20) {
               mTimerStatusFlags|=0x20;
               gSystemIRQ=TRUE;	// Added 19/09/06 fix for IRQ issue
            }

            // Reload if neccessary
            if(mTIM_5_ENABLE_RELOAD) {
               mTIM_5_CURRENT+=mTIM_5_BKUP+1;
            } else {
               mTIM_5_CURRENT=0;
            }
            mTIM_5_TIMER_DONE=TRUE;
         } else {
            mTIM_5_BORROW_OUT=FALSE;
         }
         // Set carry in as we did a count
         mTIM_5_BORROW_IN=TRUE;
      } else {
         // Clear carry in as we didn't count
         mTIM_5_BORROW_IN=FALSE;
         // Clear carry out
         mTIM_5_BORROW_OUT=FALSE;
      }

      // Prediction for next timer event cycle number

      if(mTIM_5_LINKING!=7) {
         // Sometimes timeupdates can be >2x rollover in which case
         // then CURRENT may still be negative and we can use it to
         // calc the next timer value, we just want another update ASAP
         tmp=(mTIM_5_CURRENT&0x80000000)?1:((mTIM_5_CURRENT+1)<<divide);
         tmp+=gSystemCycleCount;
         if(tmp<gNextTimerEvent) {
            gNextTimerEvent=tmp;
         }
      }
   }

   //
   // Timer 7 of Group A
   //
   // KW bugfix 13/4/99 added (mTIM_x_ENABLE_RELOAD ||  ..)
   if(mTIM_7_ENABLE_COUNT && (mTIM_7_ENABLE_RELOAD || !mTIM_7_TIMER_DONE)) {
      decval=0;

      if(mTIM_7_LINKING==0x07) {
         if(mTIM_5_BORROW_OUT) decval=1;
            mTIM_7_LAST_LINK_CARRY=mTIM_5_BORROW_OUT;
      } else {
          // Ordinary clocked mode as opposed to linked mode
          // 16MHz clock downto 1us == cyclecount >> 4
          divide=(4+mTIM_7_LINKING);
          decval=(gSystemCycleCount-mTIM_7_LAST_COUNT)>>divide;
      }

      if(decval) {
         mTIM_7_LAST_COUNT+=decval<<divide;
         mTIM_7_CURRENT-=decval;
         if(mTIM_7_CURRENT&0x80000000) {
            // Set carry out
            mTIM_7_BORROW_OUT=TRUE;

            // Set the timer status flag
            if(mTimerInterruptMask&0x80) {
               mTimerStatusFlags|=0x80;
               gSystemIRQ=TRUE;	// Added 19/09/06 fix for IRQ issue
            }

            // Reload if neccessary
            if(mTIM_7_ENABLE_RELOAD) {
               mTIM_7_CURRENT+=mTIM_7_BKUP+1;
            } else {
               mTIM_7_CURRENT=0;
            }
            mTIM_7_TIMER_DONE=TRUE;

         } else {
            mTIM_7_BORROW_OUT=FALSE;
         }
         // Set carry in as we did a count
         mTIM_7_BORROW_IN=TRUE;
      } else {
         // Clear carry in as we didn't count
         mTIM_7_BORROW_IN=FALSE;
         // Clear carry out
         mTIM_7_BORROW_OUT=FALSE;
      }

      // Prediction for next timer event cycle number

      if(mTIM_7_LINKING!=7) {
         // Sometimes timeupdates can be >2x rollover in which case
         // then CURRENT may still be negative and we can use it to
         // calc the next timer value, we just want another update ASAP
         tmp=(mTIM_7_CURRENT&0x80000000)?1:((mTIM_7_CURRENT+1)<<divide);
         tmp+=gSystemCycleCount;
         if(tmp<gNextTimerEvent) {
            gNextTimerEvent=tmp;
         }
      }
   }

   //
   // Timer 6 has no group
   //
   // KW bugfix 13/4/99 added (mTIM_x_ENABLE_RELOAD ||  ..)
   if(mTIM_6_ENABLE_COUNT && (mTIM_6_ENABLE_RELOAD || !mTIM_6_TIMER_DONE)) {
      //				if(mTIM_6_LINKING!=0x07)
      {
         // Ordinary clocked mode as opposed to linked mode
         // 16MHz clock downto 1us == cyclecount >> 4
         divide=(4+mTIM_6_LINKING);
         decval=(gSystemCycleCount-mTIM_6_LAST_COUNT)>>divide;

         if(decval) {
            mTIM_6_LAST_COUNT+=decval<<divide;
            mTIM_6_CURRENT-=decval;
            if(mTIM_6_CURRENT&0x80000000) {
               // Set carry out
               mTIM_6_BORROW_OUT=TRUE;

               // Set the timer status flag
               if(mTimerInterruptMask&0x40) {
                  mTimerStatusFlags|=0x40;
                  gSystemIRQ=TRUE;	// Added 19/09/06 fix for IRQ issue
               }

               // Reload if neccessary
               if(mTIM_6_ENABLE_RELOAD) {
                  mTIM_6_CURRENT+=mTIM_6_BKUP+1;
               } else {
                  mTIM_6_CURRENT=0;
               }
               mTIM_6_TIMER_DONE=TRUE;
            } else {
               mTIM_6_BORROW_OUT=FALSE;
            }
            // Set carry in as we did a count
            mTIM_6_BORROW_IN=TRUE;
         } else {
            // Clear carry in as we didn't count
            mTIM_6_BORROW_IN=FALSE;
            // Clear carry out
            mTIM_6_BORROW_OUT=FALSE;
         }
      }

      // Prediction for next timer event cycle number
      // (Timer 6 doesn't support linking)

      //				if(mTIM_6_LINKING!=7)
      {
         // Sometimes timeupdates can be >2x rollover in which case
         // then CURRENT may still be negative and we can use it to
         // calc the next timer value, we just want another update ASAP
         tmp=(mTIM_6_CURRENT&0x80000000)?1:((mTIM_6_CURRENT+1)<<divide);
         tmp+=gSystemCycleCount;
         if(tmp<gNextTimerEvent) {
            gNextTimerEvent=tmp;
         }
      }
   }

   //
   // If sound is enabled then update the sound subsystem
   //
   if(gAudioEnabled) {
      //
      // Audio 0
      //
      //				if(mAUDIO_0_ENABLE_COUNT && !mAUDIO_0_TIMER_DONE && mAUDIO_0_VOLUME && mAUDIO_0_BKUP)
      if(mAUDIO_0_ENABLE_COUNT && (mAUDIO_0_ENABLE_RELOAD || !mAUDIO_0_TIMER_DONE)) {
         decval=0;

         if(mAUDIO_0_LINKING==0x07) {
            if(mTIM_7_BORROW_OUT) decval=1;
               mAUDIO_0_LAST_LINK_CARRY=mTIM_7_BORROW_OUT;
         } else {
            // Ordinary clocked mode as opposed to linked mode
            // 16MHz clock downto 1us == cyclecount >> 4
            divide=(4+mAUDIO_0_LINKING);
            decval=(gSystemCycleCount-mAUDIO_0_LAST_COUNT)>>divide;
         }

         if(decval) {
            mAUDIO_0_LAST_COUNT+=decval<<divide;
            mAUDIO_0_CURRENT-=decval;
            if(mAUDIO_0_CURRENT&0x80000000) {
               // Set carry out
               mAUDIO_0_BORROW_OUT=TRUE;

               // Reload if neccessary
               if(mAUDIO_0_ENABLE_RELOAD) {
                  mAUDIO_0_CURRENT+=mAUDIO_0_BKUP+1;
                  if(mAUDIO_0_CURRENT&0x80000000) mAUDIO_0_CURRENT=0;
               } else {
                  // Set timer done
                  mAUDIO_0_TIMER_DONE=TRUE;
                  mAUDIO_0_CURRENT=0;
               }

               //
               // Update audio circuitry
               //
               if(mAUDIO_0_BKUP || mAUDIO_0_LINKING)
                  mAUDIO_0_WAVESHAPER=GetLfsrNext(mAUDIO_0_WAVESHAPER);

               if(mAUDIO_0_INTEGRATE_ENABLE) {
                  int32_t temp=mAUDIO_OUTPUT[0];
                  if(mAUDIO_0_WAVESHAPER&0x0001) temp+=mAUDIO_0_VOLUME;
                  else temp-=mAUDIO_0_VOLUME;
                  if(temp>127) temp=127;
                  if(temp<-128) temp=-128;
                  mAUDIO_OUTPUT[0]=(int8_t)temp;
               } else {
                  if(mAUDIO_0_WAVESHAPER&0x0001) mAUDIO_OUTPUT[0]=mAUDIO_0_VOLUME;
                  else mAUDIO_OUTPUT[0]=-mAUDIO_0_VOLUME;
               }
            } else {
               mAUDIO_0_BORROW_OUT=FALSE;
            }
            // Set carry in as we did a count
            mAUDIO_0_BORROW_IN=TRUE;
         } else {
            // Clear carry in as we didn't count
            mAUDIO_0_BORROW_IN=FALSE;
            // Clear carry out
            mAUDIO_0_BORROW_OUT=FALSE;
         }

         // Prediction for next timer event cycle number

         if(mAUDIO_0_LINKING!=7) {
            // Sometimes timeupdates can be >2x rollover in which case
            // then CURRENT may still be negative and we can use it to
            // calc the next timer value, we just want another update ASAP
            tmp=(mAUDIO_0_CURRENT&0x80000000)?1:((mAUDIO_0_CURRENT+1)<<divide);
            tmp+=gSystemCycleCount;
            if(tmp<gNextTimerEvent) {
               gNextTimerEvent=tmp;
            }
         }
      }

      //
      // Audio 1
      //
      //				if(mAUDIO_1_ENABLE_COUNT && !mAUDIO_1_TIMER_DONE && mAUDIO_1_VOLUME && mAUDIO_1_BKUP)
      if(mAUDIO_1_ENABLE_COUNT && (mAUDIO_1_ENABLE_RELOAD || !mAUDIO_1_TIMER_DONE)) {
         decval=0;

         if(mAUDIO_1_LINKING==0x07) {
            if(mAUDIO_0_BORROW_OUT) decval=1;
            mAUDIO_1_LAST_LINK_CARRY=mAUDIO_0_BORROW_OUT;
         } else {
            // Ordinary clocked mode as opposed to linked mode
            // 16MHz clock downto 1us == cyclecount >> 4
            divide=(4+mAUDIO_1_LINKING);
            decval=(gSystemCycleCount-mAUDIO_1_LAST_COUNT)>>divide;
         }

         if(decval) {
            mAUDIO_1_LAST_COUNT+=decval<<divide;
            mAUDIO_1_CURRENT-=decval;
            if(mAUDIO_1_CURRENT&0x80000000) {
               // Set carry out
               mAUDIO_1_BORROW_OUT=TRUE;

               // Reload if neccessary
               if(mAUDIO_1_ENABLE_RELOAD) {
                  mAUDIO_1_CURRENT+=mAUDIO_1_BKUP+1;
                  if(mAUDIO_1_CURRENT&0x80000000) mAUDIO_1_CURRENT=0;
               } else {
                  // Set timer done
                  mAUDIO_1_TIMER_DONE=TRUE;
                  mAUDIO_1_CURRENT=0;
               }

               //
               // Update audio circuitry
               //
               if(mAUDIO_1_BKUP || mAUDIO_1_LINKING)
                  mAUDIO_1_WAVESHAPER=GetLfsrNext(mAUDIO_1_WAVESHAPER);

               if(mAUDIO_1_INTEGRATE_ENABLE) {
                  int32_t temp=mAUDIO_OUTPUT[1];
                  if(mAUDIO_1_WAVESHAPER&0x0001) temp+=mAUDIO_1_VOLUME;
                  else temp-=mAUDIO_1_VOLUME;
                  if(temp>127) temp=127;
                  if(temp<-128) temp=-128;
                  mAUDIO_OUTPUT[1]=(int8_t)temp;
               } else {
                  if(mAUDIO_1_WAVESHAPER&0x0001) mAUDIO_OUTPUT[1]=mAUDIO_1_VOLUME;
                  else mAUDIO_OUTPUT[1]=-mAUDIO_1_VOLUME;
               }
            } else {
               mAUDIO_1_BORROW_OUT=FALSE;
            }
            // Set carry in as we did a count
            mAUDIO_1_BORROW_IN=TRUE;
         } else {
            // Clear carry in as we didn't count
            mAUDIO_1_BORROW_IN=FALSE;
            // Clear carry out
            mAUDIO_1_BORROW_OUT=FALSE;
         }

         // Prediction for next timer event cycle number

         if(mAUDIO_1_LINKING!=7) {
            // Sometimes timeupdates can be >2x rollover in which case
            // then CURRENT may still be negative and we can use it to
            // calc the next timer value, we just want another update ASAP
            tmp=(mAUDIO_1_CURRENT&0x80000000)?1:((mAUDIO_1_CURRENT+1)<<divide);
            tmp+=gSystemCycleCount;
            if(tmp<gNextTimerEvent) {
               gNextTimerEvent=tmp;
            }
         }
      }

      //
      // Audio 2
      //
      //				if(mAUDIO_2_ENABLE_COUNT && !mAUDIO_2_TIMER_DONE && mAUDIO_2_VOLUME && mAUDIO_2_BKUP)
      if(mAUDIO_2_ENABLE_COUNT && (mAUDIO_2_ENABLE_RELOAD || !mAUDIO_2_TIMER_DONE)) {
         decval=0;

         if(mAUDIO_2_LINKING==0x07) {
            if(mAUDIO_1_BORROW_OUT) decval=1;
            mAUDIO_2_LAST_LINK_CARRY=mAUDIO_1_BORROW_OUT;
         } else {
            // Ordinary clocked mode as opposed to linked mode
            // 16MHz clock downto 1us == cyclecount >> 4
            divide=(4+mAUDIO_2_LINKING);
            decval=(gSystemCycleCount-mAUDIO_2_LAST_COUNT)>>divide;
         }

         if(decval) {
            mAUDIO_2_LAST_COUNT+=decval<<divide;
            mAUDIO_2_CURRENT-=decval;
            if(mAUDIO_2_CURRENT&0x80000000) {
               // Set carry out
               mAUDIO_2_BORROW_OUT=TRUE;

               // Reload if neccessary
               if(mAUDIO_2_ENABLE_RELOAD) {
                  mAUDIO_2_CURRENT+=mAUDIO_2_BKUP+1;
                  if(mAUDIO_2_CURRENT&0x80000000) mAUDIO_2_CURRENT=0;
               } else {
                  // Set timer done
                  mAUDIO_2_TIMER_DONE=TRUE;
                  mAUDIO_2_CURRENT=0;
               }

               //
               // Update audio circuitry
               //
               if(mAUDIO_2_BKUP || mAUDIO_2_LINKING)
                  mAUDIO_2_WAVESHAPER=GetLfsrNext(mAUDIO_2_WAVESHAPER);

               if(mAUDIO_2_INTEGRATE_ENABLE) {
                  int32_t temp=mAUDIO_OUTPUT[2];
                  if(mAUDIO_2_WAVESHAPER&0x0001) temp+=mAUDIO_2_VOLUME;
                  else temp-=mAUDIO_2_VOLUME;
                  if(temp>127) temp=127;
                  if(temp<-128) temp=-128;
                  mAUDIO_OUTPUT[2]=(int8_t)temp;
               } else {
                  if(mAUDIO_2_WAVESHAPER&0x0001) mAUDIO_OUTPUT[2]=mAUDIO_2_VOLUME;
                  else mAUDIO_OUTPUT[2]=-mAUDIO_2_VOLUME;
               }
            } else {
               mAUDIO_2_BORROW_OUT=FALSE;
            }
            // Set carry in as we did a count
            mAUDIO_2_BORROW_IN=TRUE;
         } else {
            // Clear carry in as we didn't count
            mAUDIO_2_BORROW_IN=FALSE;
            // Clear carry out
            mAUDIO_2_BORROW_OUT=FALSE;
         }

         // Prediction for next timer event cycle number

         if(mAUDIO_2_LINKING!=7) {
            // Sometimes timeupdates can be >2x rollover in which case
            // then CURRENT may still be negative and we can use it to
            // calc the next timer value, we just want another update ASAP
            tmp=(mAUDIO_2_CURRENT&0x80000000)?1:((mAUDIO_2_CURRENT+1)<<divide);
            tmp+=gSystemCycleCount;
            if(tmp<gNextTimerEvent) {
               gNextTimerEvent=tmp;
            }
         }
      }

      //
      // Audio 3
      //
      //				if(mAUDIO_3_ENABLE_COUNT && !mAUDIO_3_TIMER_DONE && mAUDIO_3_VOLUME && mAUDIO_3_BKUP)
      if(mAUDIO_3_ENABLE_COUNT && (mAUDIO_3_ENABLE_RELOAD || !mAUDIO_3_TIMER_DONE)) {
         decval=0;

         if(mAUDIO_3_LINKING==0x07) {
            if(mAUDIO_2_BORROW_OUT) decval=1;
            mAUDIO_3_LAST_LINK_CARRY=mAUDIO_2_BORROW_OUT;
         } else {
            // Ordinary clocked mode as opposed to linked mode
            // 16MHz clock downto 1us == cyclecount >> 4
            divide=(4+mAUDIO_3_LINKING);
            decval=(gSystemCycleCount-mAUDIO_3_LAST_COUNT)>>divide;
         }

         if(decval) {
            mAUDIO_3_LAST_COUNT+=decval<<divide;
            mAUDIO_3_CURRENT-=decval;
            if(mAUDIO_3_CURRENT&0x80000000) {
               // Set carry out
               mAUDIO_3_BORROW_OUT=TRUE;

               // Reload if neccessary
               if(mAUDIO_3_ENABLE_RELOAD) {
                  mAUDIO_3_CURRENT+=mAUDIO_3_BKUP+1;
                  if(mAUDIO_3_CURRENT&0x80000000) mAUDIO_3_CURRENT=0;
               } else {
                  // Set timer done
                  mAUDIO_3_TIMER_DONE=TRUE;
                  mAUDIO_3_CURRENT=0;
               }

               //
               // Update audio circuitry
               //
               if(mAUDIO_3_BKUP || mAUDIO_3_LINKING)
                  mAUDIO_3_WAVESHAPER=GetLfsrNext(mAUDIO_3_WAVESHAPER);

               if(mAUDIO_3_INTEGRATE_ENABLE) {
                  int32_t temp=mAUDIO_OUTPUT[3];
                  if(mAUDIO_3_WAVESHAPER&0x0001) temp+=mAUDIO_3_VOLUME;
                  else temp-=mAUDIO_3_VOLUME;
                  if(temp>127) temp=127;
                  if(temp<-128) temp=-128;
                  mAUDIO_OUTPUT[3]=(int8_t)temp;
               } else {
                  if(mAUDIO_3_WAVESHAPER&0x0001) mAUDIO_OUTPUT[3]=mAUDIO_3_VOLUME;
                  else mAUDIO_OUTPUT[3]=-mAUDIO_3_VOLUME;
               }
            } else {
               mAUDIO_3_BORROW_OUT=FALSE;
            }
            // Set carry in as we did a count
            mAUDIO_3_BORROW_IN=TRUE;
         } else {
            // Clear carry in as we didn't count
            mAUDIO_3_BORROW_IN=FALSE;
            // Clear carry out
            mAUDIO_3_BORROW_OUT=FALSE;
         }

         // Prediction for next timer event cycle number

         if(mAUDIO_3_LINKING!=7) {
            // Sometimes timeupdates can be >2x rollover in which case
            // then CURRENT may still be negative and we can use it to
            // calc the next timer value, we just want another update ASAP
            tmp=(mAUDIO_3_CURRENT&0x80000000)?1:((mAUDIO_3_CURRENT+1)<<divide);
            tmp+=gSystemCycleCount;
            if(tmp<gNextTimerEvent) {
               gNextTimerEvent=tmp;
            }
         }
      }

      UpdateSound();
   }

   //			if(gSystemCycleCount==gNextTimerEvent) gError->Warning("CMikie::Update() - gSystemCycleCount==gNextTimerEvent, system lock likely");

   // Update system IRQ status as a result of timer activity
   gSystemIRQ=(mTimerStatusFlags)?true:false;
   if(gSystemIRQ && gSystemCPUSleep) { ClearCPUSleep(); /*puts("ARLARM"); */ }
   //else if(gSuzieDoneTime) SetCPUSleep();

   // Now all the timer updates are done we can increment the system
   // counter for any work done within the Update() function, gSystemCycleCounter
   // cannot be updated until this point otherwise it screws up the counters.
   gSystemCycleCount+=mikie_work_done;
}

inline void CMikie::UpdateSound(void)
{
   int cur_lsample = 0;
   int cur_rsample = 0;
   int x;

   for(x = 0; x < 4; x++){
      /// Assumption (seems there is no documentation for the Attenuation registers)
      /// a) they are linear from $0 to $f - checked!
      /// b) an attenuation of $0 is equal to channel OFF (bits in mSTEREO not set) - checked!
      /// c) an attenuation of $f is NOT equal to no attenuation (bits in PAN not set), $10 would be - checked!
      /// These assumptions can only checked with an oszilloscope... - done
      /// the values stored in mSTEREO are NOT bit-inverted ...
      /// mSTEREO was found to be set like that already (why?), but unused

      if(!(mSTEREO & (0x10 << x))) {
         if(mPAN & (0x10 << x))
            cur_lsample += (mAUDIO_OUTPUT[x]*(mAUDIO_ATTEN[x]&0xF0))/(16*16); /// NOT /15*16 see remark above
         else
            cur_lsample += mAUDIO_OUTPUT[x];
      }
      if(!(mSTEREO & (0x01 << x))) {
         if(mPAN & (0x01 << x))
            cur_rsample += (mAUDIO_OUTPUT[x]*(mAUDIO_ATTEN[x]&0x0F))/16; /// NOT /15 see remark above
         else
            cur_rsample += mAUDIO_OUTPUT[x];
      }
   }

   static int last_lsample = 0;
   static int last_rsample = 0;

   if(cur_lsample != last_lsample) {
      miksynth.offset_inline((gSystemCycleCount - gAudioLastUpdateCycle) / 4, cur_lsample - last_lsample, mikbuf.left());
      last_lsample = cur_lsample;
   }

   if(cur_rsample != last_rsample) {
      miksynth.offset_inline((gSystemCycleCount - gAudioLastUpdateCycle) / 4, cur_rsample - last_rsample, mikbuf.right());
      last_rsample = cur_rsample;
   }
}
