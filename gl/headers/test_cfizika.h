
#include <iostream>
using namespace std;
#include "cfizika.h"


#ifndef __TEST_H
#define __TEST_H

class Vector_t
{
	int ok;
	int fail;

	template<class T> void Equal(T result, T expected, const char* Name)
	{
		if(result == expected)
		{
			ok++;
		}
		else
		{
			fail++;
			std:cout << ".Fail" << Name << " (result=" << result << "  expected=" << expected << ")" << std::endl; 
		}
	}
	template<class T>void Near(T result, T expected, const char* Name)
	{
		double eps = 0.0000001;
		if (abs(result - expected) < eps)
		{
			ok++;
		}
		else
		{
			fail++;
			std::cout << ". Fail: " << Name << " (result=" << result << "  expected=" << expected << ")" << std::endl;
		}
	}

	void PrintResult()
	{
		std::cout << "Total: " << ok + fail << ". Ok:" << ok << ". Fail:" << fail << ".\n";
	}
	void TestSumSub()
	{
		Vector a = Vector(1,0,0);
		Vector b = Vector(0,1,0);
		Vector c = Vector(0,0,1);
		Vector e = Vector(1,1,1);
		Vector p = Vector(0,0,0);

		Equal(1.0, 1.0,"TestSumSub.a+b");
		Equal(a+c,Vector(1,0,1),"TestSumSub.a+c");
		Equal(c+b,Vector(0,1,1),"TestSumSub.c+b");
		Equal(a+b+c,Vector(1,1,1),"TestSumSub.a+b+c");

		Equal(e-a,Vector(0,1,1),"TestSumSub.e-a");
		Equal(e-b,Vector(1,0,1),"TestSumSub.e-b");
		Equal(e-c,Vector(1,1,0),"TestSumSub.e-c");

		Equal(e+p,Vector(1,1,1),"TestSumSub.e+p");
		Equal(a-e,Vector(0,-1,-1),"TestSumSub.a-e");

		Equal(-e,Vector(-1,-1,-1),"TestSumSub.-e");
	}
	void TestEqualOperator()
	{
		Vector a = Vector(1,0,1);
		Vector b = Vector(1,1,1);
		Vector c = Vector(1,0,1);
		double e = 10;
		double q = 1;

		Equal(a == b,false,"TestEqualOperator.a==b");
		Equal(a != b,true,"TestEqualOperator.a!=b");
		Equal(a == c,true,"TestEqualOperator.a == c");
		Equal(a != c,false,"TestEqualOperator.a != c");

		Equal(a<e,true,"TestEqualOperator.a<e");
		Equal(a<q,false,"TestEqualOperator.a<c");
	}
	void TestMulti()
	{
		Vector a = Vector(0,0,0);
		Vector b = Vector(1,1,1);
		Vector e = Vector(2,4,6);
		Vector h = Vector(5,7,8);
		double scal = 2;

		Equal(a * e,Vector(0,0,0),"TestMulti.a * e");
		Equal(b * e,Vector(2,-4,2),"TestMulti.b * e");
		Equal(e * b,Vector(-2,4,-2),"TestMulti.e * b");
		Equal(a * scal,Vector(0,0,0),"TestMulti.a * scal");
		Equal(b * scal,Vector(2,2,2),"TestMulti.b * scal");
		Equal(e/scal,Vector(1,2,3),"TestMulti.e/scal");
		Equal(e > h,Vector(10,28,48),"TestMulti.e > h");
	}
	void TestFunc()
	{
		Vector a = Vector(3,0,4);
		Vector b = Vector(4,9,16);
		Vector c = Vector(1,1,1);
		Vector e = Vector(1,2,3);
		Vector s = Vector(4,5,6);
		Near(e ^ s,0.9746318462,"TestFunc.e^s");
		Equal(a.length(),5.0,"TestFunc.a.length()");
		Equal(a.length2(),25.0,"TestFunc.a.length2()");
		Equal(b.sqrt_ve(),Vector(2,3,4),"TestFunc.a.lenght()");
	}

	Vector_t()
	{
		ok = 0;
		fail = 0;
	}
	
	void RunAll()
	{
		/*TestEqualOperator();
		TestSumSub();
		PrintResult();*/
	}
};

#endif
