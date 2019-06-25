
#include "stm32f4xx.h"
#include "system_timetick.h"
#include "HomeSwitch.h"
#include "UART.h"
#include "eeprom.h"
#include "utils.h"
#include "Calculator.h"
#include "Servo.h"
SERVO_DATA_STRUCT st_servo_data[6];
void Servo_Home_Switch_Init(void)  // Config Servo Home Switch:  
{	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG,ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStructure;
	EXTI_InitTypeDef EXTI_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	// For Servo 1 switch
	RCC_AHB1PeriphClockCmd(HOME_SERVO1_PORT_CLK,ENABLE);
	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
	GPIO_InitStructure.GPIO_Pin = HOME_SERVO1_PIN;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_Init(HOME_SERVO1_PORT, & GPIO_InitStructure);
	
	SYSCFG_EXTILineConfig(HOME_SERVO1_EXTI_PORT_SOURCE,HOME_SERVO1_EXTI_PIN_SOURCE);
	
	EXTI_InitStructure.EXTI_Line = HOME_SERVO1_EXTI_LINE;
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
	EXTI_Init(&EXTI_InitStructure);
	
	NVIC_InitStructure.NVIC_IRQChannel = HOME_SERVO1_EXTI_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	
	// For Servo 2 switch
	RCC_AHB1PeriphClockCmd(HOME_SERVO2_PORT_CLK,ENABLE);
	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
	GPIO_InitStructure.GPIO_Pin = HOME_SERVO2_PIN;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_Init(HOME_SERVO2_PORT, & GPIO_InitStructure);
	
	SYSCFG_EXTILineConfig(HOME_SERVO2_EXTI_PORT_SOURCE,HOME_SERVO2_EXTI_PIN_SOURCE);
	
	EXTI_InitStructure.EXTI_Line = HOME_SERVO2_EXTI_LINE;
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
	EXTI_Init(&EXTI_InitStructure);
	
	NVIC_InitStructure.NVIC_IRQChannel = HOME_SERVO2_EXTI_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	
	// For Servo 3 switch
	RCC_AHB1PeriphClockCmd(HOME_SERVO3_PORT_CLK,ENABLE);
	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
	GPIO_InitStructure.GPIO_Pin = HOME_SERVO3_PIN;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_Init(HOME_SERVO3_PORT, & GPIO_InitStructure);
	
	SYSCFG_EXTILineConfig(HOME_SERVO3_EXTI_PORT_SOURCE,HOME_SERVO3_EXTI_PIN_SOURCE);
	
	EXTI_InitStructure.EXTI_Line = HOME_SERVO3_EXTI_LINE;
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
	EXTI_Init(&EXTI_InitStructure);
	
	NVIC_InitStructure.NVIC_IRQChannel = HOME_SERVO3_EXTI_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	
	// For Servo 4 switch
	RCC_AHB1PeriphClockCmd(HOME_SERVO4_PORT_CLK,ENABLE);
	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
	GPIO_InitStructure.GPIO_Pin = HOME_SERVO4_PIN;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_Init(HOME_SERVO4_PORT, & GPIO_InitStructure);
	
	SYSCFG_EXTILineConfig(HOME_SERVO4_EXTI_PORT_SOURCE,HOME_SERVO4_EXTI_PIN_SOURCE);
	
	EXTI_InitStructure.EXTI_Line = HOME_SERVO4_EXTI_LINE;
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
	EXTI_Init(&EXTI_InitStructure);
	
	NVIC_InitStructure.NVIC_IRQChannel = HOME_SERVO4_EXTI_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	
	// For Servo 5 switch
	RCC_AHB1PeriphClockCmd(HOME_SERVO5_PORT_CLK,ENABLE);
	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
	GPIO_InitStructure.GPIO_Pin = HOME_SERVO5_PIN;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_Init(HOME_SERVO5_PORT, & GPIO_InitStructure);
	
	SYSCFG_EXTILineConfig(HOME_SERVO5_EXTI_PORT_SOURCE,HOME_SERVO5_EXTI_PIN_SOURCE);
	
	EXTI_InitStructure.EXTI_Line = HOME_SERVO5_EXTI_LINE;
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
	EXTI_Init(&EXTI_InitStructure);
	
	NVIC_InitStructure.NVIC_IRQChannel = HOME_SERVO5_EXTI_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	
	// For Servo 6 switch
	RCC_AHB1PeriphClockCmd(HOME_SERVO6_PORT_CLK,ENABLE);
	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
	GPIO_InitStructure.GPIO_Pin = HOME_SERVO6_PIN;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_Init(HOME_SERVO6_PORT, & GPIO_InitStructure);
	
	SYSCFG_EXTILineConfig(HOME_SERVO6_EXTI_PORT_SOURCE,HOME_SERVO6_EXTI_PIN_SOURCE);
	
	EXTI_InitStructure.EXTI_Line = HOME_SERVO6_EXTI_LINE;
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
	EXTI_Init(&EXTI_InitStructure);
	
	NVIC_InitStructure.NVIC_IRQChannel = HOME_SERVO6_EXTI_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);

}
void EXTI15_10_IRQHandler(void)
{
	//For Servo 0
	if(EXTI_GetITStatus(HOME_SERVO1_EXTI_LINE) != RESET)
	{
		EXTI_ClearITPendingBit(HOME_SERVO1_EXTI_LINE);
		st_servo_data[0].b_servo_home_done=true;
		pulse_empty[0]=Servo_dir[0];
	}
	
	//For Servo 1
	if(EXTI_GetITStatus(HOME_SERVO2_EXTI_LINE) != RESET)
	{
		EXTI_ClearITPendingBit(HOME_SERVO2_EXTI_LINE);
		st_servo_data[1].b_servo_home_done=true;
		pulse_empty[1]=Servo_dir[1];
	}
	
	//For Servo 2
	if(EXTI_GetITStatus(HOME_SERVO3_EXTI_LINE) != RESET)
	{
		EXTI_ClearITPendingBit(HOME_SERVO3_EXTI_LINE);
		st_servo_data[2].b_servo_home_done=true;
		pulse_empty[2]=Servo_dir[2];
	}
	
	//For Servo 3
	if(EXTI_GetITStatus(HOME_SERVO4_EXTI_LINE) != RESET)
	{
		EXTI_ClearITPendingBit(HOME_SERVO4_EXTI_LINE);
		st_servo_data[3].b_servo_home_done=true;
		pulse_empty[3]=Servo_dir[3];
	}
}

