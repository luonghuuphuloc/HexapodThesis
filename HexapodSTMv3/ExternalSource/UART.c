#include <stdbool.h>
#include "stm32f4xx.h"
#include "stm32f4xx_conf.h"
#include "UART.h"
#include "HomeSwitch.h"
#include <string.h>

uint8_t 	txbuff[BUFF_TX];
uint8_t 	rxbuff[BUFF_RX];

uint8_t 	txbuff_android[BUFF_TX];
uint8_t 	rxbuff_android[BUFF_RX];

char frame[100] = {0};

char frame_for_android[100] = "s_";

static char str_uart_update[100];
static char str_uart_update_android[100];



uint8_t len = 0;

void UART_DMA_Init(void)
{
	GPIO_InitTypeDef 	GPIO_InitStructure; 
	USART_InitTypeDef USART_InitStructure;   
	DMA_InitTypeDef  	DMA_InitStructure;
	NVIC_InitTypeDef  NVIC_InitStructure;	
   
  /* Enable GPIO clock */
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);
  /* Enable UART clock */
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);
	/* Enable DMA1 clock */
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA1, ENABLE);

  /* Connect USART3 pins to AF7 */  
  GPIO_PinAFConfig(GPIOB, GPIO_PinSource10, GPIO_AF_USART3);
  GPIO_PinAFConfig(GPIOB, GPIO_PinSource11, GPIO_AF_USART3); 

  /* GPIO Configuration for USART3 Tx */
  GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_10;
  GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_UP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOB, &GPIO_InitStructure);

  /* GPIO Configuration for USART Rx */
  GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_11;
  GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF;
  GPIO_Init(GPIOB, &GPIO_InitStructure);
       
  /* USARTx configured as follow:
		- BaudRate = 115200 baud  
    - Word Length = 8 Bits
    - One Stop Bit
    - No parity
    - Hardware flow control disabled (RTS and CTS signals)
    - Receive and transmit enabled
  */
  USART_InitStructure.USART_BaudRate = 115200;
  USART_InitStructure.USART_WordLength = USART_WordLength_8b;
  USART_InitStructure.USART_StopBits = USART_StopBits_1;
  USART_InitStructure.USART_Parity = USART_Parity_No;
  USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
  USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;

  USART_Init(USART3, &USART_InitStructure);
	
	/* Enable USART */
  USART_Cmd(USART3, ENABLE);
	
	/* Enable USART3 DMA */
  USART_DMACmd(USART3, USART_DMAReq_Tx, ENABLE); 
	
	/* Enable USART3 DMA */
  USART_DMACmd(USART3, USART_DMAReq_Rx, ENABLE);
	
	/* DMA1 Stream1 Channel4 for USART3 Rx configuration */			
  DMA_InitStructure.DMA_Channel = DMA_Channel_4;  
  DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)&USART3->DR;
  DMA_InitStructure.DMA_Memory0BaseAddr = (uint32_t)rxbuff;
  DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralToMemory;
  DMA_InitStructure.DMA_BufferSize = BUFF_RX;
  DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
  DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
  DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
  DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;
  DMA_InitStructure.DMA_Mode = DMA_Mode_Normal;//DMA_Mode_Circular;
  DMA_InitStructure.DMA_Priority = DMA_Priority_High;
  DMA_InitStructure.DMA_FIFOMode = DMA_FIFOMode_Disable;         
  DMA_InitStructure.DMA_FIFOThreshold = DMA_FIFOThreshold_HalfFull;
  DMA_InitStructure.DMA_MemoryBurst = DMA_MemoryBurst_Single;
  DMA_InitStructure.DMA_PeripheralBurst = DMA_PeripheralBurst_Single;
  DMA_Init(DMA1_Stream1, &DMA_InitStructure);
  DMA_Cmd(DMA1_Stream1, ENABLE);
		
	/* Enable DMA Interrupt to the highest priority */
  NVIC_InitStructure.NVIC_IRQChannel = DMA1_Stream1_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);

