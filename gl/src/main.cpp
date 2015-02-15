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

// ‘изика
// ’е-’е

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
//int maxx = 0;

Fizika* phy = NULL;
World* planes = NULL;
ContainerObjects* bal = NULL;

//Quadrocopter farse
double f1 = 24.5;//1->11\  /22 <-2			
double f2 = 24.5;//      \/ 	
double f3 = 24.5;//      /\ 	
double f4 = 24.5;//4->44/	\33 <-3	
double plusf = 0.2; 
double e [3] = {1,0,0};


int _tmp = 1;
bool pause = true;

void Clear();
void StartDemo(int);
void Demo1();
void Demo2();
void Demo3();
void Demo4();
void Demo5();
void Demo6();

void keyboard(unsigned char key, int x, int y)
{
	if (key >= '1' && key <= '6')
	{
		int num = key - '0';
		_tmp = num;
		StartDemo(_tmp);
	}
	if(_tmp==6)
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
		/*case 'e':
			if (lightHeight > -4) lightHeight-=1;
			break;*/
		case 'e':
			needStep  = true;
			break;
		case 'p':
			pause = !pause;
			break;
		case 'i':
			f2 +=plusf;
			break;
		case 'k':
			if(f2>0)
				f2-=plusf;
			break;
		case't':
			f1+=plusf;
			break;
		case 'g':
			if(f1>0)
				f1-=plusf;
			break;
		case 'r':
			f4 +=plusf;
			break;
		case 'f':
			if(f4>0)
				f4-=plusf;
			break;
		case'o':
			f3+=plusf;
			break;
		case 'l':
			if(f3>0)
				f3-=plusf;
			break;
		}
	}
	else
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
			break;
		case 'p':
			pause = !pause;
			break;
		}
	}
	glutPostRedisplay();
}

