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
int SETSPEED = 150;//设定的速度
int MA_P;
int MB_P;
int MC_P;
int MD_P;
float old_angle;//上一次的角度读取角度
void displaySensorDetails(void)
{
  sensor_t sensor;
  mag.getSensor(&sensor);
  Serial.println("------------------------------------");
  Serial.print  ("Sensor:       "); Serial.println(sensor.name);
  Serial.print  ("Driver Ver:   "); Serial.println(sensor.version);
  Serial.print  ("Unique ID:    "); Serial.println(sensor.sensor_id);
  Serial.print  ("Max Value:    "); Serial.print(sensor.max_value); Serial.println(" uT");
  Serial.print  ("Min Value:    "); Serial.print(sensor.min_value); Serial.println(" uT");
  Serial.print  ("Resolution:   "); Serial.print(sensor.resolution); Serial.println(" uT");  
  Serial.println("------------------------------------");
  Serial.println("");
  delay(500);
}

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

  Serial.begin(9600);
  Serial.println("HMC5883 Magnetometer Test"); Serial.println("");
  
  if(!mag.begin())
  {
    Serial.println("Ooops, no HMC5883 detected ... Check your wiring!");
    while(1);
  }
  displaySensorDetails();

  old_angle = read_angele();//
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
  return headingDegrees;
  Serial.print("Heading (degrees): "); Serial.println(headingDegrees);
  
  delay(10);
  
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
  setpoint = 100;//设定的角度
  input = read_angele();//实施读取的角度

  PID1.Compute();
  AUTO_temp = output;
  if(AUTO_temp > 255) AUTO_temp = 255;
  else if(AUTO_temp < -255) AUTO_temp = -255;
  
  move_rightLeft(SETSPEED);
//   move_frontBack(SETSPEED);       
  MA_SPD(MA_P);
  MB_SPD(MB_P);
  MC_SPD(MC_P);
  MD_SPD(MD_P);
}
