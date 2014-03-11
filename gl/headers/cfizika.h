#include <Windows.h>
#include<cmath>

#ifndef __FIZIKA_H
#define __FIZIKA_H

#define E 20
#define T 5
#define res 0.8
// ‘изика
//’е-’е
class Vector
{
private:
	double x;
	double y;
	double z;
public:
	Vector()
	{
		x=0;
		y=0;
		z=0;
	}
	Vector(double _x, double _y, double _z)
	{
		x=_x;
		y=_y;
		z=_z;
	}

	Vector(double v [3])
	{
		x=v[0];
		y=v[1];
		z=v[2];
	}

	double GetX()
	{
		return x;
	}
	double GetY()
	{
		return y;
	}
	double GetZ()
	{
		return z;
	}
	void SetX(double newx)
	{
		x=newx;
	}
	void SetY(double newy)
	{
		y=newy;
	}
	void SetZ(double newz)
	{
		z=newz;
	}
	double distanse (Vector ve1, Vector ve2)
	{
		double _x = ve1.GetX() - ve2.GetX();
		double _y = ve1.GetY() - ve2.GetY();
		double _z =	ve1.GetZ() - ve2.GetZ();
		return sqrt( pow(_x,2) + pow(_y,2) + pow(_z,2) ); 
	}
	double distanse()
	{
		return sqrt( pow(x,2) + pow(y,2) + pow(z,2) );
	}
	Vector operator-(Vector secondValue)
	{
		double _x = x - secondValue.GetX();
		double _y = y - secondValue.GetY();
		double _z = z - secondValue.GetZ();
		return Vector(_x, _y, _z);
	}
	Vector operator-()
	{
		double _x = - x;
		double _y = - y;
		double _z = - z;
		return Vector(_x, _y, _z); 
	}
	Vector operator+(Vector secondValue)
	{
		double _x = x + secondValue.GetX();
		double _y = y + secondValue.GetY();
		double _z = z + secondValue.GetZ();
		return Vector(_x, _y, _z);
	}
	Vector operator*(double u)
	{
		double _x = x * u;
		double _y = y * u;
		double _z = z * u;
		return Vector(_x,_y,_z);
	}
	Vector operator*(Vector count)
	{
		double _x = y * count.z - z * count.y;
		double _y = z * count.x - x * count.z;
		double _z = x * count.y - y * count.x;
		return Vector(_x,_y,_z);
	}
	double operator/(Vector count)
	{
		return x * count.GetX() + y * count.GetY() + z * count.GetZ(); 
	}
	double operator>(Vector count)
	{
		return x * count.GetX() + y * count.GetY() + z * count.GetZ(); 
	}
	Vector operator= (Vector inicialisingValue)
	{
		x = inicialisingValue.GetX();
		y = inicialisingValue.GetY();
		z = inicialisingValue.GetZ();
		return Vector (x,y,z);
	}
	Vector operator/(double u)
	{
		double _x = x * 1 / u;
		double _y = y * 1 / u;
		double _z = z * 1 / u;
		return Vector(_x,_y,_z);
	}
	bool operator !=(Vector test)
	{
		bool i = 0;
		if(x != test.GetX())
			if(y != test.GetY())
				if(z != test.GetZ())
					i=1;
		return i;
	}
	bool operator<(double test)
	{
		bool tes =0;
		if( sqrt(pow(x,2) + pow(y,2) + pow(z,2) ) < test)
			tes = 1;
		return tes;
	}
	bool operator==(Vector test)
	{
		if(x==test.GetX() && y == test.GetY() && z == test.GetZ())
			return 1;
		return 0;
	}
};

class Matrix
{
	private:
		double mat [3][3];
	public:
		Matrix()
		{
			for(int i=0;i<3;i++)
				for(int e=0;e<3;e++)
					mat[i][e] = 0;
		}

