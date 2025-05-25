#pragma once

#include <vector>
#include <map>

#include "Gate.h"

class ANDGate : public Gate {
private:
public:
	ANDGate() : Gate() {};
	void propagateOutput() override {
		State outState = HIGH_IMPEDANCE; //Dodaæ error handling
		if (in.first.connected() && in.second.connected()) {
			if (in.first.getState() == HIGH && in.second.getState() == HIGH) outState = HIGH;
			else outState = LOW;
		}
		out.setState(outState);
	};
};