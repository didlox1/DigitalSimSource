#include "Module.h"

#include <iostream>
#include <utility>
#include "ANDGate.h"

// TODO: Automatization of adding gates

int main(int argc, char* argv[]) { //Benchmark
    Module m;
    //Creating ANDGate
    std::shared_ptr<ANDGate> and1 = std::make_shared<ANDGate>();
    m.addGate(and1);
    //Getting Gate handler
    std::shared_ptr<Gate> g1 = m.getGate(0);
    //Getting connectors 
    Connector& in1 = g1->getInput().first;
    Connector& in2 = g1->getInput().second;
    Connector& out = g1->getOutputHandler();
    //Seting connectors state
    in1.setState(State::HIGH);
    in2.setState(State::HIGH);
    //Propagate an output 
    g1->propagateOutput();
    std::cout << out.getState() << std::endl;  // (1 AND 1) Should print 1 (HIGH)
    
    return 0;
}