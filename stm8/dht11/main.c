#include "stm8s.h"
#include "delay.h"
#include "dht11.h"

char temp[6]; //用于存放温度数值
char humi[6]; //用于存放湿度数值

static void CLK_Config(void);

void main(void)
{
  DHT11_Data Data;	//定义结构体变量Data，用于存储读取DHT11的值
  
  CLK_Config();
  DelayInit(16);
  
  while (1)
  {
    DelayMs(2000); //延迟2S，2S读一次数据
    
    if(!DHT11_Start())//判断DHT11是否正常工作
    {
      if(DHT11_Read_Data(&Data) == 0)	//判断读取的数据是否正确
      {					
        if(Data.Temp_L & 0x80)	//判断温度是否为负数
        {
            temp[0] = '-';
        }
        else
        {
            temp[0] = '+'; 
        }
        temp[1] = Data.Temp_H/10 + 0x30; //串口把温度整数部分发送出去，ASCII码形式
        temp[2] = Data.Temp_H%10 + 0x30; //串口把温度整数部分发送出去，ASCII码形式
        temp[3] = '.'; //发送小数点
        temp[4] = Data.Temp_L%10 + 0x30; //串口把温度小数部分发送出去，ASCII码形式
        temp[5] = '\0';

        humi[0] = Data.Humi_H/10 + 0x30; //串口把湿度整数部分发送出去，ASCII码形式
        humi[1] = Data.Humi_H%10 + 0x30; //串口把湿度整数部分发送出去，ASCII码形式
        humi[2] = '.'; //发送小数点
        humi[3] = Data.Humi_L%10 + 0x30; //串口把湿度小数部分发送出去，ASCII码形式
        humi[4] = '%'; 
        humi[5] = '\0';
        
        DelayMs(100);
      }
    }
  }

}

static void CLK_Config(void)
{
    CLK_HSIPrescalerConfig(CLK_PRESCALER_HSIDIV1);
}

#ifdef USE_FULL_ASSERT

void assert_failed(uint8_t* file, uint32_t line)
{
  while (1)
  {
  }
}
#endif
