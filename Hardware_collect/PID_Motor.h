#ifndef __PID_MOTOR__H
#define __PID_MOTOR__H

typedef struct{
	float Kp;
	float Ki;
	float Kd;
	
	float Error;
	float LastError;
	float Integral;
	
	float MaxOutput;
	float MaxIntegral;

} PID_TypeDef;

void PID_Init(PID_TypeDef *pid,float p,float i,float d,float maxout,float maxi);
float PID_Calc(PID_TypeDef *pid,float Target,float Actual);

#endif
