/********************************************************
 * DHT11的DAT线接单片机的PC3口
 *******************************************************/

/*inclides----------------------------------------------*/
#include "dht11.h"
#include "delay.h"

/*
  @brief 将IO设为输出
  @param 无
  @retval 无
 */
static void DHT11_GPIO_Output(void)
{
  GPIO_Init(DHT11_PORT, (GPIO_Pin_TypeDef)DHT11_PIN, GPIO_MODE_OUT_PP_HIGH_FAST);
}


/*
  @brief 将IO设为浮空输入
  @param 无
  @retval 无
 */
static void DHT11_GPIO_Input(void)
{
  GPIO_Init(DHT11_PORT, (GPIO_Pin_TypeDef)DHT11_PIN, GPIO_MODE_IN_FL_NO_IT);
}


/*
  @brief 对DHT11发送起始信号，并检测DHT11的响应
  @param 无
  @retval 0：DHT11响应  1：DHT11无响应
 */
unsigned char DHT11_Start(void)
{
    unsigned char retry=0;	//定义变量
					
    DHT11_GPIO_Output();	//配置数据总线IO口为输出模式
    DHT11_Clr();	//输出低电平
    DelayMs(20);	//低电平时间T（18ms<T<30ms）,向DHT11发送起始信号
    DHT11_Set();	//拉高总线
    DelayUs(10);	//延迟10us*0.82us
    DHT11_GPIO_Input();	//配置数据总线IO口为输入模式，准备检测DHT11的响应信号
		
/**************************检测DHT11响应的低电平期间*******************************/
    while (DHT11_Read()&&(retry<120))	//等待DHT11将总线拉低，并设置超时时间：120*0.82us
    {
        retry++; //retry加1
        DelayUs(1);	//延迟
    }

    if(retry>=120)	//判断是否超时
        return 1;	//超时返回1，DHT11无响应
    else
        retry=0;	//否则对retry清零


/**************************检测DHT11响应的高电平期间*******************************/
    while ((!DHT11_Read())&&(retry<120))	//等待DHT11将总线拉高，并设置超时时间：120*0.82us
    {
        retry++;	//retry加1
        DelayUs(1);	//延迟
    }

    if(retry>=120)	//判断是否超时
        return 1;	//超时返回1，DHT11无响应
    else
        return 0;	//DHT11响应，返回0
}



/*
  @brief 读一个Bit
  @param 无
  @retval 0：数据0   1：数据1
 */
static unsigned char DHT11_Read_Bit(void)
{
    unsigned char retry = 0;	//定义变量
    while(DHT11_Read()&&retry<120)	//等待DHT11将总线拉低，并设置超时时间：120*0.82us
    {
        retry++;	//retry加1
        DelayUs(1);  //延迟
    }

    retry=0;	//清零
		
    while((!DHT11_Read())&&retry<120)	//等待DHT11将总线拉高，并设置超时时间：120*0.82us
    {
        retry++;	//retry加1
        DelayUs(1); //延迟
    }

    DelayUs(45);//延迟45*8.2us，跳过数据0的高电平时间（23us~27us）

    if(DHT11_Read())	//如果PB0为高
        return 1;	//返回数据1
    else
        return 0; //否则返回数据0
}


/*
  @brief 读一个Byte
  @param 无
  @retval dat：读到的Byte
 */
static unsigned char DHT11_Read_Byte(void)
{
    unsigned char i,dat;  //定义变量
    dat=0; 
    for (i=0; i<8; i++)  //循环8次
    {
        dat<<=1;  //左移
        dat|=DHT11_Read_Bit(); //读一个Bit
    }

    return dat; //返回读到的数据
}


/*
  @brief DHT11读数据
  @param DHT11_Data *Data:传入结构体变量，保存读取的DHT11值
  @retval 0：成功   1：失败
 */
unsigned char DHT11_Read_Data(DHT11_Data *Data)
{
    unsigned char retry = 0;  //定义变量

    Data->Humi_H= DHT11_Read_Byte();	//读出8位数据-->湿度的高八位

    Data->Humi_L= DHT11_Read_Byte();	//读出8位数据-->湿度的低八位

    Data->Temp_H= DHT11_Read_Byte();	//读出8位数据-->温度的高八位

    Data->Temp_L= DHT11_Read_Byte();	//读出8位数据-->温度的低八位

    Data->Check_Sum= DHT11_Read_Byte();	//读出8位数据-->校验数据
		
    while(DHT11_Read()&&retry<120)  //等待DHT11的结束信号（54us低电平），并设置超时时间：120*0.82us
    {
        retry++;  //retry加1
        DelayUs(1);  //延迟
    }

    if(retry>=120)  //判断是否超时
        return 1; //超时返回1，DHT11无响应
    else
        retry=0;  //否则对retry清零

    while((!DHT11_Read())&&retry<120) //等待DHT11的结束信号结束，并设置超时时间：120*0.82us
    {
        retry++;  //retry加1
        DelayUs(1); //延迟
    }

    if(retry>=120)  //判断是否超时
        return 1; //超时返回1，DHT11无响应
    else
        retry=0;  //否则对retry清零

    DHT11_GPIO_Output();	//配置信号总线为输出模式
    DHT11_Set();	//输出高，将总线拉高
    
    if(Data->Check_Sum == Data->Humi_H + Data->Humi_L + Data->Temp_H+ Data->Temp_L)	//检验数据是否正确
        return 0;	//数据正确，读取成功
    else 
        return 1;	//数据错误，读取失败
}




