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
	BaseObject();
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

void Sphere::Test_Sphere(Sphere * obj, bool motion)
{
	double const res = 0.8;
	double const K = 10;
	double len = (obj->Position - Position).length2();
	if( len < (rad + obj->rad)* (rad + obj->rad) * 1.001 || motion)
	{
		double x = obj->Position.GetX() - Position.GetX();
		double y = obj->Position.GetY() - Position.GetY();
		double z = obj->Position.GetZ() - Position.GetZ();

		double eq[3]  = {x,y,z};
		Vector norm = Vector(eq);
		norm = Vector_norm(norm);
		double e[3] = {0,0,0};

		Plane * plan  = new Plane();
		plan->PlaneSetEquation(eq);	

		Vector ve2 = Vector();
		Vector ve1 = Vector();
		
		velo = plan->GetBathis() * velo;
		obj->velo = plan->GetBathis() * obj->velo;

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
		velo = ve1;
		obj->velo = ve2;

		velo = plan->GetInvertMat() * velo;
		obj->velo = plan->GetInvertMat() * obj->velo;

		//if((velo ^ norm) > 0)
		//	velo = plan->GetMat() * /*velo*/ve1 * res;
		//else
		//		velo = -/*velo*/norm * (ve1 * res).length();
		//if( (obj->velo ^ norm) < 0)
		//	obj->velo = plan->GetMat() * /*obj->velo*/ve2 * res;
		//else
		//	obj->velo = /*obj->velo*/norm * (ve2 * res).length();

		len = sqrt(len);
		len = ((rad + obj->rad) - len)/2; 
		
		 Position = Position - norm * len;
		 obj->Position = obj->Position + norm * len;

		Rotated(obj->velo,eq);
		obj->Rotated(velo,eq);

		if((norm ^ F) > 0)
		{
			F = - (norm * (obj->F & norm)) + F;
			obj->F = (norm * (F & norm) + obj->F);
		}
		else
		{
			F = (norm * (obj->F & norm)) + F;
			obj->F = -(norm * (F & norm) + obj->F);
		}
		delete plan;
	}
}

bool Sphere::Test(Sphere * obj)
{
	return ((obj->Position - Position).length2() < (rad + obj->rad)* (rad + obj->rad) * 1.001);
}
void Sphere::HandlerCollision(Sphere * obj)
{
	double x = obj->Position.GetX() - Position.GetX();
	double y = obj->Position.GetY() - Position.GetY();
	double z = obj->Position.GetZ() - Position.GetZ();

	double eq[3]  = {x,y,z};
	Vector norm = Vector(eq);
	norm = Vector_norm(norm);
	double e[3] = {0,0,0};

	Plane * plan  = new Plane();
	plan->PlaneSetEquation(eq);	

	Vector ve2 = Vector();
	Vector ve1 = Vector();
	
	velo = plan->GetBathis() * velo;
	obj->velo = plan->GetBathis() * obj->velo;

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
	velo = ve1;
	obj->velo = ve2;

	velo = plan->GetInvertMat() * velo;
	obj->velo = plan->GetInvertMat() * obj->velo;

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
	delete plan;
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
		return 0;
	else
	{
		double eqa = pow(Position.GetX()*pl.GetA() + Position.GetY()*pl.GetB() + Position.GetZ()* pl.GetC() + pl.GetD(),2);
		double lon = pow(pl.GetA(),2) + pow(pl.GetB(),2) + pow(pl.GetC(),2);

		if(lon == 0 )
			return 0;
		if((eqa/lon ) <= rad * rad)
		{
			Vector progect;
			double x = ((Position.GetX()/pl.GetA()) *(pl.GetB() * pl.GetB() + pl.GetC() * pl.GetC()) - pl.GetB() * Position.GetY() - pl.GetC() * Position.GetZ() - pl.GetD())/(pl.GetA() + (pl.GetB() * pl.GetB() + pl.GetC() * pl.GetC())/pl.GetA());
			progect = Vector(x,(pl.GetB() * (x - Position.GetX()))/pl.GetA() + Position.GetY(),(pl.GetC() * (x - Position.GetX()))/pl.GetA() + Position.GetZ());

			bool test = ((Vector(progect.GetX() - pl.tmp_p[0].GetX(),progect.GetY() - pl.tmp_p[0].GetY(),progect.GetZ() - pl.tmp_p[0].GetZ()) & pl.li[0].norm) > 0);
			bool flag = 1;

			for(int i = 1;i<pl.li_num;i++)
			{
				if( ((Vector(progect.GetX() - pl.tmp_p[i].GetX(),progect.GetY() - pl.tmp_p[i].GetY(),progect.GetZ() - pl.tmp_p[i].GetZ()) & pl.li[i].norm) != test))
				{
					flag = 0;
					return 0;
				}
			}
			if(flag == 1)
				return 1;
			else
				return 0;
		} 
	}
}
void Sphere::calculation(Plane pl,double resil, double t)
{
	Vector normal = pl.GetN();
	Rotated(velo,normal);
	//double velo = obj->velo.length();
	//obj->velo = Vector_norm(Plan[i].GetMat() * obj->velo);
	//obj->velo = obj->velo * velo * resil;
	//obj->F = obj->F + Vector_norm(Plan[i].GetN()) * obj->F.length()/** obj->velo.length()*sqrt(K * obj->m)*/;
	if(velo < 4.3)
		velo = Vector(0,0,0);

	Vector n = Vector_norm(normal);
	Vector vy = n * (((velo * resil) & normal) /normal.length());
	double Fy =  (((F * resil) & normal) /normal.length());
	Vector N_standart =  - n * Fy;
	Vector F_obj = F;
	Vector N_velo = - ((vy * 2 * m)/(t));
	F = - ((vy * 2 * m)/(t)) - n * Fy + F;
	
	cout << "Velo to Plane : {" << velo.GetX() << ", " << velo.GetY() << ", " << velo.GetZ() << "}.\n\n";
	double eqa =abs( Position.GetX()*pl.GetA() + Position.GetY()*pl.GetB() + Position.GetZ()* pl.GetC() + pl.GetD());
	double lon = pow(pl.GetA(),2) + pow(pl.GetB(),2) + pow(pl.GetC(),2);
	eqa = eqa/(sqrt(lon) );
	if((velo ^ normal) < 0 )   
		Position = Position  + normal * (rad - eqa);
	else
		Position = Position + normal * (eqa - rad);

	Vector Ft = Vector(0,-m * _g,0); 
	F = Ft; 
	accel = F / m;
	velo = velo + accel*t; 
	Position = Position + velo*t + (accel*t*t)/2; 
}
bool Sphere::inspections(Line li)
{
	return (((Vector(li.tmp.GetX() - Position.GetX(),li.tmp.GetY() - Position.GetY(),li.tmp.GetZ() - Position.GetZ()) * li.vec).length2() / li.vec.length2()) < rad * rad);
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
		Position = Position  + normal * (rad - eqa);
	else
		Position = Position + normal * (eqa - rad);

	Vector Ft = Vector(0,-m * _g,0); 
	F = Ft; 
	accel = F / m;
	velo = velo + accel*t; 
	Position = Position + velo*t + (accel*t*t)/2; 
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
		Position = Position  + normal * (rad - eqa);
	else
		Position = Position + normal * (eqa - rad);

	Vector Ft = Vector(0,-m * _g,0); 
	F = Ft; 
	accel = F / m;
	velo = velo + accel*t; 
	Position = Position + velo*t + (accel*t*t)/2; 
}

