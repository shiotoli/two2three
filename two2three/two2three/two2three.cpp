#include "two2three.h"
void two2three::initialize()
{
	string s = "D:\\YanXiao\\c2s\\two2three\\two2three\\config.txt";
	param.loadParam(s);
	t2.loadData("D:\\YanXiao\\c2s\\two2three\\data\\", &param);
	t3.assignData(&param);
	density.clear();
	for (int i = 0; i < param.frameNum; i++)
	{
		double *** density;
		assign(density, param.h,param.w,param.depth);
		for (int j = 0; j < param.h;j++)
		for (int k = 0; k < param.w;k++)
		for (int l = 0; l < param.depth; l++)
			density[j][k][l] = 0;
	}

}
void two2three::addSource(double*** field,double ***new_field)
{
	for (int i = 0; i < param.h;i++)
	for (int j = 0; j < param.w;j++)
	for (int k = 0; k < param.depth; k++)
	{
		double dis = SQR(i - param.sourcePosx) + SQR(j - param.sourcePosy) + SQR(k - param.sourcePosz);
		double dis = (param.radius - sqrt(dis))*0.5;
		if (dis>1)
			dis = 1;
		if (dis < 0)
			dis = 0;
		new_field[i][j][k] = field[i][j][k] + (1.0 - field[i][j][k])*dis;
	}
}
void two2three::rotation_velocity(double** u2, double** v2, double *** u3,double *** v3,double*** w3)
{
	int mid = param.w / 2;
	for (int i = 0; i < param.h;i++)
	for (int j = 0; j < param.w;j++)
	for (int k = 0; k < param.depth; k++)
	{
		int oldh = i;
		double oldw1 = sqrt(SQR(j - mid) + SQR(k - mid)) + mid;
		double oldw2 = -sqrt(SQR(j - mid) + SQR(k - mid)) + mid;
		if (oldw1>param.w)
			oldw1 = param.w;
		if (oldw2>param.w)
			oldw2 = param.w;
		double g1 = oldw1 - int(oldw1);
		double g2 = oldw2 - int(oldw2);
		int oldw1i = int(oldw1);
		int oldw2i = int(oldw2);
		double vold1 = (1 - g1)*v2[oldh][oldw1i];
		double uold1 = (1 - g1)*u2[oldh][oldw1i];
		double vold2 = (1 - g2)*v2[oldh][oldw2i];
		double uold2 = (1 - g2)*u2[oldh][oldw2i];
		if (abs(g1) > 1e-8)
		{
			vold1 += g1*v2[oldh][oldw1i + 1];
			uold1 += g1*u2[oldh][oldw1i + 1];
		}
		if (abs(g2) > 1e-8)
		{
			vold2 += g2*v2[oldh][oldw2i + 1];
			uold2 += g2*u2[oldh][oldw2i + 1];
		}
		if (oldw1 > w || oldw2 > w || oldw1 < 1 || oldw2 < 1)
		{
			u3[i][j][k] = v3[i][j][k] = w3[i][j][k] = 0;
			continue;
		}
		double theta = 0,gamma = 0;
		if (SQR(k - mid) + SQR(j - mid) == 0)
			theta = 0;
		else theta = acos((j - mid) / sqrt(SQR(j - mid) + SQR(k - mid)));
		if (SQR(k - mid) + SQR(j - mid) == 0)
			gamma = 0;
		else gamma = asin((k - mid) / sqrt(SQR(j - mid) + SQR(k - mid)));
		double interp = 1 - theta / PI;
		v3[i][j][k] = vold1*interp + vold2*(1 - interp);
		double planeu = uold1*interp - uold2*(1 - interp);
		u3[i][j][k] = planeu*cos(theta);
		w3[i][j][k] = planeu*sin(gamma);
	}
}