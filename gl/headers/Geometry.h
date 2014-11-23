#include<iostream> // УДАЛИТЬ!!!!!
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
	
	double operator&(Vector& const right);
	double operator^(Vector& const right);
	Vector operator*(Vector& const right);
	Vector operator>(Vector& const right);
	Vector& operator= (Vector val);

	bool operator<(double value);
	bool operator==(Vector& const right);
	bool operator!=(Vector& const right);
};
Vector sqrt_ve(Vector& const value);
Vector Vector_norm(Vector value);

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
private:
	Vector vec;
	Vector tmp;
public:
	Line();
	Line(Vector v, Vector t);
	Vector projection(Vector t);
	Vector lineXYZ(double x);
};

class Plane
{
private:
	double equa [4]; // Нормаль к плоскости.
	Matrix Mat; // Матрица перевода в СК, связанную с плоскостью.
	Vector * tmp; // Точки, определяющие ВЫПУКЛЫЙ контур.
	int num; // Количество вершин.
	Vector * vec; // Направляющие вектора прямых, ограничивающих контур. Точки, через которые проходят прямые - это tmp под номером = номеру вектора.
	int li_num; // количество прямых
	int *  tr[3]; // Треугольники. Содержит номера вершин, принадлежащих треугольникам. Необходимо для проверки столкновения и правильной отрисовки плоскостей.
	int tr_num;
	double tes [6]; // Ограничивающий куб.
public:
	Plane();
	void PlaneSetEquation(double eq[4]);
	Matrix GetBathis ();
	Plane(double Ctmp[3][3]);

	Plane(Vector x1,Vector x2, Vector x3);

	Plane(double eq [4]);
	Matrix Plane::GetInvertMat();

	void st(double * t[3]);
	void triangulation();

	bool test(Vector pos)
	{
		if(pos.GetX() < tes[0] || pos.GetX() > tes[1] || pos.GetX() < tes[2]  || pos.GetX() > tes[3] || pos.GetX() < tes[4]|| pos.GetX() > tes[5])
		{
			double x = (pos.GetX() * (equa[1] * equa[1] + equa[2] * equa[2]) - equa[0] * (equa[1] * pos.GetY() + pos.GetZ() * equa[2] + equa[3])) /  ( equa[0] * equa[0] + equa[1] * equa[1] + equa[2] * equa[2]);
			double y = (equa[1] *  (x - pos.GetX() ) ) / (equa[0]) + pos.GetY();
			double z = (equa[2] *  (x - pos.GetX() ) ) / (equa[0]) + pos.GetZ();
			Matrix ma = GetInvertMat();
			Vector p = ma * Vector(x,y,z);
		}
	}		

	Matrix GetMat();
	Vector GetN();
	double GetA();
	double GetB();
	double GetC();
	double GetD();
};

#endif