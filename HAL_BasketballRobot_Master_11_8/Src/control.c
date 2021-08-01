#include "control.h"
#include "get_info.h"

u16 Lost_IMUtime = 0;

RxPID rxPID;     //���ڵ���pid

float BASKETRY_MID;

float DIS_RADAR;
float output[6];

struct RADAR Radar;
struct VISION Vision;

MOTOR Motor[4];
ROBOT BasketballRobot;
PID_t *pidAdjust;

void Control_Init(void)
{
	BasketballRobot.X = 0;          //������������ϵ��x���� -0.52
	BasketballRobot.Y = 0;          //������������ϵ��y����  0.64
	BasketballRobot.ThetaD = 0;     //�������������y��н� �Ƕ�
	BasketballRobot.ThetaR = 0;     //�������������y��н� ����
	BasketballRobot.LastTheta = 0;  //��һʱ�̣�������theta��
	
	BasketballRobot.Vx = 0;      //������������ϵx�����ٶ�
	BasketballRobot.Vy = 0;      //������������ϵy�����ٶ�
	BasketballRobot.W = 0;       //�����˽��ٶȣ�˳ʱ��������
	
	BasketballRobot.w[0] = 0;    //��һ���������ٶ�
	BasketballRobot.w[1] = 0;     //�ڶ����������ٶ�
	
	BasketballRobot.encoderCount[0] = 0;  //��һ����������ܼ���
	BasketballRobot.encoderCount[1] = 0;  //�ڶ�����������ܼ���	
	
	HAL_UART_Receive_IT(&huart1,(u8 *)aRxBuffer1, 1);//�������ڽ����ж�
	HAL_UART_Receive_IT(&huart2,(u8 *)aRxBuffer2, 1);
	HAL_UART_Receive_IT(&huart3, &rxPID.pidReadBuf, 1);
	HAL_UART_Receive_IT(&huart4, (u8 *)aRxBuffer3, 1);
	
	IMU_Init();  //�����ǳ�ʼ��
	
	HAL_TIM_Encoder_Start(&htim2, TIM_CHANNEL_ALL);  //����������ͨ��
	HAL_TIM_Encoder_Start(&htim4, TIM_CHANNEL_ALL);

	//��������
	HAL_TIM_IC_Start_IT(&htim1, TIM_CHANNEL_1);
	HAL_TIM_Base_Start_IT(&htim1);
	HAL_TIM_Base_Start_IT(&htim5);
	HAL_TIM_PWM_Start(&htim9, TIM_CHANNEL_1);
	HAL_TIM_PWM_Start(&htim9, TIM_CHANNEL_2);
	
	Set_MotorSpeed(0,0,0,0);
}

//���õ�����ٶȣ����Ƶ�����
void Set_MotorSpeed(float V1,float V2,float V3,float V4)
{
	Motor[0].SetSpeed = V1;
	Motor[1].SetSpeed = V2;
	Motor[2].SetSpeed = V3;
	Motor[3].SetSpeed = V4;
}

void AllPID_Init(void)
{
	u8 i;
	for (i = 0;i < 4;i ++)
	{
	    PID_Init(&(Motor[i].SpeedPID), POSITION_PID, 5000, 2000,6.8f,0.3f,0);
		//Motor[0].SpeedPID
//	    PID_Init(&(Motor[i].AnglePID), POSITION_PID, ANGLE_MAX, 5000,10,0,0);//0.25,0,0
	}
}
//����PID���Ƴ���
//�����ٶ�PID��λ��PID����
void Calc_MotorSpeed_pid(void)
{
	u8 i;
	
	for (i = 0;i < 4;i ++)
	    Motor[i].Single_LoopOutput = PID_Calc(&(Motor[i].SpeedPID),
		                                  Motor[i].Speed, Motor[i].SetSpeed);
}

void Calc_MotorAngle_pid(void)
{
//	u8 i;
//	DoubleLoop_Flag = 1;
//	
//	for (i = 0;i < 4;i ++)
//	{
//	    Motor[i].SetSpeed = PID_Calc(&(Motor[i].AnglePID),
//											     Motor[i].Angle, Motor[i].SetAngle);
//		DoubleLoop_Flag = 0;
//		
//	    Motor[i].Double_LoopOutput = PID_Calc(&(Motor[i].SpeedPID),
//											     Motor[i].Speed, Motor[i].SetSpeed);
//	}
}

