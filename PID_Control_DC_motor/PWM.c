#include "stm32f10x.h"                  // Device header

void PWM_Init(void )
{
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode =GPIO_Mode_AF_PP;
	//选用复用推挽输出,把输出控制权交给片上外设
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_2;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	
	TIM_TimeBaseInitTypeDef TimeBaseInitStucture;
	TimeBaseInitStucture.TIM_ClockDivision=TIM_CKD_DIV1;
	TimeBaseInitStucture.TIM_CounterMode=TIM_CounterMode_Up;
	TimeBaseInitStucture.TIM_Period=100-1;
	TimeBaseInitStucture.TIM_Prescaler=36-1;
	TIM_TimeBaseInit(TIM2,&TimeBaseInitStucture);

	TIM_OCInitTypeDef TIM_OCInitStructure;
	TIM_OCStructInit(&TIM_OCInitStructure);
	//给TIM_OCInitStructure赋默认值，因为结构体的成员没有全部赋值
	TIM_OCInitStructure.TIM_OCMode=TIM_OCMode_PWM1;//配置输出比较模式
	TIM_OCInitStructure.TIM_OCPolarity=TIM_OCPolarity_High;//ref有效时,输出高电平
	TIM_OCInitStructure.TIM_OutputState=TIM_OutputState_Enable;//输出使能
	TIM_OCInitStructure.TIM_Pulse=0;//即配置CCR的值
	TIM_OC3Init(TIM2,&TIM_OCInitStructure);
	/*选择OC3通道进行初始化,可以选择不同的通道,
	频率相同(公用一个时钟),但是各自的占空比可以改变,相位同步(定时器同时更新)*/
	//配置TIM输出比较单元,使通道输出PWM波形
	
	
	
	TIM_Cmd(TIM2,ENABLE);
}

void PWM_Setcompare3(uint16_t i){
	TIM_SetCompare3(TIM2,i);
}


