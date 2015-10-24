#ifndef COMMON_H
#define COMMON_H

#include<stc12c5a.h>
#include<string.h>
#include<stdio.h>
#include<ctype.h>
#include<rtx51tny.h>

#include"DataType.h"
#include"kfifo.h"
#include"RC522.h"
#include"Hard.h"

extern struct kfifo Fifo;
sbit RC522RST=P1^1;
extern void delay(uint16 ms);

#define STRCMP(a,R,b) (strcmp(a,b) R 0)
#define CASE break;case
#define ClearBit(num,loc) 	 ((num)&(~(1<<(loc))))
#define SetBit(num,loc)		 ((num)|(1<<(loc)))
#define ExchangeBit(num,loc) ((num)^(1<<(loc)))

#endif