//  /* Transfer complete interrupt mask */
  DMA_ITConfig(DMA1_Stream1, DMA_IT_TC, ENABLE);
	
	
	
	/* DMA1 Stream3 Channel4 for UART4 Tx configuration */			
  DMA_InitStructure.DMA_Channel = DMA_Channel_4;  
  DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)&USART3->DR;
  DMA_InitStructure.DMA_Memory0BaseAddr = (uint32_t)txbuff;
  DMA_InitStructure.DMA_DIR = DMA_DIR_MemoryToPeripheral;
  DMA_InitStructure.DMA_BufferSize = BUFF_TX;
  DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
  DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
  DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
  DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;
  DMA_InitStructure.DMA_Mode = DMA_Mode_Normal;
  DMA_InitStructure.DMA_Priority = DMA_Priority_High;
  DMA_InitStructure.DMA_FIFOMode = DMA_FIFOMode_Disable;         
  DMA_InitStructure.DMA_FIFOThreshold = DMA_FIFOThreshold_HalfFull;
  DMA_InitStructure.DMA_MemoryBurst = DMA_MemoryBurst_Single;
  DMA_InitStructure.DMA_PeripheralBurst = DMA_PeripheralBurst_Single;
  DMA_Init(DMA1_Stream3, &DMA_InitStructure);
  DMA_Cmd(DMA1_Stream3, ENABLE);
}
//----------------------------------------------------------------------------------------------
// Send Uart Data from token trimmed from tx buffer
void Ex_Usart_SendData(char* UsartData)
{

		strcat(str_tx_uart, "\n");
		uint16_t string_lenght = strlen(str_tx_uart);
		strcat(str_tx_uart_android, "\n");
		uint16_t string_lenght_android = strlen(str_tx_uart_android);
		
		if(strlen(str_tx_uart) != 0)
		{
			DMA_Cmd(DMA1_Stream3, DISABLE);	
			memcpy(txbuff, str_tx_uart, string_lenght);
			DMA_ClearFlag(DMA1_Stream3, DMA_FLAG_TCIF3);
			DMA1_Stream3->NDTR = string_lenght;
			DMA_Cmd(DMA1_Stream3, ENABLE);	
		}
		if(strlen(str_tx_uart_android) != 0)
		{
			DMA_Cmd(DMA2_Stream6, DISABLE);	
			memcpy(txbuff_android, str_tx_uart_android, string_lenght_android);
			DMA_ClearFlag(DMA2_Stream6, DMA_FLAG_TCIF6);
			DMA2_Stream6->NDTR = string_lenght_android;
			DMA_Cmd(DMA2_Stream6, ENABLE);
		}
		memset(str_tx_uart,0,string_lenght);
		memset(str_tx_uart_android,0,string_lenght_android);
}

//----------------------------------------------------------------------------------------------

//----------------------------------------------------------------------------------------------------
//Send encoder position to GUI
void UART_Send_PC_Encoder_Pos(void)
{
	len = 0;
	frame[len++] = 'e';
	for(int index = 0; index < MAX_SERVO_NUM; index++)
	{
		if(st_servo_data[index].enc_cur_pos < 0.0f)
			st_servo_data[index].enc_cur_pos = 0.0f;
		sprintf(frame + len, "%7.3f", st_servo_data[index].enc_cur_pos);
		len += 7;
	
	}
	frame[len] = '-'; // Finish char
	
	Uart_Cmd_Update(frame);
	
	strcpy(frame_for_android, "s_");
	strcat(frame_for_android, frame);
	Uart_Cmd_Update_android(frame_for_android);

}

//----------------------------------------------------------------------------------------------
//Put new packet to string buffer, waiting for sent
void Uart_Cmd_Update(const char* strInput) 
{
	//if 2 strings are similar, skip it
	if(strInput != str_uart_update)
	{
		while(update_cmd_busy_flag);
		update_cmd_busy_flag = 1;
		strcpy(str_uart_update, strInput);
		strcat(str_tx_uart, str_uart_update);
		update_cmd_busy_flag = 0;
	}
}

void Uart_Cmd_Update_android(const char* strInput) 
{
	//if 2 strings are similar, skip it
	if(strInput != str_uart_update_android)
	{
		while(update_cmd_busy_flag_android);
		update_cmd_busy_flag_android = 1;
		strcpy(str_uart_update_android, strInput);
		strcat(str_tx_uart_android, str_uart_update_android);
		update_cmd_busy_flag_android = 0;
	}
}

