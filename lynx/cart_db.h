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

   // no-intro 2023-03-22
   { 0x97501709, "Centipede (USA) (Proto)", 131072, C128K, 0, CART_ROTATE_RIGHT, 0, 0 },
   { 0x6bceaa9c, "Eye of the Beholder (USA) (Proto)", 131072, C128K, 0, 0, 0, 0 },   //16K NVRAM
   { 0xf1b307cb, "Eye of the Beholder (USA)", 524352, C512K, 0, 0, 0, 0 },   //16K NVRAM
   { 0xdcd723e3, "Gauntlet - The Third Encounter (USA, Europe) (Beta) (1990-06-04)", 131072, C128K, 0, CART_ROTATE_LEFT, 0, 0 },
   { 0x7f0ec7ad, "Gauntlet - The Third Encounter (USA, Europe)", 131072, C128K, 0, CART_ROTATE_LEFT, 0, 0 },
   { 0x4d5d94f4, "Klax (USA, Europe) (Beta)", 262144, C256K, 0, CART_ROTATE_LEFT, 0, 0 },
   { 0xa53649f1, "Klax (USA, Europe)", 262144, C256K, 0, CART_ROTATE_LEFT, 0, 0 },
   { 0x0271b6e9, "Lexis (USA)", 262144, C256K, 0, CART_ROTATE_RIGHT, 0, 0 },
   { 0x006fd398, "NFL Football (USA, Europe)", 262144, C256K, 0, CART_ROTATE_RIGHT, 0, 0 },
   { 0xbcd10c3a, "Raiden (USA) (Proto)", 262144, C256K, 0, CART_ROTATE_RIGHT, 0, 0 },


   // no-intro private 2023-07-21
   { 0xbb27e6f0, "PONX (World) (Aftermarket) (Unl)", 131072, C256K, 0, 0, 0, 0 },
   { 0x7f8b5efa, "Wyvern Tales (World) (Aftermarket) (Unl)", 524288, C512K, 0, 0, 0, CART_EEPROM_93C46 },


   // commercial, non-datted
   { 0x9d09bc4c, "8-Bit Slicks (World) (Aftermarket) (Unl)", 524288, C512K, 0, 0, 0, CART_EEPROM_93C46 },
   { 0x95a1ea09, "Alpine Games (World) (Aftermarket) (Unl)", 524288, C256K, 0, 0, CART_AUDIN, CART_EEPROM_93C46 },
   { 0x427d0e97, "A Bug's Trip Redux (World) (Aftermarket) (Unl)", 524288, C512K, 0, 0, 0, CART_EEPROM_93C46 },
   { 0xae8c70f0, "Eye of the Beholder (USA) (Proto)", 524288, C512K, 0, 0, 0, 0 },   //16K NVRAM
   { 0xb2fa93d3, "Unnamed (World) (Aftermarket) (Unl)", 524288, C512K, 0, 0, 0, CART_EEPROM_93C46 },
   { 0xca7cf30b, "MegaPak 1 (World) (Aftermarket) (Unl)", 262144, C256K, 0, 0, 0, CART_EEPROM_93C46 },
   { 0x689f31a4, "Raiden (World) (Aftermarket) (Unl)", 524288, C512K, 0, CART_ROTATE_RIGHT, 0, 0 },
   { 0xb8879506, "Sky Raider Redux (World) (Aftermarket) (Unl)", 524288, C512K, 0, 0, 0, CART_EEPROM_93C46 },
   { 0x50b0575a, "Vikings Saga - Protect The Love (World) (Aftermarket) (Unl)", 524288, C512K, 0, 0, 0, CART_EEPROM_93C46 },
   { 0x18b006a9, "Vikings Saga - Save The Love (World) (Aftermarket) (Unl)", 524288, C512K, 0, 0, 0, CART_EEPROM_93C46 },


   // homebrew, other


   // auto-detect

