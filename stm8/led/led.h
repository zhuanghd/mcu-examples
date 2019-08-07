#ifndef __LED_H 
#define __LED_H

// LED 对应的 I/O 口（PA1）
#define LED_PORT GPIOA
#define LED_PIN GPIO_PIN_1

/**
 * 初始化 LED 的 I/O 口
 */
void LED_Init(void);

/**
 * 点亮 LED
 */
void LED_TurnON(void);

/**
 * 熄灭 LED
 */
void LED_TurnOFF(void);

#endif