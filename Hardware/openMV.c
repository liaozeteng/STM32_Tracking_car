#include "openMV.h"
#include "MPU6050.h"
extern uint8_t xunji_Flag;
uint8_t OpenMV_Data_count = 0;
uint8_t flagOpenMV = 0;			//openmv计数标志位
uint8_t flag2 = 0;					//改变中线循迹的速度三个等级(8,8)(10,10)(25,25)


uint8_t flag5 = 0;
uint8_t flag6 = 0;
uint8_t flag7 = 0;
uint8_t flag8 = 0;
uint8_t flag9 = 0;
//
uint8_t flag3 = 0;
uint8_t flag10 = 0;
uint8_t flag11 = 0;
uint8_t flag15 = 0;				//关闭重复计数
//
uint8_t flag4 = 0;
uint8_t flag12 = 0;
uint8_t flag13 = 0;
uint8_t flag14 = 0;

extern uint8_t countflag;		//用来关闭和开启计数功能
void OpenMVFind(uint8_t FindData)
{
	switch(FindData){
		case(0x3C)://00011000
			if(flag2 == 1){Set_CarTurn(10,10);}
			if(flag2 == 2){Set_CarTurn(8,8);}
			else{Set_CarTurn(25,25);}
			break;
		case(0x1E)://00001100
			Set_CarTurn(20,16);break;
		case(0x78)://00110000
			Set_CarTurn(16,20);break;
		case(0x0F)://00000110
			Set_CarTurn(19,13);break;
		case(0xF0)://01100000
			Set_CarTurn(13,19);break;
		case(0xE0)://11000000
			Set_CarTurn(10,19);break;
		case(0x07)://00000011
			Set_CarTurn(19,10);break;
		case(0x03)://00000001
			Set_CarTurn(18,7);break;
		case(0xC0)://10000000
			Set_CarTurn(7,18);break;
		case(0x01)://00000001
			Set_CarTurn(30,4);break;
		case(0x80)://10000000
			Set_CarTurn(4,30);break;
		case(0x7C)://00000001
			Set_CarTurn(13,19);break;
		case(0x3E)://10000000
			Set_CarTurn(19,13);break;
		
//		case(0x0E)://00001110
//			Set_CarTurn(25,18);break;
//		case(0x70)://01110000
//			Set_CarTurn(18,25);break;
		
	}
}

void OpenMV_Set_Countstatus(void)
{
	uint8_t flag = 0;					 //存储传感器读到的姿态数据
	if(OpenMV_Data_count == 1){//循迹到第一个黑线后
		if(flag15 == 0){
			countflag = 0;	//关闭计数
			xunji_Flag = 0; //关闭循迹
			Set_CarTurn(25,25);
		}				
		flag = MPU6050_Status();//然后开始不断检测传感器姿态
		//Delay_ms(10);
		if(flag == 1){GPIO_ResetBits(GPIOB,GPIO_Pin_15);	//上第一个坡
			//Set_CarTurn(25,25);
			flag3 = 1;
		}
		if(flag3 == 1 && flag == 3){GPIO_SetBits(GPIOB,GPIO_Pin_15);//到坡顶
			//Set_CarTurn(25,25);
			flag10 = 1;
			flag3 = 0;
		}		
		if(flag10 == 1 && flag == 2){GPIO_ResetBits(GPIOB,GPIO_Pin_15);//在下坡
			//Set_CarTurn(25,25);
			flag11 = 1;
			flag10 = 0;
		}
		if(flag11 == 1 && flag == 3){GPIO_SetBits(GPIOB,GPIO_Pin_15);	 //到平地
			flag11 = 0;
			countflag = 1;					//开启计数
			flag15 = 1;
			xunji_Flag = 1; 	//开启循迹
		}
	}
	if(OpenMV_Data_count == 2){
		//flag2 = 1;							//中线减速到10，准备迎接台阶
		//Set_CarTurn(10,10);
		if(flag14 == 0){countflag = 0;}					//关闭计数
		flag = MPU6050_Status();//然后开始不断检测传感器姿态
		//Delay_ms(10);
		if(flag == 1 && flag13 == 0){GPIO_ResetBits(GPIOB,GPIO_Pin_15);			//到达第一个上坡
			Set_CarTurn(11,11);		//将速度设置成11
			PCA9685_setAngle(0,0,80);//出大臂
			PCA9685_setAngle(0,0,80);//出大臂
			PCA9685_setAngle(0,0,80);//出大臂
			flag2 = 2;			//中线加速为(8,8)
			flag13 = 1;
			flag12 = 1;
		}	
		if(flag == 3 && flag12 == 1){GPIO_SetBits(GPIOB,GPIO_Pin_15);//到达第一个平地
			flag12 = 0;		//关闭平地亮灯
			flag4 = 1;		//到达第一个平地标志位
		}//平地亮灯
		if(flag == 1 && flag4 == 1){GPIO_ResetBits(GPIOB,GPIO_Pin_15);//到达第二个上坡
			flag4 = 0;
			flag5 = 1;
		}
		if(flag5 == 1 && flag == 3){GPIO_SetBits(GPIOB,GPIO_Pin_15);	//到达最高台阶
			Set_CarTurn(2,2);
			PCA9685_setAngle(1,0,60);//倾斜小臂载盘
			flag6 = 1;
			flag5 = 0;
		}
		if(flag6 == 1 && flag == 2){GPIO_ResetBits(GPIOB,GPIO_Pin_15);	//下第一个台阶
			flag7 = 1;
			flag6 = 0;
		}
		if(flag7 == 1 && flag == 3){GPIO_SetBits(GPIOB,GPIO_Pin_15);	//到达下第一个平地
			Set_CarTurn(1,1);
			flag2 = 2;			//中线加速为(8,8)
			flag8 = 1;
			flag7 = 0;
		}
		if(flag8 == 1 && flag == 2){GPIO_ResetBits(GPIOB,GPIO_Pin_15);	//到达下第二个台阶
			flag2 = 2;			//中线加速为(8,8)
			flag9 = 1;
			flag8 = 0;
			Set_CarTurn(1,1);
			//Delay_s(5);
		}
		if(flag9 == 1 && flag == 3){GPIO_SetBits(GPIOB,GPIO_Pin_15);	//到达下第二个平地
			countflag = 1;		//开启计数
			flag14 = 1;
			Delay_s(1);
			flag2 = 3;				//开启中线加速(25,25)
			flag9 = 0;
			PCA9685_setAngle(1,0,90);
			PCA9685_setAngle(0,0,170);
		}
	}
	if(OpenMV_Data_count == 3){
		flag2 = 2;		//改变中线速度(8,8)
		Set_CarTurn(8,8);
		USART_Cmd(USART1,ENABLE);//使能颜色识别
		OpenMV_Data_count = 4;
	}
}

void OpenMV_Get_SensorState(uint8_t FindData)
{
	if(FindData == 0xFF && flagOpenMV == 0){
		flagOpenMV = 1;
		OpenMV_Data_count++;
	}
	if(FindData != 0xFF && flagOpenMV == 1){
		flagOpenMV = 0;
	}
}

