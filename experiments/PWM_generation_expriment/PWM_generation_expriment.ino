const int pwm = 13;


void setup() {                
  pinMode(pwm, OUTPUT);     
}

void generate(unsigned pin, unsigned period, unsigned duty);


void loop() 
{
  generate(pwm,1000,250);
}


void generate(unsigned pin, unsigned period, unsigned duty)
{
  digitalWrite(pin, HIGH);
  //delay(duty);
   delayMicroseconds(duty);
  
  digitalWrite(pin, LOW);
   delayMicroseconds(period - duty);  
}

