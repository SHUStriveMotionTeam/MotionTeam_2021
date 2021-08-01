#include "find_ball.h"
#include "remote.h"

u8 ball;     
//int vision_flag1 = 0;
//int vision_flag2 = 0;
//int vision_flag3 = 0;

void FindVolleyball_Yellow(void)
{
	ball = '1';
	HAL_UART_Transmit(&huart1, &ball, 1, 1000);
}

void FindVolleyball_Red(void)
{
	ball = '2';
	HAL_UART_Transmit(&huart1, &ball, 1, 1000);
}

void FindBasketball_Blue(void)
{
	ball = '3';
	HAL_UART_Transmit(&huart1, &ball, 1 , 1000);
}

void FindBasketball_Orange(void)
{
	ball = '4';
	HAL_UART_Transmit(&huart1, &ball, 1, 1000);
}

void FindBasketball_Double(void)
{
	ball = '5';
	HAL_UART_Transmit(&huart1, &ball, 1, 1000);
}

void FindVolleyball_Double(void)
{
	ball = '6';
	HAL_UART_Transmit(&huart1, &ball, 1, 1000);
}

void FindVolleyball_jindian(void)
{
	ball = '7';
	HAL_UART_Transmit(&huart1, &ball, 1, 1000);
}

void FindBasketball_jindian(void)
{
	ball = '8';
	HAL_UART_Transmit(&huart1, &ball, 1, 1000);
}

void FindFrame(void)//找框
{
	ball = 'a';
	HAL_UART_Transmit(&huart1,&ball,1,1000);
}

//串口选球
void Choose_ball (u8 ball)
{	
	switch (ball)
	{
	case 1:
		FindVolleyball_Red();
		delay_ms(100);
		FindVolleyball_Red();
		delay_ms(100);
		FindVolleyball_Red();
		break;
	case 2:
		FindVolleyball_Yellow();
		delay_ms(100);
		FindVolleyball_Yellow();
		delay_ms(100);
		FindVolleyball_Yellow();
		break;
	case 3:
		FindBasketball_Blue();
		delay_ms(100);
		FindBasketball_Blue();
		delay_ms(100);
		FindBasketball_Blue();
		break;
	case 4:
		FindBasketball_Orange();
		delay_ms(100);
		FindBasketball_Orange();
		delay_ms(100);
		FindBasketball_Orange();
		break;
	case 5:
		FindBasketball_Double();
		delay_ms(100);
		FindBasketball_Double();
		delay_ms(100);
		FindBasketball_Double();
		break;
	case 6:
		FindVolleyball_Double();
		delay_ms(100);
		FindVolleyball_Double();
		delay_ms(100);
		FindVolleyball_Double();
		break;	
	case 7:
		FindVolleyball_jindian();
		delay_ms(100);
		FindVolleyball_jindian();
		delay_ms(100);
		FindVolleyball_jindian();
		break;
	case 8:
		FindBasketball_jindian();
		delay_ms(100);
		FindBasketball_jindian();
		delay_ms(100);
		FindBasketball_jindian();
		break;
	
	
	
	}

}


//视觉找球
//限制4米以内
void FindBall_vision(u8 ball)
{
	float w = 200;

	u8 time = 1;

	float theta = BasketballRobot.ThetaR, D_theta = 0;

	Choose_ball (ball);//串口向上位机发送需要找球的信息

	Set_MotorSpeed(0, 0, 0, 0);

	LCD_Show_getspeed();

	Vision.RX_STA = 0;
	do
	{
		//等待数据接收完成
		while ((Vision.RX_STA & 0x8000) == 0)
			;

		//所得数据无效
		if (!GetVisionData())
		{
			if (time == 0)
				;

			//尝试五次
			else if (time++ < 5)
			{
				//Set_MotorSpeed(0,0,0,0);
				continue;
			}
			//尝试五次后仍未找到球
			else if (time != 0)
				time = 0;
		}
		//数据有效
		else
			time = 1;

		//没找到球,自转
		if (time == 0)
		{
			D_theta = BasketballRobot.ThetaR - theta;
			if ((D_theta > PI / 6.0f && D_theta < PI) || (D_theta < -PI && D_theta > -PI * 11.0f / 6.0f))
			{
				w = -600;
			}
			if ((D_theta < -PI / 6.0f && D_theta > -PI) || (D_theta > PI && D_theta < PI * 11.0f / 6.0f))
			{
				w = 600;
			}
			GetMotorVelocity(0, 0, w);
			Set_MotorSpeed(Motor[0].SetSpeed, Motor[1].SetSpeed,
			               Motor[2].SetSpeed, Motor[3].SetSpeed);

			LCD_Show_getspeed();
		}

		//无效数据
		else if (Vision.Depth > 4000)
		{
			GetMotorVelocity(0, 0, 0);
			Set_MotorSpeed(Motor[0].SetSpeed, Motor[1].SetSpeed,
			               Motor[2].SetSpeed, Motor[3].SetSpeed);
		}

		else if ((Vision.X < VISION_MID - 30) && Vision.Depth > 1500)
		{
			GetMotorVelocity_Self(300, 600, 0);
			Set_MotorSpeed(Motor[0].SetSpeed, Motor[1].SetSpeed,
			               Motor[2].SetSpeed, Motor[3].SetSpeed);
		}
		else if ((Vision.X > VISION_MID + 30) && Vision.Depth > 1500)
		{
			GetMotorVelocity_Self(-300, 600, 0);
			Set_MotorSpeed(Motor[0].SetSpeed, Motor[1].SetSpeed,
			               Motor[2].SetSpeed, Motor[3].SetSpeed);
		}
		else if (Vision.Depth > 1300)
		{
			GetMotorVelocity_Self(0, 500, 0);
			Set_MotorSpeed(Motor[0].SetSpeed, Motor[1].SetSpeed,
			               Motor[2].SetSpeed, Motor[3].SetSpeed);
		}
		else if ((Vision.X < VISION_MID - 20) && Vision.Depth > 1200)
		{
			GetMotorVelocity_Self(200, 400, 0); //原来-40 0 0
			Set_MotorSpeed(Motor[0].SetSpeed, Motor[1].SetSpeed,
			               Motor[2].SetSpeed, Motor[3].SetSpeed);
		}
		else if ((Vision.X > VISION_MID + 20) && (Vision.Depth > 1200))
		{
			GetMotorVelocity_Self(-200, 400, 0); //原来4 0 0
			Set_MotorSpeed(Motor[0].SetSpeed, Motor[1].SetSpeed,
			               Motor[2].SetSpeed, Motor[3].SetSpeed);
		}
		else if (Vision.Depth > 1000)
		{
			GetMotorVelocity_Self(0, 300, 0);
			Set_MotorSpeed(Motor[0].SetSpeed, Motor[1].SetSpeed,
			               Motor[2].SetSpeed, Motor[3].SetSpeed);
		}
		else if (Vision.X < VISION_MID - 30)
		{
			GetMotorVelocity_Self(300, 0, 0);
			Set_MotorSpeed(Motor[0].SetSpeed, Motor[1].SetSpeed,
			               Motor[2].SetSpeed, Motor[3].SetSpeed);

		}
		else if (Vision.X > VISION_MID + 30)
		{
			GetMotorVelocity_Self(-300, 0, 0);
			Set_MotorSpeed(Motor[0].SetSpeed, Motor[1].SetSpeed,
			               Motor[2].SetSpeed, Motor[3].SetSpeed);
		}
		else if (Vision.X <= VISION_MID + 30 && Vision.X > VISION_MID + 10)
		{
			GetMotorVelocity_Self(-150, 0, 0);
			Set_MotorSpeed(Motor[0].SetSpeed, Motor[1].SetSpeed,
			               Motor[2].SetSpeed, Motor[3].SetSpeed);
		}
		else if (Vision.X >= VISION_MID - 30 && Vision.X < VISION_MID - 10)
		{
			GetMotorVelocity_Self(150, 0, 0);
			Set_MotorSpeed(Motor[0].SetSpeed, Motor[1].SetSpeed,
			               Motor[2].SetSpeed, Motor[3].SetSpeed);
		}
		else
		{
			Set_MotorSpeed(0, 0, 0, 0);
		
			Robot_ArmDown();
			GetMotorVelocity_Self(0, 1000, 0);
			Set_MotorSpeed(Motor[0].SetSpeed, Motor[1].SetSpeed,
			               Motor[2].SetSpeed, Motor[3].SetSpeed);
			break;
		}
	} while (1);

	GetInfraredState();

	Set_MotorSpeed(0, 0, 0, 0);

	Robot_ArmUp();
	LCD_Show_getspeed();
}

