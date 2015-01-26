#include <Windows.h>
#include <iostream>
#include <cmath>

#include "../headers/DynamicWorld.h"


const double PI = 3.1415916;
const int E = 20;

#include "../headers/Geometry.h"
#include "../headers/Objects.h"
#include "../headers/World.h"
#include "../headers/Fizika.h"
#include "../headers/colors.h"
#include "../glut/glut.h"

// Физика
// Хе-Хе

const int SCENE_W = 800;//1024;
const int SCENE_H = 600;//768;

double lightAngle = 0;
double lightHeight = 8;


double camAng1 = 90;
double camAng2 = 0;
double camHeight = 0;

double oldX = 0;
double oldY = 0;
bool dragFlag = false; 
bool needStep = false;

DWORD previousTime = 0;
DWORD t1 = 0;
DWORD FPS = 0;
double IFPS = 0;

#define Fors 5
#define Angle 2
#define Matr 0.5

//int num = 0;
int maxx = 0;

Fizika * phy = NULL;
StaticWorld* planes = NULL; 
DynamicWorld* balls = NULL; 

double e [3] = {1,0,0};


void keyboard(unsigned char key, int x, int y)
{
	switch(key)
	{
	case 'w':
		camHeight+=1;
		break;
	case 's':
		camHeight-=1;
		break;
	case 'q':
		lightHeight+=1;
		break;
	case 'e':
		if (lightHeight > -4) lightHeight-=1;
		break;
	case 't':
		needStep  = true;
	}
	glutPostRedisplay();
}
void keyboard1(unsigned char key, int x, int y)
{
	switch(key)
	{
	case 'e':
		e[0]-=0.1;
		break;
	case 'v':
		e[0]+=0.1;
		break;
	case 'r':
		e[1]-=0.1;
		break;
	case 'f':
		e[1]+=0.1;
		break;
	case 't':
		e[2]-=0.1;
		break;
	case 'c':
		e[2]+=0.1;
		break;
	}
	glutPostRedisplay();
}
void mouseClick(int button, int state, int x, int y)
{
	if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN /*&& num < 100*/)
	{
		double x1 = x * 0.05;
		double y1 = 30 - y * 0.05;
		balls->Add(Sphere(Vector(x1,y1,25)));
	}
	if(button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN )
	{
		dragFlag = true;
		oldX = x;
		oldY = y;
	}
	if(button == GLUT_RIGHT_BUTTON && state == GLUT_UP)
	{
		dragFlag = false;
	}
	//std::cout << " X : " << x << std::endl << "Y : " << y << std::endl;

}
void mouseMotion(int x, int y)
{
	if (dragFlag)
	{
		double dx = x - oldX;
		camAng1 += dx * 0.5;
		oldX = x;

		double dy = y - oldY;
		camAng2 += dy * 0.5;
		oldY = y;
	}
}
void idle(void)
{

	DWORD dt=GetTickCount();
	if(dt - FPS > 3000)
	{
		cout << "FPS. " << IFPS << endl;
		IFPS = 0;
		FPS = dt;
	}
	if(dt - previousTime > 15)
	{
		lightAngle+=2;
		if(lightAngle>360) lightAngle = 0;

		previousTime = dt;
		glutPostRedisplay();
	}
}
void reshape(int width, int height)
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60, SCENE_W/(double)SCENE_H, 1, 100);
	//gluLookAt(0,40,40,25,0,-25, 0,1,0);
	
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

}

