#include "OccupancyGrid.h"


OccupancyGrid::OccupancyGrid(Localization* SE):
	StateEstimator(SE), TempGrid(PolarGrid(StateEstimator)),
	VehicleLocation(Point()),BottomLeftLocation(Point()){
	Head =  GridNode();
	Location = &Head; // Assume location as 0,0
	VehicleGrid = CartesianGrid(&TempGrid);
	
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

Point OccupancyGrid::BinarySearch(pair<float, float>& coordinate) {
	/*
	Function that performs the binary search in the occupancy grid
	for a 2D coordinate given as input. 

	Inputs are (x,y) in meters. Step one is to convert them to long 
	long in mm.

	Step two is to search for the point in x axis first and then
	y axis, about the previous location. if point is not present, 
	expand grid. Add pointer to GridNode in Point object.

	Step 3 is to search within the grid node to obtain the index of 
	node and update it in the point object and return.

	Return Pointer
	*/
}


