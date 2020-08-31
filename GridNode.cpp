#include "GridNode.h"

GridNode::GridNode() :ResolutionX(20), ResolutionY(20),
Height(2000), Width(2000),
Center({ Height / 2,0 }) {
	/*
	Constructor to create a 2D vector of Coordinates,
	with Global center = Local center.
	*/
	// Create Empty Vector of Nodes of appropriate Size
	Map = vector<vector<Node>>(Height / ResolutionX,
		vector<Node>(Width / ResolutionY));
	SizeX = Height / ResolutionX;
	SizeY = Width / ResolutionY;
	defineEndpoints();
	initiatePointers();
	updateMapCoordinates();
}

GridNode::GridNode(long long& X, long long& Y):
	Center({X,Y}),ResolutionX(20),ResolutionY(20),
	Height(2000),Width(2000){
	Map = vector<vector<Node>>(Height / ResolutionX,
		vector<Node>(Width / ResolutionY));
	SizeX = Height / ResolutionX;
	SizeY = Width / ResolutionY;
	initiatePointers();
	defineEndpoints();
	updateMapCoordinates();
	
}

GridNode::~GridNode() {
	delete East;
	delete West;
	delete North;
	delete South;
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
	for(int i = 0;i<SizeY;i++){
		for(int j =0;j<SizeX;j++){
			long long X = BottomLeft.first + (multiplierX * (long long)(ResolutionX / 2));
			long long Y = BottomLeft.second - (multiplierY * (long long)(ResolutionY / 2));
			Map[i][j].UpdateCoordinates(X,Y);
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
}

// Function to create a GridNode in the East
void GridNode::CreateNodeEast() {
	long long x = Center.first;
	long long y = Center.second - Width;
	East = new GridNode(x,y);
	// When we create east, we need to create north east,
	// south east and update the required coordinates. 
	East->West = this;
}

// Function to create a GridNode in the West
void GridNode::CreateNodeWest() {
	long long x = Center.first;
	long long y = Center.second + Width;
	West = new GridNode(x,y);
	// edit connectivity
	West->East = this;
}

// Function to create a GridNode in the North
void GridNode::CreateNodeNorth() {
	long long x = Center.first + Height;
	long long y = Center.second;

	North = new GridNode(x,y);
	North->South = this;
}

//Function to create GridNode in the South
void GridNode::CreateNodeSouth() {
	long long x = Center.first - Height;
	long long y = Center.second;
	
	South = new GridNode(x,y);
	South->North = this;
}

///////////////// Edit Connectivity Functions //////////////
void GridNode::EditConnectivityEast() {
	/* The function will edit the pointers in the east node
	by searching clockwise and anticlockwise.
	*/

	// 1 .  ClockWise
	GoClockWiseEast();
	if (this->East->North != NULL && this->East->East != NULL &&
		this->East->South != NULL) {
		// return as all pointers are updated
		return;
	}
	GoAntiClockWiseEast();
	


}

void GridNode::EditConnectivityWest() {
	/* The function will edit the pointers in the west node
	by searching clockwise and anticlockwise.
	*/
	GoClockWiseWest();
	if (this->West->North != NULL && this->West->South != NULL &&
		this->West->West != NULL) {
		return;
	}
	GoAntiClockWiseWest();
}

void GridNode::EditConnectivityNorth() {
	/*
	This function adds all the pointers to the neighbours for a node 
	created to the north of the current gridnode.
	*/
	GoClockWiseNorth();
	if (this->North->East != NULL && this->North->North != NULL &&
		this->North->West != NULL) {
		return;
	}
	GoAntiClockWiseNorth();
}

void GridNode::EditConnectivitySouth() {
	/*
	This function adds all the pointers to the neighbours for a node
	created to the South of the current gridnode.
	*/
	GoClockWiseSouth();
	if (this->South->South != NULL && this->South->West != NULL &&
		this->South->East != NULL) {
		return;
	}
	GoAntiClockWiseSouth();
}

//////////////// EXPANSION FUNCTION /////////////////////////
void GridNode::Expand() {
	// first North
	if (this->North == NULL) {
		CreateNodeNorth();
		EditConnectivityNorth();
	} 
	if (this->East == NULL) {
		CreateNodeEast();
		EditConnectivityEast();
	}
	if (this->South == NULL) {
		CreateNodeSouth();
		EditConnectivitySouth();
	}
	if (this->West == NULL) {
		CreateNodeWest();
		EditConnectivityWest();
	}
}

void GridNode::GoClockWiseEast() {
	GridNode* Current = this;
	GridNode* Target = this->East;
	if (this->North != NULL) {
		Current = Current->North;
		if (Current->East != NULL) {
			// this means we need to add a node to north of the target
			Current = Current->East;
			Current->South = Target;
			Target->North = Current;
			// Now we progress further to east to check for the east of target
			if (Current->East != NULL) {
				Current = Current->East;
				if (Current->South != NULL) {
					// This means there is a node east of the target
					Current = Current->South;
					Current->West = Target;
					Target->East = Current;
					// Finally We check for the south
					if (Current->South != NULL) {
						Current = Current->South;
						if (Current->West != NULL) {
							// This means we have a node south of target
							Current = Current->West;
							Current->North = Target;
							Target->South = Current;
						}
					}
				}
			}
		}
	}
}

void GridNode::GoAntiClockWiseEast() {
	GridNode* Current = this;
	GridNode* Target = this->East;
	if (this->South != NULL) {
		Current = Current->South;
		if (Current->East != NULL) {
			// this means we need to add a node to south of the target
			Current = Current->East;
			Current->North = Target;
			Target->South = Current;
			// Now we progress further to east to check for the east of target
			if (Current->East != NULL) {
				Current = Current->East;
				if (Current->North != NULL) {
					// This means there is a node east of the target
					Current = Current->North;
					Current->West = Target;
					Target->East = Current;
					// Finally We check for the north
					if (Current->North != NULL) {
						Current = Current->North;
						if (Current->West != NULL) {
							// This means we have a node north of target
							Current = Current->West;
							Current->South = Target;
							Target->North = Current;
						}
					}
				}
			}
		}
	}
}

void GridNode::GoClockWiseNorth() {
	GridNode* Current = this;
	GridNode* Target = this->North;
	if (this->West != NULL) {
		Current = Current->West;
		if (Current->North != NULL) {
			// this means we need to add a node to west of the target
			Current = Current->North;
			Current->East = Target;
			Target->West = Current;
			// Now we progress further to east to check for the east of target
			if (Current->North != NULL) {
				Current = Current->North;
				if (Current->East != NULL) {
					// This means there is a node North of the target
					Current = Current->East;
					Current->South = Target;
					Target->North = Current;
					// Finally We check for the East
					if (Current->East != NULL) {
						Current = Current->East;
						if (Current->South != NULL) {
							// This means we have a node east of target
							Current = Current->South;
							Current->West = Target;
							Target->East = Current;
						}
					}
				}
			}
		}
	}
}

void GridNode::GoAntiClockWiseNorth() {
	GridNode* Current = this;
	GridNode* Target = this->North;
	if (this->East != NULL) {
		Current = Current->East;
		if (Current->North != NULL) {
			// this means we need to add a node to East of the target
			Current = Current->North;
			Current->West = Target;
			Target->East = Current;
			// Now we progress further to north to check 
			//for the north of target
			if (Current->North != NULL) {
				Current = Current->North;
				if (Current->West != NULL) {
					// This means there is a node east of the target
					Current = Current->West;
					Current->South = Target;
					Target->North = Current;
					// Finally We check for the West
					if (Current->West != NULL) {
						Current = Current->West;
						if (Current->South != NULL) {
							// This means we have a node south of target
							Current = Current->South;
							Current->East = Target;
							Target->West = Current;
						}
					}
				}
			}
		}
	}
}

void GridNode::GoClockWiseWest() {
	GridNode* Current = this;
	GridNode* Target = this->West;
	if (this->South != NULL) {
		Current = Current->South;
		if (Current->West != NULL) {
			// this means we need to add a node to South of the target
			Current = Current->West;
			Current->North = Target;
			Target->South = Current;
			// Now we progress further to east to check for the east of target
			if (Current->West != NULL) {
				Current = Current->West;
				if (Current->North != NULL) {
					// This means there is a node west of the target
					Current = Current->North;
					Current->East = Target;
					Target->West = Current;
					// Finally We check for the north
					if (Current->North != NULL) {
						Current = Current->North;
						if (Current->East != NULL) {
							// This means we have a node North of target
							Current = Current->East;
							Current->South = Target;
							Target->North = Current;
						}
					}
				}
			}
		}
	}
}

void GridNode::GoAntiClockWiseWest() {
	GridNode* Current = this;
	GridNode* Target = this->West;
	if (this->North != NULL) {
		Current = Current->North;
		if (Current->West != NULL) {
			// this means we need to add a node to North of the target
			Current = Current->West;
			Current->South = Target;
			Target->North = Current;
			// Now we progress further to West to check for the west of target
			if (Current->West != NULL) {
				Current = Current->West;
				if (Current->South != NULL) {
					// This means there is a node West of the target
					Current = Current->South;
					Current->East = Target;
					Target->West = Current;
					// Finally We check for the South
					if (Current->South != NULL) {
						Current = Current->South;
						if (Current->East != NULL) {
							// This means we have a node South of target
							Current = Current->East;
							Current->North = Target;
							Target->South = Current;
						}
					}
				}
			}
		}
	}
}

void GridNode::GoClockWiseSouth() {
	GridNode* Current = this;
	GridNode* Target = this->South;
	if (this->East != NULL) {
		Current = Current->East;
		if (Current->South != NULL) {
			// this means we need to add a node to East of the target
			Current = Current->South;
			Current->West = Target;
			Target->East = Current;
			// Now we progress further to South to check for the Southof target
			if (Current->South != NULL) {
				Current = Current->South;
				if (Current->West != NULL) {
					// This means there is a node South of the target
					Current = Current->West;
					Current->North = Target;
					Target->South = Current;
					// Finally We check for the West
					if (Current->West != NULL) {
						Current = Current->West;
						if (Current->North != NULL) {
							// This means we have a node West of target
							Current = Current->North;
							Current->East = Target;
							Target->West = Current;
						}
					}
				}
			}
		}
	}
}

void GridNode::GoAntiClockWiseSouth() {
	GridNode* Current = this;
	GridNode* Target = this->South;
	if (this->West != NULL) {
		Current = Current->West;
		if (Current->South != NULL) {
			// this means we need to add a node to West of the target
			Current = Current->South;
			Current->East = Target;
			Target->West = Current;
			// Now we progress further to South to check for the Southof target
			if (Current->South != NULL) {
				Current = Current->South;
				if (Current->East != NULL) {
					// This means there is a node South of the target
					Current = Current->East;
					Current->North = Target;
					Target->South = Current;
					// Finally We check for the East
					if (Current->East != NULL) {
						Current = Current->East;
						if (Current->North != NULL) {
							// This means we have a node West of target
							Current = Current->North;
							Current->West = Target;
							Target->East = Current;
						}
					}
				}
			}
		}
	}
}

void GridNode::printCenter() {
	std::cout << " The coordinate is (" << Center.first 
		<< "\t" << Center.second << ")" << std::endl;

}

