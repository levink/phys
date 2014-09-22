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
	Vector w;
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

class Tr_Sphere: public BaseObject
{
private: 
	double rad;
	double I;
public:
	double _g;
	Tr_Sphere();

	void Rotated(Tr_Sphere * obj);

	void Test(Tr_Sphere * obj, bool motion);
	
	double GetRad();
	
	void operator=(Tr_Sphere * count);
};

class Polyg: public BaseObject
{
private: 
	double ** tmp;
	int ** plan;
	int nom_pl;
	int nom_tmp;
public:
	Polyg();
	Polyg(double * point[3]); 
	//Polyg(double point[3]);
	void Plan();
	void Rotated();
	void Drow();
	void Test();

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