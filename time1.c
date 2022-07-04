#include "time1.h"

//变量定义
u8 gmsec1=0;//ms级定义
u8 gsec1=0;//秒定义
u8 gmin1=0;//分定义
u8 gshi1=0;

/*******************************************************************************
* 函 数 名       : time0_init
* 函数功能		 : 定时器0中断配置函数，通过设置TH和TL即可确定定时时间
* 输    入       : 无
* 输    出    	 : 无
*******************************************************************************/
void time1_init(void)
{
	TMOD|=0X10;//选择为定时器0模式，工作方式1
	TH1=0XDC;	//给定时器赋初值，定时10ms
	TL1=0X00;	
	ET1=1;//打开定时器1中断允许
	EA=1;//打开总中断
	TR1=0;//关闭定时器		
}

/*******************************************************************************
* 函 数 名       : time0_start
* 函数功能		 : 定时器0打开
* 输    入       : 无
* 输    出    	 : 无
*******************************************************************************/
void time1_start(void)
{
	TR1=1;//打开定时器	
}

/*******************************************************************************
* 函 数 名       : time0_stop
* 函数功能		 : 定时器0关闭
* 输    入       : 无
* 输    出    	 : 无
*******************************************************************************/
void time1_stop(void)
{
	TR1=0;//关闭定时器
	TH1=0X00;
	TL1=0X00;	
}

void time1() interrupt 3 //定时器0中断函数
{
	TH1=0XDC;	//给定时器赋初值，定时10ms
	TL1=0X00;
	gmsec1++;//10ms加1次
	if(gmsec1==100)//定时1秒
	{
		gmsec1=0;
		gsec1++;//对秒计数
		if(gsec1==60)//到达60秒，即1分钟
		{
			gsec1=0;
			gmin1++;//对分计数
			if(gmin1==60)
			  {gmin1=0;
			   gshi1++;
			   if(gshi1==24) gshi1 =0;		 }
		}	
	}					
}