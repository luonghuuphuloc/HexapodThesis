#include <stdint.h>
#include <stdbool.h>
#include "stm32f4xx.h"
#include "Calculator.h"
#include <stdio.h>
#include <math.h>
#include "HomeSwitch.h"


float Bytes2float(uint8_t* bytes_input)
{
	float output;
	*((uint8_t*)(&output)+3) =* (bytes_input + 3);
	*((uint8_t*)(&output)+2) =* (bytes_input + 2);
	*((uint8_t*)(&output)+1) =* (bytes_input + 1);
	*((uint8_t*)(&output)+0) =* (bytes_input + 0);
	return output;
}
uint32_t pos2pul(float pos)
{
	return (uint32_t) ((pos * 50000) / 8);
}
float pul2pos(int32_t pul, uint8_t motor_num)
{
	if(motor_num != 1)
		return (((float)pul * 8) / 200000);
	else
		return (((float)pul * 8) / 100000);
}
uint32_t pos2pul_redundance(float pos,uint8_t motor_num)
{
	float pulse_raw = (pos*50000)/8;
	float pulse_redundance_temp = pulse_raw - (uint32_t)pulse_raw + st_servo_data[motor_num].pulse_redundance;
	if(pulse_redundance_temp < 0.5f)
	{
		st_servo_data[motor_num].pulse_redundance = pulse_redundance_temp;
		return (uint32_t)pulse_raw;
	}
	else
	{
		st_servo_data[motor_num].pulse_redundance = pulse_redundance_temp - 1;
		return (uint32_t)pulse_raw + 1;
	}
}
float asc2dou(uint16_t value)
{
	return (float)(value-0x30);
}

float is_minus(uint8_t c)
{
	float ret;
	if(c == '-')
		ret = -1.0f;
	else
		ret = 1.0f;
	
	return ret;	
	
}

