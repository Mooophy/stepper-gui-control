int A = 8;
int B = 9;
int C = 10;
int D = 11;
long duty = 50;
int waitMicroSeconds = 10000;
int pulseCount = 1;

//int trigger = A0; // used only for testing purposes (trigger on oscilloscope)

void setup() {                
  pinMode(A, OUTPUT);     
  pinMode(B, OUTPUT);     
  pinMode(C, OUTPUT);     
  pinMode(D, OUTPUT);     
}

void one(){
  digitalWrite(A, HIGH);   
  digitalWrite(B, LOW);   
  digitalWrite(C, HIGH);   
  digitalWrite(D, LOW);   
}

void two(){
  digitalWrite(A, HIGH);   
  digitalWrite(B, LOW);   
  digitalWrite(C, LOW);   
  digitalWrite(D, HIGH);   
}

void three(){
  digitalWrite(A, LOW);   
  digitalWrite(B, HIGH);   
  digitalWrite(C, LOW);   
  digitalWrite(D, HIGH);   
}

void four(){
  digitalWrite(A, LOW);   
  digitalWrite(B, HIGH);   
  digitalWrite(C, HIGH);   
  digitalWrite(D, LOW);   
}


void oneB(){
  digitalWrite(A, HIGH);   
  digitalWrite(B, LOW);   
  digitalWrite(C, LOW);   
  digitalWrite(D, LOW);   
}

void twoB(){
  digitalWrite(A, LOW);   
  digitalWrite(B, LOW);   
  digitalWrite(C, LOW);   
  digitalWrite(D, HIGH);   
}

void threeB(){
  digitalWrite(A, LOW);   
  digitalWrite(B, HIGH);   
  digitalWrite(C, LOW);   
  digitalWrite(D, LOW);   
}

void fourB(){
  digitalWrite(A, LOW);   
  digitalWrite(B, LOW);   
  digitalWrite(C, HIGH);   
  digitalWrite(D, LOW);   
}


// main routine to microstep
void doStep(int st){

  long dt1 = waitMicroSeconds * duty / 100;
  long dt2 = waitMicroSeconds * (100-duty) / 100;

  for (int j = 0; j < pulseCount; j++){
    switch (st){
    case 1: 
      one();
      break;
    case 2: 
      two();
      break;
    case 3: 
      three();
      break;
    case 4: 
      four();
      break;
    case 11: 
      oneB();
      break;
    case 12: 
      twoB();
      break;
    case 13: 
      threeB();
      break;
    case 14: 
      fourB();
      break;

    case 21: 
      one();
      break;
    case 22: 
      two();
      break;
    case 23: 
      three();
      break;
    case 24: 
      four();
      break;
    case 31: 
      oneB();
      break;
    case 32: 
      twoB();
      break;
    case 33: 
      threeB();
      break;
    case 34: 
      fourB();
      break;
    }    
    delayMicroseconds(dt1);

    switch (st){
    case 1: 
      one();
      break;
    case 2: 
      two();
      break;
    case 3: 
      three();
      break;
    case 4: 
      four();
      break;
    case 11: 
      oneB();
      break;
    case 12: 
      twoB();
      break;
    case 13: 
      threeB();
      break;
    case 14: 
      fourB();
      break;

    case 21: 
      oneB();
      break;
    case 22: 
      twoB();
      break;
    case 23: 
      threeB();
      break;
    case 24: 
      fourB();
      break;
    case 31: 
      two();
      break;
    case 32: 
      three();
      break;
    case 33: 
      four();
      break;
    case 34: 
      one();
      break;
    }
    delayMicroseconds(dt2);    
  }
}

// disable motor
void motorOff(){
  /* Important note:
   Turning off the motor will make it go into a 'rest' state. 
   When using microsteps (or even full steps), this may not be the last active step. 
   So using this routine may change the position of the motor a bit.
   */

  digitalWrite(A, LOW);   
  digitalWrite(B, LOW);   
  digitalWrite(C, LOW);   
  digitalWrite(D, LOW);   
}

// full stepping 4 steps :
void do4Steps(int cnt, boolean forwards)
{
  duty = 50;
  unsigned count = 0;
  const int list[] = {1,2,3,4};
  if(forwards)
  {
    while(count<cnt)
      doStep(list[count++ %4]);
  }
  else
  {
    int index = 3;
    while(count<cnt)
    {
      doStep(list[index--]);
      if(index<0)
        index=3;
      ++count;
    }
  }
}

// half stepping 8 steps :
void do8Steps(int cnt, boolean forwards){
  //const int list[] = {1,11,2,12,3,13,4,14};
  //for (int i = 0; i < cnt; i++){
  //duty = 50;
  //if (forwards)
  //{for (int j = 0; j <= 7; j++)
  // {doStep(list[j]);}}


  //else
  // {for (int j = 7; j >= 0; j--){doStep(list[j]);}}
  //
  unsigned count = 0;
  const int list[] = {
    1,11,2,12,3,13,4,14  };
  if(forwards){
    while(count<cnt)
      doStep(list[count++ %8]);
  }
  else{
    int index = 7;
    while(count<cnt){
      doStep(list[index--]);
      if(index<0)
        index=7;
      ++count;
    }
  }
}


