#include "stm32f10x.h"                  // Device header

uint32_t counter=0;

void CountSensor_init(void)
{
	RCC_APB2PeriphClockCmd (RCC_APB2Periph_GPIOB ,ENABLE );
	RCC_APB2PeriphClockCmd (RCC_APB2Periph_AFIO ,ENABLE );
	/*EXTI与NVIC均不需要开启时钟，前者只要系统通电就一直开着，
	后者是内设无需开启，因为RCC管理外设*/
	
	GPIO_InitTypeDef GPIO_InitStructure;
	
	GPIO_InitStructure .GPIO_Mode =GPIO_Mode_IPU ;
	GPIO_InitStructure .GPIO_Pin=GPIO_Pin_14 ;
	GPIO_InitStructure .GPIO_Speed =GPIO_Speed_50MHz ;
	GPIO_Init (GPIOB ,&GPIO_InitStructure );
	//GPIO配置
	
	GPIO_EXTILineConfig (GPIO_PortSourceGPIOB ,GPIO_PinSource14);
	//AFIO配置
	
	EXTI_InitTypeDef  EXTI_InitStructure;
	EXTI_InitStructure.EXTI_Line =EXTI_Line14 ;
	EXTI_InitStructure.EXTI_LineCmd =ENABLE ;
	EXTI_InitStructure.EXTI_Mode =EXTI_Mode_Interrupt;
	EXTI_InitStructure.EXTI_Trigger =EXTI_Trigger_Falling;
	EXTI_Init (&EXTI_InitStructure );
	//配置EXTI
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//选择NVIC优先级分组
	NVIC_InitTypeDef NVIC_InitStructure;//定义结构体
	NVIC_InitStructure.NVIC_IRQChannel =EXTI15_10_IRQn;//选择中断通道
	NVIC_InitStructure.NVIC_IRQChannelCmd =ENABLE ;//开启
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority =2;//设置抢占优先级
	NVIC_InitStructure.NVIC_IRQChannelSubPriority =2;//设置响应优先级
	NVIC_Init (&NVIC_InitStructure );//初始化NVIC
	
}


void EXTI15_10_IRQHandler(void)//中断函数都有固定的名称,到startup_stm32f10x_md.s中查看
{
	//先判断是否是从我们的EXTI14进入的
	if(EXTI_GetITStatus(EXTI_Line14)==SET){
		counter++;
		EXTI_ClearITPendingBit(EXTI_Line14);
		//重要!!!中断结束后要重置中断位,否则会一直执行中断程序!
	}
}







