#include "Connector.h"
#include "Clock.h"

Connector::Connector(IO type) : m_type(type) {};
//set input to "1" or "0" for f = 0Hz (for constant states)
void Connector::setState(State state) {
	m_state.clear();
	m_state.push_back(std::pair(0, state));
}
//void setStateTimeline(std::vector<std::pair<int, State>> states)
//set m_state to the value of the timeline
void Connector::setStateTimeline(std::vector<std::pair<double, State>> states) {
	m_state = states;
}
//void connectClock(Clock c)
//Instead of setting to const "1" or const "0", connect Clock returns the timeline of the particular Clock(Period)
void Connector::connectClock(Clock& c) {
	m_state = c.getState();
}
//State getState()
//returns vector timeline of states, maybe rename to getTimeline
std::vector<std::pair<double, State>> Connector::getState() {
	if (m_connectedState) return *m_connectedState;
	else return m_state;
}
//connecting input from "other" to the output "m_state"
void Connector::connectTo(Connector& other) {
	if (m_type == IO::OUTP && other.m_type == IO::INP) {
		other.m_connectedState = &m_state;  
		other.m_state.clear(); // Clear local state when connected
	}
}
// TODO: validate
//disconnecting input of gate
void Connector::disconnect() {
	m_connectedState = nullptr;
	m_state = { {0, State::HIGH_IMPEDANCE} };
	// Initialize with default LOW state when disconnected
}

bool Connector::connected() const {
	if (m_state.size() != 0 || m_connectedState) return true;
	return false;
}
