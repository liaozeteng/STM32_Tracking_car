#include "Exti.h"

uint8_t Count=0;

void Exti_Init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_15 | GPIO_Pin_14 | GPIO_Pin_13 | GPIO_Pin_12; //| GPIO_Pin_14 | GPIO_Pin_15;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOB, GPIO_PinSource15);
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOB, GPIO_PinSource14);
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOB, GPIO_PinSource13);
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOB, GPIO_PinSource12);
	
	EXTI_InitTypeDef EXTI_InitStructure;
	EXTI_InitStructure.EXTI_Line = EXTI_Line15 | EXTI_Line14 | EXTI_Line13 | EXTI_Line12 ;//| EXTI_Line14 | EXTI_Line15;
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;
	EXTI_Init(&EXTI_InitStructure);
	
	NVIC_InitTypeDef NVIC_InitStructure;
	NVIC_InitStructure.NVIC_IRQChannel = EXTI15_10_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_Init(&NVIC_InitStructure);

}

void EXTI15_10_IRQHandler(void)
{
//	uint8_t Datatemp2 = 0;
	if (EXTI_GetITStatus(EXTI_Line15) == SET && EXTI_GetITStatus(EXTI_Line14) == SET && EXTI_GetITStatus(EXTI_Line13) == SET && EXTI_GetITStatus(EXTI_Line12) == SET)
	{
		if (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_15) == 1 && GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_14) == 1 && GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_13) == 1 && GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_12) == 1){
			//Datatemp2 = Get_SensorState();
			//if(Datatemp2 == 0x7F){
				Count++;
			//}
		}
		EXTI_ClearITPendingBit(EXTI_Line15);
		EXTI_ClearITPendingBit(EXTI_Line14);
		EXTI_ClearITPendingBit(EXTI_Line13);
		EXTI_ClearITPendingBit(EXTI_Line12);
	}
}
