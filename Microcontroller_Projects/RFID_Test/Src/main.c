/* USER CODE BEGIN Header */
/*   MIT License
*
*    Copyright (c) 2019 Timothy Pansino, Adam Behnke, Zachary Neumann, Mitchell Keeney
*
*    Permission is hereby granted, free of charge, to any person obtaining a copy
*    of this software and associated documentation files (the "Software"), to deal
*    in the Software without restriction, including without limitation the rights
*    to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
*    copies of the Software, and to permit persons to whom the Software is
*    furnished to do so, subject to the following conditions:
*
*    The above copyright notice and this permission notice shall be included in all
*    copies or substantial portions of the Software.
*
*    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
*    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
*    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
*    AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
*    LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
*    OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
*    SOFTWARE.
*/
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
#define SPI_NSS_PIN_0  GPIOC, GPIO_PIN_0
#define SPI_NSS_PIN_1  GPIOC, GPIO_PIN_1
#define ANT_SEL_PIN_0  GPIOA, GPIO_PIN_12
#define ANT_SEL_PIN_1  GPIOA, GPIO_PIN_11
#define ANT_SEL_PIN_2  GPIOB, GPIO_PIN_12
#define SpiHandle hspi2

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
SPI_HandleTypeDef hspi2;

TIM_HandleTypeDef htim3;

UART_HandleTypeDef huart2;

/* USER CODE BEGIN PV */
char receiveBuffer[100];
char transmitBuffer[100];
char s[100];
int dataReceivedFlag = 0;
uint8_t receivedData = 0;
int currentLocation = 0;
int rfidReaderAddress = 0;
int rfidAntennaAddress = 0;

char* hello_world = "Hello World!";
char* newlineStr = NEWLINE_STR;
char* backSpace = BACKSPACE_STR;

