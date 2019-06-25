
#include "stm32f4xx.h"
#include "system_timetick.h"
#include "UART.h"
#include "FSMC.h"
#include "eeprom.h"
#include "utils.h"
#include "Servo.h"
#include "Calculator.h"
#include "OperationMode.h"
#include "HomeSwitch.h"
#include "Kinematic.h"
#include "Encoder.h"
#include <string.h>
bool rx_flag = 0;
bool rx_flag_android = 0;

bool update_cmd_busy_flag;
bool update_cmd_busy_flag_android;

uint16_t save_pos_count = 0;

bool vSGUI_ready_flag = 0;
bool android_ready_flag = 0;

static bool isPCRunning = 0;
static bool isAndroidRunning = 0;

float HOME_OFFSET[6];
float MAX_OF_TRIP[6];
char str_tx_uart[500];
char str_tx_uart_android[500];

void Uart_Program(void);
void Uart_Program_android(void);
void ApplyCmd(void);
void ApplyCmd_android(void);

char p;

HEXAPOD_DATA_STRUCT st_hexapod_data;

int main()
{		
	Mode = IDLE;
	update_cmd_busy_flag = 0;
	update_cmd_busy_flag_android = 0;
	
	uint32_t ui_delay;
	UART_DMA_Init();
	UART_DMA_Init_android();

	//Home Off set for Servo
	HOME_OFFSET[0] = 33.65f;
	HOME_OFFSET[1] = 34.29f;
	HOME_OFFSET[2] = 30.39f;
	HOME_OFFSET[3] = 28.73f;
	HOME_OFFSET[4] = 31.57f;
	HOME_OFFSET[5] = 31.77f;
	
	MAX_OF_TRIP[0] = 144.977f;
	MAX_OF_TRIP[1] = 150.024f;
	MAX_OF_TRIP[2] = 146.865f;
	MAX_OF_TRIP[3] = 140.612f;
	MAX_OF_TRIP[4] = 147.100f;
	MAX_OF_TRIP[5] = 147.818f;
	
	uint8_t Pos_save_in_byte[4];
	
	//Init..................................................................................
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	
	FSMC_Init();
	EEP_Init();
	Servo_Home_Switch_Init();


	for(int i=0;i<MAX_SERVO_NUM;i++)
	{		
		EEP_ReadBytes(Pos_save_in_byte,i*4,4);
		Servo_pos_pre[i]=Bytes2float(Pos_save_in_byte);
		st_servo_data[i].enc_cur_pos = Servo_pos_pre[i];
	}
	
	for(int i=0;i<6;i++)
	{
		Servo_pos_distance[i]=0;
		Servo_dir[i]=0;

	}
	
 

	// Timer Initial must be placed here
	Servo_Control_Timer_Init();
	
	ENC_Timer_Init();
	ENC_Reset();
	
	Uart_Cmd_Update("\n");
	Ex_Usart_SendData(str_tx_uart);
	//........................................finish Init and enable timer2 for encoder cheking
	TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
	TIM_Cmd(TIM2, ENABLE);
	

	//Start hand-shaking GUI.........................................................
	vSGUI_ready_flag = 0;	
	android_ready_flag = 0;
	
	isPCRunning = 0;
	isAndroidRunning = 0;
	
	
	while(!(vSGUI_ready_flag | android_ready_flag))
	{
		Uart_Cmd_Update("lSTM Ready-");
		Uart_Cmd_Update_android("s_lSTM Ready-");
		ui_delay = 168000000/2;
		while(ui_delay--);
	}	
//	if(vSGUI_ready_flag)
//		Uart_Cmd_Update("lSTM and VSGUI connected-");
//	else if(android_ready_flag)
//		Uart_Cmd_Update_android("s_lSTM and Android connected-");
	
	//State machine loop.....................................................
	rx_flag = 0;
	rx_flag_android = 0;
	
	while(1)
	{
		if (rx_flag)
			{
				switch(Mode)
				{
					case IDLE:
						//Meanwhile, Timer2 keeps counting and update to GUI
						IdleMode();
						break;
					case TESTING:
						TestingMode();
						break;
					case HOMESCAN:
						HomeScanMode();
						break;
					case INVERSEKINEMATIC:
						InverseKinematicMode();
						break;
					default:
						break;
				}
				rx_flag=0;
			}
		else if(rx_flag_android)
	{
			switch(Mode)
			{
				case IDLE:
					//Meanwhile, Timer2 keeps counting and update to GUI
					IdleMode();
					break;
				case TESTING:
					TestingMode();
					break;
				case HOMESCAN:
					HomeScanMode();
					break;
				case INVERSEKINEMATIC:
					InverseKinematicMode();
					break;
				default:
					break;
			}
			rx_flag_android = 0;
		}
	}
}


