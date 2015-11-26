	
/***************************************************************************
 *  @file       Stepper.h
 *  @author     Yue Wang
 *  @date       15  June 2014
 *  @remark     class Stepper 
 *  @note       
 ***************************************************************************/

#ifndef STATE_H
#define STATE_H

#include <WString.h>
#include <Arduino.h>

const int A = 8;
const int B = 9;
const int C = 10;
const int D = 11;

/**
 * @brief The State class
 */
class Stepper
{
public: 
  	//!  @ctor
  	//!  @brief  :  decode cmd to generate the state.
  	Stepper(const String& cmd):
    		spd(cmd[1] * 5),
    		steps(10 * cmd[3]),
    		running(true),
    		cw(cmd[0] & 0x10),
    		mode(cmd[0] & 0x0f)  
  	{}     
	
	unsigned spd;
	unsigned steps;
	bool  running;    
	bool  cw;
	unsigned mode;
};

void wave_stepping(const Stepper* stepper);
void full_stepping(const Stepper* stepper);
void half_stepping(const Stepper* stepper);
void micr_stepping(const Stepper* stepper);

void pwm(unsigned pin, unsigned period, unsigned duty);
void build(String& cmd);

#endif //STATE_H
