#include <stdint.h>
#include <stdbool.h>
#include "stm32f4xx.h"
#include "Servo.h"
#include "Calculator.h"
#include "FSMC.h"
#include "utils.h"
#include "HomeSwitch.h"
#include <string.h>
float Servo_pos_pre[MAX_SERVO_NUM]={0,0,0,0,0,0};
float Servo_pos_cur[MAX_SERVO_NUM]={0,0,0,0,0,0};
float Servo_pos_distance[MAX_SERVO_NUM]={0,0,0,0,0,0};
uint32_t countT3;
static uint8_t Servo_dir_private[MAX_SERVO_NUM] = {0};
// a[i] factor for each motor 
static float a_1[MATRIX_ORDER] = {0}; 

// a[i] factor for 6 motor 
static float a[MAX_SERVO_NUM][MATRIX_ORDER] = {0};

uint8_t Servo_dir[MAX_SERVO_NUM]={0,0,0,0,0,0};
bool pulse_empty[MAX_SERVO_NUM];
static bool Servo_Ready_Run_flag = 0;


void Servo_Control_Timer_Init(void)
{
	    // Enable clock for TIM3
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);

    // TIM3 initialization overflow every 500ms
    // TIM3 by default has clock of 84MHz
    // Here, we must set value of prescaler and period,
    // so update event is 0.5Hz or 500ms
    // Update Event (Hz) = timer_clock / ((TIM_Prescaler + 1) * 
    // (TIM_Period + 1))
    // Update Event (Hz) = 84MHz / ((83 + 1) * (999 + 1)) = 1000 Hz
    TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;
    TIM_TimeBaseInitStruct.TIM_Prescaler = 83;
    TIM_TimeBaseInitStruct.TIM_Period = 999;
    TIM_TimeBaseInitStruct.TIM_ClockDivision = TIM_CKD_DIV1;
    TIM_TimeBaseInitStruct.TIM_CounterMode = TIM_CounterMode_Up;

    // TIM3 initialize
    TIM_TimeBaseInit(TIM3, &TIM_TimeBaseInitStruct);
    // Enable TIM3 interrupt
    TIM_ITConfig(TIM3, TIM_IT_Update, ENABLE);
    // Start TIM3
    TIM_Cmd(TIM3, DISABLE);

    // Nested vectored interrupt settings
    // TIM3 PreemptionPriority = 0 and 
    // SubPriority = 0)
    NVIC_InitTypeDef NVIC_InitStruct;
    NVIC_InitStruct.NVIC_IRQChannel = TIM3_IRQn;
    NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 0;
    NVIC_InitStruct.NVIC_IRQChannelSubPriority = 0;
    NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStruct);
}

void TIM3_IRQHandler(void)
{
    // Checks whether the TIM3 interrupt has occurred or not
    if (TIM_GetITStatus(TIM3, TIM_IT_Update))
    {
			countT3++;
			if(countT3 == 10000)
				countT3 = 0;
			if(Servo_Ready_Run_flag)
				Servo_pos_per_cycle();
		}
        // Clears the TIM3 interrupt pending bit
    TIM_ClearITPendingBit(TIM3, TIM_IT_Update);
		
}

void Calcu_Pos(float pos_cur[MAX_SERVO_NUM],float pos_pre[MAX_SERVO_NUM])
{
	for(int i=0;i<MAX_SERVO_NUM;i++)
	{
		Servo_pos_distance[i]=Servo_pos_cur[i]-Servo_pos_pre[i];
		if(Servo_pos_distance[i]<0)
		{
			Servo_dir[i]=1;
			Servo_pos_distance[i]*=-1;
		}
		else
		{
			Servo_dir[i]=0;
		}
	}
}

