const unsigned duty_arr [] = 
{500, 625, 750, 875, 1000, 875, 750, 625, 500, 375, 250, 125, 0,0,0,0,   0,0,0,0, 0,0,0,0,   0,0,0,0 ,0, 125, 250, 375};
//^0-a                                     ^8-c                          ^16-b               ^24-d 
const unsigned index_A = 0;
const unsigned index_B = 16;
const unsigned index_C = 8;
const unsigned index_D = 24;

const int A = 8;
const int B = 9;
const int C = 10;
const int D = 11;

int a,b,c,d;

void generate(unsigned pin, unsigned period, unsigned duty);

void setup() {                
  pinMode(A, OUTPUT);     
  pinMode(B, OUTPUT);     
  pinMode(C, OUTPUT);     
  pinMode(D, OUTPUT);
  
  a = index_A;
  b = index_B;
  c = index_C;
  d = index_D;    
}

void loop() {

  generate(A, 1000, duty_arr[a]);
  generate(C, 1000, duty_arr[b]);
  generate(B, 1000, duty_arr[c]);
  generate(D, 1000, duty_arr[d]);
  
  ++a;
  ++b;
  ++c;
  ++d;
  
  a %= 32;
  b %= 32;
  c %= 32;
  d %= 32;
  
  delay(50);
}

void generate(unsigned pin, unsigned period, unsigned duty)
{
  digitalWrite(pin, HIGH);
  delayMicroseconds(duty);
  
  digitalWrite(pin, LOW);
  delayMicroseconds(period - duty);  
}

