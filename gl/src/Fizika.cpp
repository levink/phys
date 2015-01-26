#include "../headers\Fizika.h"
Fizika::Fizika(StaticWorld& sw, DynamicWorld& dw)
	:planes(sw), balls(dw)
{
	n = 0.1;
	p = 1.2041;
	_g = 9.8;
}

void Fizika::MoveObject(BaseObject * obj, double t_sec)
{
	//считаем новые координаты объекта на основе его времени жизни и наших "физических" законов
	const double PI = 3.1415926;

	Vector Ft = Vector(0,-obj->m * _g,0); //+ F1 + F2 + ...
	//Vector Ftr = - (obj->velo /*> obj->velo*/ * p / 2) *  n * 3.14;
	Vector F = obj->F /*+ Ftr*/;	// + F1 + F2 + ...;
	Vector a = obj->F / obj->m;
	Vector v = obj->velo + a*t_sec; 
	Vector x = obj->Position + obj->velo*t_sec + (a*t_sec*t_sec)/2; 

	obj->accel = a;
	obj->velo = v;
	obj->Position = x;
	obj->F = Ft;

	//planes.Test(obj,1,t_sec); // 0.975

	/*double l = obj->GetRad() * 2 * PI;
	obj->Angl  = ( (obj->w * t_sec) / l) * 360 + obj->Angl;
	if(obj->Angl.GetX() > 360 || obj->Angl.GetX() < -360)
		obj->Angl.SetX(0);
	if(obj->Angl.GetY() > 360 || obj->Angl.GetY() < -360)
		obj->Angl.SetY(0);
	if(obj->Angl.GetZ() > 360 || obj->Angl.GetZ() < -360)
		obj->Angl.SetZ(0);*/
}

void Fizika::FindCollisions()
{
	//planes.inspections(balls, collision);

	//for debug!
	Collision* tmp = new Collision();
	tmp->sp = balls.Get(0);
	tmp->plane = planes.Get(0);
	tmp->type = CollisionType::WITH_PLANE;
	collision.insert(collision.end(), *tmp);
}
void Fizika::ParseCollision(double dt)
{
	//double res = 1.0;

	//for(int i = 0; i < collision.size(); i++)
	//{
	//	Collision* tmp = &(this->collision[i]);
	//	if(tmp->type == CollisionType::WITH_POINT)
	//	{
	//		tmp->sp->calculation(*tmp->point, res, dt);
	//	}
	//	if(tmp->type == CollisionType::WITH_LINE)
	//	{
	//		tmp->sp->calculation(*tmp->line, res, dt);
	//	}
	//	if(tmp->type == CollisionType::WITH_PLANE)
	//	{
	//		Sphere* s = tmp->sp; 
	//		s->calculation(*tmp->plane, res, dt);
	//	}

	//}
}