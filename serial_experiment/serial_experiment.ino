


void setup() {
        Serial.begin(9600);     // opens serial port, sets data rate to 9600 bps
        pinMode(13, HIGH);   
}

void getString(int arr[]);

void loop() {
  
  int container[6] = {0,0,0,0,0,0};
      
  getString(container);
  
  

}

void getString(int arr[])
{
  if(Serial.available() > 0)
  {
    
  }
  
  
  
}
