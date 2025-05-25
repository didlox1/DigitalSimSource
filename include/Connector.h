#pragma once

#include <vector>
#include <map>

enum IO: char
{
	INPUT,
	OUTPUT
};
// TODO: Add more functions to ERROR and HIGH_IMPEDANCE handling
enum State: int {
	LOW,
	HIGH,
	HIGH_IMPEDANCE,
	ERROR
};

class Connector {
private:
	State m_state{ State::HIGH_IMPEDANCE };
	State* m_connectedState{ nullptr };
	int m_id;
	IO m_type;
public:
	Connector(IO type) : m_type(type) {};
	void setState(State state) { m_state = state; };
	State getState() { 
		if (m_connectedState) return *m_connectedState;
		else return m_state;
	};
	void connectTo(Connector& other) {
		if (m_type == IO::OUTPUT && other.m_type == IO::INPUT) {
			other.m_connectedState = &m_state;
		}
	}
	bool connected() {
		if (m_type == HIGH || m_type == LOW) return true;
		return false;
	}
};