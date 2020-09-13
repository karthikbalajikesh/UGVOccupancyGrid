#include "OccupancyGrid.h"


OccupancyGrid::OccupancyGrid(Localization* SE):
	StateEstimator(SE), TempGrid(PolarGrid(StateEstimator)),
	VehicleLocation(Point()),BottomLeftLocation(Point()){
	// Construct the first node
	Head =  GridNode();
	Location = &Head; // Assume location as 0,0
	// Create the cartesian grid and polygon
	VehicleGrid = CartesianGrid(&TempGrid);
	// Initialize the vector of grid nodes for planning
	GridNodeList.push_back(&Head);
	constructPrimaryGrid();
	// Set the initial circle of 0.15m as free
	setPriors();
}



/*
The main Update Function which takes place at every time step
*/
void OccupancyGrid::Update(vector<pair<float,float>> Measurements) {
	/*
	Update takes the LIDAR measurements and creates a temp grid 
	and updates the map based on the occupancy

	Input:  vector<float,float> Lidar Measurements
	Output: NULL
	Purpose: Update the Occupancy Grid based on Lidar Readings
	*/
	// Step 1 - reset the temp grid and update occupancy in temp grid
	UpdateTempGrid(Measurements);
	// Step 2 - Update the location of the vehicle in the grid and 
	// bottomleft point.
	UpdateLocation();
	//  Step 3 - Update the Grid based on the cartesian Node vector. 
	// It is beneficial to create a pool of threads to accomplish this task.
	UpdateGrid();

}

void OccupancyGrid::UpdateLocation() {
	/*
	Function searches for the current pose of the vehicle and updates
	the gridNode location and index in point VehicleLocation and 
	GridNode* Location */
	pair<float, float> currentLocation = StateEstimator->getVehicleCoordinates();
	VehicleLocation = BinarySearch(currentLocation);
	Location = VehicleLocation.Location;
	// Also update the Bottom Left Coordinate
	currentLocation.first = currentLocation.first - 3.0;
	currentLocation.second = currentLocation.second + 3.0;
	BottomLeftLocation = BinarySearch(currentLocation);

}

void OccupancyGrid::UpdateTempGrid(vector<pair<float, float>>& Measurements) {
	TempGrid.Reset();
	TempGrid.updatePolarOccupancy(Measurements);
}

Point OccupancyGrid::BinarySearch(pair<float, float> coordinate) {
	Point result;
	/*
	Function that performs the binary search in the occupancy grid
	for a 2D coordinate given as input. */

	/*Inputs are (x,y) in meters. Step one is to convert them to long 
	long in mm.*/
	auto coordinateMilliMeter = convertCoordinate(coordinate);
	

	/*Step two is to search for the coordinate in x axis first and then
	y axis, about the previous location. if coordinate is not present, 
	expand grid. Add pointer of GridNode in Point object.*/

	result.Location = findGridNode(coordinateMilliMeter);

	/*Step 3 is to search within the grid node to obtain the index of 
	node and update it in the point object and return.*/

	pair<int, int> indices = result.Location->BinarySearch
	(coordinateMilliMeter.first, coordinateMilliMeter.second);

	/*Return Pointer
	*/
	result.indexX = indices.first;
	result.indexY = indices.second;

	return result;
}

//////////////
pair<long long, long long> OccupancyGrid::convertCoordinate(pair<float, float> Coordinate) {
	/*
	Function converts coordinates in meters in floating point
	to long long integers in mm.
	*/

	pair<long long, long long> result = { 0,0 };
	Coordinate.first = round(Coordinate.first * 1000);
	Coordinate.second = round(Coordinate.second * 1000);
	result = std::make_pair((long long)Coordinate.first,
		(long long)Coordinate.second);

	return result;

}

GridNode* OccupancyGrid::findGridNode(pair<long long, long long> Coordinate) {
	/*
	Function returns the pointer of GridNode object that holds the 
	coordinate given as input.
	*/
	GridNode* position = Location;
	long long x = Coordinate.first, y = Coordinate.second;
	while (!position->inGrid(x,y)) {
		// Implies current gridNode does not hold coordinate
		// step 1 - Check if x coordinate is found
		if (x < position->TopLeft.first && x >= position->BottomLeft.first) {
			// This implies the x coordinate is found
			// Now check for y coordinate
			if (y > position->TopLeft.second) {
				// this implies move west if left node exists
				if (position->West != NULL) {
					position = position->West;
				}
				else {
					// Expand the Node
					position->Expand(GridNodeList);
					position = position->West;
				}
			}
			else {
				// Move East 
				if (position->East != NULL) {
					position = position->East;
				}
				else {
					// Expand the Node
					position->Expand(GridNodeList);
					position = position->East;
				}
			}
		}
		else {
			// this implies we need to go north or south
			if (x >= position->TopLeft.first) {
				// this implies move north if top node exists
				if (position->North != NULL) {
					position = position->North;
				}
				else {
					// Expand the Node
					position->Expand(GridNodeList);
					position = position->North;
				}
			}
			else {
				// Move South 
				if (position->South != NULL) {
					position = position->South;
				}
				else {
					// Expand the Node
					position->Expand(GridNodeList);
					position = position->South;
				}
			}

		}
	}



	return position;
}

void OccupancyGrid::constructPrimaryGrid() {
	/* 
	Function Creates a Radius 20m grid around the vehicle origin at
	startup to reduce the number of expansions in binary search
	*/

	constructFirstQuadrant();
	constructSecondQuadrant();
	constructThirdQuadrant();
	constructFourthQuadrant();
	
}

