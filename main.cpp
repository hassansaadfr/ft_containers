#include "vector.hpp"
#include <iterator>
#include "Iterator.hpp"
#include <vector>

int main(void)
{
	ft::vector<int> v;
	std::vector<int> vv;

	v.push_back(42);
	v.push_back(43);
	v.push_back(44);

	v.insert(v.begin(), 1010);
	ft::vector<int>::iterator l = v.insert(v.end(), 1111);
	v.insert(l + 1, 8888);
	v.push_back(45);
	ft::vector<int>::iterator it = v.begin();

	// std::cout << *it << std::endl;

	for (ft::vector<int>::iterator i = v.begin(); i < v.end(); i++)
	{
		std::cout << *i << std::endl;
	}


	return 0;
}
