
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "wav.h"

/* Private define ------------------------------------------------------------*/

#define Num_1 1
#define Num_4 4
#define Bit_1 1
#define Bit_2 2
#define Bit_4 4

#define volume 8																				//ԽС����Խ��

/* Exported types ------------------------------------------------------------*/

/* Global variable */
uint32_t DataAddress;				//���ݵ�ַλ
WavHeader Nowwavheader;

/* Init Wav */
// StartAddr: ��Կ�ʼ��ַ
// ����ֵΪ������ʼ��ַ  
uint32_t Wav_Init(WavHeader *wavheader, uint32_t StartAddr)
{
	uint32_t Address;

	Address = StartAddr;

	//RIFF
	SerialPutString("\n");
	SerialPutString("\n");
	Flash_Read_Choose_Wav_Info((*wavheader).riffheader.szRiffID, Address, Num_4, Bit_1);		//'RIFF'
	(*wavheader).riffheader.szRiffID[4] = '\0';													//���һλ��ֵΪ'\0'
	Address = Address + Num_4 * Bit_1;															//��һ��ַ

	(*wavheader).riffheader.dwRiffSize = Flash_Read_Choose_Wav_Num(Address, Num_1, Bit_4);		//�ļ�����
	Address = Address + Num_1 * Bit_4;															//��һ��ַ

	Flash_Read_Choose_Wav_Info((*wavheader).riffheader.szRiffFormat, Address, Num_4, Bit_1);	//'WAVE'
	(*wavheader).riffheader.szRiffFormat[4] = '\0';												//���һλ��ֵΪ'\0'
	Address = Address + Num_4 * Bit_1;															//��һ��ַ

	//FMT
	Flash_Read_Choose_Wav_Info((*wavheader).pcmwaveformat.szFmtID, Address, Num_4, Bit_1);		//'fmt' 
	(*wavheader).pcmwaveformat.szFmtID[4] = '\0';													//���һλ��ֵΪ'\0'
	Address = Address + Num_4 * Bit_1;															//��һ��ַ

	(*wavheader).pcmwaveformat.wBitsPerSample = Flash_Read_Choose_Wav_Num(Address, Num_1, Bit_4);//fmt��С
	Address = Address + Num_1 * Bit_4;															//��һ��ַ

	(*wavheader).pcmwaveformat.wf.wFormatag = Flash_Read_Choose_Wav_Num(Address, Num_1, Bit_2);	//��ʽ����
	Address = Address + Num_1 * Bit_2;															//��һ��ַ

	(*wavheader).pcmwaveformat.wf.wChannls = Flash_Read_Choose_Wav_Num(Address, Num_1, Bit_2);	//ͨ����
	Address = Address + Num_1 * Bit_2;															//��һ��ַ

	(*wavheader).pcmwaveformat.wf.nSamplesPerSec = Flash_Read_Choose_Wav_Num(Address, Num_1, Bit_4);//����Ƶ��
	Address = Address + Num_1 * Bit_4;															//��һ��ַ

	(*wavheader).pcmwaveformat.wf.dwAvgBytesperSec = Flash_Read_Choose_Wav_Num(Address, Num_1, Bit_4);//��������
	Address = Address + Num_1 * Bit_4;															//��һ��ַ

	(*wavheader).pcmwaveformat.wf.wBlockAlign = Flash_Read_Choose_Wav_Num(Address, Num_1, Bit_2);//DATA���ݿ鳤
	Address = Address + Num_1 * Bit_2;															//��һ��ַ

	(*wavheader).pcmwaveformat.wf.wBitsPerSample = Flash_Read_Choose_Wav_Num(Address, Num_1, Bit_2);//PCMλ��
	Address = Address + Num_1 * Bit_2;															//��һ��ַ
	
	//DATA
	Flash_Read_Choose_Wav_Info((*wavheader).datablack.szDataID, Address, Num_4, Bit_1);			//'data'
	(*wavheader).datablack.szDataID[4] = '\0';													//���һλ��ֵΪ'\0'
	Address = Address + Num_4 * Bit_1;															//��һ��ַ
	
	(*wavheader).datablack.dwDataSize = Flash_Read_Choose_Wav_Num(Address, Num_1, Bit_4);		//�������ݳ���
	Address = Address + Num_1 * Bit_4;															//��һ��ַ
	

	//PrintWavHeader(wavheader);
	return Address;
}

