#include "remote.h"
#include "delay.h"
#include "lcd.h"
#include "main.h"
#include "control.h"

//遥控器接收状态
//[7]:收到了引导码标志
//[6]:得到了一个按键的所有信息
//[5]:保留
//[4]:标记上升沿是否已经被捕获							   
//[3:0]:溢出计时器
u8 	RmtSta=0;
u16 Dval;		//下降沿时计数器的值
u32 RmtRec=0;	//红外接收到的数据
u8  RmtCnt=0;	//按键按下的次数


//处理红外键盘
//返回值:
//	 0,没有任何按键按下
//其他,按下的按键键值.
u8 Remote_Scan(void)
{        
	u8 sta=0;       
  u8 t1,t2;  
	if(RmtSta&(1<<6))//得到一个按键的所有信息了
	{ 
	    t1=RmtRec>>24;			//得到地址码
	    t2=(RmtRec>>16)&0xff;	//得到地址反码 
 	    if((t1==(u8)~t2)&&t1==REMOTE_ID)//检验遥控识别码(ID)及地址 
	    { 
	        t1=RmtRec>>8;
	        t2=RmtRec; 	
	        if(t1==(u8)~t2)sta=t1;//键值正确	 
		}   
		if((sta==0)||((RmtSta&0X80)==0))//按键数据错误/遥控已经没有按下了
		{
		 	RmtSta&=~(1<<6);//清除接收到有效按键标识
			RmtCnt=0;		//清除按键次数计数器
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
	u8 key = 0; 				//按键值


	key=Remote_Scan();//似乎没用
	chengxu = 0;	
	//选择程序
	while (1)
	{
		LCD_ShowString(30 + 200, 500, 200, 24, 24, "chengxu:");

		key = Remote_Scan();
		switch (key)
		{
		case 0: //没有按键按下

			break;
		case KEY_RIGHT: //右
			LCD_ShowString(30 + 200 , 500,200, 24, 24, "qiu:    ");
			flag = 1;
			break;
		case KEY_DOWN: //下
			LCD_ShowString(30 + 200, 500, 200, 24, 24, "chengxu-");
			if (chengxu != 0)
				chengxu--;
			break;
		case KEY_LEFT: //左
			LCD_ShowString(30 + 200, 500, 200, 24, 24, "clear   ");
			chengxu = 0;
			break;
		case KEY_UP: //上
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
	//选择球
	while (1)
	{
		key = Remote_Scan();
		switch (key)
		{
		case 0: //没有按键按下

			break;
		case KEY_RIGHT: //右
			LCD_ShowString(30 + 200 , 500,200, 24, 24, "changdi   ");
			flag = 1;
			break;
		case KEY_DOWN: //下
			LCD_ShowString(30 + 200 , 500,200, 24, 24, "qiu-");
			if (qiu != 0)
				qiu--;
			break;
		case KEY_LEFT: //左
			LCD_ShowString(30 + 200 , 500,200, 24, 24, "clear   ");
			qiu = 0;
			break;
		case KEY_UP: //上
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
	//选择场地
	while (1)
	{
		key = Remote_Scan();
		switch (key)
		{
		case 0: //没有按键按下
			break;
		case KEY_RIGHT: //右
			LCD_ShowString(30 + 200 , 500,200, 24, 24, "start   ");
			flag = 1;
			break;
		case KEY_DOWN: //下
			LCD_ShowString(30 + 200 , 500,200, 24, 24, "changdi-");
			if (changdi != 0)
				changdi--;
			break;
		case KEY_LEFT: //左
			LCD_ShowString(30 + 200 , 500,200, 24, 24, "clear   ");
			changdi = 0;
			break;
		case KEY_UP: //上
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
