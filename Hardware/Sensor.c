#include "Sensor.h"

void Sensor_Init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOB|RCC_APB2Periph_GPIOC,ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStructure;
	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_15;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&GPIO_InitStructure);			//GPIO-B12-B13-B14-B15
	
//	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
//	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4 ;//GPIO-C4
//	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
//	GPIO_Init(GPIOA,&GPIO_InitStructure);
//	
//	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
//	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1 | GPIO_Pin_2;
//	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
//	GPIO_Init(GPIOC,&GPIO_InitStructure);			//GPIO-C1-C2
	GPIO_SetBits(GPIOB,GPIO_Pin_15);
}

//uint8_t Get_SensorState(void)
//{
//	uint8_t DataByte=0x00;
//	if(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_12)!=0){
//		DataByte=DataByte|0x01;
//	}
//	if(GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_1)!=0){
//		DataByte=DataByte|0x02;
//	}
//	if(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_13)!=0){
//		DataByte=DataByte|0x04;
//	}
//	if(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_4)!=0){
//		DataByte=DataByte|0x08;
//	}
//	if(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_14)!=0){
//		DataByte=DataByte|0x10;
//	}
//	if(GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_2)!=0){
//		DataByte=DataByte|0x20;
//	}
//	if(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_15)!=0){
//		DataByte=DataByte|0x40;
//	}
//	return DataByte;
//}


