#include"GridNode.h"

int main() {
	GridNode A;
	A.CreateNodeEast();
	A.printCenter();
	GridNode* temp = A.GetEast();
	temp->printCenter();
	return 0;
}