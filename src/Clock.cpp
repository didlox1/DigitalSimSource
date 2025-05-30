#include "Clock.h"

Clock::Clock(int period, int simTime) :m_period(period), m_simTime(simTime) {}

void Clock::changeState() {
	if (m_currentState == State::HIGH) m_currentState = State::LOW;
	else m_currentState = State::HIGH;
};

std::vector<std::pair<int, State>> Clock::generateSignal() {
	for (int t = 0; t <= m_simTime; t += m_period/2) {
		m_state.emplace_back(t, m_currentState);
		changeState();
	}
	return m_state;
}
