#include"headers\Geometry.h"
#include"headers\Objects.h"
#include"headers\World.h"
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

//bool World::TestEqua(Polyg * obj, int i)
//{
//	bool test  = 0;
//	for(int i=0;i<obj->GetN_t() && !test;i++)
//	{
//		if(obj->Get_tmpX(i) > rese[i][0] || obj->Get_tmpX(i) < rese[i][1] || obj->Get_tmpY(i) > rese[i][2] || obj->Get_tmpY(i) < rese[i][3] || obj->Get_tmpZ(i) > rese[i][4] || obj->Get_tmpZ(i) < rese[i][5])
//			if(  obj->Get_tmpX(i)* Plan[i].GetA() + obj->Get_tmpY(i)*Plan[i].GetB() + obj->Get_tmpZ(i)* Plan[i].GetC() + Plan[i].GetD()  < 0 )
//				test = 1;
//	}
//	return test;
//}

//void World::Test(Polyg * obj,double resil)
//{
//	for(int i=0;i<k;i++)
//	{
//		if(TestEqua(obj,i))
//		{
//			Vector velo = obj->velo;
//			obj->velo = Plan[i].GetMat() * obj->velo * resil;
//			obj->Rotated(velo,Plan[i].GetN());
//		}
//	}
//}