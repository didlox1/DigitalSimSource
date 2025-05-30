#include "Gate.h"

// TODO: Change setState() to setTimeline(outState)
// where outState = vector<pair<time + porpagationTime, State>>
// where "+" means shifting it by selected value

class BufforGate : public Gate{
private:
public:
	BufforGate() : Gate() {}; //dodaæ Gate(int n) gdzie n to liczba wejœæ bramki
	void propagateOutput() override;
};