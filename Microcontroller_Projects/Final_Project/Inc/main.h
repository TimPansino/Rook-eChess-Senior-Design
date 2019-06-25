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
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define BUTTON_1_Pin GPIO_PIN_2
#define BUTTON_1_GPIO_Port GPIOE
#define BUTTON_2_Pin GPIO_PIN_3
#define BUTTON_2_GPIO_Port GPIOE
#define BUTTON_3_Pin GPIO_PIN_4
#define BUTTON_3_GPIO_Port GPIOE
#define BUTTON_4_Pin GPIO_PIN_5
#define BUTTON_4_GPIO_Port GPIOE
#define BUTTON_5_Pin GPIO_PIN_6
#define BUTTON_5_GPIO_Port GPIOE
#define RFID_NSS_2_Pin GPIO_PIN_5
#define RFID_NSS_2_GPIO_Port GPIOA
#define RFID_NSS_0_Pin GPIO_PIN_4
#define RFID_NSS_0_GPIO_Port GPIOC
#define RFID_NSS_1_Pin GPIO_PIN_5
#define RFID_NSS_1_GPIO_Port GPIOC
#define LCD_RS_Pin GPIO_PIN_7
#define LCD_RS_GPIO_Port GPIOE
#define LCD_RW_Pin GPIO_PIN_8
#define LCD_RW_GPIO_Port GPIOE
#define LCD_EN_Pin GPIO_PIN_9
#define LCD_EN_GPIO_Port GPIOE
#define RFID_ANT_ADDR_0_Pin GPIO_PIN_13
#define RFID_ANT_ADDR_0_GPIO_Port GPIOB
#define RFID_ANT_ADDR_1_Pin GPIO_PIN_14
#define RFID_ANT_ADDR_1_GPIO_Port GPIOB
#define RFID_ANT_ADDR_2_Pin GPIO_PIN_15
#define RFID_ANT_ADDR_2_GPIO_Port GPIOB
#define LED_GREEN_Pin GPIO_PIN_8
#define LED_GREEN_GPIO_Port GPIOD
#define LED_BLUE_Pin GPIO_PIN_9
#define LED_BLUE_GPIO_Port GPIOD
#define RFID_NSS_5_Pin GPIO_PIN_12
#define RFID_NSS_5_GPIO_Port GPIOD
#define RFID_NSS_4_Pin GPIO_PIN_14
#define RFID_NSS_4_GPIO_Port GPIOD
#define RFID_NSS_7_Pin GPIO_PIN_6
#define RFID_NSS_7_GPIO_Port GPIOC
#define RFID_NSS_6_Pin GPIO_PIN_8
#define RFID_NSS_6_GPIO_Port GPIOC
#define RFID_NSS_3_Pin GPIO_PIN_10
#define RFID_NSS_3_GPIO_Port GPIOC
#define LED_WEN_Pin GPIO_PIN_0
#define LED_WEN_GPIO_Port GPIOD
#define LED_ADDR_0_Pin GPIO_PIN_1
#define LED_ADDR_0_GPIO_Port GPIOD
#define LED_ADDR_1_Pin GPIO_PIN_2
#define LED_ADDR_1_GPIO_Port GPIOD
#define LED_ADDR_2_Pin GPIO_PIN_3
#define LED_ADDR_2_GPIO_Port GPIOD
#define LED_ADDR_3_Pin GPIO_PIN_4
#define LED_ADDR_3_GPIO_Port GPIOD
#define LED_ADDR_4_Pin GPIO_PIN_5
#define LED_ADDR_4_GPIO_Port GPIOD
#define LED_ADDR_5_Pin GPIO_PIN_6
#define LED_ADDR_5_GPIO_Port GPIOD
#define LED_RED_Pin GPIO_PIN_7
#define LED_RED_GPIO_Port GPIOD
#define STATUS_LED_Pin GPIO_PIN_8
#define STATUS_LED_GPIO_Port GPIOB
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
