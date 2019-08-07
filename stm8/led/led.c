#include "stm8s.h"
#include "led.h"

/**
 * 初始化 LED 的 I/O 口
 * 将引脚设置为
 */
void LED_Init(void) 
{
  GPIO_Init(LED_PORT, (GPIO_Pin_TypeDef)LED_PIN, GPIO_MODE_OUT_PP_LOW_FAST);
}

/**
 * 点亮 LED
 * 由于 LED 负极连接单片机，属于低电平点亮
 */
void LED_TurnON(void)
{
  GPIO_WriteLow(LED_PORT, (GPIO_Pin_TypeDef)LED_PIN);
}

/**
 * 熄灭 LED
 * 由于 LED 负极连接单片机，高电平才会熄灭
 */
void LED_TurnOFF(void)
{
  GPIO_WriteHigh(LED_PORT, (GPIO_Pin_TypeDef)LED_PIN);
}