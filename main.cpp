#include "map.hpp"

int main()
{
	ft::map<int, int> const mp;
	ft::map<int, int>::iterator it = mp.begin(); // <-- error expected
}
