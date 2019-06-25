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
#include <string.h>

#include "ai.h"
#include "pieces.h"
#include "drivers.h"
#include "chess.h"
#include "debug.h"
#include "defs.h"
#include "protos.h"
#include "data.h"

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
UART_HandleTypeDef huart2;

/* USER CODE BEGIN PV */
char receiveBuffer[100];
char transmitBuffer[100];
char s[100];

char * newlineStr = NEWLINE_STR;
char * backSpace = BACKSPACE_STR;

C colors;
B curBoard;
B prevBoard;
M curMoves;
Move curMove;
Piece tempPiece;
int check = 0;
int status = 0;
int curSide = White;
int aiSide = 0;

/* Used to store data received from the UART */
uint8_t receivedData = 0;

/* Current Location in receiveBuffer */
int currentLocation = 0;

/* Flag signaling completed reception of line of text */
int dataReceivedFlag = 0;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_USART2_UART_Init(void);
/* USER CODE BEGIN PFP */
//static void write_LCD_msg(char lcd_upr[], char lcd_low[]);
//static void write_LCD_instr(uint8_t * instru);
void HAL_UART_RxCpltCallback(UART_HandleTypeDef * huart);

int chessMain(void);
void chessInit(char aiSide);
char * receiveString(void);
void transmitString(char * );
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
 * @brief  The application entry point.
 * @retval int
 */
int main(void) {
    /* USER CODE BEGIN 1 */
    int status;
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
    /* USER CODE BEGIN 2 */
    char send_xboard_msg[16];

    chessInit(Black);

    Print(CLEAR_TERMINAL);
    Print("\nWelcome to my half-baked chess simulator.\nType \"help\" for options!\n");
    Print("\n");
    printBoard(curBoard);

    /* USER CODE END 2 */

    /* Infinite loop */
    /* USER CODE BEGIN WHILE */
    while (1) {
        status = chessMain();
    }
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */

    /* USER CODE END 3 */
}

/**
 * @brief System Clock Configuration
 * @retval None
 */
void SystemClock_Config(void) {
    RCC_OscInitTypeDef RCC_OscInitStruct = {
        0
    };
    RCC_ClkInitTypeDef RCC_ClkInitStruct = {
        0
    };

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
    if (HAL_RCC_OscConfig( & RCC_OscInitStruct) != HAL_OK) {
        Error_Handler();
    }
    /**Initializes the CPU, AHB and APB busses clocks
     */
    RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK |
                                  RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
    RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
    RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
    RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
    RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

    if (HAL_RCC_ClockConfig( & RCC_ClkInitStruct, FLASH_LATENCY_3) != HAL_OK) {
        Error_Handler();
    }
}

/**
 * @brief USART2 Initialization Function
 * @param None
 * @retval None
 */
