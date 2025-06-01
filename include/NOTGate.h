#include "Gate.h"

// TODO: Change setState() to setTimeline(outState)
// where outState = vector<pair<time + porpagationTime, State>>
// where "+" means shifting it by selected value

class NOTGate: public Gate{
private:
public:
	NOTGate() : Gate() {}; //dodac Gate(int n) gdzie n to liczba wejsc bramki
	void propagateOutput() override;
	std::string returnType() override;
};