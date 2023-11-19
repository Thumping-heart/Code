#include <Wire.h>
// 引入驱动OLED0.96所需的库
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
 
#define SCREEN_WIDTH 128 // 设置OLED宽度,单位:像素
#define SCREEN_HEIGHT 64 // 设置OLED高度,单位:像素
 
// 自定义重置引脚,虽然教程未使用,但却是Adafruit_SSD1306库文件所必需的
#define OLED_RESET 4
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);


//DHT11
#include <DHT.h>
#define DHTPIN 2//刚才插得2号引脚
#define DHTTYPE DHT11//定义类型
DHT dht(DHTPIN,DHTTYPE);//进行初始化设置

 int ledPin = 3;//蜂鸣器
void setup()
{
  // 初始化Wire库
  //  Wire.begin();
   pinMode(ledPin,OUTPUT);
  Serial.begin(9600);//波特率
  dht.begin();//DHT开始工作
  // 初始化OLED并设置其IIC地址为 0x3C
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  
   long frequency = 4000; //频率, 单位Hz
  //tone(pin, frequency, duration)或tone(pin, frequency)
  //pin代表连接扬声器的管脚，frequency代表发声频率，duration代表持续的时间，单位是毫秒
  //如果用第二个函数，则还需另外的noTone()函数来控制音乐的停止noTone(pin)。
  //用tone()函数发出频率为frequency的波形

  for(int i =0 ; i < 2 ; i++)
  {
      tone(ledPin, frequency );
      
      delay(100); //等待1000毫秒
      
      noTone(ledPin);//停止发声
      
      delay(300); //等待2000毫秒     
  }
}
 
void loop()
{ 
  words_display();
  display.display();
}
 
void words_display()
{
  delay(2000);//延时
  float h = dht.readHumidity();//读湿度
  float t = dht.readTemperature();//读湿度
  Serial.print("Humidity：");//湿度
  Serial.print(h);
  Serial.println("%");
  Serial.print("Temperatrue：");//温度
  Serial.print(t);
  Serial.println("℃");
  // 清除屏幕
  display.clearDisplay();
 
  // 设置字体颜色,白色可见
  display.setTextColor(WHITE);
 
  //设置字体大小
  display.setTextSize(1.5);
 
  //设置光标位置
  display.setCursor(1, 0);
  display.print("TaichiMaker");
 
  display.setCursor(0, 20);
  display.print("Humidity： ");
  //打印自开发板重置以来的秒数：
  display.print(h);
  display.print(" %");
 
  display.setCursor(0, 40);
  display.print("Temperatrue: ");
  display.print(t);
  display.print(" ℃");
}
