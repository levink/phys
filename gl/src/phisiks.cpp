#include<iostream>
#include<ctime>
#include <cmath>
#include "../headers/cfizika.h"
#include "../glut/glut.h"

const double PI = 3.1415916;
#define n 0.5
#define p 1.2041
//DWORD t100 = 0;

Fizika::Fizika()
{
	_g = 9.8;
	World wor = World();
}


//void Fizika ::Kick (double plane[4],Camera * obj,double k)
//{
//	if(obj ->Position.GetX()*plane[0] + obj ->Position.GetY()*plane[1] + obj ->Position.GetZ()*plane[2] +plane[3] <= 0)
//	{
//		obj -> velo.SetY( obj -> velo.GetY() * -k);
//		if(obj ->velo.GetY() < 10 && obj ->Position.GetX()*plane[0] + obj ->Position.GetY()*plane[1] + obj ->Position.GetZ()*plane[2] +plane[3] <= 0)
//		{
//			obj -> F.SetY(-obj ->m * _g);
//		}
//	}
//}

void Fizika::MoveObject(Camera * obj, double t_sec)
{
	//считаем новые координаты объекта на основе его времени жизни и наших "физических" законов

	Vector Ft = Vector(0,-obj->m * _g,0); //+ F1 + F2 + ...
	Vector Ftr =(obj->velo * obj->velo * p / 2) *  n * 3.14;
	Vector F = Ft + Ftr; /*obj ->F;*/	// + F1 + F2 + ...;
	Vector a = F / obj->m;
	Vector v = obj->velo + a*t_sec; 
	Vector x = obj->Position + obj->velo*t_sec + obj->accel*t_sec*t_sec/2; 

	obj->accel = a;
	obj->velo = v;
	obj->Position = x;

	//DWORD t = time(NULL);

	wor.Test(obj,0.8);

	//F0.SetX(obj ->F.GetX());
	//F0.SetZ(obj ->F.GetZ());
	//F0.SetY(obj ->F.GetY());

	//obj -> F.SetY( _g * obj ->m);

	//obj ->F.SetX( obj ->F.GetX() - cos(pow(obj ->velo.GetX(),2) * 0.2));
	//obj ->F.SetZ( obj ->F.GetZ() - sin(pow(obj ->velo.GetZ(),2) * 0.2));

	//if(F0 != obj ->F)
	//	obj ->bornTime = GetTickCount();
	//
	//DWORD lifetime = GetTickCount() - obj->bornTime;
	//
	//obj ->accel = obj ->F * obj ->m; // ускорение
	//obj ->velo = obj ->accel * lifetime + obj ->velo;
	//obj ->currentPosition = obj ->velo * lifetime + obj ->accel * (lifetime * lifetime) /2;
}

void Fizika::MoveObject(Sphere * obj, double t_sec)
{
	//считаем новые координаты объекта на основе его времени жизни и наших "физических" законов

	Vector Ft = Vector(0,-obj->m * _g,0); //+ F1 + F2 + ...
	Vector Ftr =(obj->velo * obj->velo * p / 2) *  n * 3.14;
	Vector F = Ft + Ftr; /*obj ->F;*/	// + F1 + F2 + ...;
	Vector a = F / obj->m;
	Vector v = obj->velo + a*t_sec; 
	Vector x = obj->Position + obj->velo*t_sec + obj->accel*t_sec*t_sec/2; 

	obj->accel = a;
	obj->velo = v;
	obj->Position = x;
	
	wor.Test(obj,0.8);
}

Camera::Camera ()
{
	Position = Vector(0,0,0);
	velo = Vector(0,0,0);
	accel = Vector(0,0,0);
	F = Vector(0,0,0);
	m =0;
	bornTime = 0;
	angle = 0;
	m = 10;
}

double Camera ::GetAngleXOZ()
{
	return angle;
}

void Camera :: SetAngleXOZ(int ang)
{
	angle += ang;
	if(angle > 360)
		angle = 0;
}




