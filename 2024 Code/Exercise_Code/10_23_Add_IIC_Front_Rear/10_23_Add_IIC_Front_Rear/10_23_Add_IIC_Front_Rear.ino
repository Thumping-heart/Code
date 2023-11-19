#include <Wire.h>//用于IIC通信
#include "Wheel__1_0.hpp"//轮子的底层文件
#include "gw_grayscale_sensor.h"//传感器有关的头文件

//传感器从机的地址
//说明：前0 后1 左2 右3
#define Gray_Sensor_Addr_0 0x4C //编号0
#define Gray_Sensor_Addr_1 0x4D //编号1
#define Gray_Sensor_Addr_2 0x4E //编号2
#define Gray_Sensor_Addr_3 0x4F //编号3

//存传感器数据
bool Sensor_Front_Data[9] = {0};//前方传感器
bool Sensor_Rear_Data[9] = {0};//后方传感器
bool Sensor_Left_Data[9] = {0};//左侧传感器
bool Sensor_Right_Data[9] = {0};//右侧传感器

//存放轮子的PWM值
int SPD_A = 0;
int SPD_B = 0;
int SPD_C = 0;
int SPD_D = 0;

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
  
  Left_Shift(60);
  
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

void Init_READ_Digital_Sensor()//初始化 IIC读取数字量的数据
{
  Wire.beginTransmission(Gray_Sensor_Addr_0);
  Wire.write(GW_GRAY_DIGITAL_MODE);
  Wire.endTransmission();

  Wire.beginTransmission(Gray_Sensor_Addr_1);
  Wire.write(GW_GRAY_DIGITAL_MODE);
  Wire.endTransmission();

  Wire.beginTransmission(Gray_Sensor_Addr_2);
  Wire.write(GW_GRAY_DIGITAL_MODE);
  Wire.endTransmission();

  Wire.beginTransmission(Gray_Sensor_Addr_3);
  Wire.write(GW_GRAY_DIGITAL_MODE);
  Wire.endTransmission(); 
}

void Read_Sensor()//IIC读取数字量的数据
{
  uint8_t recv_value = 0;
  Wire.requestFrom(Gray_Sensor_Addr_0, 1);
  recv_value = Wire.read();
  SEP_ALL_BIT8(recv_value, Sensor_Front_Data[1], Sensor_Front_Data[2], Sensor_Front_Data[3], Sensor_Front_Data[4],
                 Sensor_Front_Data[5], Sensor_Front_Data[6], Sensor_Front_Data[7], Sensor_Front_Data[8]);
    
  Wire.requestFrom(Gray_Sensor_Addr_1, 1);
  recv_value = Wire.read();
  SEP_ALL_BIT8(recv_value, Sensor_Rear_Data[1], Sensor_Rear_Data[2], Sensor_Rear_Data[3], Sensor_Rear_Data[4],
                 Sensor_Rear_Data[5], Sensor_Rear_Data[6], Sensor_Rear_Data[7], Sensor_Rear_Data[8]);
                 
  Wire.requestFrom(Gray_Sensor_Addr_2, 1);
  recv_value = Wire.read();
  SEP_ALL_BIT8(recv_value, Sensor_Left_Data[1], Sensor_Left_Data[2], Sensor_Left_Data[3], Sensor_Left_Data[4],
                 Sensor_Left_Data[5], Sensor_Left_Data[6], Sensor_Left_Data[7], Sensor_Left_Data[8]);
    
  Wire.requestFrom(Gray_Sensor_Addr_3, 1);
  recv_value = Wire.read();
  SEP_ALL_BIT8(recv_value, Sensor_Right_Data[1], Sensor_Right_Data[2], Sensor_Right_Data[3], Sensor_Right_Data[4],
                 Sensor_Right_Data[5], Sensor_Right_Data[6], Sensor_Right_Data[7], Sensor_Right_Data[8]);
}

void Print_Sensor()//打印传感器的数据
{
    Serial.print("Addr_0:");
    for (int i = 1; i <= 8; ++i) {  
      Serial.print(" ");
      Serial.print(Sensor_Front_Data[i]);
    }
    Serial.print("  ");

    Serial.print("Addr_1:");
    for (int i = 1; i <= 8; ++i) {  
      Serial.print(" ");
      Serial.print(Sensor_Rear_Data[i]);
    }
    Serial.print("  ");
    
    Serial.print("Addr_2:");
    for (int i = 1; i <= 8; ++i) {  
      Serial.print(" ");
      Serial.print(Sensor_Left_Data[i]);
    }
    Serial.print("  ");
       
    Serial.print("Addr_3:");
    for (int i = 1; i <= 8; ++i) {  
      Serial.print(" ");
      Serial.print(Sensor_Right_Data[i]);
    }
    Serial.print("  ");

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