///////////// Primary Grid Construction Functions//////////
void OccupancyGrid::constructFirstQuadrant() {
	/* Function has to construct the grid between (0,0)
	and (20m,20m)	
	*/
	
	for (int i = 0; i < 11;i++) {
		for (int j = 0; j < 11;j++) {
			Point result = BinarySearch(std::make_pair(2*i,2*j));
		}
	}
}

void OccupancyGrid::constructSecondQuadrant() {
	/* Function has to construct the grid between (0,0)
	and (-20m,20m)
	*/

	for (int i = 0; i < 11;i++) {
		for (int j = 0; j < 11;j++) {
			Point result = BinarySearch(std::make_pair(-2 * i, 2 * j));
		}
	}
}

void OccupancyGrid::constructThirdQuadrant() {
	/* Function has to construct the grid between (0,0)
	and (-20m,-20m)
	*/

	for (int i = 0; i < 11;i++) {
		for (int j = 0; j < 11;j++) {
			Point result = BinarySearch(std::make_pair(-2 * i, -2 * j));
		}
	}
}

void OccupancyGrid::constructFourthQuadrant() {
	/* Function has to construct the grid between (0,0)
	and (20m,-20m)
	*/

	for (int i = 0; i < 11;i++) {
		for (int j = 0; j < 11;j++) {
			Point result = BinarySearch(std::make_pair(2 * i, -2 * j));
		}
	}
}


///////// Grid Update Functions ///////////////////
void OccupancyGrid::UpdateGrid() {
	/*
	Function that upgrades the grid without any thread
	*/
	vector<pair<int, int>>* inRange = &VehicleGrid.InRange;
	float logOddsMeasurement = 0;
	Point UpdateNode;
	for (int i = 0;i < inRange->size();i++) {
		// step 1 transform index based on change in coordinate
		UpdateNode = findMapNode(inRange->at(i));
		// step 2 Access the PolarNode* object of Cartesian Node
		// and get the inverse sensor model log odds. 
		logOddsMeasurement = inverseSensorModel(inRange->at(i));

		// step 3 Use the occupancy to update the log odds of the location
		updateLogOdds(UpdateNode, logOddsMeasurement);
	}
}

Point OccupancyGrid::findMapNode(pair<int, int> cell) {
	/*
	The function returns a Point object that corresponds to 
	the index in the occupancy grid that contains the cartesian grid
	node. 
	*/
	Point result;
	result.Location = BottomLeftLocation.Location;
	result.indexX = (cell.first + BottomLeftLocation.indexX) %
		result.Location->SizeX;
	result.indexY = (cell.second + BottomLeftLocation.indexY) %
		result.Location->SizeY;
	int quotientX = (cell.first + BottomLeftLocation.indexX) /
		result.Location->SizeX;
	int quotientY = (cell.second + BottomLeftLocation.indexY) /
		result.Location->SizeY;
	// shift Vertically
	for (int i = 0;i < quotientX;i++) {
		if (result.Location->North != NULL) {
			result.Location = result.Location->North;
		}
		else {
			result.Location->Expand(this->GridNodeList);
			result.Location = result.Location->North;
		}
	}
	// shift horizontally
	for (int i = 0;i < quotientY;i++) {
		if (result.Location->East != NULL) {
			result.Location = result.Location->East;
		}
		else {
			result.Location->Expand(this->GridNodeList);
			result.Location = result.Location->East;
		}
	}

	return result;

}


float OccupancyGrid::inverseSensorModel(pair<int, int> CartesianIndex) {
	/*
	Function performs the inverse sensor model function for a cell. 
	The input is the index in the cartesian grid. This is used to get the
	appropriate cell in the polar grid and based on its occupancy, a log 
	odds value is returned. Care must be taken to update the unknown as 
	rounded value of 1.00000.
	*/
	float logodds = 0.0;
	// First access the cartesian node using index
	CartesianNode* cartNode = &VehicleGrid.Map
		[CartesianIndex.first][CartesianIndex.second];
	int occupancy = cartNode->polar->occupancy;
	// Based on occupancy set the value. 
	/* 
	This is a simple inverse sensor model and the probability and odds does 
	not depend on the range. 
	*/
	if (occupancy == 1) {
		// unknown
		logodds = log(1.0);
		logodds = round(logodds);
		return logodds;
	}
	if (occupancy == 0) {
		// free cell
		logodds = log(0.05 / 0.95);
		return logodds;
	}
	if (occupancy == 2) {
		// occupiedcell 
		logodds = log(0.9 / 0.1);
		
	}
	return logodds;

}

void OccupancyGrid::updateLogOdds(Point& node, float LogOdds) {
	/*
	Function updates the log odds based on the recursive log odds 
	calculated from the inverse sensor model.
	*/
	node.Location->Map[node.indexX][node.indexY].UpdateLogOdds(LogOdds);
}

void OccupancyGrid::setPriors() {
	/*
	Function updates the initial 150mm*150mm as free
	*/
	vector<pair<float, float>> minicircle = constructMiniCircle();
	// Perform Binary search and update occupancy
	Point temp;
	for (int i = 0;i < minicircle.size();i++) {
		temp = BinarySearch(minicircle[i]);
		// update the occupancy
		updateLogOdds(temp, -1.5);
	}

}

vector<pair<float,float>> OccupancyGrid::constructMiniCircle() {
	/* Function generates the initial 150 mm circle. 
	The coordinates must be floating point numbers in Meters 
	*/
	vector<pair<float, float>> miniCircle(0);
	for (float i = -0.15;i < 0.152;i = i + 0.01) {
		for (float j = -0.15;j < 0.152;j = j + 0.01) {
			miniCircle.push_back(std::make_pair(i, j));
		}
	}

	return miniCircle;
}



