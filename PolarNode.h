#ifndef POLARNODE_H

#define POLARNODE_H

#include<utility>
class PolarNode {
public:
	PolarNode();
	PolarNode()


private:

	std::pair<int, int> TopLeft;
	std::pair<int, int> TopRight;
	std::pair<int, int> BottomLeft;
	std::pair<int, int> BottomRight;
	int occupancy;  // 0 - Not occupied, 1 - unknown, 2 - Occupied
	int width = 10; //deg
	int height = 30; //mm
};

#endif