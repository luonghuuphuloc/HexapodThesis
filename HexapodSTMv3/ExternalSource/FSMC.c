
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "stm32f4xx.h"
#include "stm32f4xx_conf.h"
#include "FSMC.h"
#include "Calculator.h"
#include "Servo.h"
#include "HomeSwitch.h"

static int32_t enc_dp[MAX_SERVO_NUM] = {0, 0, 0, 0, 0, 0};
static uint32_t enc_p0[MAX_SERVO_NUM] = {0, 0, 0, 0, 0, 0}; 
static uint32_t enc_p1[MAX_SERVO_NUM] = {0, 0, 0, 0, 0, 0};


void FSMC_Init(void)
{
	FSMC_NORSRAMInitTypeDef FSMC_InitStructure, *FSMC_NORSRAMInitStructure;
	FSMC_NORSRAMInitStructure = &FSMC_InitStructure;
	
	GPIO_InitTypeDef GPIO_InitStructure;
	
	/* 1. Enable the clock for the FSMC and associated GPIOs */
	RCC_AHB3PeriphClockCmd(RCC_AHB3Periph_FSMC, ENABLE);
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);
	
	/* 2. FSMC pins configuration */
	//enable alternate function FSMC at pins
	//PD0: AD2, PD1: AD3, PD4: NOE, PD5: NWE
	GPIO_PinAFConfig(GPIOD, GPIO_PinSource0, GPIO_AF_FSMC);
	GPIO_PinAFConfig(GPIOD, GPIO_PinSource1, GPIO_AF_FSMC);
	GPIO_PinAFConfig(GPIOD, GPIO_PinSource4, GPIO_AF_FSMC);
	GPIO_PinAFConfig(GPIOD, GPIO_PinSource5, GPIO_AF_FSMC);
	//PD7: CS, PD8: AD13, PD9: AD14, PD10: AD15 
	GPIO_PinAFConfig(GPIOD, GPIO_PinSource7, GPIO_AF_FSMC);
	GPIO_PinAFConfig(GPIOD, GPIO_PinSource8, GPIO_AF_FSMC);
	GPIO_PinAFConfig(GPIOD, GPIO_PinSource9, GPIO_AF_FSMC);
	GPIO_PinAFConfig(GPIOD, GPIO_PinSource10, GPIO_AF_FSMC);
	//PD14: AD0, PD15: AD1
	GPIO_PinAFConfig(GPIOD, GPIO_PinSource14, GPIO_AF_FSMC);
	GPIO_PinAFConfig(GPIOD, GPIO_PinSource15, GPIO_AF_FSMC);
	
	//PE7: AD4, PE8: AD5, PE9: AD6, PE10: AD7, PE11: AD8, PE12: AD9, PE13: AD10, PE14: AD11, PE15: AD12
	GPIO_PinAFConfig(GPIOE, GPIO_PinSource7, GPIO_AF_FSMC);
	GPIO_PinAFConfig(GPIOE, GPIO_PinSource8, GPIO_AF_FSMC);
	GPIO_PinAFConfig(GPIOE, GPIO_PinSource9, GPIO_AF_FSMC);
	GPIO_PinAFConfig(GPIOE, GPIO_PinSource10, GPIO_AF_FSMC);
	GPIO_PinAFConfig(GPIOE, GPIO_PinSource11, GPIO_AF_FSMC);
	GPIO_PinAFConfig(GPIOE, GPIO_PinSource12, GPIO_AF_FSMC);
	GPIO_PinAFConfig(GPIOE, GPIO_PinSource13, GPIO_AF_FSMC);
	GPIO_PinAFConfig(GPIOE, GPIO_PinSource14, GPIO_AF_FSMC);
	GPIO_PinAFConfig(GPIOE, GPIO_PinSource15, GPIO_AF_FSMC);
	
	//PB7: NADV
	GPIO_PinAFConfig(GPIOB, GPIO_PinSource7, GPIO_AF_FSMC);
	
	//config IO
	GPIO_InitStructure.GPIO_Pin = 	GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_4 | GPIO_Pin_5 | \
																	GPIO_Pin_7 | GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10 | \
																	GPIO_Pin_14 | GPIO_Pin_15;
	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOD, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = 	GPIO_Pin_7 | GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10| \
																	GPIO_Pin_11 | GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;
	GPIO_Init(GPIOE, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	/* 3. Declare a FSMCInitStruct structure */
	FSMC_NORSRAMInitStructure->FSMC_Bank = 																							FSMC_Bank1_NORSRAM1;
	FSMC_NORSRAMInitStructure->FSMC_DataAddressMux = 																		FSMC_DataAddressMux_Enable;
	FSMC_NORSRAMInitStructure->FSMC_MemoryType = 																				FSMC_MemoryType_NOR;
	FSMC_NORSRAMInitStructure->FSMC_MemoryDataWidth = 																	FSMC_MemoryDataWidth_16b;
	FSMC_NORSRAMInitStructure->FSMC_BurstAccessMode = 																	FSMC_BurstAccessMode_Disable;
	FSMC_NORSRAMInitStructure->FSMC_AsynchronousWait = 																	FSMC_AsynchronousWait_Disable;
	FSMC_NORSRAMInitStructure->FSMC_WaitSignalPolarity = 																FSMC_WaitSignalPolarity_Low;
	FSMC_NORSRAMInitStructure->FSMC_WrapMode = 																					FSMC_WrapMode_Disable;
	FSMC_NORSRAMInitStructure->FSMC_WaitSignalActive = 																	FSMC_WaitSignalActive_BeforeWaitState;
	FSMC_NORSRAMInitStructure->FSMC_WriteOperation = 																		FSMC_WriteOperation_Enable;
	FSMC_NORSRAMInitStructure->FSMC_WaitSignal = 																				FSMC_WaitSignal_Disable;
	FSMC_NORSRAMInitStructure->FSMC_ExtendedMode = 																			FSMC_ExtendedMode_Disable;
	FSMC_NORSRAMInitStructure->FSMC_WriteBurst = 																				FSMC_WriteBurst_Disable;
	
	//when extend mode disable, we need some more configure code
	FSMC_NORSRAMInitStructure->FSMC_ReadWriteTimingStruct->FSMC_AddressSetupTime = 			0xF;
	FSMC_NORSRAMInitStructure->FSMC_ReadWriteTimingStruct->FSMC_AddressHoldTime = 			0xF;
	FSMC_NORSRAMInitStructure->FSMC_ReadWriteTimingStruct->FSMC_DataSetupTime = 				0xF;
	FSMC_NORSRAMInitStructure->FSMC_ReadWriteTimingStruct->FSMC_BusTurnAroundDuration = 0x0;
	FSMC_NORSRAMInitStructure->FSMC_ReadWriteTimingStruct->FSMC_CLKDivision = 					0x0;
	FSMC_NORSRAMInitStructure->FSMC_ReadWriteTimingStruct->FSMC_DataLatency = 					0x0;
	FSMC_NORSRAMInitStructure->FSMC_ReadWriteTimingStruct->FSMC_AccessMode = 						FSMC_AccessMode_C; 
	
	FSMC_NORSRAMInitStructure->FSMC_WriteTimingStruct->FSMC_AddressSetupTime = 					0xF;
	FSMC_NORSRAMInitStructure->FSMC_WriteTimingStruct->FSMC_AddressHoldTime = 					0xF;
	FSMC_NORSRAMInitStructure->FSMC_WriteTimingStruct->FSMC_DataSetupTime = 						0x20;//0xF;
	FSMC_NORSRAMInitStructure->FSMC_WriteTimingStruct->FSMC_BusTurnAroundDuration = 		0x0;
	FSMC_NORSRAMInitStructure->FSMC_WriteTimingStruct->FSMC_CLKDivision = 							0x0;
	FSMC_NORSRAMInitStructure->FSMC_WriteTimingStruct->FSMC_DataLatency = 							0x0;
	FSMC_NORSRAMInitStructure->FSMC_WriteTimingStruct->FSMC_AccessMode = 								FSMC_AccessMode_C;
	
	/* 4. Initialize the FSMC Controller by calling the function */
	FSMC_NORSRAMInit(&FSMC_InitStructure);
	FSMC_Bank1->BTCR[1] = 0x20010303;
	
	/* 5. Then enable the NOR/SRAM Bank */
	FSMC_NORSRAMCmd(FSMC_Bank1_NORSRAM1, ENABLE);
	
	/* 6. Config some pin for control read and write data */
	//PD2: Encoder reset, PD12: Pulse write enable
	GPIO_InitStructure.GPIO_Pin 	= GPIO_Pin_2 | GPIO_Pin_11;
	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOD, &GPIO_InitStructure);
	GPIO_ResetBits(GPIOD, GPIO_Pin_2);
	//PD13: Busy signal
	GPIO_InitStructure.GPIO_Pin 	= GPIO_Pin_3;
	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_IN;
	GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOD, &GPIO_InitStructure);
	
}
void Servo_pulse(uint8_t Servo_num, uint32_t i_pulse_1, uint32_t Dir_1)
{
	
	uint32_t ui_delay;
	uint32_t ui_pulse_out = 0;


		if(i_pulse_1 > d_MAX_PULSE_PER_PERIOD)
		{
			i_pulse_1 = d_MAX_PULSE_PER_PERIOD;
		}
			
		ui_pulse_out = (Dir_1 << 7); //Chon chieu quay
		ui_pulse_out += i_pulse_1;
		
		FSMC_Write(d_PULSE_BASE_ADDR+Servo_num*2, ui_pulse_out);

		ui_pulse_out = 0;
		ui_delay = 100;
		while(ui_delay--);


	
}
void FSMC_Write(uint32_t ui_address, uint32_t ui_data)
{
	*(volatile uint16_t *)ui_address = ui_data;  
}
void FSMC_ENC_Update_Pos(void)
{
	//float servo_pulse_offset[MAX_SERVO_NUM] = {1, 1, 1, 1, 1, 1};
	for(int index = 0; index < MAX_SERVO_NUM; index++)
	{
		enc_p0[index] = (int32_t)FSMC_Read(index); // get counter value from CPLD
		//compute the counter's difference between 1 control period 1ms
		enc_dp[index] = (enc_p0[index] - enc_p1[index]);
		// in case forward overflow the counter, >65536 will reset to 0 
		if (enc_dp[index] < -32768 )
			enc_dp[index] += 65536;
		// in case reverse overflow the counter, <0 will reset to 65536 
		else if (enc_dp[index] > 32768) 
			enc_dp[index] -= 65536;
		//update storage value
		enc_p1[index] = enc_p0[index];
		// update the accumulative position 
		st_servo_data[index].enc_cur_pos += pul2pos(enc_dp[index], index);
		st_servo_data[index].set_pos += enc_dp[index];

	}		
}
void FSMC_ENC_Reset(void)
{
	for(int index = 0; index < MAX_SERVO_NUM; index++)
	{

		st_servo_data[index].enc_cur_pos = HOME_OFFSET[index] ;
		st_servo_data[index].set_pos = 0.0f;
		enc_dp[index] = 0;
		enc_p0[index] = 0;
		enc_p1[index] = 0;
	}
}


