#ifndef POLARGRID_H

#define POLARGRID_H
#include<iostream>
#include<utility>
#include<vector>
#include<algorithm>

using std::vector;

class PolarGrid {
public:

	// float 1 - Angle Phi in rad
	// float 2 - Range R in mm
	typedef std::pair<float, float> reading;
	PolarGrid();// Default constructor
	PolarGrid(vector<reading>& Measurements);// Constructor that creates temp Grid

};

#endif
