#ifndef OCCUPANCYGRID_H
#define OCCUPANCYGRID_H

#include"GridNode.h"
#include<utility>
#include<vector>
#include<iostream>
#include<algorithm>
#include"Localization.h"
#include"PolarGrid.h"
#include "Point.h"
using std::vector;
using std::pair;

class OccupancyGrid {
public:
	// Constructor
	OccupancyGrid(Localization* SE);
	// Function to search for end point
	//void SearchPolarPoint(pair<long long,long long>);
	// Function to reset TempGrid
	void UpdateTempGrid(vector<pair<float, float>> &Measurements);
	// Update the Location GridNode
	void UpdateLocation();
	// The main Update Map Function
	void Update(vector<pair<float, float>> Measurements);
private:
	GridNode* Location;
	GridNode Head;
	Localization* StateEstimator;
	PolarGrid TempGrid;
	vector<pair<long long, long long>> lidarReading;
	Point VehicleLocation;
};





#endif // !OCCUPANCYGRID_H

