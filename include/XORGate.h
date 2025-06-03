#pragma once
#include "Gate.h"
class XORGate : public Gate {
private:
public:
	XORGate(int propagationTime) : Gate(propagationTime) {};
	void propagateOutput() override;
	std::string returnType() override;
	int getNumberOfInputs() override;
};