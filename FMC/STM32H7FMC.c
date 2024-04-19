
#include "stm32h7xxfmc.h"
HAL_StatusTypeDef HAL_InitTick(uint32_t TickPriority)
{
	return HAL_OK;
}

uint32_t HAL_GetTick (void) { 
  static uint32_t ticks = 0U; 
         uint32_t i; 
 
  /* If Kernel is not running wait approximately 1 ms then increment  
     and return auxiliary tick counter value */ 
  for (i = (SystemCoreClock >> 14U); i > 0U; i--) { 
    __NOP(); __NOP(); __NOP(); __NOP(); __NOP(); __NOP(); 
    __NOP(); __NOP(); __NOP(); __NOP(); __NOP(); __NOP(); 
  } 
  return ++ticks; 
}

void HAL_Delay(uint32_t Delay) 
{ 
  uint32_t tickstart = HAL_GetTick(); 
  uint32_t wait = Delay; 
 
  /* Add a period to guaranty minimum wait */ 
  if (wait < HAL_MAX_DELAY) 
  { 
    wait += (uint32_t)(1U); 
  } 
 
  while((HAL_GetTick() - tickstart) < wait) 
  { 
    __NOP(); 
  } 
}


void MX_GPIO_Init(void)
{

  //GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOH_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();
  __HAL_RCC_GPIOE_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOG_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
//  HAL_GPIO_WritePin(LED0_GPIO_Port, LED0_Pin, GPIO_PIN_SET);

//  /*Configure GPIO pin : PtPin */
//  GPIO_InitStruct.Pin = LED0_Pin;
//  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
//  GPIO_InitStruct.Pull = GPIO_PULLUP;
//  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
//  HAL_GPIO_Init(LED0_GPIO_Port, &GPIO_InitStruct);

}

int Init_fmc (void)
{
  int result = 0;
  SystemInit(); 
  //HAL_Init();
  result = SystemClock_Config();
  if (result == 1)
    return result;
	
	MX_GPIO_Init();
  //result = NOR_Init();
	result = NAND_Init();
  if (result) {
    return 1;
	}
	
	result = HAL_NAND_Reset(&hnand1);
	if (result) {
    return 1;
	}
	
//	NAND_IDTypeDef nand_id = {0};
//	result = HAL_NAND_Read_ID(&hnand1, &nand_id);
//	if(result) {
//		return 1;
//	}
	
	// read ID (0xADF1001D for H27U1G8F2BTR)    // 0xADDC9095 for H27U4G8F2ETR
//	if(((nand_id.Maker_Id != 0xAD) || (nand_id.Device_Id != 0xF1) || (nand_id.Third_Id != 0x00) || (nand_id.Fourth_Id != 0x1D)) &&
//		 ((nand_id.Maker_Id != 0xAD) || (nand_id.Device_Id != 0xDC) || (nand_id.Third_Id != 0x90) || (nand_id.Fourth_Id != 0x95))) {
//			 return 1;
//		 }
		 
  return 0;  
}

#if 0
int SectorErase_fmc (uint32_t EraseStartAddress ,uint32_t EraseEndAddress)
{ 
int result = 0;
  result =Sector_Erase ( EraseStartAddress , EraseEndAddress);
  return result;
	
}

int Write_fmc (uint32_t Address, uint32_t Size, uint16_t* Buffer)
{ 
  int result = 0;
  result =Write_FMC ( Address,  Size, Buffer);
  return result;

}
#endif
