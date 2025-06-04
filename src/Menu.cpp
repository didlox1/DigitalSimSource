#include "Menu.h"

//Clearing terminal window (different in different OS's)
void Menu::clearScreen()
{
    #if defined(WIN32) || defined(_WIN32)
        system("cls"); //Windows
    #else
        system("clear"); //Linux Mac
    #endif
}

int Menu::getIntegerInput()
{
    int input;
    while (!(std::cin >> input)) {
        std::cin.clear(); // Clear error state, if not then garbage
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Invalid input. Enter a number: ";
    }
    return input;
}

void Menu::addComponent()
{   
    int choice{};
    int propagationTime{};
    int period{};
    int endTime{};
    std::string name;
    do {
        clearScreen();
        std::cout << "Name of component: ";
        getline(std::cin, name);
        if (name.empty()) return;
        std::cout << "Select component to add:\n";
        std::cout << "1. AND Gate\n";
        std::cout << "2. OR Gate\n";
        std::cout << "3. XOR Gate\n";
        std::cout << "4. Clock\n";
        std::cout << "5. NOT Gate\n";
        std::cout << "0. Cancel\n";
        choice = getIntegerInput();
        switch (choice) {
        case 1: 
            std::cout << "Propagation time (ms): ";
            propagationTime = getIntegerInput();
            m_module.addGate(name, Type::AND, propagationTime); break;
        case 2: 
            std::cout << "Propagation time (ms): ";
            propagationTime = getIntegerInput();
            m_module.addGate(name, Type::OR, propagationTime); break;
        case 3: 
            std::cout << "Propagation time (ms): ";
            propagationTime = getIntegerInput();
            m_module.addGate(name, Type::XOR, propagationTime); break;
        case 4: 
            std::cout << "Period (ms): ";
            period = getIntegerInput();
            std::cout << "Length of the timeline (ms): ";
            endTime = getIntegerInput();
            m_module.addClock(name, period, endTime); break;
        case 5:
            std::cout << "Propagation time (ms): ";
            propagationTime = getIntegerInput();
            m_module.addGate(name, Type::NOT, propagationTime); break;
        case 0: return; break;
        default:
            std::cout << "Invalid option.\n";
        }
    } while (choice != 0);
}

//First component - getting it's output
//Second component - getting it's input(first or second in) and connecting it to output of the first component
void Menu::connectComponents()
{
    clearScreen();
    std::string choice1;
    std::string choice2;
    int inputNumber{};
    int numberOfInputs{};
    const auto& gates = m_module.returnGates();
    const auto& clocks = m_module.returnClocks();
    listGates(gates);
    listClocks(clocks);
    //Selecting first component
    do {
        std::cout << "Select first component (output):\n";
        getline(std::cin, choice1);
        if (gates.find(choice1) != gates.end() || clocks.find(choice1) != clocks.end()) break;
        else if (choice1.empty()) return;
        else std::cout << "Invalid name.\n";
    } while (choice1 != "\n");
    //Selecting second component
    do {
        std::cout << "Select second component (input):\n";
        getline(std::cin, choice2);
        if (gates.find(choice2) != gates.end()) break;
        else if (choice2.empty()) return;
        else std::cout << "Invalid name.\n";
    } while (choice2 != "\n");
    //checking how many inputs second component have(input) have.
    numberOfInputs = gates.find(choice2)->second->getNumberOfInputs();
    if (numberOfInputs == 1) {
        m_module.connect(Connection(choice1, "1", choice2));
        return;
    }
    //Selecting input of the second component
    do {
        clearScreen();
        std::cout << "Select input number:\n";
        std::cout << "1. First\n";
        std::cout << "2. Second\n";
        std::cout << "0. Return\n";
        inputNumber = getIntegerInput();
        if (inputNumber == 1 || inputNumber == 2) {
            m_module.connect(Connection(choice1, std::to_string(inputNumber), choice2));
            return;
        }
        else if(inputNumber == 0) return;
        else std::cout << "Invalid option.\n";
    } while (true);
}

