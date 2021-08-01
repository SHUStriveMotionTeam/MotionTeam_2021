/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  ** This notice applies to any and all portions of this file
  * that are not between comment pairs USER CODE BEGIN and
  * USER CODE END. Other portions of this file, whether 
  * inserted by the user or by software development tools
  * are owned by their respective copyright owners.
  *
  * COPYRIGHT(c) 2018 STMicroelectronics
  *
  * Redistribution and use in source and binary forms, with or without modification,
  * are permitted provided that the following conditions are met:
  *   1. Redistributions of source code must retain the above copyright notice,
  *      this list of conditions and the following disclaimer.
  *   2. Redistributions in binary form must reproduce the above copyright notice,
  *      this list of conditions and the following disclaimer in the documentation
  *      and/or other materials provided with the distribution.
  *   3. Neither the name of STMicroelectronics nor the names of its contributors
  *      may be used to endorse or promote products derived from this software
  *      without specific prior written permission.
  *
  * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
  * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "can.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"
#include "fsmc.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "control.h"
#include "math.h"
#include "mpu6050.h"
#include "lcd.h"
#include "delay.h"
#include "remote.h"
#include "get_info.h"
#include "find_ball.h"

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
u8 zhongquan_case;
u8 sanfen_case;
u8 changdi=0;  	//����
u8 chengxu=0;	 //�غϳ���
u8 qiu=0;         //����
static u8 key;
/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */
	//u8 i;
	//int16_t time = 0;			//��ʱ
	//u8 findballtime = 0; 		//����ʱ�����Ƕȴ���
  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */
  delay_init(168);
  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_CAN1_Init();
  MX_FSMC_Init();
  MX_USART1_UART_Init();
  MX_USART2_UART_Init();
  MX_USART3_UART_Init();
  MX_TIM1_Init();
  MX_TIM4_Init();
  MX_TIM9_Init();
  MX_TIM5_Init();
  MX_TIM2_Init();
  MX_UART4_Init();
  /* USER CODE BEGIN 2 */
  HAL_SRAM_MspInit(&hsram1);
  Control_Init();
  CAN1_Init();
  AllPID_Init();
  LCD_Init();
  LCD_Show_Title();
		
  //FindBall_VandR_sanfenxian(6);
//FindBasketry();

//FindBall_VandR(6);
//	RobotGoTo(0.5,0.4,18);
//	while(1);

