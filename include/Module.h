#pragma once
#include <vector>
#include <map>
#include <memory>
#include "Gate.h"
#include "Connector.h"

class Module{
private:
	std::map<int ,std::shared_ptr<Gate>> m_gates;
public:
	void addGate(std::shared_ptr<Gate> g) {
		m_gates[g->getID()] = std::move(g);
	};
	std::shared_ptr<Gate> getGate(int id) {
		auto it = m_gates.find(id);
		if (it != m_gates.end()) {
			return m_gates[id];
		}
		else return nullptr;
	};
};