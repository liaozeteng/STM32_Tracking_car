#include "pac9685.h"

void PCA9685_Write(uint8_t addr,uint8_t data)
{
	iic_start();
	
	send_data(0x80);
	iic_readAck();
	
	send_data(addr);
	iic_readAck();
	
	send_data(data);
	iic_readAck();
	
	iic_stop();
	
}

uint8_t PCA9685_Read(uint8_t addr)
{
	uint8_t data;
	
	iic_start();
	
	send_data(0x80);
	iic_readAck();
	
	send_data(addr);
	iic_readAck();
	
	iic_stop();
	
	Delay_us(10);
	
	iic_start();

	send_data(0X80|0x01);
	iic_readAck();
	
	data = read_data();
	iic_sendAck(0);
	
	iic_stop();
	
	return data;
}

void PCA9685_setFreq(float freq)//freq想要设计的频率
{
	uint8_t prescale;
	float prescaleval;
	
	freq *= 0.95f;	//纠正频率设置中的过冲，进行校准
	
	//prescaleval=round(25M/4096/freq)-1;	
	prescaleval = 25000000.0f;
	prescaleval /= 4096;
	prescaleval /= freq;
	prescaleval -= 1;
	prescale = (uint8_t)(prescaleval + 0.5f);//向上取整

	PCA9685_Write(0X00, 0x10);  	  //进入SLEEP模式
	Delay_ms(2);
	PCA9685_Write(0XFE, prescale);    //设置频率
	PCA9685_Write(0X00, 0x00);		  //退出SLEEP模式
	Delay_ms(2);
	PCA9685_Write(0X00, 0xA0); //RESTART、AI 置1
	Delay_ms(500);//一定得延时 否则修改不了
	
}


/*
功能：设置占空比用，通常on为0
on:高电平的起始计数值
off:高电平结束后的计数值
*/

void PCA9685_setPWM(uint8_t num,uint32_t on,uint32_t off)
{
	//uint32_t off = 0;
	//off = (uint32_t)(102+angle*2.28);
	iic_start();
	
	send_data(0x80);
	iic_readAck();
	
	send_data(0x06+4*num);
	iic_readAck();
	
	send_data(on&0xFF);
	iic_readAck();
	
	send_data(on>>8);
	iic_readAck();
	
	send_data(off&0xFF);
	iic_readAck();
	
	send_data(off>>8);
	iic_readAck();
	
	iic_stop();
}


void PCA9685_Init(float hz,uint8_t angle)
{
//	uint32_t off = 0;
	iic_Init();
	PCA9685_Write(0x00,0x00);
	PCA9685_setFreq(hz);
//	off = (uint32_t)(102+angle*2.28);
//	PCA9685_setPWM(0,0,off);
//	PCA9685_setPWM(1,0,off);
//	PCA9685_setPWM(2,0,off);
//	PCA9685_setPWM(3,0,off);
//	PCA9685_setPWM(4,0,off);
//	PCA9685_setPWM(5,0,off);
//	PCA9685_setPWM(6,0,off);
//	PCA9685_setPWM(7,0,off);
//	PCA9685_setPWM(8,0,off);
//	PCA9685_setPWM(9,0,off);
//	PCA9685_setPWM(10,0,off);
//	PCA9685_setPWM(11,0,off);
//	PCA9685_setPWM(12,0,off);
//	PCA9685_setPWM(13,0,off);
//	PCA9685_setPWM(14,0,off);
//	PCA9685_setPWM(15,0,off);

//	Delay_ms(100);
	
}


void PCA9685_setAngle(uint8_t num,uint32_t on,uint16_t angle)
{
	uint32_t off = 0;
	off = (uint32_t)(102+angle*2.28);
	PCA9685_setPWM(num,on,off);
}

void PCA0685_work(void)
{
	PCA9685_setAngle(0,0,170);//大手臂收
	PCA9685_setAngle(0,0,170);//大手臂收
	PCA9685_setAngle(0,0,170);//大手臂收
	Delay_ms(500);
	PCA9685_setAngle(0,0,60);//大手臂出
	PCA9685_setAngle(0,0,60);//大手臂出
	Delay_s(2);
	
	PCA9685_setAngle(1,0,90);//小手臂收
	PCA9685_setAngle(1,0,90);//小手臂收
	Delay_ms(500);
	PCA9685_setAngle(1,0,180);//小手臂倒
	PCA9685_setAngle(1,0,180);//小手臂倒
	PCA9685_setAngle(1,0,180);//小手臂倒
	Delay_s(1);
	PCA9685_setAngle(1,0,90);//小手臂收
	PCA9685_setAngle(0,0,170);//大手臂收
}

