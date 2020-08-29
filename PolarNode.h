#ifndef POLARNODE_H

#define POLARNODE_H

#include<utility>
#include<vector>

using std::vector;

class PolarNode {
public:
	PolarNode();
	PolarNode(std::pair<int, int> BL);
	void updateCoordinates(std::pair<int, int> BL);
	void updateOccupancy(int occ);
	bool checkCoordinate(std::pair<float, float> Reading);
	// Width and Height
	int width = 10; //deg
	int height = 30; //mm
	vector<int> getBounds(); // in the form R_up, R_low, Phi_up, Phi_low
private:

	std::pair<int, int> TopLeft;
	std::pair<int, int> TopRight;
	std::pair<int, int> BottomLeft;
	std::pair<int, int> BottomRight;
	int occupancy;  // 0 - Not occupied, 1 - unknown, 2 - Occupied
	
};

#endif