		Matrix(double count[3][3])
		{
			for(int i=0;i<3;i++)
				for(int e=0;e<3;e++)
					mat[i][e] = count[i][e];
		}

		double  GetM(int a,int b)
		{
			return mat[a][b];
		}

		void SetM(double in_mat[3][3])
		{
			for(int i=0;i<3;i++)
				for(int e=0;e<3;e++)
					mat[i][e] = in_mat[i][e];
		}

		void SetM(double count,int a,int b)
		{
			mat[a][b] = count;
		}

		double Determinant()
		{
			double a1 = mat[0][0] * ( mat[1][1] * mat[2][2] - mat[2][1] * mat[1][2]);
			double a2 = mat[0][1] * ( mat[1][0] * mat[2][2] - mat[2][0] * mat[1][2]);
			double a3 = mat[0][2] * ( mat[1][0] * mat[2][1] - mat[2][0] * mat[1][1]);
			double determinant = a1 - a2 + a3;
			if(determinant == 0)
				determinant = 1;
			return determinant;
		}
		
		Matrix  Matrix_alg_aff()
		{
			double matA [3][3];
			
			matA[0][0] = mat[1][1] * mat[2][2] - mat[2][1] * mat[1][2];
			matA[0][1] = - ( mat[1][0] * mat[2][2] - mat[2][0] * mat[1][2] );
			matA[0][2] = mat[1][0] * mat[2][1] - mat[2][0] * mat[1][1];
			matA[1][0] = - ( mat[0][1] * mat[2][2] - mat[2][1] * mat[0][2] ); 
			matA[1][1] = mat[0][0] * mat[2][2] - mat[2][0] * mat[0][2]; 
			matA[1][2] = - ( mat[0][0] * mat[2][1] - mat[2][0] * mat[0][1] ); // сейчас 0.33 надо -0.36
			matA[2][0] = mat[0][1] * mat[1][2] - mat[1][1] * mat[0][2];
			matA[2][1] = - ( mat[0][0] * mat[1][2] - mat[1][0] * mat[0][2] );
			matA[2][2] = mat[0][0] * mat[1][1] - mat[1][0] * mat[0][1];
			
			return Matrix(matA);
		}

		Matrix Transposition()
		{
			double trans [3][3];
			for(int i=0;i<3;i++)
				for(int e=0;e<3;e++)
					trans[e][i] = mat[i][e];
			return Matrix(trans);
		}

		Matrix operator* (double t)
		{
			double _mat[3][3];
			for(int i=0;i<3;i++)
				for(int e=0;e<3;e++)
					_mat[i][e] = mat[i][e] * t;
			return Matrix(_mat);
		}

		Vector operator* (Vector vector)
		{
			double vec [3];
			for(int i=0;i<3;i++)
			{
				vec [i] = mat[i][0] * vector.GetX() +  mat[i][1] * vector.GetY() + mat[i][2] * vector.GetZ();
			}
			return Vector(vec);
		}

		Matrix operator* (Matrix Cmat)
		{
			double _mat [3][3];

			for(int i=0;i<3;i++)
			{
				for(int e=0;e<3;e++)
					_mat[i][e] = mat[i][0] * Cmat.GetM(0,e) + mat[i][1] * Cmat.GetM(1,e) + mat[i][2] * Cmat.GetM(2,e);
			}
			return Matrix(_mat);
		}

		Matrix operator/ (double t)
		{
			double _mat[3][3];
			for(int i=0;i<3;i++)
				for(int e=0;e<3;e++)
					_mat[i][e] = mat[i][e] / t;
			return Matrix(mat);
		}

		Matrix operator= ( Matrix count)
		{
			for(int i=0;i<3;i++)
				for(int e=0;e<3;e++)
					mat[i][e] = count.GetM(i,e);
			return Matrix(mat);
		}

