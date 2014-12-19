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

		return ( eqa/lon ) <= pow(obj->GetRad(),2); 
	}
}

void World::Test(Sphere * obj,double resil, double t)
{
	double const K = 0;
	for(int i=0;i<k;i++)
	{
		if(TestEqua(obj,i))
		{
			obj->Rotated(obj->velo,Plan[i].GetN());
			//double velo = obj->velo.length();
			//obj->velo = Vector_norm(Plan[i].GetMat() * obj->velo);
			//obj->velo = obj->velo * velo * resil;
			//obj->F = obj->F + Vector_norm(Plan[i].GetN()) * obj->F.length()/** obj->velo.length()*sqrt(K * obj->m)*/;
			if(obj->velo < 4.3)
				obj->velo = Vector(0,0,0);

			Vector n = Vector_norm(Plan[i].GetN());
			Vector vy = n * (((obj->velo * resil) & Plan[i].GetN()) /Plan[i].GetN().length());
			double Fy =  (((obj->F * resil) & Plan[i].GetN()) /Plan[i].GetN().length());
			Vector N_standart =  - n * Fy;
			Vector F_obj = obj->F;
			Vector N_velo = - ((vy * 2 * obj->m)/(t));
			obj->F = - ((vy * 2 * obj->m)/(t)) - n * Fy + obj->F;
			
			

			cout << "Velo to Plane : {" << obj->velo.GetX() << ", " << obj->velo.GetY() << ", " << obj->velo.GetZ() << "}.\n\n";
			double eqa =abs( obj->Position.GetX()*Plan[i].GetA() + obj->Position.GetY()*Plan[i].GetB() + obj->Position.GetZ()* Plan[i].GetC() + Plan[i].GetD());
			double lon = pow(Plan[i].GetA(),2) + pow(Plan[i].GetB(),2) + pow(Plan[i].GetC(),2);
			eqa = eqa/(sqrt(lon) );
			if((obj->velo ^ Plan[i].GetN()) < 0 )   
				obj->Position = obj->Position  + Plan[i].GetN() * (obj->GetRad() - eqa);
			else
				obj->Position = obj->Position + Plan[i].GetN() * (eqa - obj->GetRad());

			Vector Ft = Vector(0,-obj->m * obj->_g,0); 
			Vector F = obj->F; 
			Vector a = obj->F / obj->m;
			Vector v = obj->velo + a*t; 
			Vector x = obj->Position + obj->velo*t + (a*t*t)/2; 

			obj->accel = a;
			obj->velo = v;
			obj->Position = x;
			obj->F = Ft;
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

CollisionInfo * World::inspections()
{
	CollisionInfo *  col = new CollisionInfo[100];
	int current = 0;
	int max = 100;
	bool test = 1;
	for(int i = 0;i<k;i++)
	{
		Sphere * sp = NULL;//GetSphere(i);
		for(int e = 0;e <k;e++)
		{
			Plane pl = Plan[e];
			for(int c = 0;c<pl.num;c++)
			{
				if(sp->inspections(pl.tmp[i]))
				{
					current +=1;
					if(	current >= max)
					{
						CollisionInfo * copy = new CollisionInfo[max];
						for(int i = 0;i<max;i++)
						{
							copy[i] = col[i];
						}
						delete col;
						max +=10;
						col = new CollisionInfo[max];
						for(int i = 0;i<max;i++)
						{
							col[i] = copy[i];
						}
						delete copy;
					}
					col[current].pl = NULL;
					col[current].li = NULL;
					col[current].tmp = &pl.tmp[i];
					col[current].sp = sp;
					test = 0;
					return 0;
				}
			}
			for(int c = 0;c<pl.li_num && test;c++)
			{
				if(sp->inspections(pl.li[i]))
				{
					current +=1;
					if(	current >= max)
					{
						CollisionInfo * copy = new CollisionInfo[max];
						for(int i = 0;i<max;i++)
						{
							copy[i] = col[i];
						}
						delete col;
						max +=10;
						col = new CollisionInfo[max];
						for(int i = 0;i<max;i++)
						{
							col[i] = copy[i];
						}
						delete copy;
					}
					col[current].pl = NULL;
					col[current].li = &pl.li[i];
					col[current].tmp = NULL;
					col[current].sp = sp;
					test = 0;
					return 0;
				}
			}
			if(sp->inspections(pl) && test)
			{
				current +=1;
				if(	current >= max)
				{
					CollisionInfo * copy = new CollisionInfo[max];
					for(int i = 0;i<max;i++)
					{
						copy[i] = col[i];
					}
					delete col;
					max +=10;
					col = new CollisionInfo[max];
					for(int i = 0;i<max;i++)
					{
						col[i] = copy[i];
					}
					delete copy;
				}
				col[current].pl = &pl;
				col[current].li = NULL;
				col[current].tmp = NULL;
				col[current].sp = sp;
			}
			}
		}
		col[0].num = current;
	}

const double res = 1;

void World::Calculation(CollisionInfo * col, int n, double t_sec)
{
	//if(n<=col[0].num)
	//{
	//	if(col[n].tmp != NULL)
	//	{
	//		col[n].sp->calculation(col[n].tmp,res, t_sec);
	//	}
	//	if(col[n].li != NULL)
	//	{
	//		col[n].sp->calculation(col[n].li,res,t_sec);
	//	}
	//	if(col[n].pl != NULL)
	//	{
	//		col[n].sp->calculation(col[n].pl,res,t_sec);
	//	}
	//}
	
}