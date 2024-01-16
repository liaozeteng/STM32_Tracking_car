#ifndef  __USART_H
#define  __USART_H
#include "stm32f10x.h"                  // Device header
#include "Delay.h"

void Usart1_Init(void);
void Usart3_Init(void);
void Send_String(char strdata[],uint32_t strlen);
void Send_Usart_String(char strdata[],uint32_t strlen);
#endif



