#include "Objects.h"
#include "World.h"
#include "DynamicWorld.h"

#ifndef __FIZIKA_H
#define __FIZIKA_H
class Fizika
{
double n;
double p;
private:
	double _g;
public:
	
	vector<Collision> collision;
	vector<int> test;
	
	StaticWorld& planes;
	DynamicWorld& balls;

	Fizika(StaticWorld& sw, DynamicWorld& dw);
	
	
	void MoveObject(BaseObject * obj, double t);
	void FindCollisions();
	void ParseCollision(double dt);
};

#endif