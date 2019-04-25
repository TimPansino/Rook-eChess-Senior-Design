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
#include "drivers.h"

#include "ai.h"
#include "defs.h"
#include "protos.h"
#include "data.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

// Handles
#define		RFID_SPI_HANDLE             hspi2
#define		LCD_SPI_HANDLE              hspi3
#define 	UART_HANDLE                 huart1
#define 	TIMER_HANDLE                htim4

// Pins
#define     STATUS_LED                  GPIOB, 	   GPIO_PIN_8
#define     BUTTON_1                    GPIOE,     GPIO_PIN_2
#define     BUTTON_2                    GPIOE,     GPIO_PIN_3
#define     BUTTON_3                    GPIOE,     GPIO_PIN_4
#define     BUTTON_4                    GPIOE,     GPIO_PIN_5
#define     BUTTON_5                    GPIOE,     GPIO_PIN_6
#define     LCD_RS                      GPIOE,     GPIO_PIN_7
#define     LCD_RW                      GPIOE,     GPIO_PIN_8
#define     LCD_ENABLE                  GPIOE,     GPIO_PIN_9
#define     LED_ADDRESS_0               GPIOD,     GPIO_PIN_1
#define     LED_ADDRESS_1               GPIOD,     GPIO_PIN_2
#define     LED_ADDRESS_2               GPIOD,     GPIO_PIN_3
#define     LED_ADDRESS_3               GPIOD,     GPIO_PIN_4
#define     LED_ADDRESS_4               GPIOD,     GPIO_PIN_5
#define     LED_ADDRESS_5               GPIOD,     GPIO_PIN_6
#define     LED_BLUE                    GPIOD,     GPIO_PIN_9
#define     LED_GREEN                   GPIOD,     GPIO_PIN_8
#define     LED_RED                     GPIOD,     GPIO_PIN_7
#define     LED_ENABLE                  GPIOD,     GPIO_PIN_0
#define     RFID_ANTENNA_ADDRESS_0     	GPIOB,     GPIO_PIN_13
#define     RFID_ANTENNA_ADDRESS_1     	GPIOB,     GPIO_PIN_14
#define     RFID_ANTENNA_ADDRESS_2     	GPIOB,     GPIO_PIN_15
#define     RFID_SPI2_NSS_0             GPIOC,     GPIO_PIN_4
#define     RFID_SPI2_NSS_1             GPIOC,     GPIO_PIN_5
#define     RFID_SPI2_NSS_2             GPIOA, 	   GPIO_PIN_5
#define     RFID_SPI2_NSS_3             GPIOC, 	   GPIO_PIN_10
#define     RFID_SPI2_NSS_4             GPIOD,     GPIO_PIN_14
#define     RFID_SPI2_NSS_5             GPIOD,     GPIO_PIN_12
#define     RFID_SPI2_NSS_6             GPIOC,     GPIO_PIN_8
#define     RFID_SPI2_NSS_7             GPIOC,     GPIO_PIN_6

// Constants
#define 	  DISABLE_PRINT               1
#define		  LED_DEMO					  1
#define 	  SKIP_SETUP_HELP			  0

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
RTC_HandleTypeDef hrtc;

SPI_HandleTypeDef hspi2;
SPI_HandleTypeDef hspi3;

TIM_HandleTypeDef htim4;

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
char prevMove[100];

// Chess variables
int rfidReaderAddress = 0;
int rfidAntennaAddress = 0;
C colors;
B curBoard;
B prevBoard;
B prevAIBoard;
M curMoves;
Move curMove;
Piece tempPiece;
int check = 0;
int status = 10;
int curSide = White;
int aiSide = 0;
int curTime = 0;
int aiMovedFlag = 0;
char aiMove[10];

// Buttons
int prevButton[5] = {0};
int curButton[5] = {0};
int buttonFlag[5] = {0};
int resetFlag = 1;