float FSMC_ENC_Get_Vel(uint8_t motor_num)
{
	if(motor_num >= MAX_SERVO_NUM)
		return 0;
	float temp;
	switch(motor_num)
	{
		case SERVO0:
			temp = enc_dp[SERVO0] * c_PULSE_TO_POS / c_CONTROL_PERIOD;
		break;
		case SERVO1:
			temp = enc_dp[SERVO1] * c_PULSE_TO_POS / c_CONTROL_PERIOD;
		break;
		case SERVO2:
			temp = enc_dp[SERVO2] * c_PULSE_TO_POS / c_CONTROL_PERIOD;
		break;
		case SERVO3:
			temp = enc_dp[SERVO3] * c_PULSE_TO_POS / c_CONTROL_PERIOD;
		break;
		case SERVO4:
			temp = enc_dp[SERVO4] * c_PULSE_TO_POS / c_CONTROL_PERIOD;
		break;
		case SERVO5:
			temp = enc_dp[SERVO5] * c_PULSE_TO_POS / c_CONTROL_PERIOD;
		break;
	}
	return temp;
}

uint16_t FSMC_Read(uint32_t ui_enc_channel)
{
    /*
        + HADDR are internal AHB address lines that are translated to external memory 
        + NOR/PSRAM address mapping:
            - Bank select: HADDR[27:26]
                . 00, 01, 10, 11: Bank 1 NOR/PSRAM 1,2,3,4
            - Data width & external memory: HADDR[25:0]
                . 16 bit: HADDR[25:1]>>1 --> FSMC uses HADDR[25:1] to generate the address for external memory FSMC_A[24:0]  
            - BANK_NOR_ADDR
        + 4 encoder channnels have 4 address: 0x00,0x01,0x02,0x03
    */
    uint32_t address;
    uint16_t res = 0;

    address = (d_ENC_BASE_ADDR + (ui_enc_channel<<1));
    res = *(volatile uint16_t *)address;   // casting the address to pointer then get value in this address
    return res;
}
	 

