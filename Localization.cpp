#include "Localization.h"

Localization::Localization() {
	state = VectorXd(3);
	state << 1, 2, 3;
}

void Localization::printState() {
	std::cout << state << std::endl;
}
