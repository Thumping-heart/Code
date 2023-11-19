#include <Wire.h>//用于IIC通信
#include "Wheel__2_0.hpp"//轮子的底层文件
#include "GW_Grayscale_Sensor.h"//传感器有关的头文件
#include "IIC_Grayscale_Sensor__1_0.h"//IIC读取传感器的底层文件
#include "Tracking_Bottom.h"//寻迹逻辑底层

//存放运行时间
double Run_Time = 0;//用于存放时间
int Step = -1;//当前执行的步数

void setup() {
  // put your setup code here, to run once:
  Wire.begin();
  Init_Wheel();
  Init_READ_Digital_Sensor();//初始化 读取数字量的数据
  Serial.begin(115200);
}

void loop() {
  // put your main code here, to run repeatedly:
  Read_Sensor();//获取传感器的数据
  Print_Sensor();//串口打印传感器的数据
  Tracking();//寻迹部分

}

void Tracking()
{
  if(Step == -1)//左前移动
  {
    MA_SPD(170);
    MB_SPD(20);
    MC_SPD(170);
    MD_SPD(20);
    if(Sensor_Front_Data[4] == 1)
    {
      Step = 0;
    }
  }
  
  if(Step == 0)//前进
  {
    Straight(80);
    if(Sensor_Left_Data[1] == 1)
    {
      //传感器2的第1个 检测到了左边线
      Step = 1;
      Run_Time = millis();//用于设置车停止的时间
    }
  }
  
  else if(Step == 1)//停止
  {
    Stop();
    if(millis() - Run_Time > 100)
    {
      Step = 2;
      Run_Time = millis();//用于等待一段时间做后退检测
    }
  }

  else if(Step == 2)//左移
  {
    Left_Shift(100);
    if(Sensor_Rear_Data[6] == 1 && millis() - Run_Time > 2000)//等2秒再做后退检测
    {
      Step = 3;
      Run_Time = millis();//用于等待一段时间做前进检测
    }
  }
  
  else if(Step == 3)//后退
  {
    Straight(-80);
    if(Sensor_Rear_Data[1] == 0 && Sensor_Rear_Data[2] == 0 && Sensor_Rear_Data[3] == 0 && Sensor_Rear_Data[4] == 0 && 
       Sensor_Rear_Data[5] == 0 && Sensor_Rear_Data[6] == 0 && Sensor_Rear_Data[7] == 0 && Sensor_Rear_Data[8] == 0 && millis() - Run_Time > 2500)//等2秒再做后退检测
    {
      Step = 4;
    }
  }

  else if(Step == 4)//停止
  {
    Stop();
    if(millis() - Run_Time > 100)
    {
      Step = 5;
      Run_Time = millis();//用于等待一段时间再向前
    }
  }
  
  else if(Step == 5)//直行
  {
    Straight(80);
    if(Sensor_Left_Data[1] == 1 && millis() - Run_Time > 2000)//等2秒再做后退检测
    {
      Step = 6;
      Run_Time = millis();
    }
  }

  else if(Step == 6)//停止
  {
    Stop();
    if(millis() - Run_Time > 100)
    {
      Step = 7;
      Run_Time = millis();//用于等待一段时间做右移检测
    }
  }
  
  else if(Step == 7)//右移
  {
    Left_Shift(-100);
    if(Sensor_Rear_Data[6] == 1 && millis() - Run_Time > 1500)
    {
      Step = 8;
      Run_Time = millis();//用于等待一段时间做停止检测
    }
  }
  else if(Step == 8)//后退
  {
    Straight(-80);
    if(Sensor_Rear_Data[1] == 0 && Sensor_Rear_Data[2] == 0 && Sensor_Rear_Data[3] == 0 && Sensor_Rear_Data[4] == 0 && 
       Sensor_Rear_Data[5] == 0 && Sensor_Rear_Data[6] == 0 && Sensor_Rear_Data[7] == 0 && Sensor_Rear_Data[8] == 0 && 
       millis() - Run_Time > 1500)
    {
      Step = 9;
    }
  }
  else if(Step == 9)//停止
  {
    Stop();
    Step = 0;//进入循环
  }
}