//利用雷达找球
//不用区分颜色
//限制3m以内
void FindBall_radar(void)
{
	float w = 600;
	float theta = BasketballRobot.ThetaD, D_theta = 0;

	Set_MotorSpeed(0, 0, 0, 0);
	LCD_Show_getspeed();
	do
	{
		if (!GetRadarData())
		{

			Set_MotorSpeed(0, 0, 0, 0);
			continue;
		}
//		LED0 = !LED0;

//		LCD_ShowString(30 + 200, 460, 200, 16, 16, "Radar:rad");
//		LCD_ShowNum(30 + 200 + 48 + 8 + 45, 460, Radar.Angle, 4, 16);
//		LCD_ShowString(30 + 200, 480, 200, 16, 16, "Radar:length");
//		LCD_ShowNum(30 + 200 + 48 + 8 + 45, 480, Radar.Distance, 4, 16);

		Radar.State = 0;

		//		if(Radar.Distance < 10)
		//			continue;
		if (Radar.Distance > 3000)
		{
			D_theta = BasketballRobot.ThetaR - theta;
			if ((D_theta > PI / 6.0f && D_theta < PI) || (D_theta < -PI && D_theta > -PI * 11.0f / 6.0f))
			{
				w = -600;
			}
			if ((D_theta < -PI / 6.0f && D_theta > -PI) || (D_theta > PI && D_theta < PI * 11.0f / 6.0f))
			{
				w = 600;
			}
			GetMotorVelocity(0, 0, w);
			Set_MotorSpeed(Motor[0].SetSpeed, Motor[1].SetSpeed,
			               Motor[2].SetSpeed, Motor[3].SetSpeed);
			LCD_Show_setspeed();
		}
		while ((Radar.RX_STA & 0x8000) == 0);
		
		//GetVisionData();

//		if (INFRARED == 1)//如果铲到球，退出循环
//			break;
		
		//else  
			if (!GetRadarData())
		{
			Set_MotorSpeed(0,0,0,0);
			continue;
		}
		else if (Radar.Angle < RADAR_MID - 10)
		{
			GetMotorVelocity_Self(-600, 0, 0);
			Set_MotorSpeed(Motor[0].SetSpeed, Motor[1].SetSpeed,
						   Motor[2].SetSpeed, Motor[3].SetSpeed);
		}
		else if (Radar.Angle > RADAR_MID + 10)
		{
			GetMotorVelocity_Self(600, 0, 0);
			Set_MotorSpeed(Motor[0].SetSpeed, Motor[1].SetSpeed,
						   Motor[2].SetSpeed, Motor[3].SetSpeed);
		}			
		else if(Radar.Distance > 1000)
		{
			GetMotorVelocity_Self(0, 1500, 0);
			Set_MotorSpeed(Motor[0].SetSpeed, Motor[1].SetSpeed,
						   Motor[2].SetSpeed, Motor[3].SetSpeed);
		}
		else if (Radar.Angle < RADAR_MID - 3)
		{
			GetMotorVelocity_Self(-400, 0, 0);
			Set_MotorSpeed(Motor[0].SetSpeed, Motor[1].SetSpeed,
						   Motor[2].SetSpeed, Motor[3].SetSpeed);
		}
		else if (Radar.Angle > RADAR_MID + 3)
		{
			GetMotorVelocity_Self(400, 0, 0);
			Set_MotorSpeed(Motor[0].SetSpeed, Motor[1].SetSpeed,
						   Motor[2].SetSpeed, Motor[3].SetSpeed);
		}
		else if (Radar.Distance > 800)
		{
			GetMotorVelocity_Self(0, 1000, 0);
			Set_MotorSpeed(Motor[0].SetSpeed, Motor[1].SetSpeed,
						   Motor[2].SetSpeed, Motor[3].SetSpeed);
		}
		else if (Radar.Distance > 550)
		{
			GetMotorVelocity_Self(0, 800, 0);
			Set_MotorSpeed(Motor[0].SetSpeed, Motor[1].SetSpeed,
						   Motor[2].SetSpeed, Motor[3].SetSpeed);
		}
		else
		{
			Set_MotorSpeed(0, 0, 0, 0);
			Robot_ArmDown();
			GetMotorVelocity_Self(0, 500, 0);
			Set_MotorSpeed(Motor[0].SetSpeed, Motor[1].SetSpeed,
						   Motor[2].SetSpeed, Motor[3].SetSpeed);
			if (Radar.Distance < 260)
				break;
		}
		LCD_Show_setspeed();
	} while (1);

	//GetInfraredState();
//	while(1)
//	{
//		if (Radar.Distance > 150)
//			GetMotorVelocity_Self(0, 300, 0);
//	}
	delay_ms(700);
			
	Set_MotorSpeed(0, 0, 0, 0);

	Robot_ArmUp();
	LCD_Show_getspeed();
}

//视觉、雷达找球结合
//限制4m以内
void FindBall_VandR(u8 ball)
{

	float w = 600;
	u8 time = 1;
	float theta = BasketballRobot.ThetaD, D_theta = 0;
	
	Choose_ball (ball);//串口向上位机发送需要找球的信息
	
	Set_MotorSpeed(0, 0, 0, 0);
	
	LCD_Show_getspeed();

	//清空视觉串口数据
	USART1_RX_STA = 0;

	//清空串口接收数据缓存
	USART3_RX_STA = 0;
	

	while (1)//视觉走到1m
	{
		while ((Vision.RX_STA & 0x8000) == 0);
		while ((Radar.RX_STA & 0x8000) == 0);
		
		if (!GetVisionData())
		{
			if (time == 0)
			{
			}
			else if (time++ < 5)
			{
//				Set_MotorSpeed(0, 0, 0, 0);
//				continue;
			}
			else if (time != 0)
				time = 0;
		}
		else
			time = 1;
		
		GetRadarData();
		
//		if (Radar.Distance < 600)
//			break;

		//没找到球,自转
		if (time == 0)
		{
			D_theta = BasketballRobot.ThetaD - theta;
			if ((D_theta > 60 && D_theta < 180) || (D_theta < -180 && D_theta > -300))
			{
				w = 300;
			}
			if ((D_theta < -60 && D_theta > -180) || (D_theta > 180 && D_theta < 300))
			{
				w = -300;
			}
			Set_MotorSpeed(w,w,w,w);
			
			LCD_Show_getspeed();
		}
		else if (Vision.Depth > 4000)
		{
			Set_MotorSpeed(0, 0, 0, 0);
		}
		
		else if (Vision.X > VISION_MID + 40)
		{
			GetMotorVelocity_Self(-400, 0, 0);
			Set_MotorSpeed(Motor[0].SetSpeed, Motor[1].SetSpeed,Motor[2].SetSpeed, Motor[3].SetSpeed);
		}
		else if ((Vision.X < VISION_MID - 40) )
		{
			GetMotorVelocity_Self(400, 0, 0);
			Set_MotorSpeed(Motor[0].SetSpeed, Motor[1].SetSpeed,
			               Motor[2].SetSpeed, Motor[3].SetSpeed);
		}
		else if ( Vision.Depth > 2000)
		{
			GetMotorVelocity_Self(0, 1500, 0);
			Set_MotorSpeed(Motor[0].SetSpeed, Motor[1].SetSpeed,
			               Motor[2].SetSpeed, Motor[3].SetSpeed);
		}		
		
		//先调整后直行
		else if (Vision.X < VISION_MID - 30)
		{
			GetMotorVelocity_Self(600,0, 0);
			//GetMotorVelocity_Self(250,0, 0);//SELF_EDIT
			Set_MotorSpeed(Motor[0].SetSpeed, Motor[1].SetSpeed,
			               Motor[2].SetSpeed, Motor[3].SetSpeed);
		}
		else if (Vision.X > VISION_MID + 30 )
		{
			GetMotorVelocity_Self(-600, 0, 0);
			//GetMotorVelocity_Self(-250, 0, 0);//SELF_EDIT
			Set_MotorSpeed(Motor[0].SetSpeed, Motor[1].SetSpeed,
			               Motor[2].SetSpeed, Motor[3].SetSpeed);
		}
		else if (Vision.Depth > 1000)
		{
			//GetMotorVelocity_Self(0, 1000, 0);
			GetMotorVelocity_Self(0, 1000, 0);
			Set_MotorSpeed(Motor[0].SetSpeed, Motor[1].SetSpeed,
			               Motor[2].SetSpeed, Motor[3].SetSpeed);
		}
		else if (Vision.X < VISION_MID - 15)//SELF_EDIT
		{
			GetMotorVelocity_Self(200,0, 0);
			Set_MotorSpeed(Motor[0].SetSpeed, Motor[1].SetSpeed,
			               Motor[2].SetSpeed, Motor[3].SetSpeed);
		}
		else if (Vision.X > VISION_MID + 15 )//SELF_EDIT
		{
			GetMotorVelocity_Self(-200, 0, 0);
			Set_MotorSpeed(Motor[0].SetSpeed, Motor[1].SetSpeed,
			               Motor[2].SetSpeed, Motor[3].SetSpeed);
		}
		else
			break;
	} 
	
	
	
	if (Radar.Distance > 1000)
	{
		//雷达距离过大时，按照视觉数据寻找
		while (1)
		{
			while ((Vision.RX_STA & 0x8000) == 0);

			//GetVisionData();//Self_Edit
			GetRadarData();

			if (Radar.Distance < 1000)
				break;

            GetVisionData();//Self_Edit
//			if (!GetVisionData())//为了流畅临时注释
//            {
//                vision_flag1++;
//				Set_MotorSpeed(0, 0, 0, 0);
//            }

			//先调整后直行
			//else if (Vision.X > VISION_MID + 30)//为了流畅临时注释
            if (Vision.X > VISION_MID + 30)
			{
				GetMotorVelocity_Self(-800,0, 0);
				Set_MotorSpeed(Motor[0].SetSpeed, Motor[1].SetSpeed,Motor[2].SetSpeed, Motor[3].SetSpeed);
			}
			else if ((Vision.X < VISION_MID - 30) )
			{
				GetMotorVelocity_Self(800, 0, 0);
				Set_MotorSpeed(Motor[0].SetSpeed, Motor[1].SetSpeed,
							   Motor[2].SetSpeed, Motor[3].SetSpeed);
			}			
			
			else if (Vision.Depth > 1000)
			{
				GetMotorVelocity_Self(0, 1000, 0);
				Set_MotorSpeed(Motor[0].SetSpeed, Motor[1].SetSpeed,
							   Motor[2].SetSpeed, Motor[3].SetSpeed);
			}
			
			else if (Vision.X < VISION_MID - 20)
			{
				GetMotorVelocity_Self(600,0, 0);
				Set_MotorSpeed(Motor[0].SetSpeed, Motor[1].SetSpeed,
							   Motor[2].SetSpeed, Motor[3].SetSpeed);
			}
			else if (Vision.X > VISION_MID + 20 )
			{
				GetMotorVelocity_Self(-600, 0, 0);
				Set_MotorSpeed(Motor[0].SetSpeed, Motor[1].SetSpeed,
							   Motor[2].SetSpeed, Motor[3].SetSpeed);
			}
			
			else if (Vision.Depth > 700)
			{
				GetMotorVelocity_Self(0, 700, 0);
				Set_MotorSpeed(Motor[0].SetSpeed, Motor[1].SetSpeed,Motor[2].SetSpeed, Motor[3].SetSpeed);
			}
			else
			{
				Set_MotorSpeed(0, 0, 0, 0);
				Robot_ArmDown();
				GetMotorVelocity_Self(0, 500, 0);
				Set_MotorSpeed(Motor[0].SetSpeed, Motor[1].SetSpeed,Motor[2].SetSpeed, Motor[3].SetSpeed);
				break;				
			}			
		}
	}	
	
	
	//雷达距离合适，按照雷达数据寻找，雷达1m内找球
	if (Radar.Distance <= 1000)
	{
		while (1)
		{
			while ((Radar.RX_STA & 0x8000) == 0);
			
			GetVisionData();
			
			if (INFRARED == 1)
				break;			
			else if (!GetRadarData())
			{
				Set_MotorSpeed(0,0,0,0);
				continue;
			}
			else if (Radar.Angle < RADAR_MID - 10)
			{
				GetMotorVelocity_Self(-600, 0, 0);
				Set_MotorSpeed(Motor[0].SetSpeed, Motor[1].SetSpeed,
							   Motor[2].SetSpeed, Motor[3].SetSpeed);
			}
			else if (Radar.Angle > RADAR_MID + 10)
			{
				GetMotorVelocity_Self(600, 0, 0);
				Set_MotorSpeed(Motor[0].SetSpeed, Motor[1].SetSpeed,
							   Motor[2].SetSpeed, Motor[3].SetSpeed);
			}			
			else if(Radar.Distance > 800)
			{
				GetMotorVelocity_Self(0, 1000, 0);
				Set_MotorSpeed(Motor[0].SetSpeed, Motor[1].SetSpeed,
							   Motor[2].SetSpeed, Motor[3].SetSpeed);
			}
			else if (Radar.Angle < RADAR_MID - 3)
			{
				GetMotorVelocity_Self(-400, 0, 0);
				Set_MotorSpeed(Motor[0].SetSpeed, Motor[1].SetSpeed,
							   Motor[2].SetSpeed, Motor[3].SetSpeed);
			}
			else if (Radar.Angle > RADAR_MID + 3)
			{
				GetMotorVelocity_Self(400, 0, 0);
				Set_MotorSpeed(Motor[0].SetSpeed, Motor[1].SetSpeed,
							   Motor[2].SetSpeed, Motor[3].SetSpeed);
			}
			else if (Radar.Distance > 550)
			{
				GetMotorVelocity_Self(0, 800, 0);
				Set_MotorSpeed(Motor[0].SetSpeed, Motor[1].SetSpeed,
							   Motor[2].SetSpeed, Motor[3].SetSpeed);
			}
			else
			{
				Set_MotorSpeed(0, 0, 0, 0);
				Robot_ArmDown();
				GetMotorVelocity_Self(0, 500, 0);
				Set_MotorSpeed(Motor[0].SetSpeed, Motor[1].SetSpeed,
							   Motor[2].SetSpeed, Motor[3].SetSpeed);
				if (Radar.Distance < 260)
					break;
			}
		}
	}
	GetInfraredState();
	
	Set_MotorSpeed(0, 0, 0, 0);

	Robot_ArmUp();

	LCD_Show_getspeed();
	
}


