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
	// Vector of GridNode pointers for sampling
	std::vector<GridNode*> GridNodeList;

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
	void constructFirstQuadrant();
	void constructSecondQuadrant();
	void constructThirdQuadrant();
	void constructFourthQuadrant();
	// This is the main function that calculates index locations. 
	void UpdateGrid();
	// Function calculates the required index in the required GridNode based on the
	// cartesian Node coordinate
	Point findMapNode(pair<int,int> cell);
	// Function that returns the inverse sensor model value for update
	float inverseSensorModel(pair<int, int> CartesianIndex);
	// Log odds update 
	void updateLogOdds(Point &node, float LogOdds);
	// make the initial blind short region as free. Required for path planning
	void setPriors();
	// construct the initial 150 mm circle
	vector<pair<float, float>> constructMiniCircle();

};





#endif // !OCCUPANCYGRID_H

