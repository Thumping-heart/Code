#include <Wire.h>
#include "gw_grayscale_sensor.h"

// SDA : A4
// SCL : A5

//从机的地址 
#define Gray_Sensor_Addr_0 0x4C //编号0
#define Gray_Sensor_Addr_1 0x4D //编号1
#define Gray_Sensor_Addr_2 0x4E //编号2
#define Gray_Sensor_Addr_3 0x4F //编号3

void setup() {
  Wire.begin();
  Serial.begin(115200);
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW);
}

void loop() {
  uint8_t recv_value = 0;
  uint8_t Ping_Addr_0 = 0,Ping_Addr_1 = 0,Ping_Addr_2 = 0,Ping_Addr_3 = 0;
  uint8_t sensor1, sensor2, sensor3, sensor4, sensor5, sensor6, sensor7, sensor8;

  // 循环 直到PING成功 PING4个传感器
  while (Ping_Addr_0 != GW_GRAY_PING_OK && Ping_Addr_1 != GW_GRAY_PING_OK &&
         Ping_Addr_2 != GW_GRAY_PING_OK && Ping_Addr_3 != GW_GRAY_PING_OK) {
    Wire.beginTransmission(Gray_Sensor_Addr_0);
    Wire.write(GW_GRAY_PING);
    Wire.endTransmission();
    Wire.requestFrom(Gray_Sensor_Addr_0, 1);
    Ping_Addr_0 = Wire.read();
    delay(10);

    Wire.beginTransmission(Gray_Sensor_Addr_1);
    Wire.write(GW_GRAY_PING);
    Wire.endTransmission();
    Wire.requestFrom(Gray_Sensor_Addr_1, 1);
    Ping_Addr_1 = Wire.read();
    delay(10);    

    Wire.beginTransmission(Gray_Sensor_Addr_2);
    Wire.write(GW_GRAY_PING);
    Wire.endTransmission();
    Wire.requestFrom(Gray_Sensor_Addr_2, 1);
    Ping_Addr_2 = Wire.read();
    delay(10); 

    Wire.beginTransmission(Gray_Sensor_Addr_3);
    Wire.write(GW_GRAY_PING);
    Wire.endTransmission();
    Wire.requestFrom(Gray_Sensor_Addr_3, 1);
    Ping_Addr_3 = Wire.read();
    delay(10); 
  }
  
  /* ping 成功 */

  /* 数字数据模式, 设置完毕之后, 每次读取一个8bit的数据, 每个位表示1-8探头的状态 */
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

  // 打印8个探头的状态
  while (1) {
    Wire.requestFrom(Gray_Sensor_Addr_0, 1);
    recv_value = Wire.read();
    Serial.print("Addr_0:");
    for (int i = 1; i <= 8; ++i) {  //探头从1开始,不是0
      Serial.print(" ");
      Serial.print(GET_NTH_BIT(recv_value, i));
    }
    Serial.print("  ");
//    delay(10);

    Wire.requestFrom(Gray_Sensor_Addr_1, 1);
    recv_value = Wire.read();
    Serial.print("Addr_1:");
    for (int i = 1; i <= 8; ++i) {  
      Serial.print(" ");
      Serial.print(GET_NTH_BIT(recv_value, i));
    }
    Serial.print("  ");
//    delay(10);

    Wire.requestFrom(Gray_Sensor_Addr_2, 1);
    recv_value = Wire.read();
    Serial.print("Addr_2:");
    for (int i = 1; i <= 8; ++i) {  
      Serial.print(" ");
      Serial.print(GET_NTH_BIT(recv_value, i));
    }
    Serial.print("  ");
//    delay(10);

    Wire.requestFrom(Gray_Sensor_Addr_3, 1);
    recv_value = Wire.read();
    Serial.print("Addr_3:");
    for (int i = 1; i <= 8; ++i) {  
      Serial.print(" ");
      Serial.print(GET_NTH_BIT(recv_value, i));
    }
    Serial.print("  ");
//    delay(10);
    Serial.print("\n");
    
  }
}
