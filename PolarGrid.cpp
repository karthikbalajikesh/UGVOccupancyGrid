#include "PolarGrid.h"

PolarGrid::PolarGrid() :PolarMap(vector<vector<PolarNode>>
					(98, vector<PolarNode>(36,PolarNode()))){
	this->updatePolarCoordinates();
	SizeX = 98;
	SizeY = 36;
	
}

void PolarGrid::updatePolarCoordinates() {
	/*
	Function that updates the coordinates in the form of a continuous grid. 
	The first eligible bottom left node is (0,60) and last top left node(0,3000)
	*/
	
	for (int i = 0;i < 98;i++) {
		for (int j = 0;j < 36;j++) {
			int phi = j * PolarMap[i][j].width;
			int R = 60 + ( i * PolarMap[i][j].height);
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

	for (auto x : Measurements) {
		// Function returns the index of the Node which is measured as obstacle. 
		std::pair<int, int> indices = findNodeIndex(x);
		// Update that node as occupied. 
		PolarMap[indices.first][indices.second].updateOccupancy(2);
		for (int i = indices.first + 1;i < 98; i++) {
			// Anything beyond cell as unknown
			PolarMap[i][indices.second].updateOccupancy(1);
		}
	}
}

std::pair<int, int> PolarGrid::findNodeIndex(std::pair<float, float> reading) {
	/* Function to find the index position where a current node is present. 
	This will be a binary search structure
	*/
	// Reading is in the form (Phi,R)
	// However output is in the form (R_index, Phi_index)
	int readingR = (int)reading.second;
	int readingPhi = (int)reading.first;
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