#pragma once
#include <map>
#include <string>
#include <iostream>
#include <windows.h>
#include "Module.h"
#include "Connector.h"
#include "Clock.h"
#include "State.h"
#include "ANDGate.h"
#include "ORGate.h"
#include "NOTGate.h"
class Menu {
private:
	Module m_module;
    void addComponent();
    void connectComponents();
    void setConstantInput();
    void viewComponentOutput();
    void viewAllComponents();
    void listGates(const auto& gates);
    void listClocks(const auto& gates);
public:
    void mainMenu();
};