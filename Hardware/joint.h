#ifndef __JOINT_H
#define __JOINT_H
#include "stm32f10x.h"                  // Device header

void Joint_Init(void);
void PWM_SetCompare3(uint16_t Compare);
void Set_Joint_Angle(float angle);
#endif
