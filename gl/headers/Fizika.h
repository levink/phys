
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

Fizika::Fizika()
{
	n = 0.5;
	p = 1.2041;
	_g = 9.8;
	World wor = World();
}

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

	obj -> F.SetY( _g * obj ->m);
	obj ->F.SetX( obj ->F.GetX() - cos(pow(obj ->velo.GetX(),2) * 0.2));
	obj ->F.SetZ( obj ->F.GetZ() - sin(pow(obj ->velo.GetZ(),2) * 0.2));
}

void Fizika::MoveObject(Sphere * obj, double t_sec)
{
	//считаем новые координаты объекта на основе его времени жизни и наших "физических" законов

	Vector Ft = Vector(0,-obj->m * _g,0); //+ F1 + F2 + ...
	Vector Ftr =(obj->velo * obj->velo * p / 2) *  n * 3.14;
	Vector F = Ft + Ftr + obj ->F;	// + F1 + F2 + ...;
	Vector a = F / obj->m;
	Vector v = obj->velo + a*t_sec; 
	Vector x = obj->Position + obj->velo*t_sec + obj->accel*t_sec*t_sec/2; 

	obj->accel = a;
	obj->velo = v;
	obj->Position = x;

	wor.Test(obj,0.8);

	double l = obj->GetRad() * 2 * PI;
	obj->Angl  = ( (obj->ve_ro * t_sec) / l) * 360 + obj->Angl;
	if(obj->Angl.GetX() > 360)
		obj->Angl.SetX(0);
	if(obj->Angl.GetY() > 360)
		obj->Angl.SetY(0);
	if(obj->Angl.GetZ() > 360)
		obj->Angl.SetX(0);
}



#endif