#include <cmath>
#include<iostream>
#include "../headers/World.h"
using namespace std;

World::World(/*bool test*/)
	{
		double const max8 = 100;
		double const min8 = -100;
		k = 2;
		Plan = new Plane [k];
		double eq1[4]  ={-5,5,0,30};
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
		return ( obj->Position.GetX()*Plan[i].GetA() + obj->Position.GetY()*Plan[i].GetB() + obj->Position.GetZ()* Plan[i].GetC() + Plan[i].GetD() ) < 0; // изменить знак неравенства на <
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

		return ( eqa/lon ) < pow(obj->GetRad() * 1.1,2); 
	}
}

void World::Test(Sphere * obj,double resil, double t)
{
	double const K = 0;
	for(int i=0;i<k;i++)
	{
		if(TestEqua(obj,i))
		{
			//cout << "Velo to Plane : {" << obj->velo.GetX() << ", " << obj->velo.GetY() << ", " << obj->velo.GetZ() << "}.";
			obj->Rotated(obj->velo,Plan[i].GetN());
			//double velo = obj->velo.length();
			//obj->velo = Vector_norm(Plan[i].GetMat() * obj->velo);
			//obj->velo = obj->velo * velo * resil;
			//obj->F = obj->F + Vector_norm(Plan[i].GetN()) * obj->F.length()/** obj->velo.length()*sqrt(K * obj->m)*/;
			Vector vy = Vector_norm(Plan[i].GetN()) * (((obj->velo) & Plan[i].GetN()) /Plan[i].GetN().length());
			obj->F = - ((vy * 2 * obj->m)/(t)) ;
			
			cout << "Velo after Plane : {" << obj->velo.GetX() << ", " << obj->velo.GetY() << ", " << obj->velo.GetZ() << "}.\n\n";
			double eqa = obj->Position.GetX()*Plan[i].GetA() + obj->Position.GetY()*Plan[i].GetB() + obj->Position.GetZ()* Plan[i].GetC() + Plan[i].GetD();
			double lon = pow(Plan[i].GetA(),2) + pow(Plan[i].GetB(),2) + pow(Plan[i].GetC(),2);
			eqa = eqa/sqrt(lon) / 2;
			obj->Position = obj->Position + Plan[i].GetN() * eqa;
		}
	}
}

bool World::TestEqua(Tr_Sphere * obj,int i)
{
	if(obj->Position.GetX() > rese[i][0] || obj->Position.GetX() < rese[i][1] || obj->Position.GetY() > rese[i][2] || obj->Position.GetY() < rese[i][3] || obj->Position.GetZ() > rese[i][4] || obj->Position.GetZ() < rese[i][5])
		return 0;
	else
	{
		double eqa = pow(obj->Position.GetX()*Plan[i].GetA() + obj->Position.GetY()*Plan[i].GetB() + obj->Position.GetZ()* Plan[i].GetC() + Plan[i].GetD(),2);
		double lon = pow(Plan[i].GetA(),2) + pow(Plan[i].GetB(),2) + pow(Plan[i].GetC(),2);
		if(lon == 0 )
			return 0;

		return ( eqa/lon ) < pow(obj->GetRad() * 1.1,2); 
	}
}

void World::Test(Tr_Sphere * obj,double resil)
{
	double const K = 0;
	for(int i=0;i<k;i++)
	{
		if(TestEqua(obj,i))
		{
			//obj->Rotated(obj->velo,Plan[i].GetN());
			double velo = obj->velo.length();
			obj->velo = Vector_norm(Plan[i].GetMat() * obj->velo * resil);
			obj->velo = obj->velo * velo;
			//obj->F = obj->F + Vector_norm(Plan[i].GetN()) * obj->F.length()/** obj->velo.length()*sqrt(K * obj->m)*/;
			
			double eqa = obj->Position.GetX()*Plan[i].GetA() + obj->Position.GetY()*Plan[i].GetB() + obj->Position.GetZ()* Plan[i].GetC() + Plan[i].GetD();
			double lon = pow(Plan[i].GetA(),2) + pow(Plan[i].GetB(),2) + pow(Plan[i].GetC(),2);
			eqa = eqa/sqrt(lon) / 2;
			obj->Position = obj->Position + Plan[i].GetN() * eqa;
		}
	}
}

double World::GetYatXZ(double X,double Z,int nomber_plane)
{
	if(Plan[nomber_plane].GetB() == 0) 
		return 0;
	return -( ( X * Plan[nomber_plane].GetA() + Z * Plan[nomber_plane].GetC() + Plan[nomber_plane].GetD() ) / Plan[nomber_plane].GetB() );
}