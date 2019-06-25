#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "stm32f4xx.h"
#include "stm32f4xx_conf.h"
#ifndef __FSMC_H
#define __FSMC_H
#ifdef __cplusplus
 extern "C" {
#endif
#define d_MAX_PULSE_PER_PERIOD			 		50
#define d_MIN_PULSE_PER_PERIOD			 		0
#define d_PULSE_BASE_ADDR 				0x60000000

#define d_ENC_BASE_ADDR 					0x60000020

#define c_CONTROL_PERIOD 0.001f
#define c_PULSE_TO_POS 0.00016f // 8/50000

void FSMC_Init(void);
void Servo_pulse(uint8_t Servo_num, uint32_t i_pulse_1, uint32_t Dir_1);
void FSMC_Write(uint32_t ui_address, uint32_t ui_data);
void FSMC_ENC_Update_Pos(void);
void FSMC_ENC_Reset(void);
float FSMC_ENC_Get_Vel(uint8_t motor_num);
uint16_t FSMC_Read(uint32_t ui_enc_channel);

#ifdef __cplusplus
}
#endif

#endif 
