#include "stm32f4xx.h"
#include "FSMC.h"
#include "Encoder.h"
#include "stm32f4xx_conf.h"
#include "eeprom.h"
#include "Calculator.h"
#include "HomeSwitch.h"
#include "UART.h"
#include "Servo.h"
static uint16_t cnt_update_enc = 0;
uint32_t countT2;

void ENC_Timer_Init(void)
{
    // Enable clock for TIM2
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);

    // TIM2 initialization overflow every 500ms
    // TIM2 by default has clock of 84MHz
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

    // TIM2 initialize
    TIM_TimeBaseInit(TIM2, &TIM_TimeBaseInitStruct);
    // Enable TIM2 interrupt
    TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);
    // Start TIM2
    TIM_Cmd(TIM2, DISABLE);

    // Nested vectored interrupt settings
    // TIM2 PreemptionPriority = 1 and 
    // SubPriority = 0)
    NVIC_InitTypeDef NVIC_InitStruct;
    NVIC_InitStruct.NVIC_IRQChannel = TIM2_IRQn;
    NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 2;
    NVIC_InitStruct.NVIC_IRQChannelSubPriority = 1;
    NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStruct);

		
		
}
void ENC_Reset(void)
{
	//reset counter in CPLD
		GPIO_SetBits(GPIOD, GPIO_Pin_2);
		uint8_t ui_delay = 10;
		while(ui_delay--);
		GPIO_ResetBits(GPIOD, GPIO_Pin_2);
}
void TIM2_IRQHandler(void)
{
    // Checks whether the TIM2 interrupt has occurred or not
    if (TIM_GetITStatus(TIM2, TIM_IT_Update))
    {

			countT2++;
			if(countT2 == 10000)
				countT2 = 0;
      FSMC_ENC_Update_Pos();
			cnt_update_enc += 1;
			if (cnt_update_enc == 100)
			{

				UART_Send_PC_Encoder_Pos();

				Ex_Usart_SendData(str_tx_uart);			
				
				cnt_update_enc = 0;
			}
			
        // Clears the TIM2 interrupt pending bit
      TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
    }
		
}
