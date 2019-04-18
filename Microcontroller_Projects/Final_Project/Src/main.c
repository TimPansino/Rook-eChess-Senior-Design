/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  ** This notice applies to any and all portions of this file
  * that are not between comment pairs USER CODE BEGIN and
  * USER CODE END. Other portions of this file, whether 
  * inserted by the user or by software development tools
  * are owned by their respective copyright owners.
  *
  * COPYRIGHT(c) 2019 STMicroelectronics
  *
  * Redistribution and use in source and binary forms, with or without modification,
  * are permitted provided that the following conditions are met:
  *   1. Redistributions of source code must retain the above copyright notice,
  *      this list of conditions and the following disclaimer.
  *   2. Redistributions in binary form must reproduce the above copyright notice,
  *      this list of conditions and the following disclaimer in the documentation
  *      and/or other materials provided with the distribution.
  *   3. Neither the name of STMicroelectronics nor the names of its contributors
  *      may be used to endorse or promote products derived from this software
  *      without specific prior written permission.
  *
  * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
  * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include <stdarg.h>
#include <string.h>
#include "mfrc630.h"
#include "mfrc630_def.h"

#include "pieces.h"
#include "chess.h"
#include "micro.h"
#include "debug.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
#define 	STATUS_LED					GPIOB, 	   GPIO_PIN_8
#define     BUTTON_1     				GPIOE,     GPIO_PIN_2
#define     BUTTON_2     				GPIOE,     GPIO_PIN_3
#define     BUTTON_3     				GPIOE,     GPIO_PIN_4
#define     BUTTON_4     				GPIOE,     GPIO_PIN_5
#define     BUTTON_5     				GPIOE,     GPIO_PIN_6
#define     LCD_ENABLE     				GPIOE,     GPIO_PIN_9
#define     LCD_RS     					GPIOE,     GPIO_PIN_7
#define     LCD_RW     					GPIOE,     GPIO_PIN_8
#define     LED_ADDRESS_0     			GPIOD,     GPIO_PIN_1
#define     LED_ADDRESS_1     			GPIOD,     GPIO_PIN_2
#define     LED_ADDRESS_2     			GPIOD,     GPIO_PIN_3
#define     LED_ADDRESS_3     			GPIOD,     GPIO_PIN_4
#define     LED_ADDRESS_4     			GPIOD,     GPIO_PIN_5
#define     LED_ADDRESS_5     			GPIOD,     GPIO_PIN_6
#define     LED_BLUE_DATA     			GPIOD,     GPIO_PIN_9
#define     LED_GREEN_DATA     			GPIOD,     GPIO_PIN_8
#define     LED_RED_DATA     			GPIOD,     GPIO_PIN_7
#define     LED_WEN     				GPIOD,     GPIO_PIN_0
#define     RFID_ANTENNA_ADDRESS_0     	GPIOB,     GPIO_PIN_13
#define     RFID_ANTENNA_ADDRESS_1     	GPIOB,     GPIO_PIN_14
#define     RFID_ANTENNA_ADDRESS_2     	GPIOB,     GPIO_PIN_15
#define     RFID_SPI2_NSS_0 			GPIOC,     GPIO_PIN_4
#define     RFID_SPI2_NSS_1     		GPIOC,     GPIO_PIN_5
#define     RFID_SPI2_NSS_2     		GPIOC,     GPIO_PIN_6
#define     RFID_SPI2_NSS_3     		GPIOC,     GPIO_PIN_7
#define     RFID_SPI2_NSS_4     		GPIOC,     GPIO_PIN_8
#define     RFID_SPI2_NSS_5     		GPIOC,     GPIO_PIN_9
#define     RFID_SPI2_NSS_6     		GPIOC,     GPIO_PIN_10
#define     RFID_SPI2_NSS_7     		GPIOC,     GPIO_PIN_11

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
RTC_HandleTypeDef hrtc;

SPI_HandleTypeDef hspi3;

TIM_HandleTypeDef htim3;

UART_HandleTypeDef huart1;