void Menu::setConstantInput()
{

    clearScreen();
    std::string name;
    int state{};
    int input{};
    int numberOfInputs{};
    const auto& gates = m_module.returnGates();
    listGates(gates);
    //Selecting gate by name
    do {
        std::cout << "Select component (write a name):\n";
        getline(std::cin, name);
        if (gates.find(name) != gates.end()) break;
        else if (name.empty()) return;
        else std::cout << "Invalid name.\n";
    } while (name != "\n");
    do {
        clearScreen();
        std::cout << "Select state:\n";
        std::cout << "0. LOW\n";
        std::cout << "1. HIGH\n";
        std::cout << "2. Return\n";
            state = getIntegerInput();
        if (state == 0 || state == 1) break;
        else if (state == 2) return;
        else std::cout << "Invalid option.\n";
    }while(true);
    //Getting number of inputs for the menu options
    numberOfInputs = gates.find(name)->second->getNumberOfInputs();
    // if 2 inputs available then choose one
    if(numberOfInputs == 2){
        do {
            clearScreen();
            std::cout << "Select input number:\n";
            std::cout << "1. First\n";
            std::cout << "2. Second\n";
            std::cout << "0. Return\n";
            input = getIntegerInput();
            switch (input) {
            case 1: 
                m_module.connectConst(ConstInput(name, "1", std::to_string(state)));
                return;
                break;
            case 2: 
                m_module.connectConst(ConstInput(name, "2", std::to_string(state)));
                return;
                break;
            case 0: 
                return; break;
            default: std::cout << "Invalid option.\n"; break;
            }
        } while (true);
    }
    //if only one input available
    else if(numberOfInputs == 1) m_module.connectConst(ConstInput(name, "1", std::to_string(state)));
}

void Menu::viewComponentOutput()
{
    std::string choice;
    clearScreen();
    const auto& gates = m_module.returnGates();
    auto& clocks = m_module.returnClocks();
    listGates(gates);
    listClocks(clocks);
    do {
        std::cout << "Select component (write a name):\n";
        getline(std::cin, choice);
        if (gates.find(choice) != gates.end() || clocks.find(choice) != clocks.end()) break;
        else if (choice.empty()) return;
        else std::cout << "Invalid name.\n";
    } while (choice != "");
    const auto& gate = gates.find(choice);
    const auto& clock = clocks.find(choice);
    if (gate != gates.end()) {
        Connector& out = gate->second->getOutputHandler();
        for (const auto& state : out.getState()) {
            std::cout << "Time (ms): " << state.first << " State: " << state.second << "\n";
        }
    }
    if (clock != clocks.end()) {
        const auto& states =  clock->second.getState();
        for (const auto& state : states) {
            std::cout << "Time (ms): " << state.first << " State: " << state.second << "\n";
        }
    }
    //wait for input
    std::cout << "\nPress Enter to continue...";
    std::cin.get();
}

void Menu::viewAllComponents()
{
    clearScreen();
    const auto& gates = m_module.returnGates();
    const auto& clocks = m_module.returnClocks();
    listGates(gates);
    listClocks(clocks);
    //wait for input
    std::cout << "\nPress Enter to continue...";
    std::cin.get();
}

void Menu::deleteComponent()
{
    std::string name;
    clearScreen();
    const auto& gates = m_module.returnGates();
    const auto& clocks = m_module.returnClocks();
    listGates(gates);
    listClocks(clocks);
    do {
        std::cout << "Select component to remove (write a name):\n";
        getline(std::cin, name);
        if (gates.find(name) != gates.end() || clocks.find(name) != clocks.end()) break;
        else if (name.empty()) return;
        else std::cout << "Invalid name.\n";
    } while (name != "");
    m_module.remove(name);
}

void Menu::saveModule()
{
    std::string name;
    std::cout << "Write a name of the file to save your module:\n";
    getline(std::cin, name);
    if (name.empty()) return;
    else m_file.saveModule(name, m_module);
}

void Menu::openModule()
{
    std::string name;
    std::cout << "Write a name of the file to open your module:\n";
    getline(std::cin, name);
    if (name.empty()) return;
    else m_file.loadModule(name, m_module);
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
        clearScreen();
        std::cout << "=== Digital Logic Simulator ===\n";
        std::cout << "1. Add Component\n";
        std::cout << "2. Connect Connectors\n";
        std::cout << "3. Set Constant Input\n";
        std::cout << "4. Print Output\n";
        std::cout << "5. Print All Components\n";
        std::cout << "6. Remove Component\n";
        std::cout << "7. Save Module\n";
        std::cout << "8. Open Module\n";
        std::cout << "0. Exit\n> ";
        choice = getIntegerInput();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        switch (choice) {
        case 1:
            addComponent(); break;
        case 2: 
            connectComponents(); break;
        case 3: 
            setConstantInput(); break;
        case 4: 
            viewComponentOutput(); break;
        case 5: 
            viewAllComponents(); break;
        case 6:
            deleteComponent(); break;
        case 7:
            saveModule(); break;
        case 8:
            openModule(); break;
        case 0: exit(EXIT_SUCCESS); break;
        default: std::cout << "Invalid option.\n"; break;
        }
    } while (choice != 0);
}
