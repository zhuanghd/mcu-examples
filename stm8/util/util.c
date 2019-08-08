#include "stm8s.h"
#include "util.h"


/**
 * 防锁代码
 * 防止因 SWIM 无法通信而导致芯片无法编程
 */
void PreventLock(void)
{
  GPIO_Init(PREVENT_LOCK_PORT, (GPIO_Pin_TypeDef)PREVENT_LOCK_PINS, GPIO_MODE_IN_PU_NO_IT);
  if(!GPIO_ReadInputPin(PREVENT_LOCK_PORT, PREVENT_LOCK_PINS))
  {
    while(1);
  }
  GPIO_DeInit(PREVENT_LOCK_PORT);
}

