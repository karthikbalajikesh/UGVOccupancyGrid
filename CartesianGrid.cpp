#include "CartesianGrid.h"

// empty constructor
CartesianNode::CartesianNode() :height(20), width(20),
occupancy(0), Center({ 0,0 }), polar(NULL), angle(0),disttoCenter(0) {}

bool CartesianNode::CheckCoordinate(int xCoordinate, int yCoordinate) {
	if (xCoordinate < (Center.first + (height / 2)) &&
		xCoordinate >= (Center.first - (height / 2))){
		if (yCoordinate > (Center.second  - (width/2)) && 
			(yCoordinate <= (Center.second + (width/2)))) {
			return true;
		}
	}
	return false;
}

void CartesianNode::UpdateOccupancy(int occ) {
	this->occupancy = occ;
}

void CartesianNode::UpdateCoordinate(int xCoordinate, int yCoordinate) {
	Center.first = xCoordinate;
	Center.second = yCoordinate;
	disttoCenter = sqrt(pow(xCoordinate, 2) + pow(yCoordinate, 2));
	assignAngle();

}

void CartesianNode::assignPolarNode(PolarNode* Node) {
	polar = Node;
}

void CartesianNode::assignAngle() {
	double theta = (atan((double)Center.second / (double)Center.first)) * (180 / M_PI);
	if (Center.first >= 0 && Center.second >= 0) {
		angle = theta;
	}else if (Center.first < 0 && Center.second >= 0) {
		angle = 180 + theta;
	}else if (Center.first < 0 && Center.second < 0) {
		angle = 180 + theta;
	}else if (Center.first >= 0 && Center.second < 0) {
		angle = 360 + theta;
	}


}

///////////////////// CARTESIAN GRID /////////////////////

CartesianGrid::CartesianGrid() {

}


CartesianGrid::CartesianGrid(PolarGrid* Polar): grid(Polar),
	Center({0,0}), BottomLeft({ -3000,3000 }),BottomRight({-3000,-3000}),
	TopLeft({3000,3000}),TopRight({3000,-3000}),
	Height(6000), Width(6000), ResolutionX(20), ResolutionY(20)	{
	SizeX = (Height / ResolutionX);
	SizeY = (Width / ResolutionY);
	Map = (vector<vector<CartesianNode>>(SizeX, vector<CartesianNode>(SizeY)));
	UpdateCoordinates();
	UpdatePolarNodes();
	

}

void CartesianGrid::UpdateCoordinates() {
	int multiplierX = 1;
	int multiplierY = 1;
	for (int i = 0;i < SizeX;i++) {
		for (int j = 0;j < SizeY;j++) {
			int x = BottomLeft.first + (multiplierX * (int)(ResolutionX / 2));
			int y = BottomLeft.second - (multiplierY * (int)(ResolutionY / 2));
			Map[i][j].UpdateCoordinate(x, y);
			multiplierY += 2;
		}
		multiplierY = 1;
		multiplierX += 2;

	}
}

void CartesianGrid::UpdatePolarNodes() {
	/*
	The function scans every element in the Cartesian Grid,
	transforms into vehicle polar coordinate and finds the polar
	node that contains the polar coordinate if it belongs in the 
	measurement radius, and assigns the pointer value. If it is outside 
	the range, the Pointer remains NULL
	*/
	
	for (int i = 0; i < SizeX; i++) {
		for (int j = 0; j < SizeY;j++) {
			if (WithinRange(i, j)) {
				std::pair<int, int> indices = grid->findNodeIndex(Map[i][j].angle, Map[i][j].disttoCenter);
				Map[i][j].assignPolarNode(grid->getPointer(indices.first, indices.second));
				InRange.push_back(std::make_pair(i, j));
			}
			else {
				// if out of range, assign Null pointer and unknown occupancy
				Map[i][j].assignPolarNode(NULL);
				Map[i][j].UpdateOccupancy(1);
			}
			
		}

	}
	
}

bool CartesianGrid::WithinRange(int index1, int index2) {
	// first we search if it is outside radius of 3m
	CartesianNode* node = &Map[index1][index2];
	if (node->disttoCenter < 3000) {
		// next check if it is over 0.15 m
		if (node->disttoCenter >= 150) {
			return true;
		}
	}
	return false;
}
