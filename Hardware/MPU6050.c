#include "MPU6050.h"

MPU6050_Angle data;
/****************************************************************************** 
* 函数介绍： MPU6050 写寄存器函数 
* 输入参数： regAddr：寄存器地址 regData：待写入寄存器值 
* 输出参数： 无 
* 返回值 ： 无 
******************************************************************************/
void MPU6050_Write_Reg(uint8_t regAddr, uint8_t regData)
{
    /* 发送起始信号 */
    iic2_start();
    
    /* 发送设备地址 */        
    send2_data(DEV_ADDR);
    iic2_readAck(); 
    
    /* 发送寄存器地址 */
    send2_data(regAddr);
    iic2_readAck();
    
    /* 写数据到寄存器 */
    send2_data(regData);
    iic2_readAck();
    
    iic2_stop();
}

uint8_t MPU6050_Read_Reg(uint8_t regAddr)
{
    uint8_t regData;
    
    /* 发送起始信号 */
    iic2_start();
    
    /* 发送设备地址 */        
    send2_data(DEV_ADDR);
		iic2_readAck();
    
    /* 发送寄存器地址 */
    send2_data(regAddr);
    iic2_readAck();
    
    /* 发送重复起始信号 */
    iic2_start();
    
    /* 发送读模式设备地址 */     
    send2_data(DEV_ADDR | 0x01);
    iic2_readAck();
    
    /* 读寄存器数据 */
    regData = read2_data();
    iic2_sendAck(1);  // 非应答信号     
		
    iic2_stop();
    
    return regData;
}


/****************************************************************************** 
* 函数介绍： 连续读两个寄存器并合成 16 位数据 
* 输入参数： regAddr：数据低位寄存器地址 
* 输出参数： 无 
* 返回值 ： data：2 个寄存器合成的 16 位数据 
******************************************************************************/
int16_t MPU6050_Get_Data(uint8_t regAddr)
{
    uint8_t Data_H, Data_L;
    uint16_t data;
    
    Data_H = MPU6050_Read_Reg(regAddr);
    Data_L = MPU6050_Read_Reg(regAddr + 1);
    data = (Data_H << 8) | Data_L;  // 合成数据 
    return data;
}

/****************************************************************************** 
* 函数介绍： 计算 x, y, z 三轴的倾角 
* 输入参数： 无 
* 输出参数： data：角度结构体 
* 返回值 ： 无 
******************************************************************************/
void MPU6050_Get_Angle(MPU6050_Angle *data)
{ 
    /* 计算x, y, z 轴倾角，返回弧度值*/
    data->X_Angle = acos((MPU6050_Get_Data(ACCEL_XOUT_H) + X_ACCEL_OFFSET) / 16384.0);
    data->Y_Angle = acos((MPU6050_Get_Data(ACCEL_YOUT_H) + Y_ACCEL_OFFSET) / 16384.0);
    data->Z_Angle = acos((MPU6050_Get_Data(ACCEL_ZOUT_H) + Z_ACCEL_OFFSET) / 16384.0);

    /* 弧度值转换为角度值 */
    data->X_Angle = data->X_Angle * 57.29577;
    data->Y_Angle = data->Y_Angle * 57.29577;
    data->Z_Angle = data->Z_Angle * 57.29577;
} 


/****************************************************************************** 
* 函数介绍： MPU6050 初始化函数 
* 输入参数： 无 
* 输出参数： 无 
* 返回值 ： 无 
* 备 注： 配置 MPU6050 测量范围：± 2000 °/s ± 2g 
******************************************************************************/
void MPU6050_Init(void)
{
    iic2_Init();  // I2C 初始化     

    MPU6050_Write_Reg(PWR_MGMT_1, 0x00);    //解除休眠状态 
		//MPU6050_Write_Reg(PWR_MGMT_2,	0x00);
    MPU6050_Write_Reg(SMPLRT_DIV, 0x07);    //陀螺仪采样率，典型值：0x07(125Hz)     
    MPU6050_Write_Reg(CONFIG, 0x06);        //低通滤波频率，典型值：0x06(5Hz)     
    MPU6050_Write_Reg(GYRO_CONFIG, 0x18);   //陀螺仪自检及测量范围，典型值：0x18(不自检，2000deg/s)     
    MPU6050_Write_Reg(ACCEL_CONFIG, 0x01);  //加速计自检、测量范围及高通滤波频率，典型值：0x01(不自检，2G，5Hz) 
}

uint8_t MPU6050_Status(void)
{
	uint8_t status=0;
	MPU6050_Get_Angle(&data);
	if(data.X_Angle >= 110 && data.X_Angle <= 128){
		status = 1;//在上坡
	}
	if(data.X_Angle <= 74 && data.X_Angle >= 61){
		status = 2;//在下坡
	}
	if(data.X_Angle <= 95 && data.X_Angle >=90){
		status = 3;
	}
	return status;
}

