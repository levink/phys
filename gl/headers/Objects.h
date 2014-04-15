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

class Line
{
private:
	double k;
	double e;
public:
	Line();
	Line(Vector a, Vector b);
	bool Up_Down(Vector point);
};

class Margin
{
private:
	Plane plan;
	Vector * tmp;
	int number;
	int * line [2];
public:
	Margin();
	Margin(Vector point1,Vector point2,Vector point3);
	bool Test(Vector point );
	bool SetTmp(Vector point);
	void MakeLine();
};

class Polyg : public BaseObject
{
private:
	Margin * mar;
	int nu_m;
	Vector * tmp;
	int nu_t;
	double _g;
public:
	Polyg();
	void SetTmp(Vector p1);
	void SetMargin(Vector p1,Vector p2,Vector p3);
	int GetN_t();
	double Get_tmpX(int i);
	double Get_tmpY(int i);
	double Get_tmpZ(int i);
	void Rotated(Vector ve1, Vector nor);
	void Test(Polyg * obj, bool motion);
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