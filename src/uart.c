#include "../inc/uart.h"
#include "../inc/beep.h"
#include "stdio.h"
#include "stdarg.h"
#define uchar unsigned char
#define uint unsigned int

unsigned char receive_buf[20];
unsigned char i=0;
unsigned char buf=0;


/***********************************************
���пڳ�ʼ��������9600����ʱ��1��������ʽ2  *************************************************/
void serial_init(void)
{ 
PCON &= 0x7F;		//�����ʲ�����
	SCON = 0x50;		//8λ����,�ɱ䲨����
	AUXR |= 0x40;		//��ʱ��1ʱ��ΪFosc,��1T
	AUXR &= 0xFE;		//����1ѡ��ʱ��1Ϊ�����ʷ�����
	TMOD &= 0x0F;		//�����ʱ��1ģʽλ
	TMOD |= 0x20;		//�趨��ʱ��1Ϊ8λ�Զ���װ��ʽ
	TL1 = 0xCC;		//�趨��ʱ��ֵ
	TH1 = 0xCC;		//�趨��ʱ����װֵ
	ET1 = 0;		//��ֹ��ʱ��1�ж�
	ES = 1; //�򿪴����ж�
	EA=1;
	TR1 = 1;		//������ʱ��1
}
/********************* **************************	   
���пڴ�������	
        ������ʾ������ַ��������	
*************************************************/	  

void send_byte(unsigned char byte){
		ES=0;
		SBUF =byte;
		while(!TI);
		TI=0;
		ES =1;	
}

void uart_printf(unsigned char *s){
	
	while(*s){

		send_byte(*s++);
	}
}

char putchar(char c){

	send_byte( (unsigned char) c);	
	return (c);

}

/***********************************************
�����жϷ�����	
��Ƭ���������ݣ�����table����	
*************************************************/
void serial() interrupt 4
{

 ES=0;	//�ش����ж�
 buf = SBUF;

 if( buf == 0x0d ){	//�ж��Ƿ���յ��س���

 	 receive_buf[i] = '\0';//����յ��س������ڽ��յ����ַ���ĩβ�ӽ�����'\0';
	 i = 0;//���ջ������
	 //uart_printf(receive_buf);
	 //uart_printf("\n");
	 //send_byte(0x0d); //���з�
	 send_byte(0x0d); //���з�
	 send_byte(0x0a);
	 send_byte('#');
	 //send_byte(hide_box_compare_str(receive_buf,"hide_box"));
	 cmd_update = 1;//��־λ����ʾ���յ�������

	 if( (hide_box_compare_str(receive_buf,"hide_box")) == TRUE ){	//�жϽ��յ��������Ƿ���hide_box

		  hide_box_enter = TRUE; //�������hide_boxģʽ

	 }else if( (hide_box_compare_str( receive_buf,"hide_box_exit")) == TRUE ){	//�жϽ��յ��������Ƿ���hide_box_exit

		  hide_box_enter = FALSE;//�˳�hide_boxģʽ
	 }

 }else if(buf != 0x0a){

 	 receive_buf[i++] = buf;//�����յ������ݴ浽���ջ���
	 send_byte(buf); //���з�
 }

 //uart_printf("\r\nRecive is OK!\r\n");
 
 //beep(1);
 RI=0; //�����������ж�
 ES=1;//�������ж�

 }