//����������ϵ�ٶ�������ӵ��ٶ�
//�����ķ�����˶��ֽ�ʱע��ÿ�����ӵ�������
//vx�����������x���ٶ�
//vy�����������y���ٶ�
//w:  ������ԭ����ת�Ľ��ٶ�
void GetMotorVelocity_Self(float vx, float vy, float w)
{
	Motor[0].SetSpeed = vx + vy + w * PLATFORM_L;
	Motor[1].SetSpeed = vx - vy + w * PLATFORM_L;
	Motor[2].SetSpeed = - vx - vy + w * PLATFORM_L;
	Motor[3].SetSpeed = - vx + vy  + w * PLATFORM_L;
	
	LCD_Show_setspeed();
}

//�����������ٶ�������ӵ��ٶ�
//vx���������x���ٶ�
//vy���������y���ٶ�
//w:������ԭ����ת�Ľ��ٶ�
void GetMotorVelocity(int16_t vx_a, int16_t vy_a, int16_t w_a)
{
	int i;
    int16_t vx,vy,w;
	
	vx = vx_a * cos(BasketballRobot.ThetaR) + vy_a * sin(BasketballRobot.ThetaR);
	vy = -vx_a * sin(BasketballRobot.ThetaR) + vy_a * cos(BasketballRobot.ThetaR);
	w = w_a;
	
	Motor[0].SetSpeed = vx + vy + w * PLATFORM_L;
	Motor[1].SetSpeed = vx - vy + w * PLATFORM_L;
	Motor[2].SetSpeed = - vx - vy + w * PLATFORM_L;
	Motor[3].SetSpeed = - vx + vy  + w * PLATFORM_L;
	
//	if( fabs(Motor[0].SetSpeed) > 3000 || fabs(Motor[1].SetSpeed) > 3000 || fabs(Motor[2].SetSpeed) >3000 || fabs(Motor[3].SetSpeed) >3000)
//		for(i=0;i<4;i++)
//			Motor[i].SetSpeed = 0.6 * Motor[i].SetSpeed;
	
	LCD_Show_setspeed();
}

//��ȡ���⿪��״̬
void GetInfraredState(void)
{
	while (1)
	{
		if (INFRARED)
			break;
		while (!INFRARED)
		{
			GetMotorVelocity_Self(0, 300, 0);
		}
		break;
	}
}

//������״̬
void ShoveMotor(shovemotor t)
{
	if (t == DOWN)
	{
		__HAL_TIM_SET_COMPARE(&htim9, TIM_CHANNEL_1, 300);
		__HAL_TIM_SET_COMPARE(&htim9, TIM_CHANNEL_2, 0);
	}
	
	if (t == STOP)
	{
		__HAL_TIM_SET_COMPARE(&htim9, TIM_CHANNEL_1, 1000);
		__HAL_TIM_SET_COMPARE(&htim9, TIM_CHANNEL_2, 1000);
	}
	
	if (t == UP)
	{
		__HAL_TIM_SET_COMPARE(&htim9, TIM_CHANNEL_1, 0);
		__HAL_TIM_SET_COMPARE(&htim9, TIM_CHANNEL_2, 300);
	}
}

//��е���½�
void Robot_ArmDown(void)
{
	if (LimitSwitchDown == 1)
	{
		ShoveMotor(STOP);
		return;
	}
	ShoveMotor(DOWN);
	
	while (1)
	{
		if (LimitSwitchDown == 1)
		{
			delay_ms(5);
			if (LimitSwitchDown == 1)
			{
				ShoveMotor(STOP);
				break;
			}
		}
	}
	
	/*
	ShoveMotor(DOWN);
    delay_ms(2000);
	ShoveMotor(STOP);	
	
	*/
}

