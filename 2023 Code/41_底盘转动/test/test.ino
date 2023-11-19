#include "MCtrl.hpp"

int MA_P;
int MB_P;
int MC_P;
int MD_P;
void setup() {
  // put your setup code here, to run once:
  pinMode(MA_EN, OUTPUT);
  pinMode(MA_FWD, OUTPUT);
  pinMode(MA_REV, OUTPUT);
  pinMode(MB_EN, OUTPUT);
  pinMode(MB_FWD, OUTPUT);
  pinMode(MB_REV, OUTPUT);
  pinMode(MC_EN, OUTPUT);
  pinMode(MC_FWD, OUTPUT);
  pinMode(MC_REV, OUTPUT);
  pinMode(MD_EN, OUTPUT);
  pinMode(MD_FWD, OUTPUT);
  pinMode(MD_REV, OUTPUT);
}

void move_mode(unsigned char move_flag)
{
  switch(move_flag)
  {
    // AB为头
    // 右移：右侧电机转动向内 左侧电机转动向外
    // 左移：左侧电机转动向内 右侧电机转动向外
    //=======A、C：右一侧   B、D：左一侧
     case 0:MA_P = MB_P = 0;
            MC_P = MD_P = 0;     break;      // 停
     case 1:MA_P = MC_P = -50;
            MB_P = MD_P = 50;     break;      // 右自转
     case 2:MA_P = MC_P = 50;
            MB_P = MD_P = -50;     break;      // 左自转
     case 3:MA_P = MD_P = 50;
            MB_P = MC_P = -50;     break;      // 右移
     case 4:MA_P = MD_P = -50;
            MB_P = MC_P = 50;     break;      // 左移
     case 5:MA_P = MB_P = MC_P = MD_P = 50;   //前进
            break;  
     case 6:MA_P = MB_P = MC_P = MD_P = -50;   //后退
            break;                            
  }
  MA_SPD(MA_P);
  MB_SPD(MB_P);
  MC_SPD(MC_P);
  MD_SPD(MD_P);  
}

void loop() {
  // put your main code here, to run repeatedly:
  MD_P = 50;
  

  MA_SPD(MA_P);
  MB_SPD(MB_P);
  MC_SPD(MC_P);
  MD_SPD(MD_P);  
//  move_mode(1);//右自转
//  move_mode(2);//左自转
//  move_mode(3);//右移
//  move_mode(4);//左移
//  move_mode(5);//前进
//  move_mode(6);//后退
}
