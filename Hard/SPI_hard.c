#include"common.h"

volatile BOOL SPI_send;//SPI����������
volatile BOOL SPI_ren; //SPI����������
volatile uint8 SPI_re; //SPI�յ�������

void InitSPI(void)
{
	SPSTAT=SPIF|WCOL;//���SPI״̬
	SPISS=1;		 //�ӻ�δѡ��
	/*SPI��,��ģʽ,�½���/���ز���,����CPU_CLK/4(11.0592MHz/4)*/
	SPCTL=SSIG|SPEN|MSTR|CPHA|SPSPEEDHH;
	IE2|=ESPI;		 //SPI�жϿ�
	SPI_ren=0;		 //���ý���
	SPI_send=1;		 //������
}

BOOL SPISendChar(uint8 DATA)
{
	if(SPI_send)
	{
		SPDAT=DATA;
		SPI_send=0;
		return TRUE;
	}
	return FALSE;
}

void isr_SPI(void) interrupt 9
{
	SPSTAT&=SPIF|WCOL;
	SPI_send=1;
	if(!SPI_ren)//дģʽ
	{
		return;
	}
	else		//��ģʽ
	{
		SPI_re=SPDAT;
	}
}