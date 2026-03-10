#include "stm32f10x.h"                  // Device header
#include "PID_Motor.h"

void PID_Init(PID_TypeDef *pid,float p,float i,float d,float maxout,float maxi){
	pid->Kp=p;
	pid->Ki=i;
	pid->Kd=d;
	
	pid->Error =0.0;
	pid->LastError=0.0;
	pid->Integral=0.0;
	pid->MaxOutput=maxout ;
	pid->MaxIntegral=maxi ;
	
}

float PID_Calc(PID_TypeDef *pid,float Target,float Actual){
	pid->Error=Target -Actual ;
	
	pid->Integral+=pid->Error;
	
	if(pid->Integral>pid->MaxIntegral){
		pid->Integral=pid->MaxIntegral;
	}
	else if(pid->Integral<-pid->MaxIntegral){
		pid->Integral=-pid->MaxIntegral;
	}
	
	float Output;
	Output=pid->Kp*pid->Error + pid->Ki*pid->Integral +pid->Kd*(pid->Error-pid->LastError);
	
	pid->LastError=pid->Error;
	
	if (Output > pid->MaxOutput)       Output = pid->MaxOutput;
    else if (Output < -pid->MaxOutput) Output = -pid->MaxOutput;
	
	return Output;
}

