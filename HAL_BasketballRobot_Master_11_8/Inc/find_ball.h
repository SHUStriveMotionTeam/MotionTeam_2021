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

void FindBall_vision(u8 ball);		//�Ӿ�����,����4������
void FindBall_radar(void);			//���ü�������
void FindBall_VandR(u8 ball);			//�Ӿ����״�������
void FindBall_VandR_sanfenxian(u8 ball);//����������
void FindBall_VandR_middle(u8 ball);
void FindBall_VandR_sanfenxian_VisionFirst(u8 ball);//���������Ӿ���������Self_Edit

void FindBall_VandR_VisionMiddle(u8 ball);//ƽ�ƶ���

void Choose_ball(u8 ball);//����ѡ��


void GoBack_Vision(u8 ball);         //�Ӿ���λ
void FindBasketry(void);       //������ 

#endif