void PrintWavHeader(WavHeader Wavheader)
{
	char string[NumStrMax];
	SerialPutString("~~Read Start~~ ");
	
	SerialPutString("\n szRiffID: ");//1
	SerialPutString(Wavheader.riffheader.szRiffID);
	
	SerialPutString("\n dwRiffSize: ");//2
	sprintf(string, "%d", Wavheader.riffheader.dwRiffSize);
	SerialPutString(string);
	
	SerialPutString("\n szRiffFormat: ");//3
	SerialPutString(Wavheader.riffheader.szRiffFormat);
	
	SerialPutString("\n szFmtID: ");//4
	SerialPutString(Wavheader.pcmwaveformat.szFmtID);
	
	SerialPutString("\n wBitsPerSample: ");//5
	sprintf(string, "%d", Wavheader.pcmwaveformat.wBitsPerSample);
	SerialPutString(string);
	
	SerialPutString("\n wFormatag: ");//6
	sprintf(string, "%d", Wavheader.pcmwaveformat.wf.wFormatag);
	SerialPutString(string);
	
	SerialPutString("\n wChannls: ");//7
	sprintf(string, "%d", Wavheader.pcmwaveformat.wf.wChannls);
	SerialPutString(string);
	
	SerialPutString("\n nSamplesPerSec: ");//8
	sprintf(string, "%d", Wavheader.pcmwaveformat.wf.nSamplesPerSec);
	SerialPutString(string);
	
	SerialPutString("\n dwAvgBytesperSec: ");//9
	sprintf(string, "%d", Wavheader.pcmwaveformat.wf.dwAvgBytesperSec);
	SerialPutString(string);
	
	SerialPutString("\n wBlockAlign: ");//10
	sprintf(string, "%d", Wavheader.pcmwaveformat.wf.wBlockAlign);
	SerialPutString(string);
	
	SerialPutString("\n wBitsPerSample: ");//11
	sprintf(string, "%d", Wavheader.pcmwaveformat.wf.wBitsPerSample);
	SerialPutString(string);
	
	SerialPutString("\n szDataID: ");//12
	SerialPutString(Wavheader.datablack.szDataID);
	
	SerialPutString("\n dwDataSize: ");//13
	sprintf(string, "%d", Wavheader.datablack.dwDataSize);
	SerialPutString(string);
	
}


/* ��ʱ�����жϳ�ʼ�� */
void Time_Init(WavHeader wavheader)
{
    NVIC_InitTypeDef NVIC_InitStructure;
	TIM_TimeBaseInitTypeDef    TIM_TimeBaseStructure;
	uint32_t nSamplesPerSec = wavheader.pcmwaveformat.wf.nSamplesPerSec;
	
	//PrintWavHeader(wavheader);
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);									//APB1��Ƶ8MHz
	
	TIM_TimeBaseStructInit(&TIM_TimeBaseStructure); 
	TIM_TimeBaseStructure.TIM_Period = 1000000/nSamplesPerSec ;								//��ʱ����
	TIM_TimeBaseStructure.TIM_Prescaler = 7;       											//Ԥ��Ƶֵ=(8M/1M)-1
	TIM_TimeBaseStructure.TIM_ClockDivision = 0x0;    										//ʱ�ӷ�Ƶ����
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  							//����ģʽ
	
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);
	TIM_ITConfig(TIM3,TIM_IT_Update,ENABLE);
	TIM_Cmd(TIM3, ENABLE);
	
	//��ʱ����ʼ�����
	
	/* Enable the USARTy Interrupt */
    NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
    
    /* Enable the usart1 receive interrupt */
	
}

