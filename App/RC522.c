#include"common.h"
#include"RC522.h"

uint8 RC522Read(uint8 Address)
{
	uint8 ModelAndAddress;
	uint8 Re;
	ModelAndAddress=READ|(Address<<1);	//����ģʽ/��ַ����
	RC522TransEnable();					//ѡ�дӻ�
	SPISendChar(ModelAndAddress);		//����ģʽ/��ַ����
	while(!SPI_send); 					//�ȴ�����
	SPIRenEnable();		  				//�������
	SPISendChar(0x00);					//��ȡ��ַ�е���Ϣ(0x00�������κ�����,���ڻ�������)
	while(!SPI_send); 					//�ȴ�����
	RC522TransDisable();				//ȡ���ӻ�ѡ��
	SPIRenDisable();					//���ý���
	Re=SPI_re;
	return Re;							//���ض�ȡ������
}

void RC522Write(uint8 Address,uint8 Data)
{
	uint8 ModelAndAddress;
	ModelAndAddress=WRITE|(Address<<1); //����ģʽ/��ַ����
	RC522TransEnable();		 			//ѡ�дӻ�
	SPISendChar(ModelAndAddress);		//����ģʽ/��ַ����
	while(!SPI_send);		 			//�ȴ�����
	SPISendChar(Data);		 			//������Ҫд�������
	while(!SPI_send);		 			//�ȴ�����
	RC522TransDisable();	 			//ȡ���ӻ�ѡ��
}

void RC522SetBit(uint8 Address,uint8 loc)
{
	uint8 temp;				  
	temp=RC522Read(Address);  //��ȡԭ������
	temp=SetBit(temp,loc);	  //��������
	RC522Write(Address,temp); //д�봦����ɺ������
}

void RC522ClearBit(uint8 Address,uint8 loc)
{
	uint8 temp;
	temp=RC522Read(Address);  //��ȡԭ������
	temp=ClearBit(temp,loc);  //��������
	RC522Write(Address,temp); //д�봦����ɺ������
}