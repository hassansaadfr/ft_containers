#include "Exo.hpp"
#include <vector>
// #include "Vector.hpp"

int main(void)
{
	std::vector<int> v;

	v.push_back(42);
	v.push_back(4242);

	std::cout << v[0] << std::endl << v[1] << std::endl;
	v.assign(2, 42);
	std::cout << v[0] << std::endl << v[1] << std::endl;

	return 0;
}