void FindBall_VandR5(u8 ball) //self edit 脑洞产物
{

	float w = 600;
	u8 time = 1;
	float theta = BasketballRobot.ThetaD, D_theta = 0;
	
	Choose_ball (ball);//串口向上位机发送需要找球的信息
	
	Set_MotorSpeed(0, 0, 0, 0);
	
	LCD_Show_getspeed();

	//清空视觉串口数据
	USART1_RX_STA = 0;

	//清空串口接收数据缓存
	USART3_RX_STA = 0;
	

	while (1)//视觉走到1m
	{
		while ((Vision.RX_STA & 0x8000) == 0);
		while ((Radar.RX_STA & 0x8000) == 0);
		
		if (!GetVisionData())
		{
			if (time == 0)
			{
			}
			else if (time++ < 5)
			{
//				Set_MotorSpeed(0, 0, 0, 0);
//				continue;
			}
			else if (time != 0)
				time = 0;
		}
		else
			time = 1;
		
		GetRadarData();
		
//		if (Radar.Distance < 600)
//			break;

		//没找到球,自转
		if (time == 0)
		{
			D_theta = BasketballRobot.ThetaD - theta;
			if ((D_theta > 60 && D_theta < 180) || (D_theta < -180 && D_theta > -300))
			{
				w = 300;
			}
			if ((D_theta < -60 && D_theta > -180) || (D_theta > 180 && D_theta < 300))
			{
				w = -300;
			}
			Set_MotorSpeed(w,w,w,w);
			
			LCD_Show_getspeed();
		}
		else if (Vision.Depth > 4000)
		{
			Set_MotorSpeed(0, 0, 0, 0);
		}
		
		else if (Vision.X > VISION_MID + 40)
		{
			GetMotorVelocity_Self(-400, 0, 0);
			Set_MotorSpeed(Motor[0].SetSpeed, Motor[1].SetSpeed,Motor[2].SetSpeed, Motor[3].SetSpeed);
		}
		else if ((Vision.X < VISION_MID - 40) )
		{
			GetMotorVelocity_Self(400, 0, 0);
			Set_MotorSpeed(Motor[0].SetSpeed, Motor[1].SetSpeed,
			               Motor[2].SetSpeed, Motor[3].SetSpeed);
		}
		else if ( Vision.Depth > 2000)
		{
			GetMotorVelocity_Self(0, 1500, 0);
			Set_MotorSpeed(Motor[0].SetSpeed, Motor[1].SetSpeed,
			               Motor[2].SetSpeed, Motor[3].SetSpeed);
		}		
		
		//先调整后直行
		else if (Vision.X < VISION_MID - 30)
		{
			GetMotorVelocity_Self(600,0, 0);
			//GetMotorVelocity_Self(250,0, 0);//SELF_EDIT
			Set_MotorSpeed(Motor[0].SetSpeed, Motor[1].SetSpeed,
			               Motor[2].SetSpeed, Motor[3].SetSpeed);
		}
		else if (Vision.X > VISION_MID + 30 )
		{
			GetMotorVelocity_Self(-600, 0, 0);
			//GetMotorVelocity_Self(-250, 0, 0);//SELF_EDIT
			Set_MotorSpeed(Motor[0].SetSpeed, Motor[1].SetSpeed,
			               Motor[2].SetSpeed, Motor[3].SetSpeed);
		}
		else if (Vision.Depth > 1000)
		{
			//GetMotorVelocity_Self(0, 1000, 0);
			GetMotorVelocity_Self(0, 1000, 0);
			Set_MotorSpeed(Motor[0].SetSpeed, Motor[1].SetSpeed,
			               Motor[2].SetSpeed, Motor[3].SetSpeed);
		}
		else if (Vision.X < VISION_MID - 15)//SELF_EDIT
		{
			GetMotorVelocity_Self(200,0, 0);
			Set_MotorSpeed(Motor[0].SetSpeed, Motor[1].SetSpeed,
			               Motor[2].SetSpeed, Motor[3].SetSpeed);
		}
		else if (Vision.X > VISION_MID + 15 )//SELF_EDIT
		{
			GetMotorVelocity_Self(-200, 0, 0);
			Set_MotorSpeed(Motor[0].SetSpeed, Motor[1].SetSpeed,
			               Motor[2].SetSpeed, Motor[3].SetSpeed);
		}
		else
			break;
	} 
	
	
	
	if (Radar.Distance > 1000)
	{
		//雷达距离过大时，按照视觉数据寻找
		while (1)
		{
			while ((Vision.RX_STA & 0x8000) == 0);

			//GetVisionData();
			GetRadarData();

			if (Radar.Distance < 1000)
				break;

			if (!GetVisionData())
				Set_MotorSpeed(0, 0, 0, 0);

			//先调整后直行
			else if (Vision.X > VISION_MID + 30)
			{
				GetMotorVelocity_Self(-800,0, 0);
				Set_MotorSpeed(Motor[0].SetSpeed, Motor[1].SetSpeed,Motor[2].SetSpeed, Motor[3].SetSpeed);
			}
			else if ((Vision.X < VISION_MID - 30) )
			{
				GetMotorVelocity_Self(800, 0, 0);
				Set_MotorSpeed(Motor[0].SetSpeed, Motor[1].SetSpeed,
							   Motor[2].SetSpeed, Motor[3].SetSpeed);
			}			
			
			else if (Vision.Depth > 1000)
			{
				GetMotorVelocity_Self(0, 1000, 0);
				Set_MotorSpeed(Motor[0].SetSpeed, Motor[1].SetSpeed,
							   Motor[2].SetSpeed, Motor[3].SetSpeed);
			}
			
			else if (Vision.X < VISION_MID - 20)
			{
				GetMotorVelocity_Self(600,0, 0);
				Set_MotorSpeed(Motor[0].SetSpeed, Motor[1].SetSpeed,
							   Motor[2].SetSpeed, Motor[3].SetSpeed);
			}
			else if (Vision.X > VISION_MID + 20 )
			{
				GetMotorVelocity_Self(-600, 0, 0);
				Set_MotorSpeed(Motor[0].SetSpeed, Motor[1].SetSpeed,
							   Motor[2].SetSpeed, Motor[3].SetSpeed);
			}
			
			else if (Vision.Depth > 700)
			{
				GetMotorVelocity_Self(0, 700, 0);
				Set_MotorSpeed(Motor[0].SetSpeed, Motor[1].SetSpeed,Motor[2].SetSpeed, Motor[3].SetSpeed);
			}
			else
			{
				Set_MotorSpeed(0, 0, 0, 0);
				Robot_ArmDown();
				GetMotorVelocity_Self(0, 500, 0);
				Set_MotorSpeed(Motor[0].SetSpeed, Motor[1].SetSpeed,Motor[2].SetSpeed, Motor[3].SetSpeed);
				break;				
			}			
		}
	}	
	
	
	//雷达距离合适，按照雷达数据寻找，雷达1m内找球
	if (Radar.Distance <= 1000)
	{
		while (1)
		{
			while ((Radar.RX_STA & 0x8000) == 0);
			
			GetVisionData();
			
			if (INFRARED == 1)
				break;			
			else if (!GetRadarData())
			{
				Set_MotorSpeed(0,0,0,0);
				continue;
			}
			else if (Radar.Angle < RADAR_MID - 10)
			{
				GetMotorVelocity_Self(-600, 0, 0);
				Set_MotorSpeed(Motor[0].SetSpeed, Motor[1].SetSpeed,
							   Motor[2].SetSpeed, Motor[3].SetSpeed);
			}
			else if (Radar.Angle > RADAR_MID + 10)
			{
				GetMotorVelocity_Self(600, 0, 0);
				Set_MotorSpeed(Motor[0].SetSpeed, Motor[1].SetSpeed,
							   Motor[2].SetSpeed, Motor[3].SetSpeed);
			}			
			else if(Radar.Distance > 800)
			{
				GetMotorVelocity_Self(0, 1000, 0);
				Set_MotorSpeed(Motor[0].SetSpeed, Motor[1].SetSpeed,
							   Motor[2].SetSpeed, Motor[3].SetSpeed);
			}
			else if (Radar.Angle < RADAR_MID - 3)
			{
				GetMotorVelocity_Self(-400, 0, 0);
				Set_MotorSpeed(Motor[0].SetSpeed, Motor[1].SetSpeed,
							   Motor[2].SetSpeed, Motor[3].SetSpeed);
			}
			else if (Radar.Angle > RADAR_MID + 3)
			{
				GetMotorVelocity_Self(400, 0, 0);
				Set_MotorSpeed(Motor[0].SetSpeed, Motor[1].SetSpeed,
							   Motor[2].SetSpeed, Motor[3].SetSpeed);
			}
			else if (Radar.Distance > 550)
			{
				GetMotorVelocity_Self(0, 800, 0);
				Set_MotorSpeed(Motor[0].SetSpeed, Motor[1].SetSpeed,
							   Motor[2].SetSpeed, Motor[3].SetSpeed);
			}
			else
			{
				Set_MotorSpeed(0, 0, 0, 0);
				Robot_ArmDown();
				GetMotorVelocity_Self(0, 500, 0);
				Set_MotorSpeed(Motor[0].SetSpeed, Motor[1].SetSpeed,
							   Motor[2].SetSpeed, Motor[3].SetSpeed);
				if (Radar.Distance < 260)
					break;
			}
		}
	}
	GetInfraredState();
	
	Set_MotorSpeed(0, 0, 0, 0);

	Robot_ArmUp();

	LCD_Show_getspeed();
	
}
//视觉、雷达找球结合
//限制4m以内
void FindBall_VandR_sanfenxian(u8 ball)
{
	float w = 600;
	u8 time = 1;
	float theta = BasketballRobot.ThetaD, D_theta = 0;
	
	Choose_ball (ball);//串口向上位机发送需要找球的信息
	
	Set_MotorSpeed(0, 0, 0, 0);
	
	LCD_Show_getspeed();

	//清空视觉串口数据
	USART1_RX_STA = 0;

	//清空串口接收数据缓存
	USART3_RX_STA = 0;
	

	while (1)//视觉走到1m
	{
		while ((Vision.RX_STA & 0x8000) == 0);
		while ((Radar.RX_STA & 0x8000) == 0);
		
		if (!GetVisionData())
		{
			if (time == 0)
			{
			}
			else if (time++ < 5)
			{
//				Set_MotorSpeed(0, 0, 0, 0);
//				continue;
			}
			else if (time != 0)
				time = 0;
		}
		else
			time = 1;
		
		GetRadarData();
		
//		if (Radar.Distance < 600)
//			break;

		//没找到球,自转
		if (time == 0)
		{
			D_theta = BasketballRobot.ThetaD - theta;
			if ((D_theta > 60 && D_theta < 180) || (D_theta < -180 && D_theta > -315))
			{
				w = 300;
			}
			if ((D_theta < -60 && D_theta > -180) || (D_theta > 180 && D_theta < 315))
			{
				w = -300;
			}
			Set_MotorSpeed(w,w,w,w);
			
			LCD_Show_getspeed();
		}
		else if (Vision.Depth > 4000)
		{
			Set_MotorSpeed(0, 0, 0, 0);
		}
		
		else if (Vision.X > VISION_MID + 30)
		{
			GetMotorVelocity_Self(-500, 0, 0);
			Set_MotorSpeed(Motor[0].SetSpeed, Motor[1].SetSpeed,
			               Motor[2].SetSpeed, Motor[3].SetSpeed);
		}
		else if ((Vision.X < VISION_MID - 30) )
		{
			GetMotorVelocity_Self(500, 0, 0);
			Set_MotorSpeed(Motor[0].SetSpeed, Motor[1].SetSpeed,
			               Motor[2].SetSpeed, Motor[3].SetSpeed);
		}
		else if (Vision.X < VISION_MID - 20)
		{
			GetMotorVelocity_Self(300, 0, 0);
			Set_MotorSpeed(Motor[0].SetSpeed, Motor[1].SetSpeed,
			               Motor[2].SetSpeed, Motor[3].SetSpeed);
		}
		else if (Vision.X > VISION_MID + 20 )
		{
			GetMotorVelocity_Self(-300, 0, 0);
			Set_MotorSpeed(Motor[0].SetSpeed, Motor[1].SetSpeed,
			               Motor[2].SetSpeed, Motor[3].SetSpeed);
		}		

		else if (Vision.X < VISION_MID - 10)
		{
			GetMotorVelocity_Self(200, 0, 0);
			Set_MotorSpeed(Motor[0].SetSpeed, Motor[1].SetSpeed,
			               Motor[2].SetSpeed, Motor[3].SetSpeed);
		}
		else if (Vision.X > VISION_MID + 10 )
		{
			GetMotorVelocity_Self(-200, 0, 0);
			Set_MotorSpeed(Motor[0].SetSpeed, Motor[1].SetSpeed,
			               Motor[2].SetSpeed, Motor[3].SetSpeed);
		}			
		else if ( Vision.Depth > 2000)
		{
			GetMotorVelocity_Self(0, 1500, 0);
			Set_MotorSpeed(Motor[0].SetSpeed, Motor[1].SetSpeed,
			               Motor[2].SetSpeed, Motor[3].SetSpeed);
		}		

		else if (Vision.Depth > 1000)
		{
			GetMotorVelocity_Self(0, 1000, 0);
			Set_MotorSpeed(Motor[0].SetSpeed, Motor[1].SetSpeed,
			               Motor[2].SetSpeed, Motor[3].SetSpeed);
		}
		else
			break;
	}

	if (Radar.Distance > 1000)
	{
		//雷达距离过大时，按照视觉数据寻找
		while (1)
		{
			while ((Vision.RX_STA & 0x8000) == 0);

			//GetVisionData();//Self_Edit
			GetRadarData();
            GetVisionData();//Self_Edit
//			if (Radar.Distance < 700)
//				break;

//			if (!GetVisionData())//为了流畅临时注释
//            {
//                vision_flag3++;//slef_edit
//				Set_MotorSpeed(0, 0, 0, 0);
//            }

			//先调整后直行
			//else if (Vision.X > VISION_MID + 30)//为了流畅临时注释
            if (Vision.X > VISION_MID + 30)
			{
				GetMotorVelocity_Self(-800, 0, 0);
				Set_MotorSpeed(Motor[0].SetSpeed, Motor[1].SetSpeed,Motor[2].SetSpeed, Motor[3].SetSpeed);
			}
			else if (Vision.X < VISION_MID - 30)
			{
				GetMotorVelocity_Self(800, 0, 0);
				Set_MotorSpeed(Motor[0].SetSpeed, Motor[1].SetSpeed,
							   Motor[2].SetSpeed, Motor[3].SetSpeed);
			}						
			else if (Vision.X < VISION_MID - 20)
			{
				GetMotorVelocity_Self(600,0, 0);
				Set_MotorSpeed(Motor[0].SetSpeed, Motor[1].SetSpeed,
							   Motor[2].SetSpeed, Motor[3].SetSpeed);
			}
			else if (Vision.X > VISION_MID + 20 )
			{
				GetMotorVelocity_Self(-600, 0, 0);
				Set_MotorSpeed(Motor[0].SetSpeed, Motor[1].SetSpeed,
							   Motor[2].SetSpeed, Motor[3].SetSpeed);
			}
			else if (Vision.Depth > 1000)
			{
				GetMotorVelocity_Self(0, 1000, 0);
				Set_MotorSpeed(Motor[0].SetSpeed, Motor[1].SetSpeed,
							   Motor[2].SetSpeed, Motor[3].SetSpeed);
			}
			else if (Vision.Depth > 700)
			{
				GetMotorVelocity_Self(0, 700, 0);
				Set_MotorSpeed(Motor[0].SetSpeed, Motor[1].SetSpeed,Motor[2].SetSpeed, Motor[3].SetSpeed);
			}
			else
			{
				Set_MotorSpeed(0, 0, 0, 0);
				Robot_ArmDown();
				GetMotorVelocity_Self(0, 500, 0);
				Set_MotorSpeed(Motor[0].SetSpeed, Motor[1].SetSpeed,Motor[2].SetSpeed, Motor[3].SetSpeed);
				break;				
			}			
		}
	}	
	
	
	//雷达距离合适，按照雷达数据寻找，雷达1m内找球
	if (Radar.Distance <= 1000)
	{
		while (1)
		{
			while ((Radar.RX_STA & 0x8000) == 0);
			
			GetVisionData();

			if (INFRARED == 1)//如果铲到球，退出循环
				break;
			
			else  if (!GetRadarData())
			{
				Set_MotorSpeed(0,0,0,0);
				continue;
			}
			else if (Radar.Angle < RADAR_MID - 10)
			{
				GetMotorVelocity_Self(-600, 0, 0);
				Set_MotorSpeed(Motor[0].SetSpeed, Motor[1].SetSpeed,
							   Motor[2].SetSpeed, Motor[3].SetSpeed);
			}
			else if (Radar.Angle > RADAR_MID + 10)
			{
				GetMotorVelocity_Self(600, 0, 0);
				Set_MotorSpeed(Motor[0].SetSpeed, Motor[1].SetSpeed,
							   Motor[2].SetSpeed, Motor[3].SetSpeed);
			}			
			else if(Radar.Distance > 800)
			{
				GetMotorVelocity_Self(0, 1000, 0);
				Set_MotorSpeed(Motor[0].SetSpeed, Motor[1].SetSpeed,
							   Motor[2].SetSpeed, Motor[3].SetSpeed);
			}
			else if (Radar.Angle < RADAR_MID - 3)
			{
				GetMotorVelocity_Self(-400, 0, 0);
				Set_MotorSpeed(Motor[0].SetSpeed, Motor[1].SetSpeed,
							   Motor[2].SetSpeed, Motor[3].SetSpeed);
			}
			else if (Radar.Angle > RADAR_MID + 3)
			{
				GetMotorVelocity_Self(400, 0, 0);
				Set_MotorSpeed(Motor[0].SetSpeed, Motor[1].SetSpeed,
							   Motor[2].SetSpeed, Motor[3].SetSpeed);
			}
			else if (Radar.Distance > 550)
			{
				GetMotorVelocity_Self(0, 800, 0);
				Set_MotorSpeed(Motor[0].SetSpeed, Motor[1].SetSpeed,
							   Motor[2].SetSpeed, Motor[3].SetSpeed);
			}
			else
			{
				Set_MotorSpeed(0, 0, 0, 0);
				Robot_ArmDown();
				GetMotorVelocity_Self(0, 500, 0);
				Set_MotorSpeed(Motor[0].SetSpeed, Motor[1].SetSpeed,
							   Motor[2].SetSpeed, Motor[3].SetSpeed);
				if (Radar.Distance < 260)
					break;
			}
		}
	}
	GetInfraredState();
	
	Set_MotorSpeed(0, 0, 0, 0);

	Robot_ArmUp();

	LCD_Show_getspeed();
	
}



