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
};

class Sphere: public BaseObject
{
private: 
	double rad;
public:
	double _g;
	Sphere();

	void Rotated(Vector ve1, Vector nor);

	void Test_Sphere(Sphere * obj, bool motion);
	bool Test(Sphere * obj);
	void HandlerCollision(Sphere * obj);
	double GetRad();
	
	void operator=(Sphere * count);
	bool inspections(Plane pl);
	void calculation(Plane  pl, double resil, double t);
	bool inspections(Line li);
	void calculation(Line  li, double resil, double t);
	bool inspections(Vector tmp);
	void calculation(Vector  tmp, double resil, double t); 
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

class ContainerObjects
{
private:
	//Sphere ** obj;
	vector<Sphere> obj;
	int number;
public:
	void MoveOutSphere(Sphere * sp, double t_sec); 
	void MoveSphere(int n, double t_sec);
	ContainerObjects();
	void AddSphere(Sphere * count);
	Sphere* GetSphere(int n);
	CollisionInfoOfSphere* inspection();
	void calculation(CollisionInfoOfSphere * col,int n);
	void all_calculation(CollisionInfoOfSphere * col);
	int GetNumber()
	{
		return number;
	}
};

#endif