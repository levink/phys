#include <cmath>
#include <vector>
#include "Objects.h"
#include "Geometry.h"


#ifndef __WORLD_H
#define __WORLD_H

struct CollisionInfo
{
	Plane pl;
	Line li;
	Vector tmp;
	Sphere *sp;
	Quadrocopter * qa;
	int nom_qa;
	bool pl_t;
	bool li_t;
	bool tmp_t;
	bool sp_t;
	bool qa_t;
};


class World
{
private:
	vector<Plane> Plan;
	const double res;
public: 
	
	World();
	
	friend Plane*  GetPlane(World obj);

	int Count(){ return Plan.size();}

	Plane* GetPl(int i)
	{
		return &Plan[i];
	}

	double GetYatXZ(double X,double Y,int nomber_plane);

	vector<CollisionInfo> inspections(ContainerObjects *con);
	void Calculation(vector<CollisionInfo> col, int n, double t_sec);
	void Calculation_pl(vector<CollisionInfo> col, double t_sec);
	void Calculation(vector<CollisionInfo> col, double t_sec);

	void Add(Plane pl) { Plan.push_back(pl); }
	void Clear()
	{
		Plan.clear();
	}
	
};
#endif