//Receiving interrupt by DMA.......................................................
void DMA1_Stream1_IRQHandler(void)
{	
	DMA_Cmd(DMA1_Stream1, DISABLE);
	/* Clear the DMA1_Stream1 TCIF1 pending bit */
  DMA_ClearITPendingBit(DMA1_Stream1, DMA_IT_TCIF1);
	
	if((rxbuff[0] == 'p') && (rxbuff[1] == '-') && (rxbuff[51] == 0x0A ))
		Uart_Program();
	else
	{
		memset(rxbuff, 0, 52);
		rx_flag = 0;
	}
	//rx_flag = 1;

	DMA_Cmd(DMA1_Stream1, ENABLE);	
	
}
//Receiving interrupt by DMA.......................................................
void DMA2_Stream2_IRQHandler(void)
{	
	DMA_Cmd(DMA2_Stream2, DISABLE);
	/* Clear the DMA2_Stream2 TCIF2 pending bit */
  DMA_ClearITPendingBit(DMA2_Stream2, DMA_IT_TCIF2);

	if((rxbuff_android[0] == 'a') && (rxbuff_android[1] == '-') && (rxbuff_android[51] == 0x0A ))		
		Uart_Program_android();
	else
	{
		memset(rxbuff_android, 0, 52);
		rx_flag_android = 0;
	}	
	//rx_flag_android = 1;

	DMA_Cmd(DMA2_Stream2, ENABLE);	
	
}
//.........................................................................

//Handling Uart data from GUI
void Uart_Program(void)
{
		if(isAndroidRunning)
		{
			Uart_Cmd_Update("lAndroid is running-");
			Uart_Cmd_Update_android("s_lPIW-"); // PC is waiting
			isAndroidRunning = 1;
			isPCRunning = 0;
			rx_flag = 0;
		}
		else
		{
			isAndroidRunning = 0;
			isPCRunning = 1;
			ApplyCmd();
			rx_flag = 1;
		}
}

void Uart_Program_android(void)
{
		if(isPCRunning)
		{
			Uart_Cmd_Update("lAndroid is waiting-");
			Uart_Cmd_Update_android("s_lPIR-"); //PC is running
			isAndroidRunning = 0;
			isPCRunning = 1;
			rx_flag_android = 0;
		}
		else
		{
			isAndroidRunning = 1;
			isPCRunning = 0;
			ApplyCmd_android();
			rx_flag_android = 1;
		}
}

