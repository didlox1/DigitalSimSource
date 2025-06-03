#include "Module.h"
#include "Clock.h"

void Module::addGate(std::string name, Type gateType, int propagationTime)
{
	switch (gateType) {
	case Type::AND:
		m_gates[name] = std::make_unique<ANDGate>(propagationTime);
		break;
	case Type::OR:
		m_gates[name] = std::make_unique<ORGate>(propagationTime);
		break;
	case Type::XOR:
		m_gates[name] = std::make_unique<XORGate>(propagationTime);
		break;
	case Type::NOT:
		m_gates[name] = std::make_unique<NOTGate>(propagationTime);
		break;
	}
	
}

void Module::addClock(std::string name, int period, int endTime)
{
	m_clocks[name] = Clock(period, endTime);
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
	m_connections.push_back(c);
	if (m_gates.find(c.srcGate) != m_gates.end()) {
		auto& out = m_gates.find(c.srcGate)->second->getOutputHandler();
		switch (std::stoi(c.destPin)) {
		case 1:
			out.connectTo(m_gates.find(c.destGate)->second->getInput().first);
			propagateAll();
			return;
			break;
		case 2:
			out.connectTo(m_gates.find(c.destGate)->second->getInput().second);
			propagateAll();
			return;
			break;
		}
	}
	if (m_clocks.find(c.srcGate) != m_clocks.end()) {
		auto& clock = m_clocks.find(c.srcGate)->second;
		auto& in = m_gates.find(c.destGate)->second->getInput();
		switch (std::stoi(c.destPin)) {
		case 1:
			in.first.connectClock(clock);
			propagateAll();
			return;
			break;
		case 2:
			in.second.connectClock(clock);
			propagateAll();
			return;
			break;
		}
	}
}

std::map<std::string, std::unique_ptr<Gate>>& Module::returnGates()
{
	return m_gates;
}

std::map<std::string, Clock>& Module::returnClocks()
{
	return m_clocks;
}

void Module::remove(const std::string& name)
{
	// TODO: valifate
	auto it = m_connections.begin();
	while (it != m_connections.end()) {
		if ((name == it->destGate) || (name == it->srcGate)) {
			m_connections.erase(it); 
		}
		else {
			++it;
		}
	}
	m_gates.erase(name);
}

void Module::propagateAll()
{
	for (const auto& gate : m_gates) {
		gate.second->propagateOutput();
	}
}
