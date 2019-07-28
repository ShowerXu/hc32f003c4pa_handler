//===========================================================================================================================
//===========================================================================================================================
//本文件实现设备检测功能
//创建者：steve
//创建日期：2018-06- 04
//创建版本：version-1.0
//修改日期：
//修改内容：
//修改版本：
//===========================================================================================================================
#include "config.h"

comm_msg_t handler_msg;
u8 printf_tx_byte;

/*
 * 函数名：Get_ChipID
 * 描述  ：获取芯片ID
 * 输入  ：无
 * 输出  ：无
 */
void Get_ChipID(void)
{
    u32 CpuID[3];
    CpuID[0] = *(volatile u32 *)(0X1ffff7e8);
    CpuID[1] = *(volatile u32 *)(0X1ffff7ec);
    CpuID[2] = *(volatile u32 *)(0X1ffff7f0);
    memcpy(shared.pedestalNo, &CpuID[0], sizeof(shared.pedestalNo));
}

//printf redefined
void api_comm_parm_init(void)
{
    memset((char *)&handler_msg, 0, sizeof(comm_msg_t));
    handler_msg.write.max_len = COMM_BUF_LEN;
    handler_msg.read.max_len = COMM_BUF_LEN;
    Get_ChipID();
}

void uart_protocol_process(u8 *buf, u8 len)
{
    if(buf[0] == 0x01)
    {//aa 55 10 01 ID1 ... ID12 电量 上锁情况 checksum
        memcpy(shared.handler.No, &buf[1], sizeof(stHandlerPwr));
        if(shared.handler.status == 2)
        {
            
        }
    }
}
static void api_comm_handle_pack_prc(u8 *buf)
{
	static u8 cnt = 0;
	static u16 head;
	static u8 data_len;
	static u8 get_len = 0;
	static u8 step = 0;
	static u8 get_buf[128];
	static u8 checksum = 0;
	//head = buf[0];
	//os_printf("RX:%02x ",buf[0]);
	//for(cnt = 1; cnt < len; cnt++)
	{
		//os_printf("%02x ",buf[cnt]);
		if(step == 0)
		{
			head = buf[cnt-1]<<8 | buf[cnt];
			if(head == SYNC_HEAD)
			{
				step = 1;
				data_len = 0;
				get_len = 0;
				checksum = 0;
			}
		}else if(step == 1)
		{
			data_len = buf[cnt];
			step++;
			checksum += buf[cnt];
		}else if(step == 2)
		{
			get_buf[get_len] = buf[cnt];
			checksum += buf[cnt];
			get_len++;
			if(get_len == (data_len-1))
			{
				step = 3;
			}
		}else if(step == 3)
		{
			if(checksum == buf[cnt])
			{
				uart_protocol_process(get_buf, data_len-1);
				step = 0;
				//bsp_uart_tx_string(UsartInstance[index], "ok\n\0", 4);
				//uart0_sendStr("ok\n\0");
				//os_printf("check ok:%d,%d,%d\n",checksum,buf[cnt],cnt);
			}else{
				//uart0_sendStr("failed\n\0");
				//bsp_uart_tx_string(UsartInstance[index], "err\n\0", 5);
				//os_printf("check failed:%d,%d,%d\n",checksum,buf[cnt],cnt);
			}
			step = 0;
		}
	}
}

static void handle_power_prot_analysis(comm_msg_t *msg)
{
    //if(msg->dev_en == 0)return;
    if(msg->read.end_flag)
    //if(msg->read.get_len != msg->read.que_len)
    {
        u8 get_byte;
        u16 get_cnt = 0;

        msg->read.end_flag = 0;
        if(msg->read.get_len == msg->read.que_len)return;
        while(1)
        {
            get_byte = msg->read.que_buf[msg->read.get_len];
            msg->read.get_buf[get_cnt] = get_byte;
            api_comm_handle_pack_prc(msg->read.get_buf);

            msg->read.get_len++;
            get_cnt++;
            if(get_cnt >= sizeof(msg->read.get_buf))get_cnt = 0;
            if(msg->read.get_len > msg->read.max_len)msg->read.get_len = 0;
            if(msg->read.get_len == msg->read.que_len)break;
        }
        sh_printf("\r\n");
    }
}
static void api_handle_power_prot_task(void)
{
    handle_power_prot_analysis(&handler_msg);
}
void api_uart_protocol_task(void)//protocol
{
    api_handle_power_prot_task();
}
u8 api_uart_send_cmd (u8 * cmd, u8 len, char * reply1, char * reply2, u32 waittime)
{
    comm_pack_t *w_pack = (comm_pack_t *)&handler_msg.write;
    comm_pack_t *r_pack = (comm_pack_t *)&handler_msg.read;
	//sprintf(w_pack->que_buf, "%s\r\n", cmd);
	bsp_uart_tx_string(w_pack->que_buf, len);
	if((reply1 == 0) && (reply2 == 0))//不需要接收数据
	{
	    return 1;
    }
    r_pack->get_len = r_pack->que_len = 0;

    w_pack->time_out = waittime;
    r_pack->end_flag = 0;
    while(w_pack->time_out)
    {
        while ((!r_pack->end_flag) && w_pack->time_out);
        r_pack->end_flag = 0;
        handle_power_prot_analysis(&handler_msg);
        //memcpy(r_pack->get_buf, r_pack->que_buf, r_pack->que_len);
        //r_pack->get_buf[r_pack->que_len] = '\0';
    	if((reply1 != 0) && (reply2 != 0))
    	{
    	    if(strstr(r_pack->get_buf, reply1))
    	    {
                return 1;
    	    }else if(strstr(r_pack->get_buf, reply2 ))
    	    {
    		    w_pack->time_out = waittime;
    	    }
     	}
    	else if(reply1 != 0)
    	{
    	    if(strstr(r_pack->get_buf, reply1))
    	    {
    		    return 1;
    	    }
    	}else
    	{
    	    if(strstr(r_pack->get_buf, reply2))
    	    {
    		    w_pack->time_out = waittime;
    	    }
        }
    }
    return 0;
}
void api_send_cmd(char *cmd, u8 len)
{
    u8 fail = 4;

    while(fail--)
    {
        if(api_uart_send_cmd(cmd, len, "CMD OK", "status", 10))
        {
            break;
        }
    }
}
void api_send_cmd_to_wifi(u8 adr,u8 *str,u8 len)
{
    u8 i;
    u8 Chksum;
    u8 *cmd_buf;
	if(!handler_msg.dev_en)return;
    cmd_buf = handler_msg.write.que_buf;
	cmd_buf[0] = SYNC_HEAD>>8;
	cmd_buf[1] = SYNC_HEAD&0xff;
	cmd_buf[2] = len;
	cmd_buf[3] = adr;
	Chksum = (u8)(len + 2);
	Chksum += adr;
	for(i=0;i<len;i++)
	{
		cmd_buf[4+i] = *str;
		Chksum += *str++;
	}
	cmd_buf[4+i] = Chksum;
	api_send_cmd(cmd_buf, len+4);
}

void api_send_handler_sta(u8 lock)
{//发起归还
    u8 buf[128];
    shared.handler.locked = lock;
    memcpy(buf, &shared.handler, sizeof(shared.handler));
    api_send_cmd_to_wifi(CMD_READY_RETURN, buf, sizeof(shared.handler));
}

/*********************************************************
                File End
*********************************************************/
