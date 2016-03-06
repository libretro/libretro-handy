//////////////////////////////////////////////////////////////////////////////
// Lynx 3wire EEPROM class header file                                      //
//////////////////////////////////////////////////////////////////////////////


#ifndef EEPROM_H
#define EEPROM_H

enum {EE_NONE=0, EE_START, EE_DATA, EE_BUSY, EE_WAIT};

class CEEPROM : public CLynxBase
{

   // Function members

public:
   CEEPROM();
   ~CEEPROM();

   void	Reset(void);

   void ProcessEepromIO(UBYTE iodir,UBYTE iodat);
   void ProcessEepromCounter(UWORD cnt);
   void ProcessEepromBusy(void);
   bool OutputBit(void)
   {
      return mAUDIN_ext;
   };
   void SetEEPROMType(UBYTE b);

   void	Poke(ULONG addr,UBYTE data) { };
   UBYTE	Peek(ULONG addr)
   {
      return(0);
   };

private:
   void UpdateEeprom(UWORD cnt);

   UWORD ADDR_MASK;
   UBYTE CMD_BITS;
   UBYTE ADDR_BITS;
   ULONG DONE_MASK;

   UBYTE iodir, iodat;
   UWORD counter;
   int busy_count;
   int state;
   UWORD readdata;

   ULONG data;
   UWORD romdata[1024];// 128, 256, 512, 1024 WORDS bzw 128 bytes fuer byte zugriff
   UWORD addr;
   int sendbits;
   bool readonly;

   bool mAUDIN_ext;// OUTPUT

public:
};

#endif
