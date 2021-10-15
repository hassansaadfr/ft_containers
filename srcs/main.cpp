#include "Exo.hpp"
#include <vector>

int main(void)
{
	int a = 42;
	foo<int> b;
	foo<int*> z;

	test(b);
	test(z);
	(void)a;
	return 0;
}
