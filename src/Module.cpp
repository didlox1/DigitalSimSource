#include "Module.h"
#include "Clock.h"

void Module::addGate(const std::string& name, Type gateType, int propagationTime)
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

void Module::addClock(const std::string& name, int period, int endTime)
{
	m_clocks[name] = Clock(period, endTime);
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

void Module::connectConst(ConstInput c)
{
	m_constInputs.push_back(c);
	State state = State::HIGH_IMPEDANCE;
	if (c.state == "0") state = State::LOW;
	else if (c.state == "1") state = State::HIGH;
	auto& in = m_gates.find(c.destGate)->second->getInput();
	switch (std::stoi(c.destPin)) {
	case(1):
		in.first.setState(state);
		propagateAll();
		return;
		break;
	case(2):
		in.second.setState(state);
		propagateAll();
		return;
		break;
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

std::vector<ConstInput>& Module::returnConstInputs()
{
	return m_constInputs;
}

std::vector<Connection>& Module::returnConnections()
{
	return m_connections;
}

void Module::disconnectInput (const std::string& name, int inputNumber)
{
	if (m_gates.find(name) != m_gates.end()) {
		const auto& gate = m_gates.find(name)->second;
		if(inputNumber == 1) gate->getInput().first.disconnect();
		if (inputNumber == 2) gate->getInput().second.disconnect();
	}
	propagateAll();
}

void Module::propagateAll()
{
	for (const auto& gate : m_gates) {
		gate.second->propagateOutput();
	}
}
