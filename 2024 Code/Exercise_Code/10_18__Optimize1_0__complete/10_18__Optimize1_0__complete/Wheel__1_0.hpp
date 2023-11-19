#ifndef _Wheel__1_0_HPP_
#define _Wheel__1_0_HPP_

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
