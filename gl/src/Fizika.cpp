#include "../headers\Fizika.h"
Fizika::Fizika()
{
	n = 0.1;
	p = 1.2041;
	_g = 9.8;
	wor = World();
	con_obj = ContainerObjects();
}

void Fizika::MoveObject(Camera * obj, double t_sec)
{
	//считаем новые координаты объекта на основе его времени жизни и наших "физических" законов

	Vector Ft = Vector(0,-obj->m * _g,0); //+ F1 + F2 + ...
	Vector Ftr =-(obj->velo * obj->velo * p / 2) *  n * 3.14;
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

	obj -> F.SetY( _g * obj ->m);
	obj ->F.SetX( obj ->F.GetX() - cos(pow(obj ->velo.GetX(),2) * 0.2));
	obj ->F.SetZ( obj ->F.GetZ() - sin(pow(obj ->velo.GetZ(),2) * 0.2));
}

void Fizika::MoveObject(Sphere * obj, double t_sec)
{
	//считаем новые координаты объекта на основе его времени жизни и наших "физических" законов
	const double PI = 3.1415926;

	Vector Ft = Vector(0,-obj->m * _g,0); //+ F1 + F2 + ...
	//Vector Ftr = - (obj->velo /*> obj->velo*/ * p / 2) *  n * 3.14;
	Vector F = obj->F /*+ Ftr*/;	// + F1 + F2 + ...;
	Vector a = obj->F / obj->m;
	Vector v = obj->velo + a*t_sec; 
	Vector x = obj->Position + obj->velo*t_sec + (a*t_sec*t_sec)/2; 

	obj->accel = a;
	obj->velo = v;
	obj->Position = x;
	obj->F = Ft;

	wor.Test(obj,1,t_sec); // 0.975

	double l = obj->GetRad() * 2 * PI;
	obj->Angl  = ( (obj->w * t_sec) / l) * 360 + obj->Angl;
	if(obj->Angl.GetX() > 360 || obj->Angl.GetX() < -360)
		obj->Angl.SetX(0);
	if(obj->Angl.GetY() > 360 || obj->Angl.GetY() < -360)
		obj->Angl.SetY(0);
	if(obj->Angl.GetZ() > 360 || obj->Angl.GetZ() < -360)
		obj->Angl.SetZ(0);
}