void mouseClick(int button, int state, int x, int y)
{
	if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN /*&& num < 100*/)
	{
		double x1;
		double y1;
		
		x1 = x * 0.05;
		y1 = 30 - y * 0.05;

		Vector pos = Vector(x1,y1,5);

		Sphere tmp = Sphere();
		tmp.Position = pos;
		phy->balls->Add(tmp);
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
		//lightAngle+=2;
		//if(lightAngle>360) lightAngle = 0;

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

double GY (double X, double Z,Plane & pl)
{
	return -( ( X * pl.GetA() + Z * pl.GetC() + pl.GetD() ) / pl.GetB() );
}
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
	//glutSolidSphere(1,10,10);
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
	glLineWidth(1.5);
	////floor
	glNormal3d(0,1,0);
	int x = 20;
	int z = -20;

	glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE, red);
	Draw(Vector(5,0,0));
	glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE, yellow);
	Draw(Vector(0,5,0));
	glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE, blue);
	Draw(Vector(0,0,5));
	
	glPushMatrix();
	//glTranslated(-5,0,-5);

	for(int i = 0;i<planes->Count();i++)
	{
		glBegin(GL_TRIANGLES);
		Plane * pl = planes->GetPl(i);
		GLfloat col[3] = {0,0.9 - 0.05 * i,0};
		for(int e = 0;e<pl->tr_num;e++)
		{
			col[1] -=e * 0.1;
			glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE,col);
			Vector t1 = pl->tmp[pl->tr[0][e]];
			Vector t2 = pl->tmp[pl->tr[1][e]];
			Vector t3 = pl->tmp[pl->tr[2][e]];
			glVertex3d(pl->tmp[pl->tr[0][e]].GetX(), pl->tmp[pl->tr[0][e]].GetY(),pl->tmp[pl->tr[0][e]].GetZ());
			glVertex3d(pl->tmp[pl->tr[1][e]].GetX(), pl->tmp[pl->tr[1][e]].GetY(),pl->tmp[pl->tr[1][e]].GetZ());
			glVertex3d(pl->tmp[pl->tr[2][e]].GetX(), pl->tmp[pl->tr[2][e]].GetY(),pl->tmp[pl->tr[2][e]].GetZ());
		}													   
		glEnd();
	}
	/*glBegin(GL_QUADS);
	glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE, green);
	for(int t=0;t<tmp->GetK();t++)
	{
		for(int i=0;i < x; i++)
			for(int j=50;j > z; j--)
			{
				glVertex3d(i, GetWorld(phy)->GetYatXZ(i,j,t),j);
				glVertex3d(i,GetWorld(phy)->GetYatXZ(i,j-1,t),j-1);
				glVertex3d(i+1,GetWorld(phy)->GetYatXZ(i+1,j-1,t),j-1);
				glVertex3d(i+1,GetWorld(phy)->GetYatXZ(i+1,j,t),j);
			}
	}

	for(int i=0;i < x; i++)
		for(int j=0;j > z; j--)
		{
			glVertex3d(i, GetWorld(phy)->GetYatXZ(i,j,1)+10,j);
			glVertex3d(i,GetWorld(phy)->GetYatXZ(i,j-1,1)+10,j-1);
			glVertex3d(i+1,GetWorld(phy)->GetYatXZ(i+1,j-1,1)+10,j-1);
			glVertex3d(i+1,GetWorld(phy)->GetYatXZ(i+1,j,1)+10,j);
		}

	glEnd();*/

	//plane
	//glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE, green);
	/*glBegin(GL_POLYGON);
	glNormal3d(-10,10,1);*/
	/*glVertex3d(10, GetY(10,-0)-5,-0);
	glVertex3d(10, GetY(10,-40)-5,-40);
	glVertex3d(30, GetY(30,-40)-5,-40);
	glVertex3d(30, GetY(30,-0)-5,-0);*/
	/*glVertex3d(10, GetWorld(*phy)->GetYatXZ(10,-0,0),-0);
	glVertex3d(10, GetWorld(*phy)->GetYatXZ(10,-30,0),-30);
	glVertex3d(60, GetWorld(*phy)->GetYatXZ(60,-30,0),-30);
	glVertex3d(60, GetWorld(*phy)->GetYatXZ(60,-0,0),-0);*/
	/*glEnd();*/
	//glTranslated(0,0,-40);
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, red);

	//DWORD dt = GetTickCount()-t1;
	//needStep = 1; // удалить
	if(pause && needStep || !pause) 
	{
		glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, green);
		glutSolidSphere(0.4,15,15);
		needStep = false;
		DWORD t2 = GetTickCount();
		DWORD dt = t2-t1;
		t1 = t2;
		double tim = 25/1000.0;//dt/1000.0;
		
		vector<CollisionInfoOfSphere>  col_of_sp = phy->balls->inspection();
		phy->balls->all_calculation(col_of_sp, dt);

		int num_con = phy->balls->Count_sp();
		for(int i=0;i<num_con;i++)
		{
			phy->balls->MoveSphere(i, tim);
		}
		int num_qu = phy->balls->Count_quad();
		for(int i = 0;i<num_qu;i++)
		{
			//Quadrocopter control
			if(_tmp==6)
			{
				phy->balls->Get_quad(i)->SetForse(f1,f2,f3,f4);
			}
			phy->balls->MoveQuadrocopter(i, tim);
		}
		vector<CollisionInfo> col = phy->wor->inspections(phy->balls);
		phy->wor->Calculation(col,tim);
		for(int i = 0;i<col.size();i++)
		{
			if(col[i].qa_t)
			{
				Quadrocopter * qad = col[i].qa;
				qad->eng[0].F = (qad->eng[0].Position - qad->Position)*3000;
				qad->eng[1].F = (qad->eng[1].Position - qad->Position)*3000;
				qad->eng[2].F = (qad->eng[2].Position - qad->Position)*3000;
				qad->eng[3].F = (qad->eng[3].Position - qad->Position)*3000;
				qad->eng[0].SetRad(0.5);
				qad->eng[1].SetRad(0.5);
				qad->eng[2].SetRad(0.5);
				qad->eng[3].SetRad(0.5);
				phy->balls->Add(col[i].qa->eng[0]);
				phy->balls->Add(col[i].qa->eng[1]);
				phy->balls->Add(col[i].qa->eng[2]);
				phy->balls->Add(col[i].qa->eng[3]);
				qad->eng[0].Position = qad->eng[0].Position + (qad->eng[0].Position - qad->Position)*0.3;
				qad->eng[1].Position = qad->eng[1].Position + (qad->eng[1].Position - qad->Position)*0.3;
				qad->eng[2].Position = qad->eng[2].Position + (qad->eng[2].Position - qad->Position)*0.3;
				qad->eng[3].Position = qad->eng[3].Position + (qad->eng[3].Position - qad->Position)*0.3;
				qad->eng[0].F = (qad->eng[0].Position - qad->Position)*2000;
				qad->eng[1].F = (qad->eng[1].Position - qad->Position)*2000;
				qad->eng[2].F = (qad->eng[2].Position - qad->Position)*2000;
				qad->eng[3].F = (qad->eng[3].Position - qad->Position)*2000;
				phy->balls->Add(col[i].qa->eng[0]);
				phy->balls->Add(col[i].qa->eng[1]);
				phy->balls->Add(col[i].qa->eng[2]);
				phy->balls->Add(col[i].qa->eng[3]);
				qad->eng[0].Position = qad->eng[0].Position + (qad->eng[0].Position - qad->Position)*0.6;
				qad->eng[1].Position = qad->eng[1].Position + (qad->eng[1].Position - qad->Position)*0.6;
				qad->eng[2].Position = qad->eng[2].Position + (qad->eng[2].Position - qad->Position)*0.6;
				qad->eng[3].Position = qad->eng[3].Position + (qad->eng[3].Position - qad->Position)*0.6;
				qad->eng[0].F = (qad->eng[0].Position - qad->Position)*2000;
				qad->eng[1].F = (qad->eng[1].Position - qad->Position)*2000;
				qad->eng[2].F = (qad->eng[2].Position - qad->Position)*2000;
				qad->eng[3].F = (qad->eng[3].Position - qad->Position)*2000;
				phy->balls->Add(col[i].qa->eng[0]);
				phy->balls->Add(col[i].qa->eng[1]);
				phy->balls->Add(col[i].qa->eng[2]);
				phy->balls->Add(col[i].qa->eng[3]);
				phy->balls->Delete_qa(col[i].nom_qa);
			}
		}
	}
	else
	{
		glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, red);
		glutSolidSphere(0.4,15,15);
	}
	int num_obj = phy->balls->Count_sp();
	for(int i=0;i<num_obj;i++)
	{
		Sphere* tmp = phy->balls->Get_sp(i);
		glPushMatrix();
		glTranslated(tmp->Position.GetX(),tmp->Position.GetY(), tmp->Position.GetZ());
		glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, green);
		Draw(tmp->velo);
		/*glRotated(tmp->Angl.GetX(),0,0,1);
		glRotated(tmp->Angl.GetZ(),1,0,0);*/
		glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, red);
		glutSolidSphere(tmp->GetRad(),25,25);
		glPopMatrix();
	}
	int num_quad = phy->balls->Count_quad();
	for(int i = 0;i<num_quad;i++)
	{
		Quadrocopter* tmp = phy->balls->Get_quad(i);
		double r = tmp->GetRad();
		glPushMatrix();
		glTranslated(tmp->Position.GetX(),tmp->Position.GetY(), tmp->Position.GetZ());
		glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, green);
		Draw(tmp->velo);
		glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, blue);
		Draw(tmp->F/5);
		glPopMatrix();

		glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, red);
		glPushMatrix();
		glTranslated(tmp->eng[0].Position.GetX(),tmp->eng[0].Position.GetY(),tmp->eng[0].Position.GetZ());
		glutSolidSphere(tmp->eng[0].GetRad(),25,25);
		glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, blue);
		Draw(tmp->eng[0].F/5);
		glPopMatrix();
		glPushMatrix();
		glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, red);
		glTranslated(tmp->eng[1].Position.GetX(),tmp->eng[1].Position.GetY(),tmp->eng[1].Position.GetZ());
		glutSolidSphere(tmp->eng[1].GetRad(),25,25);
		glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, blue);
		Draw(tmp->eng[1].F/5);
		glPopMatrix();
		glPushMatrix();
		glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, red);
		glTranslated(tmp->eng[2].Position.GetX(),tmp->eng[2].Position.GetY(),tmp->eng[2].Position.GetZ());
		glutSolidSphere(tmp->eng[2].GetRad(),25,25);
		glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, blue);
		Draw(tmp->eng[2].F/5);
		glPopMatrix();
		glPushMatrix();
		glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, red);
		glTranslated(tmp->eng[3].Position.GetX(),tmp->eng[3].Position.GetY(),tmp->eng[3].Position.GetZ());
		glutSolidSphere(tmp->eng[3].GetRad(),25,25);
		glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, blue);
		Draw(tmp->eng[3].F/5);
		glPopMatrix();
		/*glRotated(tmp->Angl.GetX(),0,0,1);
		glRotated(tmp->Angl.GetZ(),1,0,0);*/
	}
	
	//t1 += dt;
	glPopMatrix();
	glPopMatrix();
	IFPS = IFPS + 1;
	glFlush();
	glutSwapBuffers();
}

