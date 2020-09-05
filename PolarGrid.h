#ifndef POLARGRID_H

#define POLARGRID_H
#include<iostream>
#include<utility>
#include<vector>
#include<algorithm>
#include "PolarNode.h"
#include "Localization.h"

using std::vector;
using std::pair;

class PolarGrid {
public:

	// float 1 - Angle Phi in degree decimal form
	// float 2 - Range R in mm
	typedef std::pair<float, float> reading;
	PolarGrid(Localization* SE);// Default constructor
	void updatePolarCoordinates();
	void updatePolarOccupancy(vector<reading> Measurements);
	std::pair<int, int> findNodeIndex(reading Measurement);
	// Function that transforms sensor measurements to Vehicle frame
	void transformCoordinates(vector<reading>& Measurements);
	// Function to reset the occupancy of the grid.
	void Reset();

private:
	vector<vector<PolarNode>> PolarMap;
	int SizeX, SizeY; // num of rows and columns
	Localization* StateEstimator;
};

#endif
