#include"common.h"
#include"init.h"

struct kfifo Fifo;

void Init(void)
{
	InitFifo();			//初始化缓冲区
	InitUART2();		//初始化串口2,115200-N-8-1
	InitSPI();			//初始化SPI
	EA=1;				//总中断开
	kfifo_reset(&Fifo);	//重置缓冲区
	PC_cmd=0;			//重置上位机命令
	RC522RST=0;			//RC522复位
	delay(1000);
	RC522RST=1;			//RC522复位关
}

void InitFifo(void)
{
	static uint8 xdata FifoBuf[BUFSIZE];
	Fifo.buffer = FifoBuf;
	Fifo.size = BUFSIZE;
	Fifo.in = Fifo.out = 0;
}