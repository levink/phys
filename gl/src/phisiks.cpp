#include<iostream>
#include<ctime>
#include <cmath>
#include "../headers/cfizika.h"
#include "../glut/glut.h"

const double PI = 3.1415916;
#define n 0.5
#define p 1.2041
//DWORD t100 = 0;

Fizika::Fizika()
{
	_g = 9.8;
	World wor = World();
}



void Fizika::MoveObject(Camera * obj, double t_sec)
{
	//������� ����� ���������� ������� �� ������ ��� ������� ����� � ����� "����������" �������


	Vector Ft = Vector(0,-obj->m * _g,0); //+ F1 + F2 + ...
	Vector Ftr =(obj->velo * obj->velo * p / 2) *  n * 3.14;
	Vector F = Ft + Ftr; /*obj ->F;*/	// + F1 + F2 + ...;
	Vector a = F / obj->m;
	Vector v = obj->velo + a*t_sec; 
	Vector x = obj->Position + obj->velo*t_sec + obj->accel*t_sec*t_sec/2; 

	obj->accel = a;
	obj->velo = v;
	obj->Position = x;

	//DWORD t = time(NULL);

	wor.Test(obj,0.8);

	//F0.SetX(obj ->F.GetX());
	//F0.SetZ(obj ->F.GetZ());
	//F0.SetY(obj ->F.GetY());

	obj -> F.SetY( _g * obj ->m);
	obj ->F.SetX( obj ->F.GetX() - cos(pow(obj ->velo.GetX(),2) * 0.2));
	obj ->F.SetZ( obj ->F.GetZ() - sin(pow(obj ->velo.GetZ(),2) * 0.2));
}

void Fizika::MoveObject(Sphere * obj, double t_sec)
{
	//������� ����� ���������� ������� �� ������ ��� ������� ����� � ����� "����������" �������

	Vector Ft = Vector(0,-obj->m * _g,0); //+ F1 + F2 + ...
	Vector Ftr =(obj->velo * obj->velo * p / 2) *  n * 3.14;
	Vector F = Ft + Ftr + obj ->F;	// + F1 + F2 + ...;
	Vector a = F / obj->m;
	Vector v = obj->velo + a*t_sec; 
	Vector x = obj->Position + obj->velo*t_sec + obj->accel*t_sec*t_sec/2; 

	obj->accel = a;
	obj->velo = v;
	obj->Position = x;

	wor.Test(obj,0.8);

	double l = obj->GetRad() * 2 * PI;
	obj->Angl  = ( (obj->ve_ro * t_sec) / l) * 360 + obj->Angl;
	if(obj->Angl.GetX() > 360)
		obj->Angl.SetX(0);
	if(obj->Angl.GetY() > 360)
		obj->Angl.SetY(0);
	if(obj->Angl.GetZ() > 360)
		obj->Angl.SetX(0);
}

Camera::Camera ()
{
	Position = Vector(0,0,0);
	velo = Vector(0,0,0);
	accel = Vector(0,0,0);
	F = Vector(0,0,0);
	m =0;
	bornTime = 0;
	angle = 0;
	m = 10;
}

double Camera ::GetAngleXOZ()
{
	return angle;
}

void Camera :: SetAngleXOZ(int ang)
{
	angle += ang;
	if(angle > 360)
		angle = 0;
}


//HDC        hDC=NULL;  // ��������� �������� ���������� GDI
//HGLRC      hRC=NULL;  // ���������� �������� ����������
//HWND       hWnd=NULL; // ��������� ���������� ����
//HINSTANCE  hInstance; // ��������� ��������� ����������
//
//GLuint  gmf;      // ���� ������ ����������� ��� �����
//GLfloat  cnt1;     // ������ ������� ��� ������������ � ������������ ������
//GLfloat  cnt2;     // ������ ������� ��� ������������ � ������������ ������
// 
//bool  keys[256];      // ������ ��� ������ � �����������
//bool  active=TRUE;    // ���� ��������� ����, �� ��������� = TRUE
//bool  fullscreen=TRUE;// ���� �������������� ������
// 
//LRESULT  CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);  // ���������� WndProc
//
//GLvoid BuildFont(GLvoid)  // ���������� ������ ���������� ������
//{
//  HFONT  font;            // ������������� �����
// 
//  base = glGenLists(96);  // ������� ����� ��� 96 �������� ( ����� )
// font = CreateFont(  -24,0,0,0,FW_BOLD,FALSE,        // ������
//        FALSE,        // �������������
//        FALSE,        // ��������������        
//		 ANSI_CHARSET,      // ������������� ������ ��������
//		  OUT_TT_PRECIS,      // �������� ������
//		  CLIP_DEFAULT_PRECIS,    // �������� ���������
//		    ANTIALIASED_QUALITY,    // �������� ������
//  FF_DONTCARE|DEFAULT_PITCH,  // ��������� � ���
//   "Courier New"); 
// SelectObject(hDC, font);        // ������� �����, ��������� ���� ( ����� )
// 
//  wglUseFontBitmaps(hDC, 32, 96, base); // ��������� 96 �������� ������� � ������� ( ����� )
//}
//
//GLvoid KillFont(GLvoid)            // �������� ������
//{
//   glDeleteLists(base, 96);        // �������� ���� 96 ������� ����������� ( ����� )
//}
//GLvoid glPrint(const char *fmt, ...)        // �������� ������� ������� GL
//{
//	 char    text[256];      // ����� ��� ����� ������
//  va_list    ap; 
//  if (fmt == NULL)     // ���� ��� ������
//    return;            // ������ �� ������
// 
//  va_start(ap, fmt);           // ������ ������ ����������
//      vsprintf(text, fmt, ap); // � ��������������� �������� � �������� ����
//  va_end(ap);   
//  glPushAttrib(GL_LIST_BIT);      // ����������� ���� ������ ����������� ( ����� )
//  glListBase(gmf - 32); 
//   glCallLists(strlen(text), GL_UNSIGNED_BYTE, text);// ����� �������� �����������(�����)
// glPopAttrib(); // ������� ����� ������ ����������� ( ����� )
//}

//int InitGL(GLvoid)            // ��� ��������� ��������� OpenGL �����
//{
//  glShadeModel(GL_SMOOTH);    // ��������� ������� ���������
//  glClearColor(0.0f, 0.0f, 0.0f, 0.5f); // ������ ���
//  glClearDepth(1.0f);         // ��������� ������ �������
//  glEnable(GL_DEPTH_TEST);    // ���������� ����� �������
//  glDepthFunc(GL_LEQUAL);     // ��� ����� �������
//  // ������������� ������� ���������� �����������
//  glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
//  BuildFont();            // ��������� �����
//  return TRUE;            // ������������� ��������
//}


 
