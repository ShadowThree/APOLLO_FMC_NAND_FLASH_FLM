/***********************************************************************/
/*  This file is part of the ARM Toolchain package                     */
/*  Copyright (c) 2011 Keil - An ARM Company. All rights reserved.     */
/***********************************************************************/
/*                                                                     */
/*  FlashPrg.c:  Flash Programming Functions adapted for               */
/*               ST Microelectronics STM32F4xx Flash                   */
/*                                                                     */
/***********************************************************************/

#include "..\FlashOS.H"        // FlashOS Structures
#include "STM32H7FMC.h"
#include "stm32h7xxfmc.h"

#define DEV_ADDR	(0x80000000)
#define PAGE_SIZE		(2048)
#define BLOCK_SIZE	(PAGE_SIZE * 64)

/*
 *  Initialize Flash Programming Functions
 *    Parameter:      adr:  Device Base Address
 *                    clk:  Clock Frequency (Hz)
 *                    fnc:  Function Code (1 - Erase, 2 - Program, 3 - Verify)
 *    Return Value:   0 - OK,  1 - Failed
 */

#if defined FLASH_MEM || defined FLASH_OTP
int Init (unsigned long adr, unsigned long clk, unsigned long fnc) {

  return (Init_fmc());
}
#endif


/*
 *  De-Initialize Flash Programming Functions
 *    Parameter:      fnc:  Function Code (1 - Erase, 2 - Program, 3 - Verify)
 *    Return Value:   0 - OK,  1 - Failed
 */

#if defined FLASH_MEM || defined FLASH_OTP
int UnInit (unsigned long fnc) {


  return (0);
}
#endif


/*
 *  Erase complete Flash Memory
 *    Return Value:   0 - OK,  1 - Failed
 */

#ifdef FLASH_MEM
int EraseChip (void) {
	
	return 0;
  //return (chip_Erase());                                           // Done
}
#endif


/*
 *  Erase Sector in Flash Memory
 *    Parameter:      adr:  Sector Address
 *    Return Value:   0 - OK,  1 - Failed
 */

#ifdef FLASH_MEM
int EraseSector (unsigned long adr)
{
	if(adr != DEV_ADDR) {
		return 1;
	}
	
	adr -= DEV_ADDR;
	//NAND_AddressTypeDef nand_addr = {.Page = 0, .Block = adr / BLOCK_SIZE, .Plane = 0};
	NAND_AddressTypeDef nand_addr = {.Page = 0, .Block = 0, .Plane = 0};
	if(HAL_OK != HAL_NAND_Erase_Block(&hnand1, &nand_addr)) {
		return 1;
	}
	return 0;
  //return (SectorErase_fmc ( adr , adr + 0x2000));                                           // Done
}
#endif


/*
 *  Program Page in Flash Memory
 *    Parameter:      adr:  Page Start Address
 *                    sz:   Page Size
 *                    buf:  Page Data
 *    Return Value:   0 - OK,  1 - Failed
 */

#if defined FLASH_MEM || defined FLASH_OTP
int ProgramPage (unsigned long adr, unsigned long sz, unsigned char *buf)
{
	if(adr != DEV_ADDR) {
		return 1;
	}
	
	adr -= DEV_ADDR;
	//NAND_AddressTypeDef nand_addr = {.Page = adr % BLOCK_SIZE / PAGE_SIZE, .Block = adr / BLOCK_SIZE, .Plane = 0};
	NAND_AddressTypeDef nand_addr = {.Page = 0, .Block = 0, .Plane = 0};
	if(HAL_OK != HAL_NAND_Write_Page_8b(&hnand1, &nand_addr, buf, 1)) {
		return 1;
	}
	return 0;
  //return (Write_fmc ( adr,  sz, (unsigned short *) buf));                                           // Done
}



unsigned long Verify (unsigned long adr, unsigned long sz, unsigned char *buf){
	
	int result = 0;
	
	result = Init_fmc();
	if (result !=0)
		return 1;
	
	return adr + sz;
	
//	while (sz-->0)
//	{
//		if ( *(char*)adr++ != *((char*)buf++))
//			return (adr);//  *(u32*)0x90000504;//(adr);//  
//	}
		
  return adr;
}
#endif
