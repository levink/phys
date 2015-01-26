#include <vector>
#include "Objects.h"

#ifndef __DYNAMIC_WORLD_H
#define __DYNAMIC_WORLD_H

class DynamicWorld
{
	vector<Sphere> obj;
public:
	DynamicWorld();
	Sphere* Get(int n){
		return &obj[n];
	}
	
	void Add(Sphere& item);
	int Count()
	{
		return obj.size();
	}

	void MoveOutSphere(Sphere * sp, double t_sec); 
	void MoveSphere(int n, double t_sec);

	vector<CollisionInfoOfSphere> inspection();
	void calculation(vector<CollisionInfoOfSphere> col,int n);
	void all_calculation(vector<CollisionInfoOfSphere> col);
};

#endif