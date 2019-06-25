#include <stdint.h>
#include <stdbool.h>
#include "stm32f4xx.h"
#include "stm32f4xx_conf.h"
#ifndef __ENCODER_H
#define __ENCODER_H
#ifdef __cplusplus
 extern "C" {
#endif

extern uint16_t save_pos_count;
extern uint32_t countT2;

void ENC_Timer_Init(void);
void ENC_Reset(void);

#ifdef __cplusplus
}
#endif

#endif 
