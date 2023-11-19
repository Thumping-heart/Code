#ifndef _TRACKING_Bottom_H_
#define _TRACKING_Bottom_H

//#include "Wheel__2_0.hpp"//轮子的底层文件
//#include "IIC_Grayscale_Sensor__1_0.h"//IIC读取传感器的底层文件

void Stop()//停止
{
  MA_SPD(0);
  MB_SPD(0);
  MC_SPD(0);
  MD_SPD(0);
}

//前进和后退的轮子修正
void Straight_Sensor_Front_Program()//修正前方的轮子 DA
{
  //左移动 1 2 3
  //右移动 8 7 6
  //感为科技文字朝向自己时的方向
  if(Sensor_Front_Data[1] == 1 )//车左移
  {
    SPD_A = 60;
    SPD_D = -60;
  }
  else if(Sensor_Front_Data[8] == 1)//车右移
  {
    SPD_A = -60;
    SPD_D = 60; 
  }
  
  else if(Sensor_Front_Data[2] == 1)
  {
    SPD_A = 40;
    SPD_D = -40;    
  }
  else if(Sensor_Front_Data[7] == 1)
  {
    SPD_A = -40;
    SPD_D = 40;
  }
  
  else if(Sensor_Front_Data[3] == 1)
  {
    SPD_A = 10;
    SPD_D = -10;     
  }  
  else if(Sensor_Front_Data[6] == 1)
  {
    SPD_A = -10;
    SPD_D = 10;    
  }

  else
  {
    SPD_A = 0;
    SPD_D = 0; 
  }
}

void Straight_Sensor_Rear_Program()//修正后方的轮子 CB
{
  //左移动 1 2 3
  //右移动 8 7 6  
  //感为科技文字朝向自己时的方向
  if(Sensor_Rear_Data[1] == 1)//车左移
  {
    SPD_B = 60;
    SPD_C = -60;
  }
  else if(Sensor_Rear_Data[8] == 1)//车右移
  {
    SPD_B = -60;
    SPD_C = 60;
  }
  
  else if(Sensor_Rear_Data[2] == 1)
  {
    SPD_B = 40;
    SPD_C = -40;    
  }
  else if(Sensor_Rear_Data[7] == 1)
  {
    SPD_B = -40;
    SPD_C = 40;    
  }
  
  else if(Sensor_Rear_Data[3] == 1)
  {
    SPD_B = 10;
    SPD_C = -10;    
  }
  else if(Sensor_Rear_Data[6] == 1)
  {
    SPD_B = -10;
    SPD_C = 10;    
  }

  else
  {
    SPD_B = 0;
    SPD_C = 0;
  }
}

//左平移和右平移的轮子修正
void Left_Shift_Sensor_Front_Program()//修正左侧的轮子 DC
{
  //上移动 1 2 3
  //下移动 8 7 6
  //感为科技文字朝向自己时的方向
  if(Sensor_Left_Data[1] == 1 )//车上移
  {
    SPD_C = 60;
    SPD_D = 60;
  }
  else if(Sensor_Left_Data[8] == 1)//车下移
  {
    SPD_C = -60;
    SPD_D = -60; 
  }
  
  else if(Sensor_Left_Data[2] == 1)
  {
    SPD_C = 40;
    SPD_D = 40;    
  }
  else if(Sensor_Left_Data[7] == 1)
  {
    SPD_C = -40;
    SPD_D = -40;
  }
  
  else if(Sensor_Left_Data[3] == 1)
  {
    SPD_C = 10;
    SPD_D = 10;     
  }  
  else if(Sensor_Left_Data[6] == 1)
  {
    SPD_C = -10;
    SPD_D = -10;    
  }

  else
  {
    SPD_C = 0;
    SPD_D = 0; 
  }
}

void Left_Shift_Sensor_Rear_Program()//修正右侧的轮子 AB
{
  //上移动 8 7 6 
  //下移动 1 2 3 
  //感为科技文字朝向自己时的方向
  if(Sensor_Right_Data[1] == 1)//车下移
  {
    SPD_A = -60;
    SPD_B = -60;
  }
  else if(Sensor_Right_Data[8] == 1)//车上移
  {
    SPD_A = 60;
    SPD_B = 60;
  }
  
  else if(Sensor_Right_Data[2] == 1)
  {
    SPD_A = -40;
    SPD_B = -40;    
  }
  else if(Sensor_Right_Data[7] == 1)
  {
    SPD_A = 40;
    SPD_B = 40;    
  }
  
  else if(Sensor_Right_Data[3] == 1)
  {
    SPD_A = -10;
    SPD_B = -10;    
  }
  else if(Sensor_Right_Data[6] == 1)
  {
    SPD_A = 10;
    SPD_B = 10;    
  }

  else
  {
    SPD_A = 0;
    SPD_B = 0;
  }
}

void Straight(int Straight_SPD)//当>0时前进，当<0时后退
{
  //前进和后退
  Straight_Sensor_Front_Program();//修正前方的轮子 DA
  Straight_Sensor_Rear_Program();//修正后方的轮子 CB
  MA_SPD(SPD_A);
  MB_SPD(SPD_B); 
  MC_SPD(SPD_C);
  MD_SPD(SPD_D);
}

void Left_Shift(int Left_Shift_SPD)//当>0时左移，当<0时右移
{
  //左平移和右平移
  Left_Shift_Sensor_Front_Program();//修正左侧的轮子 DC
  Left_Shift_Sensor_Rear_Program();//修正右侧的轮子 AB
  MA_SPD(SPD_A);
  MB_SPD(SPD_B);
  MC_SPD(SPD_C);
  MD_SPD(SPD_D);
}

#endif
