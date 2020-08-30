#include "Localization.h"

Localization::Localization() {
	// empty constructor which initializes pose to 0;
	state = VectorXd(3);
	state <<0,0,0;
	publicizeState();
}

void Localization::publicizeState() {
	x = state(0); // in m
	y = state(1); // in m
	theta = state(2); // in m
}

void Localization::printState() {
	std::cout << state << std::endl;
}
