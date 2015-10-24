#include"common.h"
#include"RC522.h"

uint8 RC522Read(uint8 Address)
{
	uint8 ModelAndAddress;
	uint8 Re;
	ModelAndAddress=READ|(Address<<1);	//生成模式/地址数据
	RC522TransEnable();					//选中从机
	SPISendChar(ModelAndAddress);		//传输模式/地址数据
	while(!SPI_send); 					//等待发送
	SPIRenEnable();		  				//允许接收
	SPISendChar(0x00);					//读取地址中的信息(0x00不代表任何意义,用于换出数据)
	while(!SPI_send); 					//等待发送
	RC522TransDisable();				//取消从机选择
	SPIRenDisable();					//禁用接收
	Re=SPI_re;
	return Re;							//返回读取的数据
}

void RC522Write(uint8 Address,uint8 Data)
{
	uint8 ModelAndAddress;
	ModelAndAddress=WRITE|(Address<<1); //生成模式/地址数据
	RC522TransEnable();		 			//选中从机
	SPISendChar(ModelAndAddress);		//传输模式/地址数据
	while(!SPI_send);		 			//等待发送
	SPISendChar(Data);		 			//发送需要写入的数据
	while(!SPI_send);		 			//等待发送
	RC522TransDisable();	 			//取消从机选择
}

void RC522SetBit(uint8 Address,uint8 loc)
{
	uint8 temp;				  
	temp=RC522Read(Address);  //读取原有数据
	temp=SetBit(temp,loc);	  //处理数据
	RC522Write(Address,temp); //写入处理完成后的数据
}

void RC522ClearBit(uint8 Address,uint8 loc)
{
	uint8 temp;
	temp=RC522Read(Address);  //读取原有数据
	temp=ClearBit(temp,loc);  //处理数据
	RC522Write(Address,temp); //写入处理完成后的数据
}