// LCD Menus
char* playerMenu[] = {" Select Players ", "1 Player", "2 Player"};
char* sideMenu[] = {"Select Your Side", "White", "Black"};
char* pawnPromoteMenu[] = {"Promote Pawn", "Queen", "Knight", "Rook", "Bishop"};

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_RTC_Init(void);
static void MX_USART1_UART_Init(void);
static void MX_SPI3_Init(void);
static void MX_SPI2_Init(void);
static void MX_TIM4_Init(void);
/* USER CODE BEGIN PFP */
void HAL_UART_RxCpltCallback(UART_HandleTypeDef * huart);
char * receiveString(void);
void transmitString(char *);
static void writeLCDMessage(char* lcd_upr, char* lcd_low);
static void writeLCDInstruction(uint8_t instru);
void LCDInit(void);
void RFIDInit(void);
void LEDInit(void);
void buttonInit(void);
void chessInit(char aiSide);
int chessMain(void);
void mainMenu(void);
int checkButtons(void);
void moveToLCD(void);
void moveStrToLCD(char* s);
void strToMenu(char* s, char* d);
void boardSetup(void);
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
  MX_SPI2_Init();
  MX_TIM4_Init();
  /* USER CODE BEGIN 2 */
  HAL_Delay(1000);

	// Initialize Pins
	HAL_GPIO_WritePin(STATUS_LED, 0);
	HAL_GPIO_WritePin(RFID_SPI2_NSS_0, 1);
	HAL_GPIO_WritePin(RFID_SPI2_NSS_1, 1);
	HAL_GPIO_WritePin(RFID_SPI2_NSS_2, 1);
	HAL_GPIO_WritePin(RFID_SPI2_NSS_3, 1);
	HAL_GPIO_WritePin(RFID_SPI2_NSS_4, 1);
	HAL_GPIO_WritePin(RFID_SPI2_NSS_5, 1);
	HAL_GPIO_WritePin(RFID_SPI2_NSS_6, 1);
	HAL_GPIO_WritePin(RFID_SPI2_NSS_7, 1);

	// Init Uart
	Print(CLEAR_TERMINAL);
	Print("UART Initialized.\n");

	// Init Buttons
	buttonInit();
	Print("Buttons Initialized.\n");

	// Init LCD
	LCDInit();
	Print("LCD Initialized\n");

	// Setup RFID Readers
	RFIDInit();
	Print("RFID Readers Initialized\n");

	// Setup LEDs
	LEDInit();
	Print("LEDs Initialized\n");

	// Chess Initialization
	chessInit(0);
	Print("Chess Control and AI Initialized.\n");

	// Setup Board State
	blankBoard(curBoard);

	// Start Timer
	HAL_TIM_Base_Start_IT(&TIMER_HANDLE);

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
		while (1)
		{
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
		if (resetFlag) {
			resetFlag = 0;
			blankColors(colors);
			updateColors(colors);

			mainMenu();
			buttonInit();
			boardSetup();
			moveToLCD();
		}

		// Main Loop
		RFIDInit();
		Print("Beginning Scan...\n");
		HAL_GPIO_WritePin(STATUS_LED, 1);
		updateBoard(curBoard);
		HAL_GPIO_WritePin(STATUS_LED, 0);
		Print("Scan Complete.\n");
		Print(CLEAR_TERMINAL);
		printBoard(curBoard);
		chessMain();
		printColors(colors);
		updateColors(colors);
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
  hspi2.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_8;
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
  hspi3.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_2;
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
  * @brief TIM4 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM4_Init(void)
{

  /* USER CODE BEGIN TIM4_Init 0 */

  /* USER CODE END TIM4_Init 0 */

  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};

  /* USER CODE BEGIN TIM4_Init 1 */

  /* USER CODE END TIM4_Init 1 */
  htim4.Instance = TIM4;
  htim4.Init.Prescaler = 10000;
  htim4.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim4.Init.Period = 1000;
  htim4.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  if (HAL_TIM_Base_Init(&htim4) != HAL_OK)
  {
    Error_Handler();
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim4, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim4, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM4_Init 2 */

  /* USER CODE END TIM4_Init 2 */

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
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(RFID_NSS_2_GPIO_Port, RFID_NSS_2_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOC, RFID_NSS_0_Pin|RFID_NSS_1_Pin|RFID_NSS_7_Pin|RFID_NSS_6_Pin 
                          |RFID_NSS_3_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOE, LCD_RS_Pin|LCD_RW_Pin|LCD_EN_Pin, GPIO_PIN_SET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, RFID_ANT_ADDR_0_Pin|RFID_ANT_ADDR_1_Pin|RFID_ANT_ADDR_2_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOD, LED_GREEN_Pin|LED_BLUE_Pin|RFID_NSS_5_Pin|RFID_NSS_4_Pin 
                          |LED_WEN_Pin|LED_ADDR_0_Pin|LED_ADDR_1_Pin|LED_ADDR_2_Pin 
                          |LED_ADDR_3_Pin|LED_ADDR_4_Pin|LED_ADDR_5_Pin|LED_RED_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(STATUS_LED_GPIO_Port, STATUS_LED_Pin, GPIO_PIN_SET);

  /*Configure GPIO pins : BUTTON_1_Pin BUTTON_2_Pin BUTTON_3_Pin BUTTON_4_Pin 
                           BUTTON_5_Pin */
  GPIO_InitStruct.Pin = BUTTON_1_Pin|BUTTON_2_Pin|BUTTON_3_Pin|BUTTON_4_Pin 
                          |BUTTON_5_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);

  /*Configure GPIO pin : RFID_NSS_2_Pin */
  GPIO_InitStruct.Pin = RFID_NSS_2_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(RFID_NSS_2_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : RFID_NSS_0_Pin RFID_NSS_1_Pin RFID_NSS_7_Pin RFID_NSS_6_Pin 
                           RFID_NSS_3_Pin */
  GPIO_InitStruct.Pin = RFID_NSS_0_Pin|RFID_NSS_1_Pin|RFID_NSS_7_Pin|RFID_NSS_6_Pin 
                          |RFID_NSS_3_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pins : LCD_RS_Pin LCD_RW_Pin LCD_EN_Pin */
  GPIO_InitStruct.Pin = LCD_RS_Pin|LCD_RW_Pin|LCD_EN_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);

  /*Configure GPIO pins : RFID_ANT_ADDR_0_Pin RFID_ANT_ADDR_1_Pin RFID_ANT_ADDR_2_Pin STATUS_LED_Pin */
  GPIO_InitStruct.Pin = RFID_ANT_ADDR_0_Pin|RFID_ANT_ADDR_1_Pin|RFID_ANT_ADDR_2_Pin|STATUS_LED_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pins : LED_GREEN_Pin LED_BLUE_Pin RFID_NSS_5_Pin RFID_NSS_4_Pin 
                           LED_WEN_Pin LED_ADDR_0_Pin LED_ADDR_1_Pin LED_ADDR_2_Pin 
                           LED_ADDR_3_Pin LED_ADDR_4_Pin LED_ADDR_5_Pin LED_RED_Pin */
  GPIO_InitStruct.Pin = LED_GREEN_Pin|LED_BLUE_Pin|RFID_NSS_5_Pin|RFID_NSS_4_Pin 
                          |LED_WEN_Pin|LED_ADDR_0_Pin|LED_ADDR_1_Pin|LED_ADDR_2_Pin 
                          |LED_ADDR_3_Pin|LED_ADDR_4_Pin|LED_ADDR_5_Pin|LED_RED_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

}

/* USER CODE BEGIN 4 */
void chessInit(char input) {
    char aiParam = 0;
    switch (input) {
    case White:
        aiParam = LIGHT;
        aiSide = Black;
        break;
    case Black:
        aiParam = DARK;
        aiSide = White;
        break;
    default:
        aiParam = EMPTY;
        aiSide = 0;
        break;
    }
    defaultBoard(curBoard);
    defaultBoard(prevBoard);
    blankColors(colors);
    aiInit(aiParam);
    curSide = White;
    for (int i = 0; i < 17; i++) prevMove[i] = '\0';
}

int chessMain(void) {
	blankColors(colors);

	Print("Side: %d\n", curSide);
	status = gameStatus(prevBoard, curSide);
	if (status == 2) {
      writeLCDMessage("   Stalemate    ", "  It's a draw.  ");
	  for (int j = 0; j < 4; j++) {
	    for (int i = 0; i < 8; i++) {
	      colors[i][j] = COLOR_RED;
	    }
	  }
	  for (int j = 4; j < 8; j++) {
	    for (int i = 0; i < 8; i++) {
	      colors[i][j] = COLOR_RED;
	    }
	  }
	  return status;
	}
	else if (status == 3) {
	  if (curSide == Black) {
		writeLCDMessage("   Checkmate    ", "  White Wins!   ");
	    for (int j = 0; j < 4; j++) {
	      for (int i = 0; i < 8; i++) {
	        colors[i][j] = COLOR_GREEN;
	      }
	    }
	    for (int j = 4; j < 8; j++) {
	      for (int i = 0; i < 8; i++) {
	        colors[i][j] = COLOR_RED;
	      }
	    }
	  }
	  else if (curSide == White) {
		writeLCDMessage("   Checkmate    ", "  Black Wins!   ");
	    for (int j = 0; j < 4; j++) {
	      for (int i = 0; i < 8; i++) {
	        colors[i][j] = COLOR_RED;
	      }
	    }
	    for (int j = 4; j < 8; j++) {
	      for (int i = 0; i < 8; i++) {
	        colors[i][j] = COLOR_GREEN;
	      }
	    }
	  }
		updateColors(colors);
		return status;
	}

    if (curSide == aiSide) { // AI Turn
        printTurn(curSide);
        if (aiMovedFlag) {
        	M diff1;
        	M diff2;
        	M diff3;

        	if (!diffBoards(curBoard, prevBoard, diff2)) {
				curSide = switchSide(curSide);
				aiMovedFlag = 0;
				blankColors(colors);
				//moveToLCD();
				moveStrToLCD(aiMove);
        	}
        	else {
            	diffBoards(prevAIBoard, prevBoard, diff1);
            	diffBoards(curBoard, prevAIBoard, diff3);
        		for (int j = 0; j < 8; j++) {
            		for (int i = 0; i < 8; i++) {
            			if (diff2[i][j] && diff1[i][j] && !diff3[i][j]) colors[i][j] = COLOR_ACCEPTED;
            			else if (diff2[i][j]) colors[i][j] = COLOR_ERROR;
            			else colors[i][j] = COLOR_OFF;
            		}
        		}
        	}
        }
        else {
        	aiMove[0] = '\0';
			aiMakeMove(aiMove);
			//Print("USER SIDE: %d\n", computer_side);
			if (strlen(aiMove) > 0) {
				Print("AI Move: %s\n", aiMove);
				strToMove(aiMove, &curMove);
				copyBoard(prevAIBoard, prevBoard);
				makeMove(prevBoard, curMove);
				if (aiMove[4] != '\0') { // Pawn promote
					if ((aiMove[4] >= 'a') && (aiMove[4] <= 'z')) aiMove[4] += 'A' - 'a';
					prevBoard[curMove.destCol][curMove.destRow].promotion = aiMove[4];
					aiMove[4] = '\0';
				}
				aiMovedFlag = 1;
				moveStrToLCD(aiMove);
			}
			else {
				Print("Error: AI Failed to move.\n");
			}
        }
    }
    else { // Player Turn
        printTurn(curSide);
		parseState(curBoard, prevBoard, curSide, colors, &curMove);
		if (buttonFlag[0] || buttonFlag[1]) {
			if (((buttonFlag[0]) && (curSide == White)) || ((buttonFlag[1]) && (curSide == Black))) {
				if (verifyMove(prevBoard, &curMove)) {
					char promo = '\0';

					makeMove(prevBoard, curMove);
					if (((curMove.destRow == 0) || (curMove.destRow == 7))) { // Pawn Promotion
						if ((prevBoard[curMove.destCol][curMove.destRow].type == 'P') && (prevBoard[curMove.destCol][curMove.destRow].promotion == 0)) {
							promo = pawnPromote();
							prevBoard[curMove.destCol][curMove.destRow].promotion = promo;
						}
					}

					moveToStr(&curMove, aiMove, promo);
					Print("%d\n", aiMove);
					aiParseCommand(aiMove);
					curSide = switchSide(curSide);
					moveStrToLCD(aiMove);
				}
			}

			buttonFlag[0] = 0;
			buttonFlag[1] = 0;
		}
    }

	status = gameStatus(prevBoard, curSide);
    return status;
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef * huart) {
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
        HAL_UART_Receive_IT(&UART_HANDLE, &receivedData, 1);
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
			HAL_UART_Transmit(&UART_HANDLE, (uint8_t*) newlineStr, 2, TIMEOUT);
		}
		else if (s[i] != '\r' && s[i] != '\0') {
			HAL_UART_Transmit(&UART_HANDLE, (uint8_t*) &s[i], 1, TIMEOUT);
		}
	}

	return;
}

