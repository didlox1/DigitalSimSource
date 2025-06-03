#pragma once
#include "Gate.h"
class ORGate : public Gate {
private:
public:
	ORGate(int propagationTime) : Gate(propagationTime) {};
	void propagateOutput() override;
	std::string returnType() override;
	int getNumberOfInputs() override;
};