void UART_DMA_Init_android(void)
{
	GPIO_InitTypeDef 	GPIO_InitStructure; 
	USART_InitTypeDef USART_InitStructure;   
	DMA_InitTypeDef  	DMA_InitStructure;
	NVIC_InitTypeDef  NVIC_InitStructure;	
   
  /* Enable GPIOC clock */
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);
  /* Enable USART6 clock */
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART6, ENABLE);
	/* Enable DMA2 clock */
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA2, ENABLE);

  /* Connect USART6 pins to AF8 */  
  GPIO_PinAFConfig(GPIOC, GPIO_PinSource6, GPIO_AF_USART6);
  GPIO_PinAFConfig(GPIOC, GPIO_PinSource7, GPIO_AF_USART6); 

  /* GPIO Configuration for USART6 Tx */
  GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_6;
  GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_UP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOC, &GPIO_InitStructure);

  /* GPIO Configuration for USART6 Rx */
  GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_7;
  GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF;
  GPIO_Init(GPIOC, &GPIO_InitStructure);
       
  /* USARTx configured as follow:
		- BaudRate = 115200 baud  
    - Word Length = 8 Bits
    - One Stop Bit
    - No parity
    - Hardware flow control disabled (RTS and CTS signals)
    - Receive and transmit enabled
  */
  USART_InitStructure.USART_BaudRate = 115200;
  USART_InitStructure.USART_WordLength = USART_WordLength_8b;
  USART_InitStructure.USART_StopBits = USART_StopBits_1;
  USART_InitStructure.USART_Parity = USART_Parity_No;
  USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
  USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;

  USART_Init(USART6, &USART_InitStructure);
	
	/* Enable USART6 */
  USART_Cmd(USART6, ENABLE);
	
	/* Enable USART6 DMA */
  USART_DMACmd(USART6, USART_DMAReq_Tx, ENABLE); 
	
	/* Enable USART6 DMA */
  USART_DMACmd(USART6, USART_DMAReq_Rx, ENABLE);
	
	/* DMA2 Stream2 Channel5 for USART6 Rx configuration */			
  DMA_InitStructure.DMA_Channel = DMA_Channel_5;  
  DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)&USART6->DR;
  DMA_InitStructure.DMA_Memory0BaseAddr = (uint32_t)rxbuff_android;
  DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralToMemory;
  DMA_InitStructure.DMA_BufferSize = BUFF_RX;
  DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
  DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
  DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
  DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;
  DMA_InitStructure.DMA_Mode = DMA_Mode_Normal;//DMA_Mode_Circular;
  DMA_InitStructure.DMA_Priority = DMA_Priority_High;
  DMA_InitStructure.DMA_FIFOMode = DMA_FIFOMode_Disable;         
  DMA_InitStructure.DMA_FIFOThreshold = DMA_FIFOThreshold_HalfFull;
  DMA_InitStructure.DMA_MemoryBurst = DMA_MemoryBurst_Single;
  DMA_InitStructure.DMA_PeripheralBurst = DMA_PeripheralBurst_Single;
  DMA_Init(DMA2_Stream2, &DMA_InitStructure);
  DMA_Cmd(DMA2_Stream2, ENABLE);
		
	/* Enable DMA Interrupt to the highest priority */
  NVIC_InitStructure.NVIC_IRQChannel = DMA2_Stream2_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);

//  /* Transfer complete interrupt mask */
  DMA_ITConfig(DMA2_Stream2, DMA_IT_TC, ENABLE);
	
	
	
	/* DMA2 Stream6 Channel5 for USART6 Tx configuration */			
  DMA_InitStructure.DMA_Channel = DMA_Channel_5;  
  DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)&USART6->DR;
  DMA_InitStructure.DMA_Memory0BaseAddr = (uint32_t)txbuff_android;
  DMA_InitStructure.DMA_DIR = DMA_DIR_MemoryToPeripheral;
  DMA_InitStructure.DMA_BufferSize = BUFF_TX;
  DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
  DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
  DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
  DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;
  DMA_InitStructure.DMA_Mode = DMA_Mode_Normal;
  DMA_InitStructure.DMA_Priority = DMA_Priority_High;
  DMA_InitStructure.DMA_FIFOMode = DMA_FIFOMode_Disable;         
  DMA_InitStructure.DMA_FIFOThreshold = DMA_FIFOThreshold_HalfFull;
  DMA_InitStructure.DMA_MemoryBurst = DMA_MemoryBurst_Single;
  DMA_InitStructure.DMA_PeripheralBurst = DMA_PeripheralBurst_Single;
  DMA_Init(DMA2_Stream6, &DMA_InitStructure);
  DMA_Cmd(DMA2_Stream6, ENABLE);
}
