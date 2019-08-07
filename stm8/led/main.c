#include "stm8s.h"
#include "led.h"

/**
 * 延迟一段时间
 * 只是为了让 LED 持续发光
 */
static void Sleep(u32 time)
{
  unsigned int x,y;
  for(x=time; x>0; x--)
  {
    for(y=200; y>0; y--);
  }
}

void main(void)
{ 
  LED_Init();
  
  while (1)
  {
    LED_TurnON();
    Sleep(1000);
    
    LED_TurnOFF();
    Sleep(1000);
  }
}


#ifdef USE_FULL_ASSERT

void assert_failed(uint8_t* file, uint32_t line)
{
  while (1)
  {
  }
}

#endif