static void MX_USART2_UART_Init(void) {

    /* USER CODE BEGIN USART2_Init 0 */

    /* USER CODE END USART2_Init 0 */

    /* USER CODE BEGIN USART2_Init 1 */

    /* USER CODE END USART2_Init 1 */
    huart2.Instance = USART2;
    huart2.Init.BaudRate = 38400;
    huart2.Init.WordLength = UART_WORDLENGTH_8B;
    huart2.Init.StopBits = UART_STOPBITS_1;
    huart2.Init.Parity = UART_PARITY_NONE;
    huart2.Init.Mode = UART_MODE_TX_RX;
    huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
    huart2.Init.OverSampling = UART_OVERSAMPLING_16;
    if (HAL_UART_Init( & huart2) != HAL_OK) {
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
static void MX_GPIO_Init(void) {
    GPIO_InitTypeDef GPIO_InitStruct = {
        0
    };

    /* GPIO Ports Clock Enable */
    __HAL_RCC_GPIOC_CLK_ENABLE();
    __HAL_RCC_GPIOH_CLK_ENABLE();
    __HAL_RCC_GPIOA_CLK_ENABLE();
    __HAL_RCC_GPIOB_CLK_ENABLE();

    /*Configure GPIO pin Output Level */
    HAL_GPIO_WritePin(LD2_GPIO_Port, LD2_Pin, GPIO_PIN_RESET);

    /*Configure GPIO pin : B1_Pin */
    GPIO_InitStruct.Pin = B1_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(B1_GPIO_Port, & GPIO_InitStruct);

    /*Configure GPIO pin : LD2_Pin */
    GPIO_InitStruct.Pin = LD2_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(LD2_GPIO_Port, & GPIO_InitStruct);

}

/* USER CODE BEGIN 4 */
void chessInit(char aiSide) {
    char aiParam = 0;
    switch (aiSide) {
    case White:
        aiParam = DARK;
        break;
    case Black:
        aiParam = LIGHT;
        break;
    default:
        aiParam = EMPTY;
        break;
    }
    defaultBoard(curBoard);
    defaultBoard(prevBoard);
    blankColors(colors);
    aiInit(aiParam);

    aiSide = Black;
    curSide = White;
}

int chessMain(void) {
    if (curSide == aiSide) { // AI Turn
        s[0] = '\0';
        aiMakeMove(s);
        if (strlen(s) > 0) {
            Print("AI Move: %s\n", s);
            strToMove(s, & curMove);
            makeMove(curBoard, curMove);
            copyBoard(prevBoard, curBoard);
            printBoard(curBoard);

            switch (curSide) {
            case White:
                curSide = Black;
                break;
            case Black:
                curSide = White;
                break;
            }
        }
        else {
            Print("Error: AI Failed to move.\n");
        }
    }
    else { // Player Turn
        printTurn(curSide);
        status = gameStatus(curBoard, curSide);
        Print("Game Status: %d\n", status);
        Print(">");
        Scan(s);
        if (strcmp(s, "exit") == 0) {
            Print("Exiting...\n");
            return 10;
        }
        else if (strcmp(s, "help") == 0) {
            Print("help: This menu.\n");
            Print("b2c2: Movement example.\n");
            Print("d4: Lift piece example (replaces in same spot afterwards).\n");
            Print("ai <command>: Sends the command specified to the ai.\n");
            Print("dela1: Delete piece example.\n");
            Print("pute5: Replace last deleted piece example.\n");
            Print("skip: Ends current turn.\n");
            Print("force: Ends current turn and accepts board state.\n");
            Print("reset: Put the board back to the last accepted state.\n");
            Print("newgame: Start a new game.\n");
            Print("exit: Leave the simulator.\n");
        }
        else if (strcmp(s, "reset") == 0) {
            Print("Reset board to last state.\n");
            copyBoard(curBoard, prevBoard);
        }
        else if ((s[0] == 'a') && (s[1] == 'i') && (s[2] == ' ')) {
            aiParseCommand(s + 3);
        }
        else if (strcmp(s, "force") == 0) {
            Print("Forced the board to accept current state.\n");
            copyBoard(prevBoard, curBoard);
            check = 0;
            switch (curSide) {
            case White:
                curSide = Black;
                break;
            case Black:
                curSide = White;
                break;
            }

            if ((status = gameStatus(curBoard, curSide)) > 1) {
                return status;
            }
        }
        else if (strcmp(s, "skip") == 0) {
            Print("Skipping current turn.\n");
            check = 0;
            switch (curSide) {
            case White:
                curSide = Black;
                break;
            case Black:
                curSide = White;
                break;
            }

            if ((status = gameStatus(curBoard, curSide)) > 1) {
                return status;
            }
        }
        else if (strcmp(s, "newgame") == 0) {
            check = 0;
            status = 0;
            curSide = White;

            defaultBoard(curBoard);
            defaultBoard(prevBoard);
            blankColors(colors);

            Print("New Game Started.\n");
        }
        else if ((strlen(s) == 5) && (s[0] == 'd') && (s[1] == 'e') && (s[2] == 'l')) {
            // Delete a piece
            int x, y;
            int flag = 0;

            if ((x = charToCoord(s[3])) == -1) flag = 1;
            if ((y = charToCoord(s[4])) == -1) flag = 1;
            if (flag) {
                Print("Error: Move could not be parsed.\n");
            }
            else {
                tempPiece.type = curBoard[x][y].type;
                tempPiece.side = curBoard[x][y].side;
                tempPiece.promotion = curBoard[x][y].promotion;
                tempPiece.unmoved = 0;

                curBoard[x][y].type = 0;
                curBoard[x][y].side = 0;
                check = 1;
            }
        }
        else if ((strlen(s) == 5) && (s[0] == 'p') && (s[1] == 'u') && (s[2] == 't')) {
            // Delete a piece
            int x, y;
            int flag = 0;

            if ((x = charToCoord(s[3])) == -1) flag = 1;
            if ((y = charToCoord(s[4])) == -1) flag = 1;
            if (flag) {
                Print("Error: Move could not be parsed.\n");
            }
            else if (tempPiece.side == 0) {
                Print("Error: No piece to replace.\n");
            }
            else {
                curBoard[x][y].type = tempPiece.type;
                curBoard[x][y].side = tempPiece.side;
                curBoard[x][y].promotion = tempPiece.promotion;
                curBoard[x][y].unmoved = 0;
                tempPiece.side = 0;

                check = 1;
            }
        }
        else if (strlen(s) == 2) {
            // Lift a piece to view colors
            int x, y;
            int flag = 0;

            if ((x = charToCoord(s[0])) == -1) flag = 1;
            if ((y = charToCoord(s[1])) == -1) flag = 1;
            if (flag) {
                Print("Error: Move could not be parsed.\n");
            }
            else {
                // Lift Piece
                tempPiece.type = curBoard[x][y].type;
                tempPiece.side = curBoard[x][y].side;
                curBoard[x][y].type = 0;
                curBoard[x][y].side = 0;

                // Display Status
                check = parseState(curBoard, prevBoard, curSide, colors, & curMove);
                printColors(colors);

                // Replace Piece
                curBoard[x][y].type = tempPiece.type;
                curBoard[x][y].side = tempPiece.side;

                // Display Moves
                if (curSide == curBoard[x][y].side) {
                    validMoves(curBoard, curMoves, y, x);
                    //printMoves(curBoard, curMobes);
                }
                check = 0;
            }
        }
        else if (strlen(s) == 4) {
            // Move a piece
            int x, y, xx, yy;
            int flag = 0;
            if ((x = charToCoord(s[0])) == -1) flag = 1;
            if ((y = charToCoord(s[1])) == -1) flag = 1;
            if ((xx = charToCoord(s[2])) == -1) flag = 1;
            if ((yy = charToCoord(s[3])) == -1) flag = 1;

            s[0] = x + 'a';
            s[1] = y + '1';
            s[2] = xx + 'a';
            s[3] = yy + '1';
            s[4] = '\0';

            if (flag) {
                Print("Error: Move could not be parsed.\n");
            }
            else {
                movePiece(curBoard, y, x, yy, xx, 0);
                aiParseCommand(s);
                check = 1;
            }
        }
        else {
            Print("Error: Could not parse command.\n");
        }

        if (check) {
            check = parseState(curBoard, prevBoard, curSide, colors, & curMove);
            if (check == 1) {
                copyBoard(prevBoard, curBoard);
                switch (curSide) {
                case White:
                    curSide = Black;
                    break;
                case Black:
                    curSide = White;
                    break;
                }

                Print("Move Accepted.\n");
                Print("Move: %c%c-%c%c\n", curMove.sourceCol + 'A', curMove.sourceRow + '1', curMove.destCol + 'A', curMove.destRow + '1');
                printColors(colors);
                printBoard(curBoard);
                if ((status = gameStatus(curBoard, curSide)) > 1) {
                    return status;
                }
            }
            else {
                Print("Board State Invalid.\n");
                printColors(colors);
                printBoard(curBoard);
                Print("Use \"reset\" to go back.\n");
            }
            check = 0;
        }
        else {
            Print("\n");
            printBoard(curBoard);
        }
    }
    return 0;
}

/*
static void write_LCD_msg(char lcd_upr[], char lcd_low[])
{
    uint8_t loc_instru = CURMOV;
    write_LCD_instr(&loc_instru);
    loc_instru = LINE1;
    write_LCD_instr(&loc_instru);
    HAL_GPIO_WritePin (GPIOC, rs_Pin, GPIO_PIN_SET);

    uint8_t x = lcd_upr[0];
    int count = 0;
    while(x != '\0')
    {
        HAL_SPI_Transmit (&hspi3, (uint8_t) &lcd_upr[count], 1, TIMEOUT);
        while(HAL_SPI_GetState(&hspi3) != HAL_SPI_STATE_READY)
            ;
        HAL_GPIO_WritePin (GPIOC, lcd_en_Pin, GPIO_PIN_SET);
        HAL_Delay(1);
        HAL_GPIO_WritePin (GPIOC, lcd_en_Pin, GPIO_PIN_RESET);
        count++;
        x = lcd_upr[count];
    }
    loc_instru = CURMOV;
    write_LCD_instr(&loc_instru);
    loc_instru = LINE2;
    write_LCD_instr(&loc_instru);
    HAL_GPIO_WritePin (GPIOC, rs_Pin, GPIO_PIN_SET);

    x = lcd_low[0];
    count = 0;
    while(x != '\0')
    {
        HAL_SPI_Transmit (&hspi3, (uint8_t) &lcd_upr[count], 1, TIMEOUT);
        while(HAL_SPI_GetState(&hspi3) != HAL_SPI_STATE_READY)
            ;
        HAL_GPIO_WritePin (GPIOC, lcd_en_Pin, GPIO_PIN_RESET);
        HAL_GPIO_WritePin (GPIOC, lcd_en_Pin, GPIO_PIN_SET);
        HAL_Delay(1);
        HAL_GPIO_WritePin (GPIOC, lcd_en_Pin, GPIO_PIN_RESET);
        count++;
        x = lcd_low[count];
    }
}

static void write_LCD_instr(uint8_t * instru)
{
    HAL_GPIO_WritePin (GPIOC, rs_Pin, GPIO_PIN_RESET);
    HAL_SPI_Transmit (&hspi3, instru, 1, TIMEOUT);
    while(HAL_SPI_GetState(&hspi3) != HAL_SPI_STATE_READY)
        ;
    HAL_GPIO_WritePin (GPIOC, lcd_en_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin (GPIOC, lcd_en_Pin, GPIO_PIN_SET);
    HAL_Delay(1);
    HAL_GPIO_WritePin (GPIOC, lcd_en_Pin, GPIO_PIN_RESET);
}
*/

void HAL_UART_RxCpltCallback(UART_HandleTypeDef * huart) {
    /* Move data into buffer */
    receiveBuffer[currentLocation] = receivedData;

    /* Variable to keep track of location in buffer */
    if (((char) receiveBuffer[currentLocation] == '\n') || ((char) receiveBuffer[currentLocation] == '\r')) {
        HAL_UART_Transmit( & huart2, (uint8_t * ) newlineStr, 2, TIMEOUT);
        dataReceivedFlag = 1;
        receiveBuffer[currentLocation] = '\0';
        currentLocation = 0;
    }
    else if (((char) receiveBuffer[currentLocation] == 0x08) || ((char) receiveBuffer[currentLocation] == 0x7F)) {
        if (currentLocation > 0) {
            Print(backSpace);
            receiveBuffer[currentLocation] = '\0';
            currentLocation--;
        }
    }
    else {
        HAL_UART_Transmit( & huart2, & receivedData, 1, TIMEOUT);
        currentLocation++;
    }
}

char * receiveString(void) {
    /* Listen for input; print back to screen when fully received */
    while (!dataReceivedFlag) {
        HAL_UART_Receive_IT( & huart2, & receivedData, 1);
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
            HAL_UART_Transmit( & huart2, (uint8_t * ) newlineStr, 2, TIMEOUT);
        }
        else if (s[i] != '\r' && s[i] != '\0') {
            HAL_UART_Transmit( & huart2, (uint8_t * ) & s[i], 1, TIMEOUT);
        }
    }
    //HAL_UART_Transmit_IT(&huart2, (uint8_t *) s, size);

    return;
}

void Print(const char * format, ...) {
    va_list args;
    va_start(args, format);
    vsprintf(transmitBuffer, format, args);
    transmitString(transmitBuffer);
    va_end(args);

    return;
}

void Scan(char * s) {
    receiveString();
    strcpy(s, receiveBuffer);

    return;
}
/* move_str returns a string with move m in coordinate notation */

/* USER CODE END 4 */

/**
 * @brief  This function is executed in case of error occurrence.
 * @retval None
 */
void Error_Handler(void) {
    /* USER CODE BEGIN Error_Handler_Debug */
    /* User can add his own implementation to report the HAL error return state */

    /* USER CODE END Error_Handler_Debug */
}

# ifdef USE_FULL_ASSERT
/**
 * @brief  Reports the name of the source file and the source line number
 *         where the assert_param error has occurred.
 * @param  file: pointer to the source file name
 * @param  line: assert_param error line source number
 * @retval None
 */
void assert_failed(uint8_t * file, uint32_t line) {
    /* USER CODE BEGIN 6 */
    /* User can add his own implementation to report the file name and line number,
       tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
    /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
