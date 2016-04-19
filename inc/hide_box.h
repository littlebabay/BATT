#ifndef __HIDE_BOX_H
#define __HIDE_BOX_H
#include "STC/STC12C5A.h"
#include "../inc/main.h"
#include "../inc/uart.h"
#include "../inc/beep.h"
#include "../inc/relay.h"

extern unsigned char hide_box_enter; //1������hide_boxģʽ��0��������ģʽ����
extern unsigned char cmd_update;//��־λ�� 1.���յ������� 0.��ʾû�н��յ�������
extern void hide_box(void);//hide_box����
extern unsigned char hide_box_compare_str(unsigned char *s1,unsigned char *s2);	//�ַ����ԱȺ���

#endif