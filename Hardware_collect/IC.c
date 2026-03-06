#include "stm32f10x.h"                  // Device header

void IC_Init(void){
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);

    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    TIM_TimeBaseInitTypeDef TimeBaseInitStucture;
    TimeBaseInitStucture.TIM_ClockDivision = TIM_CKD_DIV1;
    TimeBaseInitStucture.TIM_CounterMode = TIM_CounterMode_Up;
    TimeBaseInitStucture.TIM_Period = 65535;
    TimeBaseInitStucture.TIM_Prescaler = 72 - 1;
    TIM_TimeBaseInit(TIM3, &TimeBaseInitStucture);

	
	TIM_ICInitTypeDef TIM_ICInitSructure;
	TIM_ICStructInit(&TIM_ICInitSructure);
	TIM_ICInitSructure.TIM_Channel=TIM_Channel_1;//PA6对应TIM3_CH1
	TIM_ICInitSructure.TIM_ICFilter=0xF;
	TIM_ICInitSructure.TIM_ICPolarity=TIM_ICPolarity_Rising;
	TIM_ICInitSructure.TIM_ICPrescaler=TIM_ICPSC_DIV1;
	TIM_ICInitSructure.TIM_ICSelection=TIM_ICSelection_DirectTI;
	//配置输入捕获选择为直接映射到TI1上（CH1）,还有间接映射,就是选择捕获TI2的信号(TI1对应TI2),
	//即从TI2（CH2）对应的引脚输入的信号
	TIM_ICInit(TIM3,&TIM_ICInitSructure);
	
	
	TIM_PWMIConfig(TIM3,&TIM_ICInitSructure);
	//内部会自动把 CH2 配置为 下降沿、交叉映射(IndirectTI) 等互补状态
	//注意:只支持CH1与CH2,不要用在通道3和4了!!!
	
	TIM_SelectInputTrigger(TIM3,TIM_TS_TI1FP1);
	//从模式并非需要什么主模式，而是一条单独的路，当有TRGI信号时，从模式就被激活去干事
	TIM_SelectSlaveMode(TIM3,TIM_SlaveMode_Reset);
	
	TIM_Cmd(TIM3,ENABLE);
	
}

uint32_t IC_GetFreq(void){
	return 1000000/TIM_GetCapture1(TIM3);

}

uint32_t IC_GetDuty(void){
	return 100*TIM_GetCapture2(TIM3)/TIM_GetCapture1(TIM3);

}
