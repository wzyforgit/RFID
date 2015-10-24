#include"common.h"

volatile BOOL UART2_send;//����2����������

void InitUART2(void)
{
	S2CON=S2SM1|S2REN;		//��ʽ1 ��������
	BRT=250;				//115200-N-8-1
	AUXR=BRTx12|BRTR|S2SMOD;//������*24,���������ʷ�������
	IE2|=ES2;				//����2�жϿ�
	S2CON&=~(S2TI|S2RI);	//�������/���ͱ�־
	UART2_send=1;			//��������
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