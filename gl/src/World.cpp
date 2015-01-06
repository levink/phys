#include <cmath>
#include<iostream>
#include "../headers/World.h"
using namespace std;

World::World(/*bool test*/)
	{
		k = 2;
		Plan = new Plane [k];
		double eq1[4]  ={-5,5,0,30};
		double eq2[4] = {0,1,0,-3};
		
		Plan[0] = Plane(eq1);
		Plan[1] = Plane(eq2);
		Plan[0].SetTmp(Vector(-10,23,31));
		Plan[0].SetTmp(Vector(-10,3,9));
		Plan[0].SetTmp(Vector(11,3,9));
		Plan[0].SetTmp(Vector(11,23,31));
		Plan[1].SetTmp(Vector(-10,3,11));
		Plan[1].SetTmp(Vector(-10,3,-10));
		Plan[1].SetTmp(Vector(11,3,-10));
		Plan[1].SetTmp(Vector(11,3,11));
		Plan[0].triangulation();
		Plan[1].triangulation();
	}

World::World(double A, double B, double C, double D, double reserve[6])
{
	Plane * copy;
		copy = new Plane[k];
		for(int i=0;i<k;i++)
		{
			copy[i] = Plan[i];
		}
		delete Plan;
		Plan = new Plane [k++];
		for(int i=0;i<k;i++)
		{
			Plan[i] = copy[i];
		}
		delete copy;
		k++;
		double eq [4]  = {A,B,C,D};
		Plan[k] = Plane(eq);
}

