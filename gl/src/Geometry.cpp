#include<cmath>
#include"../headers/Objects.h"

//Vector::
	Vector::Vector()
	{
		x=0;
		y=0;
		z=0;
	}
	Vector::Vector(double _x, double _y, double _z)
	{
		x=_x;
		y=_y;
		z=_z;
	}
	Vector::Vector(double v[3])
	{
		x=v[0];
		y=v[1];
		z=v[2];
	}

	double Vector::GetX()
	{
		return x;
	}
	double Vector::GetY()
	{
		return y;
	}
	double Vector::GetZ()
	{
		return z;
	}
	void Vector::SetX(double newx)
	{
		x=newx;
	}
	void Vector::SetY(double newy)
	{
		y=newy;
	}
	void Vector::SetZ(double newz)
	{
		z=newz;
	}
	
	double Vector::length()
	{
		return sqrt( x*x + y*y + z*z);
	}
	double Vector::length2()
	{
		return x*x + y*y + z*z;
	}

	Vector Vector::operator+(Vector& const right)
	{
		return Vector(x+right.GetX(), y+right.GetY(), z+right.GetZ());
	}
	Vector Vector::operator-(Vector& const right)
	{
		return Vector(x - right.GetX(), y - right.GetY(), z - right.GetZ());
	}
	Vector Vector::operator-()
	{
		return Vector(-x, -y, -z); 
	}
	Vector Vector::operator*(double scale)
	{
		return Vector(x * scale, y * scale, z * scale);
	}
	Vector Vector::operator/(double u)
	{
		return Vector(x,y,z)*(1/u);
	}
	
	double Vector::operator&(Vector& const right)
	{
		//scalar multiply
		return x * right.GetX() + y * right.GetY() + z * right.GetZ(); 
	}
	double Vector::operator^(Vector& const right)
	{
		return( (x * right.GetX() + y * right.GetY() + z * right.GetZ() ) / (sqrt( (x * x + y * y + z * z) * right.length2())) );
	}
	Vector Vector::operator*(Vector& const right)
	{
		//vector multiply
		return Vector(
			y * right.z - z * right.y,
			z * right.x - x * right.z,
			x * right.y - y * right.x);
	}
	Vector sqrt_ve(Vector& const value)
	{
		return Vector(	
			sqrt(value.GetX()), 
			sqrt(value.GetY()), 
			sqrt(value.GetZ()) );
	}
	Vector Vector::operator>(Vector& const right)
	{
		return Vector(
			x * right.x,
			y * right.y,
			z * right.z);
	}
	Vector& Vector::operator= (Vector val)
	{
		x = val.GetX();
		y = val.GetY();
		z = val.GetZ();
		return *this;
	}

	bool Vector::operator<(double value)
	{	
		return value <= 0 || this->length2() < value*value;
	}
	bool Vector::operator==(Vector& const right)
	{
		return x == right.GetX() && y == right.GetY() && z == right.GetZ();
	}
	bool Vector::operator!=(Vector& const right)
	{
		return x != right.GetX() || y != right.GetY() || z != right.GetZ();	
	}
	Vector Vector_norm(Vector value)
	{
		double longg  = sqrt(value.GetX()* value.GetX() + value.GetY() * value.GetY() + value.GetZ() * value.GetZ()); 
		return Vector(
			value.GetX() / longg,
			value.GetY() / longg,
			value.GetZ() / longg );
	}
