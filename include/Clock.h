#pragma once
#include "Connector.h"
#include "vector"
#include "State.h"
#include <utility>

class Clock {
private:
	std::vector<std::pair<double, State>> m_state;
	State m_currentState{ State::LOW };
	double m_period{};		//in micro seconds
	double m_simTime{};	//in micro seconds
	void changeState();	//helping method

public:
	Clock(int period = 1, int simTime = 1); //default T = 1 ms, endTime = 1 ms
	const std::vector<std::pair<double, State>>& getState();
	void generateSignal();
};