const int pwm = 13;


void setup() {                
  pinMode(pwm, OUTPUT);     
}

void generate(unsigned pin, unsigned period, unsigned duty);

void loop() {
  generate(pwm,100,80);
}
void generate(unsigned pin, unsigned period, unsigned duty)
{
  digitalWrite(pin, HIGH);
  delay(duty);
  
  digitalWrite(pin, LOW);
  delay(period - duty);  
}

