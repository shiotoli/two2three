#pragma once
#include "stdafx.h"
class Param
{
public:
	void loadParam(string s);
	int h,w,depth;
	int frameNum;
	int sourcePosx, sourcePosy, sourcePosz;
	double radius;
};