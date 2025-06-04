#include "File.h"

/* Example
#COMPONENTS (name, type, properties)
and1 AND 10
or1 OR 10
c1 CLOCK 10000 10000
#STATIC_IN (destGate, destPin, state)
and1 1 1
and1 2 1
or1 2 0
#CONNECTIONS (srcGate, destPin, destGate)
c1 1 or1
*/

void File::saveModule(const std::string& filename, Module& m)
{
    const auto& gates = m.returnGates();
    auto& clocks = m.returnClocks();
    const auto& constInputs = m.returnConstInputs();
    const auto& connections = m.returnConnections();
    std::ofstream m_file(filename);
    if (!m_file) {
        std::cerr << "Cannot open the file" << std::endl;
        return;
    }
    m_file << "#COMPONENTS\n";
    for (const auto& gate : gates) {
        m_file << gate.first << " " << gate.second->returnType() << " " << gate.second->getPropagationTime()<< "\n";
    }
    for (auto& clock : clocks) {
        m_file << clock.first << " CLOCK " << clock.second.getPeriod() << " " << clock.second.getEndTime()<< "\n";
    }
    m_file << "#STATIC_IN\n";
    for (const auto& constInput : constInputs) {
        m_file << constInput.destGate << " " << constInput.destPin << " " << constInput.state<< "\n";
    }
    m_file << "#CONNECTIONS\n";
    for (const auto& connection : connections) {
        m_file << connection.srcGate << " " << connection.destPin << " " << connection.destGate<< "\n";
    }
    m_file.close();
}

void File::loadModule(const std::string& filename, Module& m)
{
    const auto& gates = m.returnGates();
    std::ifstream m_file(filename);
    if (!m_file) {
        std::cerr << "Cannot open the file" << std::endl;
        return;
    }

    std::string line;
    std::string current_section;

    while (getline(m_file, line)) {
        if (line[0] == '#') {
            current_section = line; //save sectionn
            continue;
        }

        std::stringstream ss(line);

        if (current_section == "#COMPONENTS") {
            // Component section
            std::string name, type;
            double delay;
            ss >> name >> type;

            if (type == "AND") {
                double delay;
                ss >> delay;
                m.addGate(name, Type::AND, delay);
            }
            else if (type == "OR") {
                double delay;
                ss >> delay;
                m.addGate(name, Type::OR, delay);
            }
            else if (type == "XOR") {
                double delay;
                ss >> delay;
                m.addGate(name, Type::XOR, delay);
            }
            else if (type == "NOT") {
                double delay;
                ss >> delay;
                m.addGate(name, Type::NOT, delay);
            }
            else if (type == "CLOCK") {
                double period, endTime;
                ss >> period >> endTime;
                m.addClock(name, period, endTime);
            }
        }
        else if (current_section == "#STATIC_IN") {
            // Constant state section
            std::string name, pin, state;
            ss >> name >> pin >> state;
            m.connectConst(ConstInput(name, pin, state));
        }
        else if (current_section == "#CONNECTIONS") {
            // Connections section
            std::string src, dest, destPin;
            ss >> src >> destPin >> dest;
            m.connect(Connection(src, destPin, dest));
        }
    }
    m_file.close();
}
