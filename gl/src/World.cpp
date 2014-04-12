#include <cmath>
#include "../headers/World.h"
using namespace std;

World::World(/*bool test*/)
	{
		k = 2;
		Plan = new Plane [k];
		double eq1[4]  ={-10,10,0,5};
		double eq2[4] = {0,1,0,-3};
		for(int i=0;i<6;i++)
		{
			//if(rese[i] == NULL)
				rese[i] = new double [k];
		}
		rese[0][0] = 50.0;
		rese[0][1] = -50;
		rese[0][2] = max8;
		rese[0][3] = 0;
		rese[0][4] = max8;
		rese[0][5] = min8;
		rese[1][0] = 20;
		rese[1][1] = -1;
		rese[1][2] = max8;
		rese[1][3] = -3;
		rese[1][4] = max8;
		rese[1][5] = min8;
		Plan[0] = Plane(eq1);
		Plan[1] = Plane(eq2);
	}

World::World(double A, double B, double C, double D, double reserve[6])
{
	Plane * copy;
	double ** cop;
		copy = new Plane[k];
		for(int i=0;i<k;i++)
		{
			copy[i] = Plan[i];
			cop[i] = rese[i];
		}
		delete Plan;
		delete rese;
		Plan = new Plane [k++];
		for(int i=0;i<6;i++)
		{
			rese[i] = new double[k++];
		}
		for(int i=0;i<k;i++)
		{
			Plan[i] = copy[i];
			rese[i] = cop[i];
		}
		delete copy;
		delete cop;
		k++;
		double eq [4]  ={A,B,C,D};
		Plan[k] = Plane(eq);
		for(int i=0;i<6;i++)
		{
			rese[k][i] = reserve[i];
		}
}


bool World::TestEqua(Camera * obj,int i)
{
	if(obj->Position.GetX() > rese[i][0] || obj->Position.GetX() < rese[i][1] || obj->Position.GetY() > rese[i][2] || obj->Position.GetY() < rese[i][3] || obj->Position.GetZ() > rese[i][4] || obj->Position.GetZ() < rese[i][5])
		return 0;
	else
		return ( obj->Position.GetX()*Plan[i].GetA() + obj->Position.GetY()*Plan[i].GetB() + obj->Position.GetZ()* Plan[i].GetC() + Plan[i].GetD() ) < 0; // �������� ���� ����������� �� <
}

void World::Test(Camera * obj,double resil)
{
	for(int i=0;i<k;i++)
	{
		if(TestEqua(obj,i))
		{
			obj->velo = Plan[i].GetMat() * obj->velo * resil;
		}
	}
}

bool World::TestEqua(Sphere * obj,int i)
{
	if(obj->Position.GetX() > rese[i][0] || obj->Position.GetX() < rese[i][1] || obj->Position.GetY() > rese[i][2] || obj->Position.GetY() < rese[i][3] || obj->Position.GetZ() > rese[i][4] || obj->Position.GetZ() < rese[i][5])
		return 0;
	else
	{
		double eqa = pow(obj->Position.GetX()*Plan[i].GetA() + obj->Position.GetY()*Plan[i].GetB() + obj->Position.GetZ()* Plan[i].GetC() + Plan[i].GetD(),2);
		double lon = pow(Plan[i].GetA(),2) + pow(Plan[i].GetB(),2) + pow(Plan[i].GetC(),2);
		if(lon == 0 )
			return 0;

		return ( eqa/lon/*obj->Position.GetX()*Plan[i].GetA() + obj->Position.GetY()*Plan[i].GetB() + obj->Position.GetZ()* Plan[i].GetC() + Plan[i].GetD()*/ ) < pow(obj->GetRad() * 1.1,2); 
	}
}

void World::Test(Sphere * obj,double resil)
{
	for(int i=0;i<k;i++)
	{
		if(TestEqua(obj,i))
		{
			Vector velo = obj->velo;
			obj->Rotated(velo,Plan[i].GetN());
			if(obj->velo.length2() < 1)
			{
				obj->F = Plan[i].GetN() * obj->m * obj->_g * 1.1;
			}
			else
			{
				obj->velo = Plan[i].GetMat() * obj->velo * resil;
				obj->F = Plan[i].GetN() * obj->m * obj->_g * obj->velo/*.length()*/ *sqrt(K * obj->m);
				/*obj->velo = Vector();*/
			}
		}
	}
}

bool World::TestEqua(Polyg * obj, int i)
{
	bool test  = 0;
	for(int i=0;i<obj->GetN_t() && !test;i++)
	{
		if(obj->Get_tmpX(i) > rese[i][0] || obj->Get_tmpX(i) < rese[i][1] || obj->Get_tmpY(i) > rese[i][2] || obj->Get_tmpY(i) < rese[i][3] || obj->Get_tmpZ(i) > rese[i][4] || obj->Get_tmpZ(i) < rese[i][5])
			if(  obj->Get_tmpX(i)* Plan[i].GetA() + obj->Get_tmpY(i)*Plan[i].GetB() + obj->Get_tmpZ(i)* Plan[i].GetC() + Plan[i].GetD()  < 0 )
				test = 1;
	}
	return test;
}

void World::Test(Polyg * obj,double resil)
{
	for(int i=0;i<k;i++)
	{
		if(TestEqua(obj,i))
		{
			Vector velo = obj->velo;
			obj->velo = Plan[i].GetMat() * obj->velo * resil;
			obj->Rotated(velo,Plan[i].GetN());
		}
	}
}