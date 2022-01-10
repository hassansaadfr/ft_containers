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
    for (size_t i = 1; i < 10; i++)
    {
        m.insert(ft::make_pair(i,i));
    }
    std::map<int> z;
    nm::map<int, int>::iterator it = m.begin();
    // it++;
    // it++;
    it++;
    std::cout << m.max_size() << std::endl;
    m.clear();
}
