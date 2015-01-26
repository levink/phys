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
	Line& operator=(Line li)
	{
		vec = li.vec;
		tmp = li.tmp;
		limit[0] = li.limit[0];
		limit[1] = li.limit[1];
		limit[2] = li.limit[2];
		limit[3] = li.limit[3];
		limit[4] = li.limit[4];
		limit[5] = li.limit[5];
	}
};

class Plane
{
public:
	double normal[4]; // Нормаль к плоскости.
	Matrix Mat; // Матрица перевода в СК, связанную с плоскостью.
	double tes [6]; // Ограничивающий куб. MaxX->MinX->MaxY->MinY->MaxZ->MinZ
	vector<int> tr[3]; // Треугольники. Содержит номера вершин, принадлежащих треугольникам. Необходимо для проверки столкновения и правильной отрисовки плоскостей.
	int tr_num;
	int val;
	vector<Vector> tmp;
	vector<Line> li;
	vector<Vector> norm[3];

	Plane();
	Plane(double normal[4]);

	Vector project(Vector* point);
	void SetPoints(vector<Vector> points);
	void triangulation();
	bool cubeinspection(Vector tmp)
	{
		bool a = tmp.GetX() < tes[0] && tmp.GetX() > tes[1];
		bool b = tmp.GetY() < tes[2] && tmp.GetY() > tes[3];
		bool c = tmp.GetZ() < tes[4] && tmp.GetZ() > tes[5];
		return ( a && b & c);
	}
	
	Matrix GetMat();
	Vector GetN();
	double GetA();
	double GetB();
	double GetC();
	double GetD();
	
	Plane& Plane::operator=(const Plane item)
	{
		throw exception("Not implemented");
		return *this;
	}
};

//class Plane
//{
//private:
//	double normal[4]; // Нормаль к плоскости.
//	Matrix Mat; // Матрица перевода в СК, связанную с плоскостью.
//	double tes [6]; // Ограничивающий куб. MaxX->MinX->MaxY->MinY->MaxZ->MinZ
//public:
//	vector<Vector> tmp; // Точки, определяющие ВЫПУКЛЫЙ контур.
//	
//	vector<Line> li;
//	vector<Vector> nor; // Нормали к прямым, ограничивающим контур. В СК, связанной с плоскостью.
//	
//	
//	Plane();
//	Plane(double normal[4]);
//	Plane(double mat[3][3]);
//	Plane(Vector x1, Vector x2, Vector x3);
//
//
//	void PlaneSetEquation(double eq[4]);
//	
//	Matrix GetBathis ();
//	Matrix GetInvertMat();
//
//	Vector project(Vector* point);
//	void SetPoints(vector<Vector> points);
//	void triangulation();
//	bool cubeinspection(Vector tmp)
//	{
//		bool a = tmp.GetX() < tes[0] && tmp.GetX() > tes[1];
//		bool b = tmp.GetY() < tes[2] && tmp.GetY() > tes[3];
//		bool c = tmp.GetZ() < tes[4] && tmp.GetZ() > tes[5];
//		return ( a && b & c);
//	}
//
//	Matrix GetMat();
//	Vector GetN();
//	double GetA();
//	double GetB();
//	double GetC();
//	double GetD();
//	
//	Plane& Plane::operator=(const Plane item)
//	{
//		throw exception("Not implemented");
//		return *this;
//	}
//};

#endif