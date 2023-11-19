#include <Wire.h>//用于IIC通信
#include "Wheel__2_0.hpp"//轮子的底层文件
#include "GW_Grayscale_Sensor.h"//传感器有关的头文件
#include "IIC_Grayscale_Sensor__1_0.h"//IIC读取传感器的底层文件


//存放轮子的PWM值
int SPD_A = 0;
int SPD_B = 0;
int SPD_C = 0;
int SPD_D = 0;

//存放运行时间
double Run_Time = 0;
int Step = -1;


void setup() {
  // put your setup code here, to run once:
  Wire.begin();  
  Init_Wheel();
  Init_READ_Digital_Sensor();//初始化 读取数字量的数据
  Serial.begin(115200);
}

void loop() {
  // put your main code here, to run repeatedly:
  //读取传感器的数据
  
  Read_Sensor();
  Print_Sensor();

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
    Step = 0;
  }
}

void Stop()//停止
{
  MA_SPD(0);
  MB_SPD(0);
  MC_SPD(0);
  MD_SPD(0);
}

void Straight(int Straight_SPD)//当>0时前进，当<0时后退
{
  //前进和后退
  Straight_Sensor_Front_Program();//修正前方的轮子 DA
  Straight_Sensor_Rear_Program();//修正后方的轮子 CB
  MA_SPD(SPD_A+Straight_SPD);
  MB_SPD(SPD_B+Straight_SPD); 
  MC_SPD(SPD_C+Straight_SPD);
  MD_SPD(SPD_D+Straight_SPD);
}

void Left_Shift(int Left_Shift_SPD)//当>0时左移，当<0时右移
{
  //左平移和右平移
  Left_Shift_Sensor_Front_Program();//修正左侧的轮子 DC
  Left_Shift_Sensor_Rear_Program();//修正右侧的轮子 AB
  MA_SPD(SPD_A+Left_Shift_SPD);
  MB_SPD(SPD_B-Left_Shift_SPD);
  MC_SPD(SPD_C+Left_Shift_SPD);
  MD_SPD(SPD_D-Left_Shift_SPD);
}

//前进和后退的轮子修正
void Straight_Sensor_Front_Program()//修正前方的轮子 DA
{
  //左移动 1 2 3
  //右移动 8 7 6
  //感为科技文字朝向自己时的方向
  if(Sensor_Front_Data[1] == 1 )//车左移
  {
    SPD_A = 60;
    SPD_D = -60;
  }
  else if(Sensor_Front_Data[8] == 1)//车右移
  {
    SPD_A = -60;
    SPD_D = 60; 
  }
  
  else if(Sensor_Front_Data[2] == 1)
  {
    SPD_A = 40;
    SPD_D = -40;    
  }
  else if(Sensor_Front_Data[7] == 1)
  {
    SPD_A = -40;
    SPD_D = 40;
  }
  
  else if(Sensor_Front_Data[3] == 1)
  {
    SPD_A = 10;
    SPD_D = -10;     
  }  
  else if(Sensor_Front_Data[6] == 1)
  {
    SPD_A = -10;
    SPD_D = 10;    
  }

  else
  {
    SPD_A = 0;
    SPD_D = 0; 
  }
}

void Straight_Sensor_Rear_Program()//修正后方的轮子 CB
{
  //左移动 1 2 3
  //右移动 8 7 6  
  //感为科技文字朝向自己时的方向
  if(Sensor_Rear_Data[1] == 1)//车左移
  {
    SPD_B = 60;
    SPD_C = -60;
  }
  else if(Sensor_Rear_Data[8] == 1)//车右移
  {
    SPD_B = -60;
    SPD_C = 60;
  }
  
  else if(Sensor_Rear_Data[2] == 1)
  {
    SPD_B = 40;
    SPD_C = -40;    
  }
  else if(Sensor_Rear_Data[7] == 1)
  {
    SPD_B = -40;
    SPD_C = 40;    
  }
  
  else if(Sensor_Rear_Data[3] == 1)
  {
    SPD_B = 10;
    SPD_C = -10;    
  }
  else if(Sensor_Rear_Data[6] == 1)
  {
    SPD_B = -10;
    SPD_C = 10;    
  }

  else
  {
    SPD_B = 0;
    SPD_C = 0;
  }
}

//左平移和右平移的轮子修正
void Left_Shift_Sensor_Front_Program()//修正左侧的轮子 DC
{
  //上移动 1 2 3
  //下移动 8 7 6
  //感为科技文字朝向自己时的方向
  if(Sensor_Left_Data[1] == 1 )//车上移
  {
    SPD_C = 60;
    SPD_D = 60;
  }
  else if(Sensor_Left_Data[8] == 1)//车下移
  {
    SPD_C = -60;
    SPD_D = -60; 
  }
  
  else if(Sensor_Left_Data[2] == 1)
  {
    SPD_C = 40;
    SPD_D = 40;    
  }
  else if(Sensor_Left_Data[7] == 1)
  {
    SPD_C = -40;
    SPD_D = -40;
  }
  
  else if(Sensor_Left_Data[3] == 1)
  {
    SPD_C = 10;
    SPD_D = 10;     
  }  
  else if(Sensor_Left_Data[6] == 1)
  {
    SPD_C = -10;
    SPD_D = -10;    
  }

  else
  {
    SPD_C = 0;
    SPD_D = 0; 
  }
}

void Left_Shift_Sensor_Rear_Program()//修正右侧的轮子 AB
{
  //上移动 8 7 6 
  //下移动 1 2 3 
  //感为科技文字朝向自己时的方向
  if(Sensor_Right_Data[1] == 1)//车下移
  {
    SPD_A = -60;
    SPD_B = -60;
  }
  else if(Sensor_Right_Data[8] == 1)//车上移
  {
    SPD_A = 60;
    SPD_B = 60;
  }
  
  else if(Sensor_Right_Data[2] == 1)
  {
    SPD_A = -40;
    SPD_B = -40;    
  }
  else if(Sensor_Right_Data[7] == 1)
  {
    SPD_A = 40;
    SPD_B = 40;    
  }
  
  else if(Sensor_Right_Data[3] == 1)
  {
    SPD_A = -10;
    SPD_B = -10;    
  }
  else if(Sensor_Right_Data[6] == 1)
  {
    SPD_A = 10;
    SPD_B = 10;    
  }

  else
  {
    SPD_A = 0;
    SPD_B = 0;
  }
}
