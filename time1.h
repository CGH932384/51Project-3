#ifndef _time1_H
#define _time1_H

#include "public.h"


//��������
extern u8 gmsec1;//ms������
extern u8 gsec1;//�붨��
extern u8 gmin1;//�ֶ���
extern u8 gshi1;//ʱ����

//��������
void time1_init(void);
void time1_start(void);
void time1_stop(void);
#endif
