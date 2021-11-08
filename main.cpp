#include "vector.hpp"
#include <iterator>
#include "Iterator.hpp"
#include <vector>
#include <list>


template < typename T >
void	print_vector(T begin, T end)
{
	for (; begin != end ; begin++)
		std::cout << *begin << std::endl;
}


#define TESTED_TYPE int

int		main(void)
{
	std::list<TESTED_TYPE> lst;
	std::list<TESTED_TYPE>::iterator lst_it;
	for (int i = 1; i < 5; ++i)
		lst.push_back(i * 3);

	ft::vector<TESTED_TYPE> vct(lst.begin(), lst.end());
	std::vector<TESTED_TYPE> vct2(lst.begin(), lst.end());



	vct.insert(vct.end(), lst.rbegin(), lst.rend());
	vct2.insert(vct2.end(), lst.rbegin(), lst.rend());
	// std::cout << "+++++++++++++" << std::endl;
	// std::cout << "STL" << std::endl;
	// print_vector(vct2.begin(), vct2.end());
	// std::cout << "My vector" << std::endl;
	// print_vector(vct.begin(), vct.end());
	// std::cout << "+++++++++++++" << std::endl;

	// std::cout << *vct.rbegin() << std::endl;
	// std::cout << *vct2.rbegin() << std::endl;

	return (0);
}
