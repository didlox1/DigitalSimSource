#include "Menu.h"
/*
Module m;
//CreatinWg ANDGate
std::shared_ptr<ANDGate> and1 = std::make_shared<ANDGate>();
m.addGate(and1);
//Getting Gate handler
std::shared_ptr<Gate> g1 = m.getGate(0);
//Getting connectors 
Connector& in1 = g1->getInput().first;
Connector& in2 = g1->getInput().second;
Connector& out = g1->getOutputHandler();
//Creating clock and setting connectors state
Clock c1;
in1.connectClock(c1);
//in1.setState(State::HIGH);
in2.setState(State::HIGH);
//Propagate an output 
g1->propagateOutput();
//std::cout << out.getState() << std::endl;  // (1 AND 1) Should print 1 (HIGH)
*/

void Menu::addComponent()
{   
    int choice{};
    std::string name;
    do {
        system("cls");
        std::cout << "Name of component: ";
        getline(std::cin, name);
        if (name.empty()) return;
        std::cout << "Select component to add:\n";
        std::cout << "1. AND\n";
        std::cout << "2. OR\n";
        std::cout << "3. XOR\n";
        std::cout << "4. Clock\n";
        std::cout << "0. Cancel\n";
        std::cin >> choice;
        switch (choice) {
        case 1: m_module.addGate(name, Type::AND); break;
        case 2: m_module.addGate(name, Type::OR); break;
        case 3: m_module.addGate(name, Type::XOR); break;
        case 4: m_module.addClock(name, 1000); break;
        case 0: return; break;
        default:
            std::cout << "Invalid option.\n";
        }
    } while (choice != 0);
}

void Menu::connectComponents()
{
    system("cls");
    std::string choice1;
    std::string choice2;
    const auto& gates = m_module.returnGates();
    const auto& clocks = m_module.returnClocks();
    listGates(gates);
    listClocks(clocks);
    do {
        std::cout << "Select first component (write a name):\n";
        std::cin >> choice1;
        if (gates.find(choice1) != gates.end() || clocks.find(choice1) != clocks.end()) break;
        else std::cout << "Invalid name.\n";
    } while (choice1 != "\n");
    do {
        std::cout << "Select second component (write a name):\n";
        std::cin >> choice2;
        if (gates.find(choice2) != gates.end() || clocks.find(choice2) != clocks.end()) break;
        else std::cout << "Invalid name.\n";
    } while (choice2 != "\n");
    if (choice1 != "\n" && choice2 != "\n") {
        //m_module.connect();
    }
    else return;
}

void Menu::setConstantInput()
{
    system("cls");
    std::string choice;
    int state{};
    int input{};
    const auto& gates = m_module.returnGates();
    listGates(gates);
    //Selecting gate
    do {
        std::cout << "Select component (write a name):\n";
        getline(std::cin, choice);
        if (gates.find(choice) != gates.end()) break;
        else if (choice.empty()) return;
        else std::cout << "Invalid name.\n";
    } while (choice != "\n");
    //Selecting input
    do {
        system("cls");
        std::cout << "Select input number:\n";
        std::cout << "1. First\n";
        std::cout << "2. Second\n";
        std::cout << "0. Return\n";
        std::cin >> input;

        switch (input) {
        case 1: break;
        case 2: break;
        case 0: return; break;
        default: std::cout << "Invalid option.\n"; break;
        }
    } while (input != 1 && input != 2);
    //Selecting state
    do {
        system("cls");
        std::cout << "Select state:\n";
        std::cout << "0. LOW\n";
        std::cout << "1. HIGH\n";
        std::cout << "2. Return\n";
        std::cin >> state;
        switch (state){
        case 0: 
            if (input == 1) {
                gates.find(choice)->second->getInput().first.setState(State::LOW);
            }
            else if (input == 2) {
                gates.find(choice)->second->getInput().second.setState(State::LOW);
            }
            m_module.propagateAll();
            return;
            break;
        case 1: 
            if (input == 1) {
                gates.find(choice)->second->getInput().first.setState(State::HIGH);
            }
            else if (input == 2) {
                gates.find(choice)->second->getInput().second.setState(State::HIGH);
            }
            m_module.propagateAll();
            return;
            break;
        case 2: return; break;
        default: std::cout << "Invalid option.\n"; break;
        }
    } while (true);
}

void Menu::viewComponentOutput()
{
    std::string choice;
    system("cls");
    const auto& gates = m_module.returnGates();
    const auto& clocks = m_module.returnClocks();
    listGates(gates);
    listClocks(clocks);

    do {
        std::cout << "Select component (write a name):\n";
        getline(std::cin, choice);
        //std::cin >> choice;
        if (gates.find(choice) != gates.end()) break;
        else if (choice.empty()) return;
        else std::cout << "Invalid name.\n";
    } while (choice != "");

    const auto& gate = gates.find(choice);
    Connector& out = gate->second->getOutputHandler();
    for (const auto& state : out.getState()) {
        std::cout << "Time (ms): " << state.first << " State: " << state.second <<"\n";
    }
    //wait for input
    std::cout << "\nPress Enter to continue...";
    std::cin.get();
}

void Menu::viewAllComponents()
{
    system("cls");
    const auto& gates = m_module.returnGates();
    const auto& clocks = m_module.returnClocks();
    listGates(gates);
    listClocks(clocks);
    //wait for input
    std::cout << "\nPress Enter to continue...";
    std::cin.get();
}   

void Menu::listGates(const auto& gates)
{
    for (const auto& gate : gates) {
        std::cout << "Name: " << gate.first <<" Type: " << gate.second->returnType() << "\n";
    }
}

void Menu::listClocks(const auto& clocks)
{
    for (const auto& clock : clocks) {
        std::cout << "Name: " << clock.first << " Type: Clock" << "\n";
    }
}


void Menu::mainMenu()
{
    int choice{};
    do {
        system("cls");
        std::cout << "=== Digital Logic Simulator ===\n";
        std::cout << "1. Add Component\n";
        std::cout << "2. Connect Connectors\n";
        std::cout << "3. Set Constant Input\n";
        std::cout << "4. Print Output\n";
        std::cout << "5. Print All Components\n";
        std::cout << "0. Exit\n> ";
        std::cin >> choice;

        switch (choice) {
        case 1:
            std::cin.ignore(10000000, '\n');
            addComponent(); break;
        case 2: 
            std::cin.ignore(10000000, '\n');
            connectComponents(); break;
        case 3: 
            std::cin.ignore(10000000, '\n');
            setConstantInput(); break;
        case 4: 
            std::cin.ignore(10000000, '\n');
            viewComponentOutput(); break;
        case 5: 
            std::cin.ignore(10000000, '\n');
            viewAllComponents(); break;
        case 0: exit(EXIT_SUCCESS); break;
        default: std::cout << "Invalid option.\n"; break;
        }
    } while (choice != 0);
}
