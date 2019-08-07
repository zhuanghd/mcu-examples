#ifndef  __DELAY_H 
#define  __DELAY_H

#define u8  unsigned char
#define u16 unsigned short 

void DelayInit(u8 clk);
void DelayUs(u16 nus);
void DelayMs(u16 nms);

#endif