void ApplyCmd(void)
{
	uint8_t Pos_save_in_byte[4];

	switch(rxbuff[2])
	{
		
		case 'c': // Hand shake
		{
			if(rxbuff[3] == 'r')
			{
				if(isAndroidRunning)
				{
					vSGUI_ready_flag = 0;
					android_ready_flag = 1;
				}
				else if(isPCRunning)
				{
					Uart_Cmd_Update("lSTM and VSGUI connected-");
					Uart_Cmd_Update_android("s_lPIR-"); //PC is running
					isAndroidRunning = 0;
					isPCRunning = 1;
					android_ready_flag = 0;
					vSGUI_ready_flag = 1;
				}
			}
			else if(rxbuff[3] == 'd')
			{
				isPCRunning = 0;
				isAndroidRunning = 0;
				Uart_Cmd_Update("lTracking Mode activated-");
				Uart_Cmd_Update_android("s_lPID-"); //PC is disconnected	
				Mode = IDLE;
			}
			break;
		}
		case 't': // Testing Mode
		{
			Servo_pos_cur[0]=asc2dou(rxbuff[4])*100+asc2dou(rxbuff[5])*10+asc2dou(rxbuff[6])+asc2dou(rxbuff[8])/10+asc2dou(rxbuff[9])/100+asc2dou(rxbuff[10])/1000;
			Servo_pos_cur[1]=asc2dou(rxbuff[11])*100+asc2dou(rxbuff[12])*10+asc2dou(rxbuff[13])+asc2dou(rxbuff[15])/10+asc2dou(rxbuff[16])/100+asc2dou(rxbuff[17])/1000;
			Servo_pos_cur[2]=asc2dou(rxbuff[18])*100+asc2dou(rxbuff[19])*10+asc2dou(rxbuff[20])+asc2dou(rxbuff[22])/10+asc2dou(rxbuff[23])/100+asc2dou(rxbuff[24])/1000;
			Servo_pos_cur[3]=asc2dou(rxbuff[25])*100+asc2dou(rxbuff[26])*10+asc2dou(rxbuff[27])+asc2dou(rxbuff[29])/10+asc2dou(rxbuff[30])/100+asc2dou(rxbuff[31])/1000;
			Servo_pos_cur[4]=asc2dou(rxbuff[32])*100+asc2dou(rxbuff[33])*10+asc2dou(rxbuff[34])+asc2dou(rxbuff[36])/10+asc2dou(rxbuff[37])/100+asc2dou(rxbuff[38])/1000;
			Servo_pos_cur[5]=asc2dou(rxbuff[39])*100+asc2dou(rxbuff[40])*10+asc2dou(rxbuff[41])+asc2dou(rxbuff[43])/10+asc2dou(rxbuff[44])/100+asc2dou(rxbuff[45])/1000;

			Mode=TESTING;
			break;
		}
		
		case 'h': // Home scan Mode
		{
			if(rxbuff[3]=='s') //set direction to home switch
			{
				// Reset Home Status
				Home_Scan_Begin();
				//Set HOMESCAN next state after setting direction
				Mode=HOMESCAN;
				
				for(int i=0;i<6;i++)
				{
					
					if(rxbuff[i+5]=='l') //To the left
					{
						if((i==0)||(i==2)||(i==4))
						{
							Servo_pos_cur[i]=150;
							Servo_pos_pre[i]=0;
						}
						else
						{
							Servo_pos_cur[i] = 0;
							Servo_pos_pre[i] = 150;
						}
					}
					else if(rxbuff[i+5]=='r') // To the right
					{
						if((i==0)||(i==2)||(i==4))
						{
							Servo_pos_cur[i] = 0;
							Servo_pos_pre[i] = 150;		
						}			
						else
						{
							Servo_pos_cur[i] = 150;
							Servo_pos_pre[i] = 0;							
						}							
					}
				}
				
			}
			else if(rxbuff[3] == 'e') //Set home offset for each nuts		
			{

					for(int i=0;i<MAX_SERVO_NUM;i++)
					{		
						
						Servo_pos_cur[i] = HOME_OFFSET[i] ;
						Servo_pos_pre[i] = HOME_OFFSET[i] ;
						
						
						//save current position to EEPROM
						float2Bytes(Pos_save_in_byte , 	HOME_OFFSET[i]);
						EEP_WriteBytes(Pos_save_in_byte , i*4, 4);

					}
					
				//Reset encoder
				ENC_Reset();
				FSMC_ENC_Reset();

					
				//Set IDLE next state	
				Mode=IDLE;
			}
			break;
		}
		
		case 'k': // Test Kinematic Mode
		{
			if(rxbuff[3]=='i')
			{
				st_hexapod_data.x = is_minus(rxbuff[4])*(asc2dou(rxbuff[5])*10+asc2dou(rxbuff[6])+asc2dou(rxbuff[8])/10+asc2dou(rxbuff[9])/100+asc2dou(rxbuff[10])/1000);
				st_hexapod_data.y = is_minus(rxbuff[11])*(asc2dou(rxbuff[12])*10+asc2dou(rxbuff[13])+asc2dou(rxbuff[15])/10+asc2dou(rxbuff[16])/100+asc2dou(rxbuff[17])/1000);
				st_hexapod_data.z = is_minus(rxbuff[18])*(asc2dou(rxbuff[19])*10+asc2dou(rxbuff[20])+asc2dou(rxbuff[22])/10+asc2dou(rxbuff[23])/100+asc2dou(rxbuff[24])/1000);
				st_hexapod_data.roll = is_minus(rxbuff[25])*(asc2dou(rxbuff[26])*10+asc2dou(rxbuff[27])+asc2dou(rxbuff[29])/10+asc2dou(rxbuff[30])/100+asc2dou(rxbuff[31])/1000);
				st_hexapod_data.pitch = is_minus(rxbuff[32])*(asc2dou(rxbuff[33])*10+asc2dou(rxbuff[34])+asc2dou(rxbuff[36])/10+asc2dou(rxbuff[37])/100+asc2dou(rxbuff[38])/1000);
				st_hexapod_data.yaw = is_minus(rxbuff[39])*(asc2dou(rxbuff[40])*10+asc2dou(rxbuff[41])+asc2dou(rxbuff[43])/10+asc2dou(rxbuff[44])/100+asc2dou(rxbuff[45])/1000);
			
				Mode = INVERSEKINEMATIC;
				break;
			}			
		}
		
		case 's': // Save position Mode
		{
			for(int i = 0; i < MAX_SERVO_NUM ; i++)
			{
				float2Bytes(Pos_save_in_byte , 	st_servo_data[i].enc_cur_pos);
				EEP_WriteBytes(Pos_save_in_byte , i*4, 4);
			}
			
			Uart_Cmd_Update("lI saved the position successfully-");
			Uart_Cmd_Update_android("s_lISTPS-"); // I saved the position successfully
			Mode = IDLE;
			break;
		}
		
	}
}