		Matrix Inverted()
		{
			Matrix InvertMat;
			double determin = Determinant();
			Matrix matAlgAff = Matrix_alg_aff();
			matAlgAff = matAlgAff.Transposition();
			InvertMat = matAlgAff * (1 / determin);
			return InvertMat;
		}
};

class Plane
{
private:
	double tmp [3][3];
	Matrix Mat;
	double equa [4];
public:
	Plane()
	{
		for(int i=0;i<3;i++)
		{
			equa[i] = 0;
			for(int e=0;e<3;e++)
			{
				tmp[i][e] = 0;
			}
		}
		equa[3] = 0; 
	}
	
	Plane(double Ctmp[3][3])
	{
		equa[0] = Ctmp[1][0]*(Ctmp[2][1] - Ctmp[2][2]) + Ctmp[1][1]*(Ctmp[2][2] - Ctmp[2][0]) + Ctmp[1][2]*(Ctmp[2][0] - Ctmp[2][1]);
		equa[1] = Ctmp[2][0]*(Ctmp[0][1] - Ctmp[0][2]) + Ctmp[2][1]*(Ctmp[0][2] - Ctmp[0][0]) + Ctmp[2][2]*(Ctmp[0][0] - Ctmp[0][1]);
		equa[2] = Ctmp[0][0]*(Ctmp[1][1] - Ctmp[1][2]) + Ctmp[0][1]*(Ctmp[1][2] - Ctmp[1][0]) + Ctmp[0][2]*(Ctmp[1][0] - Ctmp[1][1]);

		double longg  = sqrt(equa[0] * equa[0] + equa[0] * equa[0] + equa[0] * equa[0]); 
		equa[0] = equa[0] / longg;
		equa[1] = equa[1] / longg;
		equa[2] = equa[2] / longg;

		equa[3] = - equa[0] - equa[1] - equa[2];

		double a[3] = {Ctmp[0][0] - Ctmp[1][0],Ctmp[0][1] - Ctmp[1][1],Ctmp[0][2] - Ctmp[1][2]};
		double b[3];
		// коллинеальные вектора, в том числе и нормаль

		longg  = sqrt(a[0] * a[0] + a[0] * a[0] + a[0] * a[0]); 
		a[0] = a[0] / longg;
		a[1] = a[1] / longg;
		a[2] = a[2] / longg;

		b[0] = -a[0];
		b[1] = a[1];
		b[2] = a[2];
		/*double e = -(equa[2] * a[0] - a[2] * equa[0]) / (a[1]*equa[0] - a[0] * equa[1]);

		b[2] = - equa[3] / ((e * equa[1] + equa[2])/equa[0])  * equa[0] + e* equa[1] + equa[2];
		b[1] = e*b[2];
		b[0] = - (b[2] * equa[1] + b[2] * equa[2]) / equa[0];*/

		for(int i=0;i<3;i++)
		{
			Mat.SetM(a[i],i,0);
			Mat.SetM(equa[i],i,1);
			Mat.SetM(b[i],i,2);
		}
		Matrix invert = Mat;
		invert = invert.Inverted();

		double redoun[3][3] = 
		{	{1,0,0},
			{0,-1,0},
			{0,0,1}, };
		Matrix rebound = Matrix(redoun);

		Mat = invert * rebound * Mat;
	}

