#ifndef __RED_H
#define __RED_H 
#include "sys.h"   
//////////////////////////////////////////////////////////////////////////////////	 
//本程序只供学习使用，未经作者许可，不得用于其它任何用途
//ALIENTEK STM32F407开发板
//红外遥控解码驱动 代码	   
//正点原子@ALIENTEK
//技术论坛:www.openedv.com
//创建日期:2014/5/7
//版本：V1.0
//版权所有，盗版必究。
//Copyright(C) 广州市星翼电子科技有限公司 2014-2024
//All rights reserved								  
//////////////////////////////////////////////////////////////////////////////////
  
#define RDATA PAin(8)	 //红外数据输入脚

//红外遥控识别码(ID),每款遥控器的该值基本都不一样,但也有一样的.
//我们选用的遥控器识别码为0
#define REMOTE_ID 0

#define KEY_UP 98
#define KEY_DOWN 168
#define KEY_LEFT 34
#define KEY_RIGHT 194
#define KEY_POWER 162
#define KEY_PLAY 2
#define KEY_1 104
#define KEY_2 152
#define KEY_3 176
#define KEY_4 48
#define KEY_5 24
#define KEY_6 122
#define KEY_7 16
#define KEY_8 56
#define KEY_9 90
#define KEY_0 66
#define KEY_VOL_A 144
#define KEY_VOL_D 224

extern u8 RmtCnt;	//按键按下的次数
extern u8 RmtSta;
extern u16 Dval;    //下降沿时计数器的值
extern u32 RmtRec;  //红外接收到的数据

extern u8 changdi;  //场地
extern u8 chengxu;	 //回合程序

u8 Remote_Scan(void);
u8 Remote_Control(void);

#endif
