const int A = 8;
const int B = 9;
const int C = 10;
const int D = 11;

int count = 12;

// speed at 20-500
const unsigned width = 20;

void setup() {                
  pinMode(A, OUTPUT);     
  pinMode(B, OUTPUT);     
  pinMode(C, OUTPUT);     
  pinMode(D, OUTPUT);     
}

void loop() {

  while(count > 0)
  {
  digitalWrite(A, HIGH);//6
  digitalWrite(B, LOW);
  digitalWrite(C, HIGH);//6
  digitalWrite(D, LOW);
  delay(width);
  
  digitalWrite(A, HIGH);//12
  digitalWrite(B, LOW);
  digitalWrite(C, LOW);
  digitalWrite(D, LOW);
  delay(width);

  digitalWrite(A, HIGH);//6
  digitalWrite(B, LOW);
  digitalWrite(C, LOW);
  digitalWrite(D, HIGH);//6
  delay(width);
  
  digitalWrite(A, LOW);
  digitalWrite(B, LOW);
  digitalWrite(C, LOW);
  digitalWrite(D, HIGH);//12
  delay(width);

  digitalWrite(A, LOW);
  digitalWrite(B, HIGH);//6
  digitalWrite(C, LOW);
  digitalWrite(D, HIGH);//6
  delay(width);
  
  digitalWrite(A, LOW);
  digitalWrite(B, HIGH);//12
  digitalWrite(C, LOW);
  digitalWrite(D, LOW);
  delay(width);
  
  digitalWrite(A, LOW);
  digitalWrite(B, HIGH);//6
  digitalWrite(C, HIGH);//6
  digitalWrite(D, LOW);
  delay(width);
  
  digitalWrite(A, LOW);
  digitalWrite(B, LOW);
  digitalWrite(C, HIGH);//12
  digitalWrite(D, LOW);
  delay(width);
  
  --count;
}
  delay(3000);
  count = 12;

}


