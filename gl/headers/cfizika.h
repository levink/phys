#include <Windows.h>
#include<cmath>

// ‘изика
// ’е-’е

#ifndef __FIZIKA_H
#define __FIZIKA_H

#define E 20
#define T 5
#define res 0.8
#define max8 100
#define min8 -100

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
	Vector(double v[3])
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
	
	double length()
	{
		return sqrt( x*x + y*y + z*z);
	}
	double length2()
	{
		return x*x + y*y + z*z;
	}

	Vector operator+(Vector& const right)
	{
		return Vector(x+right.GetX(), y+right.GetY(), z+right.GetZ());
	}
	Vector operator-(Vector& const right)
	{
		return Vector(x - right.GetX(), y - right.GetY(), z - right.GetZ());
	}
	Vector operator-()
	{
		return Vector(-x, -y, -z); 
	}
	Vector operator*(double scale)
	{
		return Vector(x * scale, y * scale, z * scale);
	}
	Vector operator/(double u)
	{
		return Vector(x,y,z)*(1/u);
	}
	
	double operator^(Vector& const right)
	{
		//scalar multiply
		return x * right.GetX() + y * right.GetY() + z * right.GetZ(); 
	}
	Vector operator*(Vector& const right)
	{
		//vector multiply
		return Vector(
			y * right.z - z * right.y,
			z * right.x - x * right.z,
			x * right.y - y * right.x);
	}
	Vector& operator= (Vector val)
	{
		x = val.GetX();
		y = val.GetY();
		z = val.GetZ();
		return *this;
	}
	
	bool operator<(double value)
	{	
		return value < 0 || this->length2() < value*value;
	}
	bool operator==(Vector& const right)
	{
		return x == right.GetX() && y == right.GetY() && z == right.GetZ();
	}
	bool operator!=(Vector& const right)
	{
		return x != right.GetX() || y != right.GetY() || z != right.GetZ();	
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

		double GetM(int a,int b)
		{
			return mat[a][b];
		}
		
		void SetM(double value,int i,int j)
		{
			mat[i][j] = value;
		}
		
		const double* Values()
		{
			return &(mat[0][0]);
		}

		Matrix Transpose()
		{
			double tr[3][3];
			for(int i=0;i<3;i++)
				for(int e=0;e<3;e++)
					tr[e][i] = mat[i][e];
			return Matrix(tr);
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
			double vec[3];
			double vx = vector.GetX();
			double vy = vector.GetY();
			double vz = vector.GetZ();
			return Vector(
				mat[0][0] * vx +  mat[0][1] * vy + mat[0][2] * vz,
				mat[1][0] * vx +  mat[1][1] * vy + mat[1][2] * vz,
				mat[2][0] * vx +  mat[2][1] * vy + mat[2][2] * vz);
		}

		Matrix operator* (Matrix& const right)
		{
			double _mat[3][3];
			const double* m = right.Values();

			/*for(int i=0;i<3;i++)
				for(int j=0;j<3;j++)
					_mat[i][j] = m1[i*3+0] * m2[0*3 + j] + m1[i*3+1] * m2[1*3 + j] + m1[i*3+2] * m2[2*3 + j];*/
			
			// more quickly
			_mat[0][0] = mat[0][0] * m[0*3 + 0] + mat[0][1] * m[1*3 + 0] + mat[0][2] * m[2*3 + 0];
			_mat[0][1] = mat[0][0] * m[0*3 + 1] + mat[0][1] * m[1*3 + 1] + mat[0][2] * m[2*3 + 1];
			_mat[0][2] = mat[0][0] * m[0*3 + 2] + mat[0][1] * m[1*3 + 2] + mat[0][2] * m[2*3 + 2];
			_mat[1][0] = mat[1][0] * m[0*3 + 0] + mat[1][1] * m[1*3 + 0] + mat[1][2] * m[2*3 + 0];
			_mat[1][1] = mat[1][0] * m[0*3 + 1] + mat[1][1] * m[1*3 + 1] + mat[1][2] * m[2*3 + 1];
			_mat[1][2] = mat[1][0] * m[0*3 + 2] + mat[1][1] * m[1*3 + 2] + mat[1][2] * m[2*3 + 2];
			_mat[2][0] = mat[2][0] * m[0*3 + 0] + mat[2][1] * m[1*3 + 0] + mat[2][2] * m[2*3 + 0];
			_mat[2][1] = mat[2][0] * m[0*3 + 1] + mat[2][1] * m[1*3 + 1] + mat[2][2] * m[2*3 + 1];
			_mat[2][2] = mat[2][0] * m[0*3 + 2] + mat[2][1] * m[1*3 + 2] + mat[2][2] * m[2*3 + 2];
			
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

		Matrix operator= (Matrix& const right)
		{
			//TODO: test this method
			const double *items = right.Values();
			for(int i=0;i<3;i++)
				for(int j=0;j<3;j++)
					mat[i][j] = items[i*3 + j];
			return *this;
		}

		Matrix Invert()
		{
			//Determinant calculating
			double d1 = mat[0][0] * ( mat[1][1] * mat[2][2] - mat[2][1] * mat[1][2]);
			double d2 = mat[0][1] * ( mat[1][0] * mat[2][2] - mat[2][0] * mat[1][2]);
			double d3 = mat[0][2] * ( mat[1][0] * mat[2][1] - mat[2][0] * mat[1][1]);
			double det = d1 - d2 + d3;
			if(det == 0) det = 1;
			else det = 1 / det; //(!)
			
			//Mat_alg_aff + Transposition + " scale on (1/det)" in one step
			double matA [3][3];
			matA[0][0] =  (mat[1][1] * mat[2][2] - mat[2][1] * mat[1][2]) * det;
			matA[1][0] = -(mat[1][0] * mat[2][2] - mat[2][0] * mat[1][2]) * det;
			matA[2][0] =  (mat[1][0] * mat[2][1] - mat[2][0] * mat[1][1]) * det;
			matA[0][1] = -(mat[0][1] * mat[2][2] - mat[2][1] * mat[0][2]) * det; 
			matA[1][1] =  (mat[0][0] * mat[2][2] - mat[2][0] * mat[0][2]) * det; 
			matA[2][1] = -(mat[0][0] * mat[2][1] - mat[2][0] * mat[0][1]) * det;
			matA[0][2] =  (mat[0][1] * mat[1][2] - mat[1][1] * mat[0][2]) * det;
			matA[1][2] = -(mat[0][0] * mat[1][2] - mat[1][0] * mat[0][2]) * det;
			matA[2][2] =  (mat[0][0] * mat[1][1] - mat[1][0] * mat[0][1]) * det;
			
			return Matrix(matA);
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
		invert = invert.Invert();

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
				equa[i] = 0.01;
		}

		double longg  =sqrt(equa[0] * equa[0] + equa[1] * equa[1] + equa[2] * equa[2]); 
		equa[0] = equa[0] / longg;
		equa[1] = equa[1] / longg;
		equa[2] = equa[2] / longg;
		//equa[3] = - equa[0] - equa[1] - equa[2];
		if(equa[0] == 0)
			equa[0] =1;

		double a[3];
		a[0] = equa[0];
		a[1] =  - ( pow(equa[0],2) + pow(equa[2],2) )  / equa[1]; //-equa[1];
		a[2] = equa[2];

		double b[3];
		// перпендикул€рные вектора, в том числе и нормаль
		b[0] =  - ( pow(a[1],2) + pow(a[2],2)) / a[0];//-a[0];
		b[1] = a[1];
		b[2] = a[2];

		for(int i=0;i<3;i++)
		{
			Mat.SetM(a[i],i,0);
			Mat.SetM(equa[i],i,1);
			Mat.SetM(b[i],i,2);
		}
		Matrix invert = Mat;
		invert = invert.Invert();

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

class BaseObject
{
public:
	Vector Position;
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

	//Sphere * TestMO (Sphere * obj, double t);

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

		if(normal.length() != 0)
			ve_ro = normal * ( velo ^ normal ) / normal.length();
	}

	void Test(Sphere * obj, bool motion)
	{
		if((Position - obj->Position).length() < (rad + obj->rad) * 1.01 || motion)
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


			if((velo ^ norm) > 0)
				velo = plan->GetMat() * ve1 /*velo*/ * res;
			else
				velo = ve1;
			if( (obj->velo ^ norm) < 0)
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

	void operator=(Sphere * count)
	{
		Position = count->Position;
		accel = count->accel;
		F = count->F;
		m = count->m;
		velo = count->velo;
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

		if(normal.length() != 0)
			ve_ro = normal * ( velo ^ normal ) / normal.length();
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

struct AllObject
{
private:
	Sphere * obj[100];
	int gen_test [100][100];
	int nom;
public:
	AllObject()
	{
		for(int i =0;i<100;i++)
		{
			*obj[i] = Sphere();
			for(int e =0;e<100;e++)
				gen_test [i][e] =0;

		}
		nom = 0;
	}
	void CreateObj(Vector Pos)
	{
		obj[nom]->Position = Pos;
		nom++;
	}
	Sphere * GetObj(int number)
	{
		return obj[number];
	}
	int GetN()
	{
		return nom++;
	}
	int GetGen_test(int i,int e)
	{
		return gen_test[i][e]; 
	}
	void SetGen_test(int count,int i,int e)
	{
		gen_test[i][e] = count; 
	}

};

class World
{
private:
	Plane * Plan;
	double * rese[6]; // 0 - Max_x, 1 - Min_x, 2 - Max_y, 3 - Min_y, 4 - Max_z, 5 - Min_z
	int k;
public: 
	
	/*World()
	{
		for(int i=0;i<6;i++)
		{
			rese[i] = NULL;
		}
		k=0;
		Plan = NULL;
	}*/
	World(/*bool test*/)
	{
		k = 2;
		Plan = new Plane [k];
		double eq1[4]  ={-10,10,0,5};
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
		rese[1][1] = 0;
		rese[1][2] = max8;
		rese[1][3] = -3;
		rese[1][4] = max8;
		rese[1][5] = min8;
		/*double eq1 [3][3] = 
		{	{0,-14,0},
			{1,-14,0.5},
			{1,14,0}};
		*/
		Plan[0] = Plane(eq1);
		Plan[1] = Plane(eq2);
	}
	World(double A,double B,double C,double D, double reserve[6])
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

	friend Plane*  GetPlane(World obj);

	int GetK()
	{
		return k;
	}

	bool TestEqua(Camera * obj,int i)
	{
		if(obj->Position.GetX() > rese[i][0] || obj->Position.GetX() < rese[i][1] || obj->Position.GetY() > rese[i][2] || obj->Position.GetY() < rese[i][3] || obj->Position.GetZ() > rese[i][4] || obj->Position.GetZ() < rese[i][5])
			return 0;
		else
			return ( obj->Position.GetX()*Plan[i].GetA() + obj->Position.GetY()*Plan[i].GetB() + obj->Position.GetZ()* Plan[i].GetC() + Plan[i].GetD() ) < 0; // изменить знак неравенства на <
	}
	void Test(Camera * obj,double resil)
	{
		for(int i=0;i<k;i++)
		{
			if(TestEqua(obj,i))
			{
				obj->velo = Plan[i].GetMat() * obj->velo * resil;
			}
		}
	}

	bool TestEqua(Sphere * obj,int i)
	{
		if(obj->Position.GetX() > rese[i][0] || obj->Position.GetX() < rese[i][1] || obj->Position.GetY() > rese[i][2] || obj->Position.GetY() < rese[i][3] || obj->Position.GetZ() > rese[i][4] || obj->Position.GetZ() < rese[i][5])
			return 0;
		else
		{
			return ( obj->Position.GetX()*Plan[i].GetA() + obj->Position.GetY()*Plan[i].GetB() + obj->Position.GetZ()* Plan[i].GetC() + Plan[i].GetD() ) < 0; 
		}
	}
	void Test(Sphere * obj,double resil)
	{
		for(int i=0;i<k;i++)
		{
			if(TestEqua(obj,i))
			{
				Vector velo = obj->velo;

				obj->velo = Plan[i].GetMat() * obj->velo * resil;
				if(Plan[i].GetA() == 0.01 && Plan[i].GetB() == 1 && Plan[i].GetC() == 0.01)
				{
					obj->velo.SetY(0);
				}

				obj->Rotated(velo,Plan[i].GetN());
			}
		}
	}

	bool TestEqua(Polyg * obj, int i)
	{
		bool test  = 0;
		for(int i=0;i<obj->GetN_t() && !test;i++)
		{
			if(obj->Get_tmpX(i) > rese[i][0] || obj->Get_tmpX(i) < rese[i][1] || obj->Get_tmpY(i) > rese[i][2] || obj->Get_tmpY(i) < rese[i][3] || obj->Get_tmpZ(i) > rese[i][4] || obj->Get_tmpZ(i) < rese[i][5])
				if(  obj->Get_tmpX(i)* Plan[i].GetA() + obj->Get_tmpY(i)*Plan[i].GetB() + obj->Get_tmpZ(i)* Plan[i].GetC() + Plan[i].GetD()  < 0 )
					test = 1;
		}
		return test;
	}
	void Test(Polyg * obj,double resil)
	{
		for(int i=0;i<k;i++)
		{
			if(TestEqua(obj,i))
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
	AllObject * AObj;
public:
	Fizika();
	//void Kick (double plane[4],Camera * obj,double k);
	friend World* GetWorld(Fizika obj);
	void MoveObject(Camera * obj, double t);
	void MoveObject(Sphere * obj, double t);
	void MoveObj(double t);
	AllObject* GetAObj ()
	{
		return AObj;
	} 
};

#endif
