#include <stdint.h>
#include <stdbool.h>
#include "Kinematic.h"
#include <math.h>
#include "Calculator.h"
void inverse_kinematic(float pos_in[3],float matR_in[9],float q[6])
{
	float p0[3];
	float p1[3];
	float p2[3];
	float b0[3];
	float b1[3];
	float b2[3];
	float matR_x_p0[3];
	float matR_x_p1[3];
	float matR_x_p2[3];
	float pos_minus_b0[3];
	float pos_minus_b1[3];
	float pos_minus_b2[3];
	float l_0[3];
	float l_1[3];
	float l_2[3];
	float l_3[3];
	float l_4[3];
	float l_5[3];
	float l_norm[6];
	float h[6];
	
	p0[0] =  0 	 					; p0[1] =  Lp*sqrt(3)/3 			  ; p0[2] = 0 ; 
	p1[0] = -Lp/2 			; p1[1] = -Lp*sqrt(3)/6 				; p1[2] = 0 ; 
	p2[0] =  Lp/2				; p2[1] = -Lp*sqrt(3)/6				  ; p2[2] = 0 ; 
	
	b0[0] =  Lb/2 	; b0[1] = -Lb*sqrt(3)/6 ; b0[2] = 0 ; 
	b1[0] = 		0 	; b1[1] = Lb*sqrt(3)/3  ; b1[2] = 0 ; 
	b2[0] =   -Lb/2 ; b2[1] = -Lb*sqrt(3)/6 ; b2[2] = 0 ; 
	
	matrix_multiplication(matR_in,p0,3,3,3,1,matR_x_p0);
	matrix_multiplication(matR_in,p1,3,3,3,1,matR_x_p1);
	matrix_multiplication(matR_in,p2,3,3,3,1,matR_x_p2);
	
	matrix_addition(pos_in,b0,3,1,pos_minus_b0);
	matrix_addition(pos_in,b1,3,1,pos_minus_b1);
	matrix_addition(pos_in,b2,3,1,pos_minus_b2);	
	
	
	matrix_addition(matR_x_p0,pos_minus_b2,3,1,l_0);
	matrix_addition(matR_x_p0,pos_minus_b0,3,1,l_1);	
	matrix_addition(matR_x_p1,pos_minus_b0,3,1,l_2);	
	matrix_addition(matR_x_p1,pos_minus_b1,3,1,l_3);
	matrix_addition(matR_x_p2,pos_minus_b1,3,1,l_4);
	matrix_addition(matR_x_p2,pos_minus_b2,3,1,l_5);	
	
	l_norm[0] = vector_3_norm(l_0);
	l_norm[1] = vector_3_norm(l_1);
	l_norm[2] = vector_3_norm(l_2);
	l_norm[3] = vector_3_norm(l_3);
	l_norm[4] = vector_3_norm(l_4);
	l_norm[5] = vector_3_norm(l_5);
	
	h[0]=height_triangle(l_norm[0],l_norm[1],Lb);
	h[1]=h[0];
	h[2]=height_triangle(l_norm[2],l_norm[3],Lb);
	h[3]=h[2];
	h[4]=height_triangle(l_norm[4],l_norm[5],Lb);
	h[5]=h[4];	
	
	for(int i=0;i<6;i++)
	{
		*(q+i) = (Lb/2 - (sqrt(l_norm[i]*l_norm[i] - h[i]*h[i]) - sqrt(L*L - h[i]*h[i])))*10; //  unit : mm
	}
}

void pos_calculate(float* pos)
{

		*(pos+0) = st_hexapod_data.x;
		*(pos+1) = st_hexapod_data.y;
		*(pos+2) = st_hexapod_data.z;
}

void matR_calculate(float* matR)
{
	
	float r = (st_hexapod_data.roll * pi) / 180;
	float p = (st_hexapod_data.pitch * pi) / 180;
	float y = (st_hexapod_data.yaw * pi) / 180;
	*(matR+0) = cos(y)*cos(p);
	*(matR+1) = -sin(y)*cos(r) + cos(y)*sin(r)*sin(p);
	*(matR+2) = sin(y)*sin(r) + cos(y)*sin(p)*cos(r);
	*(matR+3) = sin(y)*cos(p);
	*(matR+4) = cos(y)*cos(r) + sin(y)*sin(p)*sin(r);
	*(matR+5) = -cos(y)*sin(r) + sin(y)*sin(p)*cos(r);
	*(matR+6) = -sin(p);
	*(matR+7) = cos(p)*sin(r);
	*(matR+8) = cos(p)*cos(r);	
}
