#include"GridNode.h"
#include"PolarGrid.h"
#include"Localization.h"

std::vector<std::pair<float, float>> createVector();
void testLocalization();


///////////////////////////////////////////////////////////////////////
int main() {
	
	testLocalization();
	return 0;
}
//////////////////////////////////////////////////////////////////////

void testLocalization() {
	Localization A;
	A.printState();
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