void FindBall_VandR_middle(u8 ball)
{

	float w = 300;
	u8 time = 1;
	float theta = BasketballRobot.ThetaD, D_theta = 0;
	

	//Choose_ball (ball);//串口向上位机发送需要找球的信息
	
	Set_MotorSpeed(0, 0, 0, 0);
	
	LCD_Show_setspeed();

	//清空视觉串口数据
	Vision.RX_STA = 0;

	//清空串口接收数据缓存
	Radar.RX_STA = 0;
	
	while (1)
	{
		while ((Vision.RX_STA & 0x8000) == 0);
		while ((Radar.RX_STA  & 0x8000) == 0);

		if (!GetVisionData())
		{
			if (time == 0)
			{
			}
			else if (time++ < 5)
			{

				Set_MotorSpeed(0, 0, 0, 0);
				continue;
			}
			else if (time != 0 )
				time = 0;
		}
		else
			time = 1;

		GetRadarData();
		
//		if (Radar.Distance < 700)
//			break;
		
//		if(time != 0)
//			foundball = 1;

		//没找到球
		if (time == 0)
		{
			D_theta = BasketballRobot.ThetaD - theta;

			if(BasketballRobot.Y >= 3.75f||fabs(BasketballRobot.X) > 2.0)//没找到球，走到中线起点横移找球
			{
				if(changdi == 0)
					RobotGoTo(-1.5, 2.25f,0);
				else
					RobotGoTo(1.5, 2.25f,0);
			}
			else
			{

				if ((D_theta >60 && D_theta < 180) || (D_theta < -180 && D_theta > -300))
				{
					//w = 300;
                    w = 350;
				}
				if ((D_theta < -60 && D_theta > -180) || (D_theta > 180 && D_theta < 300))
				{
					//w = -300;
                    w = -350;
				}
			}
			Set_MotorSpeed(w,w,w,w);

			LCD_Show_setspeed();
		}
		
		else if (Vision.Depth > 4000)
		{
			Set_MotorSpeed(0, 0, 0, 0);
		}
		else if (Vision.X > VISION_MID + 40)
		{
			GetMotorVelocity_Self(-500, 0, 0);  //-1000
			Set_MotorSpeed(Motor[0].SetSpeed, Motor[1].SetSpeed,
			               Motor[2].SetSpeed, Motor[3].SetSpeed);
		}
		else if ((Vision.X < VISION_MID - 40) )
		{
			GetMotorVelocity_Self(500, 0, 0);
			Set_MotorSpeed(Motor[0].SetSpeed, Motor[1].SetSpeed,
			               Motor[2].SetSpeed, Motor[3].SetSpeed);
		}
		else if ( Vision.Depth > 2000)
		{
			GetMotorVelocity_Self(0, 1500, 0);//1500
			Set_MotorSpeed(Motor[0].SetSpeed, Motor[1].SetSpeed,
			               Motor[2].SetSpeed, Motor[3].SetSpeed);
		}		
		else if (Vision.X < VISION_MID - 30)
		{
			GetMotorVelocity_Self(400, 0, 0);  //800
			Set_MotorSpeed(Motor[0].SetSpeed, Motor[1].SetSpeed,
			               Motor[2].SetSpeed, Motor[3].SetSpeed);
		}
		else if (Vision.X > VISION_MID + 30 )
		{
			GetMotorVelocity_Self(-400, 0, 0);
			Set_MotorSpeed(Motor[0].SetSpeed, Motor[1].SetSpeed,
			               Motor[2].SetSpeed, Motor[3].SetSpeed);
		}
		else if (Vision.Depth > 1000)
		{
			GetMotorVelocity_Self(0, 1000, 0);//1200
			Set_MotorSpeed(Motor[0].SetSpeed, Motor[1].SetSpeed,
			               Motor[2].SetSpeed, Motor[3].SetSpeed);
		}
		else if (Vision.X < VISION_MID - 15)
		{
			GetMotorVelocity_Self(150, 0, 0);  
			Set_MotorSpeed(Motor[0].SetSpeed, Motor[1].SetSpeed,
			               Motor[2].SetSpeed, Motor[3].SetSpeed);
		}
		else if (Vision.X > VISION_MID + 15 )
		{
			GetMotorVelocity_Self(-150, 0, 0);
			Set_MotorSpeed(Motor[0].SetSpeed, Motor[1].SetSpeed,
			               Motor[2].SetSpeed, Motor[3].SetSpeed);
		}
		else
			break;
			
	} 

	if (Radar.Distance > 1000)
	{
		//雷达距离过大时，按照视觉数据寻找
		while (1)
		{
			while ((Vision.RX_STA & 0x8000) == 0);

			//GetVisionData();//Self_Edit
			GetRadarData();

			if (Radar.Distance < 1000)
				break;
            GetVisionData();//Self_Edit
//			if (!GetVisionData())//为了流畅临时注释
//            {
//                vision_flag2++;
//				Set_MotorSpeed(0, 0, 0, 0);
//            }

			//先调整后直行
			//else if (Vision.X > VISION_MID + 30)//为了流畅临时注释
            if (Vision.X > VISION_MID + 30)
			{
				GetMotorVelocity_Self(-800,0, 0);
				Set_MotorSpeed(Motor[0].SetSpeed, Motor[1].SetSpeed,Motor[2].SetSpeed, Motor[3].SetSpeed);
			}
			else if ((Vision.X < VISION_MID - 30) )
			{
				GetMotorVelocity_Self(800, 0, 0);
				Set_MotorSpeed(Motor[0].SetSpeed, Motor[1].SetSpeed,
							   Motor[2].SetSpeed, Motor[3].SetSpeed);
			}			
			
			else if (Vision.Depth > 1000)
			{
				GetMotorVelocity_Self(0, 1000, 0);
				Set_MotorSpeed(Motor[0].SetSpeed, Motor[1].SetSpeed,
							   Motor[2].SetSpeed, Motor[3].SetSpeed);
			}
			
			else if (Vision.X < VISION_MID - 20)
			{
				GetMotorVelocity_Self(600,0, 0);
				Set_MotorSpeed(Motor[0].SetSpeed, Motor[1].SetSpeed,
							   Motor[2].SetSpeed, Motor[3].SetSpeed);
			}
			else if (Vision.X > VISION_MID + 20 )
			{
				GetMotorVelocity_Self(-600, 0, 0);
				Set_MotorSpeed(Motor[0].SetSpeed, Motor[1].SetSpeed,
							   Motor[2].SetSpeed, Motor[3].SetSpeed);
			}
			
			else if (Vision.Depth > 700)
			{
				GetMotorVelocity_Self(0, 700, 0);
				Set_MotorSpeed(Motor[0].SetSpeed, Motor[1].SetSpeed,Motor[2].SetSpeed, Motor[3].SetSpeed);
			}
			else
			{
				Set_MotorSpeed(0, 0, 0, 0);
				Robot_ArmDown();
				GetMotorVelocity_Self(0, 500, 0);
				Set_MotorSpeed(Motor[0].SetSpeed, Motor[1].SetSpeed,Motor[2].SetSpeed, Motor[3].SetSpeed);
				break;				
			}			
		}
	}	
	
	
	//雷达距离合适，按照雷达数据寻找，雷达1m内找球
	if (Radar.Distance <= 1000)
	{
		while (1)
		{
			while ((Radar.RX_STA & 0x8000) == 0);
			
			GetVisionData();

			if (INFRARED == 1)//如果铲到球，退出循环
				break;
			
			else if (!GetRadarData())
			{
				Set_MotorSpeed(0,0,0,0);
				continue;
			}
			else if (Radar.Angle < RADAR_MID - 10)
			{
				GetMotorVelocity_Self(-600, 0, 0);
				Set_MotorSpeed(Motor[0].SetSpeed, Motor[1].SetSpeed,
							   Motor[2].SetSpeed, Motor[3].SetSpeed);
			}
			else if (Radar.Angle > RADAR_MID + 10)
			{
				GetMotorVelocity_Self(600, 0, 0);
				Set_MotorSpeed(Motor[0].SetSpeed, Motor[1].SetSpeed,
							   Motor[2].SetSpeed, Motor[3].SetSpeed);
			}			
			else if(Radar.Distance > 800)
			{
				GetMotorVelocity_Self(0, 1000, 0);
				Set_MotorSpeed(Motor[0].SetSpeed, Motor[1].SetSpeed,
							   Motor[2].SetSpeed, Motor[3].SetSpeed);
			}
			else if (Radar.Angle < RADAR_MID - 3)
			{
				GetMotorVelocity_Self(-400, 0, 0);
				Set_MotorSpeed(Motor[0].SetSpeed, Motor[1].SetSpeed,
							   Motor[2].SetSpeed, Motor[3].SetSpeed);
			}
			else if (Radar.Angle > RADAR_MID + 3)
			{
				GetMotorVelocity_Self(400, 0, 0);
				Set_MotorSpeed(Motor[0].SetSpeed, Motor[1].SetSpeed,
							   Motor[2].SetSpeed, Motor[3].SetSpeed);
			}
			else if (Radar.Distance > 550)
			{
				GetMotorVelocity_Self(0, 800, 0);
				Set_MotorSpeed(Motor[0].SetSpeed, Motor[1].SetSpeed,
							   Motor[2].SetSpeed, Motor[3].SetSpeed);
			}
			else
			{
				Set_MotorSpeed(0, 0, 0, 0);
				Robot_ArmDown();
				GetMotorVelocity_Self(0, 500, 0);
				Set_MotorSpeed(Motor[0].SetSpeed, Motor[1].SetSpeed,
							   Motor[2].SetSpeed, Motor[3].SetSpeed);
				if (Radar.Distance < 260)
					break;
			}
		}
	}

	GetInfraredState();
	
	Set_MotorSpeed(0, 0, 0, 0);

	Robot_ArmUp();
	
	delay_ms(500);
	
	LCD_Show_setspeed();
		
}

