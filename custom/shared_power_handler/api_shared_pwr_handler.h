//===========================================================================================================================
//���ļ�ʵ�ֵ�ع���Ĺ���
//�����ߣ�steve
//�������ڣ�2011-02- 27
//�����汾��version-1.0
//�޸����ڣ�
//�޸����ݣ�
//�޸İ汾��
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
	u8 status;   //0:�ѽ裬1:���� 2:�黹
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

