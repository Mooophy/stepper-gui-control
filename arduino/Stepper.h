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
class State
{
public: 
  	//!  @ctor
  	//!  @brief  :  decode cmd to generate the state.
  	State(const String& cmd):
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

    void pwm(unsigned pin, unsigned period, unsigned duty);
};

void wave(const State* state);
void full(const State* state);
void half(const State* state);
void micr(const State* state);

void pwm(unsigned pin, unsigned period, unsigned duty);
void build(String& cmd);

#endif //STATE_H
