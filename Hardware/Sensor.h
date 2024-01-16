#ifndef __SENSOR_H
#define __SENSOR_H
#include "stm32f10x.h"                  // Device header

void Sensor_Init(void);
uint8_t Get_SensorState(void);
#endif
