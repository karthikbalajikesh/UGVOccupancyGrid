#include"GridNode.h"
#include"PolarGrid.h"
#include"Localization.h"
#include"CartesianGrid.h"

std::vector<std::pair<float, float>> createVector();
void testLocalization();
void testGridNode();
void testPolarGrid();
void testCartesianGrid();

///////////////////////////////////////////////////////////////////////
int main() {
	
	testCartesianGrid();
	return 0;
}
//////////////////////////////////////////////////////////////////////

void testLocalization() {
	Localization A;
	A.printState();
}



void testGridNode() {
	long long origin = 0;
	GridNode A(origin,origin);
	//std::pair<int,int> Indices = A.BinarySearch(992,-992);
	//std::cout << "( " << Indices.first << "  ,   " << Indices.second << "  )" << std::endl;
	A.Expand();

	return;

}

std::vector<std::pair<float,float>> createVector() {
	int vectorSize = 0;
	std::cout << "Insert Length of the vector :    ";
	std::cin >> vectorSize;
	std::cout << std::endl;
	std::vector<std::pair<float, float>> result(vectorSize, { 0,0 });
	for (int i = 0;i < vectorSize;i++) {
		std::cout << "Enter Phi value :  ";
		std::cin >> result[i].first;
		std::cout << "\nEnter R value :  ";
		std::cin >> result[i].second;
	}
	return result;
}

void testPolarGrid() {
	Localization A1;
	PolarGrid A(&A1);

 	std::cout << "Done\n";
}

void testCartesianGrid() {
	Localization SE;
	PolarGrid GridPolar(&SE);
	CartesianGrid GridCartesian(&GridPolar);

	std::cout << "Done\n";
}