/* USER CODE BEGIN PV */
// UART variables
char receiveBuffer[100];
char transmitBuffer[100];
int dataReceivedFlag = 0;
uint8_t receivedData = 0;
int currentLocation = 0;
char* hello_world = "Hello World!\n";
char* newlineStr = NEWLINE_STR;
char* backSpace = BACKSPACE_STR;

// Chess variables
int rfidReaderAddress = 0;
int rfidAntennaAddress = 0;

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_RTC_Init(void);
static void MX_USART1_UART_Init(void);
static void MX_SPI3_Init(void);
static void MX_TIM3_Init(void);
/* USER CODE BEGIN PFP */
static void writeLCDMessage(char lcd_upr[], char lcd_low[]);
static void writeLCDInstruction(uint8_t * instru);
void LCDInit(void);
void HAL_UART_RxCpltCallback(UART_HandleTypeDef * huart);
char * receiveString(void);
void transmitString(char *);
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_RTC_Init();
  MX_USART1_UART_Init();
  MX_SPI3_Init();
  MX_TIM3_Init();
  /* USER CODE BEGIN 2 */
  // Init Uart
  Print(CLEAR_TERMINAL);
  Print("UART Initialized.\n");

  // Init LCD
  LCDInit();
  Print("LCD Initialized\n");
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
	HAL_GPIO_WritePin(STATUS_LED, 1);
	Print(hello_world);
	writeLCDMessage("Hello", "World");
	HAL_Delay(1000);
	HAL_GPIO_WritePin(STATUS_LED, 0);
	HAL_Delay(1000);
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};
  RCC_PeriphCLKInitTypeDef PeriphClkInitStruct = {0};

  /**Configure the main internal regulator output voltage 
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);
  /**Initializes the CPU, AHB and APB busses clocks 
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI|RCC_OSCILLATORTYPE_LSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.LSIState = RCC_LSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLM = 8;
  RCC_OscInitStruct.PLL.PLLN = 100;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 4;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /**Initializes the CPU, AHB and APB busses clocks 
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_3) != HAL_OK)
  {
    Error_Handler();
  }
  PeriphClkInitStruct.PeriphClockSelection = RCC_PERIPHCLK_RTC;
  PeriphClkInitStruct.RTCClockSelection = RCC_RTCCLKSOURCE_LSI;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief RTC Initialization Function
  * @param None
  * @retval None
  */
