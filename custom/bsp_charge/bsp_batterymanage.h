//===========================================================================================================================
//本文件实现电池管理的功能
//创建者：steve
//创建日期：2011-02- 27
//创建版本：version-1.0
//修改日期：
//修改内容：
//修改版本：
//===========================================================================================================================
#ifndef _BATTERY_MANAGE_H
#define _BATTERY_MANAGE_H
#include <string.h>
#ifdef __cplusplus
extern "C" {
#endif
#define BAT_SAMPLE_LEN            16// 800ms
//#define BATT_RELEASE
#ifdef BATT_RELEASE
#define batt_printf(format...)   ((void)0)
#else
#define batt_printf(format...)   sh_printf(##format)
#endif
#define VBAT_AD_CALC_VAL(vbat)   (u32)(33000 * 33 * vbat)/(1024*220) //100k上拉，220K下拉

#define VoltageCalcToAd(v)  (u16)(v*4095/3.30)/*把电压值计算转换成12位的数值*/
#define BAT_STABLE_VALUE	VoltageCalcToAd(0.2)


#define BAT_INSERT_V	    3500
#define BAT_LOW_V	        3300

#define BAT_SHUT_TIMER      3// BAT_SAMPLE_LEN* BAT_SHUT_TIMER  >2.1s

typedef enum {
	BAT_NORMAL = 0,
	BAT_ERR,
}BAT_State;
#define BAT_CHK_TIMER   50
typedef struct
{
    u32 CheckTimer;
    u16 ADBuffer[BAT_SAMPLE_LEN];
    u16 ShutTimer;
    u8 ADCnt;
    BAT_State WorkState;
}BatStruct;

extern BatStruct Bat;

void bsp_batmanage_parm_init(void);
void bsp_bat_manage_task(void);
void BattErrProcess(u16 BatVal);
void BattNormalProcess(void);
#ifdef __cplusplus
}
#endif
#endif//_BATTERY_MANAGE_H

/*********************************************************
				File End
*********************************************************/

