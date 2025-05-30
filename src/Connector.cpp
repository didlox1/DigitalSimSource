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
void Connector::setStateTimeline(std::vector<std::pair<int, State>> states) {
	m_state = states;
}
//void connectClock(Clock c)
//Instead of setting to const "1" or const "0", connect Clock returns the timeline of the particular Clock(Period)
void Connector::connectClock(Clock& c) {
	m_state = c.generateSignal();
}
//State getState()
//returns vector timeline of states, maybe rename to getTimeline
std::vector<std::pair<int, State>> Connector::getState() {
	if (m_connectedState) return *m_connectedState;
	else return m_state;
}
//connecting input from "other" to the output "m_state"
void Connector::connectTo(Connector& other) {
	if (m_type == IO::OUTPUT && other.m_type == IO::INPUT) {
		other.m_connectedState = &m_state;  
	}
}
// TODO: validate
//disconnecting input of gate
void Connector::disconnect() {
	m_connectedState = nullptr;
}
bool Connector::connected() const {
	if (m_type == HIGH || m_type == LOW) return true;
	return false;
}