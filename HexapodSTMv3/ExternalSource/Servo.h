#include <stdint.h>
#include <stdbool.h>
#include "stm32f4xx.h"
#ifndef __SERVO_H
#define __SERVO_H
#ifdef __cplusplus
 extern "C" {
#endif
#define MAX_SERVO_NUM 6

#define SERVO0 0
#define SERVO1 1
#define SERVO2 2
#define SERVO3 3
#define SERVO4 4
#define SERVO5 5

extern float Servo_pos_pre[6];
extern float Servo_pos_cur[6];
extern float Servo_pos_distance[6];
extern uint8_t Servo_dir[6];

extern uint32_t countT3;

extern bool pulse_empty[6];

void Servo_Control_Timer_Init(void);
void TIM3_IRQHandler(void);
void Calcu_Pos(float pos_cur[6],float pos_pre[6]);
void Pos_servo_all(float q[6],uint8_t dir[6]);
void Servo_pos_per_cycle(void);

#ifdef __cplusplus
}
#endif

#endif 