	Plane(Vector x1,Vector x2, Vector x3)
	{
		equa[0] = x2.GetX() * (x3.GetY() - x3.GetZ()) + x2.GetY() * (x3.GetZ() - x3.GetX()) + x2.GetZ() * (x3.GetX() - x3.GetY());
		equa[1] = x3.GetX() * (x1.GetY() - x1.GetZ()) + x3.GetY() * (x1.GetZ() - x1.GetX()) + x3.GetZ() * (x1.GetX() - x1.GetY());
		equa[2] = x1.GetX() * (x2.GetY() - x2.GetZ()) + x1.GetY() * (x2.GetZ() - x2.GetX()) + x1.GetZ() * (x2.GetX() - x2.GetY());

		double longg  = sqrt(equa[0] * equa[0] + equa[0] * equa[0] + equa[0] * equa[0]); 
		equa[0] = equa[0] / longg;
		equa[1] = equa[1] / longg;
		equa[2] = equa[2] / longg;

		equa[3] = - equa[0] - equa[1] - equa[2];

		double a[3] = {x1.GetX() - x2.GetX(), x1.GetY() - x2.GetY(),x1.GetZ() - x2.GetZ()};
		double b[3];
		// коллинеальные вектора, в том числе и нормаль

		longg  = sqrt(a[0] * a[0] + a[0] * a[0] + a[0] * a[0]); 
		a[0] = a[0] / longg;
		a[1] = a[1] / longg;
		a[2] = a[2] / longg;

		b[0] = -a[0];
		b[1] = a[1];
		b[2] = a[2];
		/*double e = -(equa[2] * a[0] - a[2] * equa[0]) / (a[1]*equa[0] - a[0] * equa[1]);

		b[2] = - equa[3] / ((e * equa[1] + equa[2])/equa[0])  * equa[0] + e* equa[1] + equa[2];
		b[1] = e*b[2];
		b[0] = - (b[2] * equa[1] + b[2] * equa[2]) / equa[0];*/

		for(int i=0;i<3;i++)
		{
			Mat.SetM(a[i],i,0);
			Mat.SetM(equa[i],i,1);
			Mat.SetM(b[i],i,2);
		}
		/*Matrix invert = Mat;
		invert = invert.Inverted();

		double redoun[3][3] = 
		{	{1,0,0},
			{0,-1,0},
			{0,0,1}, };
		Matrix rebound = Matrix(redoun);

		Mat = invert * rebound * Mat;*/
	}

	Plane(double eq [4])
	{
		for(int i=0;i<4;i++)
		{
			equa[i] = eq[i];
			if(equa[i] == 0)
				equa[i] = 1;
		}

		double longg  =sqrt(equa[0] * equa[0] + equa[0] * equa[0] + equa[0] * equa[0]); 
		equa[0] = equa[0] / longg;
		equa[1] = equa[1] / longg;
		equa[2] = equa[2] / longg;
		//equa[3] = - equa[0] - equa[1] - equa[2];
		if(equa[0] == 0)
			equa[0] =1;

		double a[3];
		a[0] = equa[0];
		a[1] = -equa[1];
		a[2] = equa[2];

		double b[3];
		// коллинеальные вектора, в том числе и нормаль
		b[0] = -a[0];
		b[1] = a[1];
		b[2] = a[2];

		for(int i=0;i<3;i++)
		{
			Mat.SetM(a[i],i,0);
			Mat.SetM(equa[i],i,1);
			Mat.SetM(b[i],i,2);
		}
		Matrix invert = Mat;
		invert = invert.Inverted();

		double redoun[3][3] = 
		{	{1,0,0},
			{0,-1,0},
			{0,0,1}, };
		Matrix rebound = Matrix(redoun);

		Mat = invert * rebound * Mat;
	}

	Matrix GetMat()
	{
		return Mat;
	}
	Vector GetN()
	{
		return Vector(equa[0],equa[1],equa[2]);
	}
	double GetA()
	{
		return equa[0];
	}
	double GetB()
	{
		return equa[1];
	}
	double GetC()
	{
		return equa[2];
	}
	double GetD()
	{
		return equa[3];
	}
};

struct AllObject
{
	/*bool tes [100][100];
	Sphere * obj;*/
};

class BaseObject
{
public:
	Vector Position;
	DWORD bornTime;
	double m;
	Vector velo;
	Vector accel;
	Vector F;
	Vector ve_ro;
	Vector Angl;
	BaseObject()
	{
		Position = Vector(0,0,0);
		velo = Vector(0,0,0);
		accel = Vector(0,0,0);
		F = Vector(0,0,0);
		Angl = Vector(0,0,0);
		m = 10;
		bornTime = 0;
	}
};