static void MX_RTC_Init(void)
{

  /* USER CODE BEGIN RTC_Init 0 */

  /* USER CODE END RTC_Init 0 */

  /* USER CODE BEGIN RTC_Init 1 */

  /* USER CODE END RTC_Init 1 */
  /**Initialize RTC Only 
  */
  hrtc.Instance = RTC;
  hrtc.Init.HourFormat = RTC_HOURFORMAT_24;
  hrtc.Init.AsynchPrediv = 127;
  hrtc.Init.SynchPrediv = 255;
  hrtc.Init.OutPut = RTC_OUTPUT_DISABLE;
  hrtc.Init.OutPutPolarity = RTC_OUTPUT_POLARITY_HIGH;
  hrtc.Init.OutPutType = RTC_OUTPUT_TYPE_OPENDRAIN;
  if (HAL_RTC_Init(&hrtc) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN RTC_Init 2 */

  /* USER CODE END RTC_Init 2 */

}

/**
  * @brief SPI3 Initialization Function
  * @param None
  * @retval None
  */
static void MX_SPI3_Init(void)
{

  /* USER CODE BEGIN SPI3_Init 0 */

  /* USER CODE END SPI3_Init 0 */

  /* USER CODE BEGIN SPI3_Init 1 */

  /* USER CODE END SPI3_Init 1 */
  /* SPI3 parameter configuration*/
  hspi3.Instance = SPI3;
  hspi3.Init.Mode = SPI_MODE_MASTER;
  hspi3.Init.Direction = SPI_DIRECTION_2LINES;
  hspi3.Init.DataSize = SPI_DATASIZE_8BIT;
  hspi3.Init.CLKPolarity = SPI_POLARITY_LOW;
  hspi3.Init.CLKPhase = SPI_PHASE_1EDGE;
  hspi3.Init.NSS = SPI_NSS_SOFT;
  hspi3.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_256;
  hspi3.Init.FirstBit = SPI_FIRSTBIT_MSB;
  hspi3.Init.TIMode = SPI_TIMODE_DISABLE;
  hspi3.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
  hspi3.Init.CRCPolynomial = 10;
  if (HAL_SPI_Init(&hspi3) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN SPI3_Init 2 */

  /* USER CODE END SPI3_Init 2 */

}

/**
  * @brief TIM3 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM3_Init(void)
{

  /* USER CODE BEGIN TIM3_Init 0 */

  /* USER CODE END TIM3_Init 0 */

  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};

  /* USER CODE BEGIN TIM3_Init 1 */

  /* USER CODE END TIM3_Init 1 */
  htim3.Instance = TIM3;
  htim3.Init.Prescaler = 10000;
  htim3.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim3.Init.Period = 100;
  htim3.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  if (HAL_TIM_Base_Init(&htim3) != HAL_OK)
  {
    Error_Handler();
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim3, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim3, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM3_Init 2 */

  /* USER CODE END TIM3_Init 2 */

}

/**
  * @brief USART1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART1_UART_Init(void)
{

  /* USER CODE BEGIN USART1_Init 0 */

  /* USER CODE END USART1_Init 0 */

  /* USER CODE BEGIN USART1_Init 1 */

  /* USER CODE END USART1_Init 1 */
  huart1.Instance = USART1;
  huart1.Init.BaudRate = 115200;
  huart1.Init.WordLength = UART_WORDLENGTH_8B;
  huart1.Init.StopBits = UART_STOPBITS_1;
  huart1.Init.Parity = UART_PARITY_NONE;
  huart1.Init.Mode = UART_MODE_TX_RX;
  huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart1.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART1_Init 2 */

  /* USER CODE END USART1_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOE_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOC_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOE, GPIO_PIN_7|GPIO_PIN_8|GPIO_PIN_9, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(STATUS_LED_GPIO_Port, STATUS_LED_Pin, GPIO_PIN_SET);

  /*Configure GPIO pins : PE7 PE8 PE9 */
  GPIO_InitStruct.Pin = GPIO_PIN_7|GPIO_PIN_8|GPIO_PIN_9;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);

  /*Configure GPIO pin : STATUS_LED_Pin */
  GPIO_InitStruct.Pin = STATUS_LED_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(STATUS_LED_GPIO_Port, &GPIO_InitStruct);

}

/* USER CODE BEGIN 4 */
void HAL_UART_RxCpltCallback(UART_HandleTypeDef * huart)
{
    /* Move data into buffer */
    receiveBuffer[currentLocation] = receivedData;

    /* Variable to keep track of location in buffer */
    if (((char)receiveBuffer[currentLocation] == '\n') || ((char)receiveBuffer[currentLocation] == '\r')) {
        HAL_UART_Transmit(huart, (uint8_t*) newlineStr, 2, TIMEOUT);
        dataReceivedFlag = 1;
        receiveBuffer[currentLocation] = '\0';
        currentLocation = 0;
    }
    else if (((char)receiveBuffer[currentLocation] == 0x08) || ((char)receiveBuffer[currentLocation] == 0x7F)) {
    	if (currentLocation > 0) {
        	Print(backSpace);
        	receiveBuffer[currentLocation] = '\0';
    		currentLocation--;
    	}
    }
    else {
        HAL_UART_Transmit(huart, &receivedData, 1, TIMEOUT);
        currentLocation++;
    }
}

char * receiveString(void) {
    /* Listen for input; print back to screen when fully received */
    while (!dataReceivedFlag) {
        HAL_UART_Receive_IT(&huart1, &receivedData, 1);
    }
    dataReceivedFlag = 0;
    return receiveBuffer;
}

