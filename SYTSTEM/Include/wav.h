
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __WAV_H
#define __WAV_H

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private define ------------------------------------------------------------*/

/* Exported types ------------------------------------------------------------*/

typedef struct
{
	uint8_t szRiffID[5]; 			//'R','I','F','F' 
	uint32_t dwRiffSize;			//ȥͷ�ļ���С��������-8
	uint8_t szRiffFormat[5]; 		//'W','A','V','E'
}RiffHeader;

typedef struct
{
	uint16_t wFormatag; 			//�����ʽ��Ϊ1ʱ��ʾ����Ϊ����PCM����
	uint16_t wChannls;				//����������Ϊ1��˫Ϊ2
	uint32_t nSamplesPerSec;		//����Ƶ�ʣ�11,025/22,050
	uint32_t dwAvgBytesperSec;		//ÿ���������
	uint16_t wBlockAlign;			//ÿ��������Ҫ���ֽ�����1/2
	uint16_t wBitsPerSample;		//ÿ����������Ҫ��bit����8/16/32
}WaveFormat;

typedef struct
{
	uint8_t szFmtID[5]; 			//'f','m','t',' '
	uint32_t wBitsPerSample;		//WAVE�ļ��Ĳ�����С
	WaveFormat wf; 					//���θ�ʽ
}PcmWaveFormat;

typedef struct
{
	uint8_t szDataID[5];			//'d','a','t','a'
	uint32_t dwDataSize;			//���ݶεĴ�С
}DataBlack;

typedef struct
{
	uint8_t szFactID[5];			//'f','a','c','t'
	uint32_t dwFactSize;			//����
}FactBlock;

typedef struct
{
	RiffHeader riffheader;
	PcmWaveFormat pcmwaveformat;
	FactBlock factblock;
	DataBlack datablack;
}WavHeader;

/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
uint32_t Flash_Read_Choose_Wav_Num(uint32_t StartAddr, uint32_t Num, uint32_t BitNum);
void Flash_Read_Choose_Wav_Info(uint8_t *Info, uint32_t StartAddr, uint32_t Num, uint32_t BitNum);
void PrintWavHeader(WavHeader wavheader);
uint32_t Wav_Init(WavHeader *wavheader, uint32_t StartAddr);
void Play_Wav(WavHeader wavheader, uint32_t address);
void Time_Init(WavHeader wavheader);
void Wav_Config(WavHeader *wavheader);

#endif /* __WAV_H */

/*****************************END OF FILE**************************************/
