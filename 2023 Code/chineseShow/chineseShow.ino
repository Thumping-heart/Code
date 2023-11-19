#include <Wire.h>

#include "text.h"

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
#define DHTPIN 2//刚才插得2号   引脚
#define DHTTYPE DHT11//定义类型
DHT dht(DHTPIN,DHTTYPE);//进行初始化设置

 int ledPin = 3;//蜂鸣器
void setup()
{
    pinMode(12,OUTPUT);
    digitalWrite(12, LOW);
    
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
    hans_display_0();
//    hans_display_1();
}

void hans_display_0(void)
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

  
    // 显示之前清屏
    display.clearDisplay();
    // 设置字体颜色,白色可见
    display.setTextColor(WHITE);

    //设置字体大小
    display.setTextSize(3);
    // 显示文字 (左上角x坐标,左上角y坐标, 图形数组, 图形宽度像素点, 图形高度像素点, 设置颜色)
    display.drawBitmap(10 * 1, 9, hans_shi, 16, 16, 1);
    display.drawBitmap(10 * 3, 9, hans_du, 16, 16, 1);
    display.setCursor(45, 8);
    display.print(": ");
    
    display.setTextSize(2);
    //湿度
    display.setCursor(65, 10);
    display.print(h);
    
    display.drawBitmap(10 * 1, 32, hans_wen, 16, 16, 1);
    display.drawBitmap(10 *3, 32, hans_du, 16, 16, 1);
    display.setTextSize(3);
    display.setCursor(45, 31);
    display.print(": ");
    
    display.setTextSize(2);
    //温度
    display.setCursor(65, 33);
    display.print(t);

    //显示图形
    display.display();
    delay(2000);
}
