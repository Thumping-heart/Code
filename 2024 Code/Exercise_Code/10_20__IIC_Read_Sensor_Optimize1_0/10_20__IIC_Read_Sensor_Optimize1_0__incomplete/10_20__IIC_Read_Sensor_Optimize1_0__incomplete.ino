#include <Wire.h>
#include "gw_grayscale_sensor.h"//传感器有关的头文件

/*
 * 优化说明：只读取编号2和3的数据，这个两个传感器贴在车的两侧
 * 
 */

//传感器从机的地址 
#define Gray_Sensor_Addr_0 0x4C //编号0
#define Gray_Sensor_Addr_1 0x4D //编号1
#define Gray_Sensor_Addr_2 0x4E //编号2
#define Gray_Sensor_Addr_3 0x4F //编号3

bool Sensor_Left_Data[9] = {0};//左侧传感器
bool Sensor_Right_Data[9] = {0};//右侧传感器

void setup() {
  Wire.begin();
  Init_READ_Digital_Sensor();//初始化 读取数字量的数据
  Serial.begin(115200);
}

void loop() {
    Read_Sensor();
    Print_Sensor();
}

void Init_READ_Digital_Sensor()//初始化 读取数字量的数据
{
//  Wire.beginTransmission(Gray_Sensor_Addr_0);
//  Wire.write(GW_GRAY_DIGITAL_MODE);
//  Wire.endTransmission();
//
//  Wire.beginTransmission(Gray_Sensor_Addr_1);
//  Wire.write(GW_GRAY_DIGITAL_MODE);
//  Wire.endTransmission();

  Wire.beginTransmission(Gray_Sensor_Addr_2);
  Wire.write(GW_GRAY_DIGITAL_MODE);
  Wire.endTransmission();

  Wire.beginTransmission(Gray_Sensor_Addr_3);
  Wire.write(GW_GRAY_DIGITAL_MODE);
  Wire.endTransmission(); 
}

void Read_Sensor()
{
  uint8_t recv_value = 0;
  Wire.requestFrom(Gray_Sensor_Addr_2, 1);
  recv_value = Wire.read();
  SEP_ALL_BIT8(recv_value, Sensor_Left_Data[1], Sensor_Left_Data[2], Sensor_Left_Data[3], Sensor_Left_Data[4],
                 Sensor_Left_Data[5], Sensor_Left_Data[6], Sensor_Left_Data[7], Sensor_Left_Data[8]);
    
  Wire.requestFrom(Gray_Sensor_Addr_3, 1);
  recv_value = Wire.read();
  SEP_ALL_BIT8(recv_value, Sensor_Right_Data[1], Sensor_Right_Data[2], Sensor_Right_Data[3], Sensor_Right_Data[4],
                 Sensor_Right_Data[5], Sensor_Right_Data[6], Sensor_Right_Data[7], Sensor_Right_Data[8]);
}

void Print_Sensor()
{    
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
