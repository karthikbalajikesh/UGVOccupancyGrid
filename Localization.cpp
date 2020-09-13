#include "Localization.h"

Localization::Localization() {
	// empty constructor which initializes pose to 0;
	state = VectorXf(3);
	state <<0,0,0;
	publicizeState();
}

void Localization::publicizeState() {
	x = state(0); // in m
	y = state(1); // in m
	theta = state(2); // in degrees
}

void Localization::printState() {
	std::cout << state << std::endl;
}

std::vector<long long> Localization::getState() {
	std::vector<long long> result(3,0);
	result[0] = (long long)(state(0) * 1000.0);
	result[1] = (long long)(state(1) * 1000.0);
	result[2] = (long long)theta;

	return result;
}

float Localization::getAngle() {
	// return the angle for coordinate transform at PolarGrid
	return state(2);
}

pair<float, float> Localization::getVehicleCoordinates() {
	// Function returns the coordinate
	return make_pair(state(0), state(1));
}

void Localization::updateState(float x, float y, float theta) {
	state(0) = x;
	state(1) = y;
	state(2) = theta;
}