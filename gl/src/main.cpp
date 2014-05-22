#include <Windows.h>
#include <iostream>
#include <cmath>


const double PI = 3.1415916;
const int E = 20;

#include "../headers/Geometry.h"
#include "../headers/Objects.h"
#include "../headers/World.h"
#include "../headers/Fizika.h"
#include "../headers/colors.h"
#include "../glut/glut.h"

// ������
// ��-��

const int SCENE_W = 800;//1024;
const int SCENE_H = 600;//768;

double lightAngle = 0;
double lightHeight = 8;


double camAng1 = 0;
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

int num = 0;
int maxx = 0;

Sphere * obj[100];
int gen_test [100][100];
Fizika * phy;


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

World* GetWorld(Fizika* obj)
{
	return &obj->wor;
}
Plane* GetPlane(World obj)
{
	return obj.Plan;
}

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

void mouseClick(int button, int state, int x, int y)
{
	if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && num < 100)
	{
		double x1;
		double y1;
		
		x1 = x * 0.05;
		y1 = 30 - y * 0.05;

		Vector pos = Vector(x1,y1,25);

		Sphere * tmp = new Sphere();
		tmp->Position = pos;
		obj[num] = tmp;
		num++;
		tmp = NULL;
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
	std::cout << " X : " << x << std::endl << "Y : " << y << std::endl;

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
	glTranslated(-10,0,10);
	

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
	glRotated(lightAngle,0,1,0);
	glLightfv(GL_LIGHT0, GL_POSITION, pos);
	glEnable(GL_LIGHT0);
	glPopMatrix();

	//floor
	glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE, blue);
	glBegin(GL_QUADS);
	glNormal3d(0,1,0);
	int x = 20;
	int z = -20;
	/*for(int t=0;t<GetWorld(*phy)->GetK()+1;t++)
	{
		for(int i=0;i < x; i++)
			for(int j=0;j > z; j--)
			{
				glVertex3d(i, GetWorld(*phy)->GetYatXZ(i,j,t),j);
				glVertex3d(i,GetWorld(*phy)->GetYatXZ(i,j-1,t),j-1);
				glVertex3d(i+1,GetWorld(*phy)->GetYatXZ(i+1,j-1,t),j-1);
				glVertex3d(i+1,GetWorld(*phy)->GetYatXZ(i+1,j,1),t);
			}
	}*/
	World* tmp = NULL;
	tmp = GetWorld(phy);
	for(int t=0;t<tmp->GetK();t++)
	{
		for(int i=0;i < x; i++)
			for(int j=0;j > z; j--)
			{
				glVertex3d(i, GetWorld(phy)->GetYatXZ(i,j,t),j);
				glVertex3d(i,GetWorld(phy)->GetYatXZ(i,j-1,t),j-1);
				glVertex3d(i+1,GetWorld(phy)->GetYatXZ(i+1,j-1,t),j-1);
				glVertex3d(i+1,GetWorld(phy)->GetYatXZ(i+1,j,t),j);
			}
	}
	glEnd();

	//plane
	glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE, green);
	glBegin(GL_POLYGON);
	glNormal3d(-10,10,1);
	/*glVertex3d(10, GetY(10,-0)-5,-0);
	glVertex3d(10, GetY(10,-40)-5,-40);
	glVertex3d(30, GetY(30,-40)-5,-40);
	glVertex3d(30, GetY(30,-0)-5,-0);*/
	/*glVertex3d(10, GetWorld(*phy)->GetYatXZ(10,-0,0),-0);
	glVertex3d(10, GetWorld(*phy)->GetYatXZ(10,-30,0),-30);
	glVertex3d(60, GetWorld(*phy)->GetYatXZ(60,-30,0),-30);
	glVertex3d(60, GetWorld(*phy)->GetYatXZ(60,-0,0),-0);*/
	glEnd();
	glTranslated(0,0,-40);
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, red);

	//DWORD dt = GetTickCount()-t1;
	if(needStep) 
	{
		needStep = false;
		DWORD dt = 25/*GetTickCount()-t1*/; 
		Sphere te1 = Sphere();
		Sphere te2 = Sphere();
		

		double tim = dt/1000.0;
		
		for(int i=0;i<num;i++)
		{
			for(int e = 0;e<num;e++)
			{
				if(i!=e && gen_test[i][e]==0)
				{
					te1 = obj[i];
					te2 = obj[e];

					phy->MoveObject(&te1,tim);
					phy->MoveObject(&te2,tim);

					bool tes = 0;
					if((te1.Position - te2.Position).length() < ( obj[i]->GetRad() + obj[e]->GetRad()) * 1.1 )
						tes = 1;
					obj[i]->Test(obj[e],tes);

					gen_test[i][e] = 3;
					gen_test[e][i] = 3;
				}
				else
					if(gen_test[i][e] > 0)
						gen_test[i][e]--;
			}
		}
		
		for(int i=0;i<num;i++)
		{
			phy ->MoveObject(obj[i], tim);
		}
	}
	for(int i=0;i<num;i++)
	{
		glPushMatrix();
		glTranslated(obj[i]->Position.GetX(),obj[i]->Position.GetY(), obj[i]->Position.GetZ());
		glRotated(obj[i]->Angl.GetX(),0,0,1);
		glRotated(obj[i]->Angl.GetZ(),1,0,0);
		glutSolidSphere(1,5,5);
		glPopMatrix();
		
	}
	
	//t1 += dt;
	glPopMatrix();
	IFPS = IFPS + 1;
	glFlush();
	glutSwapBuffers();
}

int main()
{
	double eq[3] = {10,10,0};
	Plane pl = Plane();
	pl.PlaneSetEquation(eq);
	Matrix mat = pl.GetBathis();

	return 0;
}

int main1(int argc, char **argv)
{
	//Vector_t T;
	//T.RunAll();
	setlocale(LC_ALL,"RUS");
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(SCENE_W, SCENE_H);
	glutCreateWindow("OpenGL �������� ���");

	glutDisplayFunc(display);
	glutIdleFunc(idle);
	glutKeyboardFunc(keyboard);
	glutMouseFunc(mouseClick);
	glutMotionFunc(mouseMotion);
	glutReshapeFunc(reshape);
	glClearColor(0.0, 0.0, 0.0, 1.0);

	/*Sphere * tmp = new Sphere();
	tmp->Position = Vector(14,17,25);
	tmp->velo = Vector(0,-3,0);
	obj[num] = tmp;
	num++;*/
	/*Sphere * tmp1 = new Sphere();
	tmp1->Position = Vector(9,13,25);
	obj[num] = tmp1;
	num++;
	*/
	Sphere * tmp = new Sphere();
	tmp->Position = Vector(	12-2.78,17-1.3,25); // |
	tmp->velo = Vector(0,-3,0);
	obj[num] = tmp;
	num++;
	Sphere * tmp1 = new Sphere();
	tmp1->Position = Vector(12-1.32,17-2.74,25); // ||
	obj[num] = tmp1;
	num++;
	Sphere * tmp2 = new Sphere();
	tmp2->Position = Vector(12-3.29,17-3.22,25); // ||
	obj[num] = tmp2;
	num++;

	int d = 1;
	
	maxx = 10;
	phy = new Fizika();
	t1 = GetTickCount();

	glutMainLoop();
	
	delete obj;
	delete phy;
	return 0;
}