#include "main.h"
#include "stm32l4xx_hal.h"

ADC_HandleTypeDef hadc1;
UART_HandleTypeDef huart1;
DMA_HandleTypeDef hdma_usart1_tx;

volatile int flag;

void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_USART1_UART_Init(void);
static void MX_ADC1_ADC_Init(void);

int UART_print_string (UART_HandleTypeDef* huart1, char* array, int length)
{

	if (HAL_UART_Transmit(huart1, (uint8_t *)array, length,3000) == HAL_OK){
		return 1;
	}else
		return 0;
}






int main(void)
 {
	char tempArray[19] = {'T','e','m','p','e','r','a','t','u','r','e',' ','=',' ','1','1',' ','C','\n'};
	char received[1];
	char output[2] = {'Y','!'};
	char ch[5] = {'j','o','b','s','\n'};

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();
  /* Configure the system clock */
  SystemClock_Config();
  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_USART1_UART_Init();
	MX_ADC1_ADC_Init();

  /* Infinite loop */
  while (1)
  {

		//HAL_Delay(40);
		
		//HAL_UART_Transmit(&huart1, (uint8_t *)&ch[0], 5, 30000);
		
		//------receive 'X', transmit 'Y'------//
		
//		if (HAL_UART_Receive (&huart1, (uint8_t *)&received[0], 1, 30000) == HAL_OK && received[0] == 'X'){
//			HAL_UART_Transmit(&huart1, (uint8_t *)&output[0], 1, 30000);
//		}else{
//			HAL_UART_Transmit(&huart1, (uint8_t *)&output[1], 1, 30000);
//		}

		
		
		if(flag == 1){
			flag = 0;
		
			HAL_ADC_Start(&hadc1);		//Enable ADC, start conversion of regular group
			if(HAL_ADC_PollForConversion(&hadc1, 10000) == HAL_OK){	//checks if conversion is done
					uint32_t tempVoltage = HAL_ADC_GetValue(&hadc1);	//gets value
					int tempCelcius = __HAL_ADC_CALC_TEMPERATURE(3300, tempVoltage, ADC_RESOLUTION_12B);
	


					//---------Temperature casted to character-----------	
					tempArray[14] = (tempCelcius/10) + '0';
					tempArray[15] = (tempCelcius%10) + '0';

					UART_print_string(&huart1, tempArray, 19);	
			}			//VREF = 3.3 
		
		
		}
		
  }
}




