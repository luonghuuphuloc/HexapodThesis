#include <stdint.h>
#include <stdbool.h>
#include "stm32f4xx.h"
#include "UART.h"
#include "eeprom.h"
#include "utils.h"
#include "Calculator.h"
#include "Servo.h"

#ifndef __KINEMATIC_H
#define __KINEMATIC_H
#ifdef __cplusplus
 extern "C" {
#endif

#define Lp 24.752f
#define Lb 49.504f
#define L  20.0f

typedef struct
{
	float x;
	float y;
	float z;
	float roll;
	float pitch;
	float yaw;
}
HEXAPOD_DATA_STRUCT;

extern HEXAPOD_DATA_STRUCT st_hexapod_data;

void inverse_kinematic(float pos_in[3],float matR_in[9],float q[6]);
void pos_calculate(float* pos);
void matR_calculate(float* matR);

#ifdef __cplusplus
}
#endif

#endif 

