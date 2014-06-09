
#include "../headers\Objects.h"

//BaseObject::

BaseObject::BaseObject()
{
	Position = Vector(0,0,0);
	velo = Vector(0,0,0);
	accel = Vector(0,0,0);
	F = Vector(0,0,0);
	Angl = Vector(0,0,0);
	m = 10;
}

//Sphere::

Sphere::Sphere()
{
	rad = 1;
	_g = 9.8;
	BaseObject();
}


void Sphere::Rotated(Vector ve1, Vector nor)//начальны йвектор скорости и вектор, к которому строитс€ перпендикул€р
{
	double A = ve1.GetY() * velo.GetZ() - velo.GetY() * ve1.GetZ();
	double B = -(ve1.GetX() * velo.GetZ() - ve1.GetZ() * velo.GetX());
	double C = ve1.GetX() * velo.GetY() - ve1.GetY() * velo.GetX();
	double D = - Position.GetX() * A + Position.GetY() * B - Position.GetZ() * C;
	/*if(C == 0)
		C = 1;
	if(ve1.GetY() == 0)
		ve1.SetY(1);
	if(ve1.GetZ() == 0)
		ve1.SetZ(1);
	if(B == (C * ve1.GetY()) / ve1.GetZ() )
		B +=1;
	double _y = -D / ( B - ( ( C * ve1.GetY() ) / ve1.GetZ() ) );
	double _z = - ( ve1.GetY() * _y ) / ve1.GetZ();

	Vector normal = Vector(0,_y,_z);*/

	if(B==0)
		B = 0.0001;
	if(nor.GetY() * C + nor.GetZ() * B == 0)
		C+=1;
	double _z = - (nor.GetX() + nor.GetY() * (A + D)) / (nor.GetY() * C + nor.GetZ() * B);
	double _y = (A + _z * C + D) / B; 
	double _x = 1;
	Vector normal = Vector(_x,_y,_z);
	normal = Vector_norm(normal);
	
	if(normal.length() != 0)
		ve_ro = normal * ( velo & normal ) / normal.length() ;
		//ve_ro = ( normal * ( velo & normal ) / velo.length() ) * 0.2 ;
}

void Sphere::Test(Sphere * obj, bool motion)
{
	double const res = 0.8;
	double const K = 10;
	double len = (obj->Position - Position).length2();
	if( len < (rad + obj->rad)* (rad + obj->rad) * 1.001 || motion)
	{
		double x = obj->Position.GetX() - Position.GetX();
		double y = obj->Position.GetY() - Position.GetY();
		double z = obj->Position.GetZ() - Position.GetZ();

		double eq[3]  = {x,y,z};
		Vector norm = Vector(eq);
		norm = Vector_norm(norm);
		double e[3] = {0,0,0};

		Plane * plan  = new Plane();
		plan->PlaneSetEquation(eq);	

		Vector ve2 = Vector();
		Vector ve1 = Vector();
		
		velo = plan->GetBathis() * velo;
		obj->velo = plan->GetBathis() * obj->velo;

		Vector D = (velo - obj->velo) * obj->m;
		Vector A = velo * m + obj->velo * obj->m;
		if(D.length2() == 0)
		{
			ve1 = (A) / (m + obj->m);
			ve2 = (A - ve1 * m) / (obj->m);
		}
		else
		{
			ve1 = (A + D) / (m + obj->m);
			ve2 = (A - ve1 * m) / (obj->m);
			Vector t_1 = velo > velo * m + obj->velo > obj->velo * obj->m;
			Vector t_2 = ve1 > ve1 * m + ve2 > ve2 * obj->m; 
			double test = t_1.length2() - t_2.length2();
			if( test > 0.0000001 || test < -0.0000001)
			{
				ve1 = (A  - D) / (m + obj->m);
				ve2 = (A - ve1 * m) / (obj->m);
			}
		}

		if(ve1 < 0.01)
			ve1 = e;
		if(ve2 < 0.01)
			ve2 = e;
		velo = ve1;
		obj->velo = ve2;

		velo = plan->GetInvertMat() * velo;
		obj->velo = plan->GetInvertMat() * obj->velo;

		//if((velo ^ norm) > 0)
		//	velo = plan->GetMat() * /*velo*/ve1 * res;
		//else
		//		velo = -/*velo*/norm * (ve1 * res).length();
		//if( (obj->velo ^ norm) < 0)
		//	obj->velo = plan->GetMat() * /*obj->velo*/ve2 * res;
		//else
		//	obj->velo = /*obj->velo*/norm * (ve2 * res).length();

		len = sqrt(len);
		len = ((rad + obj->rad) - len)/2; 
		
		 Position = Position - norm * len;
		 obj->Position = obj->Position + norm * len;

		Rotated(obj->velo,eq);
		obj->Rotated(velo,eq);

		if((norm ^ F) > 0)
		{
			F = - (norm * (obj->F & norm)) + F;
			obj->F = (norm * (F & norm) + obj->F);
		}
		else
		{
			F = (norm * (obj->F & norm)) + F;
			obj->F = -(norm * (F & norm) + obj->F);
		}
		delete plan;
	}
}

double Sphere::GetRad()
{
	return rad;
}

void Sphere::operator=(Sphere * count)
{
	Position = count->Position;
	accel = count->accel;
	F = count->F;
	m = count->m;
	velo = count->velo;
}

//Camera::

Camera::Camera()
{
	BaseObject();
}
double Camera::GetAngleXOZ()
{
	return angle;
}
void Camera::SetAngleXOZ(int ang)
{
	angle += ang;
	if(angle > 360)
		angle = 0;
}