class Sphere: public BaseObject
{
private: 
	double rad;
	double _g;
public:
	Sphere()
	{
		rad = 1;
		_g = 10;
		BaseObject();
	}

	Sphere * TestMO (Sphere * obj, double t);

	void Rotated(Vector ve1, Vector nor)//начальны йвектор скорости и вектор, к которому строитс€ перпендикул€р
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
			B = 1;
		if(nor.GetY() * C + nor.GetZ() * B == 0)
			C+=1;
		double _z = - (nor.GetX() + nor.GetY() * (A + D)) / (nor.GetY() * C + nor.GetZ() * B);
		double _y = (A + _z * C + D) / B; 
		double _x = 1;
		Vector normal = Vector(_x,_y,_z);

		if(normal.distanse() != 0)
			ve_ro = normal * ( velo > normal ) / normal.distanse();
	}

	void Test(Sphere * obj, bool motion)
	{
		if(velo.distanse(Position,obj->Position) < (rad + obj->rad) * 1.01 || motion)
		{
			double x = obj->Position.GetX() - Position.GetX();
			double y = obj->Position.GetY() - Position.GetY();
			double z = obj->Position.GetZ() - Position.GetZ();

			double eq[3]  = {x,y,z};
			Vector norm = (eq);
			double e[3] = {0,0,0};
			Plane * plan  = new Plane(eq);
			Vector impulse = velo * m + obj->velo * obj->m;
			Vector ve1 = impulse / (2 * m);
			Vector ve2 = impulse / (2 * obj->m);
			
			if(velo < 0.01)
				velo = e;
			if(obj->velo < 0.01)
				obj->velo = e;


			if(velo / norm > 0)
				velo = plan->GetMat() * ve1 /*velo*/ * res;
			else
				velo = ve1;
			if(obj->velo / norm < 0)
				obj->velo = plan->GetMat() * ve2 /*obj->velo*/ * res;
			else
				obj->velo = ve2;

			Rotated(ve1,eq);
			obj->Rotated(ve2,eq);
			//	velo = plan->GetMat() * /*ve1*/ velo * res;

			//obj->velo = plan->GetMat() * /*ve2*/ obj->velo * res;
			delete plan;
		}
	}
	
	double GetRad()
	{
		return rad;
	}
};

class Line
{
private:
	double k;
	double e;
public:
	Line()
	{
		k = 0;
		e = 0;
	}
	Line(Vector a, Vector b)
	{
		k = (b.GetX() - a.GetX()) / (b.GetY() - a.GetY());
		e = a.GetX() - a.GetY() * k;
	}
	bool Up_Down(Vector point)
	{
		if(point.GetX() > point.GetY() * k + e)
			return 1;
		else
			return 0;
	}
};

