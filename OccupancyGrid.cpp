#include "OccupancyGrid.h"


OccupancyGrid::OccupancyGrid(Localization* SE):
	StateEstimator(SE), TempGrid(PolarGrid(StateEstimator)),
	VehicleLocation(Point()){
	Head =  GridNode();
	Location = &Head; // Assume location as 0,0
	
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


