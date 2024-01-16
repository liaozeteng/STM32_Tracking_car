#ifndef __TB6612_H
#define __TB6612_H
#include "stm32f10x.h"                  // Device header
#include "PID.h"
#include "Delay.h"
#include "stdio.h"
void TB6612_GPIO_Init(void);

void Set_CarForward(void);
void Set_CarRetreat(void);
void Set_CarStop(void);

void Set_CarTurn(int16_t Left,int16_t Right);
void Set_CarRight(void);
void Set_CarPosture(void);

void Set_CarLeftBuck_CarRightForward(int16_t Left,int16_t Right);
void Set_CarLeftForward_CarRightBuck(int16_t Left,int16_t Right);
#endif