// Boards
B curBoard;
B scanBoard;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_USART2_UART_Init(void);
static void MX_TIM3_Init(void);
static void MX_SPI2_Init(void);
/* USER CODE BEGIN PFP */
void HAL_UART_RxCpltCallback(UART_HandleTypeDef * huart);
char * receiveString(void);
void transmitString(char *);
void setup(void);
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
  MX_USART2_UART_Init();
  MX_TIM3_Init();
  MX_SPI2_Init();
  /* USER CODE BEGIN 2 */
  // Uart init message
  Print(CLEAR_TERMINAL);
  Print("UART Initialized.\n");

  // Initialize Pins
  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, 0);

  // Setup RFID Reader
  setup();
  mfrc630_flush_fifo(0);

  // Setup Board State
  blankBoard(curBoard);
  blankBoard(scanBoard);

  HAL_TIM_Base_Start_IT(&htim3);
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
	// Scan
	//Print(CLEAR_TERMINAL);

  	Print("Scanning...\n");
  	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, 1);
  	updateBoard(scanBoard);
  	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, 0);

	// Output results
	copyBoard(curBoard, scanBoard);
	printBoard(curBoard);

	// Delay
	HAL_Delay(1000);
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
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

  /**Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);
  /**Initializes the CPU, AHB and APB busses clocks
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLM = 16;
  RCC_OscInitStruct.PLL.PLLN = 400;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV4;
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
}

/**
  * @brief SPI2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_SPI2_Init(void)
{

  /* USER CODE BEGIN SPI2_Init 0 */

  /* USER CODE END SPI2_Init 0 */

  /* USER CODE BEGIN SPI2_Init 1 */

  /* USER CODE END SPI2_Init 1 */
  /* SPI2 parameter configuration*/
  hspi2.Instance = SPI2;
  hspi2.Init.Mode = SPI_MODE_MASTER;
  hspi2.Init.Direction = SPI_DIRECTION_2LINES;
  hspi2.Init.DataSize = SPI_DATASIZE_8BIT;
  hspi2.Init.CLKPolarity = SPI_POLARITY_LOW;
  hspi2.Init.CLKPhase = SPI_PHASE_1EDGE;
  hspi2.Init.NSS = SPI_NSS_SOFT;
  hspi2.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_64;
  hspi2.Init.FirstBit = SPI_FIRSTBIT_MSB;
  hspi2.Init.TIMode = SPI_TIMODE_DISABLE;
  hspi2.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
  hspi2.Init.CRCPolynomial = 10;
  if (HAL_SPI_Init(&hspi2) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN SPI2_Init 2 */

  /* USER CODE END SPI2_Init 2 */

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
  htim3.Init.Prescaler = 9999;
  htim3.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim3.Init.Period = 2000;
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
  * @brief USART2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART2_UART_Init(void)
{

  /* USER CODE BEGIN USART2_Init 0 */

  /* USER CODE END USART2_Init 0 */

  /* USER CODE BEGIN USART2_Init 1 */

  /* USER CODE END USART2_Init 1 */
  huart2.Instance = USART2;
  huart2.Init.BaudRate = 115200;
  huart2.Init.WordLength = UART_WORDLENGTH_8B;
  huart2.Init.StopBits = UART_STOPBITS_1;
  huart2.Init.Parity = UART_PARITY_NONE;
  huart2.Init.Mode = UART_MODE_TX_RX;
  huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart2.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart2) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART2_Init 2 */

  /* USER CODE END USART2_Init 2 */

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
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOH_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOC, SPI3_NSS_0_Pin|SPI3_NSS_1_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(LD2_GPIO_Port, LD2_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(ANT_SEL_0_GPIO_Port, ANT_SEL_0_Pin, GPIO_PIN_SET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, ANT_SEL_2_Pin|ANT_SEL_1_Pin, GPIO_PIN_SET);

  /*Configure GPIO pin : B1_Pin */
  GPIO_InitStruct.Pin = B1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(B1_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : SPI3_NSS_0_Pin SPI3_NSS_1_Pin */
  GPIO_InitStruct.Pin = SPI3_NSS_0_Pin|SPI3_NSS_1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pins : LD2_Pin ANT_SEL_2_Pin ANT_SEL_1_Pin */
  GPIO_InitStruct.Pin = LD2_Pin|ANT_SEL_2_Pin|ANT_SEL_1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pin : ANT_SEL_0_Pin */
  GPIO_InitStruct.Pin = ANT_SEL_0_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(ANT_SEL_0_GPIO_Port, &GPIO_InitStruct);

}

/* USER CODE BEGIN 4 */
void mfrc630_SPI_transfer(uint8_t* tx, uint8_t* rx, uint16_t len){
  switch(HAL_SPI_TransmitReceive(&SpiHandle, tx, rx, len, TIMEOUT)){
      case HAL_OK:
        //Print("SPI OK\n");
        break;
      case HAL_TIMEOUT:
        Print("Timeout\n");
        break;
      case HAL_ERROR:
        Print("SPI Error (No idea, good luck)\n");
        Error_Handler();
        break;
      default:
        break;
  }
}

void mfrc630_SPI_select(){
  // Unselect all pins first
  mfrc630_SPI_unselect();

  // Set reader NSS pin
  if (rfidReaderAddress == 0) {
	HAL_GPIO_WritePin(SPI_NSS_PIN_0, 0);
  }
  else if (rfidReaderAddress == 1) {
	HAL_GPIO_WritePin(SPI_NSS_PIN_1, 0);
  }

  // Set antenna address
  HAL_GPIO_WritePin(ANT_SEL_PIN_2, (rfidAntennaAddress >> 2) & 1);
  HAL_GPIO_WritePin(ANT_SEL_PIN_1, (rfidAntennaAddress >> 1) & 1);
  HAL_GPIO_WritePin(ANT_SEL_PIN_0, rfidAntennaAddress & 1);
}

void mfrc630_SPI_unselect(){
	// Unselect all readers
	HAL_GPIO_WritePin(SPI_NSS_PIN_0, 1);
	HAL_GPIO_WritePin(SPI_NSS_PIN_1, 1);
}


void setup(void) {
  // Antenna Address Init
  rfidAntennaAddress = 0;

  // Set the registers of the MFRC630 into the default.
  //for (rfidReaderAddress = 0; rfidReaderAddress < 8; rfidReaderAddress++) {
  for (rfidReaderAddress = 0; rfidReaderAddress < 2; rfidReaderAddress++) {
	  mfrc630_SPI_select();

	  mfrc630_AN1102_recommended_registers(MFRC630_PROTO_ISO14443A_106_MILLER_MANCHESTER);
	  mfrc630_write_reg(0x28, 0x8E);
	  mfrc630_write_reg(0x29, 0x15);
	  mfrc630_write_reg(0x2A, 0x11);
	  mfrc630_write_reg(0x2B, 0x06);

	  mfrc630_SPI_unselect();
  }
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
    if (htim->Instance == htim3.Instance)
    {

    }
}


void HAL_UART_RxCpltCallback(UART_HandleTypeDef * huart)
{
    /* Move data into buffer */
    receiveBuffer[currentLocation] = receivedData;

    /* Variable to keep track of location in buffer */
    if (((char)receiveBuffer[currentLocation] == '\n') || ((char)receiveBuffer[currentLocation] == '\r')) {
        HAL_UART_Transmit(&huart2, (uint8_t*) newlineStr, 2, TIMEOUT);
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
        HAL_UART_Transmit(&huart2, &receivedData, 1, TIMEOUT);
        currentLocation++;
    }
}

char * receiveString(void) {
    /* Listen for input; print back to screen when fully received */
    while (!dataReceivedFlag) {
        HAL_UART_Receive_IT(&huart2, &receivedData, 1);
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
			HAL_UART_Transmit(&huart2, (uint8_t*) newlineStr, 2, TIMEOUT);
		}
		else if (s[i] != '\r' && s[i] != '\0') {
			HAL_UART_Transmit(&huart2, (uint8_t*) &s[i], 1, TIMEOUT);
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
