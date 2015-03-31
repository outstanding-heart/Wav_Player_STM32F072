/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "wav.h" 

/** @addtogroup STM32F0xx_StdPeriph_Examples
  * @{
  */

/** @addtogroup FLASH_Program
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
typedef enum {FAILED = 0, PASSED = !FAILED} TestStatus;
/* Private define ------------------------------------------------------------*/
#ifdef STM32F072
 #define FLASH_PAGE_SIZE         ((uint32_t)0x00000400)   /* FLASH Page Size */
 #define FLASH_USER_START_ADDR   ((uint32_t)0x08009000)   /* Start @ of user Flash area */
 #define FLASH_USER_END_ADDR     ((uint32_t)0x0801FFFF)   /* End @ of user Flash area */
#else
 #define FLASH_PAGE_SIZE         ((uint32_t)0x00000400)   /* FLASH Page Size */
 #define FLASH_USER_START_ADDR   ((uint32_t)0x08009000)   /* Start @ of user Flash area */
 #define FLASH_USER_END_ADDR     ((uint32_t)0x0801FFFF)   /* End @ of user Flash area */
#endif /* STM32F072 */
#define DATA_32                 ((uint32_t)0x12345678)

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
uint32_t EraseCounter = 0x00, Address = 0x00, NowAddress = 0x00;
uint32_t Data = 0x3210ABCD;
uint32_t NbrOfPage = 0x00;
uint8_t string[20], string1[20];

__IO FLASH_Status FLASHStatus = FLASH_COMPLETE;
__IO TestStatus MemoryProgramStatus = PASSED;


/* Init Flash */
void Flash_Init(void)
{
	/* Unlock the Program memory */
	FLASH_Unlock();

	/* Clear all FLASH flags */  
	FLASH_ClearFlag(FLASH_FLAG_EOP|FLASH_FLAG_WRPERR | FLASH_FLAG_PGERR | FLASH_FLAG_BSY);   
	
	/* Define the number of page to be erased */
	NbrOfPage = (FLASH_USER_END_ADDR - FLASH_USER_START_ADDR) / FLASH_PAGE_SIZE;
	
	SerialPutString("Init OK ");
}

/* Erase Flash */

void Flash_Erase(void)
{
	for(EraseCounter = 0; (EraseCounter < NbrOfPage) && (FLASHStatus == FLASH_COMPLETE); EraseCounter++)
	{
		if (FLASH_ErasePage(FLASH_USER_START_ADDR + (FLASH_PAGE_SIZE * EraseCounter))!= FLASH_COMPLETE)
		{
			/* Error occurred while sector erase. 
			User can add here some code to deal with this error  */
			while (1)
			{
			}
		}
	}
	SerialPutString("Erase OK ");
}

/* Write Flash */
/* Program the user Flash area word by word
    (area defined by FLASH_USER_START_ADDR and FLASH_USER_END_ADDR) ***********/

void Flash_Write(void)
{
	
	Address = FLASH_USER_START_ADDR;

	while (Address < FLASH_USER_END_ADDR)
	{
		if (FLASH_ProgramWord(Address, Data) == FLASH_COMPLETE)
		{
			Address = Address + 4;
			//count = Address + '0';
			//sprintf(string, "%d ", Address);
			//SerialPutString(string);
		}
		else
		{ 
			/* Error occurred while writing data in Flash memory. 
			 User can add here some code to deal with this error */
			SerialPutString("Write ERROR ");
			while (1)
			{
			}
		}
	}
	
	SerialPutString("~~Write END~~");
	FLASH_Lock(); 
}

/* Read Flash */
/* Check if the programmed data is OK 
      MemoryProgramStatus = 0: data programmed correctly
      MemoryProgramStatus != 0: number of words not programmed correctly ******/

void Flash_Read(void)
{
	char String[NumStrMax];
	Address = FLASH_USER_START_ADDR;
	MemoryProgramStatus = PASSED;
	
	while (Address < FLASH_USER_END_ADDR)
	{
		Data = *(__IO uint8_t *)Address;
		//sprintf(string, "%d:", Address);
		sprintf(String, "~~%d~~", Data);
		//SerialPutString(string);
		SerialPutString(String);

//		if (Data != DATA_32)
//		{
//			MemoryProgramStatus = FAILED; 
//			SerialPutString("Read ERROR ");			
//		}
//		else
//		{
//			//SerialPutString(string);
//			SerialPutString("Read OK ");
//		}

		Address = Address + 1;
	}
	SerialPutString("~~Read END~~ ");

	/* Infinite loop */
	//while (1)
	//{
	//}

}

/* Read the datas from Flash that the address is from StartAddr to StartAddr+Num and write in the usart1 */
// StartAdder: ��ʼ��ַ
// Num: ��ַ����һ������BitNum
// BitNum: �ֽ�λ��


