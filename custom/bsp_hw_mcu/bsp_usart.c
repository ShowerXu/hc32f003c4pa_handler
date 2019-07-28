/**
  ******************************************************************************
  * 文件: bsp_usart.c
  * 作者: steve
  * 版本: V1.0.0
  * 描述: 串口中间件，配置串口
  ******************************************************************************
  *
  *                  版权所有 (C): steve
  *
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "config.h"

void RxIntCallback(void)
{
    handler_msg.read.que_buf[handler_msg.read.que_len] = M0P_UART1->SBUF;
    handler_msg.read.que_len++;
    if(handler_msg.read.que_len > handler_msg.read.max_len)
    {
        handler_msg.read.que_len = 0;
    }
    handler_msg.read.end_flag = 1;
}
void ErrIntCallback(void)
{

}
/**
  * 描述: 向串口发送一个字符
  * 参数: ch: 将要发送的字符
  * 返回: 无
  */
void bsp_usart_send_byte(uint8_t ch)
{

}

void bsp_uart_tx_string(u8 *buf, u8 len)
{
    while(len--)
    {
        bsp_usart_send_byte(*buf++);
    }
}
/**
  * 描述: 初始化串口
  * 参数: 无
  * 返回: 无
  */
void bsp_usart_init(void)
{
    uint16_t timer=0;
    uint32_t pclk=0;
    stc_uart_config_t  stcConfig;
    stc_uart_irq_cb_t stcUartIrqCb;
    stc_uart_multimode_t stcMulti;
    stc_uart_baud_config_t stcBaud;
    stc_bt_config_t stcBtConfig;


    DDL_ZERO_STRUCT(stcUartIrqCb);
    DDL_ZERO_STRUCT(stcMulti);
    DDL_ZERO_STRUCT(stcBaud);
    DDL_ZERO_STRUCT(stcBtConfig);


    Gpio_InitIO(T1_PORT,T1_PIN,GpioDirIn);
    Gpio_InitIO(0,3,GpioDirOut);
    Gpio_SetIO(0,3,1);

    Gpio_InitIOExt(3,5,GpioDirOut,TRUE,FALSE,FALSE,FALSE);
    Gpio_InitIOExt(3,6,GpioDirOut,TRUE,FALSE,FALSE,FALSE);

    //通道端口配置
    Gpio_SetFunc_UART1TX_P35();
    Gpio_SetFunc_UART1RX_P36();

    //外设时钟使能
    Clk_SetPeripheralGate(ClkPeripheralBt,TRUE);//模式0/2可以不使能
    Clk_SetPeripheralGate(ClkPeripheralUart1,TRUE);



    stcUartIrqCb.pfnRxIrqCb = RxIntCallback;
    stcUartIrqCb.pfnTxIrqCb = NULL;
    stcUartIrqCb.pfnRxErrIrqCb = ErrIntCallback;
    stcConfig.pstcIrqCb = &stcUartIrqCb;
    stcConfig.bTouchNvic = TRUE;


    stcConfig.enRunMode = UartMode3;//测试项，更改此处来转换4种模式测试


    stcMulti.enMulti_mode = UartNormal;//测试项，更改此处来转换多主机模式，mode2/3才有多主机模式

    stcConfig.pstcMultiMode = &stcMulti;

    stcBaud.bDbaud = 0u;//双倍波特率功能
    stcBaud.u32Baud = 115200u;//更新波特率位置
    stcBaud.u8Mode = UartMode3; //计算波特率需要模式参数
    pclk = Clk_GetPClkFreq();
    timer=Uart_SetBaudRate(UARTCH1,pclk,&stcBaud);

    stcBtConfig.enMD = BtMode2;
    stcBtConfig.enCT = BtTimer;
    Bt_Init(TIM1, &stcBtConfig);//调用basetimer1设置函数产生波特率
    Bt_ARRSet(TIM1,timer);
    Bt_Cnt16Set(TIM1,timer);
    Bt_Run(TIM1);

    Uart_Init(UARTCH1, &stcConfig);
    Uart_EnableIrq(UARTCH1,UartRxIrq);
    Uart_ClrStatus(UARTCH1,UartRxFull);
    Uart_EnableFunc(UARTCH1,UartRx);

    sh_printf("bsp_usart_init\r\n");
}

/*************************************************************************************/
