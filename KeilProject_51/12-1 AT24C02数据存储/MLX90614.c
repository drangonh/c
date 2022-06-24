#include "at89x52.h" 
#include "intrins.h" 

#define  uint  unsigned int 
#define  uchar unsigned char 
#define  Nack_counter  10 

//mlx90614 端口定义 
sbit  SCL=P1^6; // 时钟线 
sbit  SDA=P1^7; // 数据线

//************ 数据定义**************** 
bdata uchar flag;	//可位寻址数据 
sbit bit_out=flag^7;
sbit bit_in=flag^0;
uchar DataH,DataL,Pecreg;


//************************************ 
void   start_bit(void) 
{ 
   SDA=1; 
   _nop_();_nop_();_nop_();_nop_();_nop_(); 
   SCL=1; 
   _nop_();_nop_();_nop_();_nop_();_nop_(); 
   SDA=0; 
   _nop_();_nop_();_nop_();_nop_();_nop_(); 
   SCL=0; 
   _nop_();_nop_();_nop_();_nop_();_nop_(); 
 
} 



//------------------------------ 
void   stop_bit(void) 
{ 

   SCL=0; 
   _nop_();_nop_();_nop_();_nop_();_nop_(); 
   SDA=0; 
   _nop_();_nop_();_nop_();_nop_();_nop_(); 
   SCL=1; 
   _nop_();_nop_();_nop_();_nop_();_nop_(); 
   SDA=1; 
} 


//-----------发送一个位--------- 
void  send_bit(void) 
{ 
  if(bit_out==0) 
  
       SDA=0; 
  else 
     SDA=1; 
  _nop_(); 
  SCL=1; 
  _nop_();_nop_();_nop_();_nop_(); 
  _nop_();_nop_();_nop_();_nop_(); 
  SCL=0; 
  _nop_();_nop_();_nop_();_nop_(); 
  _nop_();_nop_();_nop_();_nop_(); 
} 



//---------- 接收一个位---------- 
void receive_bit(void) 
{ 
  SDA=1;bit_in=1; 
  SCL=1; 
  
	_nop_();_nop_();_nop_();_nop_(); 
	_nop_();_nop_();_nop_();_nop_(); 
  
	bit_in=SDA; 
	_nop_(); 
	SCL=0; 
  _nop_();_nop_();_nop_();_nop_(); 
  _nop_();_nop_();_nop_();_nop_(); 
}


/*
//------------ 延时-------------- 
void delay(uint N) 
{ 
  uint i; 
	
  for(i=0;i<N;i++) 
     _nop_(); 
}
*/


//--------- 发送一个字节--------- 
void  tx_byte(uchar dat_byte) 
{ 
   char i,n,dat; 
   n=Nack_counter; 
TX_again: 
   dat=dat_byte; 
   for(i=0;i<8;i++) 
   { 
     if(dat&0x80) 
      bit_out=1; 
     else 
      bit_out=0; 
     send_bit(); 
     dat=dat<<1; 
   } 
   
      receive_bit(); 
   if(bit_in==1) 
   { 
    stop_bit(); 
    if(n!=0) 
    {n--;goto Repeat;} 
    else 
     goto exit; 
   } 
   else 
    goto exit; 
Repeat: 
    start_bit(); 
    goto TX_again; 
exit: ; 
} 


//---------- 接收一个字节-------- 
uchar rx_byte(void) 
{ 
  uchar i,dat; 
  dat=0; 
  for(i=0;i<8;i++) 
  { 
    dat=dat<<1; 
    receive_bit(); 
    if(bit_in==1) 
     dat=dat+1; 
  } 
  send_bit(); 
  return dat; 
} 

uint memread(void) 
{ 
  start_bit(); 
  tx_byte(0xB4);  //Send SlaveAddress ==============================
  //tx_byte(0x00); 
  tx_byte(0x07);  //Send Command 
  //------------ 
  start_bit(); 
  tx_byte(0x01); 
  bit_out=0; 
  DataL=rx_byte(); 
  bit_out=0; 
  DataH=rx_byte(); 
  bit_out=1; 
  Pecreg=rx_byte(); 
  stop_bit(); 
  return(DataH*256+DataL); 
} 
