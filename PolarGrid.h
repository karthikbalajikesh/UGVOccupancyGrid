#ifndef POLARGRID_H

#define POLARGRID_H
#include<iostream>
#include<utility>
#include<vector>
#include<algorithm>
#include "PolarNode.h"

using std::vector;

class PolarGrid {
public:

	// float 1 - Angle Phi in rad
	// float 2 - Range R in mm
	typedef std::pair<float, float> reading;
	PolarGrid();// Default constructor
	PolarGrid(vector<reading>& Measurements);// Constructor that creates temp Grid
	void updatePolarCoordinates();
	void updatePolarOccupancy(vector<reading> Measurements);
	std::pair<int, int> findNodeIndex(reading Measurement);
private:
	vector<vector<PolarNode>> PolarMap;
	int SizeX, SizeY; // num of rows and columns
};

#endif
