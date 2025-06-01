#pragma once
#include <vector>
#include <map>
#include <string>
#include <memory>
#include "Gate.h"
#include "ANDGate.h"
#include "ORGate.h"
#include "XORGate.h"
#include "Connector.h"

// TODO: Exceptions - learn how to write

struct Connection {
	std::string srcGate;  // e.g., "AND1" "Name"
	std::string srcPin;   // e.g., "OUT"
	std::string destGate; // e.g., "OR2" "Name"
	std::string destPin;  // e.g., "IN1" "IN2"
};

enum Type {
	AND,
	OR,
	XOR,
	NOT
	// Add other gate types as needed
};

class Module{
private:
	std::map<std::string ,std::unique_ptr<Gate>> m_gates;
	std::map<std::string, Clock> m_clocks;
	std::vector<Connection> m_connections;
public:
	void addGate(std::string name, Type gateType);
	void addClock(std::string name, int propagationTime = 0);
	Gate& getGate(std::string name);
	Clock& getClock(std::string name);
	void connect(Connection c);
	
	std::map<std::string, std::unique_ptr<Gate>>& returnGates();
	std::map<std::string, Clock>& returnClocks();
	// TODO: Think carefully about disconnecting
	void disconnect(Connection c);
	void propagateAll();
};