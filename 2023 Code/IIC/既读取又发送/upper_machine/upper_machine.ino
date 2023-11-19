#include <Wire.h>
 
void setup()
{
    // Wire初始化, 加入i2c总线
    // 如果未指定，则以主机身份加入总线。
    Wire.begin();//主机
    Serial.begin(9600);
}
 
// 定义一个byte变量以便串口调试
byte x = 0;
 
void loop()
{
    Wire.requestFrom(8, 1);
    while (Wire.available())
    {
        // 接受并读取从设备发来的一个字节的数据
        char c = Wire.read();
        // 向串口打印该字节
        Serial.println(c);
    }
    // 延时500毫秒
    delay(50);
    
    // 将数据传送到从设备＃8
    Wire.beginTransmission(8);
//    // 发送5个字节
//    Wire.write("x is ");
    // 发送一个字节
    Wire.write(x);
    // 停止传送
    Wire.endTransmission();
 
    x++;
    delay(50);
}
