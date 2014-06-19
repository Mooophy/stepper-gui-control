#include "Stepper.h"

/**
 * @brief wave
 */
void wave(const State* state)
{
  //!  specify the starting index according to the direction
  unsigned a,b,c,d;
  a = 0;
  b = 2;
  c = state->cw?  3  :  1;
  d = state->cw?  1  :  3;
  
  //!  move steps as specified if running == true.
  bool arr[4] = {1,0,0,0};
  unsigned count = state->steps;
  while(count-- > 0 && state->running)
  {
    digitalWrite(A, arr[a++]);
    digitalWrite(B, arr[b++]);
    digitalWrite(C, arr[c++]);
    digitalWrite(D, arr[d++]);

    a %= 4;
    b %= 4;
    c %= 4;
    d %= 4;

    //!  speed control
    delay(10000/(state->spd));
  }
}

/**
 * @brief full
 */
void full(const State* state)
{
  //!  specify the starting index according to the direction
  unsigned a,b,c,d;
  a = state->cw?  1  :  0;
  c = state->cw?  0  :  1;  
  b = state->cw?  3  :  2;
  d = state->cw?  2  :  3;
  
  //!  move steps as specified if running == true.
  boolean arr[4] = {1,1,0,0};
  unsigned count = state->steps;
  while(count-- > 0 && state->running)
  {
    digitalWrite(A, arr[a++]);
    digitalWrite(B, arr[b++]);
    digitalWrite(C, arr[c++]);
    digitalWrite(D, arr[d++]);

    a %= 4;
    b %= 4;
    c %= 4;
    d %= 4;

    //!  speed control
    delay(10000/(state->spd));
  }
}

/**
 * @brief half
 */
void half(const State* state)
{
  //!  specify the starting index according to the direction
  int a = 0, c = 2, b = 4, d = 6;
  
  //!  move steps as specified if running == true.
  boolean arr[8] = {1,1,1,0, 0,0,0,0};
  unsigned count = state->steps;
  while(count-- > 0 && state->running)
  {
      if(!state->cw)
      {
            digitalWrite(A, arr[a++]);
            digitalWrite(B, arr[b++]);
            digitalWrite(C, arr[c++]);
            digitalWrite(D, arr[d++]);

            a %= 8;
            b %= 8;
            c %= 8;
            d %= 8;
      }
      else
      {
            digitalWrite(A, arr[a--]);
            digitalWrite(B, arr[b--]);
            digitalWrite(C, arr[c--]);
            digitalWrite(D, arr[d--]);

            if(a < 0)  a = 7;
            if(b < 0)  b = 7;
            if(c < 0)  c = 7;
            if(d < 0)  d = 7;        
      }

    //!  speed control
    delay(10000/(state->spd));
  }
}

/**
 * @brief micr
 */
void micr(const State* state)
{
    //!  specify the starting index according to the direction  	
    const unsigned arr[32] = 
    {500, 625, 750, 875, 1000, 875, 750, 625, 500, 375, 250, 125, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0 ,0, 125, 250, 375};
    //^0-a                                    ^8-c                         ^16-b             ^24-d 
    int a  =  0;
    int b  =  16;
    int c  =  8;
    int d  =  24;
    
    //!  move steps as specified if running == true.
    unsigned period  =  1000;
    unsigned count   =  state->steps;
    while(count-- > 0 && state->running)
    {        
        if(!state->cw)
        {
            pwm(A, period, arr[a++]);
            pwm(B, period, arr[b++]);
            pwm(C, period, arr[c++]);
            pwm(D, period, arr[d++]);

            a %= 32;
            b %= 32;
            c %= 32;
            d %= 32;
        }
        else  //ccw
        {
            pwm(A, period, arr[a--]);
            pwm(B, period, arr[b--]);
            pwm(C, period, arr[c--]);
            pwm(D, period, arr[d--]);
            
            if(a < 0)  a = 31;
            if(b < 0)  b = 31;
            if(c < 0)  c = 31;
            if(d < 0)  d = 31;    
        }

      //!  speed control
      delay(10000/(state->spd));
    }   
}

/**
 * @brief pwm
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
 */
void build(String& cmd)
{
  while (Serial.available()) 
  {
    delay(3);  //delay to allow buffer to fill 
    if (Serial.available() > 0) 
    {
      char c = Serial.read();  //gets one byte from serial buffer
      cmd += c; //makes the string readString
    } 
  }
}