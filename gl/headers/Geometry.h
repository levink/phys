
#ifndef __GEOMETRY_H
#define __GEOMETRY_H
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
	Vector sqrt_ve()
	{
		
		x = sqrt(x);
		y = sqrt(y);
		z = sqrt(z);
		return Vector(x,y,z);
	}
	Vector operator>(Vector& const right)
	{
		return Vector(
			x * right.x,
			y * right.y,
			z * right.z);
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
		return value <= 0 || this->length2() < value*value;
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
				equa[i] = 0.00001;
		}

		double longg  =sqrt(equa[0] * equa[0] + equa[1] * equa[1] + equa[2] * equa[2]); 
		equa[0] = equa[0] / longg;
		equa[1] = equa[1] / longg;
		equa[2] = equa[2] / longg;
		//equa[3] = - equa[0] - equa[1] - equa[2];
		if(equa[0] == 0)
			equa[0] = 0.00001;

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
#endif