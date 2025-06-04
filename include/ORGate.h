#pragma once
#include "Gate.h"
class ORGate : public Gate {
private:
public:
	ORGate(double propagationTime) : Gate(propagationTime) {};
	void propagateOutput() override;
	std::string returnType() override;
	int getNumberOfInputs() override;
};