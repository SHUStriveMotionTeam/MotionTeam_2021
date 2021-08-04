#include "find_ball.h"
#include "remote.h"

u8 ball;    
float test;

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

void FindFrame(void)//�ҿ�
{
	ball = 'a';
	HAL_UART_Transmit(&huart1,&ball,1,1000);
}

//����ѡ��
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

u8 MoveOfFindingBallByVision()
{
	float x, w;
	if ( (Radar.Distance < 1000) && (Vision.Depth < 1000) )
		return 0;	
	else
	{
		x = (float)Vision.Depth/1.8 + 500;
		w = -((float)Vision.X-VISION_MID)*4;
		if((w < 20)&&(w > -20))
			w = 0;
		GetMotorVelocity_Self(0, x, w);
		Set_MotorSpeed(Motor[0].SetSpeed, Motor[1].SetSpeed,
					   Motor[2].SetSpeed, Motor[3].SetSpeed);
		return 1;	
	}	
//	else if (Vision.Depth > 4000)
//	{
//		Set_MotorSpeed(0, 0, 0, 0);
//		return 1;
//	}
//	else if (Vision.X > VISION_MID + 40)
//	{
//		GetMotorVelocity_Self(0, 0, -600);
//		Set_MotorSpeed(Motor[0].SetSpeed, Motor[1].SetSpeed,
//					   Motor[2].SetSpeed, Motor[3].SetSpeed);
//		return 1;
//	}
//	else if (Vision.X < VISION_MID - 40)
//	{
//		GetMotorVelocity_Self(0, 0, 600);
//		Set_MotorSpeed(Motor[0].SetSpeed, Motor[1].SetSpeed,
//					   Motor[2].SetSpeed, Motor[3].SetSpeed);
//		return 1;
//	}
//	else if (Vision.Depth > 2000)
//	{
//		GetMotorVelocity_Self(0, 1500, 0);
//		Set_MotorSpeed(Motor[0].SetSpeed, Motor[1].SetSpeed,
//					   Motor[2].SetSpeed, Motor[3].SetSpeed);
//		return 1;
//	}		
//	else if (Vision.X < VISION_MID - 30)
//	{
//		GetMotorVelocity_Self(0,0,500);
//		Set_MotorSpeed(Motor[0].SetSpeed, Motor[1].SetSpeed,
//					   Motor[2].SetSpeed, Motor[3].SetSpeed);
//		return 1;
//	}
//	else if (Vision.X > VISION_MID + 30 )
//	{
//		GetMotorVelocity_Self(0, 0, -500);
//		Set_MotorSpeed(Motor[0].SetSpeed, Motor[1].SetSpeed,
//					   Motor[2].SetSpeed, Motor[3].SetSpeed);
//		return 1;
//	}
//	else if (Vision.Depth > 1000)
//	{
//		GetMotorVelocity_Self(0, 1000, 0);
//		Set_MotorSpeed(Motor[0].SetSpeed, Motor[1].SetSpeed,
//					   Motor[2].SetSpeed, Motor[3].SetSpeed);
//		return 1;
//	}
//	else if (Vision.X < VISION_MID - 15)//SELF_EDIT
//	{
//		GetMotorVelocity_Self(0,0,400);
//		Set_MotorSpeed(Motor[0].SetSpeed, Motor[1].SetSpeed,
//					   Motor[2].SetSpeed, Motor[3].SetSpeed);
//		return 1;
//	}
//	else if (Vision.X > VISION_MID + 15 )//SELF_EDIT
//	{
//		GetMotorVelocity_Self(0, 0, -400);
//		Set_MotorSpeed(Motor[0].SetSpeed, Motor[1].SetSpeed,
//					   Motor[2].SetSpeed, Motor[3].SetSpeed);
//		return 1;
//	}	
}