// Function Interrupt For Home Servo 4
void EXTI2_IRQHandler(void)
{
	if(EXTI_GetITStatus(HOME_SERVO5_EXTI_LINE) != RESET)
	{
		EXTI_ClearITPendingBit(HOME_SERVO5_EXTI_LINE);
		st_servo_data[4].b_servo_home_done=true;
		pulse_empty[4]=Servo_dir[4];		
	}
}
// Function Interrupt For Home Servo 5
void EXTI1_IRQHandler(void)
{
	if(EXTI_GetITStatus(HOME_SERVO6_EXTI_LINE) != RESET)
	{
		EXTI_ClearITPendingBit(HOME_SERVO6_EXTI_LINE);
		st_servo_data[5].b_servo_home_done=true;
		pulse_empty[5]=Servo_dir[5];		
	}
}

//----------------------------------------------------------------------------------------------				
//Get all homing status from each motor
bool Home_Status(void)
{
	bool home_scan_finish = 0;
	
	while( ! home_scan_finish )
	{
		bool temp = 1;
		for(int i=0;i<6;i++)
		{
			temp &= st_servo_data[i].b_servo_home_done;
		}
		home_scan_finish = temp;
	}
	
						
	return home_scan_finish;
}
//----------------------------------------------------------------------------------------------				
//Reset Homing status of each motor
void Home_Scan_Begin(void)
{
	for(int i=0;i<6;i++)
	{
		st_servo_data[i].b_servo_home_done=false;
	}
}

