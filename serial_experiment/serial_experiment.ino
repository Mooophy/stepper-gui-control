void setup() {
        Serial.begin(9600);     // opens serial port, sets data rate to 9600 bps
        pinMode(13, HIGH);   
}


void loop() {
  

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
}


