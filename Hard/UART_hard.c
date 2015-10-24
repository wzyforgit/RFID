#include"common.h"

volatile BOOL UART2_send;//串口2发送允许标记

void InitUART2(void)
{
	S2CON=S2SM1|S2REN;		//方式1 接收允许
	BRT=250;				//115200-N-8-1
	AUXR=BRTx12|BRTR|S2SMOD;//波特率*24,独立波特率发生器开
	IE2|=ES2;				//串口2中断开
	S2CON&=~(S2TI|S2RI);	//清除接收/发送标志
	UART2_send=1;			//发送允许
}

BOOL UARTSendChar(uint8 DATA)
{
	if(UART2_send)
	{
		S2BUF=DATA;
		UART2_send=0;
		return TRUE;
	}
	return FALSE;
}

//115200-N-8-1
void isr_UART2(void) interrupt 8
{
	if(S2CON&S2RI)
	{
		PC_cmd=S2BUF;
		S2CON&=~(S2RI);
	}
	if(S2CON&S2TI)
	{
		S2CON&=~(S2TI);
		UART2_send=1;
	}
}