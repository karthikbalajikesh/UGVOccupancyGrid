#ifndef OCCUPANCYGRID_H
#define OCCUPANCYGRID_H

#include"GridNode.h"
#include<Eigen/Dense>
#include<utility>
#include<vector>
#include<iostream>
#include<algorithm>
#include"Localization.h"
#include"PolarGrid.h"
#include "Point.h"
#include"CartesianGrid.h"
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
	// Function that identifies location of point in grid
	Point BinarySearch(pair<float, float> coordinate);

private:
	GridNode* Location;
	GridNode Head;
	Localization* StateEstimator;
	PolarGrid TempGrid;
	CartesianGrid VehicleGrid;
	vector<pair<long long, long long>> lidarReading;
	Point VehicleLocation;
	Point BottomLeftLocation;

	// Auxillary functions
	pair<long long, long long> convertCoordinate(pair<float, float> Coordinate);
	GridNode* findGridNode(pair<long long, long long> Coordinate);
	// Function to create a radius 20 grid around the origin
	void constructPrimaryGrid();
};





#endif // !OCCUPANCYGRID_H

