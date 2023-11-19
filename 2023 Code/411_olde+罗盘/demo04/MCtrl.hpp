#ifndef _MCtrl_HPP_
#define _MCtrl_HPP_

#define MA_EN  6       //   MA___F1__F2___MB
#define MA_FWD 43       //   |              |
#define MA_REV 42       //   L2            R1
#define MB_EN  4        //   |              |
#define MB_FWD A5       //   L1            R2
#define MB_REV A4       //   |              |
#define MC_EN  7        //   MC___B2__B1___MD
#define MC_FWD 37
#define MC_REV 36
#define MD_EN  11
#define MD_FWD 35
#define MD_REV 34
/*
#define MA_EN  11      //   MA___F1__F2___MB
#define MA_FWD 34     //   |              |
#define MA_REV 35     //   L2            R1
#define MB_EN  7     //   |              |
#define MB_FWD 36     //   L1            R2
#define MB_REV 37     //   |              |
#define MC_EN  4     //   MC___B2__B1___MD
#define MC_FWD A4
#define MC_REV A5
#define MD_EN  6
#define MD_FWD 42
#define MD_REV 43
*/



void MA_SPD(int MA_PWM) 
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

void MB_SPD(int MB_PWM) 
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

void MC_SPD(int MC_PWM) 
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
void MD_SPD(int MD_PWM) 
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
