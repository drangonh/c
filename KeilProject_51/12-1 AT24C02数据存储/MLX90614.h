#ifndef __MLX90614_H__
#define __MLX90614_H__

void start_bit();                 //MLX90614 ����ʼλ�ӳ��� 
void stop_bit();                //MLX90614������λ�ӳ��� 
//uchar  rx_byte(void);              //MLX90614 �����ֽ��ӳ��� 
void send_bit(void);             //MLX90614����λ�ӳ��� 
//void tx_byte(uchar dat_byte);    //MLX90614 �����ֽ��ӳ��� 
void receive_bit(void);           //MLX90614����λ�ӳ��� 
//void delay(uint N);              //��ʱ���� 
//uint memread(void);             // ���¶����� 
//uint memread(void); 
	
#endif
