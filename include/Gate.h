#pragma once

#include <vector>
#include <map>
#include <string>

#include "Connector.h"

class Gate {
protected:
	int m_id{};
	int m_propagationDelay{}; 
	static int m_gates_count; //number of all of gates
	std::pair<Connector, Connector> in;
	Connector out;
	
public:
	Gate(int propagationDelay = 0) : m_id(m_gates_count), m_propagationDelay(propagationDelay), in(IO::INP, IO::INP), out(IO::OUTP) { m_gates_count++; };
	std::pair<Connector, Connector>& getInput() { return in; };
	Connector& getOutputHandler() { return out; };
	int getID() const { return m_id; };
	// TODO: Add propagation time
	virtual void propagateOutput() = 0;
	virtual std::string returnType();
};
