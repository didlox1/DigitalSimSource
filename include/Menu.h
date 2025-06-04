#pragma once
#include <map>
#include <string>
#include <iostream>
#include <limits>
#include "Module.h"
#include "Connector.h"
#include "Clock.h"
#include "State.h"
#include "ANDGate.h"
#include "ORGate.h"
#include "NOTGate.h"
#include "File.h"
class Menu {
private:
	Module m_module;
    File m_file;
    void clearScreen();
    int getIntegerInput();
    void addComponent();
    void connectComponents();
    void setConstantInput();
    void viewComponentOutput();
    void viewAllComponents();
    void disconnectComponent();
    void saveModule();
    void openModule();
    void listGates(const auto& gates);
    void listClocks(const auto& gates);
public:
    void mainMenu();
};