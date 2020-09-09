#include "PolarGrid.h"

PolarGrid::PolarGrid(Localization* SE) : StateEstimator(SE){
	SizeX = 95; // starts from 150mm  - Due to Lidar Range
	SizeY = 36;
	PolarMap = vector<vector<PolarNode>>
		(SizeX, vector<PolarNode>(SizeY, PolarNode()));
	this->updatePolarCoordinates();
	
}

void PolarGrid::updatePolarCoordinates() {
	/*
	Function that updates the coordinates in the form of a continuous grid. 
	The first eligible bottom left node is (0,60) and last top left node(0,3000)
	*/
	
	for (int i = 0;i < SizeX;i++) {
		for (int j = 0;j < SizeY;j++) {
			int phi = j * PolarMap[i][j].width;
			int R = 150 + ( i * PolarMap[i][j].height);
			std::pair<int, int> Coordinate = { phi,R };
			PolarMap[i][j].updateCoordinates(Coordinate);
		}
	}
}

void PolarGrid::updatePolarOccupancy(vector<std::pair<float,float>> Measurements) {
	/*
	Function that Updates Occupancy of the PolarNodes based on the measurements. 
	Any occupied node will be given 2, free node 0 and unknown is 1;
	Hence for every obstacle mapped, all nodes beyond obstacle are updated as unknown.
	*/
	transformCoordinates(Measurements);

	for (auto x : Measurements) {
		// Function returns the index of the Node which is measured as obstacle. 
		std::pair<int, int> indices = findNodeIndex(x);
		// Update that node as occupied. 
		PolarMap[indices.first][indices.second].updateOccupancy(2);
		//this->AddObstacle(indices.first, indices.second);
		for (int i = indices.first + 1;i < SizeX; i++) {
			// Anything beyond cell as unknown
			PolarMap[i][indices.second].updateOccupancy(1);
			//this->AddUnknown(i, indices.second);
		}
	}
}

std::pair<int, int> PolarGrid::findNodeIndex(std::pair<float, float> reading) {
	/* Function to find the index position where a current node is present. 
	This will be a binary search structure
	*/
	// Reading is in the form (Phi,R)
	// However output is in the form (R_index, Phi_index)
	int readingR = (int)std::round(reading.second);
	if (readingR == 3000) {
		readingR = 2999;
	}
	int readingPhi = (int)std::round(reading.first);
	if (readingPhi == 360) {
		readingPhi == 359;
	}
	int UpperPhi = this->SizeY-1;
	int LowerPhi = 0;
	int UpperR = this->SizeX-1;
	int LowerR = 0;
	int IndexPhi = (UpperPhi + LowerPhi) / 2;
	int IndexR = (UpperR + LowerR) / 2;
	PolarNode CurrentNode = PolarMap[IndexR][IndexPhi];
	while (!CurrentNode.checkCoordinate(reading)) {
		// the loop enters when current Node is not the desired node
		// 1. get the bounds of the Node
		std::vector<int> bounds = CurrentNode.getBounds();
		int upperRange = bounds[0], lowerRange = bounds[1];
		int upperAngle = bounds[2], lowerAngle = bounds[3];
		
		// 1. Check for the lower bound of the current node vs desired point
		if (lowerRange<=readingR) {
			LowerR = IndexR;
		}
		if (upperRange <= readingR) {
			LowerR = IndexR + 1;
		}
		if (lowerAngle <= readingPhi) {
			LowerPhi = IndexPhi;
		}
		if (upperAngle <= readingPhi) {
			LowerPhi = IndexPhi + 1;
		}

		// 2. Check for the upper bound of the currentnode vs desired point
		if (upperRange > readingR) {
			UpperR = IndexR;
		}
		if (lowerRange > readingR) {
			UpperR = IndexR - 1;
		}
		if (upperAngle > readingPhi) {
			UpperPhi = IndexPhi;
		}
		if (lowerAngle > readingPhi) {
			UpperPhi = IndexPhi - 1;
		}

		// Update the Node
		IndexPhi = (UpperPhi + LowerPhi) / 2;
		IndexR = (UpperR + LowerR) / 2;
		CurrentNode = PolarMap[IndexR][IndexPhi];

	}

	return std::make_pair(IndexR, IndexPhi);
	
}

