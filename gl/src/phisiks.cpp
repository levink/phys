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
	//считаем новые координаты объекта на основе его времени жизни и наших "физических" законов


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
	//считаем новые координаты объекта на основе его времени жизни и наших "физических" законов

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


//HDC        hDC=NULL;  // Приватный контекст устройства GDI
//HGLRC      hRC=NULL;  // Постоянный контекст рендеринга
//HWND       hWnd=NULL; // Сохраняет дескриптор окна
//HINSTANCE  hInstance; // Сохраняет экземпляр приложения
//
//GLuint  gmf;      // База списка отображения для фонта
//GLfloat  cnt1;     // Первый счетчик для передвижения и закрашивания текста
//GLfloat  cnt2;     // Второй счетчик для передвижения и закрашивания текста
// 
//bool  keys[256];      // Массив для работы с клавиатурой
//bool  active=TRUE;    // Флаг активации окна, по умолчанию = TRUE
//bool  fullscreen=TRUE;// Флаг полноэкранного режима
// 
//LRESULT  CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);  // Объявление WndProc
//
//GLvoid BuildFont(GLvoid)  // Построение нашего растрового шрифта
//{
//  HFONT  font;            // Идентификатор фонта
// 
//  base = glGenLists(96);  // Выделим место для 96 символов ( НОВОЕ )
// font = CreateFont(  -24,0,0,0,FW_BOLD,FALSE,        // Курсив
//        FALSE,        // Подчеркивание
//        FALSE,        // Перечеркивание        
//		 ANSI_CHARSET,      // Идентификатор набора символов
//		  OUT_TT_PRECIS,      // Точность вывода
//		  CLIP_DEFAULT_PRECIS,    // Точность отсечения
//		    ANTIALIASED_QUALITY,    // Качество вывода
//  FF_DONTCARE|DEFAULT_PITCH,  // Семейство и шаг
//   "Courier New"); 
// SelectObject(hDC, font);        // Выбрать шрифт, созданный нами ( НОВОЕ )
// 
//  wglUseFontBitmaps(hDC, 32, 96, base); // Построить 96 символов начиная с пробела ( НОВОЕ )
//}
//
//GLvoid KillFont(GLvoid)            // Удаление шрифта
//{
//   glDeleteLists(base, 96);        // Удаление всех 96 списков отображения ( НОВОЕ )
//}
//GLvoid glPrint(const char *fmt, ...)        // Заказная функция «Печати» GL
//{
//	 char    text[256];      // Место для нашей строки
//  va_list    ap; 
//  if (fmt == NULL)     // Если нет текста
//    return;            // Ничего не делать
// 
//  va_start(ap, fmt);           // Разбор строки переменных
//      vsprintf(text, fmt, ap); // И конвертирование символов в реальные коды
//  va_end(ap);   
//  glPushAttrib(GL_LIST_BIT);      // Протолкнуть биты списка отображения ( НОВОЕ )
//  glListBase(gmf - 32); 
//   glCallLists(strlen(text), GL_UNSIGNED_BYTE, text);// Текст списками отображения(НОВОЕ)
// glPopAttrib(); // Возврат битов списка отображения ( НОВОЕ )
//}

//int InitGL(GLvoid)            // Все начальные настройки OpenGL здесь
//{
//  glShadeModel(GL_SMOOTH);    // Разрешить плавное затенение
//  glClearColor(0.0f, 0.0f, 0.0f, 0.5f); // Черный фон
//  glClearDepth(1.0f);         // Установка буфера глубины
//  glEnable(GL_DEPTH_TEST);    // Разрешение теста глубины
//  glDepthFunc(GL_LEQUAL);     // Тип теста глубины
//  // Действительно хорошие вычисления перспективы
//  glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
//  BuildFont();            // Построить шрифт
//  return TRUE;            // Инициализация окончена
//}


 
