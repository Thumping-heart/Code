#include "gw_grayscale_sensor.h"
#include <Wire.h>
#define GW_GRAY_ADDR GW_GRAY_ADDR_DEF // 使用默认地址
uint8_t recv_value = 0;

void setup()
{
  Wire.begin();

  Serial.begin(115200);
  while (!Serial);             // Leonardo: wait for serial monitor
  Serial.println("I2C Scanner");
}
 


void loop()
{
   Wire.beginTransmission(0x70);
   Wire.write(0x01);
   Wire.endTransmission();

   Wire.requestFrom(GW_GRAY_ADDR, 1);
   recv_value = Wire.read();
   Serial.print("Data_0:");
   for (int i = 1; i <= 8; ++i) {  //探头从1开始,不是0
     Serial.print(" ");
     Serial.print(GET_NTH_BIT(recv_value, i));
   }

   Wire.beginTransmission(0x70);
   Wire.write(0x02);
   Wire.endTransmission();
   
   Wire.requestFrom(GW_GRAY_ADDR, 1);
   recv_value = Wire.read();
   Serial.print("Data_1:");
   for (int i = 1; i <= 8; ++i) {  //探头从1开始,不是0
     Serial.print(" ");
     Serial.print(GET_NTH_BIT(recv_value, i));
   }
    
    Wire.beginTransmission(0x70);
    Wire.write(0x04);
    Wire.endTransmission();

    Wire.requestFrom(GW_GRAY_ADDR_DEF, 1);
    recv_value = Wire.read();
    Serial.print("Data_2:");
    for (int i = 1; i <= 8; ++i) {  //探头从1开始,不是0
      Serial.print(" ");
      Serial.print(GET_NTH_BIT(recv_value, i));
    }

    Wire.beginTransmission(0x70);
    Wire.write(0x08);
    Wire.endTransmission();
    
    Wire.requestFrom(GW_GRAY_ADDR_DEF, 1);
    recv_value = Wire.read();
    Serial.print("Data_3:");
    for (int i = 1; i <= 8; ++i) {  //探头从1开始,不是0
      Serial.print(" ");
      Serial.print(GET_NTH_BIT(recv_value, i));
    }
    
    Serial.print("\n");
    
} 
