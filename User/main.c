#include "math.h"
#include"reg52.h"
#include "public.h"
#include "key.h"
#include "beep.h"
#include "lcd1602.h"
#include "time.h"
#include "time1.h"
#define GPIO_KEY P1
unsigned int KeyValue;

void KeyDown(void)
{ char i =0;
GPIO_KEY=0x0f; 
 if(GPIO_KEY!=0x0f)
   { 
      if(GPIO_KEY!=0x0f)
        { GPIO_KEY=0X0F;
           switch(GPIO_KEY) 
             { case(0X07): KeyValue=1;break;
               case(0X0b): KeyValue=2;break; 
               case(0X0d): KeyValue=3;break; 
               case(0X0e): KeyValue=4;break; }
     GPIO_KEY=0XF0;
	 switch(GPIO_KEY) 
	  { case(0X70): KeyValue=KeyValue;break; 
     	case(0Xb0): KeyValue=KeyValue+4;break; 
	    case(0Xd0): KeyValue=KeyValue+8;break;
	    case(0Xe0): KeyValue=KeyValue+12;break; }
 	  } 
   }

 }
void main()
{
	
	u8 key=0;
	u8 time_buf[9];
	u8 time1_buf[9];
	u8 time_flag=0;
	u8 time1_flag=0;
	u8 naozhong =0;
		u8   gdmin=10;
		u8	gdshi=10;
	u8  gdsec=10;
	u8 gdmsec=10;
u8 naozhongset=0;
	lcd1602_init();
	time0_init();
	time1_init();
	while(1)
	{
		key=key_scan(0);
		KeyDown();
		 switch(KeyValue)
						{
									case 1:gshi++;if(gshi>=24)gshi=0;KeyValue=0;delay_ms(100); break;
									case 2:if(gshi==0)gshi=24;gshi--;KeyValue=0;delay_ms(100); break;
									case 3:gmin++;if(gmin>=60)gmin=0;KeyValue=0;delay_ms(100); break;
									case 4:if(gmin==0)gmin=60;gmin--;KeyValue=0;delay_ms(100); break;
									case 5:gshi1++;if(gshi1>=24)gshi1=0;KeyValue=0;delay_ms(100); break;
									case 6:if(gshi1==0)gshi1=24;gshi1--;KeyValue=0;delay_ms(100); break;
									case 7:gmin1++;if(gmin1>=60)gmin1=0;KeyValue=0;delay_ms(100); break;
									case 8:if(gmin1==0)gmin1=60;gmin1--;KeyValue=0;delay_ms(100); break;
									default:break;
									}
		if(key==1)//开始和停止计时
		{
			time_flag=!time_flag;
			beep_alarm(1000,10);//短暂提示音 
		}	
		else if(key==KEY2_PRESS)//清除计时
		{
			time0_stop();
			time_flag=0;
			gmin=0;
			gsec=0;
			gmsec=0;
			gshi=0;
			naozhong =0;
			beep_alarm(1000,10);//短暂提示音		
		}
   else if(key==KEY3_PRESS)
		{ 	gdshi+=abs(gshi-gshi1)-10; 
			gdmin+=abs(gmin-gmin1)-10;
		
			gdsec+=abs(gsec-gsec1)-10;
			
			if(gdsec!=0)
			{gdmin-=1;
				gdsec=60-gdsec;}
				if(gdmin!=0)
			{
				gdshi-=1;
				gdmin=60-gdmin+gmin1;}
			
			gmin1=0;
			gsec1=0;
			gmsec1=0;
			gshi1=0;
			beep_alarm(1000,10);
			lcd1602_show_string(5,1,"alarm");
		   	time1_flag=!time1_flag;
			naozhong=!naozhong;
			  
			if(naozhong)
			{lcd1602_show_string(0,1,"on!");}
			else
			{lcd1602_show_string(0,1,"off");}
			}
		 if(key==KEY4_PRESS)
		 {naozhongset=!naozhongset;}
			
			if(naozhongset)
		 {lcd1602_show_string(5,1,"alarm");
			 time1_buf[0]=gshi1/10+0x30;
		time1_buf[1]=gshi1%10+0x30;//分
		time1_buf[2]=':';//
		time1_buf[3]=gmin1/10+0x30;
		time1_buf[4]=gmin1%10+0x30;//秒
		time1_buf[5]=':';//
		time1_buf[6]=gsec1/10+0x30;
		time1_buf[7]=gsec1%10+0x30;//毫秒
		time1_buf[8]='\0';
		lcd1602_show_string(0,0,time1_buf);//显蕔
		 }
		 else{
			 lcd1602_show_string(5,1,"clock");
			 time_buf[0]=gshi/10+0x30;
		time_buf[1]=gshi%10+0x30;//分
		time_buf[2]=':';//-
		time_buf[3]=gmin/10+0x30;
		time_buf[4]=gmin%10+0x30;//秒
		time_buf[5]=':';//-
		time_buf[6]=gsec/10+0x30;
		time_buf[7]=gsec%10+0x30;//毫秒
		time_buf[8]='\0';
		lcd1602_show_string(0,0,time_buf);}
			
		
		
		if(gshi1==gdshi&&gdmin==gmin1&&gdsec==gsec1)
			{if(naozhong) 
				{beep_alarm(100000,10);
				   lcd1602_show_string(0,1,"off");

				  time0_stop();
				  naozhong=0;
					 time1_flag=!time1_flag;
				  gmin1=0;
				  gsec1=0; } 
				}
			
		if(time_flag)  
			{time0_start();//开始计时
			   }
		else
			{time0_stop();
	}//停止计时	
		if(time1_flag)  
			{time1_start();//开始计时
			   }
		else
		{time1_stop();//停止计时	
}
}
}
