/***************************************************************************
 *  @file       Stepper.cpp
 *  @author     Yue Wang
 *  @date       15  June 2014
 *  @remark     Implmentation for class Class Stepper
 *  @note       
 ***************************************************************************/

#include "Stepper.h"

/**
 * @brief   wave stepping
 *
 * @degree/step 7.5
 */
void wave_stepping(const Stepper* stepper)
{
  //!  specify the starting index according to the direction
  unsigned a,b,c,d;
  a = 0;
  b = 2;
  c = stepper->cw?  3  :  1;
  d = stepper->cw?  1  :  3;
  
  //!  move steps as specified if running == true.
  bool container[4] = {1,0,0,0};
  unsigned count = stepper->steps;
  while(count-- > 0 && stepper->running)
  {
    digitalWrite(A, container[a++]);
    digitalWrite(B, container[b++]);
    digitalWrite(C, container[c++]);
    digitalWrite(D, container[d++]);

    a %= 4;
    b %= 4;
    c %= 4;
    d %= 4;

    //!  speed control
    delay(10000/(stepper->spd));
  }
}

/**
 * @brief full stepping
 *
 * @degree/step 7.5
 */
void full_stepping(const Stepper* stepper)
{
  //!  specify the starting index according to the direction
  unsigned a,b,c,d;
  a = stepper->cw?  1  :  0;
  c = stepper->cw?  0  :  1;
  b = stepper->cw?  3  :  2;
  d = stepper->cw?  2  :  3;
  
  //!  move steps as specified if running == true.
  boolean container[4] = {1,1,0,0};
  unsigned count = stepper->steps;
  while(count-- > 0 && stepper->running)
  {
    digitalWrite(A, container[a++]);
    digitalWrite(B, container[b++]);
    digitalWrite(C, container[c++]);
    digitalWrite(D, container[d++]);

    a %= 4;
    b %= 4;
    c %= 4;
    d %= 4;

    //!  speed control
    delay(10000/(stepper->spd));
  }
}

/**
 * @brief half stepping
 *
 * @degree/step 3.75
 */
void half_stepping(const Stepper* stepper)
{
  //!  specify the starting index according to the direction
  int a = 0, c = 2, b = 4, d = 6;
  
  //!  move steps as specified if running == true.
  boolean container[8] = {1,1,1,0, 0,0,0,0};
  unsigned count = stepper->steps;
  while(count-- > 0 && stepper->running)
  {
      if(!stepper->cw)
      {
            digitalWrite(A, container[a++]);
            digitalWrite(B, container[b++]);
            digitalWrite(C, container[c++]);
            digitalWrite(D, container[d++]);

            a %= 8;
            b %= 8;
            c %= 8;
            d %= 8;
      }
      else
      {
            digitalWrite(A, container[a--]);
            digitalWrite(B, container[b--]);
            digitalWrite(C, container[c--]);
            digitalWrite(D, container[d--]);

            if(a < 0)  a = 7;
            if(b < 0)  b = 7;
            if(c < 0)  c = 7;
            if(d < 0)  d = 7;        
      }

    //!  speed control
    delay(10000/(stepper->spd));
  }
}

/**
 * @brief micro stepping
 *
 * @degree/step 1.40625
 */
void micr_stepping(const Stepper* stepper)
{
    //!  specify the starting index according to the direction  	
    const unsigned container[32] =
    {500, 625, 750, 875, 1000, 875, 750, 625, 500, 375, 250, 125, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0 ,0, 125, 250, 375};
    //^0-a                                    ^8-c                         ^16-b             ^24-d 
    int a  =  0;
    int b  =  16;
    int c  =  8;
    int d  =  24;
    
    //!  move steps as specified if running == true.
    unsigned period  =  1000;
    unsigned count   =  stepper->steps;
    while(count-- > 0 && stepper->running)
    {        
        if(!stepper->cw)
        {
            pwm(A, period, container[a++]);
            pwm(B, period, container[b++]);
            pwm(C, period, container[c++]);
            pwm(D, period, container[d++]);

            a %= 32;
            b %= 32;
            c %= 32;
            d %= 32;
        }
        else  //ccw
        {
            pwm(A, period, container[a--]);
            pwm(B, period, container[b--]);
            pwm(C, period, container[c--]);
            pwm(D, period, container[d--]);
            
            if(a < 0)  a = 31;
            if(b < 0)  b = 31;
            if(c < 0)  c = 31;
            if(d < 0)  d = 31;    
        }

      //!  speed control
      delay(10000/(stepper->spd));
    }   
}

/**
 * @brief pwm
 * @param pin
 * @param period
 * @param duty
 */
void pwm(unsigned pin, unsigned period, unsigned duty)
{
    digitalWrite(pin, HIGH);
    delayMicroseconds(duty);
  
    digitalWrite(pin, LOW);
    delayMicroseconds(period - duty);  
}

/**
 * @brief build
 *
 * receive the string from PC and store in cmd
 */
void build(String& cmd)
{
  while (Serial.available()) 
  {
    delay(3);                   //delay to allow buffer to fill
    if (Serial.available() > 0) 
    {
      char c = Serial.read();
      cmd += c;
    } 
  }
}