// microstepping 16 steps :
void do16Steps(int cnt, boolean forwards){

  //const int list[] = {1,21,11,31,2,22,12,32,3,23,13,33,4,24,14,34};
  /* for (int i = 0; i < cnt; i++){
   duty = 50;
   if (forwards)
   {for (int j = 0; j <= 15; j++)
   {doStep(list[j]);}}
   else
   {for (int j = 15; j >= 0; j--){doStep(list[j]);}}
   }  
   
   
   }*/
  unsigned count = 0;
  const int list[] = {
    1,21,11,31,2,22,12,32,3,23,13,33,4,24,14,34  };
  duty = 50;
  if(forwards){
    while(count<cnt){
      doStep(list[count++ %16]);

    }
  }
  else{
    int index = 15;
    while(count<cnt){
      doStep(list[index--]);
      if(index<0)
        index=15;
      ++count;
    }
  }
}

// microstepping >16 steps :
/*void doMoreSteps(int cnt, boolean forwards){
 const int list1[] = {1,11,2,12,3,13,4,14};
 const int list2[] = {21,31,22,32,23,33,24,34};
 unsigned count = 0;
 // for (int i = 0; i < cnt; i++){
 
 duty = 50;
 if (forwards)
 { 
 while(count<cnt)
 { 
 doStep(list1[count %8]);
 doSteps(list2[count %8]);
 
 count++;
 
 //  for (int j = 0; j <= 7; j++){doStep(list1[j]); doSteps(list2[j], forwards);}
 }
 }
 else
 {//for (int j = 7; j >= 0; j--){doSteps(list2[j], forwards); doStep(list1[j]);}}
 
 }
 }
 
 // this routine handles >16 microsteps 
 // uncomment sections to choose # steps
 void doSteps(int st){
 
 // *********************** 24 steps 
 
 // if(forwards){
 duty = 66;    doStep(st);
 duty = 33;    doStep(st);
 //}
 //else{
 //duty = 33;    doStep(st);
 // duty = 66;    doStep(st);
 //}
 
 
 
 // *********************** 32 steps 
/*
 if (forwards){
 duty = 75;    doStep(st);
 duty = 50;    doStep(st);
 duty = 25;    doStep(st);
 }
 else{
 duty = 25;    doStep(st);
 duty = 50;    doStep(st);
 duty = 75;    doStep(st);
 }
 */

// *********************** 48 steps 

/*  if (forwards){
 for (int i = 5; i >= 1; i--){duty = 17 * i; doStep(st);}
 }
 else{
 for (int i = 1; i <= 5; i++){duty = 17 * i; doStep(st);}
 }
 */


// *********************** 64 steps 
/*
  if (forwards){
 for (int i = 7; i >= 1; i--){duty = 12 * i; doStep(st);}
 }
 else{
 for (int i = 1; i <= 7; i++){duty = 12 * i; doStep(st);}
 }
 */

// *********************** 96 steps 
// if (forwards){
//  for (int i = 9; i >= 1; i--){duty = 10 * i; doStep(st);}
// }
//else{
//  for (int i = 1; i <= 9; i++){duty = 10 * i; doStep(st);}
// }





// the loop routine runs over and over again forever:
void loop() {

  // uncomment this to disable motor  
  //  motorOff();return;


  /* control the speed of the motor with a waitMicroseconds/pulseCount pair
   e.g. waitMicroSeconds / pulseCount
   500 / 5 --> one step takes 2500 microseconds
   50 / 50 --> one step also takes 2500 microseconds
   but in second pair the fequency of the wave is 20kHz, not audible..
   in 500 / 5 you may hear a high tone in the motor in microsteps  
   some motors may not respond well on higher frequencies 
   note: these parameters also control speed in normal stepping (full or half) although there's no pulses in those cases, 
   setting pulseCount = 1 might be more readable
   */
  //  waitMicroSeconds = 10000; 
  //  pulseCount = 1;

  /*  uncomment one of the next routines to choose stepping mode
   do4Steps : full stepping
   do8Steps : half stepping
   do16Steps : microstepping with 16 steps
   doMoreSteps : microstepping with more than 16 steps
   --> check routine 'doSteps' for extra uncomments      
   
   two parameters:
   1. number of steps
   2. forwards = true --> move forwards   /  forwards = false --> move backwards
   
   note: there's no speed correction for different modes, so do4Steps makes the motor go twice as fast as do8Steps and so on... 
   use waitMicroseconds and pulseCount to adapt speed when changing modes
   
   */

  // do4Steps(24, true);
  do4Steps(24, true);
  //do16Steps(24, true);
  //doMoreSteps(24, true);

  //motorOff(); // give it a rest (see note in motorOff about losing steps)
  delay(1000);

  //  do4Steps(24, false);
  //do8Steps(24, false);
  //do16Steps(24, false);
  //  doMoreSteps(24, false);

  //motorOff(); // give it a rest (see note in motorOff about losing steps)
  delay(1000);

}