//double GY (double X, double Z,Plane & pl)
//{
//	return -( ( X * pl.GetA() + Z * pl.GetC() + pl.GetD() ) / pl.GetB() );
//}
void Draw(Vector & v)
{
	glBegin(GL_LINES);
	glVertex3d(0,0,0);
	glVertex3d(v.GetX(),v.GetY(),v.GetZ());
	glEnd();
}
void DrawD(Vector & v)
{
	glBegin(GL_LINES);
	glVertex3d(-v.GetX(),-v.GetY(),-v.GetZ());
	glVertex3d(0,0,0);
	glEnd();
}
void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_NORMALIZE);
	//Camera
	glPushMatrix();
	glTranslated(0,-5,-30 + camHeight);
	glRotated(camAng2, 1,0,0);
	glRotated(camAng1, 0,1,0);
	//glTranslated(-10,0,10);
	//glTranslated(-0,0,-10);
	

	//Scene light
	GLfloat ambient[] = {0.2, 0.2, 0.2, 1.0}; 
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambient);
	glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);
	glEnable(GL_LIGHTING);
	

	//light 0
	glPushMatrix();
	GLfloat pos[] = {7, 5+lightHeight, 0, 1.0};
	glPushMatrix();
	glDisable(GL_LIGHTING);
	glColor3f(1,1,0);
	glTranslated(10,0,-10);
	glRotated(lightAngle,0,1,0);
	glTranslated(pos[0], pos[1], pos[2]);
	glutSolidSphere(1,10,10);
	glEnable(GL_LIGHTING);
	glPopMatrix();	
	glTranslated(10,0,-10);
	glRotated(lightAngle,0,0.5,0);
	glLightfv(GL_LIGHT0, GL_POSITION, pos);
	glEnable(GL_LIGHT0);
	glPopMatrix();

	/*glBegin(GL_LINES);
		glVertex
	glEnd();*/
	//glLineWidth(5.0);
	////floor
	glNormal3d(0,1,0);
	int x = 20;
	int z = -20;

	glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE, red);
	Draw(Vector(5,0,0));
	glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE, green);
	Draw(Vector(0,5,0));
	glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE, blue);
	Draw(Vector(0,0,5));
	

	//выводит только первые три точки плоскости
	StaticWorld tmp = phy->planes;
	//Plane pl = tmp.Get(0);
	glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE, blue);
	glBegin(GL_TRIANGLES);
	/*glVertex3d(pl.tmp[0].GetX(), pl.tmp[0].GetY(), pl.tmp[0].GetZ());
	glVertex3d(pl.tmp[1].GetX(), pl.tmp[1].GetY(), pl.tmp[1].GetZ());
	glVertex3d(pl.tmp[2].GetX(), pl.tmp[2].GetY(), pl.tmp[2].GetZ());*/
	glEnd();
	

	//plane
	glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE, green);
	glBegin(GL_POLYGON);
	glNormal3d(-10,10,1);
	glEnd();


	//DWORD dt = GetTickCount()-t1;
	needStep = 1; // удалить
	if(needStep) 
	{
		needStep = false;
		DWORD dt = 25;/*GetTickCount()-t1*/; 
		double tim = dt/1000.0;
	
		for(int i=0;i<phy->balls.Count();i++)
		{
			phy->balls.MoveSphere(i, tim);
		}
		
		phy->FindCollisions();
		phy->ParseCollision(tim);
	}

	
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, red);
	int number = phy->balls.Count();
	for(int i=0;i<number;i++)
	{
		//Sphere* s = &phy->balls.Get(i);
		glPushMatrix();
		//glTranslated(s->p.GetX(),s->p.GetY(), s->p.GetZ());
		//glRotated(s->Angl.GetX(),0,0,1);
		//glRotated(s->Angl.GetZ(),1,0,0);
		glutSolidSphere(1,5,5);
		glPopMatrix();
		
	}
	
	//t1 += dt;
	glPopMatrix();
	IFPS = IFPS + 1;
	glFlush();
	glutSwapBuffers();
}

int main(int argc, char **argv)
{
	setlocale(LC_ALL,"RUS");
	/*glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(SCENE_W, SCENE_H);
	glutCreateWindow("OpenGL тестовый мир");

	glutDisplayFunc(display);
	glutIdleFunc(idle);
	glutKeyboardFunc(keyboard);
	glutMouseFunc(mouseClick);
	glutMotionFunc(mouseMotion);
	glutReshapeFunc(reshape);
	glClearColor(0.0, 0.0, 0.0, 1.0);*/


	planes = new StaticWorld();
	Plane* p = planes->Get(0);
	p->val = 5;
	Vector v = p->tmp[0];


	balls = new DynamicWorld();

	balls->Add(Sphere(Vector(5,3,0)));
	
	phy = new Fizika(*planes, *balls);
	phy->FindCollisions();
	
	Collision tmp = phy->collision[0];
	
	Plane* pl = tmp.plane;

	tmp.sp->Test();
	pl->Test();
	Plane pl1 = *pl; //<-- тут ошибка.
	
	tmp.sp->Test2(pl1, 1.0, 0.03);
	(*tmp.sp).Test2(pl1, 1.0, 0.03);
	





	//phy->ParseCollision(0.03);
	
	maxx = 10;
	t1 = GetTickCount();

	//glutMainLoop();
	
	delete phy;
	return 0;
}