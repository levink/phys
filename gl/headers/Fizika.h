#include "Objects.h"
#include "World.h"
#ifndef __FIZIKA_H
#define __FIZIKA_H
class Fizika
{
double n;
double p;
private:
	double _g;
public:
	ContainerObjects* balls;
	World* wor;

	Fizika(World& w,ContainerObjects& c);

	friend World* GetWorld(Fizika* obj);
	void MoveObject(Camera * obj, double t);
	void MoveObject(Sphere * obj, double t);
};

#endif