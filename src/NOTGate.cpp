#include "NOTGate.h"

void NOTGate::propagateOutput()
{
    if (in.first.connected()) {
        std::vector<std::pair<double, State>> output;
        const std::vector<std::pair<double, State>>& a = in.first.getState();

        size_t i = 0;
        State stateA = LOW;

        while (i < a.size()) {
            double time;
            time = a[i].first;
            stateA = a[i].second;
            i++;

            // NOT Gate condition
            State result = (stateA == LOW) ? HIGH : LOW;
            output.push_back(std::pair(time + m_propagationTime, result));
        }
        out.setStateTimeline(output);
    }
}

std::string NOTGate::returnType()
{
	return "NOT";
}

int NOTGate::getNumberOfInputs()
{
    return 1;
}

