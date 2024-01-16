#include "Timer.h"
#include "pac9685.h"
extern int16_t LeftSpeed;
extern int16_t RightSpeed;
extern char USART1_RX_BUF[50];
extern uint8_t flagstopcar;
char ColourList[50];
char ColourList_2[50];
uint16_t listcount = 0;
uint16_t listcount_2 = 0;
char Redlist[] = "11111111111111111111";//21byte
char Greedlist[] = "22222222222222222222";//21byte
char Bluelist[] = "44444444444444444444";//21byte
char zorelist[] = "00000000000000000000";//21byte
char Templist[] = "xxxxxxxxxxxxxxxxxxxx";//21byte
uint8_t first_packet = 0; // 是否为第一个数据包的标志位
uint8_t flag_pca9685 = 0;

void TIM2_Measure_Speed_Init(void)//右后轮
{
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;//选择时钟分频为不分频
	TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;//选择计数模式为向上计数

	TIM_TimeBaseInitStructure.TIM_Period = 65536-1;//计数最大值
	TIM_TimeBaseInitStructure.TIM_Prescaler = 1-1;//计数时钟不分频
	//TIM_TimeBaseInitStructure.TIM_RepetitionCounter = 0;//TIM1&TIM8配置
	TIM_TimeBaseInit(TIM2,&TIM_TimeBaseInitStructure);
	
	TIM_ICInitTypeDef TIM_ICInitStructure;
	TIM_ICStructInit(&TIM_ICInitStructure);//结构参数初始化
	TIM_ICInitStructure.TIM_Channel=TIM_Channel_1;
	TIM_ICInitStructure.TIM_ICFilter = 0xF;  //输入低通滤波
	TIM_ICInit(TIM2, &TIM_ICInitStructure);
	
	TIM_ICInitStructure.TIM_Channel=TIM_Channel_2;
	TIM_ICInitStructure.TIM_ICFilter = 0xF;  //输入低通滤波
	TIM_ICInit(TIM2, &TIM_ICInitStructure);
	
	TIM_EncoderInterfaceConfig(TIM2, TIM_EncoderMode_TI12, TIM_ICPolarity_BothEdge ,TIM_ICPolarity_BothEdge);//TI12:A、B项都计数
	
	//TIM_SetCounter(TIM2,32768);
	
	TIM_Cmd(TIM2,ENABLE);
}

void TIM3_Measure_Speed_Init(void)//左后轮
{
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;//选择时钟分频为不分频
	TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;//

	TIM_TimeBaseInitStructure.TIM_Period = 65536-1;//
	TIM_TimeBaseInitStructure.TIM_Prescaler = 1-1;

	//TIM_TimeBaseInitStructure.TIM_RepetitionCounter = 0;//TIM1&TIM8配置
	TIM_TimeBaseInit(TIM3,&TIM_TimeBaseInitStructure);
	
	TIM_ICInitTypeDef TIM_ICInitStructure;  
	TIM_ICStructInit(&TIM_ICInitStructure);
	TIM_ICInitStructure.TIM_Channel=TIM_Channel_1;
	TIM_ICInitStructure.TIM_ICFilter = 0xF;  //滤波器
	TIM_ICInit(TIM3, &TIM_ICInitStructure);
	
	TIM_ICInitStructure.TIM_Channel=TIM_Channel_2;
	TIM_ICInitStructure.TIM_ICFilter = 0xF;  //输入低通滤波
	TIM_ICInit(TIM2, &TIM_ICInitStructure);
	
	TIM_EncoderInterfaceConfig(TIM3, TIM_EncoderMode_TI12, TIM_ICPolarity_BothEdge ,TIM_ICPolarity_BothEdge);//TI12:A、B项都计数
	
	//TIM_SetCounter(TIM3,32768); //
	
	TIM_Cmd(TIM3,ENABLE);
}

