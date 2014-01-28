#include <Windows.h>
#include<cmath>

#ifndef __FIZIKA_H
#define __FIZIKA_H

// Физика
//Хе-Хе
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
	DWORD bornTime;
	double m;
	Vector velo;
	Vector accel;
	Vector F;
	BaseObject()
	{
		Position = Vector(0,0,0);
		velo = Vector(0,0,0);
		accel = Vector(0,0,0);
		F = Vector(0,0,0);
		m =0;
		bornTime = 0;
	}
};

class GeneralObject
{
private:
	BaseObject * BasObj;
	Plane * pla;
	int _pl;
	Vector ** tmp;
	int _tm;
public:
	GeneralObject()
	{
		*BasObj = BaseObject();
		*pla = Plane();
		**tmp = Vector();
		_pl = 0;
		_tm = 0;
	}
	void Obj_test ()
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

class Fizika
{
private:
	double _g;

public:
	Fizika();
	//void Kick (double plane[4],Camera * obj,double k);
	void MoveObject(Camera* obj, double t);
};

class World
{
private:
	Plane * Plan;
	int k;
public: 
	World()
	{
		k = 2;
		Plan = new Plane [k];
		double eq1[4]  ={-10,10,1,0};
		/*double eq1 [3][3] = 
		{	{0,-14,0},
			{1,-14,0.5},
			{1,14,0}};
		double eq2 [3][3] = 
		{	{0,-14,0},
			{-1,-14,0.5},
			{-1,-14,0}};*/
		//double eq1 [4] = {0.5,0.5,0,14};
		//double eq2 [4] = {-0.5,0.5,0,14};

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
};
#endif
