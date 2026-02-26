#include "stm32f10x.h"                  // Device header
#include "Delay.h"
int main(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode =GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin =GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3|
	GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Speed =GPIO_Speed_50MHz;
	GPIO_Init(GPIOA ,&GPIO_InitStructure);
	
	const int arr[8]={0x0001,0x0002,0x0004,0x0008,0x0010,0x0020,0x0040,0x0080};
	while(1){
		int i;
		for(i=0;i<8;i++){
			GPIO_Write(GPIOA ,~arr[i]);
			Delay_ms (200);
	}
}
}	
