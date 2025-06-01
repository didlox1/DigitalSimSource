#include "ORGate.h"

void ORGate::propagateOutput() {
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
        // OR Gate condition
        State result = (stateA == LOW && stateB == LOW) ? LOW : HIGH;
        output.emplace_back(time + m_propagationDelay, result);
    }
    output.erase(output.begin()); // TODO: validate if always works - created to erase first {0, 0} pair
    out.setStateTimeline(output);
}
std::string ORGate::returnType()
{
    return "OR Gate";
}
;