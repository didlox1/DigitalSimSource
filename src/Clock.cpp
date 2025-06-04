#include "Clock.h"

Clock::Clock(int period, int endTime) :m_period(double(period)), m_endTime(double(endTime)) { generateSignal(); }

const std::vector<std::pair<double, State>>& Clock::getState()
{
	return m_state;
}

void Clock::changeState() {
	if (m_currentState == State::HIGH) m_currentState = State::LOW;
	else m_currentState = State::HIGH;
};

void Clock::generateSignal() {
	for (double t = 0.0; t <= m_endTime; t += m_period / 2.0) {
		m_state.emplace_back(t, m_currentState);
		changeState();
	}
}

const double Clock::getPeriod() const
{
	return m_period;
}

const double Clock::getEndTime() const
{
	return m_endTime;
}

