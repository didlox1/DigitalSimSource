#pragma once
#include <vector>
#include <map>
#include <string>
#include <memory>
#include "Gate.h"
#include "ANDGate.h"
#include "ORGate.h"
#include "XORGate.h"
#include "NOTGate.h"
#include "Connector.h"


struct Connection {
	std::string srcGate;  // e.g., "AND1" "Name"
	std::string destPin;  // e.g., "IN1/IN2"
	std::string destGate; // e.g., "OR2" "Name"
};

enum Type {
	AND,
	OR,
	XOR,
	NOT	// Add other gate types as needed
};

class Module{
private:
	std::map<std::string ,std::unique_ptr<Gate>> m_gates;
	std::map<std::string, Clock> m_clocks;
	std::vector<Connection> m_connections;
public:
	void addGate(std::string name, Type gateType, int propagationTime = 0);
	void addClock(std::string name, int period = 0, int endTime = 0);
	Gate& getGate(std::string name);
	Clock& getClock(std::string name);
	std::map<std::string, std::unique_ptr<Gate>>& returnGates();
	std::map<std::string, Clock>& returnClocks();

	void connect(Connection c);
	// TODO: Think carefully about disconnecting
	void remove(const std::string& name);
	void propagateAll();
};