//雷达找篮筐
void FindBasketry(void)
{
	float w = 300;
	float D_theta = 0;	
	
	Set_MotorSpeed(0,0,0,0);
	LCD_Show_getspeed();
	do{
		while((Radar.RX_STA & 0x8000) == 0);
		
		if(!GetRadarData())
		{	
			GetMotorVelocity_Self(0,1000,0);
		    Set_MotorSpeed(Motor[0].SetSpeed, Motor[1].SetSpeed,
			               Motor[2].SetSpeed, Motor[3].SetSpeed);
			continue;
		}
		LED0 = !LED0;

		if(Radar.Distance < 1500)
			continue;
		if(Radar.Distance > 4000)
		{
			D_theta = BasketballRobot.ThetaD;
			if(D_theta > 180 && D_theta < 270)
			{
				w = -600;
			}
			if(D_theta < 180 && D_theta > 0  )
			{
				w = 600;
			}
			GetMotorVelocity(0,0,w);
			Set_MotorSpeed(Motor[0].SetSpeed, Motor[1].SetSpeed,
			               Motor[2].SetSpeed, Motor[3].SetSpeed);
		}
		else if( Radar.Angle < BASKETRY_MID - 10 )
		{
			GetMotorVelocity_Self(0,0,-600);
			Set_MotorSpeed(Motor[0].SetSpeed, Motor[1].SetSpeed,
			               Motor[2].SetSpeed, Motor[3].SetSpeed);
			
			//Set_MotorSpeed(-400,-400,-400,-400);
			//逆时针旋转给负速度
		}
		else if(Radar.Angle > BASKETRY_MID + 10)
		{
			GetMotorVelocity_Self(0,0,600);
			Set_MotorSpeed(Motor[0].SetSpeed, Motor[1].SetSpeed,
			               Motor[2].SetSpeed, Motor[3].SetSpeed);
			Set_MotorSpeed(400,400,400,400);
		}
		else if(Radar.Distance > 3000)
		{
			GetMotorVelocity_Self(0,1000,0);
			Set_MotorSpeed(Motor[0].SetSpeed, Motor[1].SetSpeed,
			               Motor[2].SetSpeed, Motor[3].SetSpeed);
		}
		else if(Radar.Distance > DIS_RADAR + 100)
		{
			GetMotorVelocity_Self(0,500,0);
			Set_MotorSpeed(Motor[0].SetSpeed, Motor[1].SetSpeed,
			               Motor[2].SetSpeed, Motor[3].SetSpeed);
		}
		else if(Radar.Distance < DIS_RADAR - 100)
		{
			GetMotorVelocity_Self(0,-500,0);
			Set_MotorSpeed(Motor[0].SetSpeed, Motor[1].SetSpeed,
			               Motor[2].SetSpeed, Motor[3].SetSpeed);
		}
		else if(Radar.Angle < BASKETRY_MID - 5)
		{
			GetMotorVelocity_Self(0,0,-500);
			Set_MotorSpeed(Motor[0].SetSpeed, Motor[1].SetSpeed,
			               Motor[2].SetSpeed, Motor[3].SetSpeed);
		}
		else if(Radar.Angle > BASKETRY_MID + 5)
		{
			GetMotorVelocity_Self(0,0,500);
			Set_MotorSpeed(Motor[0].SetSpeed, Motor[1].SetSpeed,
			               Motor[2].SetSpeed, Motor[3].SetSpeed);
		}
		else if(Radar.Distance > DIS_RADAR + 50)
		{
			GetMotorVelocity_Self(0,300,0);
			Set_MotorSpeed(Motor[0].SetSpeed, Motor[1].SetSpeed,
			               Motor[2].SetSpeed, Motor[3].SetSpeed);
		}
		else if(Radar.Distance < DIS_RADAR - 50)
		{
			GetMotorVelocity_Self(0,-300,0);
			Set_MotorSpeed(Motor[0].SetSpeed, Motor[1].SetSpeed,
			               Motor[2].SetSpeed, Motor[3].SetSpeed);
		}
		
		else if (Radar.Angle < BASKETRY_MID - 2)
		{
			GetMotorVelocity_Self(0, 0, -200);
			Set_MotorSpeed(Motor[0].SetSpeed, Motor[1].SetSpeed,
			               Motor[2].SetSpeed, Motor[3].SetSpeed);
		}
		else if (Radar.Angle > BASKETRY_MID + 2)
		{
			GetMotorVelocity_Self(0, 0, 200); 
			Set_MotorSpeed(Motor[0].SetSpeed, Motor[1].SetSpeed,
			               Motor[2].SetSpeed, Motor[3].SetSpeed);
		}
		
		else if (Radar.Distance > DIS_RADAR + 20)
		{
			GetMotorVelocity_Self(0, 200, 0);
			Set_MotorSpeed(Motor[0].SetSpeed, Motor[1].SetSpeed,
			               Motor[2].SetSpeed, Motor[3].SetSpeed);
		}
		else if (Radar.Distance < DIS_RADAR - 20)
		{
			GetMotorVelocity_Self(0, -200, 0);
			Set_MotorSpeed(Motor[0].SetSpeed, Motor[1].SetSpeed,
			               Motor[2].SetSpeed, Motor[3].SetSpeed);
		}
		
		else if (Radar.Distance > DIS_RADAR + 10)
		{
			GetMotorVelocity_Self(0, 100, 0);
			Set_MotorSpeed(Motor[0].SetSpeed, Motor[1].SetSpeed,
			               Motor[2].SetSpeed, Motor[3].SetSpeed);
		}
		else if (Radar.Distance < DIS_RADAR - 10)
		{
			GetMotorVelocity_Self(0, -100, 0);
			Set_MotorSpeed(Motor[0].SetSpeed, Motor[1].SetSpeed,
			               Motor[2].SetSpeed, Motor[3].SetSpeed);
		}		
		else if (Radar.Angle < BASKETRY_MID - 1)
		{
			GetMotorVelocity_Self(0, 0, -100); 
			Set_MotorSpeed(Motor[0].SetSpeed, Motor[1].SetSpeed,
			               Motor[2].SetSpeed, Motor[3].SetSpeed);
		}
		else if (Radar.Angle > BASKETRY_MID + 1)
		{
			GetMotorVelocity_Self(0, 0, 100); 
			Set_MotorSpeed(Motor[0].SetSpeed, Motor[1].SetSpeed,
			               Motor[2].SetSpeed, Motor[3].SetSpeed);
		}		
		
		
		else 
		{
			Set_MotorSpeed(0,0,0,0);
			Robot_ArmDown();
		    break;
		}
	}while(1);
	
}

