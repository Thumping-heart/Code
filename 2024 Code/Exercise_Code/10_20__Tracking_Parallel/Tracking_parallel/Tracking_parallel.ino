#include "Wheel__1_0.hpp"

bool Sensor_Left_Data[9] = {0};//左侧传感器
bool Sensor_Right_Data[9] = {0};//右侧传感器

//存放轮子的PWM值
int SPD_A = 0;
int SPD_B = 0;
int SPD_C = 0;
int SPD_D = 0;
int SPD_ALL = 0;

void setup() {
  // put your setup code here, to run once:
  Init_Wheel();
  //初始化传感器IIC通信
}

void loop() {
  // put your main code here, to run repeatedly:
  //读取传感器的数据
  Sensor_Front_Program();//修正左侧的轮子 DC
  Sensor_Rear_Program();//修正右侧的轮子 AB
  MA_SPD(SPD_A+SPD_ALL);
  MB_SPD(SPD_B+SPD_ALL); 
  MC_SPD(SPD_C+SPD_ALL);
  MD_SPD(SPD_D+SPD_ALL);
}

//修正车姿态
void Sensor_Front_Program()//修正左侧的轮子 DC
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

void Sensor_Rear_Program()//修正右侧的轮子 AB
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
