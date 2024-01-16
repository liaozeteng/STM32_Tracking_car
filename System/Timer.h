#ifndef __TIMER_H
#define __TIMER_H
#include "stm32f10x.h"                  // Device header
#include "PID.h"
#include "Usart.h"
#include "openMV.h"
#include <string.h>
#include "tb6612.h"

void TIM2_Measure_Speed_Init(void);
void TIM3_Measure_Speed_Init(void);
void TIM4_Timer_Init(uint16_t per,uint16_t psc);

int16_t Left_Encoder_Get(void);
int16_t Right_Encoder_Get(void);
#endif
