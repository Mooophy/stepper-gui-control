const int A = 8;
const int B = 9;
const int C = 10;
const int D = 11;

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

void setup() 
{                
  pinMode(A, OUTPUT);     
  pinMode(B, OUTPUT);     
  pinMode(C, OUTPUT);     
  pinMode(D, OUTPUT);     
}

void loop() 
{
  
  State state;
  state.spd = 500;
  state.steps = 250;
  state.running = true;
  state.cw = true;
  
  half(&state);

  while(true);
}

//!  speed range: [10,500]
void wave(const State* state)
{
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
}

//!  speed range: [10,500]
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

//!  speed range: [10,500]
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
