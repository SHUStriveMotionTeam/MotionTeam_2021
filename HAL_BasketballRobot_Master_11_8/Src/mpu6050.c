#include "mpu6050.h"
#include "usart.h"
#include "delay.h"
#include "control.h"
#include "get_info.h"


/*******************************

为模块化的MPU6050所写，该模块自带卡尔曼滤波算法
使用前建议通过上位机对加速度、角速度做矫正
MPU_Init()函数为Z轴校准

********************************/

void IMU_Init()
{
//	u8 Baud[5]={0xFF, 0xAA, 0x04, 0x06, 0x00};//设置波特率为115200
//	u8 Rate[5]={0xFF, 0xAA, 0x03, 0x09, 0x00};//设置回传速率为100Hz
//    //u8 Rate[5]={0xFF, 0xAA, 0x03, 0x0b, 0x00};//设置回传速率为250Hz
//    HAL_UART_Transmit(&huart2,Baud,sizeof(Baud),1000);
//	HAL_UART_Transmit(&huart2,Rate,sizeof(Rate),1000);
//	
	u8 cmd1[5] = {0XFF,0XAA,0X69,0X88,0Xb5};//发送解锁指令0XFF,0XAA,0X69,0X88,0XB5
	u8 cmd2[5] = {0XFF,0XAA,0X76,0X00,0X00};//角度初始化指令，使Z轴角度归零：0XFF,0XAA,0X76,0X00,0X00
	

	
	HAL_UART_Transmit(&huart2,cmd1,5,1000);
//	
	HAL_UART_Transmit(&huart2,cmd2,5,1000);
	
	delay_ms(100);
	
}

