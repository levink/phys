#include <cmath>
#include<iostream>
#include "../headers/World.h"
using namespace std;


//коэффициент упругости

World::World(/*bool test*/)
	:res(1)
{

	//Vector a[] = {	Vector(0,0,-8),
	//				Vector(6.9282,0,-4),
	//				Vector(6.9282,0,4),
	//				Vector(0,0,8),
	//				Vector(-6.9282,0,4),
	//				Vector(-6.9282,0,-4) };
}



double World::GetYatXZ(double X, double Z, int planeNum)
{ 
	Plane* p = &Plan[planeNum];
	if(p->GetB() == 0) return 0;
	return -(( X * p->GetA() + 
		       Z * p->GetC() + 
			   1 * p->GetD() ) / p->GetB() );
}

vector<CollisionInfo> World::inspections(ContainerObjects con)
{
	vector<CollisionInfo> col;
	bool test = 1;
	for(int i = 0;i<con.Count();i++)
	{
		Sphere * sp = con.Get(i);
		for(int e = 0;e < Count(); e++)
		{
			//Plane pl = Plan[e];
			for(int c = 0;c<Plan[e].num;c++)
			{
				if(sp->inspections(Plan[e].tmp[c]))
				{
					CollisionInfo co;
					co.tmp = Plan[e].tmp[c];
					co.sp = sp;
					co.tmp_t = true;
					co.li_t = false;
					co.pl_t = false;
					col.insert(col.end(),co);		
					test = 0;
				}
			}
			for(int c = 0;c<Plan[e].li_num && test;c++)
			{
				if(sp->inspections(Plan[e].li[c]) && test)
				{
					CollisionInfo co;
					co.li = Plan[e].li[c];
					co.sp = sp;
					co.tmp_t = false;
					co.li_t = true;
					co.pl_t = false;
					col.insert(col.end(),co);
					test = 0;
				}
			}
			if(sp->inspections(Plan[e]) && test)
			{
				CollisionInfo co;
				co.pl = Plan[e];
				co.sp = sp;
				co.tmp_t = false;
				co.li_t = false;
				co.pl_t = true;
				col.insert(col.end(),co);
			}
		}
	}
		return col;
}
void World::Calculation(vector<CollisionInfo> col, int n, double t_sec)
{
	if(n<=col.size() && (col[n].tmp_t || col[n].li_t || col[n].pl_t))
	{
		if(col[n].tmp_t)
		{
			col[n].sp->calculation(col[n].tmp, res, t_sec);
		}
		if(col[n].li_t)
		{
			col[n].sp->calculation(col[n].li, res,t_sec);
		}
		if(col[n].pl_t)
		{
			col[n].sp->calculation(col[n].pl, res,t_sec);
		}
	}
	
}
void World::Calculation(vector<CollisionInfo> col, double t_sec)
{
	int c_n = col.size();
	for(int i =0; i<c_n; i++)
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