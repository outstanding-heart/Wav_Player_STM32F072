
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "wav.h"

/* Private variables ---------------------------------------------------------*/
uint32_t Usart1IRQBuffer;			//串口1缓存值
uint32_t Tim3IRQBuffer;


int main(void)
{ 
	WavHeader wavheader;
	
	Usart1IRQBuffer = 0;

	/* Init GPIO, NVIC, USART */
	USART1_Init();
	SerialPutString("\nUSART1 Init done!\n");
	
	/* Init Flash */
	Flash_Init();
	SerialPutString("Flash Init done! ");
	
	//Flash_Erase();
	//Flash_Write();
	//Flash_Read();
	
	while (1)
	{
		
		if (Usart1IRQBuffer == 1)
		{
			Wav_Config(&wavheader);		//把初始化后的数据地址传出来
			Usart1IRQBuffer = 0;
			PrintWavHeader(wavheader);
		}		
		
	}

}

void USART1_IRQHandler(void)
{
	uint8_t Key;

	if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)
	{
		
		//USART_ClearITPendingBit(USART1, USART_IT_RXNE);
		Key = USART_ReceiveData(USART1);
		
		SerialPutChar(Key);
		
		if (Key == '1')
		{
			Usart1IRQBuffer = 1; 
		}
		
	}
}

