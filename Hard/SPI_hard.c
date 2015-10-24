#include"common.h"

volatile BOOL SPI_send;//SPI发送允许标记
volatile BOOL SPI_ren; //SPI接收允许标记
volatile uint8 SPI_re; //SPI收到的数据

void InitSPI(void)
{
	SPSTAT=SPIF|WCOL;//清除SPI状态
	SPISS=1;		 //从机未选中
	/*SPI开,主模式,下降沿/后沿采样,速率CPU_CLK/4(11.0592MHz/4)*/
	SPCTL=SSIG|SPEN|MSTR|CPHA|SPSPEEDHH;
	IE2|=ESPI;		 //SPI中断开
	SPI_ren=0;		 //禁用接收
	SPI_send=1;		 //允许发送
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
	if(!SPI_ren)//写模式
	{
		return;
	}
	else		//读模式
	{
		SPI_re=SPDAT;
	}
}