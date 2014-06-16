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

void wave_step(const State* state);
void full_step(const State* state);

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
  state.spd = 200;
  state.steps = 150;
  state.running = true;
  state.cw = false;
  
  full_step(&state);

  while(true);
}

//!  speed range: [10,500]
void wave_step(const State* state)
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

void full_step(const State* state)
{
  //!  specify the starting index according to the direction
  unsigned a,b,c,d;
  b = 3;
  d = 2;
  a = state->cw?  1  :  0;
  c = state->cw?  0  :  1;
  
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

