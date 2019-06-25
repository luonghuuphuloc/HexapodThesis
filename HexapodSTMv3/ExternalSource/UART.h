#include <stdint.h>
#include <stdbool.h>
#include "stm32f4xx.h"
#include "string.h"
#include "utils.h"

#ifndef __UART_H
#define __UART_H
#ifdef __cplusplus
 extern "C" {
#endif
#define BUFF_RX 52 
#define BUFF_TX 500

extern uint8_t 	txbuff[BUFF_TX];
extern uint8_t 	rxbuff[BUFF_RX];
extern uint8_t 	txbuff_android[BUFF_TX];
extern uint8_t 	rxbuff_android[BUFF_RX];

extern char str_tx_uart[500];
extern char str_tx_uart_android[500];

extern bool update_cmd_busy_flag;
extern bool update_cmd_busy_flag_android;

void UART_DMA_Init(void);
void UART_DMA_Init_android(void);
void Ex_Usart_SendData(char* UsartData);
void UART_Send_PC_Encoder_Pos(void);
void Uart_Cmd_Update(const char* strInput);
void Uart_Cmd_Update_android(const char* strInput);

#ifdef __cplusplus
}
#endif

#endif 
