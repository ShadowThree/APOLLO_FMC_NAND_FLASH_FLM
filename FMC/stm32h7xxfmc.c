#include "stm32h7xxfmc.h"
#include <string.h>

NAND_HandleTypeDef hnand1;
FMC_NAND_PCC_TimingTypeDef ComSpaceTiming;
FMC_NAND_PCC_TimingTypeDef AttSpaceTiming;
int NAND_Init(void)
{
	memset(&hnand1, 0, sizeof(hnand1));
	memset(&ComSpaceTiming, 0, sizeof(ComSpaceTiming));
	memset(&AttSpaceTiming, 0, sizeof(AttSpaceTiming));
	
	HAL_NAND_DeInit(&hnand1);
	
	hnand1.Instance = FMC_NAND_DEVICE;
  /* hnand1.Init */
  hnand1.Init.NandBank = FMC_NAND_BANK3;
  hnand1.Init.Waitfeature = FMC_NAND_WAIT_FEATURE_ENABLE;
  hnand1.Init.MemoryDataWidth = FMC_NAND_MEM_BUS_WIDTH_8;
  hnand1.Init.EccComputation = FMC_NAND_ECC_ENABLE;
  hnand1.Init.ECCPageSize = FMC_NAND_ECC_PAGE_SIZE_2048BYTE;
  hnand1.Init.TCLRSetupTime = 2;
  hnand1.Init.TARSetupTime = 2;
  /* hnand1.Config */
  hnand1.Config.PageSize = 2048;
  hnand1.Config.SpareAreaSize = 64;
  hnand1.Config.BlockSize = 64;
  hnand1.Config.BlockNbr = 4096;
  hnand1.Config.PlaneNbr = 1;
  hnand1.Config.PlaneSize = 4096;
  hnand1.Config.ExtraCommandEnable = ENABLE;
  /* ComSpaceTiming */
  ComSpaceTiming.SetupTime = 9;
  ComSpaceTiming.WaitSetupTime = 9;
  ComSpaceTiming.HoldSetupTime = 10;
  ComSpaceTiming.HiZSetupTime = 9;
  /* AttSpaceTiming */
  AttSpaceTiming.SetupTime = 9;
  AttSpaceTiming.WaitSetupTime = 9;
  AttSpaceTiming.HoldSetupTime = 10;
  AttSpaceTiming.HiZSetupTime = 9;

  if (HAL_NAND_Init(&hnand1, &ComSpaceTiming, &AttSpaceTiming) != HAL_OK)
  {
    return 1;
  }
	return 0;
}

NOR_HandleTypeDef hnor;
FMC_NORSRAM_TimingTypeDef NOR_Timing;
int NOR_Init(void)
{ 
	memset(&hnor, 0, sizeof(hnor));
	memset(&NOR_Timing, 0, sizeof(NOR_Timing));
  hnor.Instance  = FMC_NORSRAM_DEVICE;
  hnor.Extended  = FMC_NORSRAM_EXTENDED_DEVICE;
  hnor.Init.NSBank             = FMC_NORSRAM_BANK1;
  
  HAL_NOR_DeInit(&hnor); 

  NOR_Timing.AddressSetupTime      = 4;
  NOR_Timing.AddressHoldTime       = 3;
  NOR_Timing.DataSetupTime         = 8;
  NOR_Timing.BusTurnAroundDuration = 1;
  NOR_Timing.CLKDivision           = 2;
  NOR_Timing.DataLatency           = 2;
  NOR_Timing.AccessMode            = FMC_ACCESS_MODE_A;

  hnor.Init.NSBank             = FMC_NORSRAM_BANK1;
  hnor.Init.DataAddressMux     = FMC_DATA_ADDRESS_MUX_DISABLE;
  hnor.Init.MemoryType         = FMC_MEMORY_TYPE_NOR;
  hnor.Init.MemoryDataWidth    = NOR_MEMORY_WIDTH;
  hnor.Init.BurstAccessMode    = FMC_BURST_ACCESS_MODE_DISABLE;
  hnor.Init.WaitSignalPolarity = FMC_WAIT_SIGNAL_POLARITY_LOW;
  hnor.Init.WaitSignalActive   = FMC_WAIT_TIMING_BEFORE_WS;
  hnor.Init.WriteOperation     = FMC_WRITE_OPERATION_ENABLE;
  hnor.Init.WaitSignal         = FMC_WAIT_SIGNAL_ENABLE;
  hnor.Init.ExtendedMode       = FMC_EXTENDED_MODE_DISABLE;
  hnor.Init.AsynchronousWait   = FMC_ASYNCHRONOUS_WAIT_ENABLE;
  hnor.Init.WriteBurst         = FMC_WRITE_BURST_DISABLE;
  hnor.Init.ContinuousClock    = FMC_CONTINUOUS_CLOCK_SYNC_ASYNC;
	  hnor.Init.WriteFifo =0x0 ;
  hnor.Init.PageSize = 0x0; 

  /* Initialize the NOR controller */
  if(HAL_NOR_Init(&hnor, &NOR_Timing, &NOR_Timing) != HAL_OK)
  {
    /* Initialization Error */
    return 1;
  }
  return 0;

}