//视觉回位
void GoBack_Vision(u8 ball)
{
	float w = 200;
	
	u8 time = 1;
	
	float theta = BasketballRobot.ThetaR,D_theta = 0;
	
	//发a给视觉调用回位代码
	FindFrame();
	delay_ms(100);
	FindFrame();
	delay_ms(100);
	FindFrame();
	delay_ms(100);
	
	Set_MotorSpeed(0,0,0,0);
	
	LCD_Show_getspeed();
	
	USART1_RX_STA=0;
	do{
		//等待数据接收完成
		while((Vision.RX_STA & 0x8000) == 0);
		
		//所得数据无效
		if(!GetVisionData())
		{	
			if(time == 0);
				
			//尝试五次
			else if(time++ <5)
			{				
				Set_MotorSpeed(0,0,0,0);
				continue;
			}
			//尝试五次后仍未找到框
			else if(time !=0)
				time = 0;
		}
		//数据有效
		else
			time = 1;
		
		//没找到框,自转
		if(time == 0)
		{
			D_theta = BasketballRobot.ThetaR - theta;
			if((D_theta > PI/6.0f && D_theta < PI) || (D_theta < -PI && D_theta > -PI*11.0f/6.0f))
			{
				w = -600;
			}
			if((D_theta < -PI/6.0f && D_theta > -PI) || (D_theta > PI && D_theta < PI*11.0f/6.0f))
			{
				w = 600;
			}
			GetMotorVelocity(0,0,w);
			Set_MotorSpeed(Motor[0].SetSpeed, Motor[1].SetSpeed,
			               Motor[2].SetSpeed, Motor[3].SetSpeed);
			
			LCD_Show_getspeed();

		}
		
		//无效数据
		else if(Vision.Depth > 4000)
		{
			GetMotorVelocity(0,0,0);
			Set_MotorSpeed(Motor[0].SetSpeed, Motor[1].SetSpeed,
			               Motor[2].SetSpeed, Motor[3].SetSpeed);
		}
		
		else if((Vision.X < VISION_MID - 30) && Vision.Depth > 1300)
		{
			GetMotorVelocity_Self(-300,600,0);
			Set_MotorSpeed(Motor[0].SetSpeed, Motor[1].SetSpeed,
			               Motor[2].SetSpeed, Motor[3].SetSpeed);
		}
		else if((Vision.X > VISION_MID + 30) && Vision.Depth > 1300)
		{
			GetMotorVelocity_Self(300,600,0);
			Set_MotorSpeed(Motor[0].SetSpeed, Motor[1].SetSpeed,
			               Motor[2].SetSpeed, Motor[3].SetSpeed);
		}
		else if(Vision.Depth > 1300)
		{
			GetMotorVelocity_Self(0,600,0);
			Set_MotorSpeed(Motor[0].SetSpeed, Motor[1].SetSpeed,
			               Motor[2].SetSpeed, Motor[3].SetSpeed);
		}
		else if((Vision.X< VISION_MID - 20) && Vision.Depth > 700)
		{
			GetMotorVelocity_Self(-200,400,0);
			Set_MotorSpeed(Motor[0].SetSpeed, Motor[1].SetSpeed,
			               Motor[2].SetSpeed, Motor[3].SetSpeed);
		}
		else if((Vision.X > VISION_MID + 20) && (Vision.Depth > 700))
		{
			GetMotorVelocity_Self(200,400,0);
			Set_MotorSpeed(Motor[0].SetSpeed, Motor[1].SetSpeed,
			               Motor[2].SetSpeed, Motor[3].SetSpeed);
		}
		else if(Vision.Depth > 700)
		{
			GetMotorVelocity_Self(0,400,0);
			Set_MotorSpeed(Motor[0].SetSpeed, Motor[1].SetSpeed,
			               Motor[2].SetSpeed, Motor[3].SetSpeed);
		}
		else if(Vision.X < VISION_MID - 30)
		{
			GetMotorVelocity_Self(-300,0,0);
			Set_MotorSpeed(Motor[0].SetSpeed, Motor[1].SetSpeed,
			               Motor[2].SetSpeed, Motor[3].SetSpeed);
		}
		else if(Vision.X > VISION_MID + 30)
		{
			GetMotorVelocity_Self(300,0,0);
			Set_MotorSpeed(Motor[0].SetSpeed, Motor[1].SetSpeed,
			               Motor[2].SetSpeed, Motor[3].SetSpeed);
		}
		else if(Vision.X <= VISION_MID + 30 && Vision.X > VISION_MID + 10)
		{
			GetMotorVelocity_Self(200,0,0);
			Set_MotorSpeed(Motor[0].SetSpeed, Motor[1].SetSpeed,
			               Motor[2].SetSpeed, Motor[3].SetSpeed);
		}
		else if(Vision.X >= VISION_MID - 30 && Vision.X < VISION_MID - 10)
		{
			GetMotorVelocity_Self(-200,0,0);
			Set_MotorSpeed(Motor[0].SetSpeed, Motor[1].SetSpeed,
			               Motor[2].SetSpeed, Motor[3].SetSpeed);
		}
		else 
		{
				Set_MotorSpeed(0,0,0,0);
				Robot_ArmDown();
				GetMotorVelocity_Self(0,1000,0);
				Set_MotorSpeed(Motor[0].SetSpeed, Motor[1].SetSpeed,
			                   Motor[2].SetSpeed, Motor[3].SetSpeed);
				break;
			
		}
	}while(1);
	
}

