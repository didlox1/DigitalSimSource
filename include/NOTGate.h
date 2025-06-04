#pragma once
#include "Gate.h"

class NOTGate: public Gate{
private:
public:
	NOTGate(double propagationTime) : Gate(propagationTime) {}; //dodac Gate(int n) gdzie n to liczba wejsc bramki
	void propagateOutput() override;
	std::string returnType() override;
	int getNumberOfInputs() override;
};