void Wav_Config(WavHeader *wavheader)
{
	
	uint32_t  address;//, count;
	char string[NumStrMax], 
	*RIFF = "RIFF\0", *WAVE = "WAVE\0", *fmt = "fmt \0", *data = "data\0";
	
	address = Wav_Init(&(*wavheader), 0);
	
	if(strcmp((*wavheader).riffheader.szRiffID, RIFF) != 0)		//���RIFF��־
	{
		SerialPutString("RIFF error!");
		while(1)
		{}
	}
	
	if(strcmp((*wavheader).riffheader.szRiffFormat, WAVE) != 0)	//���WAVE��־
	{
		SerialPutString("WAVE error!");
		while(1)
		{}
	}
	
	if(strcmp((*wavheader).pcmwaveformat.szFmtID, fmt) != 0)		//���fmt��־
	{
		SerialPutString("fmt error!");
		while(1)
		{}
	}
	
	if(strcmp((*wavheader).datablack.szDataID, data) != 0)			//���data��־
	{
		SerialPutString("data error!");
		while(1)
		{}
	}
	
	sprintf(string, "%d ", address);
	SerialPutString("\n");
	SerialPutString(string);
	//PrintWavHeader((*wavheader));
	Nowwavheader = (*wavheader);
	
	DAC1_Init();
	Time_Init(*wavheader);

	DataAddress = address;
	
}


/* ��ʱ��3�жϴ�����������DAC��Ƶ��� */
// WavHeader wavheader;
void TIM3_IRQHandler()
{
	uint16_t Data, data;
	//char string[NumStrMax];

	while(DataAddress < Nowwavheader.datablack.dwDataSize)					//ֻѰַ����
	{
		if(TIM_GetITStatus(TIM3 , TIM_IT_Update) == SET)
		{
			TIM_ClearITPendingBit(TIM3 , TIM_FLAG_Update);
			//SerialPutString("Tim3_IRQ ok\n");
			if(Nowwavheader.pcmwaveformat.wf.wChannls == 1)
			{
				if(Nowwavheader.pcmwaveformat.wf.wBitsPerSample == 8)		//��������λ
				{
					Data = Flash_Read_Wav_Data(DataAddress, Bit_1) ;
					
					DAC_SetChannel1Data(DAC_Align_8b_R, Data/volume);
					
					DataAddress = DataAddress + Bit_1;
				}
				else if(Nowwavheader.pcmwaveformat.wf.wBitsPerSample == 16)	//������ʮ��λ
				{
					Data = Flash_Read_Wav_Data(DataAddress, Bit_2);
					
					data = Data+(1<<15) ;
					DAC_SetChannel1Data(DAC_Align_12b_L, data/volume);

					DataAddress = DataAddress + Bit_2;
				}
				else
				{
					SerialPutString("wBitsPerSample error!");
					while(1)
					{}
				}
			}
			else if(Nowwavheader.pcmwaveformat.wf.wChannls == 2)
			{
				if(Nowwavheader.pcmwaveformat.wf.wBitsPerSample == 8)		//��������λ
				{
					Data = Flash_Read_Wav_Data(DataAddress, Bit_1) ;
					//DAC_SetChannel1Data(DAC_Align_12b_R, Data);
					DataAddress = DataAddress + Bit_1;
					DAC_SetChannel1Data(DAC_Align_12b_R, Data/volume);
					DataAddress = DataAddress + Bit_1;
				}
				else if(Nowwavheader.pcmwaveformat.wf.wBitsPerSample == 16)	//������ʮ��λ
				{
					Data = Flash_Read_Wav_Data(DataAddress, Bit_2);
					
					data = Data+(1<<15) ;
					DAC_SetChannel1Data(DAC_Align_12b_R, data/volume);
					DataAddress = DataAddress + Bit_2;
					//DAC_SetChannel1Data(DAC_Align_12b_R, Data);
					DataAddress = DataAddress + Bit_2;
				}
				else
				{
					SerialPutString("wBitsPerSample error!");
					while(1)
					{}
				}
			}
			else
			{
				SerialPutString("wChannls error!");
				while(1)
				{}
			}
		}
	
		//sprintf(string, "%d ", Data);
		//SerialPutString(string);	
	}
	if (DataAddress == Nowwavheader.datablack.dwDataSize)
	{
		TIM_ITConfig(TIM3,TIM_IT_Update,DISABLE);
	}
}


