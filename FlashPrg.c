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

#define PAGE_SIZE		(2048)
#define BLOCK_SIZE	(PAGE_SIZE * 64)

int Init(unsigned long adr, unsigned long clk, unsigned long fnc)
{
  return (Init_fmc());
}

int UnInit(unsigned long fnc)
{
	HAL_NAND_DeInit(&hnand1);
  return (0);
}

int EraseSector(unsigned long adr)
{
	adr -= DEV_ADDR;
	NAND_AddressTypeDef nand_addr = {.Page = 0, .Block = adr / BLOCK_SIZE, .Plane = 0};
	if(HAL_OK != HAL_NAND_Erase_Block(&hnand1, &nand_addr)) {
		return 1;
	}
	return 0;
}

int ProgramPage(unsigned long adr, unsigned long sz, unsigned char *buf)
{
	adr -= DEV_ADDR;
	NAND_AddressTypeDef nand_addr = {.Page = adr % BLOCK_SIZE / PAGE_SIZE, .Block = adr / BLOCK_SIZE, .Plane = 0};
	if(HAL_OK != HAL_NAND_Write_Page_8b(&hnand1, &nand_addr, buf, 1)) {
		return 1;
	}
	
//	uint8_t read_buf[PAGE_SIZE] = {0};
//	if(HAL_OK != HAL_NAND_Read_Page_8b(&hnand1, &nand_addr, read_buf, 1)) {
//		return 1;
//	}
//	for(uint16_t i = 0; i < PAGE_SIZE; i++) {
//		if(buf[i] != read_buf[i]) {
//			return 1;
//		}
//	}
	
	return 0;
}

unsigned long Verify(unsigned long adr, unsigned long sz, unsigned char *buf)
{
	uint8_t read_buf[PAGE_SIZE] = {0};
	
//	HAL_NAND_DeInit(&hnand1);
//	if(Init_fmc()) {
//		while(1);
//	}
//	HAL_NAND_Reset(&hnand1);
	
	adr -= DEV_ADDR;
	NAND_AddressTypeDef nand_addr = {.Page = adr % BLOCK_SIZE / PAGE_SIZE, .Block = adr / BLOCK_SIZE, .Plane = 0};
	if(HAL_OK != HAL_NAND_Read_Page_8b(&hnand1, &nand_addr, read_buf, 1)) {
		return 0;
	}
	
//	read_buf[0] = 0x00;
//	read_buf[1] = 0x01;
	
	for(uint16_t i = 0; i < PAGE_SIZE; i++) {
		if(read_buf[i] != buf[i]) {
			return (adr + i + DEV_ADDR);
		}
	}
	return (adr + sz + DEV_ADDR);
}

/**
	@Parameters
		adr	Block start address
		sz	Block size in bytes
		pat	Pattern to compare
	@Returns
		status information:
			0 when the block content is equal to the pattern pat.
			1 when the block content differs from the pattern pat.
	
	@brief
		The function BlankCheck can be used to check whether the specified block is empty, or whether the content is equal to a specific pattern defined in the argument pat.
		The argument adr specifies the start address of the block that is to be verified.
		The argument sz specifies the size of the block that is to be verified.
 */
int BlankCheck(unsigned long adr, unsigned long sz, unsigned char pat)
{
	uint8_t read_buf[PAGE_SIZE] = {0};
	adr -= DEV_ADDR;
	NAND_AddressTypeDef nand_addr = {.Page = 0, .Block = adr / BLOCK_SIZE, .Plane = 0};
	for(uint16_t i = 0; i < BLOCK_SIZE / PAGE_SIZE; i++) {
		nand_addr.Page = i;
		if(HAL_OK != HAL_NAND_Read_Page_8b(&hnand1, &nand_addr, read_buf, 1)) {
			return 1;
		}
		for(uint16_t j = 0; j < PAGE_SIZE; j++) {
			if(read_buf[j] != pat) {
				return 1;
			}
		}
	}
	return 0;
}
