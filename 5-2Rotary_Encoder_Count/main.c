#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "rotary_encoder.h"

int main(void)
{
	OLED_Init ();
	Rotary_Encoder_Init();
	
	while(1){
		OLED_ShowSignedNum(1,1,rtencoder_counter(),5);
	}
}
