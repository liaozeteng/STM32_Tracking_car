#ifndef __PID_H
#define __PID_H
#include "stm32f10x.h"                  // Device header
#include "Timer.h"

void PID_Right_Computer(int16_t RightTargetVlaue,int16_t RightRealityVlaue);
void PID_Left_Computer(int16_t LeftTargetVlaue,int16_t LeftRealityVlaue);

//void PID_Right_Computer_2(uint16_t RightTargetVlaue,uint16_t RightRealityVlaue);
//void PID_Left_Computer_2(uint16_t LeftTargetVlaue,uint16_t LeftRealityVlaue);
#endif