void ApplyCmd_android(void)
{
	uint8_t Pos_save_in_byte[4];

	switch(rxbuff_android[2])
	{
		
		case 'c': // Hand shake
		{
			if(rxbuff_android[3] == 'r')
			{
				if(isAndroidRunning)
				{
					Uart_Cmd_Update("lAndroid is running-");
					Uart_Cmd_Update_android("s_lSAAC-"); //STM and Android connected
					isAndroidRunning = 1;
					isPCRunning = 0;
					vSGUI_ready_flag = 0;
					android_ready_flag = 1;
				}
				else if(isPCRunning)
				{
					android_ready_flag = 0;
					vSGUI_ready_flag = 1;
				}
			}
			else if(rxbuff_android[3] == 'd')
			{
				isPCRunning = 0;
				isAndroidRunning = 0;
				Uart_Cmd_Update("lAndroid is disconnected-");
				Uart_Cmd_Update_android("s_lTMA-"); //Tracking Mode activated
				Mode = IDLE;				
			}
			break;
		}
		case 't': // Testing Mode
		{
			Servo_pos_cur[0]=asc2dou(rxbuff_android[4])*100+asc2dou(rxbuff_android[5])*10+asc2dou(rxbuff_android[6])+asc2dou(rxbuff_android[8])/10+asc2dou(rxbuff_android[9])/100+asc2dou(rxbuff_android[10])/1000;
			Servo_pos_cur[1]=asc2dou(rxbuff_android[11])*100+asc2dou(rxbuff_android[12])*10+asc2dou(rxbuff_android[13])+asc2dou(rxbuff_android[15])/10+asc2dou(rxbuff_android[16])/100+asc2dou(rxbuff_android[17])/1000;
			Servo_pos_cur[2]=asc2dou(rxbuff_android[18])*100+asc2dou(rxbuff_android[19])*10+asc2dou(rxbuff_android[20])+asc2dou(rxbuff_android[22])/10+asc2dou(rxbuff_android[23])/100+asc2dou(rxbuff_android[24])/1000;
			Servo_pos_cur[3]=asc2dou(rxbuff_android[25])*100+asc2dou(rxbuff_android[26])*10+asc2dou(rxbuff_android[27])+asc2dou(rxbuff_android[29])/10+asc2dou(rxbuff_android[30])/100+asc2dou(rxbuff_android[31])/1000;
			Servo_pos_cur[4]=asc2dou(rxbuff_android[32])*100+asc2dou(rxbuff_android[33])*10+asc2dou(rxbuff_android[34])+asc2dou(rxbuff_android[36])/10+asc2dou(rxbuff_android[37])/100+asc2dou(rxbuff_android[38])/1000;
			Servo_pos_cur[5]=asc2dou(rxbuff_android[39])*100+asc2dou(rxbuff_android[40])*10+asc2dou(rxbuff_android[41])+asc2dou(rxbuff_android[43])/10+asc2dou(rxbuff_android[44])/100+asc2dou(rxbuff_android[45])/1000;

			Mode=TESTING;
			break;
		}
		
		case 'h': // Home scan Mode
		{
			if(rxbuff_android[3]=='s') //set direction to home switch
			{
				// Reset Home Status
				Home_Scan_Begin();
				//Set HOMESCAN next state after setting direction
				Mode=HOMESCAN;
				
				for(int i=0;i<6;i++)
				{
					
					if(rxbuff_android[i+5]=='l') //To the left
					{
						if((i==0)||(i==2)||(i==4))
						{
							Servo_pos_cur[i]=150;
							Servo_pos_pre[i]=0;
						}
						else
						{
							Servo_pos_cur[i] = 0;
							Servo_pos_pre[i] = 150;
						}
					}
					else if(rxbuff_android[i+5]=='r') // To the right
					{
						if((i==0)||(i==2)||(i==4))
						{
							Servo_pos_cur[i] = 0;
							Servo_pos_pre[i] = 150;		
						}			
						else
						{
							Servo_pos_cur[i] = 150;
							Servo_pos_pre[i] = 0;							
						}							
					}
				}
				
			}
			else if(rxbuff_android[3] == 'e') //Set home offset for each nuts		
			{

					for(int i=0;i<MAX_SERVO_NUM;i++)
					{		
						
						Servo_pos_cur[i] = HOME_OFFSET[i] ;
						Servo_pos_pre[i] = HOME_OFFSET[i] ;
						
						
						//save current position to EEPROM
						float2Bytes(Pos_save_in_byte , 	HOME_OFFSET[i]);
						EEP_WriteBytes(Pos_save_in_byte , i*4, 4);

					}
					
				//Reset encoder
				ENC_Reset();
				FSMC_ENC_Reset();

					
				//Set IDLE next state	
				Mode=IDLE;
			}
			break;
		}
		
		case 'k': // Test Kinematic Mode
		{
			if(rxbuff_android[3]=='i')
			{
				st_hexapod_data.x = is_minus(rxbuff_android[4])*(asc2dou(rxbuff_android[5])*10+asc2dou(rxbuff_android[6])+asc2dou(rxbuff_android[8])/10+asc2dou(rxbuff_android[9])/100+asc2dou(rxbuff_android[10])/1000);
				st_hexapod_data.y = is_minus(rxbuff_android[11])*(asc2dou(rxbuff_android[12])*10+asc2dou(rxbuff_android[13])+asc2dou(rxbuff_android[15])/10+asc2dou(rxbuff_android[16])/100+asc2dou(rxbuff_android[17])/1000);
				st_hexapod_data.z = is_minus(rxbuff_android[18])*(asc2dou(rxbuff_android[19])*10+asc2dou(rxbuff_android[20])+asc2dou(rxbuff_android[22])/10+asc2dou(rxbuff_android[23])/100+asc2dou(rxbuff_android[24])/1000);
				st_hexapod_data.roll = is_minus(rxbuff_android[25])*(asc2dou(rxbuff_android[26])*10+asc2dou(rxbuff_android[27])+asc2dou(rxbuff_android[29])/10+asc2dou(rxbuff_android[30])/100+asc2dou(rxbuff_android[31])/1000);
				st_hexapod_data.pitch = is_minus(rxbuff_android[32])*(asc2dou(rxbuff_android[33])*10+asc2dou(rxbuff_android[34])+asc2dou(rxbuff_android[36])/10+asc2dou(rxbuff_android[37])/100+asc2dou(rxbuff_android[38])/1000);
				st_hexapod_data.yaw = is_minus(rxbuff_android[39])*(asc2dou(rxbuff_android[40])*10+asc2dou(rxbuff_android[41])+asc2dou(rxbuff_android[43])/10+asc2dou(rxbuff_android[44])/100+asc2dou(rxbuff_android[45])/1000);
			
				Mode = INVERSEKINEMATIC;
				break;
			}			
		}
		
		case 's': // Save position Mode
		{
			for(int i = 0; i < MAX_SERVO_NUM ; i++)
			{
				float2Bytes(Pos_save_in_byte , 	st_servo_data[i].enc_cur_pos);
				EEP_WriteBytes(Pos_save_in_byte , i*4, 4);
			}
			
			Uart_Cmd_Update("lI saved the position successfully-");
			Uart_Cmd_Update_android("s_lISTPS-"); //I saved the position successfully
			Mode = IDLE;
			break;
		}
		
	}
}
