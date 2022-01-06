#include <iostream>
#include "RedBlackTree.hpp"
#include "Utils.hpp"
#include "map.hpp"
#include <iostream>
#include <map>

namespace nm = ft;

int main()
{

    nm::map<int, int> m;
    for (size_t i = 0; i < 10; i++)
    {
        m.insert(ft::make_pair(i,i));
    }
    nm::map<int, int>::const_iterator it = m.begin();
    it++;
    std::cout << (*it).first << std::endl;
}
