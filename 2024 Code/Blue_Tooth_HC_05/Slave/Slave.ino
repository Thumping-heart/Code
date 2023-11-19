#include <SoftwareSerial.h>          //库文件

SoftwareSerial BT(10,9);           //PIN10接蓝牙的TXD   PIN9接蓝牙的RXD
char X;                              //定义一个变量存数据。

void setup() 
{
  Serial.begin(38400);              //串口监视器通信速率，38400
  Serial.println("蓝牙连接正常");     //串口监视器显示蓝牙正常状态

  BT.begin(9600);                  //蓝牙通信速率，默认一般为 38400
  //进入AT模式设置为38400，退出这个模式设置为9600
}

void loop()                         //大循环，执行。
{
  if (Serial.available())           //检测：【串口】如果数据写入，则执行。
  {
    X = Serial.read();              //把写入的数据给到自定义变量  X
    BT.print(X);                    //把数据给蓝牙
  }

  if (BT.available())               //检测：【蓝牙】如果数据写入，则执行。
  {
    X = BT.read();                  //把检测到的数据给到自定义变量 X
    Serial.print(X);                //把从蓝牙得到的数据显示到串口监视器
  }
}
