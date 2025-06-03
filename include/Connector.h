#pragma once
#include "State.h"
#include <vector>
#include <utility>

class Clock;

enum IO: char
{
	INP,
	OUTP
};

class Connector {
private:
	std::vector<std::pair<double, State>> m_state;
	std::vector<std::pair<double, State>>* m_connectedState{ nullptr };
	IO m_type;
public:
	Connector(IO type);
	void setState(State state);
	void setStateTimeline(std::vector<std::pair<double, State>> states);
	void connectClock(Clock& c);
	std::vector<std::pair<double, State>> getState();
	void connectTo(Connector& other);
	void disconnect();
	bool connected() const;
};