u8 MoveOfFindingBallByRadar()
{
	if (INFRARED == 1 || Radar.Distance < 150)
		return 0;	
	else if (!GetRadarData())
	{
		Set_MotorSpeed(0,0,0,0);
		return 1;
	}
	else if (Radar.Angle < RADAR_MID - 10)
	{
		GetMotorVelocity_Self(-600, 0, 0);
		Set_MotorSpeed(Motor[0].SetSpeed, Motor[1].SetSpeed,
					   Motor[2].SetSpeed, Motor[3].SetSpeed);
		return 1;
	}
	else if (Radar.Angle > RADAR_MID + 10)
	{
		GetMotorVelocity_Self(600, 0, 0);
		Set_MotorSpeed(Motor[0].SetSpeed, Motor[1].SetSpeed,
					   Motor[2].SetSpeed, Motor[3].SetSpeed);
		return 1;
	}			
	else if(Radar.Distance > 800)
	{
		GetMotorVelocity_Self(0, 1000, 0);
		Set_MotorSpeed(Motor[0].SetSpeed, Motor[1].SetSpeed,
					   Motor[2].SetSpeed, Motor[3].SetSpeed);
		return 1;
	}
	else if (Radar.Angle < RADAR_MID - 3)
	{
		GetMotorVelocity_Self(-400, 0, 0);
		Set_MotorSpeed(Motor[0].SetSpeed, Motor[1].SetSpeed,
					   Motor[2].SetSpeed, Motor[3].SetSpeed);
		return 1;
	}
	else if (Radar.Angle > RADAR_MID + 3)
	{
		GetMotorVelocity_Self(400, 0, 0);
		Set_MotorSpeed(Motor[0].SetSpeed, Motor[1].SetSpeed,
					   Motor[2].SetSpeed, Motor[3].SetSpeed);
		return 1;
	}
	else if (Radar.Distance > 550)
	{
		GetMotorVelocity_Self(0, 800, 0);
		Set_MotorSpeed(Motor[0].SetSpeed, Motor[1].SetSpeed,
					   Motor[2].SetSpeed, Motor[3].SetSpeed);
		return 1;
	}
	else
	{
		Set_MotorSpeed(0, 0, 0, 0);
		Robot_ArmDown();
		GetMotorVelocity_Self(0, 500, 0);
		Set_MotorSpeed(Motor[0].SetSpeed, Motor[1].SetSpeed,
					   Motor[2].SetSpeed, Motor[3].SetSpeed);
		return 1;
	}
}

void RotateOnItsOwnAxis(float theta)
{
    float D_theta;
    static int state = 1;
    switch(state)
    {
        case 1:
            while(1)
            {
                D_theta = BasketballRobot.ThetaR - theta;
                test = D_theta;
                GetMotorVelocity(0, 0, 1500);
                Set_MotorSpeed(Motor[0].SetSpeed, Motor[1].SetSpeed,
                               Motor[2].SetSpeed, Motor[3].SetSpeed);
                LCD_Show_setspeed();
                if ((D_theta < -PI / 6.0f && D_theta > -PI) || (D_theta > PI && D_theta < PI * 11.0f / 6.0f))
                {
                    Set_MotorSpeed(0,0,0,0);
                    LCD_Show_setspeed();
                    state = -state;
                    delay_ms(800);
                    return;
                }
            }
        case -1:
            while(1)
            {
                D_theta = BasketballRobot.ThetaR - theta;
                test = D_theta;
                GetMotorVelocity(0, 0, -1500);
                Set_MotorSpeed(Motor[0].SetSpeed, Motor[1].SetSpeed,
                               Motor[2].SetSpeed, Motor[3].SetSpeed);
                LCD_Show_setspeed();
                if ((D_theta > PI / 6.0f && D_theta < PI) || (D_theta < -PI && D_theta > -PI * 11.0f / 6.0f))
                {
                    Set_MotorSpeed(0,0,0,0);
                    LCD_Show_setspeed();
                    state = -state;
                    delay_ms(800);
                    return;
                }
            }
    }
    

//	if ((D_theta > PI / 6.0f && D_theta < PI) || (D_theta < -PI && D_theta > -PI * 11.0f / 6.0f))
//	{
//		w = -600;
//	}
//	if ((D_theta < -PI / 6.0f && D_theta > -PI) || (D_theta > PI && D_theta < PI * 11.0f / 6.0f))
//	{
//		w = 600;
//	}
//	GetMotorVelocity(0, 0, w);
//	Set_MotorSpeed(Motor[0].SetSpeed, Motor[1].SetSpeed,
//				   Motor[2].SetSpeed, Motor[3].SetSpeed);
//	LCD_Show_setspeed();
	
}