//��е������
void Robot_ArmUp(void)
{
	if (LimitSwitchUp == 1)
	{
		ShoveMotor(STOP);
		return;
	}
	ShoveMotor(UP);
	
	while (1)
	{
		if (LimitSwitchUp == 1)
		{
			delay_ms(5);
			if (LimitSwitchUp == 1)
			{
				ShoveMotor(STOP);
				break;
			}
		}
	}
	/*ShoveMotor(UP);
    delay_ms(2000);
	ShoveMotor(STOP);*/

}

//PD�������ٶ�
static float adjustAngleVw_PD(float D_Theta)
{
	float Vw = 0;
	
	if (D_Theta > 0 && D_Theta < 180)
		Vw = -D_Theta * 20;
	else if (D_Theta > 180)
	{
		D_Theta = 360 - D_Theta;
		Vw = D_Theta * 20;
	}
	else if (D_Theta > -180)
		Vw = -D_Theta * 20;
	else if (D_Theta < -180)
	{
		D_Theta = 360 + D_Theta;
		Vw = -D_Theta * 20;
	}
	
	if (Vw > 1000)
		Vw = 1000;
	if (Vw < -1000)
		Vw = -1000;
	
	if (Vw > 0 && Vw < 150)
		Vw = 150;
	if (Vw > -150 && Vw < 0)
		Vw = -150;
	
	return Vw;
}
/*
//PD����X���ٶ�
static float adjustVx_PD(float D_X, float ID_X)
{
	float sx, Now_DX, Last_DX=0;
	Now_DX = D_X;
	
	
	if (Now_DX > 0.05f)
	{
		 if (Now_DX < 1.0f)  //����Ŀ��С��1m
			sx = Now_DX * 2300 + 100 * (Now_DX - Last_DX) + 200;	
		 
		else if (fabs(ID_X - Now_DX) < 0.4f)  //�������С��0.4m��������
			sx =fabs(ID_X - Now_DX) * 5500  + 300;
		
		else
			sx = 2500;
		
		if (sx > 2500)
			sx = 2500;
	}
	
	else if (Now_DX < -0.05f)
	{
		 if (Now_DX > -1.0f)
			sx = Now_DX * 2300 +  100 * (Now_DX - Last_DX) -200;		
		
		else if (-fabs(ID_X - Now_DX) > -0.4f)
			sx =-fabs(ID_X - Now_DX) * 5500  - 300;
		
		else
			sx = -2500;
		
		if (sx < -2500)
			sx = -2500;
	}
	else
		sx = 0;
	
	
	Last_DX = Now_DX;
	
	return sx;	
}


//PD����Y���ٶ�
static float adjustVy_PD(float D_Y , float ID_Y)
{
	
	float sy, Now_DY, Last_DY=0;
	Now_DY = D_Y;
	
	
	if (Now_DY > 0.05f)
	{
		//sy = Now_DY * 1000 + 200;
		
		if (Now_DY < 1.0f)  //����Ŀ��С��1m
			sy = Now_DY * 2300 + 100 * (Now_DY - Last_DY) + 200;
			
		else if(fabs(ID_Y-Now_DY) < 0.4f)//�������С��0.3m
			sy =fabs(ID_Y-Now_DY) * 5500  + 300;
		
		else
			sy = 2500;
		
		if (sy > 2500)
			sy = 2500;
	}
	
	else if (Now_DY < -0.05f)
	{
		 if (Now_DY > -1.0f)
			sy = Now_DY * 2300 +  100 * (Now_DY - Last_DY) -200;
		
		else if (-fabs(ID_Y - Now_DY) > -0.4f)//����Ŀ��С��0.3m
			sy =-fabs(ID_Y - Now_DY) * 5500  - 300;

		else
			sy = -2500;
		
		if (sy < -2500)
			sy = -2500;
	}
	else
		sy = 0;
	
	
	Last_DY=Now_DY;
	
	return sy;
}*/
/*
//PD����X���ٶ�  �����ٶ�3500
static float adjustVx_PD(float D_X, float ID_X)
{
	float sx, Now_DX, Last_DX=0;
	Now_DX = D_X;
	
	
	if (Now_DX > 0.05f)
	{		
		if (fabs(ID_X - Now_DX) < 0.4f)  //�������С��0.4m��������
			sx =fabs(ID_X - Now_DX) * 9500  + 300;
		
		else if (Now_DX < 1.0f)  //����Ŀ��С��1m
			sx = Now_DX * 3800 + 100 * (Now_DX - Last_DX) + 200;
		else
			sx = 4000;
		
		if (sx > 4000)
			sx = 4000;
	}
	
	else if (Now_DX < -0.05f)
	{
		if (-fabs(ID_X - Now_DX) > -0.4f)
			sx =-fabs(ID_X - Now_DX) * 9500  - 300;
		
		else if (Now_DX > -1.0f)
			sx = Now_DX * 3800 +  100 * (Now_DX - Last_DX) -200;
		else
			sx = -4000;
		
		if (sx < -4000)
			sx = -4000;
	}
	else
		sx = 0;
	
	
	Last_DX = Now_DX;
	
	return sx;	
}




//PD����Y���ٶ�  �����ٶ�3500
static float adjustVy_PD(float D_Y , float ID_Y)
{
	
	float sy, Now_DY, Last_DY=0;
	Now_DY = D_Y;
	
	
	if (Now_DY > 0.05f)
	{
		//sy = Now_DY * 8000 + 200;
		
		if (fabs(ID_Y-Now_DY) < 0.4f)//�������С��0.3m
			sy =fabs(ID_Y-Now_DY) * 8000  + 300;
		
		else if (Now_DY < 1.0f)  //����Ŀ��С��1m
			sy = Now_DY * 3300 + 100 * (Now_DY - Last_DY) + 200;
		else
			sy = 3500;
		
		if (sy > 3500)
			sy = 3500;
	}
	
	else if (Now_DY < -0.05f)
	{
		if (-fabs(ID_Y - Now_DY) > -0.4f)//����Ŀ��С��0.3m
			sy =-fabs(ID_Y - Now_DY) * 8000  - 300;
		
		else if (Now_DY > -1.0f)
			sy = Now_DY * 3300 +  100 * (Now_DY - Last_DY) -200;
		else
			sy = -3500;
		
		if (sy < -3500)
			sy = -3500;
	}
	else
		sy = 0;
	
	
	Last_DY=Now_DY;
	
	return sy;
}*/



