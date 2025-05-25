#pragma once

#include <vector>
#include <map>

#include "Connector.h"

class Gate {
protected:
	int m_id{};
	static int m_count; //number of all of gates
	std::pair<Connector, Connector> in;
	Connector out;
	
public:
	Gate() : m_id(m_count), in(IO::INPUT, IO::INPUT), out(IO::OUTPUT) { m_count++; };
	std::pair<Connector, Connector>& getInput() { return in; };
	Connector& getOutputHandler() { return out; };
	int getID() const { return m_id; };
	// TODO: Add propagation time
	virtual void propagateOutput() = 0;
};
