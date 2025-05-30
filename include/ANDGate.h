#pragma once
#include "Gate.h"

// TODO: Change setState() to setTimeline(outState) ????
// where outState = vector<pair<time + porpagationTime, State>>
// where "+" means shifting it by selected value

class ANDGate : public Gate {
private:
public:
	ANDGate() : Gate() {};
	void propagateOutput() override;
};