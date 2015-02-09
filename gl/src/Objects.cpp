#include "../headers\Objects.h"
//BaseObject::
double const PI = 3.1415926535897932384626;
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
	m = 10;
}


void Sphere::Rotated(Vector ve1, Vector nor)//начальны йвектор скорости и вектор, к которому строится перпендикуляр
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
		B = 0.0001;
	if(nor.GetY() * C + nor.GetZ() * B == 0)
		C+=1;
	double _z = - (nor.GetX() + nor.GetY() * (A + D)) / (nor.GetY() * C + nor.GetZ() * B);
	double _y = (A + _z * C + D) / B; 
	double _x = 1;
	Vector normal = Vector_norm(Vector(_x,_y,_z));
	
	if(normal.length() != 0)
		w = normal * ( velo & normal ) / normal.length() ;
		//w = ( normal * ( velo & normal ) / velo.length() ) * 0.2 ;
}


bool Sphere::Test(Sphere * obj)
{
	return ((obj->Position - Position).length2() < (rad + obj->rad)* (rad + obj->rad) * 1.001);
}
void Sphere::HandlerCollision(Sphere * obj, double tim)
{
	double x = obj->Position.GetX() - Position.GetX();
	double y = obj->Position.GetY() - Position.GetY();
	double z = obj->Position.GetZ() - Position.GetZ();

	double eq[3]  = {x,y,z};
	Vector norm = Vector(eq);
	norm = Vector_norm(norm);
	double e[3] = {0,0,0};

	Vector ve2 = Vector();
	Vector ve1 = Vector();

	Vector D = (velo - obj->velo) * obj->m;
	Vector A = velo * m + obj->velo * obj->m;
	if(D.length2() == 0)
	{
		ve1 = (A) / (m + obj->m);
		ve2 = (A - ve1 * m) / (obj->m);
	}
	else
	{
		ve1 = (A + D) / (m + obj->m);
		ve2 = (A - ve1 * m) / (obj->m);
		Vector t_1 = velo > velo * m + obj->velo > obj->velo * obj->m;
		Vector t_2 = ve1 > ve1 * m + ve2 > ve2 * obj->m; 
		double test = t_1.length2() - t_2.length2();
		if( test > 0.0000001 || test < -0.0000001)
		{
			ve1 = (A  - D) / (m + obj->m);
			ve2 = (A - ve1 * m) / (obj->m);
		}
	}

	if(ve1 < 0.01)
		ve1 = e;
	if(ve2 < 0.01)
		ve2 = e;
	
	velo = -norm * ve2.length();
	obj->velo = norm * ve1.length();
	/*velo = ve1;
	obj->velo = ve2;*/
	
	/*velo = plan->GetInvertMat() * velo;
	obj->velo = plan->GetInvertMat() * obj->velo;*/

	//if((velo ^ norm) > 0)
	//	velo = plan->GetMat() * /*velo*/ve1 * res;
	//else
	//		velo = -/*velo*/norm * (ve1 * res).length();
	//if( (obj->velo ^ norm) < 0)
	//	obj->velo = plan->GetMat() * /*obj->velo*/ve2 * res;
	//else
	//	obj->velo = /*obj->velo*/norm * (ve2 * res).length();
	double len = (obj->Position - Position).length2();
	len = sqrt(len);
	len = ((rad + obj->GetRad()) - len)/2; 
	
	 Position = Position - norm * len;
	 obj->Position = obj->Position + norm * len;

	Rotated(obj->velo,eq);
	obj->Rotated(velo,eq);

	if((norm & F) > 0)
	{
		F = - (norm * (obj->F & norm)) + F;
		obj->F = (norm * (F & norm) + obj->F);
	}
	else
	{
		F = (norm * (obj->F & norm)) + F;
		obj->F = -(norm * (F & norm) + obj->F);
	}
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

bool Sphere::inspections(Plane pl)
{
	if(!pl.cubeinspection(Position))
		return false;
	else
	{
		double eqa = pow(Position.GetX()*pl.GetA() + Position.GetY()*pl.GetB() + Position.GetZ()* pl.GetC() + pl.GetD(),2);
		double lon = pow(pl.GetA(),2) + pow(pl.GetB(),2) + pow(pl.GetC(),2);

		if(lon == 0 )
			return false;
		if((eqa/lon ) <= rad * rad)
		{
			Vector progect = pl.project(&Position);
			
			bool flag = false;
			for(int i = 0; i< pl.tr_num; i++)
			{
				if(((Vector(progect.GetX() - pl.tmp[pl.tr[0][i]].GetX(),progect.GetY() - pl.tmp[pl.tr[0][i]].GetY(),progect.GetZ() - pl.tmp[pl.tr[0][i]].GetZ()) & pl.nor[0][i]) >= 0) &&
					((Vector(progect.GetX() - pl.tmp[pl.tr[1][i]].GetX(),progect.GetY() - pl.tmp[pl.tr[1][i]].GetY(),progect.GetZ() - pl.tmp[pl.tr[1][i]].GetZ()) & pl.nor[1][i]) >= 0) &&
					((Vector(progect.GetX() - pl.tmp[pl.tr[2][i]].GetX(),progect.GetY() - pl.tmp[pl.tr[2][i]].GetY(),progect.GetZ() - pl.tmp[pl.tr[2][i]].GetZ()) & pl.nor[2][i]) >= 0) )
				{
					flag = true;
					return true;
				}
			}
			if(flag)
				return true;
			else
				return false;
		}
		else
			return false;
	}
}
void Sphere::calculation(Plane pl,double resil, double t)
{
	Vector normal = pl.GetN();
	Rotated(velo,normal);
	Vector ve = velo;
	//double velo = obj->velo.length();
	//obj->velo = Vector_norm(Plan[i].GetMat() * obj->velo);
	//obj->velo = obj->velo * velo * resil;
	//obj->F = obj->F + Vector_norm(Plan[i].GetN()) * obj->F.length()/** obj->velo.length()*sqrt(K * obj->m)*/;
	/*if(velo < 0.1)
		velo = Vector(0,0,0);*/

	Vector n = Vector_norm(normal);
	Vector vy = n * (((velo * resil) & normal) /normal.length());
	double Fy =  (((F /** resil*/) & normal) /normal.length());
	Vector N_standart =  - n * Fy;
	Vector F_obj = F;
	Vector N_velo = - ((vy * 2 * m)/(t));
	F = - ((vy * 2 * m)/(t)) - n * Fy + F;

	/*if((normal & ve) <= 0)
		F = -F;*/

	cout << "Velo to Plane : {" << velo.GetX() << ", " << velo.GetY() << ", " << velo.GetZ() << "}.\n\n";
	double eqa =abs( Position.GetX()*pl.GetA() + Position.GetY()*pl.GetB() + Position.GetZ()* pl.GetC() + pl.GetD());
	double lon = pow(pl.GetA(),2) + pow(pl.GetB(),2) + pow(pl.GetC(),2);
	eqa = eqa/(sqrt(lon));
	if((ve ^ normal) < 0 )   
		Position = Position  + n * (rad - eqa);
	else
		Position = Position + n * (eqa - rad);

	accel = F/m;
	velo = velo +  accel*t;
	F = Vector(0,-m * _g,0);
}
bool Sphere::inspections(Line li)
{
	Vector pro = li.projection(Position);
	bool a = pro.GetX() < li.limit[0] + rad && pro.GetX() > li.limit[1] - rad; 
	bool b = pro.GetY() < li.limit[2] + rad && pro.GetY() > li.limit[3] - rad; 
	bool c = pro.GetZ() < li.limit[4] + rad && pro.GetZ() > li.limit[5] - rad;
	if(a && b && c)
	{
		if(((Vector(li.tmp.GetX() - Position.GetX(),li.tmp.GetY() - Position.GetY(),li.tmp.GetZ() - Position.GetZ()) * li.vec).length2() / li.vec.length2()) < rad * rad)
		{
			return true;
		}
		else
			return false;
		//return (((Vector(li.tmp.GetX() - Position.GetX(),li.tmp.GetY() - Position.GetY(),li.tmp.GetZ() - Position.GetZ()) * li.vec).length2() / li.vec.length2()) < rad * rad);
	}
	else
		return false;
}
void Sphere::calculation(Line li, double resil, double t)
{
	Vector pro = li.projection(Position);
	Vector normal = Vector(Position.GetX() - pro.GetX(),Position.GetY() - pro.GetY(),Position.GetZ() - pro.GetZ());
	Vector vec_n = Vector_norm(normal);
	Vector vy = vec_n * (((velo * resil) & normal) /normal.length());
	double Fy =  (((F * resil) & normal) /normal.length());
	F = - ((vy * 2 * m) / t) + vec_n * Fy + F;

	double eqa = abs( Position.GetX()*normal.GetX() + Position.GetY()*normal.GetY() + Position.GetZ()* normal.GetZ() - (li.tmp.GetX() * normal.GetX() + li.tmp.GetY() * normal.GetY() + li.tmp.GetZ() * normal.GetZ()));
	double lon = pow(normal.GetX(),2) + pow(normal.GetY(),2) + pow(normal.GetZ(),2);
	eqa = eqa/(sqrt(lon) );
	if((velo ^ normal) < 0 )   
		Position = Position  + vec_n * (rad - eqa);
	else
		Position = Position + vec_n * (eqa - rad);

	accel = F/m;
	velo = velo +  accel*t;
	F = Vector(0,-m * _g,0);
	
}
bool Sphere::inspections(Vector tmp)
{
	return ((Vector(tmp.GetX() - Position.GetX(),tmp.GetY() - Position.GetY(),tmp.GetZ() - Position.GetZ()).length2()) < rad * rad);
}
void Sphere::calculation(Vector tmp, double resil, double t)
{
	Vector normal = Vector(Position.GetX() - tmp.GetX(), Position.GetX() - tmp.GetY(), Position.GetX() - tmp.GetZ());
	Vector vec_n = Vector_norm(normal);
	Vector vy = vec_n * (((velo * resil) & normal) /normal.length());
	double Fy =  (((F * resil) & normal) /normal.length());
	F = - ((vy * 2 * m) / t) + vec_n * Fy + F;

	double eqa = abs( Position.GetX()*normal.GetX() + Position.GetY()*normal.GetY() + Position.GetZ()* normal.GetZ() - (tmp.GetX() * normal.GetX() + tmp.GetY() * normal.GetY() + tmp.GetZ() * normal.GetZ()));
	double lon = pow(normal.GetX(),2) + pow(normal.GetY(),2) + pow(normal.GetZ(),2);
	eqa = eqa/(sqrt(lon) );
	if((velo ^ normal) < 0 )   
		Position = Position  + vec_n * (rad - eqa);
	else
		Position = Position + vec_n * (eqa - rad);

	accel = F/m;
	velo = velo +  accel*t;
	F = Vector(0,-m * _g,0);
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

//Quadrocopter
Quadrocopter::Quadrocopter()
{
	centre = Sphere();
	eng[0] = Sphere();
	eng[1] = Sphere();
	eng[2] = Sphere();
	eng[3] = Sphere();
	eng[0].Position = Vector(centre.GetRad(),0,centre.GetRad());
	eng[1].Position = Vector(-centre.GetRad(),0,centre.GetRad());
	eng[2].Position = Vector(-centre.GetRad(),0,-centre.GetRad());
	eng[3].Position = Vector(centre.GetRad(),0,-centre.GetRad());
	I = Vector();
	a_tang = Vector();
	X = Vector(1,0,0);
	Y = Vector(0,1,0);
	Z = Vector(0,0,1);
}
Quadrocopter::Quadrocopter(Vector pos)
{
	centre = Sphere();
	centre.Position = pos;
	eng[0] = Sphere();
	eng[1] = Sphere();
	eng[2] = Sphere();
	eng[3] = Sphere();
	eng[0].Position = Vector(centre.GetRad() + pos.GetX(),pos.GetY(),centre.GetRad() + pos.GetZ());
	eng[1].Position = Vector(-centre.GetRad() + pos.GetX(),pos.GetY(),centre.GetRad() + pos.GetZ());
	eng[2].Position = Vector(-centre.GetRad() + pos.GetX(),pos.GetY(),-centre.GetRad() + pos.GetZ());
	eng[3].Position = Vector(centre.GetRad() + pos.GetX(),pos.GetY(),-centre.GetRad() + pos.GetZ());
	I = Vector();
	a_tang = Vector();
	X = Vector(1,0,0);
	Y = Vector(0,1,0);
	Z = Vector(0,0,1);
}
void Quadrocopter::SetForse(double e1, double e2, double e3, double e4)
{
	eng[0].F = eng[0].F + Y * e1;
	eng[1].F = eng[1].F + Y * e2;
	eng[2].F = eng[2].F + Y * e3;
	eng[3].F = eng[3].F + Y * e4;
}
void Quadrocopter::Rotated(double t_sec)
{
	// положить в рссчёт перемещения
	int min = 0;
	if(eng[0].F.length2() > eng[1].F.length2())
	{
		min = 1;
	}
	if(eng[min].F.length2() > eng[2].F.length2())
	{
		min = 2;
	}
	if(eng[min].F.length2() > eng[3].F.length2())
	{
		min = 3;
	}
	// положить в рссчёт перемещения eng[min].F - сила, действующая на центр
	double r = 1.141421 * centre.GetRad();
	double Jx[4];
	double Jy[4];
	double Jz[4];
	for(int  i = 0;i<4;i++)
	{
		Jx[i] = ((eng[i].F * r) & X); // будет работать только если X, Y, Z - нормализованны
		Jy[i] = ((eng[i].F * r) & Y);
		Jz[i] = ((eng[i].F * r) & Z);
	}
	a_tang.SetX((Jx[0] + Jx[1] + Jx[2] + Jx[3])/I.GetX());
	a_tang.SetY((Jy[0] + Jy[1] + Jy[2] + Jy[3])/I.GetY());
	a_tang.SetZ((Jz[0] + Jz[1] + Jz[2] + Jz[3])/I.GetZ());
	w.SetX(w.GetX() + a_tang.GetX() * t_sec);
	w.SetY(w.GetY() + a_tang.GetY() * t_sec);
	w.SetZ(w.GetZ() + a_tang.GetZ() * t_sec);
	Angl.SetX(Angl.GetX() + w.GetX() * t_sec);
	Angl.SetY(Angl.GetY() + w.GetY() * t_sec);
	Angl.SetZ(Angl.GetZ() + w.GetZ() * t_sec);
	if(Angl.GetX() > 360)
		Angl.SetX(Angl.GetX() - 360);
	if(Angl.GetY() > 360)
		Angl.SetY(Angl.GetY() - 360);
	if(Angl.GetZ() > 360)
		Angl.SetZ(Angl.GetZ() - 360);
}

//ContainerObjects
void ContainerObjects::MoveSphere(int n,double t_sec)
{
	Vector Ft = Vector(0,-obj[n].m * obj[n]._g,0); 
	//Vector Ftr = - (obj.velo /*> obj.velo*/ * p / 2) *  n * 3.14;
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

ContainerObjects::ContainerObjects()
{

}

vector<CollisionInfoOfSphere> ContainerObjects::inspection()
{
	vector<CollisionInfoOfSphere> col;
	for(int i = 0;i<Count();i++)
	{
		for(int e = i+1; e<Count();e++)
		{
			if(obj[i].Test(&obj[e]))
			{	
				CollisionInfoOfSphere co;
				co.sp1 = &obj[i];
				co.sp2 = &obj[e];
				col.insert(col.end(),co);
			}
		}
	}
	return col;
}
void ContainerObjects::calculation(vector<CollisionInfoOfSphere> col,int n,double time)
{
	if(n <=col.size())
	{
		col[n].sp1->HandlerCollision(col[n].sp2,time);
	}
}
void ContainerObjects::all_calculation(vector<CollisionInfoOfSphere> col,double time)
{
	int c_n = col.size(); 
	for(int i = 0;i<c_n;i++)
	{
		col[i].sp1->HandlerCollision(col[i].sp2,time);
	}
}


void Polyg::Plan()
{
	/*double com = 0;
	bool pl_test = 1;
	int global_test = 0; // мы можем с уверенностью сказать, что определили все грани фигуры, 
	int er_cou = 0;		 // если каждое её ребро принадлежит двум граням, чесло граней = число вершин. 
	bool test = 0;		 // Тогда, если global_test = число вершин * 2, то мы определили все грани.
	bool cor_test;
	bool one = 1;
	bool one_er = 1;
	double tm[3][3] = { {tmp[0][0],tmp[0][1],tmp[0][2]},
						{tmp[1][0],tmp[1][1],tmp[1][2]},
						{tmp[2][0],tmp[2][1],tmp[2][2]}};
	plan = new int[3][9];
	plan[0][0] = 0;
	plan[0][1] = 1;
	plan[0][2] = 2;
	int max = 8;
	int nom = 2;
	nom_pl = 0;
	Plane pl = Plane(tm);
	global_test += 1; // первая грань, образованная 1 и 0 точками, принадлежит одной плоскости
	while(global_test < nom_tmp*2)
	{
		
		for(int i = 0;i<nom_tmp;i++)
		{
			com = pl.GetA() * tmp[i][0] + pl.GetB() * tmp[i][1] + pl.GetC() * tmp[i][2] + pl.GetD();
			while(one)
			{
				if(i!= plan[nom_pl][0] && i!= plan[nom_pl][1] && i!=plan[nom_pl][2])
				{
					test = com > 0;
					one = 0;
				}
				i++;
			}
			if(i!= plan[nom_pl][0] && i!= plan[nom_pl][1] && i!=plan[nom_pl][2])
			{
				cor_test = com > 0;
			}
			if(cor_test != test)
			{
				pl_test = 0;
				return;
			}
			if(com == 0 )
			{
				if(nom<max)
				{
					nom++;
					plan[nom_pl][nom] = i;
				}
				else
				{
					int ** cop;
					cop = new int[nom_pl][max]; 
					for(int i = 0;i <= nom_pl;i++)
					{
						for(int e = 0; e <= max; e++)
						{
							cop[i][e] = plan[i][e]; 
						}
					}
					delete plan;
					max +=6;
					plan = new int[nom_pl][max];
					for(int i = 0;i<=nom_pl;i++)
					{
						for(int e = 0; e <= nom; e++)
						{
							plan[i][e] = cop[i][e];
						}
					}
					nom++;
					plan[nom_pl][nom] = i;
				}
				if(plan[nom_pl][nom] = plan[nom_pl][nom-1] + 1 || (plan[nom_pl][nom] == nom_tmp-- && plan[nom_pl][0] == 0))
				{
					global_test++;
				}
			}
		}
	}*/
}