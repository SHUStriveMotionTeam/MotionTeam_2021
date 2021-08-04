#include "mpu6050.h"
#include "usart.h"
#include "delay.h"
#include "control.h"
#include "get_info.h"


/*******************************

Ϊģ�黯��MPU6050��д����ģ���Դ��������˲��㷨
ʹ��ǰ����ͨ����λ���Լ��ٶȡ����ٶ�������
MPU_Init()����ΪZ��У׼

********************************/

void IMU_Init()
{
//	u8 Baud[5]={0xFF, 0xAA, 0x04, 0x06, 0x00};//���ò�����Ϊ115200
//	u8 Rate[5]={0xFF, 0xAA, 0x03, 0x09, 0x00};//���ûش�����Ϊ100Hz
//    //u8 Rate[5]={0xFF, 0xAA, 0x03, 0x0b, 0x00};//���ûش�����Ϊ250Hz
//    HAL_UART_Transmit(&huart2,Baud,sizeof(Baud),1000);
//	HAL_UART_Transmit(&huart2,Rate,sizeof(Rate),1000);
//	
	u8 cmd1[5] = {0XFF,0XAA,0X69,0X88,0Xb5};//���ͽ���ָ��0XFF,0XAA,0X69,0X88,0XB5
	u8 cmd2[5] = {0XFF,0XAA,0X76,0X00,0X00};//�Ƕȳ�ʼ��ָ�ʹZ��Ƕȹ��㣺0XFF,0XAA,0X76,0X00,0X00
	

	
	HAL_UART_Transmit(&huart2,cmd1,5,1000);
//	
	HAL_UART_Transmit(&huart2,cmd2,5,1000);
	
	delay_ms(100);
	
}

