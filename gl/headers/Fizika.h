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
	World wor;
public:
	Fizika();
	//void Kick (double plane[4],Camera * obj,double k);
	friend World* GetWorld(Fizika obj);
	void MoveObject(Camera * obj, double t);
	void MoveObject(Sphere * obj, double t);
	Sphere* TestMO (Sphere * obj, double t); 
};

#endif