#pragma once
// TODO: Change setState() to setTimeline(outState)
// where outState = vector<pair<time + porpagationTime, State>>
// where "+" means shifting it by selected value
#include "Gate.h"
// TODO: Add more Gates
class ORGate : public Gate {
private:
public:
	ORGate() : Gate() {};
	void propagateOutput() override;
	std::string returnType() override;
};