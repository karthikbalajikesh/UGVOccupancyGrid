#include "Node.h"

// Default Constructor
Node::Node() :coordinates({ 0,0 }), probability(0.5) {}

// Overloaded Constructor with Float values
Node::Node(float x, float y):coordinates({x,y}),probability(0.5){}

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

// Update Coordinates from the input arguments
void Node::UpdateCoordinates(float x, float y) {
	// update the coordinates from the input 
	this->coordinates = std::make_pair(x, y);
}

// Update Probability
void Node::UpdateProbability(float prob) {
	this->probability = prob;
}
