#include "../headers\Fizika.h"
Fizika::Fizika(World& w)
{
	n = 0.1;
	p = 1.2041;
	_g = 9.8;
	wor = &w;
	balls = ContainerObjects();
}
