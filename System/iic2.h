#ifndef __IIC2_H_
#define __IIC2_H_
#include "stm32f10x.h"                  // Device header
#include "stdio.h"
#include "Delay.h"
void SCL2_W(uint8_t value);
void SDA2_W(uint8_t value);
uint8_t SDA2_R(void);

void iic2_Init(void);
void iic2_start(void);
void iic2_stop(void);
void send2_data(uint8_t byte);
uint8_t read2_data(void);
void iic2_sendAck(uint8_t ack);
uint8_t iic2_readAck(void);

#endif
