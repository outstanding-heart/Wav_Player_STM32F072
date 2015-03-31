/**
  ******************************************************************************
  * @file    STM32F0xx_IAP/inc/main.h 
  * @author  MCD Application Team
  * @version V1.0.0
  * @date    17-March-2015
  * @brief   Header for main.c module
  ******************************************************************************
  * @attention
  */
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

/* Includes ------------------------------------------------------------------*/
#include "stm32f0xx.h"
#include "stm320518_eval.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Private define ------------------------------------------------------------*/
//#define RECEIVE_BUFF_LEN			1024
#define SerialPutString(x)   Serial_PutString((uint8_t*)(x))
#define NumStrMax				(100)


/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */

void SerialPutChar(uint8_t c);
void Serial_PutString(uint8_t *s);
uint32_t SerialKeyPressed(uint8_t *key);

void USART1_Init(void);
void DAC1_Init(void);

void Flash_Init(void);
void Flash_Erase(void);
void Flash_Write(void);
void Flash_Read(void);
void Flash_Write_String(uint8_t *s);
void Flash_Write_Char(uint8_t c);
void Flash_Read_Choose(uint32_t StartAddr, uint32_t Num, uint32_t BitNum);
uint16_t Flash_Read_Wav_Data(uint32_t StartAddr, uint32_t BitNum);





#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/

