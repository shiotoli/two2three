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

void two2three::advect(double*** field, double*** u, double*** v, double***w, double*** new_field,double dt)
{
	double*** tmp1, ***tmp2;
	assign(tmp1, param.h, param.w, param.depth);
	assign(tmp2, param.h, param.w, param.depth);
	advect_simple(field, u, v, w, tmp1, dt);
	advect_simple(tmp1, u, v, w, tmp2, -dt);
	for (int i = 0; i < param.h;i++)
	for (int j = 0; j < param.w;j++)
	for (int k = 0; k < param.depth; k++)
	{
		tmp1[i][j][k] = field[i][j][k] + (field[i][j][k] - tmp2[i][j][k]) / 2;
	}
	advect_simple(tmp1, u, v, w, new_field, dt);

	release(tmp1, param.h, param.w, param.depth);
	release(tmp2, param.h, param.w, param.depth);

}
void two2three::advect_simple(double*** field, double*** u, double*** v, double***w, double*** new_field,double dt)
{
	for (int i = 0; i < param.h; i++)
	for (int j = 0; j < param.w; j++)
	for (int k = 0; k < param.depth; k++)
		new_field[i][j][k] = field[i][j][k];
	for (int i = 1; i < param.h - 1; i++)
	for (int j = 1; j < param.w - 1; j++)
	for (int k = 1; k < param.depth - 1; k++)
	{
		double t1 = i - v[i][j][k] * dt;
		double t2 = j - u[i][j][k] * dt;
		double t3 = k - w[i][j][k] * dt;
		t1 = (t1 < 1.5) ? 1.5 : t1;
		t2 = (t2 < 1.5) ? 1.5 : t2;
		t3 = (t3 < 1.5) ? 1.5 : t3;
		t1 = (t1>param.h - 0.5) ? param.h - 0.5 : t1;
		t2 = (t2>param.w - 0.5) ? param.w - 0.5 : t2;
		t3 = (t3>param.depth - 0.5) ? param.depth - 0.5 : t3;
		int t1_1 = int(t1);
		int t2_1 = int(t2);
		int t3_1 = int(t3);
		int t1_2 = t1_1 + 1;
		int t2_2 = t2_1 + 1;
		int t3_2 = t3_1 + 1;
		double alpha_1 = t1 - t1_1;
		double alpha_2 = t2 - t2_1;
		double alpha_3 = t3 - t3_1;
		double g111 = (1 - alpha_1)*(1 - alpha_2)*(1 - alpha_3);
		double g112 = (1 - alpha_1)*(1 - alpha_2)*alpha_3;
		double g121 = (1 - alpha_1)*alpha_2*(1 - alpha_3);
		double g211 = alpha_1*(1 - alpha_2)*(1 - alpha_3);
		double g122 = (1 - alpha_1)*alpha_2*alpha_3;
		double g212 = alpha_1*(1 - alpha_2)*alpha_3;
		double g221 = alpha_1*alpha_2*(1 - alpha_3);
		double g222 = alpha_1*alpha_2*alpha_3;
		new_field[i][j][k] = g111*field[t1_1][t2_1][t3_1] + g112*field[t1_1][t2_1][t3_2] + g121*field[t1_1][t2_2][t3_1] +
			g211*field[t1_2][t2_1][t3_1] + g122*field[t1_1][t2_2][t3_2] + g221*field[t1_2][t2_2][t3_1] + g212*field[t1_2][t2_1][t3_2] +
			g222*field[t1_2][t2_2][t3_2];
	}
}
void two2three::addSource(double*** field,double ***new_field)
{
	for (int i = 0; i < param.h;i++)
	for (int j = 0; j < param.w;j++)
	for (int k = 0; k < param.depth; k++)
	{
		double dis = SQR(i - param.sourcePosx) + SQR(j - param.sourcePosy) + SQR(k - param.sourcePosz);
		dis = (param.radius - sqrt(dis))*0.5;
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
		if (oldw1 > param.w || oldw2 > param.w || oldw1 < 1 || oldw2 < 1)
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