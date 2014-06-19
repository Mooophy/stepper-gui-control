#include "Stepper.h"

void setup() 
{                
  pinMode(A, OUTPUT);     
  pinMode(B, OUTPUT);     
  pinMode(C, OUTPUT);     
  pinMode(D, OUTPUT);

  Serial.begin(9600);  
}

void loop() 
{
  String command;
  build(command);
  
  State state(command);  
  switch (state.mode)
  {
    case 1  :  wave(&state);  break;
    case 2  :  full(&state);  break;
    case 4  :  half(&state);  break;
    case 8  :  micr(&state);  break;
  }
  
  if(command.length() > 0) 
  {
    Serial.println(command); //see what was received
  }  
}