class Margin
{
private:
	Plane plan;
	Vector * tmp;
	int number;
	int * line [2];
public:
	Margin()
	{
		plan = Plane();
		tmp = NULL;
		number = 0;
		line[0] = NULL;
		line[1] = NULL;
	}
	Margin(Vector point1,Vector point2,Vector point3)
	{
		Vector * copy;
			copy = new Vector[number];
			for(int i=0;i<number;i++)
			{
				copy[i] = tmp[i];
			}
			delete tmp;
			tmp = new Vector [number+3];
			for(int i=0;i<number;i++)
			{
				tmp[i] = copy[i];
			}
				number++;
				tmp[number] = point1;
				number++;
				tmp[number] = point2;
				number++;
				tmp[number] = point3;
			delete copy;
		plan = Plane(point1,point2,point3);
	}
	bool Test(Vector point )
	{
		if(plan.GetA() * point.GetX() + plan.GetB() * point.GetX() + plan.GetC() * point.GetZ() + plan.GetD() ==0)
			return 1;
		else 
			return 0;
	}
	bool SetTmp(Vector point)
	{
		if(Test(point) ==1)
		{
			Vector * copy;
			copy = new Vector[number];
			for(int i=0;i<number;i++)
			{
				copy[i] = tmp[i];
			}
			delete tmp;
			tmp = new Vector [number++];
			for(int i=0;i<number;i++)
			{
				tmp[i] = copy[i];
			}
			number++;
			tmp[number] = point;
			delete copy;
			return 1;
		}
		else 
			return 0;

	}
	void MakeLine()
	{
		Line l;
		bool t;
		line[0] = new int [number];
		line[1] = new int [number];
		int l_t = 0;
		Vector * c_tmp;
		c_tmp = new Vector [number];
		for(int i=0;i<number;i++)
		{
			c_tmp[i] = plan.GetMat() * tmp[i]; 
		}
		for(int i=0;i<number;i++)
		{
			for(int e=0;e<number;e++)
			{
				if(i != e)
				{	
					l = Line(tmp[i],tmp[e]);
					for(int a =0;a<number;a++)
					{
						bool test;
						bool first = 1;
						if(a != e && a!= i)
						{
							if(first)
							{
								test = l.Up_Down(tmp[a]);\
								first = 0;
							}
							if(l.Up_Down(tmp[a]) != test)
							{
								t = 0;
								return;
							}
						}
					}
					if(t != 0)
					{
						line[0][l_t] = i;
						line[0][l_t] = i;
						l_t++;
					}
				}
			}
		}
	}
};

class Polyg : public BaseObject
{
private:
	Margin * mar;
	int nu_m;
	Vector * tmp;
	int nu_t;
	double _g;
public:
	Polyg()
	{
		mar = NULL;
		nu_m = 0;
		tmp = NULL;
		nu_t = 0;
		_g = 9.8;
	}
	void SetTmp(Vector p1)
	{
		Vector * copy;
		copy = new Vector [nu_t];
		for(int i=0;i<nu_t ;i++)
		{
			copy[i] = tmp[i];
		}
		delete tmp;
		tmp = new Vector[nu_t++];
		for(int i=0;i<nu_t;i++)
		{
			tmp[i] = copy[i];
		}
		nu_t ++;
		tmp[nu_t ] = p1;
		delete copy;
	}
	void SetMargin(Vector p1,Vector p2,Vector p3)
	{
		Margin * copy;
		copy = new Margin [nu_m];
		for(int i=0;i<nu_m ;i++)
		{
			copy[i] = mar[i];
		}
		delete mar;
		mar = new Margin[nu_m++];
		for(int i=0;i<nu_m;i++)
		{
			mar[i] = copy[i];
		}
		nu_m ++;
		mar[nu_m ] = Margin(p1,p2,p3);
		delete copy;
	}
	int GetN_t()
	{
		return nu_t;
	}
	double Get_tmpX(int i)
	{
		if(i<=nu_t)
			return tmp[i].GetX();
		else
			return 0;
	}
	double Get_tmpY(int i)
	{
		if(i<=nu_t)
			return tmp[i].GetY();
		else
			return 0;
	}
	double Get_tmpZ(int i)
	{
		if(i<=nu_t)
			return tmp[i].GetZ();
		else
			return 0;
	}
	void Rotated(Vector ve1, Vector nor)//начальны йвектор скорости и вектор, к которому строитс€ перпендикул€р
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
			B = 1;
		if(nor.GetY() * C + nor.GetZ() * B == 0)
			C+=1;
		double _z = - (nor.GetX() + nor.GetY() * (A + D)) / (nor.GetY() * C + nor.GetZ() * B);
		double _y = (A + _z * C + D) / B; 
		double _x = 1;
		Vector normal = Vector(_x,_y,_z);