void FindBall_VandR_sanfenxian_VisionFirst(u8 ball)//Self_Edit视觉优先找球
{
    float w = 200;

	u8 time = 1;

	float theta = BasketballRobot.ThetaD, D_theta = 0;

	Choose_ball (ball);//串口向上位机发送需要找球的信息

	Set_MotorSpeed(0, 0, 0, 0);

	LCD_Show_getspeed();
    
    USART1_RX_STA = 0;

	USART3_RX_STA = 0;

	Vision.RX_STA = 0;
    
    Radar.RX_STA  = 0;
    
	do
	{
		//等待数据接收完成
		while ((Vision.RX_STA & 0x8000) == 0)
			;

		//所得数据无效
		if (!GetVisionData())
		{
			if (time == 0)
				;

			//尝试五次
			else if (time++ < 5)
			{
				//Set_MotorSpeed(0,0,0,0);
				continue;
			}
			//尝试五次后仍未找到球
			else if (time != 0)
				time = 0;
		}
		//数据有效
		else
			time = 1;

		//没找到球,自转
        if (time == 0)
		{
			D_theta = BasketballRobot.ThetaD - theta;
			if ((D_theta > 60 && D_theta < 180) || (D_theta < -180 && D_theta > -300))
			{
				w = 300;
			}
			if ((D_theta < -60 && D_theta > -180) || (D_theta > 180 && D_theta < 300))
			{
				w = -300;
			}
			Set_MotorSpeed(w,w,w,w);
			
			LCD_Show_getspeed();
		}

		//无效数据
		else if (Vision.Depth > 4000)
		{
			GetMotorVelocity(0, 0, 0);
			Set_MotorSpeed(Motor[0].SetSpeed, Motor[1].SetSpeed,
			               Motor[2].SetSpeed, Motor[3].SetSpeed);
		}
		else if (Vision.X < VISION_MID - 20)
		{
			GetMotorVelocity_Self(600, 0, 0); //原来400
			Set_MotorSpeed(Motor[0].SetSpeed, Motor[1].SetSpeed,
			               Motor[2].SetSpeed, Motor[3].SetSpeed);
		}
		else if (Vision.X > VISION_MID + 20)
		{
			GetMotorVelocity_Self(-600, 0, 0); //原来400
			Set_MotorSpeed(Motor[0].SetSpeed, Motor[1].SetSpeed,
			               Motor[2].SetSpeed, Motor[3].SetSpeed);
		}
        else if (Vision.Depth > 1300)
		{
			GetMotorVelocity_Self(0, 1000, 0);//原800
			Set_MotorSpeed(Motor[0].SetSpeed, Motor[1].SetSpeed,
			               Motor[2].SetSpeed, Motor[3].SetSpeed);
		}
		else if (Vision.X < VISION_MID - 30)
		{
			GetMotorVelocity_Self(600, 0, 0);//原来400
			Set_MotorSpeed(Motor[0].SetSpeed, Motor[1].SetSpeed,
			               Motor[2].SetSpeed, Motor[3].SetSpeed);

		}
		else if (Vision.X > VISION_MID + 30)
		{
			GetMotorVelocity_Self(-600, 0, 0);//原来400
			Set_MotorSpeed(Motor[0].SetSpeed, Motor[1].SetSpeed,
			               Motor[2].SetSpeed, Motor[3].SetSpeed);
		}
		else if (Vision.Depth > 1000)
		{
			GetMotorVelocity_Self(0, 800, 0);//原700
			Set_MotorSpeed(Motor[0].SetSpeed, Motor[1].SetSpeed,
			               Motor[2].SetSpeed, Motor[3].SetSpeed);
		}
		else if (Vision.X <= VISION_MID + 30 && Vision.X > VISION_MID + 10)
		{
			GetMotorVelocity_Self(-300, 0, 0);//yuan 250
			Set_MotorSpeed(Motor[0].SetSpeed, Motor[1].SetSpeed,
			               Motor[2].SetSpeed, Motor[3].SetSpeed);
		}
		else if (Vision.X >= VISION_MID - 30 && Vision.X < VISION_MID - 10)
		{
			GetMotorVelocity_Self(300, 0, 0);//yuan 250
			Set_MotorSpeed(Motor[0].SetSpeed, Motor[1].SetSpeed,
			               Motor[2].SetSpeed, Motor[3].SetSpeed);
		}
        else if (Vision.Depth > 900)//Self_Edit
		{
			GetMotorVelocity_Self(0, 700, 0);//yuan 600
			Set_MotorSpeed(Motor[0].SetSpeed, Motor[1].SetSpeed,
			               Motor[2].SetSpeed, Motor[3].SetSpeed);
        }
		else
		{
			Set_MotorSpeed(0, 0, 0, 0);
			Robot_ArmDown();
			GetMotorVelocity_Self(0, 600, 0);
			Set_MotorSpeed(Motor[0].SetSpeed, Motor[1].SetSpeed,
			               Motor[2].SetSpeed, Motor[3].SetSpeed);
			break;
		}
	} while (1);
    
    GetRadarData();
    
    while (1)
    {
        while ((Radar.RX_STA & 0x8000) == 0);
        
        //GetVisionData();
        
        if (INFRARED == 1)
            break;			
        else if (!GetRadarData())
        {
            Set_MotorSpeed(0,0,0,0);
            continue;
        }
        else if(Radar.Distance > 1000)
        {
            GetMotorVelocity_Self(0, 1000, 0);
            Set_MotorSpeed(Motor[0].SetSpeed, Motor[1].SetSpeed,
                           Motor[2].SetSpeed, Motor[3].SetSpeed);
        }
        else if (Radar.Angle < RADAR_MID - 10)
        {
            GetMotorVelocity_Self(-600, 0, 0);
            Set_MotorSpeed(Motor[0].SetSpeed, Motor[1].SetSpeed,
                           Motor[2].SetSpeed, Motor[3].SetSpeed);
        }
        else if (Radar.Angle > RADAR_MID + 10)
        {
            GetMotorVelocity_Self(600, 0, 0);
            Set_MotorSpeed(Motor[0].SetSpeed, Motor[1].SetSpeed,
                           Motor[2].SetSpeed, Motor[3].SetSpeed);
        }			
        else if(Radar.Distance > 800)
        {
            GetMotorVelocity_Self(0, 1000, 0);
            Set_MotorSpeed(Motor[0].SetSpeed, Motor[1].SetSpeed,
                           Motor[2].SetSpeed, Motor[3].SetSpeed);
        }
        else if (Radar.Angle < RADAR_MID - 3)
        {
            GetMotorVelocity_Self(-400, 0, 0);
            Set_MotorSpeed(Motor[0].SetSpeed, Motor[1].SetSpeed,
                           Motor[2].SetSpeed, Motor[3].SetSpeed);
        }
        else if (Radar.Angle > RADAR_MID + 3)
        {
            GetMotorVelocity_Self(400, 0, 0);
            Set_MotorSpeed(Motor[0].SetSpeed, Motor[1].SetSpeed,
                           Motor[2].SetSpeed, Motor[3].SetSpeed);
        }
        else if (Radar.Distance > 550)
        {
            GetMotorVelocity_Self(0, 800, 0);
            Set_MotorSpeed(Motor[0].SetSpeed, Motor[1].SetSpeed,
                           Motor[2].SetSpeed, Motor[3].SetSpeed);
        }
        else
        {
            Set_MotorSpeed(0, 0, 0, 0);
            //Robot_ArmDown();
            GetMotorVelocity_Self(0, 500, 0);
            Set_MotorSpeed(Motor[0].SetSpeed, Motor[1].SetSpeed,
                           Motor[2].SetSpeed, Motor[3].SetSpeed);
            if (Radar.Distance < 260)
                break;
        }
    }

	GetInfraredState();

	Set_MotorSpeed(0, 0, 0, 0);

	Robot_ArmUp();
	LCD_Show_getspeed();
}

