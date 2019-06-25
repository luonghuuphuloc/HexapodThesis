#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "stm32f4xx.h"
#include "stm32f4xx_conf.h"
#ifndef __OPERATIONMODE_H
#define __OPERATIONMODE_H
#ifdef __cplusplus
 extern "C" {
#endif

#define IDLE										0
#define TESTING 								1
#define HOMESCAN 								2
#define INVERSEKINEMATIC		 			3
extern uint8_t Mode;

extern bool reset_flag;
void TestingMode(void);	 
void HomeScanMode(void);
void InverseKinematicMode(void);
void IdleMode(void);
#ifdef __cplusplus
}
#endif

#endif 
