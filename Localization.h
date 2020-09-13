#ifndef LOCALIZATION_H

#define LOCALIZATION_H

#include<iostream>
#include<Eigen/Dense>
#include<vector>
#include<utility>

using std::pair;
using std::vector;
using std::make_pair;
using Eigen::VectorXf;

class Localization {
public:
	float x;
	float y;
	float theta;
		
	Localization();
	void printState();
	void publicizeState();
	vector<long long> getState();
	// Function that returns angle in degrees in float
	// for polar grid
	float getAngle();
	// function that returns a pair for floats indicating 
	// coordinates in meters. 
	pair<float, float> getVehicleCoordinates();
	void updateState(float x, float y, float theta);
private:
	VectorXf state; // x in m, y in m and theta in degrees

};



#endif
