#include "Module.h"
#include "Clock.h"

void Module::addGate(std::string name, Type gateType)
{
	switch (gateType) {
	case Type::AND:
		m_gates[name] = std::make_unique<ANDGate>();
		break;
	case Type::OR:
		m_gates[name] = std::make_unique<ORGate>();
		break;
	case Type::XOR:
		m_gates[name] = std::make_unique<XORGate>();
		break;
	}
}

void Module::addClock(std::string name, int propagationTime)
{
	m_clocks[name] = Clock(propagationTime, propagationTime);
}

Gate& Module::getGate(std::string name)
{
	auto gate = m_gates.find(name);
	if (gate != m_gates.end()) {
		return *(gate->second);
	}
	else throw("Gate not found");
}

Clock& Module::getClock(std::string name)
{
	auto clock = m_clocks.find(name);
	if (clock != m_clocks.end()) {
		return clock->second;
	}
	else throw("Clock not found");
}

void Module::connect(Connection c)
{
	c.srcGate;
	c.destPin;
	c.srcPin;
	c.destGate;
}

std::map<std::string, std::unique_ptr<Gate>>& Module::returnGates()
{
	return m_gates;
}

std::map<std::string, Clock>& Module::returnClocks()
{
	return m_clocks;
}

void Module::disconnect(Connection c)
{
}

void Module::propagateAll()
{
	for (const auto& gate : m_gates) {
		gate.second->propagateOutput();
	}
}
