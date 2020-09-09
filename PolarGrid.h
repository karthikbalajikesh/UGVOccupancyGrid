#ifndef POLARGRID_H

#define POLARGRID_H
#include<iostream>
#include<utility>
#include<vector>
#include<algorithm>
#include<cmath>
#include "PolarNode.h"
#include "Localization.h"

using std::vector;
using std::pair;



class PolarGrid {
public:

	// float 1 - Angle Phi in degree decimal form
	// float 2 - Range R in mm
	typedef std::pair<float, float> reading;
	
	//////////////////////////////////////////////////
	PolarGrid(Localization* SE);// Default constructor
	//////////////////////////////////////////////////
	void updatePolarCoordinates();
	void updatePolarOccupancy(vector<reading> Measurements);
	std::pair<int, int> findNodeIndex(std::pair<float,float> Measurement);
	std::pair<int, int> findNodeIndex(double angle, double range);
	// Function that transforms sensor measurements to Vehicle frame
	void transformCoordinates(vector<reading>& Measurements);
	// Function to reset the occupancy of the grid.
	void Reset();
	// Function to add to the vector of Obstacles
	void AddObstacle(int index1, int index2);
	// Function to add unknown to the vector of unknowns
	void AddUnknown(int index1, int index2);
	// Function that returns pointer of Polar Node in indices
	PolarNode* getPointer(int index1, int index2);
	/////////////////////////////////////////////////
	// vectors of obstacles and unknowns
	std::vector<std::pair<int, int>> Obstacles;
	std::vector<std::pair<int, int>> Unknown;
    /////////////////////////////////////////////////
private:
	vector<vector<PolarNode>> PolarMap;
	int SizeX, SizeY; // num of rows and columns
	Localization* StateEstimator;
};

#endif
