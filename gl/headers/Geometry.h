#include<iostream> // УДАЛИТЬ!!!!!
#include <vector>

#ifndef __GEOMETRY_H
#define __GEOMETRY_H

using namespace std;

class Vector
{
private:
	double x;
	double y;
	double z;
public:
	Vector();
	Vector(double _x, double _y, double _z);
	Vector(double v[3]);

	double GetX();
	double GetY();
	double GetZ();
	void SetX(double newx);
	void SetY(double newy);
	void SetZ(double newz);
	
	double length();
	double length2();

	Vector operator+(Vector& const right);
	Vector operator-(Vector& const right);
	Vector operator-();
	Vector operator*(double scale);
	Vector operator/(double u);
	Vector operator/(Vector& const right);
	
	double operator&(Vector& const right);
	double operator^(Vector& const right);
	double operator%(Vector& const right);
	Vector operator*(Vector& const right);
	Vector operator>(Vector& const right);
	Vector& operator= (Vector val);

	bool operator<(double value);
	bool operator==(Vector& const right);
	bool operator!=(Vector& const right);
};
Vector sqrt_ve(Vector& const value);
Vector Vector_norm(Vector value);
int rotateXZ(Vector, Vector, Vector);
class Qaternion
{
private:
	Vector u;
	double a;
public:
	Qaternion();
	Qaternion(Vector count,double co);
	Vector Getu()
	{
		return u;
	}
	double Geta()
	{
		return a;
	}
	Qaternion operator*(Qaternion & right);
	Vector rotate(Vector count)
	{
		Vector fin = Vector(); 
		double inv = 1/(a * a + pow(u.length(),2));
		Qaternion _qa = Qaternion(-u*inv,a*inv);
		return (*this * (Qaternion(count,0)) * (_qa)).Getu(); 
	}
};
class Matrix
{
	private:
		double mat [3][3];
	public:
		Matrix();

		Matrix(double count[3][3]);

		double GetM(int a,int b);
		
		void SetM(double value,int i,int j);
		
		const double* Values();

		Matrix Transpose();

		Matrix operator* (double t);

		Vector operator* (Vector vector);

		Matrix operator* (Matrix& const right);

		Matrix operator/ (double t);

		Matrix operator= (Matrix& const right);

		Matrix Invert();
};

class Line 
{
public:
	Vector vec;
	Vector tmp;
	double limit[6]; // Max X -> Min X -> Max Y -> Min Y -> Max Z -> Min Z

	Line();
	Line(Vector v, Vector t);
	Vector projection(Vector t);
	Vector lineXYZ(double x);
};

class Plane
{
private:
	double equa [4]; // Нормаль к плоскости.
	//Matrix Mat; // Матрица перевода в СК, связанную с плоскостью.
	//Vector * vec; // Направляющие вектора прямых, ограничивающих контур. Точки, через которые проходят прямые - это tmp под номером = номеру вектора.
	double tes [6]; // Ограничивающий куб. MaxX->MinX->MaxY->MinY->MaxZ->MinZ
public:
	vector <int> tr[3]; // Треугольники. Содержит номера вершин, принадлежащих треугольникам. Необходимо для проверки столкновения и правильной отрисовки плоскостей.
	int tr_num; // количество треугольников, нужно для того, чтобы понять, было ли столкновение. 
	vector<Vector> tmp; // Точки, определяющие ВЫПУКЛЫЙ контур.
	int num;
	Line * li;
	// Проекции точек, определяющих ВЫПУКЛЫЙ контур.
	int li_num;

	Plane();
	Plane(double eq [4]);
	Plane(double Ctmp[3][3]);
	Plane(Vector x1,Vector x2, Vector x3);

	double* Calculeqa(Vector O,Vector A, Vector B);
	void PlaneSetEquation(double eq[4]);

	Vector project(Vector* point);
	void SetPoints(Vector * t, int l);
	void triangulation();
	bool cubeinspection(Vector tmp, double rad)
	{
		bool a = tmp.GetX() < tes[0]+rad && tmp.GetX() > tes[1]-rad;
		bool b = tmp.GetY() < tes[2]+rad && tmp.GetY() > tes[3]-rad;
		bool c = tmp.GetZ() < tes[4]+rad && tmp.GetZ() > tes[5]-rad;
		return ( a && b & c);
	}

	//Matrix GetMat();
	Vector GetN();
	double GetA();
	double GetB();
	double GetC();
	double GetD();
};

#endif