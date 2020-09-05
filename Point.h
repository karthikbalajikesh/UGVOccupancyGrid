#ifndef POINT_H

#define POINT_H

#include<iostream>
#include<utility>
#include<vector>
#include<algorithm>
#include"GridNode.h"

class Point {
public:
	Point() {
		Location = NULL;
		indexX = 0;
		indexY = 0;
	}

	// member Variables
	GridNode* Location;
	int indexX;
	int indexY;

};


#endif // !POINT_H


