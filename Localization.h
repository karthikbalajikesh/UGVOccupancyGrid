#ifndef LOCALIZATION_H

#define LOCALIZATION_H

#include<iostream>
#include<Eigen/Dense>

using Eigen::VectorXd;

class Localization {
public:
	float x;
	float y;
	float theta;
		
	Localization();
	void printState();
	void publicizeState();
private:
	VectorXd state;

};



#endif
