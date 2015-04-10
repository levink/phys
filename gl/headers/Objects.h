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
	double k; // коэффициент упругости объекта
	double u; // коэффициент трения
	Vector velo;
	Vector accel;
	Vector F;
	Vector w;
	Vector e;
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

	double Rotated(Vector point, Vector fors,double m,double k2);

	bool Test(Sphere * obj);
	void HandlerCollision(Sphere * obj, double tim);
	double GetRad();
	void SetRad(double r);
	
	void operator=(Sphere * count);
	bool inspections(Plane pl);
	void calculation(Plane  pl,double resil, double t);
	bool inspections(Line li);
	void calculation(Line  li, double resil, double t);
	bool inspections(Vector tmp);
	void calculation(Vector  tmp, double resil, double t); 
};

class Quadrocopter: public Sphere
{
private:
	const double rate;//коэффициент 
public:
	Sphere eng[4];
	Vector Fors[4];
	Vector I;
	Vector a_tang;
	Vector X;
	Vector Y;
	Vector Z; 
	Quadrocopter();
	Quadrocopter(Vector pos);

	void operator=(Quadrocopter& count);
	void SetForse(double e1, double e2, double e3, double e4);
	void Rotated(double t_sec);
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
};

class ContainerObjects
{
private:
	vector <Sphere> obj;
	vector <Quadrocopter> quad;
public:
	ContainerObjects();
	
	void MoveSphere(int n, double t_sec);
	void MoveQuadrocopter(int n,double t_sec);
	
	void Add(Sphere item) { obj.push_back(item); }
	void Add(Quadrocopter item)  { quad.push_back(item); }
	void Delete_sp(int n) { obj.erase(obj.begin()+n,obj.begin()+n); }
	void Delete_qa(int n) { quad.erase(quad.begin()+n,quad.begin()+n+1); }
	Sphere* Get_sp(int i){return &obj[i];}
	Quadrocopter* Get_quad(int i){return &quad[i];}
	vector<CollisionInfoOfSphere> inspection();
	void calculation(vector<CollisionInfoOfSphere> col,int n,double time);
	void all_calculation(vector<CollisionInfoOfSphere> col,double time);
	int Count_sp()
	{
		return obj.size();
	}
	int Count_quad()
	{
		return quad.size();
	}
	void Clear()
	{
		obj.clear();
		quad.clear();
	}
};

#endif