/**
* @brief  System Clock Configuration
*         The system Clock is configured as follow : 
*            System Clock source            = PLL (HSE)
*            SYSCLK(Hz)                     = 400000000 (CM7 frequency)
*            HCLK(Hz)                       = 20000000  (CM4 frequency)
*            D1AHB Prescaler                = 1
*            D1APB1 Prescaler               = 1
*            D2APB1 Prescaler               = 1
*            D2APB2 Prescaler               = 1
*            HSE Frequency(Hz)              = 24000000
*            PLL_M                          = 12
*            PLL_N                          = 400
*            PLL_P                          = 2
*            Flash Latency(WS)              = 4
* @param  None
* @retval None
*/
 int SystemClock_Config(void)
{
  
  RCC_ClkInitTypeDef RCC_ClkInitStruct;
  RCC_OscInitTypeDef RCC_OscInitStruct;
  HAL_StatusTypeDef ret = HAL_OK;
  
  /*!< Supply configuration update enable */
  MODIFY_REG(PWR->CR3, PWR_CR3_SCUEN, 0);

  /* The voltage scaling allows optimizing the power consumption when the device is
     clocked below the maximum system frequency, to update the voltage scaling value
     regarding system frequency refer to product datasheet.  */
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

  while(!__HAL_PWR_GET_FLAG(PWR_FLAG_VOSRDY)) {}
  
  /* Enable HSE Oscillator and activate PLL with HSE as source */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.HSIState = RCC_HSI_OFF;
  RCC_OscInitStruct.CSIState = RCC_CSI_OFF;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;

  RCC_OscInitStruct.PLL.PLLM = 5;
  RCC_OscInitStruct.PLL.PLLN = 160;
  RCC_OscInitStruct.PLL.PLLP = 2;
  RCC_OscInitStruct.PLL.PLLR = 2;
  RCC_OscInitStruct.PLL.PLLQ = 4;

  RCC_OscInitStruct.PLL.PLLVCOSEL = RCC_PLL1VCOWIDE;
  RCC_OscInitStruct.PLL.PLLRGE = RCC_PLL1VCIRANGE_2;
  ret = HAL_RCC_OscConfig(&RCC_OscInitStruct);
  if(ret != HAL_OK)
  {
    return 1;
  }
  
/* Select PLL as system clock source and configure  bus clocks dividers */
  RCC_ClkInitStruct.ClockType = (RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_D1PCLK1 | RCC_CLOCKTYPE_PCLK1 | \
                                 RCC_CLOCKTYPE_PCLK2  | RCC_CLOCKTYPE_D3PCLK1);

  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.SYSCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB3CLKDivider = RCC_APB3_DIV2;  
  RCC_ClkInitStruct.APB1CLKDivider = RCC_APB1_DIV2; 
  RCC_ClkInitStruct.APB2CLKDivider = RCC_APB2_DIV2; 
  RCC_ClkInitStruct.APB4CLKDivider = RCC_APB4_DIV2; 
  ret = HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_4);
  if(ret != HAL_OK)
  {
    return 1;
  }
  
    /*Activate CSI clock mondatory for I/O Compensation Cell*/ 
  __HAL_RCC_CSI_ENABLE() ;
    
  /* Enable SYSCFG clock mondatory for I/O Compensation Cell */
  __HAL_RCC_SYSCFG_CLK_ENABLE() ;
  
  /* Enables the I/O Compensation Cell */ 
  HAL_EnableCompensationCell();
  
  return 0;
  
}
#if 0
int Sector_Erase (uint32_t EraseStartAddress ,uint32_t EraseEndAddress)
{     
  uint32_t BlockAddr;
  EraseStartAddress = EraseStartAddress -  EraseStartAddress%0x20000;
  while (EraseEndAddress>=EraseStartAddress)
  {
    BlockAddr = EraseStartAddress - StartAddresse;
    HAL_NOR_Erase_Block(&hnor, BlockAddr, NOR_BANK_ADDR);
    if(HAL_NOR_GetStatus(&hnor, NOR_BANK_ADDR, ERASE_TIMEOUT) != HAL_NOR_STATUS_SUCCESS)
      return 1;
    EraseStartAddress+=0x20000;
  }
  return 0;	
}

