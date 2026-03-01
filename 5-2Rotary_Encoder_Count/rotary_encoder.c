#include "stm32f10x.h"                  // Device header

int16_t Encoder_Count;

void Rotary_Encoder_Init(void)
{
	RCC_APB2PeriphClockCmd (RCC_APB2Periph_GPIOB ,ENABLE );
	RCC_APB2PeriphClockCmd (RCC_APB2Periph_AFIO ,ENABLE );

	GPIO_InitTypeDef  GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Mode =GPIO_Mode_IPU ;
	GPIO_InitStructure .GPIO_Pin =GPIO_Pin_1|GPIO_Pin_0;
	GPIO_InitStructure .GPIO_Speed =GPIO_Speed_50MHz ;
	GPIO_Init(GPIOB ,&GPIO_InitStructure);
	
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOB,GPIO_PinSource0);
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOB,GPIO_PinSource1);

	EXTI_InitTypeDef EXTI_InitStructure;
	EXTI_InitStructure .EXTI_Line =EXTI_Line0|EXTI_Line1;//怎么保证line0对上afio选择的0？固定的吗？
	EXTI_InitStructure.EXTI_LineCmd=ENABLE ;
	EXTI_InitStructure.EXTI_Mode=EXTI_Mode_Interrupt;
	EXTI_InitStructure.EXTI_Trigger=EXTI_Trigger_Falling; 
	EXTI_Init(&EXTI_InitStructure);
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	
	NVIC_InitTypeDef NVIC_InitStructure;
	NVIC_InitStructure.NVIC_IRQChannel=EXTI0_IRQn;//为什么是0/1,stm32f10x.h中没有这两个啊？
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE ;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=1;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=1;
	NVIC_Init(&NVIC_InitStructure);
	
	
	NVIC_InitStructure.NVIC_IRQChannel=EXTI1_IRQn;//为什么是0/1,stm32f10x.h中没有这两个啊？
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE ;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=1;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=2;
	NVIC_Init(&NVIC_InitStructure);

}
void EXTI0_IRQHandler()//为什么同一个名字有两个前缀?DCD,EXPORT
{
	if(EXTI_GetITStatus(EXTI_Line0)==SET){
		if(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_1)==0){
			Encoder_Count--;//?没初始化数值为什么还能这样用
		}
		EXTI_ClearITPendingBit(EXTI_Line0);
	}
}

void EXTI1_IRQHandler()
{
	if(EXTI_GetITStatus(EXTI_Line1)==SET){
		if(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_0)==0){
			Encoder_Count++;
		}
		EXTI_ClearITPendingBit(EXTI_Line1);
	}
}

int32_t rtencoder_counter(void){
	return Encoder_Count;
}


