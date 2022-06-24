#ifndef __MLX90614_H__
#define __MLX90614_H__

void start_bit();                 //MLX90614 发起始位子程序 
void stop_bit();                //MLX90614发结束位子程序 
//uchar  rx_byte(void);              //MLX90614 接收字节子程序 
void send_bit(void);             //MLX90614发送位子程序 
//void tx_byte(uchar dat_byte);    //MLX90614 接收字节子程序 
void receive_bit(void);           //MLX90614接收位子程序 
//void delay(uint N);              //延时程序 
//uint memread(void);             // 读温度数据 
//uint memread(void); 
	
#endif
