#include <iostream>
#include "Geometry.h"

using namespace std;
#ifndef __OBJECT_H
#define __OBJECT_H
class BaseObject
{
public:
	Vector Position;
	double m;
	Vector velo;
	Vector accel;
	Vector F;
	Vector ve_ro;
	Vector Angl;
	BaseObject();
};

class Sphere: public BaseObject
{
private: 
	double rad;
public:
	double _g;
	Sphere();

	void Rotated(Vector ve1, Vector nor);

	void Test(Sphere * obj, bool motion);
	
	double GetRad();
	
	void operator=(Sphere * count);
};

class Camera: public BaseObject
{
private:
	double angle;
public:
	Camera();
	double GetAngleXOZ();
	void SetAngleXOZ(int ang);
};

#endif