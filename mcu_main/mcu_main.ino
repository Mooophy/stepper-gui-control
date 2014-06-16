const int A = 8;
const int B = 9;
const int C = 10;
const int D = 11;

void wave_step(const unsigned* spd, const unsigned* steps, const boolean* cw);

void setup() {                
  pinMode(A, OUTPUT);     
  pinMode(B, OUTPUT);     
  pinMode(C, OUTPUT);     
  pinMode(D, OUTPUT);     
}

void loop() 
{
  unsigned spd = 300;
  unsigned steps = 30;
  boolean  cw = true;
  wave_step(&spd, &steps, &cw);

  while(true);
}

//!  speed range: [10,500]
void wave_step(const unsigned* spd, const unsigned* steps, const boolean* cw)
{
  boolean arr[4] = {1,0,0,0};
  unsigned count = *steps;
  unsigned a,b,c,d;

  //!  specify the starting index according to the direction
  a = 0;
  b = 2;
  c = *cw?  3  :  1;
  d = *cw?  1  :  3;
  
  while(count--)
  {
    digitalWrite(A, arr[a++]);
    digitalWrite(B, arr[b++]);
    digitalWrite(C, arr[c++]);
    digitalWrite(D, arr[d++]);

    a %= 4;
    b %= 4;
    c %= 4;
    d %= 4;

    delay(10000/(*spd));
  }
}