void Pos_servo_all(float q[MAX_SERVO_NUM],uint8_t dir[MAX_SERVO_NUM])
{
	bool initial_cal_flag[MAX_SERVO_NUM] = {1,1,1,1,1,1};
	
	// Safety Factor
	float ks = 0.66;
	
	for(uint8_t i = 0; i < MATRIX_ORDER; i++)
		a_1[i] = 0;
	
	for(uint8_t i = 0; i < MAX_SERVO_NUM; i++)
	{
		Servo_dir_private[i] = dir[i];
		for(uint8_t j = 0; j < MATRIX_ORDER; j++)
			a[i][j] = 0;
	}
	
	for(int j=0;j<MAX_SERVO_NUM;j++)
	{
		st_servo_data[j].cannot_path_planning = 0;
		st_servo_data[j].pulse_redundance = 0;
		
		if(q[j] != 0)
		{

			if(j != 1)
			{
				st_servo_data[j].pulse_total = pos2pul(q[j]);				
			}
			else
			{
				st_servo_data[j].pulse_total = pos2pul(q[j]/2);
			}
			
			// Cannot calculate Path-planning if pulse_total < 500
			if(st_servo_data[j].pulse_total <= 500 )
				st_servo_data[j].cannot_path_planning = 1;
			else
			{
				pulse_path_planning(q[j],ks,j,a_1); // Calculate a[i] factor
				for(int k = 0; k < MATRIX_ORDER; k++)
				{
					a[j][k] = a_1[k];
				}				
			}
			pulse_empty[j] = 0;
		}
		else
		{
			pulse_empty[j] = 1;
		}
	}
	for(int i = 0; i < MAX_SERVO_NUM; i++)
	{
		st_servo_data[i].pre_t = 0;
		st_servo_data[i].t = 0.001;
	}
	Servo_Ready_Run_flag = 0;
	TIM_ClearITPendingBit(TIM3, TIM_IT_Update);
	TIM_Cmd(TIM3, ENABLE);
	
	while(! (pulse_empty[0] & pulse_empty[1] & pulse_empty[2] & pulse_empty[3] & pulse_empty[4] & pulse_empty[5]))
	{	
		for(uint8_t i=0;i<MAX_SERVO_NUM;i++)
		{
			if(initial_cal_flag[i])
			{
				for(int j = 0; j < MATRIX_ORDER; j++)
				{
					a_1[j] = a[i][j];
				}				
				st_servo_data[i].pulse_per_cycle = pulse_pp_cal(a_1, st_servo_data[i].pre_t, st_servo_data[i].t, i);
				initial_cal_flag[i] = 0;
				Servo_Ready_Run_flag = 1;
			}
		}
		
	}
	
	TIM_Cmd(TIM3, DISABLE);

}

void Servo_pos_per_cycle(void)
{
	uint8_t ui_delay;
	for(uint8_t i = 0; i < MAX_SERVO_NUM; i++)
	{
			pulse_empty[i] |= Read_Home_Switch(i,Servo_dir_private[i]);
		
			if(pulse_empty[i] == 1)
			{
				Servo_pulse(i, 0, Servo_dir_private[i]);
				st_servo_data[i].pulse_total = 0;
			}
			else
			{
					// If initial amount of pulse < 50 then not use Path-planning
					if(st_servo_data[i].cannot_path_planning == 1 )
					{
						Servo_pulse(i, st_servo_data[i].pulse_total, Servo_dir_private[i]);
						st_servo_data[i].pulse_total = 0;
						pulse_empty[i] = 1;
					}
					// If initial amount of pulse > 50 then use Path-planning
					else
					{
						if(st_servo_data[i].pulse_total <= 5)
						{
							Servo_pulse(i, st_servo_data[i].pulse_total, Servo_dir_private[i]);
							st_servo_data[i].pulse_total = 0;
							pulse_empty[i] = 1;							
						}
						else
						{
							Servo_pulse(i,st_servo_data[i].pulse_per_cycle,Servo_dir_private[i]);
							
							st_servo_data[i].pulse_total -= st_servo_data[i].pulse_per_cycle;
						}
					}
				
			}

		}
		GPIO_SetBits(GPIOD, GPIO_Pin_11);
		ui_delay = 10;
		while(ui_delay--);
		GPIO_ResetBits(GPIOD, GPIO_Pin_11);
		
		GPIO_SetBits(GPIOD, GPIO_Pin_11);
		ui_delay = 10;
		while(ui_delay--);
		GPIO_ResetBits(GPIOD, GPIO_Pin_11);
		
		// Update Path-planning pulses for next 1ms-cycle
		for(int i=0;i<MAX_SERVO_NUM;i++)
		{		
			if(st_servo_data[i].pulse_total != 0)
			{
				for(int j=0;j<MATRIX_ORDER;j++)
				{
					a_1[j]=a[i][j];
				}
				st_servo_data[i].pre_t=st_servo_data[i].t;
				st_servo_data[i].t+=0.001f;
				st_servo_data[i].pulse_per_cycle=pulse_pp_cal(a_1, st_servo_data[i].pre_t, st_servo_data[i].t, i);
			}
		}		
}
