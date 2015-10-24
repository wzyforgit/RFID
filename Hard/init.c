#include"common.h"
#include"init.h"

struct kfifo Fifo;

void Init(void)
{
	InitFifo();			//��ʼ��������
	InitUART2();		//��ʼ������2,115200-N-8-1
	InitSPI();			//��ʼ��SPI
	EA=1;				//���жϿ�
	kfifo_reset(&Fifo);	//���û�����
	PC_cmd=0;			//������λ������
	RC522RST=0;			//RC522��λ
	delay(1000);
	RC522RST=1;			//RC522��λ��
}

void InitFifo(void)
{
	static uint8 xdata FifoBuf[BUFSIZE];
	Fifo.buffer = FifoBuf;
	Fifo.size = BUFSIZE;
	Fifo.in = Fifo.out = 0;
}