#include"init.h"
#include"common.h"
#include"app.h"

volatile uint8 PC_cmd;	 //上位机指令

void delay(uint16 ms)
{
	volatile x,y;
	for(x=ms;x>0;x--)
		for(y=880;y>0;y--);
}

void Menu(void)
{
	UartPrintf("初始化完成,请选择操作指令\n");
	UartPrintf("A:串口通信测试\n");
	UartPrintf("B:读取模块版本信息\n");
	UartPrintf("C:RC522读写测试\n");
}

void WriteTest(void)
{
	uint8 Message;
	Message=RC522Read(Status2Reg);
	UartPrintf("s:%x\n",0xff00|Message);

/*	RC522Write(Status2Reg,0x80);
	Message=RC522Read(Status2Reg);
	UartPrintf("n:%x\n",0xff00|Message);*/	
}

void start(void) _task_	0
{
	Init();
	os_create_task(1);
	os_create_task(2);

	os_delete_task(0);
}

void SendMessage(void) _task_ 1
{
	uint8 Message;
	for(;;)
	{
		if(kfifo_len(&Fifo)&&UART2_send)
		{
			kfifo_get(&Fifo,&Message,1);
			UARTSendChar(Message);
		}
	}
}

void DealCmd(void) _task_ 2
{
	uint8 Message;
	uint16 mask=0xff00;
	Menu();
	for(;;)
	{
		if(PC_cmd)
		{
			PC_cmd=toupper(PC_cmd);
			switch(PC_cmd)
			{
				default: UartPrintf("指令错误!\n");
				CASE 'A':UartPrintf("Testing\n");
				CASE 'B':Message=RC522Read(VersionReg);
				 		 UartPrintf("模块版本为:%x\n",mask|VersionReg);
				CASE 'C':WriteTest();
			}
			PC_cmd=0;
		}
	}
}
/*
int main(void)
{
	uint8 Message;
	Init();
	Menu();
	for(;;)
	{
		if(kfifo_len(&Fifo)&&UART2_send)
		{
			kfifo_get(&Fifo,&Message,1);
			UARTSendChar(Message);
		}
		if(PC_cmd)
		{
			PC_cmd=toupper(PC_cmd);
			switch(PC_cmd)
			{
				default: UartPrintf("指令错误!\n");
				CASE 'A':UartPrintf("Testing\n");
				CASE 'B':Message=RC522Read(VersionReg);
				 		 UartPrintf("模块版本为:%c\n",VersionReg);
			}
			PC_cmd=0;
		}
	}
	return 0;
}
*/