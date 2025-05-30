#pragma once
#include "Connector.h"
#include "vector"
#include "State.h"
#include <utility>

class Clock {
private:
	std::vector<std::pair<int, State>> m_state;
	State m_currentState{ State::LOW };
	int m_period{};		//in micro seconds
	int m_simTime{};	//in micro seconds
	void changeState();	//helping method

public:
	Clock(int period = 1000000, int simTime = 1000000); //default T = 1 sec, endTime = 1 sec
	std::vector<std::pair<int, State>> generateSignal();
};