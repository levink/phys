#include <cmath>
#include "Objects.h"
#include "Geometry.h"


#ifndef __WORLD_H
#define __WORLD_H

struct CollisionInfo
{
	Plane pl;
	Line li;
	Vector tmp;
	Sphere * sp;
	bool pl_t;
	bool li_t;
	bool tmp_t;
	int num;
};


class World
{
private:
	Plane * Plan;
	int k;
public: 
	
	World();
	World(double A, double B, double C, double D, double reserve[6]);

	friend Plane*  GetPlane(World obj);

	int GetK()
	{
		return k;
	}
	Plane GetPl(int i)
	{
		if(i<=k)
			return Plan[i];
		return Plane();
	}
	bool TestEqua(Camera * obj,int i);
	void Test(Camera * obj,double resil);
	bool TestEqua(Sphere * obj,int i);
	void Test(Sphere * obj,double resil, double t);

	CollisionInfo* inspections(ContainerObjects con);
	void Calculation(CollisionInfo * col, int n, double t_sec);
	void Calculation(CollisionInfo * col, double t_sec);

	double GetYatXZ(double X,double Y,int nomber_plane);
};
#endif