Tr_Sphere:: Tr_Sphere()
{
	rad = 1;
	_g = 9.8;
	BaseObject();
	I = 0.4 * m * rad * rad;
}

void Tr_Sphere:: Rotated(Tr_Sphere * obj)
{
	Vector norm = Vector(1,1,-((obj->velo.GetX() + obj->velo.GetY()) / obj->velo.GetZ()));
	Vector tmp = Vector(Position.GetX() - ((Position.GetX() * velo.GetY() * norm.GetX() - obj->Position.GetX() * norm.GetY() *  velo.GetX() - Position.GetY() * velo.GetX() * norm.GetX() + obj->Position.GetY() * velo.GetX() * norm.GetX())/ (velo.GetY() * norm.GetX() - norm.GetY() * velo.GetX())),
						Position.GetY() - ((Position.GetY() * velo.GetX() * norm.GetY() - obj->Position.GetY() * norm.GetX() *  velo.GetY() - Position.GetX() * velo.GetY() * norm.GetX() + obj->Position.GetX() * velo.GetY() * norm.GetY())/ (velo.GetX() * norm.GetY() - norm.GetX() * velo.GetY())),
						Position.GetZ() - ((Position.GetZ() * velo.GetY() * norm.GetZ() - obj->Position.GetZ() * norm.GetY() *  velo.GetZ() - Position.GetY() * velo.GetZ() * norm.GetX() + obj->Position.GetY() * velo.GetZ() * norm.GetZ())/ (velo.GetY() * norm.GetZ() - norm.GetY() * velo.GetZ())));
	double r = tmp.length();
	Vector rot = velo *  (velo.length() - ((velo & norm) / norm.length())); 
	double en = ((r/rad) * m * (pow(rot.length(),2)))/ I;

}

