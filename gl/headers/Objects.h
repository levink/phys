#include <iostream>
#include <vector>
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
	BaseObject(Vector pos);
};

class Sphere
{
private: 
	double rad;
	Vector Position;
	
public:
	double _g;
	Sphere(Vector position){
		Position = position;
		rad = 1;
		_g = 9.8;	
	}
	void Test(){
		rad = rad + 1;
	}

	Sphere& operator=(const Sphere *);
	
	void Test2(Plane  pl, double resil, double t)
	{
		pl.Test();
	}
	
	//void Rotated(Vector ve1, Vector nor);
	//void Test_Sphere(Sphere * obj, bool motion);
	//bool Test(Sphere * obj);
	//void HandlerCollision(Sphere * obj);
	//double GetRad();
	//
	

	//bool inspections(Plane pl);
	//bool inspections(Line li);
	//bool inspections(Vector tmp);

	//void calculation(Plane  pl, double resil, double t);
	//void calculation(Line  li, double resil, double t);
	//void calculation(Vector  tmp, double resil, double t); 
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

struct CollisionInfoOfSphere
{
	Sphere * sp1;
	Sphere * sp2;
	int num;
};


#endif