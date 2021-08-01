#ifndef __FINDBALL_H__
#define __FINDBALL_H__

#include "control.h"


void FindVolleyball_Yellow(void);
void FindVolleyball_Red(void);
void FindBasketball_Blue(void);
void FindVolleyball_Orange(void);
void FindVolleyball_Double(void);
void FindBasketball_Double(void);
void FindVolleyball_jindian(void);
void FindBasketball_jindian(void);
void FindFrame(void);

void FindBall_vision(u8 ball);		//视觉找球,限制4米以内
void FindBall_radar(void);			//利用激光找球
void FindBall_VandR(u8 ball);			//视觉、雷达找球结合
void FindBall_VandR_sanfenxian(u8 ball);//三分线找球
void FindBall_VandR_middle(u8 ball);
void FindBall_VandR_sanfenxian_VisionFirst(u8 ball);//三分线内视觉优先找球Self_Edit

void FindBall_VandR_VisionMiddle(u8 ball);//平移对正

void Choose_ball(u8 ball);//串口选球


void GoBack_Vision(u8 ball);         //视觉回位
void FindBasketry(void);       //找篮筐 

#endif