void Tr_Sphere:: Test(Tr_Sphere * obj, bool motion)
{
	double const res = 0.8;
	double const K = 10;
	double len = (obj->Position - Position).length2();
	if( len < (rad + obj->rad)* (rad + obj->rad) * 1.001 || motion)
	{
		double x = obj->Position.GetX() - Position.GetX();
		double y = obj->Position.GetY() - Position.GetY();
		double z = obj->Position.GetZ() - Position.GetZ();

		double eq[3]  = {x,y,z};
		Vector norm = Vector(eq);
		norm = Vector_norm(norm);
		double e[3] = {0,0,0};

		Plane * plan  = new Plane();
		plan->PlaneSetEquation(eq);	

		Vector ve2 = Vector();
		Vector ve1 = Vector();
		
		velo = plan->GetBathis() * velo;
		obj->velo = plan->GetBathis() * obj->velo;

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
		
		if((-velo ^ ve1) > 0)
			velo = plan->GetInvertMat() * ve1 * res;
		if((-obj->velo ^ norm) < 0)
			obj->velo = plan->GetInvertMat() * ve2 * res;

		velo = plan->GetInvertMat() * ve1;
		obj->velo = plan->GetInvertMat() * ve2;

		len = sqrt(len);
		len = ((rad + obj->rad) - len)/2; 
		
		 Position = Position - norm * len;
		 obj->Position = obj->Position + norm * len;

		//Rotated(obj->velo,eq);
		//obj->Rotated(velo,eq);

		if((norm ^ F) > 0)
		{
			F = - (norm * (obj->F & norm)) + F;
			obj->F = (norm * (F & norm) + obj->F);
		}
		else
		{
			F = (norm * (obj->F & norm)) + F;
			obj->F = -(norm * (F & norm) + obj->F);
		}
		delete plan;
	}
}

double Tr_Sphere:: GetRad()
{
	return rad;
}

void Tr_Sphere:: operator=(Tr_Sphere * count)
{
	Position = count->Position;
	accel = count->accel;
	F = count->F;
	m = count->m;
	velo = count->velo;
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

void ContainerObjects::MoveOutSphere(Sphere * sp, double t_sec)
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

void ContainerObjects::MoveSphere(int n,double t_sec)
{
	Vector Ft = Vector(0,-obj[n]->m * obj[n]->_g,0); 
	//Vector Ftr = - (obj->velo /*> obj->velo*/ * p / 2) *  n * 3.14;
	Vector F = obj[n]->F /*+ Ftr*/;	// + F1 + F2 + ...;
	Vector a = obj[n]->F / obj[n]->m;
	Vector v = obj[n]->velo + a*t_sec; 
	Vector x = obj[n]->Position + obj[n]->velo*t_sec + (a*t_sec*t_sec)/2; 

	obj[n]->accel = a;
	obj[n]->velo = v;
	obj[n]->Position = x;
	obj[n]->F = Ft;

	double l = obj[n]->GetRad() * 2 * PI;
	obj[n]->Angl  = ( (obj[n]->w * t_sec) / l) * 360 + obj[n]->Angl;
	if(obj[n]->Angl.GetX() > 360 || obj[n]->Angl.GetX() < -360)
		obj[n]->Angl.SetX(0);
	if(obj[n]->Angl.GetY() > 360 || obj[n]->Angl.GetY() < -360)
		obj[n]->Angl.SetY(0);
	if(obj[n]->Angl.GetZ() > 360 || obj[n]->Angl.GetZ() < -360)
		obj[n]->Angl.SetZ(0);
}

ContainerObjects::ContainerObjects()
{
	obj = NULL;
	number = 0;
}

void ContainerObjects::CreateSphere(Sphere * count)
{
	number +=1;
	Sphere ** copy = new Sphere*[number];
	for(int i = 0; i< number;i++)
	{
		copy[i] = obj[i];
	}
	delete obj;
	obj = new Sphere*[number];
	for(int i = 0; i<number;i++)
	{
		obj[i] = copy[i];
	}
	delete copy;
	obj[number] = count;
}

Sphere* ContainerObjects::GetSphere(int n)
{
	if(n<=number)
		return obj[n];
	else
		return &Sphere();
}

CollisionInfoOfSphere* ContainerObjects::inspection()
{
	CollisionInfoOfSphere * col = new CollisionInfoOfSphere[50];
	int current = 0;
	int max = 100;
	for(int i = 0;i<number;i++)
	{
		for(int e = i+1; e<number;e++)
		{
			if(obj[i]->Test(obj[e]))
			{
				current +=1;
				if(	current >= max)
				{
				/*	CollisionInfo * copy = new CollisionInfo[max];
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
					delete copy;*/
				}
				col[current].sp1 = obj[i];
				col[current].sp2 = obj[e];
			}
		}
	}
	col[0].num = current;
	return NULL;
}
void ContainerObjects::calculation(CollisionInfoOfSphere * col,int n)
{
	if(n <=col[0].num)
	{
		col[n].sp1->HandlerCollision(col[n].sp2);
	}
}
void ContainerObjects::all_calculation(CollisionInfoOfSphere * col)
{
	for(int i = 0;i<col[0].num;i++)
	{
		col[i].sp1->HandlerCollision(col[i].sp2);
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