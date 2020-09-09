#include "PolarNode.h"
#include <cmath>


PolarNode::PolarNode() :BottomLeft({ 0,60 }), BottomRight({ 10,60 }),
TopLeft({ 0,90 }), TopRight({10,90}),occupancy(0) {

}

PolarNode::PolarNode(std::pair<int, int> BL) : BottomLeft(BL),occupancy(0){
	BottomRight = std::make_pair(BL.first + width, BL.second);
	TopLeft = std::make_pair(BL.first, BL.second + height);
	TopRight = std::make_pair(BL.first + width, BL.second + height);

}

void PolarNode::updateCoordinates(std::pair<int, int> BL) {
	BottomLeft = BL;
	BottomRight = std::make_pair(BL.first + width, BL.second);
	TopLeft = std::make_pair(BL.first, BL.second + height);
	TopRight = std::make_pair(BL.first + width, BL.second + height);
}

void PolarNode::updateOccupancy(int occ) {
	occupancy = occ;
}

bool PolarNode::checkCoordinate(std::pair<float, float> reading) {
	/* Function to check whether a given coordinate is present
	inside the current node*/
	int ReadingPhi = (int)std::round(reading.first);
	if (ReadingPhi == 360) {
		ReadingPhi = 359;
	}
	
	int ReadingR = (int)std::round(reading.second);
	if (ReadingR == 3000) {
		ReadingR = 2999;
	}
	if ((ReadingPhi >= BottomLeft.first) && (ReadingPhi < BottomRight.first)) {
		if ((ReadingR >= BottomLeft.second) && (ReadingR < TopLeft.second)) {
			return true;
		}
	}

	return false;
}

std::vector<int> PolarNode::getBounds() {
	/*
		Function that returns the boundaries of the current node in 
		the order of R_up, R_low, Phi_up and Phi_low.
	*/
	std::vector<int> result(4, 0);
	result[0] = TopLeft.second;
	result[1] = BottomLeft.second;
	result[2] = BottomRight.first;
	result[3] = BottomLeft.first;

	return result;
}

