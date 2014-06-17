const int A = 8;
const int B = 9;
const int C = 10;
const int D = 11;
const int indicator = 13;

//!  struct storing the state information
class State
{
  public:  
  unsigned spd;
  unsigned steps;
  boolean  running;    
  boolean  cw;
};

void wave(const State* state);
void full(const State* state);
void half(const State* state);
void micr(const State* state);
void pwm(unsigned pin, unsigned period, unsigned duty);
void indicate(boolean running);

void setup() 
{                
  pinMode(A, OUTPUT);     
  pinMode(B, OUTPUT);     
  pinMode(C, OUTPUT);     
  pinMode(D, OUTPUT);

  pinMode(indicator, HIGH);

  Serial.begin(9600);  
}



void loop() 
{
  String cmd;
  while (Serial.available()) 
  {
    delay(3);  //delay to allow buffer to fill 
    if (Serial.available() > 0) 
    {
      char c = Serial.read();  //gets one byte from serial buffer
      cmd += c; //makes the string readString
    } 
  }

  if(cmd.length() > 0) 
  {
    Serial.println(cmd); //see what was received
  }  
  


  if(cmd.length() > 3)
  {    
    State state;
    state.spd = cmd[1] * 5;
    state.steps =  cmd[3] + (cmd[2] << 8);
    state.running = true;
    state.cw = cmd[0] & 0x10;
  
    switch (cmd[0] & 0x0f)
    {
      case 1  :  wave(&state);  break;
      case 2  :  full(&state);  break;
      case 4  :  half(&state);  break;
      case 8  :  micr(&state);  break;
    }
  }
  
  if(cmd.length() > 0) 
  {
    Serial.println(cmd); //see what was received
  }  
  
  
    
}

//!  @brief :  wave stepping
//!  @speed range:  [10,500]
void wave(const State* state)
{
  indicate(true);
  //!  specify the starting index according to the direction
  unsigned a,b,c,d;
  a = 0;
  b = 2;
  c = state->cw?  3  :  1;
  d = state->cw?  1  :  3;
  
  //!  move steps as specified if running == true.
  boolean arr[4] = {1,0,0,0};
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
  indicate(false);
}

//!  @brief :  full stepping
//!  @speed range:  [10,500]
void full(const State* state)
{
  indicate(true);
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
  indicate(false);  
}

//!  @brief :  half stepping
//!  @speed range:  [10,500]
void half(const State* state)
{
  indicate(true);  
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
  indicate(false);
}

//!  @brief :  micro stepping
//!  @speed range:  [10,500]
void micr(const State* state)
{
    indicate(true);
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
    indicate(false);    
}

//!  @brief  :  pwm signal generation
void pwm(unsigned pin, unsigned period, unsigned duty)
{
    digitalWrite(pin, HIGH);
    delayMicroseconds(duty);
  
    digitalWrite(pin, LOW);
    delayMicroseconds(period - duty);  
}

//!  @brief  :  operate the built-in led i.e. pin 13
void indicate(boolean running)
{
    digitalWrite(indicator, running);
}
