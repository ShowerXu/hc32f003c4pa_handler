//===========================================================================================================================
//���ļ�ʵ���豸��⹦��
//�����ߣ�steve
//�������ڣ�2018-06- 04
//�����汾��version-1.0
//�޸����ڣ�
//�޸����ݣ�
//�޸İ汾��
//===========================================================================================================================
#ifndef __API_UART_PROTOCOL_H__
#define __API_UART_PROTOCOL_H__


#ifdef __cplusplus
extern "C" {
#endif
#define SYNC_HEAD          0xaa55
typedef enum
{
	CMD_READY_RENT = 1,////�����������
	CMD_READY_RETURN,//����黹
	CMD_READY_RETURN_NOTIFY,//�ֱ��黹���
	CMD_READY_NOTIFY,//֪ͨ�����
}eUART_CMD;

enum{
    UART_RX_STATE_READY = 0,
    UART_RX_STATE_START,
};
#define HANDLE_POWER_UNIT           4
#define COMM_BUF_LEN              100
typedef struct
{
    char get_buf[COMM_BUF_LEN+1];
    char que_buf[COMM_BUF_LEN+1];
    u16 que_len;
    u16 get_len;
    u16 max_len;
    u8 end_flag;
    u32 time_out;
}comm_pack_t;
typedef struct
{
    comm_pack_t read;
    comm_pack_t write;
    u8 dev_en;
}comm_msg_t;

extern comm_msg_t handler_msg;

void api_uart_protocol_task(void);
u8 api_uart_send_cmd (u8 * cmd, u8 len, char * reply1, char * reply2, u32 waittime);
void api_comm_cmd(char *cmd);
void api_comm_parm_init(void);
void api_send_handler_sta(u8 lock);
#ifdef __cplusplus
}
#endif
#endif//__API_UART_PROTOCOL_H__

/*********************************************************
				File End
*********************************************************/