#if 0
   // no-intro 2023-03-22
   { 0x540e9bb7, "Alien vs Predator (USA) (Proto) (1993-12-17)", 262144, C256K, 0, 0, 0, 0 },
   { 0xf6fb48fb, "A.P.B. (USA, Europe)", 262144, C256K, 0, 0, 0, 0 },
   { 0x0483cd2a, "Awesome Golf (USA, Europe)", 262144, C256K, 0, 0, 0, 0 },
   { 0x3943c116, "Baseball Heroes (USA, Europe)", 262144, C256K, 0, 0, 0, 0 },
   { 0x4161bb4a, "Basketbrawl (USA, Europe)", 131072, C128K, 0, 0, 0, 0 },
   { 0x277f82c2, "Batman Returns (USA, Europe)", 262144, C256K, 0, 0, 0, 0 },
   { 0x779faece, "Battle Wheels (USA, Europe)", 131072, C128K, 0, 0, 0, 0 },
   { 0x30fee726, "Battlezone 2000 (USA, Europe)", 262144, C256K, 0, 0, 0, 0 },
   { 0x143a313e, "Bill & Ted's Excellent Adventure (USA, Europe)", 262144, C256K, 0, 0, 0, 0 },
   { 0x3cd75df3, "Block Out (USA, Europe)", 131072, C128K, 0, 0, 0, 0 },
   { 0xdaf587b1, "Blue Lightning (USA, Europe)", 131072, C128K, 0, 0, 0, 0 },
   { 0xbfe36525, "Blue Lightning (USA, Europe) (Demo)", 131072, C128K, 0, 0, 0, 0 },
   { 0x333daece, "Bubble Trouble (USA, Europe)", 262144, C256K, 0, 0, 0, 0 },
   { 0xa08f0b59, "California Games (USA, Europe)", 131072, C128K, 0, 0, 0, 0 },
   { 0x19c5a7a5, "Checkered Flag (USA, Europe)", 262144, C256K, 0, 0, 0, 0 },
   { 0x6a5f53ed, "Chip's Challenge (USA, Europe)", 131072, C128K, 0, 0, 0, 0 },
   { 0xaec474c8, "Crystal Mines II (USA, Europe)", 131072, C128K, 0, 0, 0, 0 },
   { 0x99729395, "Daemonsgate (USA) (Proto)", 262144, C256K, 0, 0, 0, 0 },
   { 0xb9ac1fe5, "Desert Strike - Return to the Gulf (USA, Europe)", 262144, C256K, 0, 0, 0, 0 },
   { 0x50386cfa, "Dinolympics (USA, Europe)", 262144, C256K, 0, 0, 0, 0 },
   { 0xd565fbb7, "Dirty Larry - Renegade Cop (USA, Europe)", 262144, C256K, 0, 0, 0, 0 },
   { 0xfbfc0f05, "Double Dragon (USA, Europe)", 262144, C256K, 0, 0, 0, 0 },
   { 0x33bb74c7, "Dracula the Undead (USA, Europe)", 262144, C256K, 0, 0, 0, 0 },
   { 0xbd97116b, "Electrocop (USA, Europe)", 131072, C128K, 0, 0, 0, 0 },
   { 0xf83397f9, "European Soccer Challenge (USA, Europe)", 131072, C128K, 0, 0, 0, 0 },
   { 0x9034ee27, "Fat Bobby (USA, Europe)", 262144, C256K, 0, 0, 0, 0 },
   { 0x7e4b5945, "Fidelity Ultimate Chess Challenge, The (USA, Europe)", 131072, C128K, 0, 0, 0, 0 },
   { 0x494cc568, "Gates of Zendocon (USA, Europe)", 131072, C128K, 0, 0, 0, 0 },
   { 0xd20a85fc, "Gordo 106 (USA, Europe)", 262144, C256K, 0, 0, 0, 0 },
   { 0x6df63834, "Hard Drivin' (USA, Europe)", 131072, C128K, 0, 0, 0, 0 },
   { 0xe8b45707, "Hockey (USA, Europe)", 262144, C256K, 0, 0, 0, 0 },
   { 0xe3041c6c, "Hydra (USA, Europe)", 262144, C256K, 0, 0, 0, 0 },
   { 0x5cf8bbf0, "Ishido - The Way of Stones (USA, Europe)", 131072, C128K, 0, 0, 0, 0 },
   { 0x2455b6cf, "Jimmy Connors' Tennis (USA, Europe)", 524288, C512K, 0, 0, 0, 0 },
   { 0x5dba792a, "Joust (USA, Europe)", 131072, C128K, 0, 0, 0, 0 },
   { 0xbed5ba2b, "Krazy Ace - Miniature Golf (USA, Europe)", 262144, C256K, 0, 0, 0, 0 },
   { 0xcd1bd405, "Kung Food (USA, Europe)", 262144, C256K, 0, 0, 0, 0 },
   { 0x39b9b8cc, "Lemmings (USA, Europe)", 262144, C256K, 0, 0, 0, 0 },
   { 0x8b4d5ed6, "Lode Runner (USA) (Proto 1)", 262144, C256K, 0, 0, 0, 0 },
   { 0xae5ac8a9, "Lode Runner (USA) (Proto 2)", 262144, C256K, 0, 0, 0, 0 },
   { 0xb1c25ef1, "Loopz (USA) (Proto)", 262144, C256K, 0, 0, 0, 0 },
   { 0x1091a268, "Lynx Casino (USA, Europe)", 262144, C256K, 0, 0, 0, 0 },
   { 0x28ada019, "Lynx II Production Test Program (USA)", 262144, C256K, 0, 0, 0, 0 },
   { 0x4329084a, "Malibu Bikini Volleyball (USA, Europe) (Beta) (1993-05-11)", 262144, C256K, 0, 0, 0, 0 },
   { 0xaba6da3d, "Malibu Bikini Volleyball (USA, Europe)", 262144, C256K, 0, 0, 0, 0 },
   { 0xc3fa0d4d, "Marlboro Go! (Europe) (Proto)", 262144, C256K, 0, 0, 0, 0 },
   { 0x7de3783a, "Ms. Pac-Man (USA, Europe)", 131072, C128K, 0, 0, 0, 0 },
   { 0xf3e3f811, "Ninja Gaiden III - The Ancient Ship of Doom (USA, Europe)", 524288, C512K, 0, 0, 0 },
   { 0x22d47d51, "Ninja Gaiden (USA, Europe)", 262144, C256K, 0, 0, 0, 0 },
   { 0xaa50dd22, "Pac-Land (USA, Europe)", 131072, C128K, 0, 0, 0, 0 },
   { 0x4cdfbd57, "Paperboy (USA, Europe)", 131072, C128K, 0, 0, 0, 0 },
   { 0x14d38ca7, "Pinball Jam (USA, Europe)", 262144, C256K, 0, 0, 0, 0 },
   { 0xe7a5a4d0, "Pit-Fighter (USA, Europe) (Beta) (1992-10-13)", 524288, C512K, 0, 0, 0, 0 },
   { 0x2393135f, "Pit-Fighter (USA, Europe)", 524288, C512K, 0, 0, 0, 0 },
   { 0x99c42034, "Power Factor (USA, Europe)", 262144, C256K, 0, 0, 0, 0 },
   { 0xb9881423, "QIX (USA, Europe)", 131072, C128K, 0, 0, 0, 0 },
   { 0xb10b7c8e, "Rampage (USA, Europe)", 262144, C256K, 0, 0, 0, 0 },
   { 0x139f301d, "Rampart (USA, Europe)", 262144, C256K, 0, 0, 0, 0 },
   { 0xeccea0d5, "Road Riot 4WD (USA) (Proto 1)", 262144, C256K, 0, 0, 0, 0 },
   { 0x82555eeb, "Road Riot 4WD (USA) (Proto 2)", 262144, C256K, 0, 0, 0, 0 },
   { 0x69959a3b, "Road Riot 4WD (USA) (Proto 3)", 262144, C256K, 0, 0, 0, 0 },
   { 0x6867e80c, "RoadBlasters (USA, Europe)", 262144, C256K, 0, 0, 0, 0 },
   { 0xd1dff2b2, "Robo-Squash (USA, Europe)", 131072, C128K, 0, 0, 0, 0 },
   { 0x7a6049b5, "Robotron 2084 (USA, Europe)", 131072, C128K, 0, 0, 0, 0 },
   { 0x67e5bdba, "Rygar (USA, Europe)", 262144, C256K, 0, 0, 0, 0 },
   { 0xbe166f3b, "Scrapyard Dog (USA, Europe)", 262144, C256K, 0, 0, 0, 0 },
   { 0xeb78baa3, "Shadow of the Beast (USA, Europe)", 262144, C256K, 0, 0, 0, 0 },
   { 0x192bcd04, "Shanghai (USA, Europe)", 131072, C128K, 0, 0, 0, 0 },
   { 0x5b2308ed, "Steel Talons (USA, Europe)", 262144, C256K, 0, 0, 0, 0 },
   { 0x8595c40b, "S.T.U.N. Runner (USA, Europe)", 262144, C256K, 0, 0, 0, 0 },
   { 0x2da7e2a8, "Super Asteroids, Missile Command (USA, Europe)", 131072, C128K, 0, 0, 0, 0 },
   { 0x690caeb0, "Super Off-Road (USA, Europe)", 262144, C256K, 0, 0, 0, 0 },
   { 0xdfa61571, "Super Skweek (USA, Europe)", 262144, C256K, 0, 0, 0, 0 },
   { 0x13657705, "Switchblade II (USA, Europe)", 262144, C256K, 0, 0, 0, 0 },
   { 0xae267e29, "Todd's Adventures in Slime World (USA, Europe)", 131072, C128K, 0, 0, 0, 0 },
   { 0x156a4a4c, "Toki (USA, Europe)", 262144, C256K, 0, 0, 0, 0 },
   { 0x0590a9e3, "Tournament Cyberball (USA, Europe)", 262144, C256K, 0, 0, 0, 0 },
   { 0xa4b924d6, "Turbo Sub (USA, Europe)", 131072, C128K, 0, 0, 0, 0 },
   { 0x8d56828b, "Viking Child (USA, Europe)", 262144, C256K, 0, 0, 0, 0 },
   { 0xb946ba49, "Warbirds (USA, Europe)", 131072, C128K, 0, 0, 0, 0 },
   { 0x91233794, "World Class Soccer (USA, Europe)", 262144, C256K, 0, 0, 0, 0 },
   { 0x9bed736d, "Xenophobe (USA, Europe)", 131072, C128K, 0, 0, 0, 0 },
   { 0x89e2a595, "Xybots (USA, Europe)", 262144, C256K, 0, 0, 0, 0 },
   { 0xb3747c71, "Zaku (USA) (Beta) (Unl)", 262144, C256K, 0, 0, 0, 0 },
   { 0x4ea845da, "Zaku (USA) (Unl)", 524288, C512K, 0, 0, 0, 0 },
   { 0xcb27199d, "Zarlor Mercenary (USA, Europe)", 131072, C128K, 0, 0, 0, 0 },


   // commercial, non-datted
   { 0xf8158766, "Cabal (USA) (Proto)", 262144, C256K, 0, 0, 0, 0 },
   { 0xede3a0fc, "Championship Rally (World) (Aftermarket) (Unl)", 524288, C512K, 0, 0, 0, 0 },
   { 0x122ec861, "Crystal Mines II - Buried Treasure (USA)", 262144, C256K, 0, 0, 0, 0 },
   { 0xef529ed4, "Daemonsgate (USA) (Proto)", 262144, C256K, 0, 0, 0, 0 },
   { 0xef529ed4, "Full Court Press (USA) (Proto)", 262144, C256K, 0, 0, 0, 0 },
   { 0xbd4bf2b0, "Geoduel (USA) (Proto)", 262144, C256K, 0, 0, 0, 0 },
   { 0x8f0e72c6, "Guardians Storm Over Doria (USA) (Proto)", 262144, C256K, 0, 0, 0, 0 },
   { 0x0e335aa8, "Guardians Storm Over Doria (USA) (Proto)", 262144, C256K, 0, 0, 0, 0 },
   { 0xd2b07d4d, "Loopz (USA) (Proto) (1992-09-16)", 262144, C256K, 0, 0, 0, 0 },
   { 0xd659adf8, "Lynx Othello (USA)", 524288, C512K, 0, 0, 0, 0 },
   { 0xb17a36ad, "Marlboro Go! (Germany) (Proto)", 262144, C256K, 0, 0, 0, 0 },
   { 0xf428008d, "Ninja Nerd (USA) (Proto)", 262144, C256K, 0, 0, 0, 0 },
   { 0xc45bcd62, "Poker (France) (Proto)", 131072, C128K, 0, 0, 0, 0 },
   { 0x5d1abfe7, "Pounce (USA) (Proto)", 262144, C256K, 0, 0, 0, 0 },
   { 0xbfecefc3, "Road Riot 4WD (USA) (Proto)", 262144, C256K, 0, 0, 0, 0 },
   { 0x467f8fd9, "Rolling Thunder (USA) (Proto)", 262144, C256K, 0, 0, 0, 0 },
   { 0x59510cb3, "Spacewar (USA) (Proto)", 131072, C128K, 0, 0, 0, 0 },
   { 0x6e084b3a, "Vindicators (Proto)", 131072, C128K, 0, 0, 0, 0 },
   { 0xa0c59271, "Weltenschlächter (World) (Aftermarket) (Unl)", 524288, C512K, 0, 0, 0, 0 },
   { 0xc5ebd679, "Wolfman (USA) (Proto)", 262144, C256K, 0, 0, 0, 0 },


   // cartridge, non-datted
   { 0xb02821fa, "Conquest of Zow (Proto)", 262144, C256K, 0, 0, 0, 0 },
   { 0x5598a4c9, "Dragnet (Demo)", 262144, C256K, 0, 0, 0, 0 },
   { 0xff9e0126, "Friendly (Proto)", 131072, C128K, 0, 0, 0, 0 },
   { 0x74ec2b2b, "RAM Cart (Proto)", 131072, C128K, 0, 0, 0, 0 },
   { 0xa6fe24af, "Yastuna Vol.1 - The Alchemy of Cubes (World) (Aftermarket) (Unl)", 262144, C256K, 0, 0, 0, 0 },
   { 0x6b09d810, "Yastuna Vol.2 - The Space Incident (World) (Aftermarket) (Unl)", 262144, C256K, 0, 0, 0, 0 },


   // homebrew, other
#endif

   { 0, NULL, 0, 0, 0, 0, 0, 0 },
};