//PD����X���ٶ�  �����ٶ�4000
static float adjustVx_PD(float D_X, float ID_X)
{
	float sx, Now_DX, Last_DX=0;
	Now_DX = D_X;
	
	
	if (Now_DX > 0.05f)
	{		
		if (fabs(ID_X - Now_DX) < 0.4f)  //�������С��0.4m��������
			sx =fabs(ID_X - Now_DX) * 9500  + 300;
		
		else if (Now_DX < 1.0f)  //����Ŀ��С��1m
			sx = Now_DX * 3800 + 100 * (Now_DX - Last_DX) + 200;
		else
			sx = 4000;
		
		if (sx > 4000)
			sx = 4000;
	}
	
	else if (Now_DX < -0.05f)
	{
		if (-fabs(ID_X - Now_DX) > -0.4f)
			sx =-fabs(ID_X - Now_DX) * 9500  - 300;
		
		else if (Now_DX > -1.0f)
			sx = Now_DX * 3800 +  100 * (Now_DX - Last_DX) -200;
		else
			sx = -4000;
		
		if (sx < -4000)
			sx = -4000;
	}
	else
		sx = 0;
	
	
	Last_DX = Now_DX;
	
	return sx;	
}

//PD����Y���ٶ�  �����ٶ�4000
static float adjustVy_PD(float D_Y , float ID_Y)
{
	
	float sy, Now_DY, Last_DY=0;
	Now_DY = D_Y;
	
	
	if (Now_DY > 0.05f)
	{
		//sy = Now_DY * 9500 + 200;
		
		if (fabs(ID_Y-Now_DY) < 0.4f)//�������С��0.3m
			sy =fabs(ID_Y-Now_DY) * 9500  + 300;
		
		else if (Now_DY < 1.0f)  //����Ŀ��С��1m
			sy = Now_DY * 3800 + 100 * (Now_DY - Last_DY) + 200;
		else
			sy = 4000;
		
		if (sy > 4000)
			sy = 4000;
	}
	
	else if (Now_DY < -0.05f)
	{
		if (-fabs(ID_Y - Now_DY) > -0.4f)//����Ŀ��С��0.3m
			sy =-fabs(ID_Y - Now_DY) * 9500  - 300;
		
		else if (Now_DY > -1.0f)
			sy = Now_DY * 3800 +  100 * (Now_DY - Last_DY) -200;
		else
			sy = -4000;
		
		if (sy < -4000)
			sy = -4000;
	}
	else
		sy = 0;
	
	
	Last_DY=Now_DY;
	
	return sy;
}





