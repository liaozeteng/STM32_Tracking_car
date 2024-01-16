#ifndef __IIC_H_
#define __IIC_H_
#include "stm32f10x.h"                  // Device header
#include "stdio.h"
#include "Delay.h"
void SCL_W(uint8_t value);
void SDA_W(uint8_t value);
uint8_t SDA_R(void);

void iic_Init(void);
void iic_start(void);
void iic_stop(void);
void send_data(uint8_t byte);
uint8_t read_data(void);
void iic_sendAck(uint8_t ack);
uint8_t iic_readAck(void);

#endif
