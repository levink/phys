
#include "headers\Objects.h"

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
		B = 1;
	if(nor.GetY() * C + nor.GetZ() * B == 0)
		C+=1;
	double _z = - (nor.GetX() + nor.GetY() * (A + D)) / (nor.GetY() * C + nor.GetZ() * B);
	double _y = (A + _z * C + D) / B; 
	double _x = 1;
	Vector normal = Vector(_x,_y,_z);

	if(normal.length() != 0)
		ve_ro = normal * ( velo ^ normal ) / normal.length();
}

void Sphere::Test(Sphere * obj, bool motion)
{
	double const res = 0.8;
	double const K = 10;
	double len = (Position - obj->Position).length();
	if( len < (rad + obj->rad) * 1.01 || motion)
	{
		double x = obj->Position.GetX() - Position.GetX();
		double y = obj->Position.GetY() - Position.GetY();
		double z = obj->Position.GetZ() - Position.GetZ();

		double eq[3]  = {x,y,z};
		Vector norm = (eq);
		double e[3] = {0,0,0};

		Plane * plan  = new Plane(eq);
	
		Vector v = velo - obj->velo;
		Vector B = velo * m + obj->velo * obj->m;
		if( v.GetX() < 0)
		{
			v.SetX( - v.GetX());
		}
		if( v.GetY() < 0)
		{
			v.SetY( - v.GetY());
		}
		if( v.GetZ() < 0)
		{
			v.SetZ( -v.GetZ());
		}
		Vector ve2 = Vector();
		Vector ve1 = Vector();
		Vector D = v * 2 * m * obj->m;

		if( D.length2() == 0)
		{
			ve2 = ( B ) / (m + obj->m);
		}
		else
		{
			ve2 = ( B + (velo - obj->velo) * m ) / (m + obj->m);
			ve1 = (velo * m + (obj->velo - ve2) * obj->m) / m;

			if(B != ve1 * m + ve2 * obj->m)
			{
				ve2 = ( B - (velo - obj->velo) * m ) / (m + obj->m);
				ve1 = (velo * m + (obj->velo - ve2) * obj->m) / m;
			}
		}

		if(ve1 < 1)
			ve1 = e;
		if(ve2 < 1)
			ve2 = e;
		velo = ve1;
		obj->velo = ve2;

		if((velo ^ norm) > 0)
			velo = plan->GetMat() * velo * res;
		else
			velo = velo * res;
		if( (obj->velo ^ norm) < 0)
			obj->velo = plan->GetMat() * obj->velo * res;
		else
			obj->velo = obj->velo * res;

		len = (rad + obj->rad) - len; 
		F = plan->GetN() * m * _g * pow(len * K,3)/** velo.length() *sqrt(K * m)*/;
		obj->F = plan->GetN() * obj->m * obj->_g * len * K/** obj->velo.length() *sqrt(K * obj->m)*/;

		Rotated(ve1,eq);
		obj->Rotated(ve2,eq);

		delete plan;
	}
	obj->F = Vector();
	F = Vector();
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

//Line::

Line::Line()
{
	k = 0;
	e = 0;
}
Line::Line(Vector a, Vector b)
{
	k = (b.GetX() - a.GetX()) / (b.GetY() - a.GetY());
	e = a.GetX() - a.GetY() * k;
}
bool Line::Up_Down(Vector point)
{
	if(point.GetX() > point.GetY() * k + e)
		return 1;
	else
		return 0;
}

//Margin::

Margin::Margin()
{
	plan = Plane();
	tmp = NULL;
	number = 0;
	line[0] = NULL;
	line[1] = NULL;
}
Margin::Margin(Vector point1,Vector point2,Vector point3)
{
	Vector * copy;
		copy = new Vector[number];
		for(int i=0;i<number;i++)
		{
			copy[i] = tmp[i];
		}
		delete tmp;
		tmp = new Vector [number+3];
		for(int i=0;i<number;i++)
		{
			tmp[i] = copy[i];
		}
			number++;
			tmp[number] = point1;
			number++;
			tmp[number] = point2;
			number++;
			tmp[number] = point3;
		delete copy;
	plan = Plane(point1,point2,point3);
}
bool Margin::Test(Vector point )
{
	if(plan.GetA() * point.GetX() + plan.GetB() * point.GetX() + plan.GetC() * point.GetZ() + plan.GetD() ==0)
		return 1;
	else 
		return 0;
}
bool Margin::SetTmp(Vector point)
{
	if(Test(point) ==1)
	{
		Vector * copy;
		copy = new Vector[number];
		for(int i=0;i<number;i++)
		{
			copy[i] = tmp[i];
		}
		delete tmp;
		tmp = new Vector [number++];
		for(int i=0;i<number;i++)
		{
			tmp[i] = copy[i];
		}
		number++;
		tmp[number] = point;
		delete copy;
		return 1;
	}
	else 
		return 0;

}
void Margin::MakeLine()
{
	Line l;
	bool t;
	line[0] = new int [number];
	line[1] = new int [number];
	int l_t = 0;
	Vector * c_tmp;
	c_tmp = new Vector [number];
	for(int i=0;i<number;i++)
	{
		c_tmp[i] = plan.GetMat() * tmp[i]; 
	}
	for(int i=0;i<number;i++)
	{
		for(int e=0;e<number;e++)
		{
			if(i != e)
			{	
				l = Line(tmp[i],tmp[e]);
				for(int a =0;a<number;a++)
				{
					bool test;
					bool first = 1;
					if(a != e && a!= i)
					{
						if(first)
						{
							test = l.Up_Down(tmp[a]);\
							first = 0;
						}
						if(l.Up_Down(tmp[a]) != test)
						{
							t = 0;
							return;
						}
					}
				}
				if(t != 0)
				{
					line[0][l_t] = i;
					line[0][l_t] = i;
					l_t++;
				}
			}
		}
	}
}

//Polyg::

Polyg::Polyg()
{
	mar = NULL;
	nu_m = 0;
	tmp = NULL;
	nu_t = 0;
	_g = 9.8;
}
void Polyg::SetTmp(Vector p1)
{
	Vector * copy;
	copy = new Vector [nu_t];
	for(int i=0;i<nu_t ;i++)
	{
		copy[i] = tmp[i];
	}
	delete tmp;
	tmp = new Vector[nu_t++];
	for(int i=0;i<nu_t;i++)
	{
		tmp[i] = copy[i];
	}
	nu_t ++;
	tmp[nu_t ] = p1;
	delete copy;
}
void Polyg::SetMargin(Vector p1,Vector p2,Vector p3)
{
	Margin * copy;
	copy = new Margin [nu_m];
	for(int i=0;i<nu_m ;i++)
	{
		copy[i] = mar[i];
	}
	delete mar;
	mar = new Margin[nu_m++];
	for(int i=0;i<nu_m;i++)
	{
		mar[i] = copy[i];
	}
	nu_m ++;
	mar[nu_m ] = Margin(p1,p2,p3);
	delete copy;
}
int Polyg::GetN_t()
{
	return nu_t;
}
double Polyg::Get_tmpX(int i)
{
	if(i<=nu_t)
		return tmp[i].GetX();
	else
		return 0;
}
double Polyg::Get_tmpY(int i)
{
	if(i<=nu_t)
		return tmp[i].GetY();
	else
		return 0;
}
double Polyg::Get_tmpZ(int i)
{
	if(i<=nu_t)
		return tmp[i].GetZ();
	else
		return 0;
}
void Polyg::Rotated(Vector ve1, Vector nor)//начальны йвектор скорости и вектор, к которому строитс€ перпендикул€р
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
		B = 1;
	if(nor.GetY() * C + nor.GetZ() * B == 0)
		C+=1;
	double _z = - (nor.GetX() + nor.GetY() * (A + D)) / (nor.GetY() * C + nor.GetZ() * B);
	double _y = (A + _z * C + D) / B; 
	double _x = 1;
	Vector normal = Vector(_x,_y,_z);

	if(normal.length() != 0)
		ve_ro = normal * ( velo ^ normal ) / normal.length();
}
void Polyg::Test(Polyg * obj, bool motion)
{

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

