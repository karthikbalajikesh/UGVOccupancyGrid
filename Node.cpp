#include "Node.h"
#include<iostream>
// Default Constructor
Node::Node() :coordinates({ 0,0 }), probability(0.5), ResolutionX(20), ResolutionY(20) {}

// Overloaded Constructor with long long values
Node::Node(long long &x, long long &y):coordinates({x,y}), probability(0.5), ResolutionX(20), ResolutionY(20){}
						 

// Overloaded Constructor with float values in meter
Node::Node(float x, float y):coordinates({x*1000.0,y*1000.0}), probability(0.5), ResolutionX(20), ResolutionY(20) {}

// Check Occupancy function
bool Node::CheckOccupancy() {
	// if probability less than 0.35 , return false, else true
	if (this->probability < 0.35) {
		return false;
	}
	else {
		return true;
	}
}

// Function that returns true when a coordinate is present in a cell
bool Node::CheckCoordinate(long long x, long long y) {
	if (x < (coordinates.first + (ResolutionX / 2)) &&
		x >= (coordinates.first - (ResolutionX / 2))) {
		if (y > (coordinates.second - (ResolutionY / 2)) &&
			(y <= (coordinates.second + (ResolutionY / 2)))) {
			return true;
		}
	}
	return false;
}

// Update Coordinates from the input arguments
void Node::UpdateCoordinates(long long &x, long long &y) {
	// update the coordinates from the input 
	this->coordinates = std::make_pair(x, y);
}

void Node::UpdateCoordinates(float x, float y) {
	// update the coordinates from the input 
	coordinates.first = x * 1000.0;
	coordinates.second = y * 1000.0;
}

// Update Probability
void Node::UpdateProbability(float prob) {
	this->probability = prob;
}

// Get coordinates of the center
std::pair<long long, long long> Node::getCenterCoordinates() {
	return coordinates;
}

std::vector<long long> Node::getbounds() {
	// x max, xmin , y max and ymin
	std::vector<long long> Bounds(4, 0);
	Bounds[0] = coordinates.first + (ResolutionX / 2);
	Bounds[1] = coordinates.first - (ResolutionX / 2);
	Bounds[2] = coordinates.second + (ResolutionY / 2);
	Bounds[3] = coordinates.second - (ResolutionY / 2);

	return Bounds;
}