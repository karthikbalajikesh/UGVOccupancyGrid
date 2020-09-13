#include"GridNode.h"
#include"PolarGrid.h"
#include"Localization.h"
#include"CartesianGrid.h"
#include"OccupancyGrid.h"
#include"Point.h"
#include<chrono>


using std::vector;
using std::pair;
using std::cout;
using std::endl;
using std::make_pair;

using namespace std::chrono;
std::vector<std::pair<float, float>> createVector();
void testLocalization();
void testGridNode();
void testPolarGrid();
void testCartesianGrid();
void testOccupancyGrid();

void testMapping();

///////////////////////////////////////////////////////////////////////
int main() {
	
	testMapping();
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

void testOccupancyGrid() {
	Localization SE;
	
	OccupancyGrid Grid(&SE);
	
	
	auto start = high_resolution_clock::now();
	Point result = Grid.BinarySearch({ 8.3255,-7.212 });
	auto stop = high_resolution_clock::now();
	auto duration = duration_cast<microseconds>(stop - start);
	cout << duration.count()<<endl;
	std::cout << "Done\n";
}

void testMapping() {
	Localization SE;
	OccupancyGrid Grid(&SE);
	vector<pair<float, float>> measurements;
	measurements.push_back(make_pair(308.2695, 2292.7));
	measurements.push_back(make_pair(309.7261, 1846.3));
	measurements.push_back(make_pair(321.3402, 1920.9));
		
	Grid.Update(measurements);
	// pose 2
	measurements.clear();
	measurements.push_back(make_pair(316.8934, 2421.3));
	measurements.push_back(make_pair(325.3048, 2236.1));
	measurements.push_back(make_pair(331.1328, 2519.2));
	auto start = high_resolution_clock::now();
	Grid.Update(measurements);
	//Point result = Grid.BinarySearch({ 1.5,1.2 });
	auto stop = high_resolution_clock::now();
	auto duration = duration_cast<microseconds>(stop - start);
	cout << duration.count() << endl;
	cout << "DONE"<<endl;
}