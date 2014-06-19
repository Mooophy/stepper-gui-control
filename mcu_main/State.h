#ifndef STATE_H
#define STATE_H

#include <WString.h>

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
};
#endif //STATE_H
