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
	std::string srcGate;  // np. "AND1" "Name"
	std::string destPin;  // np. "IN1/IN2"
	std::string destGate; // np. "OR2" "Name"
};

struct ConstInput {
	std::string destGate;	// np. and1 
	std::string destPin;	// np. second 
	std::string state;		// np. 0
};

enum Type {
	AND,
	OR,
	XOR,
	NOT	
};

class Module{
private:
	std::map<std::string ,std::unique_ptr<Gate>> m_gates;
	std::map<std::string, Clock> m_clocks;
	std::vector<Connection> m_connections;
	std::vector<ConstInput> m_constInputs; //stores name and const State
public:
	void addGate(const std::string& name, Type gateType, int propagationTime);
	void addClock(const std::string&, int period, int endTime);
	std::map<std::string, std::unique_ptr<Gate>>& returnGates();
	std::map<std::string, Clock>& returnClocks();
	std::vector<ConstInput>& returnConstInputs();
	std::vector<Connection>& returnConnections();

	void connect(Connection c);
	void connectConst(ConstInput c);
	// TODO: Think carefully about disconnecting
	void disconnectInput(const std::string& name, int inputNumber);
	void propagateAll();
};