void FindBall_VandR_VisionMiddle(u8 ball)//平移对正后前进
{
    float w = 200;

	u8 time = 1;

	float theta = BasketballRobot.ThetaD, D_theta = 0;

	Choose_ball (ball);//串口向上位机发送需要找球的信息

	Set_MotorSpeed(0, 0, 0, 0);

	LCD_Show_getspeed();
    
    USART1_RX_STA = 0;

	USART3_RX_STA = 0;

	Vision.RX_STA = 0;
    
    Radar.RX_STA  = 0;
    
	do
	{
		//等待数据接收完成
		while ((Vision.RX_STA & 0x8000) == 0)
			;

		//所得数据无效
		if (!GetVisionData())
		{
			if (time == 0)
				;

			//尝试五次
			else if (time++ < 5)
			{
				//Set_MotorSpeed(0,0,0,0);
				continue;
			}
			//尝试五次后仍未找到球
			else if (time != 0)
				time = 0;
		}
		//数据有效
		else
			time = 1;

		//没找到球,自转
        if (time == 0)
        {
            D_theta = BasketballRobot.ThetaD - theta;
            if ((D_theta > 60 && D_theta < 180) || (D_theta < -180 && D_theta > -300))
            {
                w = 300;
            }
            if ((D_theta < -60 && D_theta > -180) || (D_theta > 180 && D_theta < 300))
            {
                w = -300;
            }
            Set_MotorSpeed(w,w,w,w);
            
            LCD_Show_getspeed();
        }

        //无效数据
        else if (Vision.Depth > 4000)
        {
            GetMotorVelocity(0, 0, 0);
            Set_MotorSpeed(Motor[0].SetSpeed, Motor[1].SetSpeed,
                           Motor[2].SetSpeed, Motor[3].SetSpeed);
        }
        
        else if (Vision.X < VISION_MID - 30)
        {
            GetMotorVelocity_Self(600, 0, 0);//原来400
            Set_MotorSpeed(Motor[0].SetSpeed, Motor[1].SetSpeed,
                           Motor[2].SetSpeed, Motor[3].SetSpeed);

        }
        
        else if (Vision.X > VISION_MID + 30)
        {
            GetMotorVelocity_Self(-600, 0, 0);//原来400
            Set_MotorSpeed(Motor[0].SetSpeed, Motor[1].SetSpeed,
                           Motor[2].SetSpeed, Motor[3].SetSpeed);
        }
        
        else if (Vision.X < VISION_MID - 10)
        {
            GetMotorVelocity_Self(400, 0, 0);//原来400
            Set_MotorSpeed(Motor[0].SetSpeed, Motor[1].SetSpeed,
                           Motor[2].SetSpeed, Motor[3].SetSpeed);

        }
        
        else if (Vision.X > VISION_MID + 10)
        {
            GetMotorVelocity_Self(-400, 0, 0);//原来400
            Set_MotorSpeed(Motor[0].SetSpeed, Motor[1].SetSpeed,
                           Motor[2].SetSpeed, Motor[3].SetSpeed);
        }
        
        else if (Vision.Depth > 1200)
        {
            GetMotorVelocity_Self(0, 1300, 0);//yuan 600
            Set_MotorSpeed(Motor[0].SetSpeed, Motor[1].SetSpeed,
                           Motor[2].SetSpeed, Motor[3].SetSpeed);
        }
        
        else if (Vision.Depth > 900)
        {
            GetMotorVelocity_Self(0, 700, 0);//yuan 600
            Set_MotorSpeed(Motor[0].SetSpeed, Motor[1].SetSpeed,
                           Motor[2].SetSpeed, Motor[3].SetSpeed);
        }
        
        else
        {
            Set_MotorSpeed(0, 0, 0, 0);
            Robot_ArmDown();
            GetMotorVelocity_Self(0, 600, 0);
            Set_MotorSpeed(Motor[0].SetSpeed, Motor[1].SetSpeed,
                           Motor[2].SetSpeed, Motor[3].SetSpeed);
            break;
        }
    } while (1);
    
    GetRadarData();
    
    while (1)
    {
        while ((Radar.RX_STA & 0x8000) == 0);
        
        //GetVisionData();
        
        if (INFRARED == 1)
            break;			
        else if (!GetRadarData())
        {
            Set_MotorSpeed(0,0,0,0);
            continue;
        }
        else if(Radar.Distance > 1000)
        {
            GetMotorVelocity_Self(0, 1000, 0);
            Set_MotorSpeed(Motor[0].SetSpeed, Motor[1].SetSpeed,
                           Motor[2].SetSpeed, Motor[3].SetSpeed);
        }
        else if (Radar.Angle < RADAR_MID - 10)
        {
            GetMotorVelocity_Self(-600, 0, 0);
            Set_MotorSpeed(Motor[0].SetSpeed, Motor[1].SetSpeed,
                           Motor[2].SetSpeed, Motor[3].SetSpeed);
        }
        else if (Radar.Angle > RADAR_MID + 10)
        {
            GetMotorVelocity_Self(600, 0, 0);
            Set_MotorSpeed(Motor[0].SetSpeed, Motor[1].SetSpeed,
                           Motor[2].SetSpeed, Motor[3].SetSpeed);
        }			
        else if(Radar.Distance > 800)
        {
            GetMotorVelocity_Self(0, 1000, 0);
            Set_MotorSpeed(Motor[0].SetSpeed, Motor[1].SetSpeed,
                           Motor[2].SetSpeed, Motor[3].SetSpeed);
        }
        else if (Radar.Angle < RADAR_MID - 3)
        {
            GetMotorVelocity_Self(-400, 0, 0);
            Set_MotorSpeed(Motor[0].SetSpeed, Motor[1].SetSpeed,
                           Motor[2].SetSpeed, Motor[3].SetSpeed);
        }
        else if (Radar.Angle > RADAR_MID + 3)
        {
            GetMotorVelocity_Self(400, 0, 0);
            Set_MotorSpeed(Motor[0].SetSpeed, Motor[1].SetSpeed,
                           Motor[2].SetSpeed, Motor[3].SetSpeed);
        }
        else if (Radar.Distance > 550)
        {
            GetMotorVelocity_Self(0, 800, 0);
            Set_MotorSpeed(Motor[0].SetSpeed, Motor[1].SetSpeed,
                           Motor[2].SetSpeed, Motor[3].SetSpeed);
        }
        else
        {
            Set_MotorSpeed(0, 0, 0, 0);
            //Robot_ArmDown();
            GetMotorVelocity_Self(0, 500, 0);
            Set_MotorSpeed(Motor[0].SetSpeed, Motor[1].SetSpeed,
                           Motor[2].SetSpeed, Motor[3].SetSpeed);
            if (Radar.Distance < 260)
                break;
        }
    }

	GetInfraredState();

	Set_MotorSpeed(0, 0, 0, 0);

	Robot_ArmUp();
	LCD_Show_getspeed();
}
