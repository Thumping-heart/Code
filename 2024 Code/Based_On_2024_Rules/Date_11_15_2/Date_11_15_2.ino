#include <Wire.h>
#include "gw_grayscale_sensor.h"
#include "Wheel__1_0.hpp"
#include <Wire.h>
#define GW_GRAY_ADDR GW_GRAY_ADDR_DEF // 传感器地址0X4C

//存传感器数据
bool Sensor_Left_up_Data[9] = {0};//左上方传感器 0
bool Sensor_Left_down_Data[9] = {0};//左下方传感器 1
bool Sensor_Right_up_Data[9] = {0};//右上方传感器 2
bool Sensor_Right_down_Data[9] = {0};//右下方传感器 3

//存放轮子的PWM值
int SPD_A = 0;
int SPD_B = 0;
int SPD_C = 0;
int SPD_D = 0;
int SPD_ALL = 0;

void setup()
{
  Wire.begin();
  Serial.begin(115200);
  while (!Serial);             // Leonardo: wait for serial monitor
  Init_Wheel();
}

void loop()
{
  Read_Left_Digital_Sensor();
  Print_Left_Digital_Sensor();

  Move_Left_Up(60);
//  Move_Right_Up(60);
}


/*==========================寻迹修正部分============================*/
void Move_Left_Up(int Right_Up_SPD)//当>0时右上移动，当<0时右下
{
  //右上通过左侧的传感器修正
  Sensor_Right_up_Program();
  Sensor_Right_down_Program();
  
  MA_SPD(SPD_A+Right_Up_SPD);
  MB_SPD(SPD_B); 
  MC_SPD(SPD_C+Right_Up_SPD);
  MD_SPD(SPD_D);
}

void Move_Right_Up(int Left_Up_SPD)//当>0时左上移动，当<0时左下
{
  //左上通过右侧的传感器修正
  Sensor_Left_up_Program();
  Sensor_Left_down_Program();
    
  MA_SPD(SPD_A);
  MB_SPD(SPD_B+Left_Up_SPD); 
  MC_SPD(SPD_C);
  MD_SPD(SPD_D+Left_Up_SPD);
}

