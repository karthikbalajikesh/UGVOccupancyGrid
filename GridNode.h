#ifndef GRIDNODE_H
#define GRIDNODE_H


#include<iostream>
#include<utility>
#include<vector>
#include<algorithm>
#include<string>
#include "Node.h"

using std::vector;
using std::pair;
using std::cout;
using std::endl;
using std::string;

// Grid Node is every grid element that gets added to an oct tree of grids at high level. 
// This class has to hold the resolution, width and leaf GridNode Pointers. 
// The path planning is done with mm scale as integers.
// X is vehicle longitudinal axis and Y the lateral 
class GridNode {
public:
	typedef std::pair<long long, long long> Cood;
	// The grid
	vector<vector<Node>> Map;
	// Default Constructor - only 1st initiation
	GridNode();
	// Constructor with Center Point
	GridNode(long long &X, long long &Y);
	// Destructor
	~GridNode();
	// Function to define endpoints
	void defineEndpoints();
	// Function to update Coordinates of Map
	void updateMapCoordinates();
	// Pointer Functions
	void initiatePointers();
	// Pointer Return Functions

	void CreateNodeEast();
	void CreateNodeWest();
	void CreateNodeNorth();
	void CreateNodeSouth();
	
	// Expansion Related Functions
	void Expand();
	void EditConnectivityEast();
	void EditConnectivityWest();
	void EditConnectivityNorth();
	void EditConnectivitySouth();

	// Clockwise and AntiClockwise Search Functions
	void GoClockWiseNorth();
	void GoAntiClockWiseNorth();
	void GoClockWiseEast();
	void GoAntiClockWiseEast();
	void GoClockWiseWest();
	void GoAntiClockWiseWest();
	void GoClockWiseSouth();
	void GoAntiClockWiseSouth();


	GridNode* West;
	GridNode* East;
	GridNode* North;
	GridNode* South;
	// Debug Functions
	void printCenter();
	int SizeX;
	int SizeY;

private:
	// range of grid in mm
	int Height; //xRange= 2000mm
	int Width; //yRange = 2000mm
	int ResolutionX; // = 20 mm - mm/cell
	int ResolutionY; // = 20 mm - mm/cell
	pair<long long, long long> Center;
	pair<long long, long long> BottomLeft;
	pair<long long, long long> BottonRight;
	pair<long long, long long> TopLeft;
	pair<long long, long long> TopRight;
	

};

#endif // !GRIDNODE_H