int Write_FMC (uint32_t Address, uint32_t Size, uint16_t* Buffer)
{    
  uint32_t InternalAddr = Address - StartAddresse;
  uint32_t uwIndex = 0;
  uint32_t WritedData = 0;
  uint32_t Counter = 0;   
  uint16_t TmpBuffer = 0x00000000;
  uint16_t * writeBuffer ;    
  if (InternalAddr%2 != 0)
  {
    HAL_NOR_ReadBuffer(&hnor, (NOR_BANK_ADDR + InternalAddr - InternalAddr%2),&TmpBuffer, 1);
        
    for (Counter =0; (Counter<(2-InternalAddr%2))&&(Counter<Size); Counter++)
      *((uint8_t*)(&TmpBuffer)+InternalAddr%2+Counter) = * ((uint8_t*)Buffer+Counter);
        
   HAL_NOR_Program(&hnor, (uint32_t *)(NOR_BANK_ADDR + InternalAddr - InternalAddr%2), &TmpBuffer);
   if(HAL_NOR_GetStatus(&hnor, NOR_BANK_ADDR + InternalAddr - InternalAddr%2, PROGRAM_TIMEOUT) != HAL_NOR_STATUS_SUCCESS)
    {
      return HAL_NOR_STATUS_ERROR;
    }
         
    WritedData += Counter;
  }
       
  if (Size-WritedData >= 2)
  {
    writeBuffer = (uint16_t*)((uint8_t*)Buffer+WritedData);
      for (uwIndex = 0; uwIndex < ((Size-WritedData)/2); uwIndex++)
  {
    /* Write data to NOR */
    HAL_NOR_Program(&hnor, (uint32_t *)(NOR_BANK_ADDR +InternalAddr+WritedData + 2*uwIndex), writeBuffer);

    /* Read NOR device status */
    if(HAL_NOR_GetStatus(&hnor, NOR_BANK_ADDR + InternalAddr+WritedData + 2*uwIndex, PROGRAM_TIMEOUT) != HAL_NOR_STATUS_SUCCESS)
    {
      return HAL_NOR_STATUS_ERROR;
    }
    writeBuffer ++ ;
  }
    
    WritedData += (((Size-WritedData)/2)*2);
  }
        
  if (WritedData < Size)
  {
    HAL_NOR_ReadBuffer(&hnor, NOR_BANK_ADDR+ InternalAddr+WritedData,&TmpBuffer, 1);

    for (Counter =0; Counter<(Size-WritedData); Counter++)
      *((uint8_t*)(&TmpBuffer)+Counter) = *((uint8_t*)Buffer+WritedData+Counter);
      
    HAL_NOR_Program(&hnor, (uint32_t *)(NOR_BANK_ADDR + InternalAddr+WritedData), &TmpBuffer);  
    if(HAL_NOR_GetStatus(&hnor,NOR_BANK_ADDR + InternalAddr+WritedData, PROGRAM_TIMEOUT) != HAL_NOR_STATUS_SUCCESS)
    {
      return HAL_NOR_STATUS_ERROR;
    }

  }

  return 0;
}
int chip_Erase(void )
	{	
	HAL_NOR_Erase_Chip(&hnor ,	NOR_BANK_ADDR);
	
	if(HAL_NOR_GetStatus(&hnor, NOR_BANK_ADDR, ERASE_TIMEOUT) != HAL_NOR_STATUS_SUCCESS)		
		return 1;
	
	return 0;
	}
#endif



