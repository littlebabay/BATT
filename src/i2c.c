#include "../inc/i2c.h"
/**********************************************************************************
*
*					i2c��ʼ������
*
**********************************************************************************/
void i2c_init(void){
	
	I2C_SCL   = 1;
	I2C_SDA   = 1;
	I2C_ALERT = 1;

}

void Delay1us(unsigned char cnt)		//@16MHz
{
	unsigned char i;

	while(cnt--){
	   i = 3;
	   while (--i);
	}	
	
}
/************************************************************
*
*			I2C START �ź� 
*
/************************************************************/
void i2c_start(void){
	
	I2C_SDA = 1;
	Delay1us(1);
	I2C_SCL = 1;
	Delay1us(5);
	I2C_SDA = 0;
	Delay1us(5);
	I2C_SCL = 0;
	Delay1us(2);

}
/************************************************************
*
*			I2C STOP �ź� 
*
/************************************************************/
void i2c_stop(void){
	
	I2C_SDA = 0;
	Delay1us(1);
	I2C_SCL = 1;
	Delay1us(5);
	I2C_SDA = 1;
	Delay1us(4);
}
/************************************************************
*
*			I2C �ֽ�д 
*
/************************************************************/
void i2c_byte_write(unsigned char dat){

	unsigned char i =0;

	for( i = 0; i < 8; i++ ){
		
		if((dat<<i) & 0x80){
		  	I2C_SDA=1;
		}else{
			I2C_SDA=0;
		}
		Delay1us(1);
		I2C_SCL = 1;
		Delay1us(5);	
		I2C_SCL = 0;
	}


}
/************************************************************
*
*			I2C �ֽڶ� 
*
************************************************************/
unsigned char i2c_byte_read(void){
	 
	unsigned char i =0;
	unsigned char dat=0;

	//I2C_SCL = 0;
	//Delay1us(3);
	I2C_SDA  = 1;

	for( i = 0; i < 8; i++ ){
			
		Delay1us(1);
		I2C_SCL = 0;
		Delay1us(5);
		I2C_SCL = 1;
		Delay1us(3);
		if(I2C_SDA == 1 ){
			dat = (dat<<1) + 1;
		
		}else{
			dat = (dat<<1) + 0;
		}
		Delay1us(2);

	}

	I2C_SCL =0;
	Delay1us(2);

	return dat;

}
/*********************************************************************************************************
*
*			I2C��ȡack��Ӧ���ź�
*	  �����б�unsigned char ack_no   ��ʾǰ�漸�ε���ack�ķ��ؽ����0x03 ��ʾǰ���ε���ackû�еõ���Ӧ
*     �����б�unsigned char ack_no   ��־����ε���ackΪֹ��ÿһ��ack��Ӧ������
*
*********************************************************************************************************/
unsigned char i2c_ask_read(unsigned char ack_no){
		
	 
	Delay1us(2);
	I2C_SDA = 1;
	Delay1us(2);
	I2C_SCL = 1;
	Delay1us(3);
	if(I2C_SDA == 0){ 
		I2C_SCL = 0;
		Delay1us(2);
		return (ack_no<<1);//��ʾ�������յ�Ӧ��
	}else{
		I2C_SCL = 0;
		Delay1us(2);
		return (ack_no<<1)+1 ;//��ʾ�������յ�Ӧ��
	
	}
	
}
/********************************************************************************
*
*				 ����дӦ���ź�
*
*
********************************************************************************/
void i2c_ask_write(void){

	//Delay1us(1);
	I2C_SDA = 0;
	Delay1us(3);
	I2C_SCL = 1;
	Delay1us(5);
	I2C_SCL = 0;
	Delay1us(2);

}
/************************************************************
*
*			I2C д�Ĵ���
*       �����б�unsigned char i2c_addr 	������ַ
*				  unsigned char reg_addr 	�Ĵ�����ַ
*				  unsigned int  dat      	��д�������
*		���ز�����unsigned char ack_result  ackӦ���źű�־λ��
*											����0x00��ʾ�����ɹ�����0x00�Ĵӵ�λ����λ��
*											���δ����1��2��3��4��������ack�Ľ����
*											ÿһλ0��ʾ�ô���Ӧ��1��ʾ�ô�û��Ӧ�� 
*						
/************************************************************/
unsigned char i2c_write(unsigned char i2c_addr,unsigned char reg_addr,unsigned int dat){

	unsigned char ack_result=0;	

	i2c_addr<<=1; //����һλ��ĩβ���죬��ʾִ��д��

	i2c_start();  //START�ź�

	i2c_byte_write(i2c_addr); //дI2C��ַ
	ack_result = i2c_ask_read(ack_result);

	i2c_byte_write(reg_addr); //д�Ĵ�����ַ
	ack_result = i2c_ask_read(ack_result);

   	i2c_byte_write( (unsigned char)(dat>>8));//д���ݸ߰�λ
	ack_result = i2c_ask_read(ack_result);

	i2c_byte_write( (unsigned char)(dat&0x00ff));//д���ݵͰ�λ
	ack_result = i2c_ask_read(ack_result);

	i2c_stop();//ֹͣ

	return ack_result;

}

unsigned char i2c_change_reg_addr(unsigned char i2c_addr , unsigned char reg_addr){

	unsigned char ack_result=0;	

	i2c_addr<<=1; //����һλ��ĩβ���죬��ʾִ��д��

	i2c_start();  //START�ź�

	i2c_byte_write(i2c_addr); //дI2C��ַ
	ack_result = i2c_ask_read(ack_result);

	i2c_byte_write(reg_addr); //д�Ĵ�����ַ
	ack_result = i2c_ask_read(ack_result);

	i2c_stop();//ֹͣ

	return ack_result;

}
/************************************************************
*
*			I2C ���Ĵ���
*
/************************************************************/
unsigned char i2c_read(unsigned char i2c_addr,unsigned char reg_addr,unsigned int *dat){

	unsigned char ack_result=0;
	*dat = 0;	

	EA=0;

	//i2c_change_reg_addr(i2c_addr,reg_addr);//�޸ļĴ���ָ��
	//i2c_change_reg_addr(i2c_addr,reg_addr);//�޸ļĴ���ָ��
	//i2c_change_reg_addr(i2c_addr,reg_addr);//�޸ļĴ���ָ��
	//i2c_change_reg_addr(i2c_addr,reg_addr);//�޸ļĴ���ָ��
	//i2c_change_reg_addr(i2c_addr,reg_addr);//�޸ļĴ���ָ��
	i2c_change_reg_addr(i2c_addr,reg_addr);//�޸ļĴ���ָ��

	i2c_addr = (i2c_addr<<1) +1;//����һλ��ĩβ��һ����ʾ������

	i2c_start();  //START�ź�

	i2c_byte_write(i2c_addr); //дI2C��ַ
	ack_result = i2c_ask_read(ack_result);

   	*dat = (unsigned int)(i2c_byte_read());//�����ݸ߰�λ
	i2c_ask_write();

	*dat <<= 8;
	*dat |= (unsigned int)(i2c_byte_read());//�����ݵͰ�λ
	i2c_ask_write();
	
	i2c_stop();//ֹͣ

	EA=1;
	return ack_result;

}
