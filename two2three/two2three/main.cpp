#include "two2three.h"
#include "stdafx.h"
#include "Param.h"
int main()
{
	two2three t2t;
	t2t.initialize();
	double*** density;
	double dt = 0.125;
	assign(density, t2t.param.h, t2t.param.w, t2t.param.depth);
	t2t.density.push_back(density);
	for (int i = 0; i < 300; i++)
	{
		t2t.rotation_velocity(t2t.t2.u2[i], t2t.t2.v2[i], t2t.t3.u3[i], t2t.t3.v3[i], t2t.t3.w3[i]);
		double*** tmp, ***density;
		assign(density, t2t.param.h, t2t.param.w, t2t.param.depth);
		assign(tmp, t2t.param.h, t2t.param.w, t2t.param.depth);
		t2t.addSource(t2t.density[i], tmp);
		t2t.advect(tmp, t2t.t3.u3[i], t2t.t3.v3[i], t2t.t3.w3[i],density, dt);
		t2t.density.push_back(density);
	}
	return 0;
}