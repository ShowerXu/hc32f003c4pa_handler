//===========================================================================================================================
//���ļ�ʵ�ֵ�ع���Ĺ���
//�����ߣ�steve
//�������ڣ�2014-05-10
//�����汾��version-1.0
//�޸����ڣ�
//�޸����ݣ����½�ʱ��ֱ������Ϊ9.5Vʱ�Źػ�����������ߵ�10.5V���ϵ�ѹ�����¿���
//                          ������ʱ��ֱ������Ϊ17Vʱ�Źػ���������½���16V���µ�ѹ�����¿���
//�޸İ汾��
//===========================================================================================================================
#include "config.h"
#if (CHK_BATT_EN)
BatStruct Bat;
void bsp_batmanage_parm_init(void)
{
    memset((char *)&Bat, 0, sizeof(Bat));
    Bat.WorkState = BAT_NORMAL;
}
static u8 bsp_bat_stable_chk(void)
{
	u16 max,min,i;

	max = Bat.ADBuffer[0];
	min = Bat.ADBuffer[0];
	for(i=1; i<BAT_SAMPLE_LEN; i++){
		if(Bat.ADBuffer[i] > max)max = Bat.ADBuffer[i];
		if(Bat.ADBuffer[i] < min)min = Bat.ADBuffer[i];
	}
	return((max-min) < BAT_STABLE_VALUE);
}

void bsp_bat_manage_task(void)
{// 50ms loop
    if(Bat.ADCnt >= BAT_SAMPLE_LEN)
    {
        u32 bat_conv_value;
        u16 bat_ave_value;
        u8 i;
        Bat.ADCnt = 0;
        /* Calculate AD value average */
        bat_conv_value = 0;
        for(i = 0; i < BAT_SAMPLE_LEN; i++)
        {
            bat_conv_value += Bat.ADBuffer[i];
            //sh_printf("%d,",Bat.ADBuffer[i]);
        }
        //batt_printf(", tol :%d\r\n",bat_conv_value);
        bat_ave_value = bat_conv_value/BAT_SAMPLE_LEN;
        //batt_printf("BATT AD:%d,%d\r\n",bat_ave_value,BAT_LOW_V);
        if((bat_ave_value < BAT_LOW_V))
        {
            //��ص�ѹ�������ޣ���Ҫ�رյ�Դ�������
            Bat.ShutTimer = BAT_SHUT_TIMER;
            if(Bat.WorkState != BAT_ERR)
            {
                if(bsp_bat_stable_chk() != 0)
                {
                    Bat.WorkState = BAT_ERR;
                    BattErrProcess(bat_ave_value);
                }
            }
        }else if((bat_ave_value > BAT_LOW_V))
        {
            //�����������
            if(Bat.WorkState != BAT_NORMAL)
            {
                if((bat_ave_value > BAT_INSERT_V))
                {
                    if(bsp_bat_stable_chk() != 0)
                    {
                        if(Bat.ShutTimer)
                        {
                            Bat.ShutTimer--;
                            if(Bat.ShutTimer == 0)
                            {//������������
                                Bat.WorkState = BAT_NORMAL;
                                BattNormalProcess();
                            }
                        }
                    }
                }
            }
        }
    }else
    {
        Bat.ADBuffer[Bat.ADCnt]= bsp_adc_get_val(BATT_ADC_CHAN);
        Bat.ADCnt++;
    }
}

void BattErrProcess(u16 BatVal)
{
    batt_printf("BattErrProcess:%d\r\n",BatVal);
}

void BattNormalProcess(void)
{
	batt_printf("BattNormalProcess\r\n");
}
#endif
/*********************************************************
                File End
*********************************************************/
