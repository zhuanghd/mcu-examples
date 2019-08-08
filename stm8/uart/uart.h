#ifndef __UART_H
#define __UART_H

#include "stm8s.h"
#include "stm8s_clk.h"

/**
 * 串口配置
 */ 
void UART_Init(void);

/**
 * 发送字符
 */ 
void UART_SendChar(char c);

/**
 * 发送字符串
 */
void UART_SendString(uint8_t *Buffer);

/**
 * 接收字符
 */ 
char UART_ReceiveChar(void);

#endif /* __UART_H */