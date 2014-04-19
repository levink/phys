#include <cmath>
#include "Objects.h"

#ifndef __WORLD_H
#define __WORLD_H

class World
{
private:
	Plane * Plan;
	double * rese[6]; // 0 - Max_x, 1 - Min_x, 2 - Max_y, 3 - Min_y, 4 - Max_z, 5 - Min_z
	int k;
public: 
	
	World();
	
	World(double A, double B, double C, double D, double reserve[6]);

	friend Plane*  GetPlane(World obj);

	int GetK()
	{
		return k;
	}

	bool TestEqua(Camera * obj,int i);
	void Test(Camera * obj,double resil);
	bool TestEqua(Sphere * obj,int i);
	void Test(Sphere * obj,double resil);
	bool TestEqua(Polyg * obj, int i);
	void Test(Polyg * obj,double resil);

	double GetYatXZ(double X, double Z, int i);
};
#endif