#include "uart.h"

/**
 * 串口配置
 */
void UART_Init(void)
{   
  UART1_DeInit(); //清除之前的串口配置
  UART1_Init((u32)115200, UART1_WORDLENGTH_8D, UART1_STOPBITS_1, UART1_PARITY_NO,
              UART1_SYNCMODE_CLOCK_DISABLE, UART1_MODE_TXRX_ENABLE);
  //串口配置：波特率115200，字节数8，1个停止位，无奇偶效验位，非同步模式，允许接受和发送
  UART1_Cmd(ENABLE);  //启用串口
}

/**
 * 发送字符
 */ 
void UART_SendChar(char c) 
{
  UART1_SendData8(c);
  while (UART1_GetFlagStatus(UART1_FLAG_TXE)==RESET);
}

/**
 * 发送字符串
 */ 
void UART_SendString(uint8_t *Buffer) //发送一个字符
{
  uint8_t *String;
  String = Buffer;
  while(*String!='\0')
  {
    UART1_SendData8(*String);
    while (UART1_GetFlagStatus(UART1_FLAG_TXE)==RESET);
    String++;
  }
}

/**
 * 接收字符
 */ 
char UART_ReceiveChar(void) 
{
  char c = 0;
  while (UART1_GetFlagStatus(UART1_FLAG_RXNE) == RESET);
  c = UART1_ReceiveData8();
  return c;
}
