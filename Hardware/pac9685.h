#ifndef __PAC9685_H
#define __PAC9685_H
#include "stm32f10x.h"                  // Device header
#include "iic.h"

void PCA9685_Write(uint8_t addr,uint8_t data);
uint8_t PCA9685_Read(uint8_t addr);
void PCA9685_setFreq(float freq);
void PCA9685_setPWM(uint8_t num,uint32_t on,uint32_t angle);
void PCA9685_Init(float hz,uint8_t angle);
void PCA9685_setAngle(uint8_t num,uint32_t on,uint16_t angle);
void PCA0685_work(void);
#endif
