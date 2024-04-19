
#include "stm32h7xxfmc.h"
HAL_StatusTypeDef HAL_InitTick(uint32_t TickPriority)
{
	return HAL_OK;
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
	
  if (result == 1)
    return result;
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