bool World::TestEqua(Camera * obj,int i)
{
	/*if(obj->Position.GetX() > rese[i][0] || obj->Position.GetX() < rese[i][1] || obj->Position.GetY() > rese[i][2] || obj->Position.GetY() < rese[i][3] || obj->Position.GetZ() > rese[i][4] || obj->Position.GetZ() < rese[i][5])
		return 0;
	else*/
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
	/*if(obj->Position.GetX() > rese[i][0] || obj->Position.GetX() < rese[i][1] || obj->Position.GetY() > rese[i][2] || obj->Position.GetY() < rese[i][3] || obj->Position.GetZ() > rese[i][4] || obj->Position.GetZ() < rese[i][5])
		return 0;
	else
	{*/
		double eqa = pow(obj->Position.GetX()*Plan[i].GetA() + obj->Position.GetY()*Plan[i].GetB() + obj->Position.GetZ()* Plan[i].GetC() + Plan[i].GetD(),2);
		double lon = pow(Plan[i].GetA(),2) + pow(Plan[i].GetB(),2) + pow(Plan[i].GetC(),2);
		if(lon == 0 )
			return 0;

		return ( eqa/lon ) <= pow(obj->GetRad(),2); 
	//}
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

double World::GetYatXZ(double X,double Z,int nomber_plane)
{
	if(Plan[nomber_plane].GetB() == 0) 
		return 0;
	return -( ( X * Plan[nomber_plane].GetA() + Z * Plan[nomber_plane].GetC() + Plan[nomber_plane].GetD() ) / Plan[nomber_plane].GetB() );
}

CollisionInfo * World::inspections(ContainerObjects con)
{
	CollisionInfo *  col = new CollisionInfo[100];
	for(int i = 0;i<100;i++)
	{
		col[i].tmp = Vector();
		col[i].li = Line();
		col[i].pl = Plane();
		col[i].sp = NULL;
		col[i].pl_t = 0;
		col[i].li_t = 0;
		col[i].tmp_t = 0;

	}
	int current = 0;
	int max = 100;
	bool test = 1;
	for(int i = 0;i<con.GetNumber();i++)
	{
		Sphere * sp = con.GetSphere(i);
		for(int e = 0;e <k;e++)
		{
			//Plane pl = Plan[e];
			for(int c = 0;c<Plan[e].num;c++)
			{
				if(sp->inspections(Plan[e].tmp[c]))
				{
					col[current].tmp = Plan[e].tmp[c];
					col[current].sp = sp;
					col[current].tmp_t = true;
					current += 1;
					if(	current >= max)
					{
						CollisionInfo * copy = new CollisionInfo[current];
						for(int i = 0;i<current;i++)
						{
							copy[i] = col[i];
						}
						delete col;
						col = new CollisionInfo[current+100];
						for(int i = 0;i<current+100;i++)
						{
							col[i].tmp = Vector();
							col[i].li = Line();
							col[i].pl = Plane();
							col[i].sp = NULL;
							col[i].pl_t = 0;
							col[i].li_t = 0;
							col[i].tmp_t = 0;
						}
						for(int i = 0; i < current;i++)
						{
							col[i] = copy[i];
						}
						delete copy;
						max +=100;
						
					}
					test = 0;
					return 0;
				}
			}
			for(int c = 0;c<Plan[e].li_num && test;c++)
			{
				if(sp->inspections(Plan[e].li[c]) && test)
				{
					col[current].li = Plan[e].li[c];
					col[current].sp = sp;
					col[current].li_t = true;
					current += 1;
					if(	current >= max)
					{
					
						CollisionInfo * copy = new CollisionInfo[current];
						for(int i = 0;i<current;i++)
						{
							copy[i] = col[i];
						}
						delete col;
						col = new CollisionInfo[current+100];
						for(int i = 0;i<current + 100;i++)
						{
							col[i].tmp = Vector();
							col[i].li = Line();
							col[i].pl = Plane();
							col[i].sp = NULL;
							col[i].pl_t = 0;
							col[i].li_t = 0;
							col[i].tmp_t = 0;
						}
						for(int i = 0; i < current;i++)
						{
							col[i] = copy[i];
						}
						delete copy;
						max +=100;
						
					}
					test = 0;
					return 0;
				}
			}
			if(sp->inspections(Plan[e]) && test)
			{
				col[current].pl = Plan[e];
				col[current].sp = sp;
				col[current].pl_t = true;
				current += 1;
				if(	current >= max)
				{
				
					CollisionInfo * copy = new CollisionInfo[current];
					for(int i = 0;i<current;i++)
					{
						copy[i] = col[i];
					}
					delete col;
					col = new CollisionInfo[current+100];
					for(int i = 0;i<current + 100;i++)
					{
						col[i].tmp = Vector();
						col[i].li = Line();
						col[i].pl = Plane();
						col[i].sp = NULL;
						col[i].pl_t = 0;
						col[i].li_t = 0;
						col[i].tmp_t = 0;
					}
					for(int i = 0; i < current;i++)
					{
						col[i] = copy[i];
					}
					delete copy;
					max +=100;
					
				}
			}
		}
	}
		col[0].num = current;
		return col;
}

const double res = 1;

void World::Calculation(CollisionInfo * col, int n, double t_sec)
{
	if(n<=col[0].num && (col[n].tmp_t || col[n].li_t || col[n].pl_t))
	{
		if(col[n].tmp_t)
		{
			col[n].sp->calculation(col[n].tmp,res, t_sec);
		}
		if(col[n].li_t)
		{
			col[n].sp->calculation(col[n].li,res,t_sec);
		}
		if(col[n].pl_t)
		{
			col[n].sp->calculation(col[n].pl,res,t_sec);
		}
	}
	
}
void World::Calculation(CollisionInfo * col, double t_sec)
{
	for(int i =0; i<col[0].num; i++)
	{
		if(col[i].tmp_t || col[i].li_t || col[i].pl_t )
		{
			if(col[i].tmp_t)
			{
				col[i].sp->calculation(col[i].tmp,res, t_sec);
			}
			if(col[i].li_t)
			{
				col[i].sp->calculation(col[i].li,res,t_sec);
			}
			if(col[i].pl_t)
			{
				col[i].sp->calculation(col[i].pl,res,t_sec);
			}
		}
	}
}