void float2Bytes(uint8_t* bytes_temp,float float_variable)
{ 
     *(float*)bytes_temp = float_variable;  
}
void pulse_path_planning(float d,float ks,uint8_t motor_num,float *a)
{
	float tneed=(d/8)/ks; // (s)
	float a_1[MATRIX_ORDER]={0,0,0,0}; //a0 a1 a2 a3 a4 a5

	find_a_factor(a_1,d,tneed);
	for(int i=0;i<MATRIX_ORDER;i++)
	{
		*(a+i)=a_1[i];
	}

}
uint32_t pulse_pp_cal(float a[MATRIX_ORDER],float pre_t,float t,uint8_t motor_num)
{
	float delta_q; // (mm)
	delta_q=q_calculate(t,a)-q_calculate(pre_t,a);
	if(motor_num!=1)
	{
		return pos2pul_redundance(delta_q,motor_num);
	}
	else
	{
		return pos2pul_redundance(delta_q/2,motor_num);
	}
}
float q_calculate(float t,float a[MATRIX_ORDER])
{
	return a[0]+a[1]*t+a[2]*t*t+a[3]*t*t*t+a[4]*t*t*t*t+a[5]*t*t*t*t*t;
}
void find_a_factor(float* a,float d, float tf)
{
		float m[MATRIX_ORDER][MATRIX_ORDER]; //ve trai
		float m_1[MATRIX_ORDER*MATRIX_ORDER];
		float k[MATRIX_ORDER][1]; //ve phai
		float k_1[MATRIX_ORDER];
		float m_inverse_type_1[MATRIX_ORDER*MATRIX_ORDER]; // mang 1 chieu cua ve trai nghich dao

		float a_out[MATRIX_ORDER];
		uint8_t temp=0;
		m[0][0]=1;	m[0][1]=0;	m[0][2]=0;			m[0][3]=0;				
		m[1][0]=0;	m[1][1]=1;	m[1][2]=0;			m[1][3]=0;				
		m[2][0]=1;	m[2][1]=tf;	m[2][2]=tf*tf;	m[2][3]=tf*tf*tf;				
		m[3][0]=0;	m[3][1]=1;	m[3][2]=tf*2;	  m[3][3]=tf*tf*3;	
		for(int i=0;i<MATRIX_ORDER;i++)
		{
			for(int j=0;j<MATRIX_ORDER;j++)
			{
				m_1[temp]=m[i][j];
				temp++;
			}
		}
		matrix_inverse(m_1,m_inverse_type_1);
	//Chuyen tu mang 1 chieu sang 2 chieu cho ve trai nghich dao
		k[0][0]=0;
		k[1][0]=0;
		k[2][0]=d;
		k[3][0]=0;

		temp=0;
		for(int i=0;i<MATRIX_ORDER;i++)
		{
			for(int j=0;j<1;j++)
			{
				k_1[temp]=k[i][j];
				temp++;
			}
		}
		matrix_multiplication(m_inverse_type_1,k_1,MATRIX_ORDER,MATRIX_ORDER,MATRIX_ORDER,1,a_out);
		for(int i=0;i<MATRIX_ORDER;i++)
		{
			*(a+i)=a_out[i];
		}
		
		
}
void matrix_inverse(float m_in_1[MATRIX_ORDER*MATRIX_ORDER],float* m_out)
{
    float ratio,a;
    int i, j, k, n;
		float m_in[MATRIX_ORDER][2*MATRIX_ORDER];
		uint8_t temp=0;

		n=MATRIX_ORDER;
		temp=0;
		for(i = 0; i < n; i++){
        for(j = 0; j < n; j++){
					m_in[i][j]=m_in_1[temp];
					temp++;
        }
    }
    for(i = 0; i < n; i++){
        for(j = n; j < 2*n; j++){
            if(i==(j-n))
                m_in[i][j] = 1.0;
            else
                m_in[i][j] = 0.0;
        }
    }
    for(i = 0; i < n; i++){
        for(j = 0; j < n; j++){
            if(i!=j){
                ratio = m_in[j][i]/m_in[i][i];
                for(k = 0; k < 2*n; k++){
                    m_in[j][k] -= ratio * m_in[i][k];
                }
            }
        }
    }
		
    for(i = 0; i < n; i++){
        a = m_in[i][i];
        for(j = 0; j < 2*n; j++){
            m_in[i][j] /= a;
        }
    }
		
		
		temp=0;
    for(i = 0; i < n; i++){
        for(j = n; j < 2*n; j++){
          *(m_out+temp)=m_in[i][j];
					temp++;
        }
    }

}
void matrix_multiplication(float m_1_1[50],float m_2_1[50],uint8_t m, uint8_t n, uint8_t p, uint8_t q, float* m_out)
{
  int  c, d, k;
	float m_1[m][n],m_2[p][q];
  float  multiply[m][q],sum=0;
	
	uint8_t temp = 0;

	for(int i=0;i<m;i++)
	{
		for(int j=0;j<n;j++)
		{
			m_1[i][j]=m_1_1[temp];
			temp++;
		}
	}
	temp=0;
	for(int i=0;i<p;i++)
	{
		for(int j=0;j<q;j++)
		{
			m_2[i][j]=m_2_1[temp];
			temp++;
		}
	}
  if (n != p)
	;
  else
  {
    for (c = 0; c < m; c++) {
      for (d = 0; d < q; d++) {
        for (k = 0; k < p; k++) {
          sum = sum + m_1[c][k]*m_2[k][d];
        }
 
        multiply[c][d] = sum;
        sum = 0;
      }
    }
 
	uint8_t temp=0;
    for (c = 0; c < m; c++) {
      for (d = 0; d < q; d++)
			{
        //printf("%d\t", multiply[c][d]);
				*(m_out+temp)=multiply[c][d];
				temp++;
      //printf("\n");
			}
		}
	}

}

void matrix_addition(float m_1[50],float m_2[50], uint8_t m,uint8_t n, float *a_out)
{
	 int c, d;
	 float first[m][n], second[m][n], sum[m][n];
 
	 uint8_t temp = 0;
   for (c = 0; c < m; c++)
      for (d = 0; d < n; d++)
			{
        first[c][d] = m_1[temp];
				temp++;
			}
 
	 temp = 0;
   for (c = 0; c < m; c++)
      for (d = 0 ; d < n; d++)
      {
        second[c][d] = m_2[temp];
				temp++;					 
		  }
   
   
   for (c = 0; c < m; c++) {
      for (d = 0 ; d < n; d++) {
         sum[c][d] = first[c][d] + second[c][d];
      }
   }
 
	 temp = 0;
   for (c = 0; c < m; c++)
      for (d = 0 ; d < n; d++)
      {
        *(a_out+temp)=sum[c][d];
				temp++;					 
		  }	 

}

float height_triangle(float a, float b, float c)
{
	float p=(a+b+c)/2;
	return (2 * (sqrt(p*(p-a)*(p-b)*(p-c))/c));
}

float vector_3_norm(float v[3])
{
	return sqrt(v[0]*v[0] + v[1]*v[1] + v[2]*v[2]);
	
}
