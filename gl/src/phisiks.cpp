#include<ctime>
#include <cmath>
#include "../headers/cfizika.h"
#include "../glut/glut.h"

const double PI = 3.1415916;
#define n 0.5
#define p 1.2041

Fizika::Fizika()
{
	_g = 9.8;
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

void Fizika::MoveObject(Camera* obj, double t_sec)
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

	World wor = World();

	wor.Test(obj,0.2);

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


//double Fizika :: Forse ()
//{
//		double f = 0;
//		F[0][1] =  - g * m; // сила т€жести
//
//		for( int i=0;i<3;i++)
//		{
//			F[1][i] = -0.2 * v[i];  // сила трени€
//
//
//			f = F[3][i];
//			
//			F[3][i] = F[0][i] + F[1][i] + F[2][i]; // равнодействующ€€ всех сил, сила F[2][i] задаЄтс€ в keyboard
//			if(!Wor.Test(tmp[0],i))
//				F[3][i] = 0;
//			if(f != F[3][i])
//				t1 = GetTickCount();
//		}
//	return 0;
//}

//Fizika::Fizika()
//{
//	_g = 9.8;
//}
	/*Wor.New_Cub(0,100,-1,30,0,100);
	for(int i=0;i<3;i++)
	{
		for(int e=0;e<4;e++)
		{
			F [e][i] = 0;
		}
		a[i] = 0;
		v[i] = 0;
		s[i] = 0;
		tmp[i] = 0;
	}
	m = 1;
	t1 = GetTickCount();
	t2 = 0;*/
//}


//double Fizika ::Pozition(char st)
//{
//	Forse();
//	t2 = GetTickCount();
//	switch(st)
//	{
//		case 'X' :
//			a[0] = F[3][0] / m;
//			v[0] = v[0] + a[0] * (t2 - t1) / 1000;
//			s[0] = ( v[0] * (t2 - t1) + a[0] * (t2 - t1) *(t2 - t1)/1000000 /2 );
//			
//			return s[0];
//		case 'Y' :
//			a[1] = F[3][1] / m;
//			v[1] = v[1] + a[1] * (t2 - t1);
//			s[1] = ( v[1] * (t2 - t1) + a[1] * (t2 - t1) *(t2 - t1)/1000000 /2 ); 
//			//t1 = GetTickCount();
//			return s[1];
//		case 'Z' :
//			a[2] = F[3][2] / m;
//			v[2] = v[2] + a[2] * (t2 - t1);
//			s[2] = ( v[2] * (t2 - t1) + a[2] * (t2 - t1) *(t2 - t1)/1000000 /2 ) ; 
//			//t1 = GetTickCount();
//			return s[2];
//
//		default : return 0;
//	}
//}


