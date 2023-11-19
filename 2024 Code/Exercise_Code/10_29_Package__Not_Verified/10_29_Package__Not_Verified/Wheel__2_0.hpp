#ifndef _Wheel__2_0_HPP_
#define _Wheel__2_0_HPP_

#define MA_EN  4        //   MD___F1__F2___MA
#define MA_FWD A4       //   |              |
#define MA_REV A5       //   L2            R1
#define MB_EN  6        //   |              |
#define MB_FWD 43       //   L1            R2
#define MB_REV 42       //   |              |
#define MC_EN  11       //   MC___B2__B1___MB
#define MC_FWD 35
#define MC_REV 34
#define MD_EN  7        
#define MD_FWD 37
#define MD_REV 36

//存放轮子的PWM值
extern int SPD_A = 0;
extern int SPD_B = 0;
extern int SPD_C = 0;
extern int SPD_D = 0;

//轮子初始化部分
void Init_Wheel()
{
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

//轮子运动的底层函数
extern void MA_SPD(int MA_PWM) 
{
  if(MA_PWM>0)
  {
    analogWrite (MA_EN , MA_PWM);
    digitalWrite(MA_FWD, HIGH);
    digitalWrite(MA_REV, LOW);
  }
  else if(MA_PWM<0)
  {
    analogWrite (MA_EN , abs(MA_PWM));
    digitalWrite(MA_FWD, LOW);
    digitalWrite(MA_REV, HIGH);
  }
  else
  {
    digitalWrite(MA_FWD, LOW);
    digitalWrite(MA_REV, LOW);
  }
}

extern void MB_SPD(int MB_PWM) 
{
  if(MB_PWM>0)
  {
    analogWrite (MB_EN , MB_PWM);
    digitalWrite(MB_FWD, HIGH);
    digitalWrite(MB_REV, LOW);
  }
  else if(MB_PWM<0)
  {
    analogWrite (MB_EN , abs(MB_PWM));
    digitalWrite(MB_FWD, LOW);
    digitalWrite(MB_REV, HIGH);
  }
  else
  {
    digitalWrite(MB_FWD, LOW);
    digitalWrite(MB_REV, LOW);
  }
}

extern void MC_SPD(int MC_PWM) 
{
  if(MC_PWM>0)
  {
    analogWrite (MC_EN , MC_PWM);
    digitalWrite(MC_FWD, HIGH);
    digitalWrite(MC_REV, LOW);
  }
  else if(MC_PWM<0)
  {
    analogWrite (MC_EN , abs(MC_PWM));
    digitalWrite(MC_FWD, LOW);
    digitalWrite(MC_REV, HIGH);
  }
  else
  {
    digitalWrite(MC_FWD, LOW);
    digitalWrite(MC_REV, LOW);
  }
}

extern void MD_SPD(int MD_PWM) 
{
  if(MD_PWM>0)
  {
    analogWrite (MD_EN , MD_PWM);
    digitalWrite(MD_FWD, HIGH);
    digitalWrite(MD_REV, LOW);
  }
  else if(MD_PWM<0)
  {
    analogWrite (MD_EN , abs(MD_PWM));
    digitalWrite(MD_FWD, LOW);
    digitalWrite(MD_REV, HIGH);
  }
  else
  {
    digitalWrite(MD_FWD, LOW);
    digitalWrite(MD_REV, LOW);
  }
}

#endif
