#ifndef	HARD_H
#define HARD_H

/*UART*/
extern BOOL UARTSendChar(uint8 DATA);
extern void InitUART2(void);

extern volatile BOOL UART2_send;   //串口2发送允许标记
extern volatile uint8 PC_cmd;	   //收到的上位机指令

/*SPI*/
extern BOOL SPISendChar(uint8 DATA);
extern void InitSPI(void);

extern volatile BOOL SPI_send;	   //SPI发送允许标记
extern volatile BOOL SPI_ren;	   //SPI接收允许标记
extern volatile uint8 SPI_re;	   //SPI收到的数据

#define RC522TransEnable()  SPISS=0
#define RC522TransDisable() SPISS=1
#define SPIRenEnable()		SPI_ren=1
#define SPIRenDisable()		SPI_ren=0

#endif