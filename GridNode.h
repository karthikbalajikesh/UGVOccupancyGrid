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
	GridNode(long long X, long long Y);
	// Destructor
	~GridNode();
	// Function to define endpoints
	void defineEndpoints();
	// Function to update Coordinates of Map
	void updateMapCoordinates();
	// Pointer Functions
	void initiatePointers();
	
	// Search and Query Functions
	// Function that returns true if a coordinate is in the 
	// bounds of the grid
	bool inGrid(long long x, long long y);
	std::pair<int, int> BinarySearch(long long x, long long y);
	
	
	// Expansion Related Functions
	void Expand();
	void Expand(std::vector<GridNode*> &GridNodeList);
	void CreateNodeEast();
	void CreateNodeWest();
	void CreateNodeNorth();
	void CreateNodeSouth();
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

	// Variables
	int SizeX;
	int SizeY;
	pair<long long, long long> BottomLeft;
	pair<long long, long long> BottomRight;
	pair<long long, long long> TopLeft;
	pair<long long, long long> TopRight;
	GridNode* West;
	GridNode* East;
	GridNode* North;
	GridNode* South;

	// Debug Functions
	void printCenter();
	

private:
	// range of grid in mm
	int Height; //xRange= 2000mm
	int Width; //yRange = 2000mm
	int ResolutionX; // = 20 mm - mm/cell
	int ResolutionY; // = 20 mm - mm/cell
	pair<long long, long long> Center;
	
	

};

#endif // !GRIDNODE_H

