#include "stm32f10x.h"                  // Device header
#include "stdio.h"
#include "Delay.h"
#include "Usart.h"
#include "Timer.h"
#include "pwm.h"
//#include "Exti.h"
#include "PID.h"
#include "Sensor.h"
#include "tb6612.h"
#include "openMV.h"
#include "joint.h"
#include "pac9685.h"
#include "MPU6050.h"

//extern uint8_t OpenMV_Data_count;
extern char USART1_RX_BUF[50];
extern char USART3_RX_BUF[50];
extern uint8_t Count;
extern uint8_t flag_pca9685;
extern uint8_t flag2;
int16_t LeftSpeed=15;
int16_t RightSpeed=15;
uint8_t countflag = 1;
uint8_t flagstopcar = 0;
uint8_t xunji_Flag = 1;

int main(void)
{
	Usart1_Init();		 //初始化颜色识别OPENMV
	Usart3_Init();		 //初始化循迹OPENMV
	TIM1_PWM10K_Init();//初始化四轮PWM驱动
	TIM2_Measure_Speed_Init();//初始化编码器计数
	TIM3_Measure_Speed_Init();//初始化编码器计数
	TIM4_Timer_Init(10000,72);//10ms定时器
	TB6612_GPIO_Init();
	Sensor_Init();
//	Exti_Init();
//	Joint_Init();
	PCA9685_Init(50,0);//初始化舵机频率50Hz
	MPU6050_Init();		 //初始化MPU6050
	MPU6050_Init();		 //初始化MPU6050
	Delay_ms(500);		 //上电等待OPENMV就绪
	Set_CarForward();	 //设置小车前进
	Set_CarTurn(25,25);//坐右轮25前进
	Delay_ms(800);
	while(1)
	{
		if(countflag == 1){
			OpenMV_Get_SensorState(USART3_RX_BUF[1]);//检查数据包
		}
		if(xunji_Flag == 1){
			OpenMVFind(USART3_RX_BUF[1]);						 //循迹
		}
		OpenMV_Set_Countstatus();//执行计数状态
		if(flag_pca9685 == 1){
			PCA0685_work();
			Delay_s(1);
			USART_Cmd(USART1,DISABLE);
			flag_pca9685 = 0;
			flagstopcar = 1;
			Set_CarForward();//设置小车前进
			Set_CarTurn(10,10);	//前进(10,10)
			Delay_s(1);					//前进1s掠过
			flag2 = 3;		//改变中线速度(25,25)
		}
	}
}