		if(normal.distanse() != 0)
			ve_ro = normal * ( velo > normal ) / normal.distanse();
	}
	void Test(Polyg * obj, bool motion)
	{

	}
};

class Camera: public BaseObject
{
private:
	double angle;
public:
	Camera();
	double GetAngleXOZ();
	void SetAngleXOZ(int ang);
	//void Turn(double ang);
	
};

class World
{
private:
	Plane * Plan;
	int k;
public: 
	World(DWORD t)
	{
		double _pi = 3.1415926;
		k = 2;
		Plan = new Plane [k];
		//double eq1[4]  ={-10,10,1,0};
		double eq1 [4];
		eq1[0] = E * cos ( t * (2 * _pi) / T);
		if(eq1[0]  < 0)
			eq1[0] = -eq1[0];

		eq1[1] = E * sin ( t * (2 * _pi) / T);
		if(eq1[1]  < 0)
			eq1[1] = -eq1[1];

		eq1[2]  = 1;
		eq1[3]  = 0;
		/*double eq1 [3][3] = 
		{	{0,-14,0},
			{1,-14,0.5},
			{1,14,0}};
		*/

		Plan[0] = Plane(eq1);
		//Plan[1] = Plane(eq2);
	}

	World()
	{
		k = 2;
		Plan = new Plane [k];
		double eq1[4]  ={-10,10,1,0};
		/*double eq1 [3][3] = 
		{	{0,-14,0},
			{1,-14,0.5},
			{1,14,0}};
		*/
		Plan[0] = Plane(eq1);
		//Plan[1] = Plane(eq2);
	}

	bool TestEqua(Camera * obj,Plane  Plan)
	{
		return ( obj->Position.GetX()*Plan.GetA() + obj->Position.GetY()*Plan.GetB() + obj->Position.GetZ()* Plan.GetC() + Plan.GetD() ) < 0; // изменить знак неравенства на <
	}
	void Test(Camera * obj,double resil)
	{
		for(int i=0;i<k;i++)
		{
			if(TestEqua(obj,Plan[i]))
			{
				obj->velo = Plan[i].GetMat() * obj->velo * resil;
			}
		}
	}

	bool TestEqua(Sphere * obj,Plane  Plan)
	{
		return ( obj->Position.GetX()*Plan.GetA() + obj->Position.GetY()*Plan.GetB() + obj->Position.GetZ()* Plan.GetC() + Plan.GetD() ) < 0; // изменить знак неравенства на <
	}
	void Test(Sphere * obj,double resil)
	{
		for(int i=0;i<k;i++)
		{
			if(TestEqua(obj,Plan[i]))
			{
				Vector velo = obj->velo;

				obj->velo = Plan[i].GetMat() * obj->velo * resil;

				obj->Rotated(velo,Plan[i].GetN());
			}
		}
	}

	bool TestEqua(Polyg * obj,Plane Plan)
	{
		bool test  = 0;
		for(int i=0;i<obj->GetN_t() && !test;i++)
		{
			if(  obj->Get_tmpX(i)* Plan.GetA() + obj->Get_tmpY(i)*Plan.GetB() + obj->Get_tmpZ(i)* Plan.GetC() + Plan.GetD()  < 0 )
				test = 1;
		}
		return test;
	}
	void Test(Polyg * obj,double resil)
	{
		for(int i=0;i<k;i++)
		{
			if(TestEqua(obj,Plan[i]))
			{
				Vector velo = obj->velo;
				obj->velo = Plan[i].GetMat() * obj->velo * resil;
				obj->Rotated(velo,Plan[i].GetN());
			}
		}
	}
};

class Fizika
{
private:
	double _g;
	World wor;
public:
	Fizika();
	//void Kick (double plane[4],Camera * obj,double k);
	void MoveObject(Camera * obj, double t);
	void MoveObject(Sphere * obj, double t);
	Sphere* TestMO (Sphere * obj, double t); 
};

#endif
