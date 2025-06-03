#include "XORGate.h"

void XORGate::propagateOutput() {
    if (in.first.connected() && in.second.connected()) {
        std::vector<std::pair<double, State>> output;
        const std::vector<std::pair<double, State>>& a = in.first.getState();
        const std::vector<std::pair<double, State>>& b = in.second.getState();

        size_t i = 0, j = 0;
        State stateA = LOW, stateB = LOW;

        while (i < a.size() || j < b.size()) {
            double time;
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
            // XOR Gate condition
            State result = (stateA != stateB) ? HIGH : LOW;
            output.push_back(std::pair(time + m_propagationDelay, result));
        }
        output.erase(output.begin()); 
        out.setStateTimeline(output);
    }
}
std::string XORGate::returnType()
{
    return "XOR Gate";
}
int XORGate::getNumberOfInputs()
{
    return 2;
}
;