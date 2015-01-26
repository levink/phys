#include <cmath>
#include "Objects.h"
#include "Geometry.h"
#include "DynamicWorld.h"


#ifndef __StaticWorld_H
#define __StaticWorld_H

enum CollisionType {NONE=0, WITH_POINT, WITH_LINE, WITH_PLANE};

class Collision
{
public:
	CollisionType type;
	Sphere * sp;
	Plane* plane;
	Line* line;
	Vector *point;

	Collision()
	{
		plane = NULL;
		line = NULL; 
		point = NULL;
		sp = NULL;
		type = CollisionType::NONE;
	}
};

class StaticWorld
{
	vector<Plane> items;
public: 
	StaticWorld();
	
	Plane* Get(int num){
		return &items[num];
	}

	bool TestEqua(Camera * obj,int i);
	void Test(Camera * obj,double resil);
	bool TestEqua(Sphere * obj,int i);
	void Test(Sphere * obj,double resil, double t);

	void inspections(DynamicWorld con, vector<Collision>& result);
	void Calculation(vector<Collision>& col, int n, double t_sec);
	void Calculation(vector<Collision>& col, double t_sec);

	int Count()
	{
		return items.size();
	}

	double GetYatXZ(double X,double Y,int nomber_plane);
};


#endif