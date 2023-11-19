#ifndef IIC_GRAYSCALE_SENSOR__1_0_H_
#define IIC_GRAYSCALE_SENSOR__1_0_H_

//传感器从机的地址
//说明：前0 后1 左2 右3
#define Gray_Sensor_Addr_0 0x4C //编号0
#define Gray_Sensor_Addr_1 0x4D //编号1
#define Gray_Sensor_Addr_2 0x4E //编号2
#define Gray_Sensor_Addr_3 0x4F //编号3

//存传感器数据
extern int Sensor_Front_Data[9] = {0};//前方传感器  0
extern int Sensor_Rear_Data[9] = {0};//后方传感器   1
extern int Sensor_Left_Data[9] = {0};//左侧传感器   2
extern int Sensor_Right_Data[9] = {0};//右侧传感器  3

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


#endif
