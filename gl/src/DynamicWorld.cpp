#include "../headers/DynamicWorld.h"
const double PI = 3.1415926;
void DynamicWorld::MoveOutSphere(Sphere * sp, double t_sec)
{
	Vector Ft = Vector(0,-sp->m * sp->_g,0); 
	//Vector Ftr = - (obj->velo /*> obj->velo*/ * p / 2) *  n * 3.14;
	Vector F = sp->F /*+ Ftr*/;	// + F1 + F2 + ...;
	Vector a = sp->F / sp->m;
	Vector v = sp->velo + a*t_sec; 
	Vector x = sp->Position + sp->velo*t_sec + (a*t_sec*t_sec)/2; 

	sp->accel = a;
	sp->velo = v;
	sp->Position = x;
	sp->F = Ft;

	double l = sp->GetRad() * 2 * PI;
	sp->Angl  = ( (sp->w * t_sec) / l) * 360 + sp->Angl;
	if(sp->Angl.GetX() > 360 || sp->Angl.GetX() < -360)
		sp->Angl.SetX(0);
	if(sp->Angl.GetY() > 360 || sp->Angl.GetY() < -360)
		sp->Angl.SetY(0);
	if(sp->Angl.GetZ() > 360 || sp->Angl.GetZ() < -360)
		sp->Angl.SetZ(0);
}

void DynamicWorld::MoveSphere(int n,double t_sec)
{
	Vector Ft = Vector(0,-obj[n].m * obj[n]._g,0); 
	//Vector Ftr = - (obj->velo /*> obj->velo*/ * p / 2) *  n * 3.14;
	Vector F = obj[n].F /*+ Ftr*/;	// + F1 + F2 + ...;
	Vector a = obj[n].F / obj[n].m;
	Vector v = obj[n].velo + a*t_sec; 
	Vector x = obj[n].Position + obj[n].velo*t_sec + (a*t_sec*t_sec)/2; 

	obj[n].accel = a;
	obj[n].velo = v;
	obj[n].Position = x;
	obj[n].F = Ft;

	double l = obj[n].GetRad() * 2 * PI;
	obj[n].Angl  = ( (obj[n].w * t_sec) / l) * 360 + obj[n].Angl;
	if(obj[n].Angl.GetX() > 360 || obj[n].Angl.GetX() < -360)
	   obj[n].Angl.SetX(0);
	if(obj[n].Angl.GetY() > 360 || obj[n].Angl.GetY() < -360)
		obj[n].Angl.SetY(0);
	if(obj[n].Angl.GetZ() > 360 || obj[n].Angl.GetZ() < -360)
		obj[n].Angl.SetZ(0);
}

DynamicWorld::DynamicWorld()
{
	
}

void DynamicWorld::Add(Sphere& elem)
{	
	Sphere* tmp = new Sphere(elem);
	obj.insert(obj.end(), *tmp);
}

vector<CollisionInfoOfSphere> DynamicWorld::inspection()
{
	vector <CollisionInfoOfSphere>  col;
	int current = 0;
	for(int i = 0;i<obj.size();i++)
	{
		for(int e = i+1; e<obj.size();e++)
		{
			if(obj[i].Test(&obj[e]))
			{
				col[current].sp1 = &obj[i];
				col[current].sp2 = &obj[e];
				current += 1;
			}
		}
	}
	return col;
}
void DynamicWorld::calculation(vector<CollisionInfoOfSphere> col,int n)
{
	if(n <=col.size())
	{
		col[n].sp1->HandlerCollision(col[n].sp2);
	}
}
void DynamicWorld::all_calculation(vector<CollisionInfoOfSphere> col)
{
	int c_n = col.size();
	for(int i = 0;i<c_n;i++)
	{
		col[i].sp1->HandlerCollision(col[i].sp2);
	}
}
