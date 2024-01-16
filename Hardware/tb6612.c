#include "tb6612.h"
#include "Sensor.h"

extern int16_t LeftSpeed;
extern int16_t RightSpeed;
extern uint8_t Count;

void TB6612_GPIO_Init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOB|RCC_APB2Periph_GPIOC,ENABLE);
	GPIO_InitTypeDef GPIO_InitStructure;
	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStructure);		//GPIO-A3
	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_5 | GPIO_Pin_10 | GPIO_Pin_11;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&GPIO_InitStructure);	//GPIO-B0-B1-B5-B10-B11
	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3 | GPIO_Pin_4;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOC,&GPIO_InitStructure);	//GPIO-C3-C4
	
	GPIO_SetBits(GPIOA,GPIO_Pin_3);
	GPIO_SetBits(GPIOB,GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_5 | GPIO_Pin_10 | GPIO_Pin_11);
	GPIO_SetBits(GPIOC,GPIO_Pin_3 | GPIO_Pin_4);
}

void Set_CarForward(void)
{
	GPIO_SetBits(GPIOB,GPIO_Pin_0|GPIO_Pin_5|GPIO_Pin_10);
	GPIO_SetBits(GPIOA,GPIO_Pin_3);
	
	GPIO_ResetBits(GPIOB,GPIO_Pin_1|GPIO_Pin_11);
	GPIO_ResetBits(GPIOC,GPIO_Pin_3|GPIO_Pin_4);
}

void Set_CarRetreat(void)
{
	GPIO_SetBits(GPIOB,GPIO_Pin_1|GPIO_Pin_11);
	GPIO_SetBits(GPIOC,GPIO_Pin_3|GPIO_Pin_4);
	
	GPIO_ResetBits(GPIOB,GPIO_Pin_0|GPIO_Pin_5|GPIO_Pin_10);
	GPIO_ResetBits(GPIOA,GPIO_Pin_3);
}

void Set_CarStop(void)
{
	Set_CarTurn(0,0);
	GPIO_ResetBits(GPIOB,GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_5|GPIO_Pin_10|GPIO_Pin_11);
	GPIO_ResetBits(GPIOC,GPIO_Pin_3|GPIO_Pin_4);
	GPIO_ResetBits(GPIOA,GPIO_Pin_3);
}

void Set_CarTurn(int16_t Left,int16_t Right)
{
	LeftSpeed = Left;
	RightSpeed = Right;
}

void Set_CarLeftBuck_CarRightForward(int16_t Left,int16_t Right)
{
	GPIO_SetBits(GPIOB , GPIO_Pin_0);//右前轮正转
	GPIO_ResetBits(GPIOB , GPIO_Pin_1);
	
	GPIO_ResetBits(GPIOC , GPIO_Pin_4);//右后轮正转
	GPIO_SetBits(GPIOA , GPIO_Pin_3);
	
	GPIO_ResetBits(GPIOB , GPIO_Pin_5);//左前轮反转
	GPIO_SetBits(GPIOC, GPIO_Pin_3);
	
	GPIO_ResetBits(GPIOB , GPIO_Pin_10);//左后轮反转
	GPIO_SetBits(GPIOB , GPIO_Pin_11);
	
	LeftSpeed = Left;
	RightSpeed = Right;
}

void Set_CarLeftForward_CarRightBuck(int16_t Left,int16_t Right)
{
	//TIM_EncoderInterfaceConfig(TIM2, TIM_EncoderMode_TI12, TIM_ICPolarity_BothEdge ,TIM_ICPolarity_BothEdge);//TI12:A、B项都计数
	GPIO_ResetBits(GPIOB , GPIO_Pin_0);//右前轮正转
	GPIO_SetBits(GPIOB , GPIO_Pin_1);
	
	GPIO_SetBits(GPIOC , GPIO_Pin_4);//右后轮正转
	GPIO_ResetBits(GPIOA , GPIO_Pin_3);
	
	GPIO_SetBits(GPIOB , GPIO_Pin_5);//左前轮反转
	GPIO_ResetBits(GPIOC, GPIO_Pin_3);
	
	GPIO_SetBits(GPIOB , GPIO_Pin_10);//左后轮反转
	GPIO_ResetBits(GPIOB , GPIO_Pin_11);
	
	LeftSpeed = Left;
	RightSpeed = Right;
}

//void Set_CarPosture(void)
//{
//	uint8_t Datatemp;
//	Datatemp = Get_SensorState();
//	
//  if(Datatemp == 0x7F){
//		if(Count == 0){Set_CarTurn(10,10);}
//		if(Count == 2){Set_CarTurn(20,20);}
//		if(Count == 4){Set_CarTurn(25,25);}
//		if(Count == 5){Set_CarTurn(5,5);}
//		if(Count == 6){
//			Set_CarStop();
//			//while(1);
//		}
//		//Set_CarTurn(5,5);
//	}//全部识别
//	else if(Datatemp==0x01){
//		Set_CarTurn(40,0);
//		Delay_ms(80);
//	}//最右边识别
//	else if(Datatemp==0x40){
//		Set_CarTurn(0,40);
//		Delay_ms(80);
//	}//最左边识别
//	else if(Datatemp==0x1C){Set_CarTurn(10,10);}
//	
//	else if(Datatemp==0x30){Set_CarTurn(0,27);}
//	else if(Datatemp==0x70){Set_CarTurn(0,25);}
//	else if(Datatemp==0x60){Set_CarTurn(0,32);}
//	
//	else if(Datatemp==0x38){Set_CarTurn(0,20);}
//	
//	else if(Datatemp==0x03){Set_CarTurn(32,0);}
//	else if(Datatemp==0x07){Set_CarTurn(27,0);}
//	else if(Datatemp==0x06){Set_CarTurn(25,0);}
//	
//	else if(Datatemp==0x0E){Set_CarTurn(20,0);}
//}

