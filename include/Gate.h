#pragma once

#include <vector>
#include <map>
#include <string>

#include "Connector.h"

class Gate {
protected:
	int m_propagationDelay{}; 
	std::pair<Connector, Connector> in;
	Connector out;
	
public:
	Gate(int propagationDelay = 0) : m_propagationDelay(propagationDelay), in(IO::INP, IO::INP), out(IO::OUTP) {};
	std::pair<Connector, Connector>& getInput() { return in; };
	Connector& getOutputHandler() { return out; };
	//virtual func
	virtual void propagateOutput(){};
	virtual std::string returnType() { return "Gate"; };
	virtual int getNumberOfInputs() { return 2; };
};
