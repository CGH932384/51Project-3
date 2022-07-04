#ifndef _time1_H
#define _time1_H

#include "public.h"


//变量声明
extern u8 gmsec1;//ms级定义
extern u8 gsec1;//秒定义
extern u8 gmin1;//分定义
extern u8 gshi1;//时定义

//函数声明
void time1_init(void);
void time1_start(void);
void time1_stop(void);
#endif
