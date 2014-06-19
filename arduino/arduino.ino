	
/***************************************************************************
 *  @file       Stepper.h
 *  @author     Yue Wang
 *  @date       15  June 2014
 *  @remark     Implemented for project 2, 282.478
 *  @note       
 ***************************************************************************/
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
  
  Stepper stepper(command);  
  switch (stepper.mode)
  {
    case 1  :  wave_stepping(&stepper);  break;
    case 2  :  full_stepping(&stepper);  break;
    case 4  :  half_stepping(&stepper);  break;
    case 8  :  micr_stepping(&stepper);  break;
  }
  
  if(command.length() > 0) 
  {
    Serial.println(command); //see what was received
  }  
}

