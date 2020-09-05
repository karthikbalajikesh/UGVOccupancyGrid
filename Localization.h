#ifndef LOCALIZATION_H

#define LOCALIZATION_H

#include<iostream>
#include<Eigen/Dense>
#include<vector>

using std::vector;

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
private:
	VectorXf state; // x in m, y in m and theta in degrees

};



#endif
