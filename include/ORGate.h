#pragma once

#include "Gate.h"
// TODO: Add more Gates
class ORGate : public Gate {
private:
public:
	ORGate() : Gate() {};
	void propagateOutput() override {
		State outState = HIGH_IMPEDANCE; //Dodaæ error handling
		if (in.first.connected() && in.second.connected()) {
			if (in.first.getState() == LOW && in.second.getState() == LOW) outState = LOW;
			else outState = HIGH;
		}
		out.setState(outState);
	};
};