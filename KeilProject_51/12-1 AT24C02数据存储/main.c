#include <REGX52.H>
#include "LCD1602.h"
#include "Key.h"
#include "AT24C02.h"
#include "Delay.h"
#include "MLX90614.h"
#include "intrins.h"

#define  uint  unsigned int 
#define  uchar unsigned char 
#define  Nack_counter  10 

unsigned char KeyNum;
unsigned int Num;
unsigned int Tem; 
unsigned int T,a,b; 

sbit  SCL=P1^6; // 时钟线 
sbit  SDA=P1^7; // 数据线

void main()
{
	LCD_Init();
	LCD_ShowNum(1,1,5555,4);
	
	
	
	//函数部分 
	SCL=1;SDA=1;_nop_(); 
	_nop_();_nop_();_nop_(); 
	SCL=0; 
	Delay(30); 
	SCL=1; 
	
	while(1) 
	{ 
		Tem=memread(); 
		
		T=Tem*2;
		if(T>27315){
			T=T-27315; 
			a=T/100; 
			b=T-a*100; 
		}
		else{
			T=27315-T; 
			a=T/100; 
			b=T-a*100; 
		}
		
		 //printf("ASCII 值 = %d\n", Tem );
		LCD_ShowNum(2,1,a,4);
		LCD_ShowString(2,5,".");
		LCD_ShowNum(2,6,b,2);
		//display(Tem); 
		//delay(20); 
	} 
	
	/*
	while(1)
	{
		KeyNum=Key();
		if(KeyNum==1)	//K1按键，Num自增
		{
			Num++;
			LCD_ShowNum(1,1,Num,5);
		}
		if(KeyNum==2)	//K2按键，Num自减
		{
			Num--;
			LCD_ShowNum(1,1,Num,5);
		}
		if(KeyNum==3)	//K3按键，向AT24C02写入数据
		{
			AT24C02_WriteByte(0,Num%256);
			Delay(5);
			AT24C02_WriteByte(1,Num/256);
			Delay(5);
			LCD_ShowString(2,1,"Write OK");
			Delay(1000);
			LCD_ShowString(2,1,"        ");
		}
		if(KeyNum==4)	//K4按键，从AT24C02读取数据
		{
			Num=AT24C02_ReadByte(0);
			Num|=AT24C02_ReadByte(1)<<8;
			LCD_ShowNum(1,1,Num,5);
			LCD_ShowString(2,1,"Read OK ");
			Delay(1000);
			LCD_ShowString(2,1,"        ");
		}
	}
	*/
}
