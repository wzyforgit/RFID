#include"common.h"
#include<stdarg.h>

void UartPuts(uint8 *s)
{
	kfifo_put(&Fifo,s,strlen(s));
}

void UartPrintf(uint8 *s,...)
{
    static uint8 xdata buf[64];
    va_list ag;
    va_start(ag,s);
    vsprintf(buf,s,ag);
    va_end(ag);
    UartPuts(buf);
}