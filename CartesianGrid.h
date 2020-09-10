#ifndef CARTESIANGRID_H
#define CARTESIANGRID_H
#define _USE_MATH_DEFINES

#include<iostream>
#include<vector>
#include<utility>
#include<cmath>
#include<math.h>
#include"PolarGrid.h"
#include"Localization.h"

using std::vector;
using std::pair;

class CartesianNode {
public:
	////////////////////////////////////////
	// Default Constructor
	CartesianNode();
	////////////////////////////////////////
	// Function that returns true if given coordinate exists in Node
	bool CheckCoordinate(int xCoordinate, int yCoordinate);
	// Function that assigns occupancy to the Node
	void UpdateOccupancy(int occ);
	// Function that updates the Coordinate values from input
	void UpdateCoordinate(int xCoordinate, int yCoordinate);
	// Function that assigns a PolarNode value to pointer
	void assignPolarNode(PolarNode* Node);
	// Assign angle based on coordinates
	void assignAngle();
	/////////////////////////////////////////
	PolarNode* polar;
	int occupancy;
	double disttoCenter;
	double angle;

private:
	int width, height;
	std::pair<int, int> Center;
};

class CartesianGrid {
public:
	// Empty Constructor
	CartesianGrid();
	CartesianGrid(PolarGrid* Polar); // Default Constructor
	// Function that updates the coordinates
	void UpdateCoordinates();
	// Function that assigns Polar Nodes to every CartesianNode
	void UpdatePolarNodes();
	// Function to check whether node is within range
	bool WithinRange(int index1, int index2);

	/////////////////////////////////////////
	vector<vector<CartesianNode>> Map;
	PolarGrid* grid;
	pair<int, int> BottomLeft;
	pair<int, int> BottomRight;
	pair<int, int> TopLeft;
	pair<int, int> TopRight;
	int SizeX, SizeY;
	vector<pair<int, int>> InRange;
private:
	int Height, Width;
	int ResolutionX, ResolutionY;
	pair<int, int> Center;
};

#endif