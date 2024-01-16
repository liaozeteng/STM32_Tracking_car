#include "PID.h"

float Kp=10;
float Ki=2;
float Kd=0.2;

int16_t LeftRealityVlaue;	//实际测量值
//int16_t LeftTargetVlaue;	//目标速度值
int16_t LeftEk;						//实际值与目标值的差值
int16_t LeftEk_1 = 0;			//下一个实际值与目标值的差值		
int16_t LeftEk_2 = 0;			//再下一个实际值与目标值的差值	
int16_t LeftPkVlaue;			//计算出的矫正值
int16_t out_left = 0;

int16_t RightRealityVlaue;	//实际测量值
//int16_t RightTargetVlaue;		//目标速度值
int16_t RightEk;						//实际值与目标值的差值
int16_t RightEk_1 = 0;			//下一个实际值与目标值的差值		
int16_t RightEk_2 = 0;			//再下一个实际值与目标值的差值	
int16_t RightPkVlaue;				//计算出的矫正值
int16_t out_right = 0;

void PID_Right_Computer(int16_t RightTargetVlaue,int16_t RightRealityVlaue)//输入目标设计值
{
	//右边小轮调控
	RightEk = RightTargetVlaue - RightRealityVlaue;//期望值-实际值
	RightPkVlaue = Kp*(RightEk-RightEk_1) + Ki*RightEk + Kd*(RightEk+RightEk_2-2*RightEk_1);
	out_right+=RightPkVlaue;
	if(out_right<0){out_right = 0;}
	if(out_right>100){out_right = 100;} 
	TIM_SetCompare1(TIM1,out_right);	//右前轮
	TIM_SetCompare2(TIM1,out_right);	//右后轮
	RightEk_2 = RightEk_1;
	RightEk_1 = RightEk;
	//结束
}

//void PID_Right_Computer_2(uint16_t RightTargetVlaue,uint16_t RightRealityVlaue)//输入目标设计值
//{
//	//右边小轮调控
//	RightEk = RightTargetVlaue - RightRealityVlaue;//期望值-实际值
//	RightPkVlaue = Kp*(RightEk-RightEk_1) + Ki*RightEk + Kd*(RightEk+RightEk_2-2*RightEk_1);
//	out_right-=RightPkVlaue;
//	if(out_right<0){out_right = 0;}
//	if(out_right>100){out_right = 100;} 
//	TIM_SetCompare1(TIM1,out_right);	//右前轮
//	TIM_SetCompare2(TIM1,out_right);	//右后轮
//	RightEk_2 = RightEk_1;
//	RightEk_1 = RightEk;
//	//结束
//}

void PID_Left_Computer(int16_t LeftTargetVlaue,int16_t LeftRealityVlaue)
{
	//左边小轮调控
	LeftEk = LeftTargetVlaue - LeftRealityVlaue;
	LeftPkVlaue = Kp*(LeftEk-LeftEk_1) + Ki*LeftEk + Kd*(LeftEk+LeftEk_2-2*LeftEk_1);
	out_left += LeftPkVlaue;
	if(out_left<0){out_left = 0;}
	if(out_left>100){out_left = 100;} 	
	TIM_SetCompare3(TIM1,out_left);	//左前轮
	TIM_SetCompare4(TIM1,out_left);	//左后轮
	LeftEk_2 = LeftEk_1;
	LeftEk_1 = LeftEk; 
	//结束
}

//void PID_Left_Computer_2(uint16_t LeftTargetVlaue,uint16_t LeftRealityVlaue)
//{
//	//左边小轮调控
//	LeftEk = LeftTargetVlaue - LeftRealityVlaue;
//	LeftPkVlaue = Kp*(LeftEk-LeftEk_1) + Ki*LeftEk + Kd*(LeftEk+LeftEk_2-2*LeftEk_1);
//	out_left -= LeftPkVlaue;
//	if(out_left<0){out_left = 0;}
//	if(out_left>100){out_left = 100;} 	
//	TIM_SetCompare3(TIM1,out_left);	//左前轮
//	TIM_SetCompare4(TIM1,out_left);	//左后轮
//	LeftEk_2 = LeftEk_1;
//	LeftEk_1 = LeftEk; 
//	//结束
//}
