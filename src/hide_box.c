#include "../inc/hide_box.h"
#include "../inc/ina226.h"
#include "../inc/relay.h"

unsigned char hide_box_enter = 0; //1������hide_boxģʽ��0��������ģʽ����
unsigned char cmd_update = 0; //��־λ�� 1.���յ������� 0.��ʾû�н��յ�������
/*************************************************************************************
*
* 			�ַ����ȽϺ�������������ַ�����ȫ��ͬ������TRUE����֮������FALSE
*
**************************************************************************************/
unsigned char hide_box_compare_str(unsigned char *s1,unsigned char *s2){

	while( (*s1 != '\0') && (*s2 !='\0') ){
		
		if( (*s1++) != (*s2++) )
			return FALSE;			

	}

	if( ( *s1 == '\0') && ( *s2 == '\0') )
		return TRUE;
	else 
		return FALSE;

}

/***************************************************************************************
*
*						�ںв���
*
****************************************************************************************/
void hide_box(){
	
	
	uart_printf("Entering hide box mode\n\r#");

	ET0=0; //�ص�LEDˢ��
	
	while(hide_box_enter == TRUE){
		
		if(cmd_update == TRUE ){ //����½��յ������������Աȣ�������ִ����������
		
			/****************************���п�ִ�еĲ�������*************************/
			
			if( (hide_box_compare_str( receive_buf ,"beep")) == TRUE) beep(2);

			if( (hide_box_compare_str( receive_buf ,"relay_test")) == TRUE) relay_test_all();

			if( (hide_box_compare_str( receive_buf ,"relay_out")) == TRUE) relay_out();
			
			if( (hide_box_compare_str( receive_buf ,"print_ina226_charge")) == TRUE){ 
				
				ina226_print_all_reg(I2C_ADDR_CHARGE);
			}

			if( (hide_box_compare_str( receive_buf ,"print_ina226_discharge")) == TRUE){ 
				
		
				ina226_print_all_reg(I2C_ADDR_DISCHARGE);
			}
			
			if( (hide_box_compare_str( receive_buf ,"print_ina226_batt_1")) == TRUE){ 
				
			
				ina226_print_all_reg(I2C_ADDR_BATT_1);
			}
			if( (hide_box_compare_str( receive_buf ,"print_ina226_batt_2")) == TRUE){ 
				
			
				ina226_print_all_reg(I2C_ADDR_BATT_2);
			}
			if( (hide_box_compare_str( receive_buf ,"print_ina226_batt_3")) == TRUE){ 
				
				
				ina226_print_all_reg(I2C_ADDR_BATT_3);
			}
			if( (hide_box_compare_str( receive_buf ,"print_ina226_batt_4")) == TRUE){ 
				
			
				ina226_print_all_reg(I2C_ADDR_BATT_4);
			}
			if( (hide_box_compare_str( receive_buf ,"print_ina226")) == TRUE){ 
				

				ina226_print_all_reg(I2C_ADDR_CHARGE);
		
				ina226_print_all_reg(I2C_ADDR_DISCHARGE);
			
				ina226_print_all_reg(I2C_ADDR_BATT_1);
		
				ina226_print_all_reg(I2C_ADDR_BATT_2);
			
				ina226_print_all_reg(I2C_ADDR_BATT_3);

				ina226_print_all_reg(I2C_ADDR_BATT_4);
			}
			
				
			cmd_update = FALSE;//���������ɺ������־λ��Ϊ��һ�����������׼��
		}
		
	}
	ET0=1;
	uart_printf("Exit form hide box mode\n\r#");
}

