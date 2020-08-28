#ifndef NODE_H

#include<utility>

#define NODE_H

class Node {
public:
	typedef std::pair<long long, long long> Cood;
	// Default construtor which assigns (0,0) and 0.5 Prob
	Node();
	// Constructor that assigns (x,y) and 0.5 prob
	Node(long long &x, long long &y);
	// Constructor that assigns (x,y) and 0.5 prob receiving floating points
	Node(float x, float y);
	// Function to return occupancy
	bool CheckOccupancy();
	// Function to update Coordinates from the arguments
	void UpdateCoordinates(long long &x, long long &y);
	// Function to updae Coordinates from float arguments in meter
	void UpdateCoordinates(float x, float y);
	// Function to update the Probability by Log odds
	void UpdateProbability(float prob);
	// Function that returns coordinates of center
	Cood getCenterCoordinates();

	

private:
	std::pair<long long, long long> coordinates;
	float probability;
	
};


#endif // !NODE_H


