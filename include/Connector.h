#pragma once
#include "State.h"
#include <vector>
#include <utility>

class Clock;

enum IO: char
{
	INPUT,
	OUTPUT
};

class Connector {
private:
	//State m_state{ State::HIGH_IMPEDANCE };
	//State* m_connectedState{ nullptr };
	std::vector<std::pair<int, State>> m_state;
	std::vector<std::pair<int, State>>* m_connectedState{ nullptr };
	IO m_type;
public:
	Connector(IO type);
	void setState(State state);
	void setStateTimeline(std::vector<std::pair<int, State>> states);
	void connectClock(Clock& c);
	std::vector<std::pair<int, State>> getState();
	void connectTo(Connector& other);
	void disconnect();
	bool connected() const;
};