void Flash_Read_Choose(uint32_t StartAddr, uint32_t Num, uint32_t BitNum)
{
	uint32_t address, EndAddr, data;
//	char String[NumStrMax];
	
	StartAddr = StartAddr + FLASH_USER_START_ADDR; 		//��ʼ��ַ=��ʼλ+���ݶο�ʼ��ַ
	EndAddr = StartAddr + Num;
	address = StartAddr;
	MemoryProgramStatus = PASSED;
	
	while (address < EndAddr)
	{
		if (BitNum == 4)								//λ��Ϊ32
		{
			data = *(__IO uint32_t *)address;
		}
		else if (BitNum == 2)							//λ��Ϊ16
		{
			data = *(__IO uint16_t *)address;
		}
		else if (BitNum == 1)							//λ��Ϊ8
		{
			data = *(__IO uint8_t *)address;			
		}
		else
		{
			SerialPutString("BitNum error!");
			while(1)
			{}
		}
		//if()
		//sprintf(String, "~~%d~~", data);
		//SerialPutString(String);

		address = address + BitNum;
	}
	SerialPutString("~~Read END~~ ");

}

/* Read the datas from Flash that the address is from StartAddr to StartAddr+Num and write in the usart1 */
// StartAdder: ��ʼ��ַ
// Num: ��ַ����һ������BitNum
// BitNum: �ֽ�λ��
// data: ����

uint32_t Flash_Read_Choose_Wav_Num(uint32_t StartAddr, uint32_t Num, uint32_t BitNum)
{
	uint32_t address, EndAddr, data;//, count=0;
//	char String[NumStrMax];
	
	StartAddr = StartAddr + FLASH_USER_START_ADDR; 		//��ʼ��ַ=��ʼλ+���ݶο�ʼ��ַ
	EndAddr = StartAddr + Num;
	address = StartAddr;
	MemoryProgramStatus = PASSED;
	
	while (address < EndAddr)
	{
		if (BitNum == 4)								//λ��Ϊ32
		{
			data = *(__IO uint32_t *)address;
		}
		else if (BitNum == 2)							//λ��Ϊ16
		{
			data = *(__IO uint16_t *)address;
		}
		else if (BitNum == 1)							//λ��Ϊ8
		{
			data = *(__IO uint8_t *)address;			
		}
		else
		{
			SerialPutString("BitNum error!");
			while(1)
			{}
		}
		
		//SerialPutString("~~Read END~~\n");
		//sprintf(String, "~~%d~~", data);
		//SerialPutString(String);

		address = address + BitNum;
	}
	//sprintf(String, "~~%d~~", data);
	//SerialPutString(String);
	return data;
}

/* Read the datas from Flash that the address is from StartAddr to StartAddr+Num and write in the usart1 */
// StartAdder: ��ʼ��ַ
// Num: ��ַ����һ������BitNum
// BitNum: �ֽ�λ��
// 

void Flash_Read_Choose_Wav_Info(uint8_t *Info, uint32_t StartAddr, uint32_t Num, uint32_t BitNum)
{
	uint32_t address, EndAddr, data, count=0;
	//char String[NumStrMax];
	 		
	StartAddr = StartAddr + FLASH_USER_START_ADDR; 		//��ʼ��ַ=��ʼλ+���ݶο�ʼ��ַ
	EndAddr = StartAddr + Num;
	address = StartAddr;
	MemoryProgramStatus = PASSED;
	
	while (address < EndAddr)
	{
		if (BitNum == 4)								//λ��Ϊ32
		{
			data = *(__IO uint32_t *)address;
		}
		else if (BitNum == 2)							//λ��Ϊ16
		{
			data = *(__IO uint16_t *)address;
		}
		else if (BitNum == 1)							//λ��Ϊ8
		{
			data = *(__IO uint8_t *)address;			
		}
		else
		{
			SerialPutString("BitNum error!");
			while(1)
			{}
		}
		Info[count] = data;
		count++;
		//sprintf(String, "~~%d~~", data);
		//SerialPutString(String);

		address = address + BitNum;
	}
	//SerialPutString("~~Read END~~ \n");
	//SerialPutString(Info);
}

uint16_t Flash_Read_Wav_Data(uint32_t StartAddr, uint32_t BitNum)
{
	uint32_t address, data;
//	char String[NumStrMax];
	
		 		
	address = StartAddr + FLASH_USER_START_ADDR; 		//��ʼ��ַ=��ʼλ+���ݶο�ʼ��ַ
	MemoryProgramStatus = PASSED;

	//if (BitNum == 4)								//λ��Ϊ32
	//{
	//	data = *(__IO uint32_t *)address;
	//}
	if (BitNum == 2)								//λ��Ϊ16
	{
		data = *(__IO uint16_t *)address;
	}
	else if (BitNum == 1)							//λ��Ϊ8
	{
		data = *(__IO uint8_t *)address;			
	}
	else
	{
		SerialPutString("BitNum error!");
		while(1)
		{}
	}
	return data;

	//sprintf(String, "~~%d~~", data);
	//SerialPutString(String);
	//SerialPutString("~~Read END~~ ");
}

/* Write into the flash from usart1 */
	
void Flash_Write_Char(uint8_t c)
{ 
	
	if (FLASH_ProgramWord(Address, c) == FLASH_COMPLETE)
	{
		NowAddress = NowAddress + 4;
	}
  
}

/**
  * @brief  Write a string on the HyperTerminal in Flash
  * @param  s: The string to be Writed
  * @retval None
  */
void Flash_Write_String(uint8_t *s)
{
	NowAddress = FLASH_USER_START_ADDR;
	while (*s != '\0')
	{
		Flash_Write_Char(*s);
		s++;
	}
}
