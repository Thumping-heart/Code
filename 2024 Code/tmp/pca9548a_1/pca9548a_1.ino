#include "gw_grayscale_sensor.h"
#include <Wire.h>
#define SDA_PIN 4
#define SLK_PIN 5
 #define GW_GRAY_ADDR GW_GRAY_ADDR_DEF // 使用默认地址
 
void setup()
{
  Wire.begin();
//  Wire.begin(SDA_PIN,SLK_PIN);

 
  Serial.begin(9600);
  while (!Serial);             // Leonardo: wait for serial monitor
  Serial.println("I2C Scanner");
}
 
   uint8_t recv_value = 0;
void loop()
{
  byte error, address;
  int nDevices;
 
  Serial.println("Scanning...");
 
  nDevices = 0;
  for(address = 1; address < 127; address++ )
  {
    // The i2c_scanner uses the return value of
    // the Write.endTransmisstion to see if
    // a device did acknowledge to the address.
    Wire.beginTransmission(address);
    error = Wire.endTransmission();
 
    if (error == 0)
    {
      Serial.print("I2C device found at address 0x");
      if (address<16)
        Serial.print("0");
      Serial.print(address,HEX);
      Serial.println("  !");
 
      nDevices++;
    }
    else if (error==4)
    {
      Serial.print("Unknown error at address 0x");
      if (address<16)
        Serial.print("0");
      Serial.println(address,HEX);
    }    
  }
  if (nDevices == 0)
    Serial.println("No I2C devices found");
  else
  {
    
    Wire.beginTransmission(0x70);
    Wire.write(0x01);
    Wire.endTransmission();
//    Serial.println("done");
//    Serial.println(nDevices);

    Wire.requestFrom(GW_GRAY_ADDR, 1);
    recv_value = Wire.read();
    Serial.print("传感器数字数据:");
    for (int i = 1; i <= 8; ++i) {  //探头从1开始,不是0
      Serial.print(" ");
      Serial.print(GET_NTH_BIT(recv_value, i));
    }
    Serial.print("\n");
  }
  
 
//  delay(2000);           // wait 5 seconds for next scan
} 
