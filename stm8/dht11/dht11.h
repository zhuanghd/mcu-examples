#ifndef __DTH11__H
#define __DHT11__H


/*includes----------------------------------------------*/
#include "stm8s.h"


/*definition--------------------------------------------*/
#define DHT11_PORT             (GPIOC)
#define DHT11_PIN              (GPIO_PIN_3)
#define DHT11_Set() 	       (GPIO_WriteHigh(DHT11_PORT,(GPIO_Pin_TypeDef)DHT11_PIN))  //数据线输出高
#define DHT11_Clr() 	       (GPIO_WriteLow(DHT11_PORT,(GPIO_Pin_TypeDef)DHT11_PIN))  //数据线输出低
#define	DHT11_Read()	       (GPIO_ReadInputPin(DHT11_PORT,(GPIO_Pin_TypeDef)DHT11_PIN) != RESET ? 1 : 0)	//读数据线电平


/*定义结构体，保存读取的温度值*/
typedef struct
{
    unsigned char Humi_H;		//湿度的整数部分
    unsigned char Humi_L;	 	//湿度的小数部分
    unsigned char Temp_H;	 	//温度的整数部分
    unsigned char Temp_L;	 	//温度的小数部分
    unsigned char Check_Sum;	 	//校验和
} DHT11_Data;


/*declaration----------------------------------------------*/
unsigned char DHT11_Start(void);  //声明DHT11初始化函数
unsigned char DHT11_Read_Data(DHT11_Data *Data);	//声明读取DHT11数据函数

#endif