//左上侧传感器修正车的姿态
void Sensor_Left_up_Program()
{
  //控制逻辑：左上侧传感器0 控制AD轮子 左下侧传感器1 控制BC轮子 
  if(Sensor_Left_up_Data[1] == 1)
  {
    SPD_A = 60;
    SPD_D = -60;
  }
  else if(Sensor_Left_up_Data[8] == 1)
  {
    SPD_A = -60;
    SPD_D = 60;
  }
  
  else if(Sensor_Left_up_Data[2] == 1)
  {
    SPD_A = 40;
    SPD_D = -40;
  }
  else if(Sensor_Left_up_Data[7] == 1)
  {
    SPD_A = -40;
    SPD_D = 40;
  }
  
  else if(Sensor_Left_up_Data[3] == 1)
  {
    SPD_A = 10;
    SPD_D = -10;
  }  
  else if(Sensor_Left_up_Data[6] == 1)
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

//左下侧传感器修正车的姿态
void Sensor_Left_down_Program()
{
  //控制逻辑：左上侧传感器0 控制AD轮子 左下侧传感器1 控制BC轮子 
  if(Sensor_Left_down_Data[1] == 1)
  {
    SPD_B = 60;
    SPD_C = -60;
  }
  else if(Sensor_Left_down_Data[8] == 1)
  {
    SPD_B = -60;
    SPD_C = 60;
  }
  else if(Sensor_Left_down_Data[2] == 1)
  {
    SPD_B = 40;
    SPD_C = -40;
  }
  else if(Sensor_Left_down_Data[7] == 1)
  {
    SPD_B = -40;
    SPD_C = 40;
  }
  else if(Sensor_Left_down_Data[3] == 1)
  {
    SPD_B = 10;
    SPD_C = -10;
  }  
  else if(Sensor_Left_down_Data[6] == 1)
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

//右上侧传感器修正车的姿态
void Sensor_Right_up_Program()
{
  //控制逻辑：右上侧传感器2 控制AD轮子 右下侧传感器3 控制BC轮子 
  if(Sensor_Right_up_Data[1] == 1)
  {
    SPD_A = 80;
    SPD_D = -80;
  }
  else if(Sensor_Right_up_Data[8] == 1)
  {
    SPD_A = -80;
    SPD_D = 80;
  }
  
  else if(Sensor_Right_up_Data[2] == 1)
  {
    SPD_A = 60;
    SPD_D = -60;
  }
  else if(Sensor_Right_up_Data[7] == 1)
  {
    SPD_A = -60;
    SPD_D = 60;
  }
  
  else if(Sensor_Right_up_Data[3] == 1)
  {
    SPD_A = 30;
    SPD_D = -30;
  }  
  else if(Sensor_Right_up_Data[6] == 1)
  {
    SPD_A = -30;
    SPD_D = 30;
  }
  else
  {
    SPD_A = 0;
    SPD_D = 0; 
  }
}

//右下侧传感器修正车的姿态
void Sensor_Right_down_Program()
{
  //控制逻辑：右上侧传感器2 控制AD轮子 右下侧传感器3 控制BC轮子  
  if(Sensor_Right_down_Data[1] == 1)
  {
    SPD_B = 60;
    SPD_C = -60;
  }
  else if(Sensor_Right_down_Data[8] == 1)
  {
    SPD_B = -60;
    SPD_C = 60;
  }
  else if(Sensor_Right_down_Data[2] == 1)
  {
    SPD_B = 40;
    SPD_C = -40;
  }
  else if(Sensor_Right_down_Data[7] == 1)
  {
    SPD_B = -40;
    SPD_C = 40;
  }
  else if(Sensor_Right_down_Data[3] == 1)
  {
    SPD_B = 10;
    SPD_C = -10;
  }  
  else if(Sensor_Right_down_Data[6] == 1)
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

/*==========================传感器数据部分============================*/
void Read_Left_Digital_Sensor()//获取传感器的数据
{
  uint8_t recv_value = 0;
  Wire.beginTransmission(0x70);
  Wire.write(0x01);
  Wire.endTransmission();
  Wire.requestFrom(GW_GRAY_ADDR, 1);
  recv_value = Wire.read();
  SEP_ALL_BIT8(recv_value, Sensor_Left_up_Data[1], Sensor_Left_up_Data[2], Sensor_Left_up_Data[3], Sensor_Left_up_Data[4],
                 Sensor_Left_up_Data[5], Sensor_Left_up_Data[6], Sensor_Left_up_Data[7], Sensor_Left_up_Data[8]);

  Wire.beginTransmission(0x70);
  Wire.write(0x02);
  Wire.endTransmission();
  Wire.requestFrom(GW_GRAY_ADDR, 1);
  recv_value = Wire.read();
  SEP_ALL_BIT8(recv_value, Sensor_Left_down_Data[1], Sensor_Left_down_Data[2], Sensor_Left_down_Data[3], Sensor_Left_down_Data[4],
                 Sensor_Left_down_Data[5], Sensor_Left_down_Data[6], Sensor_Left_down_Data[7], Sensor_Left_down_Data[8]);

   Wire.beginTransmission(0x70);
   Wire.write(0x04);
   Wire.endTransmission();
   Wire.requestFrom(GW_GRAY_ADDR_DEF, 1);
   recv_value = Wire.read();
   SEP_ALL_BIT8(recv_value, Sensor_Right_up_Data[1], Sensor_Right_up_Data[2], Sensor_Right_up_Data[3], Sensor_Right_up_Data[4],
                 Sensor_Right_up_Data[5], Sensor_Right_up_Data[6], Sensor_Right_up_Data[7], Sensor_Right_up_Data[8]);

   Wire.beginTransmission(0x70);
   Wire.write(0x08);
   Wire.endTransmission();
   Wire.requestFrom(GW_GRAY_ADDR_DEF, 1);
   recv_value = Wire.read();
   SEP_ALL_BIT8(recv_value, Sensor_Right_down_Data[1], Sensor_Right_down_Data[2], Sensor_Right_down_Data[3], Sensor_Right_down_Data[4],
                 Sensor_Right_down_Data[5], Sensor_Right_down_Data[6], Sensor_Right_down_Data[7], Sensor_Right_down_Data[8]);
}

void Print_Left_Digital_Sensor()//串口打印传感器的数据
{
   Serial.print("Data_0:");
   for (int i = 1; i <= 8; ++i) {  //探头从1开始,不是0
     Serial.print(" ");
     Serial.print(Sensor_Left_up_Data[i]);
   }
   
   Serial.print("Data_1:");
   for (int i = 1; i <= 8; ++i) {  
     Serial.print(" ");
     Serial.print(Sensor_Left_down_Data[i]);
   }
   
   Serial.print("Data_2:");
   for (int i = 1; i <= 8; ++i) {  
     Serial.print(" ");
     Serial.print(Sensor_Right_up_Data[i]);
   }

   Serial.print("Data_3:");
   for (int i = 1; i <= 8; ++i) {  
     Serial.print(" ");
     Serial.print(Sensor_Right_down_Data[i]);
   }

   Serial.print("\n");
}


void Init_Wheel()//轮子初始化部分
{
  pinMode(MA_EN, OUTPUT);
  pinMode(MA_FWD, OUTPUT);
  pinMode(MA_REV, OUTPUT);
  pinMode(MB_EN, OUTPUT);
  pinMode(MB_FWD, OUTPUT);
  pinMode(MB_REV, OUTPUT);
  pinMode(MC_EN, OUTPUT);
  pinMode(MC_FWD, OUTPUT);
  pinMode(MC_REV, OUTPUT);
  pinMode(MD_EN, OUTPUT);
  pinMode(MD_FWD, OUTPUT);
  pinMode(MD_REV, OUTPUT);
}
