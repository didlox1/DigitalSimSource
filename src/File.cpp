#include "File.h"

/* Example
#Components
and1 AND 10
or1 OR 10
c1 CLOCK 10000 10000
#STATIC_IN
and1 first 1
and1 second 1
or1 second 0
#CONNECTIONS
c1 FIRST or1
*/

void File::saveModule(const std::string& filename, const Module& m)
{
	std::ofstream m_file(filename);
}

void File::loadModule(const std::string& filename, Module& m)
{
    const auto& gates = m.returnGates();
    std::ifstream m_file(filename);
    if (!m_file.is_open()) {
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
        std::string token;

        if (current_section == "#COMPONENTS") {
            // Component section
            std::string name, type;
            ss >> name >> type;

            if (type == "AND") {
                int delay;
                ss >> delay;
                m.addGate(name, Type::AND, delay);
            }
            else if (type == "OR") {
                int delay;
                ss >> delay;
                m.addGate(name, Type::OR, delay);
            }
            else if (type == "XOR") {
                int delay;
                ss >> delay;
                m.addGate(name, Type::XOR, delay);
            }
            else if (type == "NOT") {
                int delay;
                ss >> delay;
                m.addGate(name, Type::NOT, delay);
            }
            else if (type == "CLOCK") {
                int period, endTime;
                ss >> period >> endTime;
                m.addClock(name, period, endTime);
            }
        }
        else if (current_section == "#STATIC_IN") {
            // Constant state section
            std::string component, pin, value;
            ss >> component >> pin >> value;
            if (value == "0") {
                if (pin == "first") {
                    gates.find(component)->second->getInput().first.setState(State::LOW);
                }
                else if (pin == "second") {
                    gates.find(component)->second->getInput().second.setState(State::LOW);
                }
            }
            else if (value == "1") {
                if (pin == "first") {
                    gates.find(component)->second->getInput().second.setState(State::HIGH);
                }
                else if (pin == "second") {
                    gates.find(component)->second->getInput().second.setState(State::LOW);
                }
            }
        }
        else if (current_section == "#CONNECTIONS") {
            // Connections section
            std::string src, dest, destPin; // TODO: do that one
            ss >> src >> destPin >> dest;
            //m.connect(Connection(src, destPin, dest)); // TODO: do connect() ???
        }
    }
}
