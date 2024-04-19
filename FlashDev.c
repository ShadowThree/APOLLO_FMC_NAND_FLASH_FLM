/***********************************************************************/
/*  This file is part of the ARM Toolchain package                     */
/*  Copyright (c) 2011 Keil - An ARM Company. All rights reserved.     */
/***********************************************************************/
/*                                                                     */
/*  FlashDev.c:  Device Description for ST STM32F4xx Flash             */
/*                                                                     */
/***********************************************************************/

#include "..\FlashOS.H"        // FlashOS Structures

#ifdef FLASH_MEM
struct FlashDevice const FlashDevice  =  {
   FLASH_DRV_VERS,             // Driver Version, do not modify!
   "APOLLO_NAND_FLASH",          // Device Name 
   EXT8BIT,                     // Device Type
   DEV_ADDR,                 // Device Start Address
   0x20000000,                 // Device Size in Bytes (512MB)
   2048,                       // Programming Page Size
   0x00,                          // Reserved, must be 0
   0xFF,                       // Initial Content of Erased Memory
   10000,                        // Program Page Timeout 100 mSec
   6000,                       // Erase Sector Timeout 6000 mSec

// Specify Size and Address of Sectors
   0x20000, 0x000000,          // Sector Size  128kB (4096 Sectors)
   SECTOR_END
};
#endif // FLASH_MEM
