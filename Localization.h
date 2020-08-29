#ifndef LOCALIZATION_H

#define LOCALIZATION_H

#include<iostream>
#include<Eigen/Dense>

using Eigen::VectorXd;

class Localization {
public:
	Localization();
	void printState();
private:
	VectorXd state;

};



#endif
