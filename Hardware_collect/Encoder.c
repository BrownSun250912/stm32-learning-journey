#include "stm32f10x.h"                  // Device header

void TIM_Encoder_Init(void){
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	TIM_TimeBaseInitTypeDef TimeBaseInitStucture;
    TimeBaseInitStucture.TIM_ClockDivision = TIM_CKD_DIV1;
    TimeBaseInitStucture.TIM_CounterMode = TIM_CounterMode_Up;
    TimeBaseInitStucture.TIM_Period = 65535;
    TimeBaseInitStucture.TIM_Prescaler = 1 - 1;
    TIM_TimeBaseInit(TIM3, &TimeBaseInitStucture);

	
	TIM_ICInitTypeDef TIM_ICInitSructure;
	TIM_ICStructInit(&TIM_ICInitSructure);
	
	TIM_ICInitSructure.TIM_Channel=TIM_Channel_1;//PA6对应TIM3_CH1
	TIM_ICInitSructure.TIM_ICFilter=0xF;
	TIM_ICInit(TIM3,&TIM_ICInitSructure);
	
	TIM_ICInitSructure.TIM_Channel=TIM_Channel_2;//PA6对应TIM3_CH1
	TIM_ICInitSructure.TIM_ICFilter=0xF;
	TIM_ICInit(TIM3,&TIM_ICInitSructure);
	
	TIM_EncoderInterfaceConfig(TIM3,TIM_EncoderMode_TI12,TIM_ICPolarity_Rising,TIM_ICPolarity_Rising);
	
	
	TIM_Cmd(TIM3,ENABLE);

}

int16_t Encoder_Get(void){
	return TIM_GetCounter(TIM3);
}