std::pair<int, int> PolarGrid::findNodeIndex(double angle, double range) {
	/* Function to find the index position where a current node is present.
	This will be a binary search structure
	*/
	// Input is in the form of double values angle and range
	// However output is in the form (R_index, Phi_index)
	int readingR = (int)std::round(range);
	if (readingR == 3000) {
		readingR = 2999;
	}
	int readingPhi = (int)std::round(angle);
	if (readingPhi == 360) {
		readingPhi == 359;
	}
	std::pair<float, float> reading = std::make_pair((float)angle, (float)range);
	int UpperPhi = this->SizeY - 1;
	int LowerPhi = 0;
	int UpperR = this->SizeX - 1;
	int LowerR = 0;
	int IndexPhi = (UpperPhi + LowerPhi) / 2;
	int IndexR = (UpperR + LowerR) / 2;
	PolarNode CurrentNode = PolarMap[IndexR][IndexPhi];
	while (!CurrentNode.checkCoordinate(reading)) {
		// the loop enters when current Node is not the desired node
		// 1. get the bounds of the Node
		std::vector<int> bounds = CurrentNode.getBounds();
		int upperRange = bounds[0], lowerRange = bounds[1];
		int upperAngle = bounds[2], lowerAngle = bounds[3];

		// 1. Check for the lower bound of the current node vs desired point
		if (lowerRange <= readingR) {
			LowerR = IndexR;
		}
		if (upperRange <= readingR) {
			LowerR = IndexR + 1;
		}
		if (lowerAngle <= readingPhi) {
			LowerPhi = IndexPhi;
		}
		if (upperAngle <= readingPhi) {
			LowerPhi = IndexPhi + 1;
		}

		// 2. Check for the upper bound of the currentnode vs desired point
		if (upperRange > readingR) {
			UpperR = IndexR;
		}
		if (lowerRange > readingR) {
			UpperR = IndexR - 1;
		}
		if (upperAngle > readingPhi) {
			UpperPhi = IndexPhi;
		}
		if (lowerAngle > readingPhi) {
			UpperPhi = IndexPhi - 1;
		}

		// Update the Node
		IndexPhi = (UpperPhi + LowerPhi) / 2;
		IndexR = (UpperR + LowerR) / 2;
		CurrentNode = PolarMap[IndexR][IndexPhi];

	}

	return std::make_pair(IndexR, IndexPhi);
}

void PolarGrid::transformCoordinates(vector < pair<float, float>> &Measurements) {
	/* 
	Function accepts the measurement vector from the lidar and transforms the 
	coordinates into vehicle frame in polar coordinates. 
	Input: Measurements <Angle in degrees, range in mm>
	Output: Measurements <theta_Effective in degrees, range in mm>
	Equation : Theta_effective = Theta_pose from Localization 
									- THeta_lidar from Measurement + 360
	*/

	for (pair<float, float> coordinate : Measurements) {
		float theta_lidar = coordinate.first;
		float theta_pose = StateEstimator->getAngle();
		coordinate.first = theta_pose - theta_lidar + 360.0;
	}
}

void PolarGrid::Reset() {
	// Function resets occupancy to 0
	for (int i = 0;i < SizeX;i++) {
		for (int j = 0;j < SizeY;j++) {
			PolarMap[i][j].updateOccupancy(0);
		}
	}
	// Also reset the vector of obstacles and unknowns
	//this->Obstacles.clear();
	// this->Unknown.clear();
}

void PolarGrid::AddObstacle(int index1, int index2) {
	/* 
	Function that adds the coordinate of obstacles into the vector of obstacles based on the End points.
	The input are the indices in integer form. 
	Use GetBounds() function of PolarNode and add the 4 end points to the vector 
	*/
	std::vector<int> Bounds = this->PolarMap[index1][index2].getBounds();
	// First add bottom left coordinate in (theta,range) form.
	this->Obstacles.push_back(std::make_pair(Bounds[3], Bounds[1]));
	// Next the bottom right node
	this->Obstacles.push_back(std::make_pair(Bounds[2], Bounds[1]));
	// Next the top left
	this->Obstacles.push_back(std::make_pair(Bounds[3], Bounds[0]));
	// Finally top right
	this->Obstacles.push_back(std::make_pair(Bounds[2], Bounds[0]));


}

void PolarGrid::AddUnknown(int index1, int index2) {
	/*
	Function that adds the coordinate of obstacles into the vector of obstacles based on the End points.
	The input are the indices in integer form.
	Use GetBounds() function of PolarNode and add the top left and top right points
	*/
	std::vector<int> Bounds = this->PolarMap[index1][index2].getBounds();
	// Add the top left Node
	this->Unknown.push_back(std::make_pair(Bounds[3], Bounds[0]));
	// Add the top right Node
	this->Unknown.push_back(std::make_pair(Bounds[2], Bounds[0]));
}

PolarNode* PolarGrid::getPointer(int index1, int index2) {
	// Function returns the pointer of PolarNode specified by the index
	return &PolarMap[index1][index2];
}