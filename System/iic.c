#include "iic.h"

/**
  * @brief  初始化模拟IIC配置.
  * @retval None
  */
void iic_Init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_OD;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8|GPIO_Pin_9;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	GPIO_SetBits(GPIOB, GPIO_Pin_8|GPIO_Pin_9);
}

/**
  * @brief  SCL总线写电平.
	* @param  value:写电平值.
  * @retval None
  */
void SCL_W(uint8_t value)
{
	GPIO_WriteBit(GPIOB, GPIO_Pin_8,(BitAction)value);//SCL
	Delay_us(10);
}

/**
  * @brief  SDA总线写电平.
	* @param  value:写电平值.
  * @retval None
  */
void SDA_W(uint8_t value)
{
	GPIO_WriteBit(GPIOB, GPIO_Pin_9,(BitAction)value);//SDA
	Delay_us(10);
}

/**
  * @brief  SDA总线读电平.
  * @retval 返回电平值
  */
uint8_t SDA_R(void)
{
	uint8_t value;
	value = GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_9);//SDA,开漏输出 不需要设置输入模式
	Delay_us(10);
	return value;
}

/**
  * @brief  IIC起始信号.
  * @retval None
  */
void iic_start(void)
{
	SCL_W(1);
	SDA_W(1);
	
	SDA_W(0);
	SCL_W(0);
}

/**
  * @brief  IIC停止信号.
  * @retval None
  */
void iic_stop(void)
{
	SDA_W(0);	
	SCL_W(1);
	SDA_W(1);
}

/**
  * @brief  iic发送字节byte.
	* @param  byte:字节数,最后以为读写位,1表示读,0表示写.
  * @retval None
  */
void send_data(uint8_t byte)
{
	uint8_t i=0;
	for(i=0;i<8;i++)//写0000 0001
	{
		SDA_W(byte&0x80);
		byte=byte<<1;
		SCL_W(1);
		SCL_W(0);
	}
}

/**
  * @brief  iic读字节byte.
  * @retval 读取到的字节数
  */
uint8_t read_data(void)
{
	uint8_t i=0,byte=0x00;
	SDA_W(1);//由于是开漏又输出高电平,这是后GPIO就像浮空输入
	for(i=0;i<8;i++)//0110 0100 		0 0 0 0 0 0 0 0
	{
		SCL_W(1);
		if (SDA_R() == 1){byte |= (0x80 >> i);}
//		byte=byte<<1;//此种写法要写在此之前,不然多移了一位
//		if(SDA_R()==1){
//			byte|=0x01;
//		}
		SCL_W(0);
	}
	return byte;
}

/**
  * @brief  iic发送响应信号.
	* @param  ack:响应信号值可能是1|0,0表示回应,1表示不回应.
  * @retval None
  */
void iic_sendAck(uint8_t ack)
{
	SDA_W(ack);
	SCL_W(1);
	SCL_W(0);
}

/**
  * @brief  iic读取响应信号.
  * @retval 返回响应值可能是0|1.
  */
uint8_t iic_readAck(void)
{
	uint8_t ACKvalue=0;
	SDA_W(1);
	SCL_W(1);
	ACKvalue=SDA_R();
	SCL_W(0);
	return ACKvalue;
}