void Print(const char* format, ...) {
  va_list args;

  if (DISABLE_PRINT) return;
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

static void writeLCDMessage(char* lcd_upr, char* lcd_low) {
	int size;
	uint8_t x;

    // Fake Function
    Print(CLEAR_TERMINAL);
    Print(lcd_upr);
    Print("\n");
    Print(lcd_low);
    Print("\n");
    //return;

    // Start Real Function
    //writeLCDInstruction(LCDCLR);
    writeLCDInstruction(CURMOV);
    writeLCDInstruction(LINE1);
    HAL_GPIO_WritePin (LCD_RS, GPIO_PIN_SET);

    size = strlen(lcd_upr);
    for (int i = 0; i < 16; i++)
    {
    	if (i >= size) x = ' ';
    	else x = lcd_upr[i];

        HAL_SPI_Transmit (&LCD_SPI_HANDLE, &x, 1, TIMEOUT);
        while(HAL_SPI_GetState(&LCD_SPI_HANDLE) != HAL_SPI_STATE_READY);
        HAL_GPIO_WritePin (LCD_ENABLE, GPIO_PIN_RESET);
        HAL_Delay(1);
        HAL_GPIO_WritePin (LCD_ENABLE, GPIO_PIN_SET);
        HAL_Delay(1);
        HAL_GPIO_WritePin (LCD_ENABLE, GPIO_PIN_RESET);
    }
    writeLCDInstruction(CURMOV);
    writeLCDInstruction(LINE2);
    HAL_GPIO_WritePin (LCD_RS, GPIO_PIN_SET);


    size = strlen(lcd_low);
    for (int i = 0; i < 16; i++)
    {
    	if (i >= size) x = ' ';
    	else x = lcd_low[i];

        HAL_SPI_Transmit (&LCD_SPI_HANDLE, &x, 1, TIMEOUT);
        while(HAL_SPI_GetState(&LCD_SPI_HANDLE) != HAL_SPI_STATE_READY);
        HAL_GPIO_WritePin (LCD_ENABLE, GPIO_PIN_RESET);
        HAL_Delay(1);
        HAL_GPIO_WritePin (LCD_ENABLE, GPIO_PIN_SET);
        HAL_Delay(1);
        HAL_GPIO_WritePin (LCD_ENABLE, GPIO_PIN_RESET);
    }
}

static void writeLCDInstruction(uint8_t instru) {
    HAL_GPIO_WritePin (LCD_RS, GPIO_PIN_RESET);
    HAL_SPI_Transmit (&LCD_SPI_HANDLE, &instru, 1, TIMEOUT);
    while(HAL_SPI_GetState(&LCD_SPI_HANDLE) != HAL_SPI_STATE_READY);
    HAL_GPIO_WritePin (LCD_ENABLE, GPIO_PIN_RESET);
    HAL_Delay(1);
    HAL_GPIO_WritePin (LCD_ENABLE, GPIO_PIN_SET);
    HAL_Delay(1);
    HAL_GPIO_WritePin (LCD_ENABLE, GPIO_PIN_RESET);
}

void LCDInit(void) {
	HAL_GPIO_WritePin (LCD_RS, GPIO_PIN_RESET);
	HAL_GPIO_WritePin (LCD_RW, GPIO_PIN_RESET);
	HAL_GPIO_WritePin (LCD_ENABLE, GPIO_PIN_RESET);
	writeLCDInstruction(LCDON);
	HAL_Delay(4);
	writeLCDInstruction(TWOLINE);
	writeLCDInstruction(LCDCLR);

	writeLCDMessage("Booting...", "Enjoy the lights");
}

void mfrc630_SPI_transfer(uint8_t* tx, uint8_t* rx, uint16_t len){
  switch(HAL_SPI_TransmitReceive(&RFID_SPI_HANDLE, tx, rx, len, TIMEOUT)){
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

void mfrc630_SPI_select(void) {
  // Unselect all pins first
  mfrc630_SPI_unselect();

  // Set reader NSS pin
  if (rfidReaderAddress == 0) {
	HAL_GPIO_WritePin(RFID_SPI2_NSS_0, 0);
  }
  else if (rfidReaderAddress == 1) {
	HAL_GPIO_WritePin(RFID_SPI2_NSS_1, 0);
  }
  else if (rfidReaderAddress == 2) {
	HAL_GPIO_WritePin(RFID_SPI2_NSS_2, 0);
  }
  else if (rfidReaderAddress == 3) {
	HAL_GPIO_WritePin(RFID_SPI2_NSS_3, 0);
  }
  else if (rfidReaderAddress == 4) {
	HAL_GPIO_WritePin(RFID_SPI2_NSS_4, 0);
  }
  else if (rfidReaderAddress == 5) {
	HAL_GPIO_WritePin(RFID_SPI2_NSS_5, 0);
  }
  else if (rfidReaderAddress == 6) {
	HAL_GPIO_WritePin(RFID_SPI2_NSS_6, 0);
  }
  else if (rfidReaderAddress == 7) {
	HAL_GPIO_WritePin(RFID_SPI2_NSS_7, 0);
  }
}

void antennaSelect(void) {
  // Set antenna address
  HAL_GPIO_WritePin(RFID_ANTENNA_ADDRESS_2, (rfidAntennaAddress >> 2) & 1);
  HAL_GPIO_WritePin(RFID_ANTENNA_ADDRESS_1, (rfidAntennaAddress >> 1) & 1);
  HAL_GPIO_WritePin(RFID_ANTENNA_ADDRESS_0, rfidAntennaAddress & 1);
  HAL_Delay(1);
}

void mfrc630_SPI_unselect(void) {
	// Unselect all readers
	HAL_GPIO_WritePin(RFID_SPI2_NSS_0, 1);
	HAL_GPIO_WritePin(RFID_SPI2_NSS_1, 1);
	HAL_GPIO_WritePin(RFID_SPI2_NSS_2, 1);
	HAL_GPIO_WritePin(RFID_SPI2_NSS_3, 1);
	HAL_GPIO_WritePin(RFID_SPI2_NSS_4, 1);
	HAL_GPIO_WritePin(RFID_SPI2_NSS_5, 1);
	HAL_GPIO_WritePin(RFID_SPI2_NSS_6, 1);
	HAL_GPIO_WritePin(RFID_SPI2_NSS_7, 1);
}

void RFIDInit(void) {
  // Antenna Address Default
  rfidAntennaAddress = 0;
  antennaSelect();

  // Set the registers of the MFRC630 into the default.
  for (rfidReaderAddress = 0; rfidReaderAddress < 8; rfidReaderAddress++) {
	  mfrc630_SPI_select();

	  mfrc630_AN1102_recommended_registers(MFRC630_PROTO_ISO14443A_106_MILLER_MANCHESTER);
	  mfrc630_write_reg(0x28, 0x8E);
	  mfrc630_write_reg(0x29, 0x15);
	  mfrc630_write_reg(0x2A, 0x11);
	  mfrc630_write_reg(0x2B, 0x06);

	  mfrc630_SPI_unselect();
	  // Delay slightly
	  HAL_Delay(1);
  }


  return;
}

void buttonInit(void) {
	for (int i = 0; i < 5; i++) {
		buttonFlag[i] = 0;
		curButton[i] = 0;
		prevButton[i] = 0;
	}

	return;
}

void updateLED(int ledAddress, char color) {
	color = ~color;

	// Disable first
	HAL_GPIO_WritePin(LED_ENABLE, 0);

	// Set color
	HAL_GPIO_WritePin(LED_RED, color & 1);
	HAL_GPIO_WritePin(LED_BLUE, (color >> 1) & 1);
	HAL_GPIO_WritePin(LED_GREEN, (color >> 2) & 1);

	// Set address
	HAL_GPIO_WritePin(LED_ADDRESS_0, ledAddress & 1);
	HAL_GPIO_WritePin(LED_ADDRESS_1, (ledAddress >> 1) & 1);
	HAL_GPIO_WritePin(LED_ADDRESS_2, (ledAddress >> 2) & 1);
	HAL_GPIO_WritePin(LED_ADDRESS_3, ((ledAddress >> 3) & 1) ^ 1);
	HAL_GPIO_WritePin(LED_ADDRESS_4, (ledAddress >> 4) & 1);
	HAL_GPIO_WritePin(LED_ADDRESS_5, (ledAddress >> 5) & 1);

	// Clock in
	HAL_GPIO_WritePin(LED_ENABLE, 1);
	HAL_GPIO_WritePin(LED_ENABLE, 0);
}

void LEDInit(void) {
	C colors;

	HAL_Delay(10);
	blankColors(colors);
	updateColors(colors);
	if (LED_DEMO) {
		for (int c = 0; c <= 8; c++) {
			for (int j = 0; j < 8; j++) {
				for (int i = 0; i < 8; i++) {
					colors[i][j] = c;
				}
				updateColors(colors);
			}
			HAL_Delay(500);
		}
		blankColors(colors);
		updateColors(colors);
	}

	return;
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim) {
    if (htim->Instance == TIMER_HANDLE.Instance)
    {
    	curTime += 100;
    	if (curTime >= 10000) curTime = 0;

    	// Read current state
        curButton[0] = HAL_GPIO_ReadPin(BUTTON_1);
        curButton[1] = HAL_GPIO_ReadPin(BUTTON_2);
        curButton[2] = HAL_GPIO_ReadPin(BUTTON_3);
        curButton[3] = HAL_GPIO_ReadPin(BUTTON_4);
        curButton[4] = HAL_GPIO_ReadPin(BUTTON_5);

        // Set flags and previous state
        for (int i = 0; i < 5; i++) {
        	if ((curButton[i] == 1) && (prevButton[i] == 0)) {
        		buttonFlag[i] = 1;
        	}
        	prevButton[i] = curButton[i];
        }

        // Reset Flag - both left and right pushed at the same time
        if (curButton[4] && curButton[2] && (buttonFlag[2] || buttonFlag[4])) {
        	resetFlag = 1;
        }
    }
}

int get_ms(void) {
	// Wrapper function for AI time keeping
	return curTime;
}


int LCDMenu(char ** menu, int size) {
	char* message = menu[0];
	char select[100];
	int button = 0;
	int ptr = 1;

	buttonFlag[2] = 0;
	buttonFlag[3] = 0;
	buttonFlag[4] = 0;

	while (1) {
		strToMenu(menu[ptr], select);

		writeLCDMessage(message, select);
		button = checkButtons();

		if (button == 2) {
			break;
		}
		else if (button == 1) {
			ptr--;
			if (ptr <= 0) ptr = size;
		}
		else if (button == 3) {
			ptr++;
			if (ptr > size) ptr = 1;
		}
		//HAL_Delay(100);
	}

	return ptr;
}

void strToMenu(char* s, char* d) {
	int size = strlen(s);
	int i;

	if (size > 16) {
		return;
	}
	else if (size == 16) {
		strcpy(d, s);
	}
	else if (size == 15) {
		strcpy(d, s);
		d[15] = ' ';
		d[16] = '\0';
	}
	else {
		d[0] = '<';
		for (i = 1; i < ((16 - size) / 2); i++) {
			d[i] = ' ';
		}
		strcpy(&d[i], s);

		for (i = i + size; i < 16; i++) {
			d[i] = ' ';
		}
		d[15] = '>';
		d[16] = '\0';
	}

	return;
}

void mainMenu(void) {
	int players = 1;
	int playerSide = White;

	players = LCDMenu(playerMenu, 2);

	if (players == 2) {
		chessInit(0);
	}
	else {
		playerSide = LCDMenu(sideMenu, 2);
		chessInit(playerSide);
	}

	resetFlag = 0;
	return;
}

int checkButtons(void) {
	if (buttonFlag[3]) { 	  // ENTER
		buttonFlag[2] = 0;
		buttonFlag[3] = 0;
		buttonFlag[4] = 0;
		return 2;
	}
	else if (buttonFlag[2]) { // LEFT
		buttonFlag[2] = 0;
		buttonFlag[3] = 0;
		buttonFlag[4] = 0;
		return 1;
	}
	else if (buttonFlag[4]) { // RIGHT
		buttonFlag[2] = 0;
		buttonFlag[3] = 0;
		buttonFlag[4] = 0;
		return 3;
	}

	return 0;
}


void moveStrToLCD(char* s) {
	if (aiMovedFlag) {
		strcpy(prevMove, "AI's Move: ");
	}
	else {
		strcpy(prevMove, "Last Move: ");
	}
	prevMove[11] = s[0] + 'A' - 'a';
	prevMove[12] = s[1];
	prevMove[13] = '-';
	prevMove[14] = s[2] + 'A' - 'a';
	prevMove[15] = s[3];
	prevMove[16] = '\0';

	moveToLCD();
}

void moveToLCD(void) {
	switch(curSide) {
	case White:
		writeLCDMessage("  White's Turn  ", prevMove);
		break;
	case Black:
		writeLCDMessage("  Black's Turn  ", prevMove);
		break;
	default:
		writeLCDMessage("Error", "No Side Set");
		break;
	}
	return;
}

char pawnPromote(void) {
	char type;

	type = LCDMenu(pawnPromoteMenu, 4);
	switch(type) {
	case 1:
		type = 'Q';
		break;
	case 2:
		type = 'N';
		break;
	case 3:
		type = 'R';
		break;
	case 4:
		type = 'B';
		break;
	default:
		type = 'Q';
		break;
	}

	return type;
}

void boardSetup(void) {
	B blank;
	B setup;
	char missing;
	M diff;
	M diffMissing;

	if (SKIP_SETUP_HELP) return; // Global override

	buttonFlag[3] = 0;
	blankBoard(blank);
	defaultBoard(setup);
	blankColors(colors);
	while (1) {
		// Scan
		RFIDInit();
		updateBoard(curBoard);
		diffBoards(curBoard, setup, diff);
		diffBoards(curBoard, blank, diffMissing);
		updateColors(colors);
		printBoard(curBoard);

		// Largest Missing Piece
		missing = 0;
		for (int j = 0; j < 8; j++) {
			for (int i = 0; i < 8; i++) {
				if (diff[j][i]) {
					if ((setup[j][i].type == 'K') || (missing == 'K')) {
						missing = 'K';
					}
					else if ((setup[j][i].type == 'Q') || (missing == 'Q')) {
						missing = 'Q';
					}
					else if ((setup[j][i].type == 'B') || (missing == 'B')) {
						missing = 'B';
					}
					else if ((setup[j][i].type == 'N') || (missing == 'N')) {
						missing = 'N';
					}
					else if ((setup[j][i].type == 'R') || (missing == 'R')) {
						missing = 'R';
					}
					else if ((setup[j][i].type == 'P') || (missing == 'P')) {
						missing = 'P';
					}
				}
			}
		}
		if (!missing) break;

		// LCD Message
		switch(missing) {
		case 'K':
			writeLCDMessage("< White  Black >", "  Place Kings   ");
			break;
		case 'Q':
			writeLCDMessage("< White  Black >", "  Place Queens  ");
			break;
		case 'B':
			writeLCDMessage("< White  Black >", " Place Bishops  ");
			break;
		case 'N':
			writeLCDMessage("< White  Black >", " Place Knights  ");
			break;
		case 'R':
			writeLCDMessage("< White  Black >", "  Place Rooks   ");
			break;
		case 'P':
			writeLCDMessage("< White  Black >", "  Place Pawns   ");
			break;
		default:
			break;
		}

		// Board Colors
		blankColors(colors);
		for (int j = 0; j < 8; j++) {
			for (int i = 0; i < 8; i++) {
				if (diff[j][i] && diffMissing[j][i]) {
					colors[j][i] = COLOR_ERROR;
				}
				else if (diff[j][i] && setup[j][i].type == missing) {
					colors[j][i] = COLOR_ACCEPTED;
				}
			}
		}
	}

	blankColors(colors);
	updateColors(colors);
	writeLCDInstruction(LCDCLR);
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
	Print("ERROR HANDLER CALLED!\nSomething went very wrong.\n");
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