//  RobotGoTo(0,0,18);
//	FindBall_VandR(5);

  //ѡ����λ��PID���ζ���
  //rxPID.pidAdjust = &(Motor[3].AnglePID);

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  
	while (1)
	{
    /* USER CODE END WHILE */
    /* USER CODE BEGIN 3 */ 

//	    Robot_ArmUp();
		
		Remote_Control();  //ң����ѡ���򡢻غϳ��򡢳���
		
		switch (chengxu)
		{
			case 0:  //���Գ���
				switch (qiu)
				{
					case 0:  //����
                        
//                        SHOT = 1;
//                       delay_ms(1000);
//                       SHOT = 0;
                        //FindBall_vision(6);
						RobotRotate(180);
                        //RobotGoTo(0,1, 0);//self
                        //FindBall_VandR(6);
						break;
					case 1:  //��е���½�
						Robot_ArmDown();
//                        while(1)
//						{
//							if(LimitSwitchUp) //����λ����Ϊ�ߵ�ƽ
//								BEEP = 1;
//							else
//								BEEP = 0;
//						}
						break;
					case 2:  //��е������
                        Robot_ArmUp();
//                        while(1)
//						{
//							if(LimitSwitchDown) //����λ����Ϊ�ߵ�ƽ
//								BEEP = 1;
//							else
//								BEEP = 0;
//						}
						break;
					case 3:  //����
						while(1)
						{
							if(INFRARED) //��ס����Ϊ�ߵ�ƽ
								BEEP = 1;
							else
								BEEP = 0;
						}
						break;
					case 4:
						//�������
                        while(1)
                            SHOT = 1;
//						while (1)
//						{
//							key = Remote_Scan();
//							switch (key)
//							{
//								case KEY_1:
//									delay_ms(1000);
//									SHOT = 1;
//									break;

//								case KEY_2:
//									delay_ms(1000);
//									SHOT = 0;
//									break;

//								case KEY_3:
//									delay_ms(1000);
//									SHOT = 1;
//									delay_ms(1000);
//									SHOT = 0;
//									break;
//							}
//						}
						break;

					case 5://��ʾ����
                        RobotGoTo(0, 1.68f, 0);//�����_����
//                        FindBall_VandR_sanfenxian_VisionFirst(6);
                    
                        RobotGoTo(0.395, 4.678f, 20.258f);//Ͷ���
                        
//                        FindBasketry();

                        while (Up_ShotBall());
                    
//                        RobotRotate(120);
//                    
//                        FindBall_VandR_sanfenxian_VisionFirst(6);

//                        RobotGoTo(0.386f, 4.753f, 20.63f);//Ͷ���

//                        FindBasketry();

//                        while (Up_ShotBall());
//                        
//                        //�˺���ͣ
//                        Set_MotorSpeed(0, 0, 0, 0);
                        RobotGoTo(0,0,0);
                        break;
                        
					case 6:
						//�Ӿ��״����������
						FindBall_VandR(changdi);
						RobotGoTo(BasketballRobot.X,BasketballRobot.Y-0.5f,BasketballRobot.ThetaD);
						LED0 = !LED0;
						break;
					case 7:
						//��������
						//RobotGoTo(-5.06f-3.425f, 3.05f, 70.8f);
						FindBasketry();
					    while(Up_ShotBall());
						BEEP = 1;
						delay_ms(500);
						BEEP = 0;
						break;
					case 8:
						//����ֱ��
						FindBall_VandR(5);
                        //FindBall_vision(6);
						//RobotGoAvoidance();
						break;
                    
					case 9:
						FindBall_VandR_sanfenxian_VisionFirst(6);
						break;
					}
					break;	  
			
			case 1:			//�����һ�غ�
				switch (changdi)
				{
					case 1: //�°볡	
						RobotGoTo(0, 2.4, 0);

						
						//RobotGoTo(1.668, 2.4f, -120);//Ͷ���
                        RobotGoTo(0.92, 2.271f, -115);//Self_Edit �����
					
						while (Up_ShotBall());
                    
                        //RobotGoTo(1.349, 2.358f, 0);//Self_Edit

						RobotRotate(0);//Self_Editת������
					
						//FindBall_VandR_middle(5);
                        FindBall_VandR(5);

						//RobotGoTo(1.668, 2.4f, -120);//Ͷ���
                        RobotGoTo(0.92, 2.271f, -115);//Self_Edit �����
					
						while (Up_ShotBall());//��ѹ����Ϊ0.3MPa
						
						RobotGoTo(-0.1, 1 , 0);//��λ
                    
						RobotGoTo(-0.1,-0.1,0);
					
						break;                 
						
					case 0: //�ϰ볡/////////////////////////////////////////////////////////////////////
						RobotGoTo(0, 2.4, 0);	
						
						//RobotGoTo(-1.668f, 2.4f, 120);//Ͷ���
                        RobotGoTo(-0.92f, 2.271f, 121.267);//Self_Edit�����
					
						while (Up_ShotBall());//��ѹ����Ϊ0.3MPa

						RobotRotate(0);//ת������
					
						//FindBall_VandR_middle(5);
                        FindBall_VandR(5);

						//RobotGoTo(-1.668, 2.4f, 120);//Ͷ���
                        RobotGoTo(-0.92f, 2.271f, 121.267);//Self_Edit�����
					
						while (Up_ShotBall());
					
						
						RobotGoTo(0.2, 1 , 0);//Self��λ
					
						RobotGoTo(0.2, -0.1, 0);//Self��λ
					
						break;
				}
				break;					
		
			case 2: //����ڶ��غ�
				switch (changdi)
				{
					case 1: //�°볡
						RobotGoTo(0, 2.3, 0);//ֱ������


						//RobotGoTo(1.668, 2.4f, -30);//�����
                        RobotGoTo(0.92, 2.401f, 0);//Self_Edit_�����
					
                        FindBall_VandR(5);
						//FindBall_VandR_middle(5);

						//RobotGoTo(1.668, 2.4f, -120);//Ͷ���
                        //RobotGoTo(0.92f, 2.571f, -115);//Self_Edit�����
                        RobotGoTo(0.92f, 2.271f, -115);//Self_Edit�����
					
						while (Up_ShotBall());
                        

						//RobotGoTo(4.3f, 2.5f , -120);//�����������
                        RobotGoTo(4.37f, 1.756f , -90);//Self_Edit_�����������_����
					
						//FindBall_VandR(5);
                        FindBall_VandR(5);//Self_Edit
						
						//RobotGoTo(1.668, 2.4f, -120);//����Ͷ��
                        RobotGoTo(1.558, 2.4f, -120);//Self_Edit�����
					
						while(Up_ShotBall());

						RobotGoTo(-0.1, 1 , 0);//��λ
                    
						RobotGoTo(-0.1,-0.1,0);

						break;
						
					case 0: //�ϰ볡/////////////////////////////////////////////////////////////////////
						//����ڶ��غ�
						RobotGoTo(0, 2.6, 0);//ֱ������

						//RobotGoTo(-0.92f, 2.271f, 0);//Self_Edit
					
						//FindBall_VandR_middle(5);
                        FindBall_VandR(5);

						RobotGoTo(-0.92f, 2.271f, 121.267);//Self_Edit�����
					
						while (Up_ShotBall());

						RobotGoTo(-4.66f, 1.804f, 90);//�����������
					
                        //FindBall_vision(5);
						FindBall_VandR(5);//Self_Edit
						
						RobotGoTo(-1.568, 2.4f, 125);//Self_Edit�����
					
						while(Up_ShotBall());
                               
						RobotGoTo(0.2 , 1 , 0);//Self��λ
						
						RobotGoTo(0.2, -0.1 , 0);//Self��λ
							
						break;					
				}
				break;						
				
			case 3: //��������غ�
				switch (changdi)
				{
					case 1: //�°볡					
						//����ʱʮ��
						RobotGoTo(0, 2.5, 0);
	
		
						//����
						//RobotGoTo(4.3f, 2.5f, -100);//�����������
                        RobotGoTo(4.37f, 1.756f , -90);//Self_Edit_�����������_����
						FindBall_VandR_sanfenxian(5);//_Self_Edit

						//��¼�����A��λ��
						BasketballRobot.PX = BasketballRobot.X;
						BasketballRobot.PY = BasketballRobot.Y;

						//Ͷ��
						RobotGoTo(1.558, 2.4f, -120);//Ͷ���					
						while (Up_ShotBall());

						//�����������
						//if(BasketballRobot.PX>7.2f)//����ҵ�����������
                        if(BasketballRobot.PX>6.3f)//���ǰһ���ҵ�����������_Self_Edit
						{
							//RobotGoTo(4.3f, 2.5f, -120);//�����������
                            RobotGoTo(4.23f, 2.704f , -90);//Self_Edit_�����������_����
						}						
                        if(BasketballRobot.PX<6.3f)//���ǰһ���ҵ������������_Self_Edit
						{
							//RobotGoTo(4.3f, 2.5f, -120);//�����������
                            RobotGoTo(BasketballRobot.PX, BasketballRobot.PY , -110);//Self_Edit_�����������_����
						}
//						else if(BasketballRobot.PY<2.5f)
//						{
//							RobotGoTo(BasketballRobot.PX+0.3f,BasketballRobot.PY,-60);
//						}
//						else
//						{
//							RobotGoTo(BasketballRobot.PX+0.3f,BasketballRobot.PY,-90);
//						}	
						
						FindBall_VandR(5);//Self_Edit
						//FindBall_VandR(5);//_Self_Edit
						
						//if(BasketballRobot.PX<7.2f)//�����һ���������������������ҵ�
                        if(BasketballRobot.PX<6.3f)//�����һ��������_Self_Edit
							RobotGoTo(BasketballRobot.PX+0.2f,BasketballRobot.PY,-120);

						//Ͷ���
						RobotGoTo(1.558, 2.4f, -120);//Self_Edit Ͷ���
						
						while (Up_ShotBall());

						//��λ				
						RobotGoTo(-0.1, 1 , 0);//��λ
                    
						RobotGoTo(-0.1,-0.1,0);
						
						break;				

					case 0: //�ϰ볡/////////////////////////////////////////////////////////////////////
						//����ʱʮ��
						RobotGoTo(0, 2.5, 0);
	
		
						//����
						RobotGoTo(-4.66f, 1.804f, 90);//�����������
						FindBall_VandR_sanfenxian(5);

						//��¼�����A��λ��
						BasketballRobot.PX = BasketballRobot.X;
						BasketballRobot.PY = BasketballRobot.Y;

						//Ͷ��
						//RobotGoTo(-4.97,BasketballRobot.PY,-155);//���ߵ�Ͷ��㣬��ֹײ��
						//RobotGoTo(-4.97, 3.106f,-155);	//Ͷ���
						RobotGoTo(-1.508, 2.4f, 125);//Ͷ���
					
						while (Up_ShotBall());

						//�����������
						if(BasketballRobot.PX<-6.3f)//����ҵ��������ϵ���
						{
							RobotGoTo(-4.2f, 2.5f, 100);//�����������
						}						
                        if(BasketballRobot.PX>-6.3f)//���ǰһ���ҵ��������ڵ���_Self_Edit
						{
							//RobotGoTo(4.3f, 2.5f, -120);//�����������
                            RobotGoTo(BasketballRobot.PX-0.3f, BasketballRobot.PY , 120);//Self_Edit_�����������_����
						}
//						else if(BasketballRobot.PY<2.5f)
//						{
//							RobotGoTo(BasketballRobot.PX - 0.3f,BasketballRobot.PY,60);
//						}
//						else
//						{
//							RobotGoTo(BasketballRobot.PX-0.3f,BasketballRobot.PY,90);
//						}	
						FindBall_VandR(5);//Self_Edit
						//FindBall_VandR(5);
						
//						if(BasketballRobot.PX>-5.3f)//�����һ���������������������ҵ�	
//							RobotGoTo(BasketballRobot.PX-0.3f,BasketballRobot.PY,120);

						//Ͷ���
						RobotGoTo(-1.568, 2.4f, 125);//Self_EditͶ���
						
						while (Up_ShotBall());

						//��λ				
        				RobotGoTo(0.2f, 1, 0);//Self��λ				
	 					RobotGoTo(0.2f, -0.1, 0);//Self��λ
						break;
				}
				break;				
				
			case 4: //Ͷ����һ�غ� 
				switch (changdi)
				{
					case 1: //�°볡
						//�볡
						RobotGoTo(0, 2.875, 0);
	
		  
						//RobotGoTo(8.749f, 2.875f, -71.510f);
                        RobotGoTo(8.549f, 2.875f, -71.510f);//Self_EditͶ���

						//�״��ҿ�
						FindBasketry();

						while (Up_ShotBall());
						
						//RobotGoTo(1.7f,2.4f,-30);//���������
                        RobotGoTo(-0.4, 2.3f, 0);//Self_Edit_����� XY-0.4�� 2.3
                        FindBall_VandR(6);
						//FindBall_VandR_middle(6);//������˫����

						//RobotGoTo(8.501f, 2.984f, -68.440f);//Ͷ��� BASKETRY_MID��  260    2540
                        RobotGoTo(8.549f, 2.875f, -71.510f);//Self_EditͶ���
					
						FindBasketry();

						while (Up_ShotBall());

						Set_MotorSpeed(0,0,0,0);
						
						delay_ms(10000);
						
//						RobotGoTo(0.25 , 1 , 0);//��λ
//						RobotGoTo(0.25, -0.17 , 0);*/

						break;
						
					case 0: //�ϰ볡/////////////////////////////////////////////////////////////////////
						//Ͷ����һ�غ�
						RobotGoTo(0, 2.984, 0);

		  
						//RobotGoTo(-8.749f, 2.875f, 71.510f);///////////////////////////////
                        RobotGoTo(-8.165f, 2.887f, 67.423f);//Self_Edit ��ѹ��0.3
						//�״��ҿ�
						FindBasketry();
						
						while (Up_ShotBall());
						
						Robot_ArmUp();

						RobotGoTo(-0.92f,2.71f,0);//Self_Edit���������

                        FindBall_VandR(6);
						//FindBall_VandR_middle(6);//������˫����

						RobotGoTo(-8.165f, 2.887f, 67.423f);//Self_Edit ��ѹ��0.3///////////

						FindBasketry();

						while (Up_ShotBall());

						Set_MotorSpeed(0,0,0,0);
						
						
//						RobotGoTo(0.25 , 1 , 0);//��λ
//						RobotGoTo(0.25, -0.17 , 0);*/

						break;
				}
				break;		
			
			case 5: //Ͷ���ڶ��غ�
				switch (changdi)
				{
					case 1: //�°볡				
				
						//����ʱʮ��
						RobotGoTo(0, 2.5, 0);
					
						//RobotGoTo(4.3f, 2.5f, -90);//-3.425f
                        RobotGoTo(4.37f, 1.765f , -90);//Self_Edit_�����������
                        //FindBall_VandR_VisionFirst(6);//Self_Edit
						FindBall_VandR(6);

						//��¼�����A��λ��
						BasketballRobot.PX = BasketballRobot.X;
						BasketballRobot.PY = BasketballRobot.Y;

						//Ͷ���
						//RobotGoTo(-8.749f, 2.875f, 71.510f);///////////////////////////////
                        RobotGoTo(8.549f, 2.875f, -71.510f);//Self_EditͶ���

						//�״��ҿ�
						FindBasketry();
		//				RobotRotate(-70.8f);
		//				FindBasketry();

						while (Up_ShotBall());

						//�ȵ�������ֹײ��
						RobotGoTo(BasketballRobot.PX , BasketballRobot.PY , 260);

						//�ٵ����������
						//RobotGoTo(1.7f, 2.4f, -30);
                        RobotGoTo(-0.4, 2.3f, 0);//Self_Edit��������� XY0.92f, 2.56f
                        FindBall_VandR(6);//Self_Edit
						//FindBall_VandR_middle(6);

						//Ͷ���
						RobotGoTo(BasketballRobot.PX, BasketballRobot.PY, -30);
						//RobotGoTo(-8.749f, 2.875f, 71.510f);///////////////////////////////
                        RobotGoTo(8.549f, 2.875f, -71.510f);//Self_EditͶ���



						FindBasketry();

						while (Up_ShotBall());

						//��ͣ
						Set_MotorSpeed(0, 0, 0, 0);
						
		//				RobotGoTo(0.25 , 1 , 0);//��λ
		//				RobotGoTo(0.25, -0.17 , 0);
						
						break;
						
					case 0: //�ϰ볡/////////////////////////////////////////////////////////////////////
						RobotGoTo(0, 2.5, 0);
					
						//�����������Exc
						RobotGoTo(-4.66f, 1.804f, 90);

						//RobotGoTo(4.3f, 2.5f, 290);
                        //FindBall_VandR_VisionFirst(6);//Self_Edit
						FindBall_VandR(6);

						//��¼�����A��λ��
						BasketballRobot.PX = BasketballRobot.X;
						BasketballRobot.PY = BasketballRobot.Y;

						//Ͷ���
						RobotGoTo(-8.165f, 2.887f, 67.423f);//Self_Edit ��ѹ��0.3///////////////////////////////


						//�״��ҿ�
						FindBasketry();

						while (Up_ShotBall());

						//�ȵ�������ֹײ��
						RobotGoTo(BasketballRobot.PX , BasketballRobot.PY , -260);

						//�ٵ����������
						RobotGoTo(-0.92f, 2.271f, 0);//���������
                        FindBall_VandR(6);//Self_Edit
						//FindBall_VandR_middle(6);

						//Ͷ���
						RobotGoTo(BasketballRobot.PX, BasketballRobot.PY, 30);
						RobotGoTo(-8.165f, 2.887f, 67.423f);//Self_Edit ��ѹ��0.3///////////////////////////

						FindBasketry();

						while (Up_ShotBall());

						//��ͣ
						Set_MotorSpeed(0, 0, 0, 0);
						
//						RobotGoTo(0.25 , 1 , 0);//��λ
//						RobotGoTo(0.25, -0.17 , 0);
						
						break;
				}
				break;						


			case 6: //Ͷ�������غ�	
				switch (changdi)
				{
					case 1: //�°볡				
						
						//����ʱʮ��
						RobotGoTo(0, 2.5, 0);
					
						//�����������
						//RobotGoTo(4.3f, 2.5f, 290);
						//RobotGoTo(4.3f, 2.5f, -90);
                        RobotGoTo(4.37f, 2.8f , -90);//Self_Edit_�����������_����
						FindBall_VandR_sanfenxian(6);
                    
                        //��¼������λ��_Self_Edit
                        BasketballRobot.PX = BasketballRobot.X;
						BasketballRobot.PY = BasketballRobot.Y;
					
                        if(BasketballRobot.PX<6.3)//������ҵ���һ�ŵ���_Self_Edit
                        {//ʹ�������ұ���ֱ��
                            RobotRotate(-90);
                            RobotGoAvoidance();
                        }

						//Ͷ���
						//RobotGoTo(8.501f, 2.984f, -68.440f);//Ͷ��� BASKETRY_MID��  260    2540
                        RobotGoTo(8.549f, 2.875f, -71.510f);//Self_EditͶ���
						
						FindBasketry();
//						RobotRotate(-70.8f);
//						FindBasketry();

						while (Up_ShotBall());

						//�����������
						//if(BasketballRobot.Y>7.2)//������ҵ��ڶ��ŵ���
                        if(BasketballRobot.PX>6.3)//������ҵ��ڶ��ŵ���_Self_Edit
						{
							RobotGoTo(BasketballRobot.PX, BasketballRobot.PY , 150);
						}	
						else
						{
							//RobotRotate(-90);   //��ʱ��ת��90��
							RobotRotate(120);   //_Self_Edit
						}
						
						//FindBall_radar();
                        //FindBall_VandR_VisionFirst(6);//Self_Edit
						FindBall_VandR(6);

						//Ͷ���
						//RobotGoTo(8.501f, 2.984f, -68.440f);//Ͷ��� BASKETRY_MID��  260    2540
                        RobotGoTo(8.549f, 2.875f, -71.510f);//Self_EditͶ���

						FindBasketry();
						//RobotRotate(-70.8f);
						//FindBasketry();

						while (Up_ShotBall());
                        

						//�˺���ͣ
						Set_MotorSpeed(0, 0, 0, 0);

						break;
				

					case 0: //�ϰ볡/////////////////////////////////////////////////////////////////////
						//����ʱʮ��
						RobotGoTo(0, 2.5, 0);
					
						//�����������
					    RobotGoTo(-3.85f, 2.75f, 90);
						FindBall_VandR_sanfenxian(6);
                    
                        BasketballRobot.PX = BasketballRobot.X;
						BasketballRobot.PY = BasketballRobot.Y;

						//ʹ�������ұ���ֱ��
						RobotRotate(90);
						RobotGoAvoidance();

						//Ͷ���
						RobotGoTo(-8.165f, 2.887f, 67.423f);//Self_Edit ��ѹ��0.3/////////////////////

						FindBasketry();

						while (Up_ShotBall());
                    
                        if(BasketballRobot.PX<-6.3)//������ҵ��ڶ��ŵ���_Self_Edit
						{
							RobotGoTo(BasketballRobot.PX, BasketballRobot.PY , 90);
						}	
						else
						{
							//RobotRotate(-90);   //��ʱ��ת��90��
							RobotRotate(-120);   //_Self_Edit
						}

//						//�����������
//						if(BasketballRobot.Y>7.2)//������ҵ��ڶ��ŵ���
//							RobotGoTo(BasketballRobot.PX, BasketballRobot.PY ,-90);
//						else
//							RobotGoTo(BasketballRobot.X-1, 3.0,-100);
						
						//FindBall_radar();
                        //FindBall_VandR_VisionFirst(6);//Self_Edit
						FindBall_VandR(6);

						//Ͷ���
						RobotGoTo(-8.165f, 2.887f, 67.423f);//Self_Edit ��ѹ��0.3//////////////////
						
						FindBasketry();

						while (Up_ShotBall());

						//�˺���ͣ
						Set_MotorSpeed(0, 0, 0, 0);

                            ;
				}
				break;				
		}
		break;
		
	}
 
	while(1)//ͣ��ԭ�ؾ�ֹ����
		Set_MotorSpeed(0,0,0,0);
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /**Configure the main internal regulator output voltage 
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);
  /**Initializes the CPU, AHB and APB busses clocks 
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 8;
  RCC_OscInitStruct.PLL.PLLN = 336;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 4;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /**Initializes the CPU, AHB and APB busses clocks 
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */

  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{ 
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