//�Ӿ�����
//����4������
void FindBall_vision(u8 ball)
{
	float w = 200;

	u8 time = 1;

	float theta = BasketballRobot.ThetaR, D_theta = 0;

	Choose_ball (ball);//��������λ��������Ҫ�������Ϣ

	Set_MotorSpeed(0, 0, 0, 0);

	LCD_Show_getspeed();

	Vision.RX_STA = 0;
	do
	{
		//�ȴ����ݽ������
		while ((Vision.RX_STA & 0x8000) == 0)
			;

		//����������Ч
		if (!GetVisionData())
		{
			if (time == 0)
				;

			//�������
			else if (time++ < 5)
			{
				//Set_MotorSpeed(0,0,0,0);
				continue;
			}
			//������κ���δ�ҵ���
			else if (time != 0)
				time = 0;
		}
		//������Ч
		else
			time = 1;

		//û�ҵ���,��ת
		if (time == 0)
			RotateOnItsOwnAxis(theta);

		//��Ч����
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
			GetMotorVelocity_Self(200, 400, 0); //ԭ��-40 0 0
			Set_MotorSpeed(Motor[0].SetSpeed, Motor[1].SetSpeed,
			               Motor[2].SetSpeed, Motor[3].SetSpeed);
		}
		else if ((Vision.X > VISION_MID + 20) && (Vision.Depth > 1200))
		{
			GetMotorVelocity_Self(-200, 400, 0); //ԭ��4 0 0
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

//�����״�����
//����������ɫ
//����3m����
void FindBall_radar(void)
{
	u8 radar_flag;
	float theta = BasketballRobot.ThetaD;

	Set_MotorSpeed(0, 0, 0, 0);
	LCD_Show_getspeed();
	while (1)
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
			RotateOnItsOwnAxis(theta);
		while ((Radar.RX_STA & 0x8000) == 0);
		
		//GetVisionData();

//		if (INFRARED == 1)//����������˳�ѭ��
//			break;
		
		//else  
		if (!GetRadarData())
		{
			Set_MotorSpeed(0,0,0,0);
			continue;
		}
		else
		{
			radar_flag = MoveOfFindingBallByRadar();
			if (radar_flag == 0)
				break;
		}
		LCD_Show_setspeed();
	}
	GetInfraredState();
	Set_MotorSpeed(0, 0, 0, 0);
	Robot_ArmUp();
	LCD_Show_getspeed();
}

//�Ӿ����״�������
//����4m����
void FindBall_VandR(u8 ball)
{
	u8 vision_flag = 1;
	u8 radar_flag = 1;
	u8 rotate_flag = 1;
	u8 time = 1;
	float theta = BasketballRobot.ThetaR;
	
	Choose_ball (ball);//��������λ��������Ҫ�������Ϣ
	
	Set_MotorSpeed(0, 0, 0, 0);
	
	LCD_Show_getspeed();

	//����Ӿ���������
	USART1_RX_STA = 0;

	//��մ��ڽ������ݻ���
	USART3_RX_STA = 0;

	while (1)//�Ӿ��ߵ�1m
	{
		while ((Vision.RX_STA & 0x8000) == 0);
		//while ((Radar.RX_STA & 0x8000) == 0);
		
		if(!GetVisionData())
		{	
			if(time == 0);
				
			//�������
			else if(time++ <5)
			{				
				Set_MotorSpeed(0,0,0,0);
				continue;
			}
			//������κ���δ�ҵ���
			else if(time != 0)
				time = 0;
		}
		//������Ч
		else
			time = 1;
		
		GetRadarData();
		
		if (time == 0 && rotate_flag == 1)
			RotateOnItsOwnAxis(theta);//û�ҵ���,��ת
		else
		{
			rotate_flag = 0;
			vision_flag = MoveOfFindingBallByVision();
			if (vision_flag == 0)
				break;
		}
	} 
	
	//�״������ʣ������״�����Ѱ�ң��״�1m������
	if (Radar.Distance < 1000)
	{
		while (1)
		{
			while ((Radar.RX_STA & 0x8000) == 0);
			radar_flag = MoveOfFindingBallByRadar();
			if (radar_flag == 0)
				break;
		}
	}
    GetInfraredState();
	
	Set_MotorSpeed(0, 0, 0, 0);

	Robot_ArmUp();

	LCD_Show_getspeed();
	
}


//�Ӿ����״�������
//����4m����
void FindBall_VandR_sanfenxian(u8 ball)
{
	u8 vision_flag;
	u8 radar_flag;
	u8 time = 1;
	float theta = BasketballRobot.ThetaD;
	
	Choose_ball (ball);//��������λ��������Ҫ�������Ϣ
	
	Set_MotorSpeed(0, 0, 0, 0);
	
	LCD_Show_getspeed();

	//����Ӿ���������
	USART1_RX_STA = 0;

	//��մ��ڽ������ݻ���
	USART3_RX_STA = 0;
	
	while (1)//�Ӿ��ߵ�1m
	{
		while ((Vision.RX_STA & 0x8000) == 0);
		while ((Radar.RX_STA & 0x8000) == 0);
		
//		if (Radar.Distance < 600)
//			break;

		//û�ҵ���,��ת
		if(!GetVisionData())
		{	
			if(time == 0);
				
			//�������
			else if(time++ <5)
			{				
				Set_MotorSpeed(0,0,0,0);
				continue;
			}
			//������κ���δ�ҵ���
			else if(time !=0)
				time = 0;
		}
		//������Ч
		else
			time = 1;
		
		if (time == 0)
			RotateOnItsOwnAxis(theta);
		else
		{
			vision_flag = MoveOfFindingBallByVision();
			if (vision_flag == 0)
				break;
		}
	}

	//�״������ʣ������״�����Ѱ�ң��״�1m������
	if (Radar.Distance <= 1000)
	{
		while (1)
		{
			while ((Radar.RX_STA & 0x8000) == 0);
			radar_flag = MoveOfFindingBallByRadar();
			if (radar_flag == 0)
				break;
		}
	}
	
	GetInfraredState();
	
	Set_MotorSpeed(0, 0, 0, 0);

	Robot_ArmUp();

	LCD_Show_getspeed();
	
}

void FindBall_VandR_middle(u8 ball)
{
	u8 vision_flag;
	u8 radar_flag;
	float theta = BasketballRobot.ThetaD, D_theta;
	
	Choose_ball (ball);//��������λ��������Ҫ�������Ϣ
	
	Set_MotorSpeed(0, 0, 0, 0);
	
	LCD_Show_setspeed();

	//����Ӿ���������
	Vision.RX_STA = 0;

	//��մ��ڽ������ݻ���
	Radar.RX_STA = 0;
	
	while (1)
	{
		while ((Vision.RX_STA & 0x8000) == 0);
		while ((Radar.RX_STA  & 0x8000) == 0);

		GetRadarData();
		
//		if (Radar.Distance < 700)
//			break;

		//û�ҵ���
		if (!GetVisionData())
		{
			D_theta = BasketballRobot.ThetaD - theta;

			if(BasketballRobot.Y >= 3.75f||fabs(BasketballRobot.X) > 2.0)//û�ҵ����ߵ���������������
			{
				if(changdi == 0)
					RobotGoTo(-1.5, 2.25f,0);
				else
					RobotGoTo(1.5, 2.25f,0);
			}
			else
				RotateOnItsOwnAxis(theta);
		}
		else
		{
			vision_flag = MoveOfFindingBallByVision();
			if (vision_flag == 0)
				break;
		}
	} 

	//�״������ʣ������״�����Ѱ�ң��״�1m������
	if (Radar.Distance <= 1000)
	{
		while (1)
		{
			while ((Radar.RX_STA & 0x8000) == 0);
			radar_flag = MoveOfFindingBallByRadar();
			if (radar_flag == 0)
				break;
		}
	}

	GetInfraredState();
	
	Set_MotorSpeed(0, 0, 0, 0);

	Robot_ArmUp();
	
	LCD_Show_setspeed();
		
}

//�״�������
void FindBasketry(void)
{
	float w = 300;
	float D_theta = 0;	
	
	Set_MotorSpeed(0,0,0,0);
	LCD_Show_getspeed();
	while(1)
	{	
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
			//��ʱ����ת�����ٶ�
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
	}
	
}

//�Ӿ���λ
void GoBack_Vision(u8 ball)
{
	float w = 200;
	
	u8 time = 1;
	
	float theta = BasketballRobot.ThetaR,D_theta = 0;
	
	//��a���Ӿ����û�λ����
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
		//�ȴ����ݽ������
		while((Vision.RX_STA & 0x8000) == 0);
		
		//����������Ч
		if(!GetVisionData())
		{	
			if(time == 0);
				
			//�������
			else if(time++ <5)
			{				
				Set_MotorSpeed(0,0,0,0);
				continue;
			}
			//������κ���δ�ҵ���
			else if(time !=0)
				time = 0;
		}
		//������Ч
		else
			time = 1;
		
		//û�ҵ���,��ת
		if(time == 0)
			RotateOnItsOwnAxis(theta);
		
		//��Ч����
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

void FindBall_VandR_sanfenxian_VisionFirst(u8 ball)//Self_Edit���������Ӿ���������
{
    u8 vision_flag, radar_flag;
	u8 time = 1;
	float theta = BasketballRobot.ThetaD, D_theta = 0;
	
	Choose_ball (ball);//��������λ��������Ҫ�������Ϣ
	
	Set_MotorSpeed(0, 0, 0, 0);
	
	LCD_Show_getspeed();

	//����Ӿ���������
	USART1_RX_STA = 0;

	//��մ��ڽ������ݻ���
	USART3_RX_STA = 0;
	

	while (1)//�Ӿ��ߵ�1m
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

		//û�ҵ���,��ת
		if (time == 0)
			RotateOnItsOwnAxis(theta);
		else
		{
			vision_flag = MoveOfFindingBallByVision();
			if (vision_flag == 0)
				break;
		}
	} 
	
	//�״������ʣ������״�����Ѱ�ң��״�1m������
	if (Radar.Distance <= 1000)
	{
		while (1)
		{
			while ((Radar.RX_STA & 0x8000) == 0);
			radar_flag = MoveOfFindingBallByRadar();
			if (radar_flag == 0)
				break;
		}
			
	}
	GetInfraredState();
	
	Set_MotorSpeed(0, 0, 0, 0);

	Robot_ArmUp();

	LCD_Show_getspeed();
	
}

