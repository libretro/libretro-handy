/*
CRC32 hash

Software title
File size

Bank0 size:
C64K   = 0x100
C128K  = 0x200
C256K  = 0x400
C512K  = 0x800
C1024K = 0x1000

Bank1 size

Rotation
Audin
Eeprom
*/


static LYNX_DB lynxDB[] = {

   { 0x9d09bc4c, "8-Bit Slicks (World) (Aftermarket) (Unl)", 524288, C512K, 0, 0, 0, CART_EEPROM_93C46 },
   { 0x95a1ea09, "Alpine Games (World) (Aftermarket) (Unl)", 524288, C256K, 0, 0, CART_AUDIN, CART_EEPROM_93C46 },
   { 0x427d0e97, "A Bug's Trip Redux (World) (Aftermarket) (Unl)", 524288, C512K, 0, 0, 0, CART_EEPROM_93C46 },
   { 0x97501709, "Centipede (USA) (Proto)", 131072, C128K, 0, CART_ROTATE_RIGHT, 0, 0 },
   { 0x6bceaa9c, "Eye of the Beholder (USA) (Proto)", 131072, C128K, 0, 0, 0, 0 },   //16K NVRAM
   { 0xae8c70f0, "Eye of the Beholder (USA) (Proto)", 524288, C512K, 0, 0, 0, 0 },   //16K NVRAM
   { 0xf1b307cb, "Eye of the Beholder (USA)", 524352, C512K, 0, 0, 0, 0 },   //16K NVRAM
   { 0xdcd723e3, "Gauntlet - The Third Encounter (USA, Europe) (Beta) (1990-06-04)", 131072, C128K, 0, CART_ROTATE_LEFT, 0, 0 },
   { 0x7f0ec7ad, "Gauntlet - The Third Encounter (USA, Europe)", 131072, C128K, 0, CART_ROTATE_LEFT, 0, 0 },
   { 0x4d5d94f4, "Klax (USA, Europe) (Beta)", 262144, C256K, 0, CART_ROTATE_LEFT, 0, 0 },
   { 0xa53649f1, "Klax (USA, Europe)", 262144, C256K, 0, CART_ROTATE_LEFT, 0, 0 },
   { 0x0271b6e9, "Lexis (USA)", 262144, C256K, 0, CART_ROTATE_RIGHT, 0, 0 },
   { 0xca7cf30b, "MegaPak 1 (World) (Aftermarket) (Unl)", 262144, C256K, 0, 0, 0, CART_EEPROM_93C46 },
   { 0x006fd398, "NFL Football (USA, Europe)", 262144, C256K, 0, CART_ROTATE_RIGHT, 0, 0 },
   { 0xbb27e6f0, "Ponx (World) (Aftermarket) (Unl)", 131072, C256K, 0, 0, 0, 0 },
   { 0xbcd10c3a, "Raiden (USA) (Proto)", 262144, C256K, 0, CART_ROTATE_RIGHT, 0, 0 },
   { 0x689f31a4, "Raiden (World) (Aftermarket) (Unl)", 524288, C512K, 0, CART_ROTATE_RIGHT, 0, 0 },
   { 0xb8879506, "Sky Raider Redux (World) (Aftermarket) (Unl)", 524288, C512K, 0, 0, 0, CART_EEPROM_93C46 },
   { 0xb2fa93d3, "Unnamed (World) (Aftermarket) (Unl)", 524288, C512K, 0, 0, 0, CART_EEPROM_93C46 },
   { 0x50b0575a, "Vikings Saga - Protect The Love (World) (Aftermarket) (Unl)", 524288, C512K, 0, 0, 0, CART_EEPROM_93C46 },
   { 0x18b006a9, "Vikings Saga - Save The Love (World) (Aftermarket) (Unl)", 524288, C512K, 0, 0, 0, CART_EEPROM_93C46 },
   { 0x7f8b5efa, "Wyvern Tales (World) (Aftermarket) (Unl)", 524288, C512K, 0, 0, 0, CART_EEPROM_93C46 },

   // auto-detect
   { 0, NULL, 0, 0, 0, 0, 0, 0 },
};
