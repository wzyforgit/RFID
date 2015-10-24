#ifndef APP_H
#define APP_H

/*UART*/
extern void UartPuts(uint8 *s);
extern void UartPrintf(uint8 *s,...);

extern volatile uint8 PC_cmd;	   //收到的上位机指令

/*RC522*/
extern uint8 RC522Read(uint8 Address);
extern void RC522Write(uint8 Address,uint8 DATA);
extern void RC522SetBit(uint8 Address,uint8 loc);
extern void RC522ClearBit(uint8 Address,uint8 loc);

#endif