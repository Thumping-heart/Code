#include "MCtrl.hpp"
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_HMC5883_U.h>

Adafruit_HMC5883_Unified mag = Adafruit_HMC5883_Unified(12345);


#include <PID_v1.h>
double kp = 1.5, ki = 0, kd = 0; //p比系数i积系数d微系数PID运算器精度设置
double input = 0, output = 0, setpoint = 0;
PID PID1(&input, &output, &setpoint, kp, ki, kd, DIRECT);

int AUTO_temp;//差值中转量


int SETSPEED =  50;//设定的速度


int MA_P;
int MB_P;
int MC_P;
int MD_P;
float curr_angle;//当前读取角度
float set_angle = 290;//设定到达角度
int Init = 1;//用于初始化
int angle_last = 180,step_curr=0,lap_curr=0,angle_curr,first_angle;//a:上一次的角度值
long t;
float outR = 0;//返回的角度

//屏幕部分
#include <Adafruit_SSD1306.h> //屏幕库

#define SCREEN_WIDTH 128 //屏幕像素X
#define SCREEN_HEIGHT 64 //屏幕像素Y

#define SCREEN_ADDRESS 0x3C //屏幕i2c地址
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire); //配置屏幕
long S;


void setup() {
  // put your setup code here, to run once:
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

  PID1.SetMode(AUTOMATIC);
  PID1.SetSampleTime(1);
  PID1.SetOutputLimits(-150, 150);

  Serial.begin(115200);
  if(!mag.begin())
  {
    while(1);
  }
  delay(500);

  //屏幕显示
  Wire.begin(1); //初始化i2c
  display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS); //初始化屏幕
  display.setTextColor(SSD1306_WHITE);
  display.setRotation(2);
  display.clearDisplay();     //清屏
  display.display();          //刷新
}


float read_angele()
{
   sensors_event_t event; 
   mag.getEvent(&event);
   float heading = atan2(event.magnetic.y, event.magnetic.x);
  
  float declinationAngle = 0.22;
  heading += declinationAngle;
  
  if(heading < 0)
    heading += 2*PI;

  if(heading > 2*PI)
    heading -= 2*PI;
   
  float headingDegrees = heading * 180/M_PI; 
  if((outR - headingDegrees > 0.5) || (outR - headingDegrees < -0.5))
   {
    outR = headingDegrees;
   }
  //Serial.print("Heading (degrees): "); 
  //Serial.print(outR);
  //Serial.print(headingDegrees);
  //Serial.print("    ");
  return outR;
  
  //return headingDegrees;

  
  //delay(1);
  
}
//==========前进 后退=======================
void move_frontBack(int set_Speed)
{
    MA_P = MC_P = set_Speed + AUTO_temp;
    MB_P = MD_P = set_Speed + (AUTO_temp*-1);  
}
//==========左移 右移=======================
void move_rightLeft(int set_Speed)
{
   //AB为头
   //set_Speed 为正向右 set_Speed 为负向左
   MA_P = set_Speed + AUTO_temp;
   MB_P = (set_Speed * -1) + (AUTO_temp*-1);
   MC_P = (set_Speed * -1) + AUTO_temp;
   MD_P = set_Speed + (AUTO_temp*-1);
}

void loop() 
{
  display_oled();
  if(step_curr==0)
  {
    first_angle = read_angele();
    t = millis();
    setpoint = 0;//设定的角度

    step_curr = 1;
  }

  angle_curr = read_angele();//实施读取的角度
  //delay(10);

  if((angle_curr-angle_last)>180)
  {
    lap_curr = lap_curr-1;
  }
  else if((angle_curr-angle_last)<-180)
  {
    lap_curr = lap_curr+1;
  }
  input=angle_curr+(360*lap_curr)-first_angle;
  
  //Serial.print("--");
  //Serial.println(angle_curr);
  
  Serial.println(input);
  
  angle_last = angle_curr; 
  
  if(millis()-t>2000&&step_curr==1)
  {
    setpoint = 90;
    t=millis();
    step_curr=2;
  }
  else if(millis()-t>2000&&step_curr==2)
  {
    setpoint = 180;
    t=millis();
    step_curr=3;
  }
//  else if(millis()-t>2000&&step_curr==3)
//  {
//    setpoint = 180;
//    t=millis();
//    step_curr=3;
//  }


  
  //Serial.println(t);
  PID1.Compute();
  AUTO_temp = output;
  if(AUTO_temp > 255) AUTO_temp = 255;
  else if(AUTO_temp < -255) AUTO_temp = -255;

  
  //move_rightLeft(SETSPEED);
  if(step_curr != 3)
    move_frontBack(SETSPEED); 
  else
  {
    MA_P = MB_P = MC_P = MD_P = 0;
  }
           
  MA_SPD(MA_P);
  MB_SPD(MB_P);
  MC_SPD(MC_P);
  MD_SPD(MD_P);
 
}

void display_oled()
{
   //屏幕部分
  display.clearDisplay();     //清屏
//=========================================
  display.setTextSize(2);     //字体大小  
  display.setCursor(24, 8);
  display.print("step:"); 
//=========================================
  display.setTextSize(2);     //字体大小
  display.setCursor(95, 8);     //坐标
  display.print(step_curr);           //显示当前运行步骤
//=========================================
  display.setTextSize(2);     //字体大小  
  display.setCursor(18,33);
  display.print("angle:"); 
//=========================================  
  display.setTextSize(2);     //字体大小
  display.setCursor(92,33);     //坐标
  display.print(angle_curr);           //显示当前角度

  display.display();        //刷新  
  
}
