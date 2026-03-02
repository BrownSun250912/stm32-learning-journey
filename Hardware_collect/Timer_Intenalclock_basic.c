#include "stm32f10x.h"                  // Device header

void Timer_Init(void){
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE); //打开TIM2的时钟
	
	TIM_InternalClockConfig(TIM2);//配置时钟模式为内部时钟
	
	TIM_TimeBaseInitTypeDef TimeBase_InitStructure;
	TimeBase_InitStructure.TIM_ClockDivision=TIM_CKD_DIV1;
	//这个分频器是干什么用的？
	//处理外部信号的毛刺，如果把外部引脚接到定时器上检测输入，这时这个分频器就起作用了
	TimeBase_InitStructure.TIM_CounterMode=TIM_CounterMode_Up;
	//配置计数模式，还有其他的模式
	//还有下降,中央对其模式,一般是UP模式
	TimeBase_InitStructure.TIM_Period=10000-1;//不能超过65536(16位)
	TimeBase_InitStructure.TIM_Prescaler=7200-1;//不能超过65536(16位)
	//TimeBase_InitStructure.TIM_RepetitionCounter=;
	//上面那条只有高级定时器才有，基本和通用都没有
	TIM_TimeBaseInit(TIM2,&TimeBase_InitStructure);
	//配置时基单元

	
	TIM_ClearFlag(TIM2,TIM_FLAG_Update);
	//清除TIM初始化时由于软件模拟产生更新所产生的更新中断标志位,会立即触发一次中断事件
	/*注意与TIM_ClearITPendingBit的区别，二者都是操作同一个SR(状态寄存器)
	真正的区别在于二者配套的Get函数:
	TIM_GetFlagStatus()：极其单纯。 
	它只看硬件 SR 寄存器里那个标志位是不是 1。只要时间到了，哪怕你没开中断，它也返回 SET。
	TIM_GetITStatus()：极其严谨！
	它不仅会去看 SR 寄存器里的标志位是不是 1，它还会顺便去查一下 DIER（中断使能寄存器），
	看看你到底有没有允许这个中断发生！ 只有当“事件发生了”且“你开启了该中断”，它才会返回 SET。
	*/
	
	TIM_ITConfig(TIM2,TIM_IT_Update,ENABLE);
	//中断输出控制，即配置中断触发条件，TIM_IT_Update是CNT数满一圈触发一次中断
	
	
	NVIC_InitTypeDef NVICInitStructure;
	NVICInitStructure.NVIC_IRQChannel=TIM2_IRQn;
	NVICInitStructure.NVIC_IRQChannelCmd=ENABLE;
	NVICInitStructure.NVIC_IRQChannelPreemptionPriority=1;
	NVICInitStructure.NVIC_IRQChannelSubPriority=1;
	NVIC_Init(&NVICInitStructure);
	//配置NVIC，打开TIM2通道
	
	
	TIM_Cmd(TIM2 ,ENABLE );
	//使能TIM2外设
	/*在极其严谨的底层代码中，我们通常会把 TIM_Cmd(TIM2, ENABLE); 这句话，
	挪到整个 Timer_Init 函数的最后一行！ 这是最后一道工序！
	在确保所有安保系统(NVIC)全部就绪后,才启动TIM*/
}

/*
void TIM2_IRQHandler(void){
	if(TIM_GetITStatus(TIM2,TIM_IT_Update)==SET){
		Num++;
		TIM_ClearITPendingBit(TIM2,TIM_IT_Update);
		中断事件执行完成之后一定要把SR寄存器的UIF(状态位)置0,否则会一直执行中断函数
	}
}
在需要调用中断函数的文件里面写中断函数,防止Num的跨文件调用*/

//没有调用这个函数怎么会运行呢？
/*中断函数在编译的时候就被编译器把物理地址填入"中断向量表"中,修改了寄存器状态
只要满足中断条件,CPU接受NVIC指令立刻停止所做,执行中断函数
*/


