#include "Wheel__1_0.hpp"

//传感器引脚
//前
#define Sensor_1_Front 22
#define Sensor_2_Front 24
#define Sensor_3_Front 26
#define Sensor_4_Front 28
#define Sensor_5_Front 10
#define Sensor_6_Front 23
#define Sensor_7_Front 25
#define Sensor_8_Front 27
//后
#define Sensor_1_Rear 29
#define Sensor_2_Rear 39
#define Sensor_3_Rear 46
#define Sensor_4_Rear 45
#define Sensor_5_Rear 44
#define Sensor_6_Rear A10
#define Sensor_7_Rear 10
#define Sensor_8_Rear 9

//存传感器数据
bool Sensor_Front_Data[9] = {0};//前方传感器
bool Sensor_Rear_Data[9] = {0};//后方传感器

//存放轮子的PWM值
int SPD_A = 0;
int SPD_B = 0;
int SPD_C = 0;
int SPD_D = 0;
int SPD_ALL = -80;

/*
 * 逻辑：前方的控制前方两个轮子 DA
 *      后方的控制后方两个轮子 CB
 * 说明：相比于10_18__Optimize1_0__complete版，修改了判断优先级判断,使用了不同的PWM值做修正，增加了直行
 * 
 */

void setup() {
  // put your setup code here, to run once:
  Init_Wheel();
  Init_Sensor();
  Serial.begin(110200);
}

void loop() {
  // put your main code here, to run repeatedly:
  Read_Sensor();
  Print_Sensor();  //1是检测到白线

  Sensor_Front_Program();//修正前方的轮子 DA
  Sensor_Rear_Program();//修正后方的轮子 CB

  MA_SPD(SPD_A+SPD_ALL);
  MB_SPD(SPD_B+SPD_ALL); 
  MC_SPD(SPD_C+SPD_ALL);
  MD_SPD(SPD_D+SPD_ALL);
}

//修正车姿态
void Sensor_Front_Program()//修正前方的轮子 DA
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

void Sensor_Rear_Program()//修正后方的轮子 CB
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

//传感器部分
void Init_Sensor()
{
  pinMode(Sensor_1_Front, INPUT_PULLUP);  
  pinMode(Sensor_2_Front, INPUT_PULLUP);
  pinMode(Sensor_3_Front, INPUT_PULLUP);
  pinMode(Sensor_4_Front, INPUT_PULLUP);
  pinMode(Sensor_5_Front, INPUT_PULLUP);
  pinMode(Sensor_6_Front, INPUT_PULLUP);
  pinMode(Sensor_7_Front, INPUT_PULLUP);
  pinMode(Sensor_8_Front, INPUT_PULLUP);
  
  pinMode(Sensor_1_Rear, INPUT_PULLUP);  
  pinMode(Sensor_2_Rear, INPUT_PULLUP);
  pinMode(Sensor_3_Rear, INPUT_PULLUP);
  pinMode(Sensor_4_Rear, INPUT_PULLUP);
  pinMode(Sensor_5_Rear, INPUT_PULLUP);
  pinMode(Sensor_6_Rear, INPUT_PULLUP);
  pinMode(Sensor_7_Rear, INPUT_PULLUP);
  pinMode(Sensor_8_Rear, INPUT_PULLUP);  
}

void Read_Sensor()
{
    Sensor_Front_Data[1] = digitalRead(Sensor_1_Front);
    Sensor_Front_Data[2] = digitalRead(Sensor_2_Front);
    Sensor_Front_Data[3] = digitalRead(Sensor_3_Front);
    Sensor_Front_Data[4] = digitalRead(Sensor_4_Front);
    Sensor_Front_Data[5] = digitalRead(Sensor_5_Front);
    Sensor_Front_Data[6] = digitalRead(Sensor_6_Front);
    Sensor_Front_Data[7] = digitalRead(Sensor_7_Front);
    Sensor_Front_Data[8] = digitalRead(Sensor_8_Front);

    Sensor_Rear_Data[1] = digitalRead(Sensor_1_Rear);
    Sensor_Rear_Data[2] = digitalRead(Sensor_2_Rear);
    Sensor_Rear_Data[3] = digitalRead(Sensor_3_Rear);
    Sensor_Rear_Data[4] = digitalRead(Sensor_4_Rear);
    Sensor_Rear_Data[5] = digitalRead(Sensor_5_Rear);
    Sensor_Rear_Data[6] = digitalRead(Sensor_6_Rear);
    Sensor_Rear_Data[7] = digitalRead(Sensor_7_Rear);
    Sensor_Rear_Data[8] = digitalRead(Sensor_8_Rear);
}

void Print_Sensor()
{
  Serial.print("Front:");
  Serial.print(Sensor_Front_Data[1]);
  Serial.print(Sensor_Front_Data[2]);  
  Serial.print(Sensor_Front_Data[3]);
  Serial.print(Sensor_Front_Data[4]);
  Serial.print(Sensor_Front_Data[5]);
  Serial.print(Sensor_Front_Data[6]);
  Serial.print(Sensor_Front_Data[7]);
  Serial.print(Sensor_Front_Data[8]);

  Serial.print("  ");
  Serial.print("Rear:");
  Serial.print(Sensor_Rear_Data[1]);
  Serial.print(Sensor_Rear_Data[2]);  
  Serial.print(Sensor_Rear_Data[3]);
  Serial.print(Sensor_Rear_Data[4]);
  Serial.print(Sensor_Rear_Data[5]);
  Serial.print(Sensor_Rear_Data[6]);
  Serial.print(Sensor_Rear_Data[7]);
  Serial.println(Sensor_Rear_Data[8]);  
}

//轮子部分
void Init_Wheel()
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
