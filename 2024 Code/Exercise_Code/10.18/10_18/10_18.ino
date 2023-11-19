#include "MCtrl.hpp"


//前
//#define Sensor_1 22
//#define Sensor_2 24
//#define Sensor_3 26
//#define Sensor_4 28
//#define Sensor_5 30
//#define Sensor_6 23
//#define Sensor_7 25
//#define Sensor_8 27

//后
#define Sensor_1 29
#define Sensor_2 39
#define Sensor_3 46
#define Sensor_4 45
#define Sensor_5 44
#define Sensor_6 A15
#define Sensor_7 10
#define Sensor_8 9



bool Sensor_Data[9] = {0};//存传感器数据

void setup() {
  // put your setup code here, to run once:
  Init_Wheel();
  Init_Sensor();
  Serial.begin(9600);
}


void loop() {
  // put your main code here, to run repeatedly:

  Read_Sensor();
  Print_Sensor();

  //1是踩线


  if(Sensor_Data[1] == 1 || Sensor_Data[2] == 1 || Sensor_Data[3] == 1)//左移
  {
//        //左移 前传感器
//  MA_SPD(60);
//  MB_SPD(-60);
//  MC_SPD(60);
//  MD_SPD(-60);

    MA_SPD(-60);
  MB_SPD(60);
  MC_SPD(-60);
  MD_SPD(60);
  }
  else if(Sensor_Data[8] == 1 || Sensor_Data[7] == 1 || Sensor_Data[6] == 1)//右移
  {
//      //右移 前传感器
//  MA_SPD(-60);
//  MB_SPD(60);
//  MC_SPD(-60);
//  MD_SPD(60); 

    MA_SPD(60);
  MB_SPD(-60);
  MC_SPD(60);
  MD_SPD(-60);
  }
  else
  {
     MA_SPD(0);
  MB_SPD(0);
  MC_SPD(0);
  MD_SPD(0);  
  }
  
  //左移
//  MA_SPD(60);
//  MB_SPD(-60);
//  MC_SPD(60);
//  MD_SPD(-60);

//  //右移
//  MA_SPD(-60);
//  MB_SPD(60);
//  MC_SPD(-60);
//  MD_SPD(60); 
}

//传感器部分
void Init_Sensor()
{
  pinMode(Sensor_1, INPUT_PULLUP);  
  pinMode(Sensor_2, INPUT_PULLUP);
  pinMode(Sensor_3, INPUT_PULLUP);
  pinMode(Sensor_4, INPUT_PULLUP);
  pinMode(Sensor_5, INPUT_PULLUP);
  pinMode(Sensor_6, INPUT_PULLUP);
  pinMode(Sensor_7, INPUT_PULLUP);
  pinMode(Sensor_8, INPUT_PULLUP);
}

void Read_Sensor()
{
    Sensor_Data[1] = digitalRead(Sensor_1);
    Sensor_Data[2] = digitalRead(Sensor_2);
    Sensor_Data[3] = digitalRead(Sensor_3);
    Sensor_Data[4] = digitalRead(Sensor_4);
    Sensor_Data[5] = digitalRead(Sensor_5);
    Sensor_Data[6] = digitalRead(Sensor_6);
    Sensor_Data[7] = digitalRead(Sensor_7);
    Sensor_Data[8] = digitalRead(Sensor_8);
}

void Print_Sensor()
{
  Serial.print(Sensor_Data[1]);
  Serial.print(Sensor_Data[2]);  
  Serial.print(Sensor_Data[3]);
  Serial.print(Sensor_Data[4]);
  Serial.print(Sensor_Data[5]);
  Serial.print(Sensor_Data[6]);
  Serial.print(Sensor_Data[7]);
  Serial.println(Sensor_Data[8]);
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
