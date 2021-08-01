#include "remote.h"
#include "delay.h"
#include "lcd.h"
#include "main.h"
#include "control.h"

//ң��������״̬
//[7]:�յ����������־
//[6]:�õ���һ��������������Ϣ
//[5]:����
//[4]:����������Ƿ��Ѿ�������							   
//[3:0]:�����ʱ��
u8 	RmtSta=0;
u16 Dval;		//�½���ʱ��������ֵ
u32 RmtRec=0;	//������յ�������
u8  RmtCnt=0;	//�������µĴ���


//����������
//����ֵ:
//	 0,û���κΰ�������
//����,���µİ�����ֵ.
u8 Remote_Scan(void)
{        
	u8 sta=0;       
  u8 t1,t2;  
	if(RmtSta&(1<<6))//�õ�һ��������������Ϣ��
	{ 
	    t1=RmtRec>>24;			//�õ���ַ��
	    t2=(RmtRec>>16)&0xff;	//�õ���ַ���� 
 	    if((t1==(u8)~t2)&&t1==REMOTE_ID)//����ң��ʶ����(ID)����ַ 
	    { 
	        t1=RmtRec>>8;
	        t2=RmtRec; 	
	        if(t1==(u8)~t2)sta=t1;//��ֵ��ȷ	 
		}   
		if((sta==0)||((RmtSta&0X80)==0))//�������ݴ���/ң���Ѿ�û�а�����
		{
		 	RmtSta&=~(1<<6);//������յ���Ч������ʶ
			RmtCnt=0;		//�����������������
		}
	}
	if (sta)
	{
		delay_ms(500);
		RmtSta = 0;
	}	
    return sta;
}


u8 Remote_Control(void)
{
	u8 flag = 0;
	u8 key = 0; 				//����ֵ


	key=Remote_Scan();//�ƺ�û��
	chengxu = 0;	
	//ѡ�����
	while (1)
	{
		LCD_ShowString(30 + 200, 500, 200, 24, 24, "chengxu:");

		key = Remote_Scan();
		switch (key)
		{
		case 0: //û�а�������

			break;
		case KEY_RIGHT: //��
			LCD_ShowString(30 + 200 , 500,200, 24, 24, "qiu:    ");
			flag = 1;
			break;
		case KEY_DOWN: //��
			LCD_ShowString(30 + 200, 500, 200, 24, 24, "chengxu-");
			if (chengxu != 0)
				chengxu--;
			break;
		case KEY_LEFT: //��
			LCD_ShowString(30 + 200, 500, 200, 24, 24, "clear   ");
			chengxu = 0;
			break;
		case KEY_UP: //��
			LCD_ShowString(30 + 200, 500, 200, 24, 24, "chengxu+");
			chengxu++;
			break;
		case KEY_0:
			chengxu = 0;
			break;		
		case KEY_1:
			chengxu = 1;
			break;
		case KEY_2:
			chengxu = 2;
			break;
		case KEY_3:
			chengxu = 3;
			break;
		case KEY_4:
			chengxu = 4;
			break;
		case KEY_5:
			chengxu = 5;
			break;
		case KEY_6:
			chengxu = 6;
			break;
		}
		
		LCD_ShowNum(30 + 200 + 48 + 36 + 45, 380, chengxu, 4, 24);

		if (flag)
			break;
	}

	flag = 0;
	key = 0;
	//ѡ����
	while (1)
	{
		key = Remote_Scan();
		switch (key)
		{
		case 0: //û�а�������

			break;
		case KEY_RIGHT: //��
			LCD_ShowString(30 + 200 , 500,200, 24, 24, "changdi   ");
			flag = 1;
			break;
		case KEY_DOWN: //��
			LCD_ShowString(30 + 200 , 500,200, 24, 24, "qiu-");
			if (qiu != 0)
				qiu--;
			break;
		case KEY_LEFT: //��
			LCD_ShowString(30 + 200 , 500,200, 24, 24, "clear   ");
			qiu = 0;
			break;
		case KEY_UP: //��
			LCD_ShowString(30 + 200 , 500,200, 24, 24, "qiu+");
			qiu++;
			break;
		case KEY_0:
			qiu = 0;
			break;		
		case KEY_1:
			qiu = 1;
			break;
		case KEY_2:
			qiu = 2;
			break;
		case KEY_3:
			qiu = 3;
			break;
		case KEY_4:
			qiu = 4;
			break;
		case KEY_5:
			qiu = 5;
			break;
		case KEY_6:
			qiu = 6;
			break;
		case KEY_7:
			qiu = 7;
			break;
/////////////////Self_Edit
		case KEY_8:
			qiu = 8;//Self_Edit
			break;
		case KEY_9:
			qiu = 9;//Self_Edit
			break;
/////////////////
		}

		LCD_ShowNum(30 + 200 + 48 + 36 + 45, 420, qiu, 4, 24);

		if (flag)
			break;
	}

	flag = 0;
	key = 0;
	//ѡ�񳡵�
	while (1)
	{
		key = Remote_Scan();
		switch (key)
		{
		case 0: //û�а�������
			break;
		case KEY_RIGHT: //��
			LCD_ShowString(30 + 200 , 500,200, 24, 24, "start   ");
			flag = 1;
			break;
		case KEY_DOWN: //��
			LCD_ShowString(30 + 200 , 500,200, 24, 24, "changdi-");
			if (changdi != 0)
				changdi--;
			break;
		case KEY_LEFT: //��
			LCD_ShowString(30 + 200 , 500,200, 24, 24, "clear   ");
			changdi = 0;
			break;
		case KEY_UP: //��
			LCD_ShowString(30 + 200 , 500,200, 24, 24, "changdi+");
			changdi++;
			break;
		case KEY_POWER:
			flag = 1;
			chengxu = 99;
			break;
		case KEY_0:
			changdi = 0;
			break;		
		case KEY_1:
			changdi = 1;
		    break;
		case KEY_2:
			changdi = 2;
		    break;
		case KEY_3:
			changdi = 3;
		    break;
		case KEY_4:
			changdi = 4;
		    break;
		case KEY_5:
			changdi = 5;
		    break;
		case KEY_6:
			changdi = 6;
		    break;
		}
		
		Basketry(changdi);
		Distance(changdi);

		
		LCD_ShowNum(30 + 200 + 48 + 36 + 45, 460, changdi, 4, 24);

		if (flag)
			break;
	}  


}