void transmitString(char * s) {
	//int size = 0;
	int i;

	//while(s[size] != '\0') size++;
	for (i = 0; s[i] != '\0'; i++) {
		if (s[i] == '\n') {
			HAL_UART_Transmit(&huart1, (uint8_t*) newlineStr, 2, TIMEOUT);
		}
		else if (s[i] != '\r' && s[i] != '\0') {
			HAL_UART_Transmit(&huart1, (uint8_t*) &s[i], 1, TIMEOUT);
		}
	}

	return;
}

void Print(const char* format, ...) {
  va_list args;
  va_start(args, format);
  vsprintf(transmitBuffer, format, args);
  transmitString(transmitBuffer);
  va_end(args);

  return;
}

static void writeLCDMessage(char* lcd_upr, char* lcd_low)
{
    uint8_t loc_instru = CURMOV;
    writeLCDInstruction(&loc_instru);
    loc_instru = LINE1;
    writeLCDInstruction(&loc_instru);
    HAL_GPIO_WritePin (LCD_RS, GPIO_PIN_SET);

    uint8_t x = lcd_upr[0];
    int count = 0;
    while(x != '\0')
    {
        HAL_SPI_Transmit (&hspi3, (uint8_t) &lcd_upr[count], 1, TIMEOUT);
        while(HAL_SPI_GetState(&hspi3) != HAL_SPI_STATE_READY)
            ;
        HAL_GPIO_WritePin (LCD_ENABLE, GPIO_PIN_SET);
        HAL_Delay(1);
        HAL_GPIO_WritePin (LCD_ENABLE, GPIO_PIN_RESET);
        count++;
        x = lcd_upr[count];
    }
    loc_instru = CURMOV;
    writeLCDInstruction(&loc_instru);
    loc_instru = LINE2;
    writeLCDInstruction(&loc_instru);
    HAL_GPIO_WritePin (LCD_RS, GPIO_PIN_SET);

    x = lcd_low[0];
    count = 0;
    while(x != '\0')
    {
        HAL_SPI_Transmit (&hspi3, (uint8_t) &lcd_upr[count], 1, TIMEOUT);
        while(HAL_SPI_GetState(&hspi3) != HAL_SPI_STATE_READY)
            ;
        HAL_GPIO_WritePin (LCD_ENABLE, GPIO_PIN_RESET);
        HAL_GPIO_WritePin (LCD_ENABLE, GPIO_PIN_SET);
        HAL_Delay(1);
        HAL_GPIO_WritePin (LCD_ENABLE, GPIO_PIN_RESET);
        count++;
        x = lcd_low[count];
    }
}

static void writeLCDInstruction(uint8_t * instru)
{
    HAL_GPIO_WritePin (LCD_RS, GPIO_PIN_RESET);
    HAL_SPI_Transmit (&hspi3, instru, 1, TIMEOUT);
    while(HAL_SPI_GetState(&hspi3) != HAL_SPI_STATE_READY)
        ;
    HAL_GPIO_WritePin (LCD_ENABLE, GPIO_PIN_RESET);
    HAL_GPIO_WritePin (LCD_ENABLE, GPIO_PIN_SET);
    HAL_Delay(1);
    HAL_GPIO_WritePin (LCD_ENABLE, GPIO_PIN_RESET);
}

void LCDInit(void) {
	HAL_Delay(15);
	HAL_GPIO_WritePin (LCD_RS, GPIO_PIN_RESET);
	HAL_GPIO_WritePin (LCD_RW, GPIO_PIN_RESET);
	uint8_t instru = LCDON;
	writeLCDInstruction(&instru);
	HAL_Delay(4);
	instru = TWOLINE;
	writeLCDInstruction(&instru);
	instru = LCDCLR;
	writeLCDInstruction(&instru);
	instru = MODE;
	writeLCDInstruction(&instru);
}

void Scan(char* s) {
	receiveString();
	strcpy(s, receiveBuffer);

	return;
}
/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */

  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{ 
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