//----ADC initialization function------
void MX_ADC1_ADC_Init(void){
	
	
	__HAL_RCC_ADC_CLK_ENABLE(); 
														
	hadc1.Instance = ADC1;		
	hadc1.Init.ClockPrescaler = ADC_CLOCKPRESCALER_PCLK_DIV2; 
																								
	hadc1.Init.Resolution = ADC_RESOLUTION_12B;	//ADC 12-bit resolution 
	hadc1.Init.DataAlign = ADC_DATAALIGN_RIGHT;	//MSB is left most bit in Right alligned
	hadc1.Init.ScanConvMode = ADC_SCAN_DISABLE;	//Scan mode disabled, Conversion is performed in single mode
	hadc1.Init.EOCSelection = DISABLE; 
	hadc1.Init.LowPowerAutoWait = DISABLE;	//new conversion start only when the previous conversion has been retrieved by user software
	hadc1.Init.DiscontinuousConvMode = DISABLE;
	hadc1.Init.ContinuousConvMode = ENABLE;	//the conversion is performed in single mode, maybe redundant
	hadc1.Init.ExternalTrigConv = ADC_SOFTWARE_START;	//software trigger is used to trigger ADC group regular conversion
	hadc1.Init.NbrOfConversion = 1;
	hadc1.Init.DMAContinuousRequests = ENABLE;
	hadc1.Init.Overrun = ADC_OVR_DATA_OVERWRITTEN;	
	
	//Initialize the ADC peripheral and regular group according to parameters specified in structure "ADC_InitTypeDef"
	if (HAL_ADC_Init(&hadc1) != HAL_OK){
		_Error_Handler(__FILE__, __LINE__);
	}
	
	//-------channel configuration for regular group parameters------
	ADC_ChannelConfTypeDef channelConfig;	//instantiation of a sub
	
	channelConfig.Channel = ADC_CHANNEL_TEMPSENSOR; //ADC temperature sensor channel 
  channelConfig.Rank = ADC_REGULAR_RANK_1;	//The only ADC being used
	channelConfig.SamplingTime = ADC_SAMPLETIME_47CYCLES_5;	//refer to temp sensor
	//channelConfig.SingleDiff = ADC_SINGLE_ENDED;	//ADC channel set in single-ended input mode 
	//channelConfig.OffsetNumber = ADC_OFFSET_NONE;	//No offset correction 
	channelConfig.Offset = 0;	//Zero Offset, maybe redundant
	
	//Configure a channel to be assigned to ADC group regular, initialize the sub-modules/sub-instances
	if (HAL_ADC_ConfigChannel(&hadc1, &channelConfig) != HAL_OK){
		_Error_Handler(__FILE__, __LINE__);
	}
	

	if (HAL_ADCEx_Calibration_Start(&hadc1, ADC_SINGLE_ENDED) != HAL_OK){
		_Error_Handler(__FILE__, __LINE__);
	}
}
void SystemClock_Config(void)
{

  RCC_OscInitTypeDef RCC_OscInitStruct;
  RCC_ClkInitTypeDef RCC_ClkInitStruct;
  RCC_PeriphCLKInitTypeDef PeriphClkInit;

    /**Initializes the CPU, AHB and APB busses clocks 
    */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_MSI;
  RCC_OscInitStruct.MSIState = RCC_MSI_ON;
  RCC_OscInitStruct.MSICalibrationValue = 0;
  RCC_OscInitStruct.MSIClockRange = RCC_MSIRANGE_6;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_MSI;
  RCC_OscInitStruct.PLL.PLLM = 1;
  RCC_OscInitStruct.PLL.PLLN = 40;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV7;
  RCC_OscInitStruct.PLL.PLLQ = RCC_PLLQ_DIV2;
  RCC_OscInitStruct.PLL.PLLR = RCC_PLLR_DIV2;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

    /**Initializes the CPU, AHB and APB busses clocks 
    */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_4) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_USART1|RCC_PERIPHCLK_ADC;
  PeriphClkInit.Usart1ClockSelection = RCC_USART1CLKSOURCE_PCLK2;
  PeriphClkInit.AdcClockSelection = RCC_ADCCLKSOURCE_PLLSAI1;
  PeriphClkInit.PLLSAI1.PLLSAI1Source = RCC_PLLSOURCE_MSI;
  PeriphClkInit.PLLSAI1.PLLSAI1M = 1;
  PeriphClkInit.PLLSAI1.PLLSAI1N = 32;
  PeriphClkInit.PLLSAI1.PLLSAI1P = RCC_PLLP_DIV7;
  PeriphClkInit.PLLSAI1.PLLSAI1Q = RCC_PLLQ_DIV2;
  PeriphClkInit.PLLSAI1.PLLSAI1R = RCC_PLLR_DIV2;
  PeriphClkInit.PLLSAI1.PLLSAI1ClockOut = RCC_PLLSAI1_ADC1CLK;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

    /**Configure the main internal regulator output voltage 
    */
  if (HAL_PWREx_ControlVoltageScaling(PWR_REGULATOR_VOLTAGE_SCALE1) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

    /**Configure the Systick interrupt time 
			reload value = sys tick counter clock (Hz) x desired time base (s)
    */
  HAL_SYSTICK_Config(HAL_RCC_GetHCLKFreq()/10);



    /**Configure the Systick 
    */
  HAL_SYSTICK_CLKSourceConfig(SYSTICK_CLKSOURCE_HCLK);

  /* SysTick_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(SysTick_IRQn, 0, 0);
}

/* USART1 init function */
static void MX_USART1_UART_Init(void)
{
  huart1.Instance = USART1;
  huart1.Init.BaudRate = 115200;
  huart1.Init.WordLength = UART_WORDLENGTH_8B;
  huart1.Init.StopBits = UART_STOPBITS_1;
  huart1.Init.Parity = UART_PARITY_NONE;
  huart1.Init.Mode = UART_MODE_TX_RX;
  huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart1.Init.OverSampling = UART_OVERSAMPLING_16;
  huart1.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
  huart1.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
  if (HAL_UART_Init(&huart1) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

}

static void MX_GPIO_Init(void)
{
  __HAL_RCC_GPIOB_CLK_ENABLE();
}


void _Error_Handler(char *file, int line)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  while(1)
  {
  }
}

#ifdef  USE_FULL_ASSERT
void assert_failed(uint8_t* file, uint32_t line)
{ 
}
#endif /* USE_FULL_ASSERT */