/*
void RobotRotate_Vision(u32 V_X, u32 V_D)
{
	float D_X, D_Y, D_Theta, N_Theta;
	float Vw = 0;  //w > 0��˳ʱ��
	
	D_X = -(V_X - VISION_MID) / 200.0f;
	D_Y = V_D / 1000.0f;
	D_Theta = -atan2(D_Y, D_X) / PI * 180.0f;
	N_Theta = BasketballRobot.D_Theta;
	
	while(D_Theta > 1 || D_Theta < -1)
	{
		D_Theta = D_Theta - (BasketballRobot.D_Theta - N_Theta);
		
		Vw = adjustAngleVw_PD(D_Theta);
		
		Set_MotorSpeed(Vw,Vw,Vw,Vw);
		
		LCD_Show_setspeed();
	}
	Set_MotorSpeed(0,0,0,0);
}*/

//�����˶����������Ƕȣ��Զ�����
void RobotRotate(float theta)
{
	float D_Theta;
	float Vw = 0;  //w > 0��˳ʱ��
	
	while (theta < 0)
		theta = theta + 360;
	
	while (theta > 360)
		theta = theta - 360;
	
	D_Theta = theta - BasketballRobot.ThetaD;
	
	Vw = adjustAngleVw_PD(D_Theta);

	while (D_Theta > 1 || D_Theta < -1)
	{
		Set_MotorSpeed(Vw,Vw,Vw,Vw);
		
		D_Theta = theta - BasketballRobot.ThetaD;
		
		Vw = adjustAngleVw_PD(D_Theta);
		
		LCD_Show_setspeed();
	}
	
	Set_MotorSpeed(0,0,0,0);
}

//����Ŀ�ĵ�
//X_I:Ŀ�ĵ������X
//Y_I:Ŀ�ĵ������Y
//Theta_I:Ŀ�ĵ�����ĽǶ�
void RobotGoTo(float X_I,float Y_I,float Theta_I)
{
	float D_Theta, D_X, D_Y, ID_X, ID_Y, Vw, sx, sy;
	
	D_Theta = Theta_I - BasketballRobot.ThetaD;
	D_X = X_I - BasketballRobot.X;
	D_Y = Y_I - BasketballRobot.Y;
	ID_Y=D_Y;
	ID_X=D_X;
	
	while (fabs(D_Y) > 0.05f || fabs(D_X) > 0.05f)
	{
		sy = adjustVy_PD(D_Y, ID_Y);
		sx = adjustVx_PD(D_X, ID_X);
		Vw = adjustAngleVw_PD(D_Theta);
		
		GetMotorVelocity(sx,sy,Vw);
		
		Set_MotorSpeed(Motor[0].SetSpeed,Motor[1].SetSpeed,
		               Motor[2].SetSpeed,Motor[3].SetSpeed);
		
		D_Theta = Theta_I - BasketballRobot.ThetaD;
	    D_X = X_I - BasketballRobot.X;
	    D_Y = Y_I - BasketballRobot.Y;
	}
	RobotRotate(Theta_I);
	
	Set_MotorSpeed(0,0,0,0);
}

