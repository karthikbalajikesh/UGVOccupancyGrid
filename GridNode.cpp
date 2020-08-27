#include "GridNode.h"

GridNode::GridNode():ResolutionX(20),ResolutionY(20),
			Height(2000), Width(2000),
	Center({Height/2,0}) {
	/*
	Constructor to create a 2D vector of Coordinates,
	with Global center = Local center.
	*/
	// Create Empty Vector of Nodes of appropriate Size
	Map = vector<vector<Node>>(Height / ResolutionX,
						vector<Node>(Width/ResolutionY));
	defineEndpoints();
	initiatePointers();
	updateMapCoordinates();

}

GridNode::GridNode(long long& X, long long& Y):
	Center({X,Y}),ResolutionX(20),ResolutionY(20),
	Height(2000),Width(2000){
	initiatePointers();
	defineEndpoints();
	updateMapCoordinates();
}

GridNode::~GridNode() {
	delete East;
	delete West;
	delete North;
	delete South;
	delete NorthEast;
	delete SouthEast;
	delete SouthWest;
	delete NorthWest;
}

// Function that defines the endpoints in mm
void GridNode::defineEndpoints() {
	BottomLeft = { Center.first - (Height / 2),
				Center.second + (Width / 2) };
	BottonRight = {BottomLeft.first,
				Center.second - (Width / 2) };
	TopLeft = { BottomLeft.first + Height, 
				BottomLeft.second };
	TopRight = { TopLeft.first,
				BottonRight.second };

}

// Function to update the coordinates of cells in map
void GridNode::updateMapCoordinates() {
	int multiplierX = 1;
	int multiplierY = 1;
	for (auto x : Map) {
		for (auto y : x) {
			y.UpdateCoordinates(multiplierX*ResolutionX/2,
						multiplierY*(-ResolutionY)/2);
			multiplierY += 2;
		}
		multiplierX += 2;
		multiplierY = 1;
	}
}


/////////////////Pointer Functions//////////////
void GridNode::initiatePointers() {
	East = NULL;
	West = NULL;
	North = NULL;
	South = NULL;
	NorthEast = NULL;
	NorthWest = NULL;
	SouthEast = NULL;
	SouthWest = NULL;
}

// Function Returns pointer of East Node
GridNode* GridNode::GetEast() {
	return East;
}

// Function returns pointer of west node
GridNode* GridNode::GetWest() {
	return West;
}

//Function returns pointer of north node
GridNode* GridNode::GetNorth() {
	return North;
}

// Function returns pointer to south node
GridNode* GridNode::GetSouth() {
	return South;
}

//Function returns pointer of southeast node
GridNode* GridNode::GetSouthEast() {
	return SouthEast;
}

//Function returns pointer to southwest node
GridNode* GridNode::GetSouthWest() {
	return SouthWest;
}

//Function returns pointer to northeast node
GridNode* GridNode::GetNorthEast() {
	return NorthEast;
}

//Function returns pointer to northwest node
GridNode* GridNode::GetNorthWest() {
	return NorthWest;
}

// Function to create a GridNode in the East
void GridNode::CreateNodeEast() {
	long long x = Center.first;
	long long y = Center.second - Width;
	East = new GridNode(x,y);
}

// Function to create a GridNode in the West
void GridNode::CreateNodeWest() {
	long long x = Center.first;
	long long y = Center.second + Width;
	West = new GridNode(x,y);
}

// Function to create a GridNode in the North
void GridNode::CreateNodeNorth() {
	long long x = Center.first + Height;
	long long y = Center.second;
	North = new GridNode(x,y);
}

//Function to create GridNode in the South
void GridNode::CreateNodeSouth() {
	long long x = Center.first - Height;
	long long y = Center.second;
	South = new GridNode(x,y);
}

//Function to create GridNode in the NorthEast
void GridNode::CreateNodeNorthEast() {
	long long x = Center.first + Height;
	long long y = Center.second - Width;
	NorthEast = new GridNode(x,y);
}

//Function to create GridNode in NorthWest
void GridNode::CreateNodeNorthWest() {
	long long x = Center.first + Height;
	long long y = Center.second + Width;
	NorthWest = new GridNode(x,y);
}

//Function to create GridNode in the SouthEast
void GridNode::CreateNodeSouthEast() {
	long long x = Center.first - Height;
	long long y = Center.second - Width;
	SouthEast = new GridNode(x,y);
}

//Function to create GridNode in the SouthWest
void GridNode::CreateNodeSouthWest() {
	long long x = Center.first - Height;
	long long y = Center.second + Width;
	SouthWest = new GridNode(x,y);
}

void GridNode::printCenter() {
	std::cout << " The coordinate is (" << Center.first 
		<< "\t" << Center.second << ")" << std::endl;

}

