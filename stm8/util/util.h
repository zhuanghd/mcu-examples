#ifndef __UTIL_H 
#define __UTIL_H

//防锁按钮
#define PREVENT_LOCK_PORT (GPIOC)
#define PREVENT_LOCK_PINS (GPIO_PIN_5)

/**
 * 防锁代码
 */
void PreventLock(void);

#endif