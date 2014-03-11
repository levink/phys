#include <iostream>
#include <cmath>
#include <Windows.h>
#include <ctime>
#include "../glut/glut.h"
#include "../headers/cfizika.h"
#include "../headers/func.h"

const int SCENE_W = 1024;
const int SCENE_H = 768;

double angle = 0, step = 0;
const double PI = 3.1415916;
double camLookAt[3] = {0,0,0};

DWORD previousTime = 0;
DWORD t1 = 0;

#define Fors 5
#define Angle 2
#define Matr 0.5

//double down = 0;
int num = 0;
int max = 0;

Sphere * obj[100];
int gen_test [100][100];
//int in = 0;
Fizika * phy;

int InvIn();
void Start();
double getY(double x, double z);
void keybord(unsigned char key, int x, int y)
{
	std::cout << "Key: " << key << "\n";
	
	if (key == 'w' || key == 246)
	{
		
	}
	if (key == 's' || key == 251)
	{
		
	}

	
	glutPostRedisplay();
}

void mouseMotion(int button, int state, int x, int y)
{
	if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && num < 100)
	{
		double x1;
		double y1;
		
		x1 = x - 407.5; // преобразование ск окна в ск "мира"
		y1 = y - 335;
		x1 *= 0.04878;
		y1 *= -0.050847;
		Vector pos = Vector(x1,y1,-10);

		Sphere * tmp = new Sphere();
		tmp->Position = pos;
		obj[num] = tmp;
		num++;
		//CopyFanc(obj,tmp,num,max);
		std::cout << "Sphere X: " << x1 << ", Y: " << y1 << std::endl;
	}
	//std::cout << "Mouse X: " << x << ", Y: " << y << std::endl;
}

void idle(void)
{
	angle+=0.05;
	if(angle>360) angle = 0;
	
	DWORD dt=GetTickCount();
	if(dt - previousTime > 15)
	{
		previousTime = dt;
		glutPostRedisplay();
	}
}

void display(void)
{
	GLfloat colorX[3] = {1,0,0};
	GLfloat colorY[3] = {0,0,1};
	GLfloat colorZ[3] = {1,0.5,0};
	GLfloat colorA[3] = {0,1,1};
	GLfloat green[] = {0,0.6,0};
	
	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_NORMALIZE);
	glShadeModel (GL_SMOOTH);

	GLfloat amb[3] = {0.8,0.8,0.8};
	GLfloat pos[3] = {1, 50, -1};
	glLightfv(GL_LIGHT0, GL_AMBIENT_AND_DIFFUSE, amb);
	glLightfv(GL_LIGHT0, GL_POSITION, pos);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);


	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	//glOrtho(0,50,0,37,0,50);
	gluPerspective(60, SCENE_W/(double)SCENE_H, 1, 100);
	gluLookAt(0,40,40,25,0,-25, 0,1,0);
	
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glMaterialfv(GL_FRONT_AND_BACK,GL_DIFFUSE,colorZ);

	glBegin(GL_POLYGON);
		glNormal3d(0,1,0);
		glVertex3d(0,0,0);
		glVertex3d(0,0,-50);
		glVertex3d(50,0,-50);
		glVertex3d(50,0,0);
	glEnd();


	glMaterialfv(GL_FRONT_AND_BACK,GL_DIFFUSE,green);
	glBegin(GL_POLYGON);
		glNormal3d(-10,10,1);
		glVertex3d(10, getY(10,-0),-0);
		glVertex3d(10, getY(10,-40),-40);
		glVertex3d(30,getY(30,-40),-40);
		glVertex3d(30,getY(30,-0),-0);
	glEnd();

	glTranslated(0,0,-40);
	glMaterialfv(GL_FRONT_AND_BACK,GL_DIFFUSE,colorY);

	DWORD dt = GetTickCount()-t1;
	Sphere * te1 = new Sphere();
	Sphere * te2 = new Sphere();

	double tim = dt/1000.0;
	
	for(int i=0;i<num;i++)
	{
		for(int e = 0;e<num;e++)
		{
			/*if(i==e && num == 1)
			{
				phy->MoveObject(obj[in][i],tim);
				int _inv = InvIn();
				obj[_inv][i] = obj[in][i];
			}*/ // та самая ерунда
			if(i!=e && gen_test[i][e]==0) // она же
			{
				/*if(in == 0)
				{
					obj[1][i] = obj[0][i];
					obj[1][e] = obj[0][e];
				}
				else
				{
					obj[0][i] = obj[1][i];
					obj[0][e] = obj[1][e];
				}
				phy ->MoveObject(obj[in][i], tim );
				phy ->MoveObject(obj[in][e], tim );*/ //  и снова здравствуйте
				te1 = obj[i];
				te2 = obj[e];
				te1->TestMO(te1,tim);
				te2->TestMO(te2,tim);

				bool tes = 0;
				if(te1->velo.distanse(te1->Position,te2->Position) < ( obj[i]->GetRad() + obj[e]->GetRad()) * 1.1 )
					tes = 1;
				obj[i]->Test(obj[e],tes);

				//obj[in][i]->Test(obj[in][e]);
				gen_test[i][e] = 2;
				gen_test[e][i] = 2;
			}
			else
				if(gen_test[i][e] > 0)
					gen_test[i][e]--;
		}
	}
	
	for(int i=0;i<num;i++)
	{
		phy ->MoveObject(obj[i], tim);
		glPushMatrix();
		glTranslated(obj[i]->Position.GetX(),obj[i]->Position.GetY(), obj[i]->Position.GetZ());
		glRotated(obj[i]->Angl.GetX(),0,0,1);
		glRotated(obj[i]->Angl.GetZ(),1,0,0);
		glutSolidSphere(1,5,5);
		glPopMatrix();
	}

	t1 += dt;
	glFlush();
	glutSwapBuffers();
}

int main(int argc, char **argv)
{
	setlocale(LC_ALL,"RUS");
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(SCENE_W, SCENE_H);
	glutCreateWindow("OpenGL тестовый мир");

	glutDisplayFunc(display);
	glutIdleFunc(idle);
	glutKeyboardFunc(keybord);
	glutMouseFunc(mouseMotion);
	glClearColor(0.0, 0.0, 0.0, 1.0);

	int d = 1;
	//Vector Cam = Vector(0,14,-10);

	//obj = new Camera * [10];
	max = 10;
	phy = new Fizika;
	//obj[0] ->Position = Cam;
	t1 = GetTickCount();

	glutMainLoop();
	
	delete obj;
	delete phy;
	return 0;
}

//int InvIn()
//{
//	int inv;
//	if( in == 0)
//		inv = 1;
//	else
//		inv = 0;
//	return inv;
//}

void Start()
{
	for(int i=0;i<100;i++)
	{
		*obj[i] = Sphere();
		for(int e=0;e<100;e++)
		{
			gen_test[i][e] = 0;
		}
	}
}

World* GetWorld(Fizika obj)
{
	return &obj.wor;
}

double getY(double x, double z)
{
	double e[4]  ={-10,10,1,0};
	if(e[1] == 0) return 0;
	return -(e[3] + e[2]*z + e[0]*x)/e[1];
}