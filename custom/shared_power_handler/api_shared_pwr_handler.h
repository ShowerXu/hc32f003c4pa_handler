//===========================================================================================================================
//本文件实现电池管理的功能
//创建者：steve
//创建日期：2011-02- 27
//创建版本：version-1.0
//修改日期：
//修改内容：
//修改版本：
//===========================================================================================================================
#ifndef _API_SHARED_PWR_HANDLER_H
#define _API_SHARED_PWR_HANDLER_H
#include <string.h>
#ifdef __cplusplus
extern "C" {
#endif

#define MCU_ID_LEN_MAX                    12
typedef struct{
	u8 No[MCU_ID_LEN_MAX];
	u8 status;   //0:已借，1:存在 2:归还
	u8 bat_level;
	u8 locked;
}stHandlerPwr;
typedef struct{
	stHandlerPwr handler;
}stSharedDevInfo;
extern stSharedDevInfo  shared;
#ifdef __cplusplus
}
#endif
#endif//_API_SHARED_PWR_HANDLER_H

/*********************************************************
				File End
*********************************************************/