//����ֱ��
//ֱ��1m
void RobotGoAvoidance(void)
{
	//float w = 100;
	float theta = BasketballRobot.ThetaD, D_theta = 0;
	u8 time = 1;

	Set_MotorSpeed(0,0,0,0);
	LCD_Show_getspeed();
	
	Radar.RX_STA = 0;
	
	do
	{
		while((Radar.RX_STA&0x8000) == 0);//����δ���
		
		if (!GetRadarData())
		{
			if (time == 0)
			{
			}
			else if (time++ < 5)
			{
				Set_MotorSpeed(0, 0, 0, 0);
				continue;
			}
			else if (time != 0)
				time = 0;
		}
		else
			time = 1;

		//		if(Radar.Distance < 10)
		//			continue;
	
		if (time == 0)
		{
			GetMotorVelocity_Self(0, 1000, 0);
			Set_MotorSpeed(Motor[0].SetSpeed, Motor[1].SetSpeed, Motor[2].SetSpeed,Motor[3].SetSpeed);
			delay_ms(5000);
			Set_MotorSpeed(0,0,0,0);
			break;
		}
		
		
		if (Radar.Angle < RADAR_MID - 15)
		{
			GetMotorVelocity_Self(-500, 0, 0);
			Set_MotorSpeed(Motor[0].SetSpeed, Motor[1].SetSpeed, Motor[2].SetSpeed,Motor[3].SetSpeed);
		}
		else if (Radar.Angle > RADAR_MID + 15)
		{
			GetMotorVelocity_Self(500, 0, 0);
			Set_MotorSpeed(Motor[0].SetSpeed, Motor[1].SetSpeed, Motor[2].SetSpeed,Motor[3].SetSpeed);
		}
		else if (Radar.Distance > 300)
		{
			GetMotorVelocity_Self(0, 1000, 0);
			Set_MotorSpeed(Motor[0].SetSpeed, Motor[1].SetSpeed, Motor[2].SetSpeed,Motor[3].SetSpeed);
		}
		else if (Radar.Angle < RADAR_MID - 10)
		{
			GetMotorVelocity_Self(-300, 0, 0);
			Set_MotorSpeed(Motor[0].SetSpeed, Motor[1].SetSpeed, Motor[2].SetSpeed,Motor[3].SetSpeed);
		}
		else if ((Radar.Angle > RADAR_MID + 10))
		{
			GetMotorVelocity_Self(300, 0, 0);
			Set_MotorSpeed(Motor[0].SetSpeed, Motor[1].SetSpeed, Motor[2].SetSpeed,Motor[3].SetSpeed);
		}
		
		else if (Radar.Angle < RADAR_MID - 5)
		{
			GetMotorVelocity_Self(-200, 0, 0);
			Set_MotorSpeed(Motor[0].SetSpeed, Motor[1].SetSpeed, Motor[2].SetSpeed,Motor[3].SetSpeed);
		}
		else if (Radar.Angle > RADAR_MID + 5)
		{
			GetMotorVelocity_Self(200, 0, 0);
			Set_MotorSpeed(Motor[0].SetSpeed, Motor[1].SetSpeed, Motor[2].SetSpeed,Motor[3].SetSpeed);
		}
		else
		{
			if(BasketballRobot.Y >= 2.4f)
				RobotGoTo(BasketballRobot.X ,BasketballRobot.Y- 0.48f,BasketballRobot.ThetaD);
			else
				RobotGoTo(BasketballRobot.X ,BasketballRobot.Y+ 0.48f,BasketballRobot.ThetaD);
			
			GetMotorVelocity_Self(0, 1400, 0);
			Set_MotorSpeed(Motor[0].SetSpeed, Motor[1].SetSpeed, Motor[2].SetSpeed,Motor[3].SetSpeed);
			delay_ms(1700);
			Set_MotorSpeed(0,0,0,0);
			break;
		}
		LCD_Show_getspeed();
	} while (1);

	Set_MotorSpeed(0,0,0,0);
	LCD_Show_getspeed();	
}

