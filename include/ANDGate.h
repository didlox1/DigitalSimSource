#pragma once
#include "Gate.h"

class ANDGate : public Gate {
private:
public:
	ANDGate(int propagationTime) : Gate(propagationTime) {};
	void propagateOutput() override;
	std::string returnType() override;
	int getNumberOfInputs() override;
};