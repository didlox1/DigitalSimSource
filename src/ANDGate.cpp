#include "ANDGate.h"

void ANDGate::propagateOutput() {
    // TODO: dodac warunek ze podlaczone
    // if (in.first.connected() && in.second.connected()) 
    // else throw exception
    std::vector<std::pair<int, State>> output;
    const std::vector<std::pair<int, State>>& a = in.first.getState();
    const std::vector<std::pair<int, State>>& b = in.second.getState();

    size_t i = 0, j = 0;
    State stateA = LOW, stateB = LOW;

    while (i < a.size() || j < b.size()) {
        int time;
        if (i < a.size() && (j >= b.size() || a[i].first <= b[j].first)) {
            time = a[i].first;
            stateA = a[i].second;
            i++;
        }
        else {
            time = b[j].first;
            stateB = b[j].second;
            j++;
        }

        State result = (stateA == HIGH && stateB == HIGH) ? HIGH : LOW;
        output.emplace_back(time + m_propagationDelay, result);
    }
    out.setStateTimeline(output);
};