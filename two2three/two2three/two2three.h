#include "two.h"
#include "three.h"
#include"Param.h"
#include "stdafx.h"
class two2three
{
public:
	three t3;
	two t2; 
	void rotation_velocity(double** u2, double** v2, double *** u3, double *** v3, double*** w3);
	Param param;
	vector<double**> density;
	void initialize();
	void addSource(double***);
};