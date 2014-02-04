#include <iostream>
#include <cmath>
#include <Windows.h>
#include <ctime>
#include "../glut/glut.h"
#include "../headers/cfizika.h"
#include "../headers/func.h"

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
Fizika * phy;

void keybord(unsigned char key, int x, int y)
{
	std::cout << "Key: " << key << "\n";
	/*if (key == 'j')
	{
		glutFullScreen();
	}*/
	//if (key == 'w' || key == 246)//&& camPos[0] <= 90 && camPos[0] > 10
	//{
	//	obj ->F.SetX(Fors * cos(obj ->GetAngleXOZ() * PI /180));
	//	obj ->F.SetZ(Fors * sin(obj ->GetAngleXOZ() * PI /180));
	//}
	//if (key == 's' || key == 251)
	//{
	//	obj ->F.SetX(-Fors);
	//	obj ->F.SetZ(-Fors);
	//}

	//if (key == 'a' || key == 244)
	//{
	//	obj ->SetAngleXOZ(-Angle);
	//}
	//if (key == 'd' || key == 226)
	//{
	//	obj ->SetAngleXOZ(Angle);
	//}

	//if(key == 'e' || key == 'у')
	//{
	//	obj ->F.SetY(Fors);
	//}

	//obj -> F = Vector(0,0,0);

	//// вынести в функцию
	///*if (key == 'x' && camPos[1] <=30  && camPos[1] > 0)
	//{
	//	camPos[1]-=10;
	//	camLookAt[1]-=10;
	//}
	//	if (key == 'c' && camPos[1] < 30  && camPos[1] >= 0)
	//{
	//	camPos[1]+=10;
	//	camLookAt[1]+=10;
	//}*/
	//std :: cout << key << " --- " << (int) key << std :: endl
	//	<<"------" << obj ->Position.GetX() << std:: endl << "-------"<<  obj ->Position.GetZ()  
	//	<<  "ForseX -- " << obj ->F.GetX() << "ForseZ -- " << obj ->F.GetZ()  << std ::endl <<"VeloX -- " << obj ->velo.GetX() << "VeloZ -- " << obj ->velo.GetZ() 
	//	<<"\n\n"; 

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

		Sphere * tmp = new Sphere;
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
	//GLfloat arr[4] = {0.0,0.0,0.0,1.0};
	//GLfloat arr2[3] = {20.0,20.0,0.0};
	//GLfloat colorTeapot[3] = {1,1,0};
	GLfloat colorX[3] = {1,0,0};
	GLfloat colorY[3] = {0,0,1};
	GLfloat colorZ[3] = {1,0.5,0};
	GLfloat colorA[3] = {0,1,1};
	GLfloat green[] = {0,0.6,0};
	GLfloat amb[4] = {0,1,0,0};
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glShadeModel (GL_SMOOTH);

	//glLightfv(GL_LIGHT0, GL_SPECULAR, amb);
	//glEnable(GL_DEPTH_TEST);//¬ Ћё„≈Ќ»≈ Ѕ”‘‘≈–ј √Ћ”Ѕ»Ќџ


	//glLightfv(GL_LIGHT0, GL_POSITION, arr);         //откуда
	//glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, arr2); // куда светим

	glOrtho(0,50,0,37,0,50);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glMaterialfv(GL_FRONT_AND_BACK,GL_DIFFUSE,colorZ);
	glTranslated(20,20,0);

	glBegin(GL_POLYGON);
		glVertex3d(-15,15,0);
		glVertex3d(15,15,0);
		glVertex3d(15,-15,0);
		glVertex3d(-15,-15,0);
	glEnd();

	glMaterialfv(GL_FRONT_AND_BACK,GL_DIFFUSE,green);

	glBegin(GL_POLYGON);
		glVertex3d(18.8,16.7,-1);
		glVertex3d(17.8,17.7,-1);
		glVertex3d(-16.4,-18.3,-1);
		glVertex3d(-15.4,-19.3,-1);
	glEnd();

	glTranslated(0,0,-40);
	glMaterialfv(GL_FRONT_AND_BACK,GL_DIFFUSE,colorY);

	DWORD dt = GetTickCount()-t1;
	for(int i=0;i<num;i++)
	{
		for(int e = 0;e<num;e++)
		{
			if(i!=e)
				obj[i]->Test(obj[e]);
		}

		phy ->MoveObject(obj[i], dt/1000.0);

		glPushMatrix();
		glTranslated(obj[i]->Position.GetX(),obj[i]->Position.GetY(), obj[i]->Position.GetZ());
		glutSolidSphere(1,10,10);
		glPopMatrix();
	}
	DWORD e = time(NULL);

	/*glMaterialfv(GL_FRONT_AND_BACK,GL_DIFFUSE,colorX);
	glBegin(GL_TRIANGLE_STRIP);
		glVertex3d(30 * cos ( e * (2 * PI) / 5),30 * cos ( e * (2 * PI) / 5),-2);
		glVertex3d(5,0,-2);
		glVertex3d(-5,0,-2);
	glEnd();*/

	t1 += dt;

	glNormal3d(1,15,5);

	/*GLfloat green[] = {0,0.6,0};
	glMaterialfv(GL_FRONT_AND_BACK,GL_DIFFUSE,colorZ);*/

	glFlush();
	glutSwapBuffers();
}

int main(int argc, char **argv)
{
	setlocale(LC_ALL,"RUS");
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(1024, 768);
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