void TIM4_Timer_Init(uint16_t per,uint16_t psc)
{
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4,ENABLE);
	
	//选择时钟源为内部时钟
	//TIM_InternalClockConfig(TIM4);//默认为内部时钟

	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;//选择计数模式为向上计数

	TIM_TimeBaseInitStructure.TIM_Period = per-1;//配置周期（ARR自动重装器的值）
	TIM_TimeBaseInitStructure.TIM_Prescaler = psc-1;//配置PSC预分频器的值
	TIM_TimeBaseInit(TIM4,&TIM_TimeBaseInitStructure);

	TIM_ITConfig(TIM4,TIM_IT_Update,ENABLE);

	NVIC_InitTypeDef NVIC_InitStructure;
	NVIC_InitStructure.NVIC_IRQChannel = TIM4_IRQn;//选择中断通道
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;//开启中断通道
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_Init(&NVIC_InitStructure);
	
	TIM_Cmd(TIM4,ENABLE);
}

int16_t Left_Encoder_Get(void)
{
	int16_t datatemp;
	//uint16_t datatemp2;
	datatemp=TIM_GetCounter(TIM3);
	TIM_SetCounter(TIM3,0);
	//datatemp2=datatemp;
//	if(datatemp<0){datatemp2=datatemp;}
//	else{datatemp2=datatemp;}
	return datatemp;
}

int16_t Right_Encoder_Get(void)
{
	int16_t datatemp;
	//uint16_t datatemp2;
	datatemp=TIM_GetCounter(TIM2);
	TIM_SetCounter(TIM2,0);
	//datatemp2=datatemp;
//	if(datatemp<0){datatemp2=datatemp;}
//	else{datatemp2=datatemp;}
	return datatemp;
}

void TIM4_IRQHandler(void)//测出的速度：计数量/10ms
{
	int16_t LeftSpeedNOW=0;
	int16_t RightSpeedNOW=0;
	if(TIM_GetITStatus(TIM4, TIM_IT_Update) != RESET)
	{
		LeftSpeedNOW = Left_Encoder_Get();	//获取左后轮的速度
		RightSpeedNOW = Right_Encoder_Get();//获取右后轮的速度
		PID_Right_Computer(RightSpeed,RightSpeedNOW);
		PID_Left_Computer(LeftSpeed,LeftSpeedNOW);
		
		//计数颜色采样是否稳定
		if((first_packet == 0 || first_packet == 2) && USART1_RX_BUF[1] != '0'){//识别到颜色
			ColourList[listcount++] = USART1_RX_BUF[1];//记下颜色
			if(listcount == 20 && first_packet == 0){
				ColourList[listcount] = '\0';
				if(strcmp(ColourList,Redlist) == 0||strcmp(ColourList,Bluelist) == 0||strcmp(ColourList,Greedlist) == 0){
					listcount = 0;
					first_packet = 1;//标记第一个数据包为组委会的颜色.
					strcpy(Templist,ColourList);//存好这个数据包.
				}
				else{
					first_packet = 0;
					listcount = 0;
				}
			}
			if(listcount == 20 && first_packet == 2){
				ColourList[listcount] = '\0';
				if(strcmp(ColourList,Templist) == 0){
					listcount = 0;
					if(flagstopcar == 0){
						Set_CarStop();		//停车
						flag_pca9685 = 1;	//开启舵机工作
					}
				}
				else{listcount = 0;} 
			}
		}
		else if(first_packet == 1 && USART1_RX_BUF[1] == '0'){
			ColourList_2[listcount_2++] = USART1_RX_BUF[1];//记下颜色
			if(listcount_2 == 20){
				ColourList_2[listcount_2] = '\0';
				if(strcmp(ColourList_2,zorelist) == 0){
					listcount_2 = 0;
					first_packet = 2;//标记第一个数据包为组委会的颜色.
				}
				else{
					listcount_2 = 0;
				}
			}
		}
		else{
			listcount = 0;
			listcount_2 = 0;
		}//清除计数
	}
	TIM_ClearITPendingBit(TIM4, TIM_IT_Update);
}
