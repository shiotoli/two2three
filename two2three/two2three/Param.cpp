#include "Param.h"
void Param::loadParam(string s)
{
	FILE* fp;
	fp = fopen(s.c_str(),"r");
	fscanf(fp,"%d %d %d",&h,&w,&depth);
	fscanf(fp,"%d",&frameNum);
	sourcePosx = (h + w / 16);
	sourcePosy = (w / 2);
	sourcePosz = (depth / 2);
	radius = w / 8;
};