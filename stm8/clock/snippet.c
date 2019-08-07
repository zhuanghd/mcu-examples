
// ============== 时钟分频 ==============

// 配置 HSI 分频
CLK_HSIPrescalerConfig(CLK_PRESCALER_HSIDIV1); 　

// 配置 CPU 分频
CLK_SYSCLKConfig(CLK_PRESCALER_CPUDIV1);

// 配置 HSI 分频
CLK_SYSCLKConfig(CLK_PRESCALER_HSIDIV1);


// ============== 时钟切换 ==============

CLK_DeInit();  //时钟各变量重置
CLK_HSECmd(ENABLE); //外部高速晶振使能
while(SET != CLK_GetFlagStatus(CLK_FLAG_HSERDY)); //判断外部高速晶振位是不是使能
CLK_SYSCLKConfig(CLK_PRESCALER_CPUDIV1); //外部时钟预分频器设置（1分频）
CLK_ClockSwitchCmd(ENABLE); //使能时钟切换功能
//执行时钟切换 (自动切换模式, 切换到外部高速晶振 , 禁止切换中断 , 当前钟状态为使能)
CLK_ClockSwitchConfig(CLK_SWITCHMODE_AUTO, CLK_SOURCE_HSE, DISABLE, CLK_CURRENTCLOCKSTATE_ENABLE);


// ============== 获取频率 ==============

freq = CLK_GetClockFreq(); // 启动频率 2000000


// ============== 时钟安全 ==============

/* 使能时钟安全系统中断 */
CLK_ITConfig(CLK_IT_CSSD, ENABLE);

/* 使能时钟安全系统 */
CLK_ClockSecuritySystemEnable();


// ============== 时钟输出 ==============

// CLK_OUTPUT_HSI, CLK_OUTPUT_LSI, CLK_OUTPUT_HSE, CLK_OUTPUT_CPU ...
CLK_CCOConfig(CLK_OUTPUT_HSI);
CLK_CCOCmd(ENABLE);

