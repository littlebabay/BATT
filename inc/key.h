#ifndef __KEY_H
#define __KEY_H
#include "STC/STC12C5A.h"

#define  POWER_HOLD_ENABLE  P1M1&=~(0x01<<6);P1M0|=(0x01<<6);P1M1|=(0x01<<7);P1M0&=~(0x01<<7);P16=1  //��������
#define  POWER_HOLD_DISABLE P16=0 //�ػ�
#define  POWER_KEY 		    P17 //��Դ���� 1.��������  0.��Դ��û�а���

#define  KEY_NONE		 0x00	
#define  KEY_OUT_EN		 0X01
#define  KEY_OUT_48V	 0X02
#define  KEY_OUT_96V	 0X04
#define  KEY_OUT_144V	 0X08
#define  KEY_OUT_192V	 0X10

extern unsigned char key_scan(void);

#endif							    