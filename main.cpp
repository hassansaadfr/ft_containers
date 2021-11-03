#include "vector.hpp"
#include <iterator>
#include "Iterator.hpp"
#include <vector>

int main(void)
{
	ft::vector<int> v;

	v.push_back(42);
	v.push_back(43);
	v.push_back(44);
	v.push_back(45);


	for (ft::vector<int>::iterator i = v.begin(); i < v.end(); i++)
	{
		std::cout << *i << std::endl;
	}


	return 0;
}
