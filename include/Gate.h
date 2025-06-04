#pragma once

#include <vector>
#include <map>
#include <string>

#include "Connector.h"

class Gate {
protected:
	double m_propagationTime{}; 
	std::pair<Connector, Connector> in;
	Connector out;
	
public:
	Gate(int propagationTime = 0) : m_propagationTime(propagationTime), in(IO::INP, IO::INP), out(IO::OUTP) {};
	std::pair<Connector, Connector>& getInput() { return in; };
	Connector& getOutputHandler() { return out; };
	//virtual func
	virtual void propagateOutput(){};
	virtual std::string returnType() { return "Gate"; };
	virtual int getNumberOfInputs() { return 2; };
	double getPropagationTime() { return m_propagationTime; };
};
