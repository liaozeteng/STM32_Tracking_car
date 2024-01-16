#ifndef __OPENMV_H
#define __OPENMV_H
#include "stm32f10x.h"                  // Device header
#include "Usart.h"
#include "tb6612.h"
#include "Sensor.h"
#include "PID.h"
#include "joint.h"
#include "pac9685.h"
void OpenMVFind(uint8_t FindData);
void OpenMV_Set_Countstatus(void);
void OpenMV_Get_SensorState(uint8_t FindData);
#endif
