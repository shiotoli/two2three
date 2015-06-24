#include"stdafx.h"
#include "three.h"
#include "Param.h"

void three::assignData(Param* pp)
{
	for (int i = 0;i<pp->frameNum;i++)
	{
		double*** tmp;
		assign(tmp,pp->h,pp->w,pp->depth);
		u3.push_back(tmp);
	}
	for (int i = 0;i<pp->frameNum;i++)
	{
		double*** tmp;
		assign(tmp,pp->h,pp->w,pp->depth);
		v3.push_back(tmp);
	}
	for (int i = 0;i<pp->frameNum;i++)
	{
		double*** tmp;
		assign(tmp,pp->h,pp->w,pp->depth);
		w3.push_back(tmp);
	}
}