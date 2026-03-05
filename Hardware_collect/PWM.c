#include "stm32f10x.h" // Device header

void PWM_Init(void)
{
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);

	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	// 选用复用推挽输出,把输出控制权交给片上外设
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	TIM_TimeBaseInitTypeDef TimeBaseInitStucture;
	TimeBaseInitStucture.TIM_ClockDivision = TIM_CKD_DIV1;
	TimeBaseInitStucture.TIM_CounterMode = TIM_CounterMode_Up;
	TimeBaseInitStucture.TIM_Period = 100 - 1;
	TimeBaseInitStucture.TIM_Prescaler = 720 - 1;
	TIM_TimeBaseInit(TIM2, &TimeBaseInitStucture);

	TIM_OCInitTypeDef TIM_OCInitStructure;
	TIM_OCStructInit(&TIM_OCInitStructure);						  // 给TIM_OCInitStructure赋默认值，因为结构体的成员没有全部赋值
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;			  // 配置输出比较模式为PWM模式1,当计数器的值小于CCR的值时,输出高电平,否则输出低电平
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;	  // ref有效时,输出高电平，如果配置为TIM_OCPolarity_Low,则ref有效时输出低电平
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; // 使能'TIM输出比较单元''
	TIM_OCInitStructure.TIM_Pulse = 0;							  // 即配置CCR的值
	TIM_OC1Init(TIM2, &TIM_OCInitStructure);
	// 配置TIM输出比较单元,使通道输出PWM波形

	TIM_Cmd(TIM2, ENABLE); // 使能TIM2(最后一步,先配置好TIM2的各项参数,再使能TIM2)
}
