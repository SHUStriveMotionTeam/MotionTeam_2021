#ifndef _CONTROL_H
#define _CONTROL_H

#include "stm32f4xx_HAL.h"
#include "sys.h"
#include "pid.h"
#include <math.h>
#include "tim.h"
#include "usart.h"
#include "lcd.h"
#include "mpu6050.h"
#include "delay.h"
#include "gpio.h"
#include "get_info.h"

#define CURRENT_MAX 8000				//电流最大值
#define ANGLE_MAX   8191                //转子机械角度最大值，对应转子机械角度360°
#define PI 3.141592654f

#define PLATFORM_L 1.0f   //平台车轮长方向中心距离的一半与平台车轮宽方向中心距离的一半之和
#define VISION_MID 256    //视觉定位中心
#define RADAR_MID  266    //雷达定位中心   机器人同向雷达角度从左往右越来越大
//#define DIS_RADAR 	2485//投球点与篮筐间的雷达定位距离 2500
#define DIS_VISION 	280   //篮筐视觉定位距离

//#define Basketry(x) ((x == 1) ? (BASKETRY_MID = 261) : (BASKETRY_MID = 270.5))
#define Basketry(x) ((x == 1) ? (BASKETRY_MID = 266) : (BASKETRY_MID = 266))//Self_Edit 1：向右调小266    0:向右调小 268
//#define Distance(x) ((x == 1) ? (DIS_RADAR = 2478) : (DIS_RADAR = 2420))
#define Distance(x) ((x == 1) ? (DIS_RADAR = 1842) : (DIS_RADAR = 1842))//Self_Edit向前调小


extern float output[6];
extern float BASKETRY_MID;
extern float DIS_RADAR;

enum{
    SPEED = 0,
    CURRENT 	,
    POSITION 	,
};

typedef struct
{
	uint16_t Angle;		  //转子机械角度
	int16_t Speed;	      //转子转速
	int16_t Current;      //转矩电流
	int16_t Temperature;  //电机温度
	int16_t SetSpeed;
	int16_t SetAngle;
	
	PID_t SpeedPID;
	PID_t AnglePID;
	
	int16_t Single_LoopOutput;
//	int16_t Double_LoopOutput;
//	int16_t AngleOutput;

}MOTOR;


//接收雷达数据，极坐标
struct RADAR
{
	uint16_t RX_STA;
	
	uint8_t RX_BUF[20];
	
	uint32_t Distance;  //距离
	
	uint32_t Angle;     //角度
	
	u8 State;           //状态
	
};

//接收视觉数据
struct VISION
{
	uint16_t RX_STA;
	
	uint16_t RX_BUF[20];
	
	uint32_t Depth;  //深度，纵轴
	
	uint32_t X;      //X位置，横轴
	
	u8 State;        //状态
};

//铲球电机运行状态
typedef enum
{
	STOP = 0,
	UP,
	DOWN
}shovemotor;

typedef struct
{
    uint8_t Count;
	uint8_t Buf[20];
	u8		Sum;
	u8		pidReadBuf;
	PID_t* 	pidAdjust;
} RxPID;

typedef struct
{
	float X;                  //机器人在坐标系中y坐标
	float Y;		          //机器人在坐标系中y坐标
	float PX;		          //点的x坐标
	float PY;		          //点的y坐标
	float ThetaR;             //机器人正方向和x轴夹角 弧度
	float ThetaD;	          //机器人正方向和x轴夹角 角度
	float D_Theta;
	
	float Vx;		          //机器人在坐标系x方向速度
	float Vy;		          //机器人在坐标系y方向速度	
	float W;		          //机器人角速度，顺时针正方向
	
	int16_t w[2];             //编码器速度
	int64_t encoderCount[2];  //编码器总计数
	
	float LastTheta;          //上一时刻，机器人Theta角
	
}ROBOT;

//extern PID_t* pidAdjust;
extern MOTOR Motor[4];
extern ROBOT BasketballRobot;
extern RxPID rxPID;
extern struct RADAR Radar;
extern struct VISION Vision;

void Control_Init(void);
void AllPID_Init(void);
void Calc_MotorSpeed_pid(void);
void Calc_MotorAngle_pid(void);
void Set_MotorSpeed(float V1,float V2,float V3,float V4);  //设置电机的速度（控制电流）
void GetMotorVelocity_Self(float vx, float vy, float w);
void GetMotorVelocity(int16_t vx_a, int16_t vy_a, int16_t w_a);
void GetInfraredState(void);    //获取红外开关状态
void ShoveMotor(shovemotor t);  //铲球电机状态
void Robot_ArmDown(void);       //机械臂下降
void Robot_ArmUp(void);         //机械臂上升
static float adjustAngleVw_PD(float D_Theta);  //PD调整角速度
static float adjustVy_PD(float D_Y,  float ID_Y);//PD调整Y轴速度
static float adjustVx_PD(float D_X,  float ID_X); //PD调整X轴速度                 //自转一周
void RobotRotate_Vision(u32 V_X, u32 V_D);
void RobotRotate(float theta);                 //自旋运动，根据误差角度，自动调节
void RobotGoTo(float X_I,float Y_I,float Theta_I);  //行至目的地
void RobotGoAvoidance(void);
void RobotGoToAvoid(float X_I, float Y_I, float Theta_I);
u8 Shot_Ball(void);
u8 Up_ShotBall(void);

#endif
