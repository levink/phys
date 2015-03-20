#include "../headers\Objects.h"
//BaseObject::
double const PI = 3.1415926535897932384626;
BaseObject::BaseObject()
{
	Position = Vector(0,0,0);
	velo = Vector(0,0,0);
	accel = Vector(0,0,0);
	F = Vector(0,0,0);
	w = Vector(0,0,0);
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
void Sphere::SetRad(double r)
{
	rad = r;
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
			if(rotateXZ(pl.tmp[pl.tr[0][i]],pl.tmp[pl.tr[1][i]],progect)>= 0 && 
				rotateXZ(pl.tmp[pl.tr[1][i]],pl.tmp[pl.tr[2][i]],progect)>=0 && 
				rotateXZ(pl.tmp[pl.tr[2][i]],pl.tmp[pl.tr[0][i]],progect)>=0)
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
	:rate(sqrt(2.0/3.0))
{
	SetRad(GetRad() * 4.828427);
	eng[0] = Sphere();
	eng[1] = Sphere();
	eng[2] = Sphere();
	eng[3] = Sphere();
	eng[0].Position = Vector(eng[0].GetRad(),0,eng[0].GetRad());
	eng[1].Position = Vector(-eng[1].GetRad(),0,eng[1].GetRad());
	eng[2].Position = Vector(-eng[2].GetRad(),0,-eng[2].GetRad());
	eng[3].Position = Vector(eng[3].GetRad(),0,-eng[3].GetRad());
	I = Vector(5.6 * m * pow(eng[0].GetRad(),2),9.6 * m * pow(eng[0].GetRad(),2),5.6 * m * pow(eng[0].GetRad(),2));
	a_tang = Vector();
	X = Vector(1,0,0);
	Y = Vector(0,1,0);
	Z = Vector(0,0,1);
	/*double rox[3][3] = {{1,0,0},
						{0,cos(0.0174532),sin(0.0174532)},
						{0,-sin(0.0174532),cos(0.0174532)}};
	double roy[3][3] = {{cos(0.0174532),0,-sin(0.0174532)},
						{0,1,0},
						{sin(0.0174532),0,cos(0.0174532)} };
	double roz[3][3] = {{cos(0.0174532),sin(0.0174532),0},
						{-sin(0.0174532),cos(0.0174532),0},
						{0,0,1} };
	Matrix rx = Matrix(rox);
	Matrix ry = Matrix(roy);
	Matrix rz = Matrix(roz);
	rotated = rx * ry * rz;*/
}
Quadrocopter::Quadrocopter(Vector pos)
	:rate(sqrt(2.0/3.0))
{
	Position = pos;
	SetRad(GetRad() * 4.828427);
	eng[0] = Sphere();
	eng[1] = Sphere();
	eng[2] = Sphere();
	eng[3] = Sphere();
	eng[0].Position = Vector(eng[0].GetRad() + pos.GetX(),pos.GetY(),eng[0].GetRad() + pos.GetZ());
	eng[1].Position = Vector(-eng[1].GetRad() + pos.GetX(),pos.GetY(),eng[1].GetRad() + pos.GetZ());
	eng[2].Position = Vector(-eng[2].GetRad() + pos.GetX(),pos.GetY(),-eng[2].GetRad() + pos.GetZ());
	eng[3].Position = Vector(eng[3].GetRad() + pos.GetX(),pos.GetY(),-eng[3].GetRad() + pos.GetZ());
	I = Vector(5.6 * m * pow(eng[0].GetRad(),2),9.6 * m * pow(eng[0].GetRad(),2),5.6 * m * pow(eng[0].GetRad(),2));
	a_tang = Vector();
	X = Vector(1,0,0);
	Y = Vector(0,1,0);
	Z = Vector(0,0,1);
}
void Quadrocopter::operator=(Quadrocopter& count)
{
	Position = count.Position;
	accel = count.accel;
	F = count.F;
	m = count.m;
	velo = count.velo;
	w = count.w;
	Angl = count.Angl;
	eng[0] = count.eng[0];
	eng[1] = count.eng[1];
	eng[2] = count.eng[2];
	eng[3] = count.eng[3];
	Fors[0] = count.Fors[0];
	Fors[1] = count.Fors[1];
	Fors[2] = count.Fors[2];
	Fors[3] = count.Fors[3];
	I = count.I;
	a_tang = count.a_tang;
	X = count.X;
	Y = count.Y;
	Z = count.Z; 
}
void Quadrocopter::SetForse(double e1, double e2, double e3, double e4)
{
	eng[0].F = Y * e1;//+ X * e1*0.5 + Z * e1*0.5;
	eng[1].F = Y * e2;//- X * e2*0.5 + Z * e2*0.5;
	eng[2].F = Y * e3;//- X * e3*0.5 - Z * e3*0.5;
	eng[3].F = Y * e4;//+ X * e4*0.5 - Z * e4*0.5;
	Fors[0] = X * e1*0.5 - Z * e1*0.5;
	Fors[1] = -X * e2*0.5 - Z * e2*0.5;
	Fors[2] = -X * e3*0.5 + Z * e3*0.5;
	Fors[3] = X * e4*0.5 + Z * e4*0.5;
}
void Quadrocopter::Rotated(double t_sec)
{
	Vector J[4];	// strange old comment, all right

	double local[3][3] = { {X.GetX(),X.GetY(),X.GetZ()},
	{Y.GetX(),Y.GetY(),Y.GetZ()},
	{Z.GetX(),Z.GetY(),Z.GetZ()} };
	Matrix loc_sys = Matrix(local);
	Matrix ret_loc = loc_sys.Invert();

	for(int  i = 0;i<4;i++)
	{
		J[i] = loc_sys * ((Position - eng[i].Position) * (eng[i].F + Fors[i])); 
	}
	a_tang.SetX((J[0].GetX() + J[1].GetX() + J[2].GetX() + J[3].GetX())/I.GetX()); 
	a_tang.SetY((J[0].GetY() + J[1].GetY() + J[2].GetY() + J[3].GetY())/I.GetY()); 
	a_tang.SetZ((J[0].GetZ() + J[1].GetZ() + J[2].GetZ() + J[3].GetZ())/I.GetZ());
	w.SetX(w.GetX() + a_tang.GetX() * t_sec);
	w.SetY(w.GetY() + a_tang.GetY() * t_sec);
	w.SetZ(w.GetZ() + a_tang.GetZ() * t_sec);
	double t2 = t_sec * t_sec;
	double AX = w.GetX() * t_sec + a_tang.GetX() * t2;
	double AY = w.GetY() * t_sec + a_tang.GetY() * t2;
	double AZ = w.GetZ() * t_sec + a_tang.GetZ() * t2;
	Angl.SetX(Angl.GetX() + AX);
	Angl.SetY(Angl.GetY() + AY);
	Angl.SetZ(Angl.GetZ() + AZ);
	if(Angl.GetX() > 360)
		Angl.SetX(Angl.GetX() - 360);
	if(Angl.GetY() > 360)
		Angl.SetY(Angl.GetY() - 360);
	if(Angl.GetZ() > 360)
		Angl.SetZ(Angl.GetZ() - 360);
	
	double cx = cos(AX);
	double sx = sin(AX);
	double cy = cos(AY);
	double sy = sin(AY);
	double cz = cos(AZ);
	double sz = sin(AZ);
	double rox[3][3] = {	{1,0,0},
						{0,cx,sx},
						{0,-sx,cx}};
	double roy[3][3] = {	{cy,0,-sy},
							{0,1,0},
							{sy,0,cy} };
	double roz[3][3] = {{cz,sz,0},
						{-sz,cz,0},
						{0,0,1} };
	Matrix rotx = Matrix(rox);
	Matrix roty = Matrix(roy);
	Matrix rotz = Matrix(roz);
	Matrix fin = ret_loc * rotx * roty * rotz ;
	eng[0].Position = fin * (loc_sys * (eng[0].Position - Position)) + Position;
	eng[1].Position = fin * (loc_sys * (eng[1].Position - Position)) + Position;
	eng[2].Position = fin * (loc_sys * (eng[2].Position - Position)) + Position;
	eng[3].Position = fin *	(loc_sys * (eng[3].Position - Position)) + Position;
	fin = fin * loc_sys;
	X = Vector_norm(fin * X);
	Y = Vector_norm(fin * Y);
	Z = Vector_norm(fin * Z);
	double k = sqrt(2.0/3.0);
	double l[4] = {(eng[0].F*k).length(),(eng[1].F*k).length(),(eng[2].F*k).length(),(eng[3].F*k).length()};
	eng[0].F = Y * l[0];// + X * l[0]*0.5 + Z * l[0]*0.5; 
	eng[1].F = Y * l[1];// - X * l[1]*0.5 + Z * l[1]*0.5; 
	eng[2].F = Y * l[2];// - X * l[2]*0.5 - Z * l[2]*0.5; 
	eng[3].F = Y * l[3];// + X * l[3]*0.5 - Z * l[3]*0.5; 
	Fors[0] = X * l[0]*0.5 - Z * l[0]*0.5;
	Fors[1] = - X * l[1]*0.5 - Z * l[1]*0.5;
	Fors[2] = - X * l[2]*0.5 + Z * l[2]*0.5;
	Fors[3] = X * l[3]*0.5 + Z * l[3]*0.5;
	//Qaternion rx = Qaternion(X,Angl.GetX()); // кватернионы ОНО РАБОТАЛО!!
	//Qaternion ry = Qaternion(Y,Angl.GetY());
	//Qaternion rz = Qaternion(Z,Angl.GetZ());
	//Qaternion fin = rx * ry * rz;
	//eng[0].Position = fin.rotate(eng[0].Position);
	//eng[1].Position = fin.rotate(eng[1].Position);
	//eng[2].Position = fin.rotate(eng[2].Position);
	//eng[3].Position = fin.rotate(eng[3].Position);
	//X = fin.rotate(X);
	//Y = fin.rotate(Y);
	//Z = fin.rotate(Z);
}

//ContainerObjects
ContainerObjects::ContainerObjects()
{
}
void ContainerObjects::MoveSphere(int n,double t_sec)
{
	Vector Ft = Vector(0,-obj[n].m * obj[n]._g,0); 
	//Vector Ftr = - (obj.velo /*> obj.velo*/ * p / 2) *  n * 3.14;
	Vector F = obj[n].F /*+ Ftr*/;	// + F1 + F2 + ...;
	Vector a = obj[n].F / obj[n].m;
	Vector v = obj[n].velo + a*t_sec; 
	Vector x = obj[n].Position + obj[n].velo*t_sec + (a*t_sec*t_sec)*0.5; 

	obj[n].accel = a;
	obj[n].velo = v;
	obj[n].Position = x;
	obj[n].F = Ft;
}
void ContainerObjects::MoveQuadrocopter(int n,double t_sec)
{
	int min = 0;
	if(quad[n].eng[0].F.length2() > quad[n].eng[1].F.length2())
	{
		min = 1;
	}
	if(quad[n].eng[min].F.length2() > quad[n].eng[2].F.length2())
	{
		min = 2;
	}
	if(quad[n].eng[min].F.length2() > quad[n].eng[3].F.length2())
	{
		min = 3;
	}
	Vector Ft = Vector(0,-quad[n].m * quad[n]._g,0); 
	Vector Ftr = - (quad[n].velo > quad[n].velo * 0.47 *0.5) * pow(quad[n].eng[0].GetRad(),2)  * PI;
	Vector tes = quad[n].eng[min].F * 4;
	Vector F = quad[n].F + Ftr + tes;	// + F1 + F2 + ...; // Очень странно себя ведёт
	Vector a = quad[n].F / quad[n].m;
	Vector v = quad[n].velo + a*t_sec; 

	Vector x1 = quad[n].eng[0].Position + quad[n].velo*t_sec + (a*t_sec*t_sec)*0.5; 
	Vector x2 = quad[n].eng[1].Position + quad[n].velo*t_sec + (a*t_sec*t_sec)*0.5;
	Vector x3 = quad[n].eng[2].Position + quad[n].velo*t_sec + (a*t_sec*t_sec)*0.5;
	Vector x4 = quad[n].eng[3].Position + quad[n].velo*t_sec + (a*t_sec*t_sec)*0.5;
	Vector x = quad[n].Position + quad[n].velo*t_sec + (a*t_sec*t_sec)*0.5; 

	quad[n].accel = a;
	quad[n].velo = v;
	quad[n].eng[0].Position = x1;
	quad[n].eng[1].Position = x2;
	quad[n].eng[2].Position = x3;
	quad[n].eng[3].Position = x4;
	quad[n].Position = x;
	quad[n].F = Ft + quad[n].eng[min].F * 4;

	quad[n].Rotated(t_sec);
}

vector<CollisionInfoOfSphere> ContainerObjects::inspection()
{
	vector<CollisionInfoOfSphere> col;
	int num_sp = Count_sp();
	for(int i = 0;i<num_sp;i++)
	{
		for(int e = i+1; e<num_sp;e++)
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