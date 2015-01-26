#include <cmath>
#include<iostream>
#include "../headers/World.h"
#include "../headers/DynamicWorld.h"
using namespace std;

StaticWorld::StaticWorld()
{
	double eq[4] = {0,1,0,-3}; // немного не правильный шестиугольник
	Plan[0] = Plane(eq);
	vector<Vector> a;
	a.insert(a.end(),Vector(0,0,-8));
	a.insert(a.end(),Vector(6.9282,0,-4));
	a.insert(a.end(),Vector(6.9282,0,4));
	a.insert(a.end(),Vector(0,0,8));
	a.insert(a.end(),Vector(-6.9282,0,4));
	a.insert(a.end(),Vector(-6.9282,0,-4));
	Plan[0].SetPoints(a);
}

bool StaticWorld::TestEqua(Camera * obj,int i)
{
	throw exception("Not tested");
	/*if(obj->p.GetX() > rese[i][0] || obj->p.GetX() < rese[i][1] || obj->p.GetY() > rese[i][2] || obj->p.GetY() < rese[i][3] || obj->p.GetZ() > rese[i][4] || obj->p.GetZ() < rese[i][5])
		return 0;
	else*/
	return true;//( obj->Position.GetX()*items[i].GetA() + obj->Position.GetY()*items[i].GetB() + obj->Position.GetZ()* items[i].GetC() + items[i].GetD() ) < 0; // изменить знак неравенства на <
}

void StaticWorld::Test(Camera * obj,double resil)
{
	throw exception("Not tested");
	/*for(int i=0;i<k;i++)
	{
		if(TestEqua(obj,i))
		{
			obj->velo = Plan[i].GetMat() * obj->velo * resil;
		}
	}*/
}

bool StaticWorld::TestEqua(Sphere * obj,int i)
{
	throw exception("Not tested");
	/*if(obj->p.GetX() > rese[i][0] || obj->p.GetX() < rese[i][1] || obj->p.GetY() > rese[i][2] || obj->p.GetY() < rese[i][3] || obj->p.GetZ() > rese[i][4] || obj->p.GetZ() < rese[i][5])
		return 0;
	else
	{*/
	/*	double eqa = pow(obj->p.GetX()*Plan[i].GetA() + obj->p.GetY()*Plan[i].GetB() + obj->p.GetZ()* Plan[i].GetC() + Plan[i].GetD(),2);
		double lon = pow(Plan[i].GetA(),2) + pow(Plan[i].GetB(),2) + pow(Plan[i].GetC(),2);
		if(lon == 0 )
			return 0;

		return ( eqa/lon ) <= pow(obj->GetRad(),2); */
	return false;
	//}
}

void StaticWorld::Test(Sphere * obj,double resil, double t)
{
	throw exception("Not tested");
	//double const K = 0;
	//for(int i=0;i<k;i++)
	//{
	//	if(TestEqua(obj,i))
	//	{
	//		obj->Rotated(obj->velo,Plan[i].GetN());
	//		//double velo = obj->velo.length();
	//		//obj->velo = Vector_norm(Plan[i].GetMat() * obj->velo);
	//		//obj->velo = obj->velo * velo * resil;
	//		//obj->F = obj->F + Vector_norm(Plan[i].GetN()) * obj->F.length()/** obj->velo.length()*sqrt(K * obj->m)*/;
	//		if(obj->velo < 4.3)
	//			obj->velo = Vector(0,0,0);

	//		Vector n = Vector_norm(Plan[i].GetN());
	//		Vector vy = n * (((obj->velo * resil) & Plan[i].GetN()) /Plan[i].GetN().length());
	//		double Fy =  (((obj->F * resil) & Plan[i].GetN()) /Plan[i].GetN().length());
	//		Vector N_standart =  - n * Fy;
	//		Vector F_obj = obj->F;
	//		Vector N_velo = - ((vy * 2 * obj->m)/(t));
	//		obj->F = - ((vy * 2 * obj->m)/(t)) - n * Fy + obj->F;

	//		cout << "Velo to Plane : {" << obj->velo.GetX() << ", " << obj->velo.GetY() << ", " << obj->velo.GetZ() << "}.\n\n";
	//		double eqa =abs( obj->p.GetX()*Plan[i].GetA() + obj->p.GetY()*Plan[i].GetB() + obj->p.GetZ()* Plan[i].GetC() + Plan[i].GetD());
	//		double lon = pow(Plan[i].GetA(),2) + pow(Plan[i].GetB(),2) + pow(Plan[i].GetC(),2);
	//		eqa = eqa/(sqrt(lon) );
	//		if((obj->velo ^ Plan[i].GetN()) < 0 )   
	//			obj->p = obj->p  + Plan[i].GetN() * (obj->GetRad() - eqa);
	//		else
	//			obj->p = obj->p + Plan[i].GetN() * (eqa - obj->GetRad());

	//		Vector Ft = Vector(0,-obj->m * obj->_g,0); 
	//		Vector F = obj->F; 
	//		Vector a = obj->F / obj->m;
	//		Vector v = obj->velo + a*t; 
	//		Vector x = obj->p + obj->velo*t + (a*t*t)/2; 

	//		obj->a = a;
	//		obj->velo = v;
	//		obj->p = x;
	//		obj->F = Ft;
	//	}
	//}
}

double StaticWorld::GetYatXZ(double X,double Z,int nomber_plane)
{
	if(Plan[nomber_plane].GetB() == 0) 
		return 0;
	return -( ( X * Plan[nomber_plane].GetA() + Z * Plan[nomber_plane].GetC() + Plan[nomber_plane].GetD() ) / Plan[nomber_plane].GetB() );
}

void StaticWorld::inspections(DynamicWorld con, vector<Collision>& v)
{
	int sphereCount = con.Count();
	for(int i = 0;i<sphereCount;i++)
	{
		bool found = false;
		Sphere *sp = con.Get(i);
		int planeCount = Plan.size();
		for(int j = 0; !found && j < planeCount; j++)
		{	
			//Пересечение с углами
			Plane &pl = Plan[j];
			for(int c = 0;c < pl.tmp.size(); c++)
			{
				if(sp->inspections(pl.tmp[c]))
				{
					collision[i].type = CollisionType::WITH_POINT;
					collision[i].sp = con.Get(i);
					found = true;
				}
			}
			
			//Пересечение с гранями
			int edges = pl.li.size();
			for(int c = 0; !found && c < edges; c++)
			{
				if(sp->inspections(pl.li[c]))
				{
					tmp.type = CollisionType::WITH_LINE;
					tmp.line = &pl.li[c];
					found = true;
				}
			}
			
			//Пересечение с плоскостью
			if(!found && tmp.sp->inspections(pl))
			{
				tmp.type = CollisionType::WITH_PLANE;
				tmp.plane = &pl;
				found = true;
			}
			if (found)
			{
				v.insert(v.end(), tmp);
			}
		}
	}
}

void StaticWorld::Calculation(vector<Collision>& v, double t_sec)
{
	/*double res = 1.0;
	for(int i = 0; i < v.size(); i++)
	{
		if(v[i].type == CollisionType::WITH_POINT)
		{
			(*v[i].sp).calculation(*v[i].point, res, t_sec);
		}
		if(v[i].type == CollisionType::WITH_LINE)
		{
			(*v[i].sp).calculation(*v[i].line, res, t_sec);
		}
		if(v[i].type == CollisionType::WITH_PLANE)
		{
			Sphere s = Sphere(*v[i].sp);
			s.calculation(*v[i].plane, res, t_sec);
		}

	}*/
}