int main(int argc, char **argv)
{
	//Vector_t T;
	//T.RunAll();
	setlocale(LC_ALL,"RUS");
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(SCENE_W, SCENE_H);
	glutCreateWindow("OpenGL тестовый мир");

	glutDisplayFunc(display);
	glutIdleFunc(idle);
	glutKeyboardFunc(keyboard);
	glutMouseFunc(mouseClick);
	glutMotionFunc(mouseMotion);
	glutReshapeFunc(reshape);
	glClearColor(0.0, 0.0, 0.0, 1.0);

	planes = new World();
	bal = new ContainerObjects();
	phy = new Fizika(*planes,*bal);
	StartDemo(_tmp);
	
	t1 = GetTickCount();

	glutMainLoop();
	
	delete phy;
	delete planes;
	return 0;
}
void StartDemo(int num)
{
	if (num >= 1 && num <= 6) 
	{
		Clear();
		f1=24.5;
		f2=24.5;
		f3=24.5;
		f4=24.5;
	}
	if (num == 1) Demo1();
	else if (num == 2) Demo2();
	else if (num == 3) Demo3();
	else if (num == 4) Demo4();
	else if (num == 5) Demo5();
	else if (num == 6) Demo6();
}
void Demo1()
{
	//отскок от трЄх плоскостей
	//пол
	//Vector v0[4] = {
	//	Vector(0,0,0),
	//	Vector(10,0,0),
	//	Vector(10,0,10),
	//	Vector(0,0,10),
	//};
	//Plane floor = Plane();
	//floor.SetPoints(v0, 4);

	////стенка1
	//Vector v1[4] = {
	//	Vector(10,0,0),
	//	Vector(15,5,0),
	//	Vector(15,5,10),
	//	Vector(10,0,10),
	//};
	//Plane wall = Plane();
	//wall.SetPoints(v1,4);

	////стенка2
	//Vector v2[4] = {
	//	Vector(0,0,0),
	//	Vector(-5,5,0),
	//	Vector(-5,5,10),
	//	Vector(0,0,10),
	//};
	//Plane wall2 = Plane();
	//wall2.SetPoints(v2,4);

	//planes->Add(floor);
	//planes->Add(wall);
	//planes->Add(wall2);
	Vector floor[5] = {
		Vector(10,0,0),
		Vector(10,0,10),
		Vector(5,0,5),
		Vector(0,0,10),
		Vector(0,0,0)};
	Plane f1 = Plane();
	f1.SetPoints(floor,5);
	planes->Add(f1);

	//Ball
	Sphere tmp = Sphere();
	tmp.Position = Vector(2,5,2);
	//tmp.Position = Vector(13,5,5);
	bal->Add(tmp);
	tmp.Position = Vector(5,5,7);
	bal->Add(tmp);
	tmp.Position = Vector(7,5,2);
	bal->Add(tmp);
}
void Demo2()
{
	//1 шарик падает сверху на второй
	
	//пол
	Vector f2[6] = {	Vector(0,0,-8),
					Vector(6.9282,0,-4),
					Vector(6.9282,0,4),
					Vector(0,0,8),
					Vector(-6.9282,0,4),
					Vector(-6.9282,0,-4) };
	
	Plane floor = Plane(f2[0],f2[1],f2[2]);
	floor.SetPoints(f2, 6);
	planes->Add(floor);
	Sphere tmp = Sphere();
	tmp.Position = Vector(1,1.7,3.5);
	bal->Add(tmp);
	tmp.Position = Vector(0,8,3);
	bal->Add(tmp);
}
void Demo3()
{
	//как биль€рд
	
	//пол
	Vector f2[6] = {	Vector(0,0,-8),
					Vector(6.9282,0,-4),
					Vector(6.9282,0,4),
					Vector(0,0,8),
					Vector(-6.9282,0,4),
					Vector(-6.9282,0,-4) };
	
	Plane floor = Plane(f2[0],f2[1],f2[2]);
	floor.SetPoints(f2, 6);
	planes->Add(floor);

	Sphere tmp = Sphere();
	tmp.Position = Vector(1,2,3);
	bal->Add(tmp);
	tmp.Position = Vector(0,1,-3);
	tmp.velo = Vector(0,0,15);
	bal->Add(tmp);
}
void Demo4()
{
	Vector r[4] = {	Vector(0,10,0),
					Vector(18,10,0),
					Vector(18,0,5),
					Vector(0,0,5)};
	Plane right = Plane(r[0],r[1],r[2]);
	right.SetPoints(r, 4);
	planes->Add(right);
	Vector l[4] = {	Vector(0,10,0),
					Vector(18,10,0),
					Vector(18,0,-5),
					Vector(0,0,-5)};
	Plane left = Plane(l[0],l[1],l[2]);
	left.SetPoints(l, 4);
	planes->Add(left);

	Sphere tmp = Sphere();
	tmp.Position = Vector(1,14,0.5);
	bal->Add(tmp);
	tmp.Position = Vector(4,14,-0.5);
	bal->Add(tmp);
	tmp.Position = Vector(7,14,0.5);
	bal->Add(tmp);
	tmp.Position = Vector(10,14,-0.5);
	bal->Add(tmp);
	tmp.Position = Vector(13,14,0.5);
	bal->Add(tmp);
	tmp.Position = Vector(16,13.8,-0.5);
	bal->Add(tmp);
}
void Demo5()
{
	Vector f1[4] = {Vector(0,6,0),
					Vector(6,6,0),
					Vector(6,6,10),
					Vector(0,6,10)};
	Plane floor1 = Plane();
	floor1.SetPoints(f1,4);

	Vector w1[4] = {Vector(6.01,3,0),
					Vector(6,6,0),
					Vector(6,6,10),
					Vector(6.01,3,10)};
	Plane wall1 = Plane();
	wall1.SetPoints(w1,4);

	Vector f2[4] = {Vector(6,3,0),
					Vector(12,3,0),
					Vector(12,3,10),
					Vector(6,3,10)};
	Plane floor2 = Plane();
	floor2.SetPoints(f2,4);

	Vector w2[4] = {Vector(12,0,0),
					Vector(12,0,10),
					Vector(12.01,3,10),
					Vector(12.01,3,0)};
	Plane wall2 = Plane();
	wall2.SetPoints(w2,4);

	Vector f3[4] = {Vector(12,0,0),
					Vector(20,0,0),
					Vector(20,0,10),
					Vector(12,0,10)};
	Plane floor3 = Plane();
	floor3.SetPoints(f3,4);

	Vector w3[4] = {Vector(20,0,0),
					Vector(20,0,10),
					Vector(20.01,5,10),
					Vector(20.01,5,0)};
	Plane wall3 = Plane();
	wall3.SetPoints(w3,4);
	
	Sphere tmp = Sphere();
	tmp.Position = Vector(2,7.5,3);
	tmp.velo = Vector(5,-5,0);
	bal->Add(tmp);

	planes->Add(floor1);
	planes->Add(floor2);
	planes->Add(floor3);
	planes->Add(wall1);
	planes->Add(wall2);
	planes->Add(wall3);
}
void Demo6()
{
	Vector v0[4] = {
		Vector(0,0,0),
		Vector(10,0,0),
		Vector(10,0,10),
		Vector(0,0,10),
	};
	Plane floor = Plane();
	floor.SetPoints(v0, 4);

	//стенка1
	Vector v1[4] = {
		Vector(10,0,0),
		Vector(15,5,0),
		Vector(15,5,10),
		Vector(10,0,10),
	};
	Plane wall = Plane();
	wall.SetPoints(v1,4);

	//стенка2
	Vector v2[4] = {
		Vector(0,0,10),
		Vector(-5,5,10),
		Vector(-5,5,0),
		Vector(0,0,0),
	};
	Plane wall2 = Plane();
	wall2.SetPoints(v2,4);

	planes->Add(floor);
	planes->Add(wall);
	planes->Add(wall2);

	//Quadrocopter
	Quadrocopter qu  = Quadrocopter(Vector(5,15,5));
	qu.SetForse(24.5,24.5,24.5,24.5); // 24.5 for static
	//for(int i =0;i<500;i++)
	//{
		bal->Add(qu);
	//}
}
void Clear()
{
	planes->Clear();
	bal->Clear();
}