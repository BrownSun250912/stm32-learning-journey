#include "stm32f10x.h"                  // Device header
#include "OLED.h"
#include "Motor.h" 
#include "PID_Motor.h"
#include "Encoder.h"
#include "PWM.h"
#include "stm32f10x_it.h"


#define ENCODER_CPR   448.0f    
// 查到的基础脉冲数 (如果是 X4 模式且 448 已经是四倍频后的结果，就填 448)
#define GEAR_RATIO    30.0f     
// 占位符：减速比先假设为 30，等你查到了随时改！
#define CALC_CONST    (6000.0f / (ENCODER_CPR * GEAR_RATIO)) 
// 编译器会自动算好这个常数，不消耗单片机算力！


float Target_RPM=120.0f;//f是什么意思？
float Actual_RPM=0.0f;
extern PID_TypeDef PID_InitStructure;

int main(void)
{
	SysTick_Config(SystemCoreClock / 100);
	OLED_Init();
	Motor_Init();
	PWM_Init();
	PID_Init(&PID_InitStructure,2,1,0,100,20);
	TIM_Encoder_Init();
	
	
	while(1){
		
	}
}

void SysTick_Handler(void){
	int16_t current_pulses=Encoder_Get();  //读取编码器的脉冲数
	
	Actual_RPM = (float)current_pulses * CALC_CONST;
	float pwm_out = PID_Calc(&PID_InitStructure, Target_RPM, Actual_RPM);
	
	Motor_Setspeed((int8_t) pwm_out);
	
	TIM_SetCounter(TIM1,0);
}
