/**
  ******************************************************************************
  * �ļ�: drv_iwdg.c
  * ����: steve
  * �汾: V1.0.0
  * ����: IWDG �м������ʼ�� IWDG
  ******************************************************************************
  *
  *                  ��Ȩ���� (C): steve
  *                                
  *
  ******************************************************************************
  */
  
/* Includes ------------------------------------------------------------------*/
#include "config.h"

/**
  * ����: ��ʼ�� IWDG������ IWDG Ԥ��Ƶ������ֵ
  * ����: iwdg_prescaler: IWDG Ԥ��Ƶ
  *       time_out_ms: IWDG ��ʱʱ�䣬��λΪ����
  * ����: ��
  */
void bsp_clk_cfg(void)
{    
    u32 u32Val;
    stc_clk_systickcfg_t stcCfg;
    #if 1
    //RCH 24MHz
    Clk_SwitchTo(ClkRCL);
    Clk_SetRCHFreq(ClkFreq22_12Mhz);
    Clk_SwitchTo(ClkRCH);
    u32Val = Clk_GetHClkFreq();
    #endif
    DDL_ZERO_STRUCT(stcCfg);
    stcCfg.enClk = ClkRCH;          //hclk/8
    stcCfg.u32LoadVal = 0xF9Fu;     //1ms
    Clk_SysTickConfig(&stcCfg);
    SysTick_Config(stcCfg.u32LoadVal);
}

/*************************************************************************************/
