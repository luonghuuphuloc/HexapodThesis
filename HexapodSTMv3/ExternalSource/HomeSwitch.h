#include <stdint.h>
#include <stdbool.h>
#include "stm32f4xx.h"
#include "UART.h"
#include "eeprom.h"
#include "utils.h"
#include "Calculator.h"
#include "Servo.h"

#ifndef __HOMESWITCH_H
#define __HOMESWITCH_H
#ifdef __cplusplus
 extern "C" {
#endif
#define BUTTON_START_PORT 									GPIOA
#define BUTTON_START_PORT_CLK								RCC_AHB1Periph_GPIOA
#define BUTTON_START_PIN        						GPIO_Pin_3
#define BUTTON_START_PIN_SOURCE 						GPIO_PinSource3
#define BUTTON_START_EXTI_LINE							EXTI_Line3
#define BUTTON_START_EXTI_PORT_SOURCE				EXTI_PortSourceGPIOA
#define BUTTON_START_EXTI_PIN_SOURCE				EXTI_PinSource3
#define BUTTON_START_EXTI_IRQn							EXTI3_IRQn

#define BUTTON_STOP_PORT 										GPIOA
#define BUTTON_STOP_PORT_CLK								RCC_AHB1Periph_GPIOA
#define BUTTON_STOP_PIN        							GPIO_Pin_6
#define BUTTON_STOP_PIN_SOURCE 							GPIO_PinSource6
#define BUTTON_STOP_EXTI_LINE								EXTI_Line6
#define BUTTON_STOP_EXTI_PORT_SOURCE				EXTI_PortSourceGPIOA
#define BUTTON_STOP_EXTI_PIN_SOURCE					EXTI_PinSource6
#define BUTTON_STOP_EXTI_IRQn								EXTI9_5_IRQn

#define BUTTON_HOME_PORT 										GPIOA
#define BUTTON_HOME_PORT_CLK								RCC_AHB1Periph_GPIOA
#define BUTTON_HOME_PIN        							GPIO_Pin_4
#define BUTTON_HOME_PIN_SOURCE 							GPIO_PinSource4
#define BUTTON_HOME_EXTI_LINE								EXTI_Line4
#define BUTTON_HOME_EXTI_PORT_SOURCE				EXTI_PortSourceGPIOA
#define BUTTON_HOME_EXTI_PIN_SOURCE					EXTI_PinSource4
#define BUTTON_HOME_EXTI_IRQn								EXTI4_IRQn

#define HOME_SERVO1_PORT 										GPIOB
#define HOME_SERVO1_PORT_CLK								RCC_AHB1Periph_GPIOB
#define HOME_SERVO1_PIN        							GPIO_Pin_12
#define HOME_SERVO1_PIN_SOURCE 							GPIO_PinSource12
#define HOME_SERVO1_EXTI_LINE								EXTI_Line12
#define HOME_SERVO1_EXTI_PORT_SOURCE				EXTI_PortSourceGPIOB
#define HOME_SERVO1_EXTI_PIN_SOURCE					EXTI_PinSource12
#define HOME_SERVO1_EXTI_IRQn								EXTI15_10_IRQn

#define HOME_SERVO2_PORT 										GPIOB
#define HOME_SERVO2_PORT_CLK								RCC_AHB1Periph_GPIOB
#define HOME_SERVO2_PIN        							GPIO_Pin_13
#define HOME_SERVO2_PIN_SOURCE 							GPIO_PinSource13
#define HOME_SERVO2_EXTI_LINE								EXTI_Line13
#define HOME_SERVO2_EXTI_PORT_SOURCE				EXTI_PortSourceGPIOB
#define HOME_SERVO2_EXTI_PIN_SOURCE					EXTI_PinSource13
#define HOME_SERVO2_EXTI_IRQn								EXTI15_10_IRQn

#define HOME_SERVO3_PORT 										GPIOB
#define HOME_SERVO3_PORT_CLK								RCC_AHB1Periph_GPIOB
#define HOME_SERVO3_PIN        							GPIO_Pin_14
#define HOME_SERVO3_PIN_SOURCE 							GPIO_PinSource14
#define HOME_SERVO3_EXTI_LINE								EXTI_Line14
#define HOME_SERVO3_EXTI_PORT_SOURCE				EXTI_PortSourceGPIOB
#define HOME_SERVO3_EXTI_PIN_SOURCE					EXTI_PinSource14
#define HOME_SERVO3_EXTI_IRQn								EXTI15_10_IRQn

#define HOME_SERVO4_PORT 										GPIOB
#define HOME_SERVO4_PORT_CLK								RCC_AHB1Periph_GPIOB
#define HOME_SERVO4_PIN        							GPIO_Pin_15
#define HOME_SERVO4_PIN_SOURCE 							GPIO_PinSource15
#define HOME_SERVO4_EXTI_LINE								EXTI_Line15
#define HOME_SERVO4_EXTI_PORT_SOURCE				EXTI_PortSourceGPIOB
#define HOME_SERVO4_EXTI_PIN_SOURCE					EXTI_PinSource15
#define HOME_SERVO4_EXTI_IRQn								EXTI15_10_IRQn

#define HOME_SERVO5_PORT 										GPIOA
#define HOME_SERVO5_PORT_CLK								RCC_AHB1Periph_GPIOA
#define HOME_SERVO5_PIN        							GPIO_Pin_2
#define HOME_SERVO5_PIN_SOURCE 							GPIO_PinSource2
#define HOME_SERVO5_EXTI_LINE								EXTI_Line2
#define HOME_SERVO5_EXTI_PORT_SOURCE				EXTI_PortSourceGPIOA
#define HOME_SERVO5_EXTI_PIN_SOURCE					EXTI_PinSource2
#define HOME_SERVO5_EXTI_IRQn								EXTI2_IRQn

#define HOME_SERVO6_PORT 										GPIOA
#define HOME_SERVO6_PORT_CLK								RCC_AHB1Periph_GPIOA
#define HOME_SERVO6_PIN        							GPIO_Pin_1
#define HOME_SERVO6_PIN_SOURCE 							GPIO_PinSource1
#define HOME_SERVO6_EXTI_LINE								EXTI_Line1
#define HOME_SERVO6_EXTI_PORT_SOURCE				EXTI_PortSourceGPIOA
#define HOME_SERVO6_EXTI_PIN_SOURCE					EXTI_PinSource1
#define HOME_SERVO6_EXTI_IRQn								EXTI1_IRQn

extern float HOME_OFFSET[6];
extern float MAX_OF_TRIP[6];

typedef struct
{
	bool b_servo_home_done;
	float pre_t;
	float t;
	uint32_t pulse_per_cycle;
	uint32_t pulse_total;
	float pulse_redundance;
	bool cannot_path_planning;
	float enc_cur_pos;
	float set_pos;
}
SERVO_DATA_STRUCT;

extern SERVO_DATA_STRUCT st_servo_data[6];

void Servo_Home_Switch_Init(void);
bool Home_Status(void);
void Home_Scan_Begin(void);

#ifdef __cplusplus
}
#endif

#endif 

