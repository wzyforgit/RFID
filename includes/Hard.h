#ifndef	HARD_H
#define HARD_H

/*UART*/
extern BOOL UARTSendChar(uint8 DATA);
extern void InitUART2(void);

extern volatile BOOL UART2_send;   //����2����������
extern volatile uint8 PC_cmd;	   //�յ�����λ��ָ��

/*SPI*/
extern BOOL SPISendChar(uint8 DATA);
extern void InitSPI(void);

extern volatile BOOL SPI_send;	   //SPI����������
extern volatile BOOL SPI_ren;	   //SPI����������
extern volatile uint8 SPI_re;	   //SPI�յ�������

#define RC522TransEnable()  SPISS=0
#define RC522TransDisable() SPISS=1
#define SPIRenEnable()		SPI_ren=1
#define SPIRenDisable()		SPI_ren=0

#endif