//Matrix::
		Matrix::Matrix()
		{
			for(int i=0;i<3;i++)
				for(int e=0;e<3;e++)
					mat[i][e] = 0;
		}

		Matrix::Matrix(double count[3][3])
		{
			for(int i=0;i<3;i++)
				for(int e=0;e<3;e++)
					mat[i][e] = count[i][e];
		}

		double Matrix::GetM(int a,int b)
		{
			return mat[a][b];
		}
		
		void Matrix::SetM(double value,int i,int j)
		{
			mat[i][j] = value;
		}
		
		const double* Matrix::Values()
		{
			return &(mat[0][0]);
		}

		Matrix Matrix::Transpose()
		{
			double tr[3][3];
			for(int i=0;i<3;i++)
				for(int e=0;e<3;e++)
					tr[e][i] = mat[i][e];
			return Matrix(tr);
		}

		Matrix Matrix::operator* (double t)
		{
			double _mat[3][3];
			for(int i=0;i<3;i++)
				for(int e=0;e<3;e++)
					_mat[i][e] = mat[i][e] * t;
			return Matrix(_mat);
		}

		Vector Matrix::operator* (Vector vector)
		{
			double vx = vector.GetX();
			double vy = vector.GetY();
			double vz = vector.GetZ();
			return Vector(
				(mat[0][0] * vx +  mat[0][1] * vy + mat[0][2] * vz),
				(mat[1][0] * vx +  mat[1][1] * vy + mat[1][2] * vz),
				(mat[2][0] * vx +  mat[2][1] * vy + mat[2][2] * vz));
		}

		Matrix Matrix::operator* (Matrix& const right)
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

		Matrix Matrix::operator/ (double t)
		{
			double _mat[3][3];
			for(int i=0;i<3;i++)
				for(int e=0;e<3;e++)
					_mat[i][e] = mat[i][e] / t;
			return Matrix(mat);
		}

		Matrix Matrix::operator= (Matrix& const right)
		{
			//TODO: test this method
			const double *items = right.Values();
			for(int i=0;i<3;i++)
				for(int j=0;j<3;j++)
					mat[i][j] = items[i*3 + j];
			return *this;
		}

		Matrix Matrix::Invert()
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
//Plane
	Plane::Plane()
	{
		equa[0] = 0;
		equa[1] = 0;
		equa[2] = 0;
		equa[3] = 0; 
		tmp[0] = NULL;
		tmp[1] = NULL;
		tmp[2] = NULL;
		num = 0;
		Mat = Matrix();
		tr[0] = NULL;
		tr[1] = NULL;
		tr[2] = NULL;
		tes[0] = 0;
		tes[1] = 0;
		tes[2] = 0;
		tes[3] = 0;
		tes[4] = 0;
		tes[5] = 0;
	}

	void Plane::PlaneSetEquation(double eq[4])
	{
		equa[0] = eq[0];
		equa[1] = eq[1];
		equa[2] = eq[2];
		equa[3] = eq[3];
	}

	Matrix Plane::GetBathis ()
	{
		double a [3]; // x0
		double b [3]; // x1
		double c [3]; // x2
		double f [3];
		double e [3] = {0,0,0};

		if(equa[2] != 0)
		{
			a[0] = 1;
			a[1] = 1;
			a[2] = - ((equa[0] * a[0] + equa[1] * a[1] + equa[3])/equa[2]);
			b[0] = 2;
			b[1] = 2;
			b[2] = - ((equa[0] * b[0] + equa[1] * b[1] + equa[3])/equa[2]);
			c[0] = 3;
			e[0] = c[0] - a[0];

			f[0] = b[0] - a[0];
			f[1] = b[1] - a[1];
			f[2] = b[2] - a[2];

			e[1] = (equa[0] * (e[0] + a[0]) + equa[1] * a[1] - ((equa[2] * e[0] * f[0])/f[2]) + equa[2] * a[2]) / (((equa[2] * f[1])/f[2]) - equa[1]);
			e[2] = -((e[0] * f[0] + e[1] * f[1])/f[2]);
		}

		if(equa[2] == 0 && equa[0] != 0 &&  equa[1] != 0)
		{
			a[1] = 1;
			a[2] = 1;
			a[0] = - ((equa[1] * a[1] + equa[3])/equa[0]);
			b[1] = 2;
			b[2] = 2;
			b[0] = - ((equa[1] * b[1] + equa[3])/equa[0]);
			c[0] = 3;
			e[0] = c[0] - a[0];

			f[0] = b[0] - a[0];
			f[1] = b[1] - a[1];
			f[2] = b[2] - a[2];

			e[1] = -((equa[0] * (e[0] + a[0]) + equa[1] * a[1] + equa[3])/equa[1]);
			e[2] = -((e[0] * f[0] + e[1] * f[1])/f[2]);
		}
		if(equa[2] == 0 && equa[0] == 0)
		{
			a[0] = 1;
			a[2] = 1;
			a[1] = - (equa[3]/equa[1]);
			b[0] = 2;
			b[2] = 2;
			b[1] = - (equa[3]/equa[1]);
			c[0] = 3;
			e[0] = c[0] - a[0];

			f[0] = b[0] - a[0];
			f[1] = b[1] - a[1];
			f[2] = b[2] - a[2];

			e[1] = -((equa[1]  * a[1] + equa[3]) / equa[1]);
			e[2] = -((e[0] * f[0])/f[2]);
		}
		if(equa[1] == 0 && equa[2] == 0)
		{
			a[1] = 1;
			a[2] = 1;
			a[0] = - (equa[3]/equa[0]);
			b[1] = 2;
			b[2] = 2;
			b[0] = - (equa[3]/equa[0]);
			c[1] = 3;
			c[0] = - (equa[3]/equa[0]);
			e[1] = c[1] - a[1];

			f[0] = b[0] - a[0];
			f[1] = b[1] - a[1];
			f[2] = b[2] - a[2];

			e[0] = -(equa[3] / equa[0]);
			e[2] = (( -c[0] * f[0] + a[0] * f[0] - c[1] * f[1] + a[1] * f[1])/f[2]) + a[2];
		}
		double  x[3][3] = { 
					{f[0],f[1],f[2]},
					{equa[0],equa[1],equa[2]},
					{e[0],e[1],e[2]} };

		Vector f1 = Vector(f);
		Vector e1 = Vector(e);
		double ang = e1 & f1;
		cout << ang << endl;
		if(ang > 0.000001 || ang < -0.000001)
		{
			cout << "ERROR\n";
		}

		return Matrix(x);
	}
	
	Plane::Plane(double Ctmp[3][3])
	{
		equa[0] = Ctmp[1][0]*(Ctmp[2][1] - Ctmp[2][2]) + Ctmp[1][1]*(Ctmp[2][2] - Ctmp[2][0]) + Ctmp[1][2]*(Ctmp[2][0] - Ctmp[2][1]);
		equa[1] = Ctmp[2][0]*(Ctmp[0][1] - Ctmp[0][2]) + Ctmp[2][1]*(Ctmp[0][2] - Ctmp[0][0]) + Ctmp[2][2]*(Ctmp[0][0] - Ctmp[0][1]);
		equa[2] = Ctmp[0][0]*(Ctmp[1][1] - Ctmp[1][2]) + Ctmp[0][1]*(Ctmp[1][2] - Ctmp[1][0]) + Ctmp[0][2]*(Ctmp[1][0] - Ctmp[1][1]);

		double longg  = sqrt(equa[0] * equa[0] + equa[0] * equa[0] + equa[0] * equa[0]); 
		equa[0] = equa[0] / longg;
		equa[1] = equa[1] / longg;
		equa[2] = equa[2] / longg;

		Mat = GetBathis();
		Matrix invert = Mat.Invert();

		/*double redoun[3][3] = 
		{	{1,0,0},
			{0,-1,0},
			{0,0,1}, };
		Matrix rebound = Matrix(redoun);*/

		Mat = invert /** rebound * Mat*/;
	}

	Plane::Plane(Vector x1,Vector x2, Vector x3)
	{
		equa[0] = x2.GetX() * (x3.GetY() - x3.GetZ()) + x2.GetY() * (x3.GetZ() - x3.GetX()) + x2.GetZ() * (x3.GetX() - x3.GetY());
		equa[1] = x3.GetX() * (x1.GetY() - x1.GetZ()) + x3.GetY() * (x1.GetZ() - x1.GetX()) + x3.GetZ() * (x1.GetX() - x1.GetY());
		equa[2] = x1.GetX() * (x2.GetY() - x2.GetZ()) + x1.GetY() * (x2.GetZ() - x2.GetX()) + x1.GetZ() * (x2.GetX() - x2.GetY());

		double longg  = sqrt(equa[0] * equa[0] + equa[0] * equa[0] + equa[0] * equa[0]); 
		equa[0] = equa[0] / longg;
		equa[1] = equa[1] / longg;
		equa[2] = equa[2] / longg;

		Mat = GetBathis();
		Matrix invert = Mat.Invert();

		/*double redoun[3][3] = 
		{	{1,0,0},
			{0,-1,0},
			{0,0,1}, };
		Matrix rebound = Matrix(redoun);*/

		Mat = invert /** rebound * Mat*/;
	}

	Plane::Plane(double eq [4])
	{
		for(int i=0;i<4;i++)
		{
			equa[i] = eq[i];
		}
		double length = sqrt(eq[0] * eq[0] + eq[1] * eq[1] + eq[2] * eq[2]); 

		equa[0] = equa[0] / length;
		equa[1] = equa[1] / length;
		equa[2] = equa[2] / length;
		equa[3] = equa[3] / length;

		Mat = GetBathis();
		Matrix invert = Mat.Invert();

		/*double redoun[3][3] = 
		{	{1,0,0},
			{0,-1,0},
			{0,0,1}, };
		Matrix rebound = Matrix(redoun);*/

		Mat = invert /** rebound * Mat*/;
	}

	Matrix Plane::GetInvertMat()                            
	{
		Matrix Matr  = GetBathis();
		Matr = Matr.Invert();
		/*double e[3][3] = {
			{1,0,0},
			{0,-1,0},
			{0,0,1} };*/
		return  /*Matrix(e) **/ Matr;
	}

	Matrix Plane::GetMat()
	{
		return Mat;
	}
	Vector Plane::GetN()
	{
		return Vector(equa[0],equa[1],equa[2]);
	}
	double Plane::GetA()
	{
		return equa[0];
	}
	double Plane::GetB()
	{
		return equa[1];
	}
	double Plane::GetC()
	{
		return equa[2];
	}
	double Plane::GetD()
	{
		return equa[3];
	}
	void Plane::st(double * t[3])
	{
		Vector * cop;
		cop = new Vector[num];
		for(int i =0;i<num;i++)
		{
			cop[i] = tmp[i];
			
		}
		delete tmp;
		tmp = new Vector[num+1];
		for(int i =0;i<num;i++)
		{
			tmp[i] = cop[i];
		}
		delete cop;
	}
	void Plane::triangulation() // триангуляция !!!!!!!работает только для четырёхугольников! + определение ограничивающего куба + определение контура
	{
		Vector * t_p = new Vector[num];

		/*for(int i = 0;i<num;i++)
		{
			t_p = GetInvertMat() 
		}*/

		tr[0] = new int[2];
		tr[1] = new int[2];
		tr[2] = new int[2];
		tr[0][0] = 0;
		tr[1][0] = 1;
		tr[2][0] = 2;
		tr[0][1] = 0;
		tr[1][1] = 2;
		tr[2][1] = 3;

		vec = new Vector[num];
		vec[0] = Vector(tmp[1].GetX() - tmp[0].GetX(),tmp[1].GetY() - tmp[0].GetY(),tmp[1].GetZ() - tmp[0].GetZ());
		vec[1] = Vector(tmp[2].GetX() - tmp[1].GetX(),tmp[2].GetY() - tmp[1].GetY(),tmp[2].GetZ() - tmp[1].GetZ());
		vec[2] = Vector(tmp[3].GetX() - tmp[2].GetX(),tmp[3].GetY() - tmp[2].GetY(),tmp[3].GetZ() - tmp[2].GetZ());
		vec[3] = Vector(tmp[0].GetX() - tmp[3].GetX(),tmp[0].GetY() - tmp[3].GetY(),tmp[0].GetZ() - tmp[3].GetZ());

		Vector * ve = new Vector[num];
		tmp_p = new Vector[num];
		for(int i = 0;i<num;i++)
		{
			ve[i] = Mat * vec[i];
			tmp_p[i] = Mat * tmp[i];
		}
		int n = 0;
		Vector testing;
		for(int i = 0;i<num;i++)
		{
			n = i + 2;
			if(n > num)
			{
				n  = n - (num+1);
			}
			testing = Vector(tmp_p[n].GetX() - tmp_p[i].GetX(),tmp_p[n].GetY() - tmp_p[i].GetY(), 0);

			if(ve[i].GetY() == 0)
			{
				nor[i] = Vector(0,1,0);
				if((nor[i] ^ testing )< 0) // Возможно, надо оптимизировать поиск значения угла
				{
					nor[i] = Vector(0,-1,0);
				}
			}
			else
			{
				nor[i] = Vector(1,-(ve[i].GetX()/ve[i].GetY()),0);
				if((nor[i] ^ testing) < 0) // Возможно, надо оптимизировать поиск значения угла
				{
					nor[i] = Vector(-1,-(ve[i].GetX()/ve[i].GetY()),0);
				}
			}

		}

		double max = tmp[num].GetX();
		for(int i = 0;i<num;i++)
		{
			if(tmp[i].GetX() < max)
			{
				max = tmp[i].GetX();
			}
		}
		tes[0] = max - 2;
		max = tmp[num].GetX();
		for(int i = 0;i<num;i++)
		{
			if(tmp[i].GetX() > max)
			{
				max = tmp[i].GetX();
			}
		}
		tes[1] = max + 2;
		max = tmp[num].GetY();
		for(int i = 0;i<num;i++)
		{
			if(tmp[i].GetY() < max)
			{
				max = tmp[i].GetY();
			}
		}
		tes[2] = max - 2;
		max = tmp[num].GetY();
		for(int i = 0;i<num;i++)
		{
			if(tmp[i].GetY() > max)
			{
				max = tmp[i].GetY();
			}
		}
		tes[3] = max + 2;
		max = tmp[num].GetY();
		for(int i = 0;i<num;i++)
		{
			if(tmp[i].GetZ() < max)
			{
				max = tmp[i].GetZ();
			}
		}
		tes[4] = max - 2;
		max = tmp[num].GetZ();
		for(int i = 0;i<num;i++)
		{
			if(tmp[i].GetZ() > max)
			{
				max = tmp[i].GetZ();
			}
		}
		tes[5] = max + 2;
	}

	Line::Line ()
	{
		vec = Vector();
		tmp = Vector();
	}
	Line::Line(Vector v, Vector t)
	{
		vec = v;
		tmp = t;
	}
	Vector Line::projection(Vector t)
	{
		double p[3] = {vec.GetX(),vec.GetY(),vec.GetZ()};
		double _p1 = 1/p[1];
		double D = - vec & t;
		double A = (p[0] * p[0] + p[2] * p[2] ) * _p1;
		double y = (t.GetY() * A - t.GetX() * p[0] - t.GetZ() * p[2] - D) / ( A + p[1]);
		double x = (y - t.GetY()) * p[0] * _p1 + t.GetX();
		double z = (y - t.GetY()) * p[2] * _p1 + t.GetZ();
		return Vector(x,y,z);
	}
	Vector Line::lineXYZ(double x)
	{
		Vector t = Vector(x,vec.GetY() * (x - tmp.GetX())/vec.GetX() + tmp.GetY(), vec.GetZ() * (x - tmp.GetX())/vec.GetX() + tmp.GetZ());
		return t ;
	}