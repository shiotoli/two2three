#pragma once
#include <iostream>
using namespace std;
#include <vector>
#include <string>
#define SQR(x) ((x)*(x))
#define PI 3.14159265359
inline void assign(double** &field,int h,int w)
{
	field = new double*[h];
	for (int i = 0;i<h;i++)
		field[i] = new double[w];
}
inline void release(double** &field,int h,int w)
{
	for (int i = 0;i<h;i++)
		delete [] field[i];
	delete [] field;
}

inline void assign(double*** &field,int h,int w,int depth)
{
	field = new double**[h];
	for (int i = 0;i<h;i++)
		field[i] = new double*[w];
	for (int i = 0;i<h;i++)
		for (int j = 0;j<w;j++)
			field[i][j] = new double[depth];
}
inline void release(double*** &field,int h,int w,int depth)
{
	for (int i = 0;i<h;i++)
		for (int j = 0;j<w;j++)
			delete [] field[i][j];
	for (int i = 0;i<h;i++)
		delete [] field[i];
	delete [] field;
}
