#ifndef NODE_H

#include<utility>

#define NODE_H

class Node {
public:
	// Default construtor which assigns (0,0) and 0.5 Prob
	Node();
	// Constructor that assigns (x,y) and 0.5 prob
	Node(float x, float y);
	// Function to return occupancy
	bool CheckOccupancy();
	// Function to update Coordinates from the arguments
	void UpdateCoordinates(float x, float y);
	// Function to update the Probability by Log odds
	void UpdateProbability(float prob);
private:
	std::pair<float, float> coordinates;
	float probability;
	
};


#endif // !NODE_H