//����ָ������
//X_I:Ŀ�������X
//Y_I:Ŀ�������Y
//Theta_I:Ŀ������ĽǶ�
//angle:Ŀ������͵�ǰ����������ĽǶ�
//�ȶ�׼Ŀ�����꣬ǰ�й������ж��Ƿ����ϰ��������޷��б��������ǻ����ˣ���˽����������м�տ�����
void RobotGoToAvoid(float X_I, float Y_I, float Theta_I)
{

	float D_Theta, D_X, D_Y, Vw = 0, sx, sy = 0,ObsDistance;
	float Offest_theta, angle, standard = 350, Distance, ID_Y, ID_X;

	D_X = X_I - BasketballRobot.X;
	D_Y = Y_I - BasketballRobot.Y;
	ID_X = D_X;
	ID_Y = D_Y;

	angle = atan2(D_Y, D_X);

	//if (angle > 0)
		angle = PI / 2 - angle;

//	else
//		angle = -PI / 2 - angle;

	RobotRotate(-angle / PI * 180);

	D_Theta = Theta_I - BasketballRobot.ThetaD; //�ǶȲ�

	while (fabs(D_Y) > 0.05f || fabs(D_X) > 0.05f)
	{

		//while((Radar.RX_STA&0x8000) != 0);

		GetRadarData();

		if (Radar.Distance > 1500 || (Radar.State == 0))
		{

			sx = adjustVx_PD(D_X, ID_X) / 2;

			sy = adjustVy_PD(D_Y, ID_Y) / 2;

			Vw = adjustAngleVw_PD(angle - BasketballRobot.ThetaD + 360);

			GetMotorVelocity(sx, sy, 0);

			Set_MotorSpeed(Motor[0].SetSpeed, Motor[1].SetSpeed, Motor[2].SetSpeed, Motor[3].SetSpeed);

			D_Theta = Theta_I - BasketballRobot.ThetaD;
			D_X = X_I - BasketballRobot.X;
			D_Y = Y_I - BasketballRobot.Y;
			//RobotGoTo(X_I,Y_I,Theta_I);
			//Radar.State = 0;
		}
		else
		{

			//SetPWM(0,0,0);

			Offest_theta = (Radar.Angle * 1.0f - RADAR_MID) * 1.0f * PI / 180;
			Distance = Radar.Distance * sin(Offest_theta);
			ObsDistance=0.5f+Radar.Distance * cos(Offest_theta)/1000;
			if (fabs(Distance) > 400)
			{
				RobotGoTo(BasketballRobot.X - ObsDistance * sin(BasketballRobot.ThetaR), BasketballRobot.Y + ObsDistance * cos(BasketballRobot.ThetaR), BasketballRobot.ThetaD);
				continue;
			}

			if (Offest_theta > 0)
			{

				if (Distance < 400)
				{

					GetMotorVelocity_Self((Distance - standard) / 5, 0, 0);
					Set_MotorSpeed(Motor[0].SetSpeed, Motor[1].SetSpeed, Motor[2].SetSpeed, Motor[3].SetSpeed);
					while (((Radar.RX_STA & 0x8000) == 0));
					//							Offest_theta=(Radar.Angle*1.0f-RADAR_MID)*PI/180;
					//							Distance=Radar.Distance*sin(Offest_theta);
				}
			}
			else
			{
				if (Distance > -600)
				{
					GetMotorVelocity_Self((Distance - standard) / 5, 0, 0);
					Set_MotorSpeed(Motor[0].SetSpeed, Motor[1].SetSpeed, Motor[2].SetSpeed, Motor[3].SetSpeed);

					while (((Radar.RX_STA & 0x8000) == 0));
					//						Offest_theta=(Radar.Angle*1.0f-RADAR_MID)*PI/180;
					//						Distance=Radar.Distance*sin(Offest_theta);
				}
			}
			//				RobotGoTo(BasketballRobot.X,Y_I,angle);
			//				RobotGoTo(X_I,Y_I,Theta_I);
			Radar.State = 0;
		}
	}
	Set_MotorSpeed(0, 0, 0, 0);
	delay_ms(1000);
	RobotRotate(Theta_I);
}

//����ʱ�����������
u8 Up_ShotBall(void)
{
	Robot_ArmDown();
	
	if (LimitSwitchDown == 1)
	{
		delay_ms(500);
		SHOT = 1;
		delay_ms(700);
		SHOT = 0;
		delay_ms(500);
		Robot_ArmUp();
		
		return 0;
	}
	return 1;
}

//����ʱ�����������
u8 Shot_Ball(void)
{
	if (LimitSwitchDown == 1)
	{
		delay_ms(500);
		SHOT = 1;
		delay_ms(500);
		SHOT = 0;
		
		return 0;
	}
	
	return 1;	
}
