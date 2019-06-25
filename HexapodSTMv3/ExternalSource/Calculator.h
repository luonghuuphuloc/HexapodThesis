#include <stdint.h>
#include <stdbool.h>
#include "stm32f4xx.h"
#include <stdio.h>
#include <math.h>
#ifndef __CALCULATOR_H
#define __CALCULATOR_H
#ifdef __cplusplus
 extern "C" {
#endif
#define MATRIX_ORDER 4
#define pi 3.14159265359f

float Bytes2float(uint8_t* bytes_input);

uint32_t pos2pul(float pos);

uint32_t pos2pul_redundance(float pos,uint8_t motor_num);

float asc2dou(uint16_t value);

float is_minus(uint8_t c);

void float2Bytes(uint8_t* bytes_temp,float float_variable);

void find_a_factor(float* a,float d, float tf);

void pulse_path_planning(float d,float ks,uint8_t motor_num,float *a);

void matrix_inverse(float m_in[36],float *m_out);

void matrix_multiplication(float m_1_1[50],float m_2_1[50],uint8_t m, uint8_t n, uint8_t p, uint8_t q, float* m_out); 

void matrix_addition(float m_1[50],float m_2[50], uint8_t m,uint8_t n, float *a_out);

float height_triangle(float a, float b, float c);

float vector_3_norm(float v[3]);

float q_calculate(float t,float a[6]);

uint32_t pulse_pp_cal(float a[6],float pre_t,float t,uint8_t motor_num);

float pul2pos(int32_t pul, uint8_t motor_num);

//function declaration for holding determinant of A 

#ifdef __cplusplus
}
#endif

#endif 


