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
		normal[0] = 0;
		normal[1] = 0;
		normal[2] = 0;
		normal[3] = 0; 
		
		Mat = Matrix();
	
		tes[0] = 0;
		tes[1] = 0;
		tes[2] = 0;
		tes[3] = 0;
		tes[4] = 0;
		tes[5] = 0;
	}

	Plane::Plane(double eq[4])
	{
		Mat = Matrix();
		tes[0] = 0;
		tes[1] = 0;
		tes[2] = 0;
		tes[3] = 0;
		tes[4] = 0;
		tes[5] = 0;
		normal[0] = eq[0];
		normal[1] = eq[1];
		normal[2] = eq[2];
		normal[3] = eq[3];
	}

	//Matrix Plane::GetBathis ()
	//{
	//	double a [3]; // x0
	//	double b [3]; // x1
	//	double c [3]; // x2
	//	double f [3];
	//	double e [3] = {0,0,0};

	//	if(normal[2] != 0)
	//	{
	//		a[0] = 1;
	//		a[1] = 1;
	//		a[2] = - ((normal [0] * a[0] + normal [1] * a[1] + normal [3])/normal [2]);
	//		b[0] = 2;
	//		b[1] = 2;
	//		b[2] = - ((normal [0] * b[0] + normal [1] * b[1] + normal [3])/normal [2]);
	//		c[0] = 3;
	//		e[0] = c[0] - a[0];

	//		f[0] = b[0] - a[0];
	//		f[1] = b[1] - a[1];
	//		f[2] = b[2] - a[2];

	//		e[1] = (normal [0] * (e[0] + a[0]) + normal [1] * a[1] - ((normal [2] * e[0] * f[0])/f[2]) + normal [2] * a[2]) / (((normal [2] * f[1])/f[2]) - normal [1]);
	//		e[2] = -((e[0] * f[0] + e[1] * f[1])/f[2]);
	//	}

	//	if(normal [2] == 0 && normal [0] != 0 &&  normal [1] != 0)
	//	{
	//		a[1] = 1;
	//		a[2] = 1;
	//		a[0] = - ((normal [1] * a[1] + normal [3])/normal [0]);
	//		b[1] = 2;
	//		b[2] = 2;
	//		b[0] = - ((normal [1] * b[1] + normal [3])/normal [0]);
	//		c[0] = 3;
	//		e[0] = c[0] - a[0];

	//		f[0] = b[0] - a[0];
	//		f[1] = b[1] - a[1];
	//		f[2] = b[2] - a[2];

	//		e[1] = -((normal [0] * (e[0] + a[0]) + normal [1] * a[1] + normal [3])/normal [1]);
	//		e[2] = -((e[0] * f[0] + e[1] * f[1])/f[2]);
	//	}
	//	if(normal [2] == 0 && normal [0] == 0)
	//	{
	//		a[0] = 1;
	//		a[2] = 1;
	//		a[1] = - (normal [3]/normal [1]);
	//		b[0] = 2;
	//		b[2] = 2;
	//		b[1] = - (normal [3]/normal [1]);
	//		c[0] = 3;
	//		e[0] = c[0] - a[0];

	//		f[0] = b[0] - a[0];
	//		f[1] = b[1] - a[1];
	//		f[2] = b[2] - a[2];

	//		e[1] = -((normal [1]  * a[1] + normal [3]) / normal [1]);
	//		e[2] = -((e[0] * f[0])/f[2]);
	//	}
	//	if(normal [1] == 0 && normal [2] == 0)
	//	{
	//		a[1] = 1;
	//		a[2] = 1;
	//		a[0] = - (normal [3]/normal [0]);
	//		b[1] = 2;
	//		b[2] = 2;
	//		b[0] = - (normal [3]/normal [0]);
	//		c[1] = 3;
	//		c[0] = - (normal [3]/normal [0]);
	//		e[1] = c[1] - a[1];

	//		f[0] = b[0] - a[0];
	//		f[1] = b[1] - a[1];
	//		f[2] = b[2] - a[2];

	//		e[0] = -(normal [3] / normal [0]);
	//		e[2] = (( -c[0] * f[0] + a[0] * f[0] - c[1] * f[1] + a[1] * f[1])/f[2]) + a[2];
	//	}
	//	double  x[3][3] = { 
	//				{f[0],f[1],f[2]},
	//				{normal [0],normal [1],normal [2]},
	//				{e[0],e[1],e[2]} };

	//	Vector f1 = Vector(f);
	//	Vector e1 = Vector(e);
	//	double ang = e1 & f1;
	//	cout << ang << endl;
	//	if(ang > 0.000001 || ang < -0.000001)
	//	{
	//		cout << "ERROR\n";
	//	}

	//	return Matrix(x);
	//}
	//
	//Plane::Plane(double Ctmp[3][3])
	//{
	//	normal [0] = Ctmp[1][0]*(Ctmp[2][1] - Ctmp[2][2]) + Ctmp[1][1]*(Ctmp[2][2] - Ctmp[2][0]) + Ctmp[1][2]*(Ctmp[2][0] - Ctmp[2][1]);
	//	normal [1] = Ctmp[2][0]*(Ctmp[0][1] - Ctmp[0][2]) + Ctmp[2][1]*(Ctmp[0][2] - Ctmp[0][0]) + Ctmp[2][2]*(Ctmp[0][0] - Ctmp[0][1]);
	//	normal [2] = Ctmp[0][0]*(Ctmp[1][1] - Ctmp[1][2]) + Ctmp[0][1]*(Ctmp[1][2] - Ctmp[1][0]) + Ctmp[0][2]*(Ctmp[1][0] - Ctmp[1][1]);

	//	double longg  = sqrt(normal [0] * normal [0] + normal [0] * normal [0] + normal [0] * normal [0]); 
	//	double eq[4] = {normal [0],normal [1],normal [2],normal [3]};
	//	normal [0] = normal [0] / longg;
	//	normal [1] = normal [1] / longg;
	//	normal [2] = normal [2] / longg;

	//	Mat = GetBathis();
	//	Matrix invert = Mat.Invert();

	//	/*double redoun[3][3] = 
	//	{	{1,0,0},
	//		{0,-1,0},
	//		{0,0,1}, };
	//	Matrix rebound = Matrix(redoun);*/
	//	normal [0] = eq[0];
	//	normal [1] = eq[1];
	//	normal [2] = eq[2];
	//	normal [3] = eq[3];
	//	Mat = invert /** rebound * Mat*/;
	//}

	//Plane::Plane(Vector x1,Vector x2, Vector x3)
	//{
	//	//normal [0] = x2.GetX() * (x3.GetY() - x3.GetZ()) + x2.GetY() * (x3.GetZ() - x3.GetX()) + x2.GetZ() * (x3.GetX() - x3.GetY());
	//	//normal [1] = x3.GetX() * (x1.GetY() - x1.GetZ()) + x3.GetY() * (x1.GetZ() - x1.GetX()) + x3.GetZ() * (x1.GetX() - x1.GetY());
	//	//normal [2] = x1.GetX() * (x2.GetY() - x2.GetZ()) + x1.GetY() * (x2.GetZ() - x2.GetX()) + x1.GetZ() * (x2.GetX() - x2.GetY());

	//	//double longg  = sqrt(normal [0] * normal [0] + normal [0] * normal [0] + normal [0] * normal [0]); 
	//	//double eq[4] = {normal [0],normal [1],normal [2],normal [3]};
	//	//normal [0] = normal [0] / longg;
	//	//normal [1] = normal [1] / longg;
	//	//normal [2] = normal [2] / longg;

	//	//Mat = GetBathis();
	//	//Matrix invert = Mat.Invert();

	//	///*double redoun[3][3] = 
	//	//{	{1,0,0},
	//	//	{0,-1,0},
	//	//	{0,0,1}, };
	//	//Matrix rebound = Matrix(redoun);*/
	//	//normal [0] = eq[0];
	//	//normal [1] = eq[1];
	//	//normal [2] = eq[2];
	//	//normal [3] = eq[3];
	//	//Mat = invert /** rebound * Mat*/;
	//}

	//Plane::Plane(double n[4])
	//{
	//	Mat = Matrix();
	//	tes[0] = 0;
	//	tes[1] = 0;
	//	tes[2] = 0;
	//	tes[3] = 0;
	//	tes[4] = 0;
	//	tes[5] = 0;

	//	for(int i=0;i<4;i++)
	//	{
	//		normal [i] = n[i];
	//	}
	//	double length = sqrt(n[0] * n[0] + n[1] * n[1] + n[2] * n[2]); 
	//	double equation[4] = {normal [0], normal [1], normal [2], normal [3]};
	//	normal [0] = normal [0] / length;
	//	normal [1] = normal [1] / length;
	//	normal [2] = normal [2] / length;
	//	normal [3] = normal [3] / length;

	//	Mat = GetBathis();
	//	Matrix invert = Mat.Invert();

	//	normal [0] = equation[0];
	//	normal [1] = equation[1];
	//	normal [2] = equation[2];
	//	normal [3] = equation[3];
	//	Mat = invert /** rebound * Mat*/;

	//}

	//Matrix Plane::GetInvertMat()                            
	//{
	//	Matrix Matr  = GetBathis();
	//	Matr = Matr.Invert();
	//	/*double e[3][3] = {
	//		{1,0,0},
	//		{0,-1,0},
	//		{0,0,1} };*/
	//	return  /*Matrix(e) **/ Matr;
	//}

	Matrix Plane::GetMat()
	{
		return Mat;
	}
	Vector Plane::GetN()
	{
		return Vector(normal [0],normal [1],normal [2]);
	}
	double Plane::GetA()
	{
		return normal [0];
	}
	double Plane::GetB()
	{
		return normal [1];
	}
	double Plane::GetC()
	{
		return normal [2];
	}
	double Plane::GetD()
	{
		return normal [3];
	}
	Vector Plane::project(Vector* point) // проекци точки на плоскость
	{
		double test = normal [0] * point->GetX() + normal [1] * point->GetY() + normal [2] * point->GetZ() + normal [3];
		if(test >=0.0000001 || test <=-0.0000001)
		{
			double _x = point->GetX();
			double _y = point->GetY();
			double _z = point->GetZ();
			if(normal [0] != 0)
			{
				double x = (_x * ( normal [1] * normal [1] + normal [2] * normal [2]) - normal [0] * (normal [1] * _y + normal [2] * _z + normal [3])) / Vector(normal [0],normal [1],normal [2]).length2();
				return(Vector(x,(normal [1] * (x - _x))/normal [0] + _y,(normal [2] * (x - _x))/normal [0] + _z));
			}
			if(normal [1] != 0)
			{
				double y = (_y * ( normal [0] * normal [0] + normal [2] * normal [2]) - normal [1] * (normal [0] * _x + normal [2] * _z + normal [3])) / Vector(normal [0],normal [1],normal [2]).length2();
				return(Vector((normal [0] * (y - _y))/normal [1] + _x,y,(normal [2] * (y - _y))/normal [1] + _z));
			}
			if(normal [2] != 0)
			{
				double z = (_z * ( normal [0] * normal [0] + normal [1] * normal [1]) - normal [2] * (normal [0] * _x + normal [1] * _y + normal [3])) / Vector(normal [0],normal [1],normal [2]).length2();
				return(Vector((normal [0] * (z - _z))/normal [2] + _x,(normal [1] * (z - _z))/normal [2] + _y,z));
			}
		}
		return (*point);
	}
	void Plane::SetPoints(vector<Vector> points)
	{
		tmp = vector<Vector>(points);
		this->triangulation();
	}
	void Plane::triangulation() // триангуляция !!!!!!!(не работает вообще 06.01.2015)работает только для четырёхугольников! + определение ограничивающего куба + определение нормалей к контуру
	{
		//throw exception("Not tested");
		int current = 0;
		int num = 3;
		vector<int> rejected;
		int signal = num;

		int n = 0;
		for(int i =0;i<num;i++)
		{
			n = i + 1;
			if(n >= num)
				n  = n - (num);
			li[i].vec = Vector(tmp[n].GetX() - tmp[i].GetX(),tmp[n].GetY() - tmp[i].GetY(),tmp[n].GetZ() - tmp[i].GetZ());
			li[i].tmp = tmp[i];
			if(tmp[i].GetX() > tmp[n].GetX())
			{
				li[i].limit[0] = tmp[i].GetX();
				li[i].limit[1] = tmp[n].GetX();
			}	
			else
			{	
				li[i].limit[0] = tmp[n].GetX();
				li[i].limit[1] = tmp[i].GetX();
			}
			if(tmp[i].GetY() > tmp[n].GetY())
			{
				li[i].limit[2] = tmp[i].GetY();
				li[i].limit[3] = tmp[n].GetY();
			}	
			else
			{	
				li[i].limit[2] = tmp[n].GetY();
				li[i].limit[3] = tmp[i].GetY();
			}
			if(tmp[i].GetZ() > tmp[n].GetZ())
			{
				li[i].limit[4] = tmp[i].GetZ();
				li[i].limit[5] = tmp[n].GetZ();
			}						 
			else					 
			{						 
				li[i].limit[4] = tmp[n].GetZ();
				li[i].limit[5] = tmp[i].GetZ();
			}
			
		}

		Vector testing = Vector();
		n = 0;
		int  i = 0;
		int e  = 0;
		while(signal >= 3) // начало триангуляции 
		{
			bool et = true;
			bool nt = true;
			bool it = true;
			e = i + 1; 
			n = i - 1; 
			while(et || nt || it)
			{
				int r_s = rejected.size();
				if(et)
				{
					bool erej = true;
					if(e >= num)
					{
						e  = e - (num);
					}
					for(int i = 0;i<r_s;i++)
					{
						if(rejected[i] == e)
						{
							erej = false;
							break;
						}
					}
					if(!erej)
					{
						e++;
						erej = true;
					}
					else
					{
						et = false;
					}
				}
				if(nt)
				{
					bool nrej = true;
					if(n < 0)
					{
						n = num + n;
					}
					for(int i = 0;i<r_s;i++)
					{
						if(rejected[i] == n)
						{
							nrej = false;
							break;
						}
					}
					if(!nrej)
					{
						n--;
						nrej = true;
					}
					else
					{
						nt = false;
					}
				}
				if(it)
				{
					bool irej = true;
					if(i >= num)
					{
						i = 0;
					}
					for(int c = 0;c<r_s;c++)
					{
						if(rejected[c] == i)
						{
							irej = false;
							break;
						}
					}
					if(!irej)
					{
						i++;
						irej = true;
					}
					else
					{
						it = false;
					}
				}
			}

			bool convex = true;
			bool left_turn;
			bool left_test = true;
			for(int con = 0;con<num;con++)
			{
				bool conrej = true;
				while(conrej)
				{
					if(con == i || con == n)
						conrej = false;
					int r_s = rejected.size();
					for(int con_ = 0;con_<r_s && conrej;con_++)
					{
						if(rejected[con_] == con)
						{
							conrej = false;
							break;
						}
					}
					if(!conrej)
					{
						con++;
						conrej = true;
					}
					else
					{
						break;
					}
				}
				if(left_test)
				{
					left_turn = (((tmp[n].GetX() - tmp[i].GetX()) * (tmp[con].GetY()-tmp[i].GetY()) - (tmp[n].GetY() - tmp[i].GetY()) * (tmp[con].GetX()-tmp[i].GetX())) > 0);
					left_test = false;
				}
				else
				{
					if((((tmp[n].GetX() - tmp[i].GetX()) * (tmp[con].GetY()-tmp[i].GetY()) - (tmp[n].GetY() - tmp[i].GetY()) * (tmp[con].GetX()-tmp[i].GetX())) > 0) != left_turn)
					{
						convex = false;
						break;
					}
				}
			}
			if(convex)
			{
				Vector normal[3];
				Vector edge = Vector(tmp[e].GetX() - tmp[i].GetX(),0, tmp[e].GetZ() - tmp[i].GetZ());
				normal[0] = Vector(edge.GetZ(), 0, -edge.GetX()); // Всё правильно, не надо пугаться 
				testing = Vector(tmp[n].GetX() - tmp[e].GetX(), 0, tmp[n].GetZ() - tmp[e].GetZ());
				if((normal[0] & testing) <= 0)
				{
					if((normal[0] & testing) == 0)
					{
						Vector tes = Vector(tmp[n].GetX() - tmp[i].GetX(),0, tmp[n].GetZ() - tmp[i].GetZ());
						if((normal[0] & tes) < 0)
							normal[0] = Vector(-edge.GetZ(), 0, edge.GetX());
					}
					else
						normal[0] = Vector(-edge.GetZ(), 0, edge.GetX());
				}
				testing = - edge;
				edge = Vector(tmp[n].GetX() - tmp[e].GetX(),0, tmp[n].GetZ() - tmp[e].GetZ());
				normal[1] = Vector(edge.GetZ(), 0, -edge.GetX());
				if((normal[1] & testing) <= 0)
				{
					if((normal[1] & testing) == 0)
					{
						Vector tes = Vector(tmp[i].GetX() - tmp[n].GetX(),0, tmp[i].GetZ() - tmp[n].GetZ());
						if((normal[i] & tes) < 0)
							normal[1] = Vector(-edge.GetZ(), 0, edge.GetX());
					}
					else
						normal[1] = Vector(-edge.GetZ(), 0, edge.GetX());
				}
				testing = - edge;
				edge = Vector(tmp[i].GetX() - tmp[n].GetX(),0, tmp[i].GetZ() - tmp[n].GetZ());
				normal[2] = Vector(edge.GetZ(), 0, -edge.GetX());
				if((normal[2] & testing) <= 0)
				{
					if((normal[2] & testing) == 0)
					{
						Vector tes = Vector(tmp[e].GetX() - tmp[i].GetX(),0, tmp[e].GetZ() - tmp[i].GetZ());
						if((normal[2] & tes) < 0)
							normal[2] = Vector(-edge.GetZ(), 0, edge.GetX());
					}
					else
						normal[2] = Vector(-edge.GetZ(), 0, edge.GetX());
				}
				bool flag = 1;
				for(int c = 0;c<num;c++)
				{
					if(c!=i)
					{
						testing = Vector(tmp[c].GetX() - tmp[i].GetX(),0, tmp[c].GetZ() - tmp[i].GetZ());
						if((normal[0] & testing) > 0 && (normal[1] & testing) > 0 && (normal[2] & testing) > 0)
						{
							flag = 0;
							break;
						}
					}
				}
				if(flag)
				{
					tr[current][0] = i;
					tr[current][1] = e;
					tr[current][2] = n;
					tr_num +=1;
					norm[current][0] = normal[0];
					norm[current][1] = normal[1];
					norm[current][2] = normal[2];
					current += 1;
					signal -= 1;
					rejected.insert(rejected.end(),i);
				}
			}// конец триангуляции, конец света, конец добра и зла, чёрная дыра без массы и тому подобные прелести ( Конец шуту и королю, и глупости, и уму. Исполняли Никитины, Автора стихов не помню)
			i++;
		}
		// Конец поиска.
		//Определение ограничивающего куба.
		double maxX = tmp[num].GetX();
		double maxY = tmp[num].GetY();
		double maxZ = tmp[num].GetZ();
		for(int i = 0;i<num;i++) 
		{
			if(tmp[i].GetX() > maxX)
			{
				maxX = tmp[i].GetX();
			}
			if(tmp[i].GetY() > maxY)
			{
				maxY = tmp[i].GetY();
			}
			if(tmp[i].GetZ() > maxZ)
			{
				maxZ = tmp[i].GetZ();
			}
		}
		tes[0] = maxX + 2;
		tes[2] = maxY + 2;
		tes[4] = maxZ + 2;
		maxX = tmp[num].GetX();
		maxY = tmp[num].GetY();
		maxZ = tmp[num].GetZ();
		for(int i = 0;i<num;i++) 
		{
			if(tmp[i].GetX() < maxX)
			{
				maxX = tmp[i].GetX();
			}
			if(tmp[i].GetY() < maxY)
			{
				maxY = tmp[i].GetY();
			}
			if(tmp[i].GetZ() < maxZ)
			{
				maxZ = tmp[i].GetZ();
			}
		}
		tes[1] = maxX - 2;
		tes[3] = maxY - 2;
		tes[5] = maxZ - 2;
		//Конец определения куба.
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
	Vector Line::projection(Vector t) // не работает для случаев vec.GetY() == 0
	{
		double x,y,z;
		double p[3] = {vec.GetX(),vec.GetY(),vec.GetZ()};
		bool flag = true;
		if(p[0] != 0)
		{
			x = (p[0] * ( p[0] * t.GetX() + p[1] * ( t.GetY() - tmp.GetY()) + p[2]*(t.GetZ() - tmp.GetZ())) + tmp.GetX() * (p[1] * p[1] + p[2] * p[2])) / (p[0] * p[0] + p[1] * p[1] + p[2] * p[2]);
			y = tmp.GetY() - (p[1] * (tmp.GetX() - x)) / (p[0]); 
			z = tmp.GetZ() - (p[2] * (tmp.GetX() - x)) / (p[0]);
			flag = false;
		}
		if(p[1] != 0 && flag)
		{
			y = (p[1] * (p[1] * t.GetY() + p[0] * (t.GetX() - tmp.GetX()) + p[2]*(t.GetZ() - tmp.GetZ())) + tmp.GetY() * (p[0] * p[0] + p[2] * p[2])) / (p[0] * p[0] + p[1] * p[1] + p[2] * p[2]);
			x = tmp.GetX() - (p[0] * (tmp.GetY() - y )) / (p[1]);
			z = tmp.GetZ() - (p[2] * (tmp.GetY() - y )) / (p[1]);
			flag = false;
		}
		if(p[2] != 0 && flag)
		{
			z = (p[2] * (p[2] * t.GetZ() + p[0] * (t.GetX() + tmp.GetX()) + p[1]*(t.GetY() + tmp.GetY())) + tmp.GetZ() * (p[0] * p[0] + p[1] * p[1])) / (p[0] * p[0] + p[1] * p[1] + p[2] * p[2]);
			x = tmp.GetX() - (p[0] * (tmp.GetZ() - z)) / (p[2]);
			y = tmp.GetY() - (p[1] * (tmp.GetZ() - z)) / (p[2]);
		}
		return Vector(x,y,z);
	}
	Vector Line::lineXYZ(double x)
	{
		Vector t = Vector(x,vec.GetY() * (x - tmp.GetX())/vec.GetX() + tmp.GetY(), vec.GetZ() * (x - tmp.GetX())/vec.GetX() + tmp.GetZ());
		return t ;
	}