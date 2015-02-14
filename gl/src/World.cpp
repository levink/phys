#include <cmath>
#include<iostream>
#include "../headers/World.h"
using namespace std;


//коэффициент упругости

World::World(/*bool test*/)
	:res(0.95)
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

vector<CollisionInfo> World::inspections(ContainerObjects* con)
{
	vector<CollisionInfo> col;
	bool test = 1;
	int co_qa = con->Count_quad();
	int co_sp = con->Count_sp();
	int co = 0;
	if(co_sp >co_qa)
		co = co_sp;
	else
		co = co_qa;
	for(int i = 0;i<co;i++)
	{
		Sphere * sp;
		Quadrocopter * qa;
		bool sp_gl_tes = true;
		bool qa_gl_tes = true;
		if(i<co_sp)
			sp = con->Get_sp(i);
		else
			sp_gl_tes = false;
		if(i<co_qa)
			qa = con->Get_quad(i);
		else
			qa_gl_tes = false;
		for(int e = 0;e < Count(); e++)
		{
			bool sp_tes = false;
			bool qa_tes = false;
			if(sp_gl_tes)
				if(Plan[e].cubeinspection(sp->Position,sp->GetRad()))
					sp_tes = true;
			if(qa_gl_tes)
				if(Plan[e].cubeinspection(qa->Position,qa->GetRad()))
					qa_tes = true;
			for(int c = 0;c<Plan[e].num;c++)
			{
				if(sp_gl_tes)
					if(sp->inspections(Plan[e].tmp[c]) && sp_tes)
					{
						CollisionInfo co;
						co.tmp = Plan[e].tmp[c];
						co.sp = sp;
						co.tmp_t = true;
						co.li_t = false;
						co.pl_t = false;
						co.sp_t = true;
						co.qa_t = false;
						col.insert(col.end(),co);		
						test = 0;
					}
				if(qa_gl_tes)
					if(qa->eng[0].inspections(Plan[e].tmp[c]) || qa->eng[1].inspections(Plan[e].tmp[c])
						|| qa->eng[2].inspections(Plan[e].tmp[c]) || qa->eng[3].inspections(Plan[e].tmp[c]))
					{
						CollisionInfo co;
						co.tmp = Plan[e].tmp[c];
						co.qa = qa;
						co.tmp_t = true;
						co.li_t = false;
						co.pl_t = false;
						co.sp_t = false;
						co.qa_t = true;
						co.nom_qa = i;
						col.insert(col.end(),co);		
						test = 0;
					}
			}
			for(int c = 0;c<Plan[e].li_num && test;c++)
			{
				if(sp_gl_tes)
					if(sp->inspections(Plan[e].li[c]) && test)
					{
						CollisionInfo co;
						co.li = Plan[e].li[c];
						co.sp = sp;
						co.tmp_t = false;
						co.li_t = true;
						co.pl_t = false;
						co.sp_t = true;
						co.qa_t = false;
						col.insert(col.end(),co);
						test = 0;
					}
				if(qa_gl_tes)
					if(	(qa->eng[0].inspections(Plan[e].li[c]) || qa->eng[1].inspections(Plan[e].li[c])||
						qa->eng[2].inspections(Plan[e].li[c]) || qa->eng[3].inspections(Plan[e].li[c])) && test)
					{
						CollisionInfo co;
						co.li = Plan[e].li[c];
						co.qa = qa;
						co.tmp_t = false;
						co.li_t = true;
						co.pl_t = false;
						co.sp_t = false;
						co.qa_t = true;
						co.nom_qa = i;
						col.insert(col.end(),co);		
						test = 0;
					}
			}
			if(sp_gl_tes)
				if(sp->inspections(Plan[e]) && test)
				{
					CollisionInfo co;
					co.pl = Plan[e];
					co.sp = sp;
					co.tmp_t = false;
					co.li_t = false;
					co.pl_t = true;
					co.sp_t = true;
					co.qa_t = false;
					col.insert(col.end(),co);
				}
			if(qa_gl_tes)
				if(	(qa->eng[0].inspections(Plan[e]) || qa->eng[1].inspections(Plan[e])||
					qa->eng[2].inspections(Plan[e]) || qa->eng[3].inspections(Plan[e])) && test)
					{
						CollisionInfo co;
						co.pl = Plan[e];
						co.qa = qa;
						co.tmp_t = false;
						co.li_t = false;
						co.pl_t = true;
						co.sp_t = false;
						co.qa_t = true;
						co.nom_qa = i;
						col.insert(col.end(),co);		
						test = 0;
					}
		}
	}
	return col;
}

void World::Calculation(vector<CollisionInfo> col, int n, double t_sec)
{
	if(n<=col.size() && (col[n].tmp_t || col[n].li_t || col[n].pl_t))
	{
		if(col[n].tmp_t && col[n].sp_t)
		{
			col[n].sp->calculation(col[n].tmp, res, t_sec);
		}
		if(col[n].li_t && col[n].sp_t)
		{
			col[n].sp->calculation(col[n].li, res,t_sec);
		}
		if(col[n].pl_t && col[n].sp_t)
		{
			col[n].sp->calculation(col[n].pl, res,t_sec);
		}
	}
	
}
void World::Calculation_pl(vector<CollisionInfo> col, double t_sec)
{
	int c_n = col.size();
	for(int i =0; i<c_n; i++)
	{
		if(col[i].pl_t)
		{
			col[i].sp->calculation(col[i].pl,res,t_sec);
		}
	}
}
void World::Calculation(vector<CollisionInfo> col, double t_sec)
{
	int c_n = col.size();
	for(int i =0; i<c_n; i++)
	{
		if(col[i].tmp_t && col[i].sp_t)
		{
			col[i].sp->calculation(col[i].tmp,res, t_sec);
		}
		if(col[i].li_t && col[i].sp_t)
		{
			col[i].sp->calculation(col[i].li,res,t_sec);
		}
		if(col[i].pl_t && col[i].sp_t)
		{
			col[i].sp->calculation(col[i].pl,res,t_sec);
		}
	}
}