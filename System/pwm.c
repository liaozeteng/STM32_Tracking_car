#include "pwm.h"                  // Device header

void TIM1_PWM10K_Init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);

	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8 |GPIO_Pin_9 | GPIO_Pin_10 | GPIO_Pin_11;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStructure);

	/*初始化定时器参数*/
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;//选择时钟分频为不分频
	TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;//选择计数模式为向上计数
	TIM_TimeBaseInitStructure.TIM_Period = 100-1;//配置周期（ARR自动重装器的值）
	TIM_TimeBaseInitStructure.TIM_Prescaler = 72-1;//配置PSC预分频器的值
	TIM_TimeBaseInitStructure.TIM_RepetitionCounter = 0;//重复计数器的值，高级计数器才需配置
	TIM_TimeBaseInit(TIM1,&TIM_TimeBaseInitStructure);
	//TIM_ClearFlag(TIM4,TIM_FLAG_Update);//先清除标志位，避免刚初始化就进入中断
	
	/*初始化PWM参数*/
	TIM_OCInitTypeDef TIM_OCInitStructure;
	TIM_OCInitStructure.TIM_Pulse = 0;
	TIM_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Reset;
	TIM_OCInitStructure.TIM_OCNIdleState = TIM_OCNIdleState_Reset;
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;//选择PWM1模式
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;//输出极性：低电平有效
	TIM_OCInitStructure.TIM_OCNPolarity = TIM_OCNPolarity_High;
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;//使能
	TIM_OCInitStructure.TIM_OutputNState = TIM_OutputNState_Enable;
	TIM_OC1Init(TIM1,&TIM_OCInitStructure);
	TIM_OC2Init(TIM1,&TIM_OCInitStructure);
	TIM_OC3Init(TIM1,&TIM_OCInitStructure);
	TIM_OC4Init(TIM1,&TIM_OCInitStructure);
	
	/*使能TIMX在CCRX上的预装载寄存器*/
	TIM_OC1PreloadConfig(TIM1,TIM_OCPreload_Enable);
	TIM_OC2PreloadConfig(TIM1,TIM_OCPreload_Enable);
	TIM_OC3PreloadConfig(TIM1,TIM_OCPreload_Enable);
	TIM_OC4PreloadConfig(TIM1,TIM_OCPreload_Enable);
	
	TIM_CtrlPWMOutputs(TIM1,ENABLE);
	
	/*使能TIMX在ARR上的预装载寄存器允许位*/
	//TIM_ARRPreloadConfig(TIM4,ENABLE);
	
	/*开启定时器*/
	TIM_Cmd(TIM1,ENABLE);
	
	TIM_SetCompare1(TIM1,50);//给一个起始PWM,后期由PID接管
	TIM_SetCompare2(TIM1,50);//给一个起始PWM,后期由PID接管
	TIM_SetCompare3(TIM1,50);//给一个起始PWM,后期由PID接管
	TIM_SetCompare4(TIM1,50);//给一个起始PWM,后期由PID接管
}	

