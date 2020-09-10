#include "OccupancyGrid.h"


OccupancyGrid::OccupancyGrid(Localization* SE):
	StateEstimator(SE), TempGrid(PolarGrid(StateEstimator)),
	VehicleLocation(Point()),BottomLeftLocation(Point()){
	Head =  GridNode();
	Location = &Head; // Assume location as 0,0
	VehicleGrid = CartesianGrid(&TempGrid);
	constructPrimaryGrid();
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
	// Step 2 - Update the location of the vehicle in the grid
	UpdateLocation();

}

void OccupancyGrid::UpdateLocation() {

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
					position->Expand();
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
					position->Expand();
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
					position->Expand();
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
					position->Expand();
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

	GridNode* position = &Head;
	// to be continued
}


