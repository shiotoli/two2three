#include "Param.h"
#include "two.h"
void two::loadData(string s,Param* pp)
{
	for (int i = 0;i<pp->frameNum;i++)
	{
		double** tmp;
		assign(tmp, pp->h, pp->w);
		printf("%d\n", i);
		char name[100];
		sprintf(name,"u_%d.txt",i+1);
		string s1 = s+string(name);
		FILE* fp = fopen(s1.c_str(),"r");
		for (int j = 0;j<pp->h;j++)
			for (int k = 0;k<pp->w;k++)
				fscanf(fp,"%lf",&tmp[j][k]);
			u2.push_back(tmp);
			fclose(fp);
	}
	for (int i = 0;i<pp->frameNum;i++)
	{
		double** tmp;
		if (i == 208)
		{
			tmp = nullptr;
		}
		assign(tmp,pp->h,pp->w);
		char name[100];
		printf("%d\n",i);
		sprintf(name,"v_%d.txt",i+1);
		string s1 = s+string(name);
		FILE* fp = fopen(s1.c_str(),"r");
		for (int j = 0;j<pp->h;j++)
			for (int k = 0;k<pp->w;k++)
				fscanf(fp,"%lf",&tmp[j][k]);
		v2.push_back(tmp);
		fclose(fp);
	}
	
}