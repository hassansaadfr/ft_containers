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
    m.print();
    nm::map<int, int>::iterator it = m.begin();
    it++;
    std::cout << *it << std::endl;
    m.erase(it);
    // it++;
    m.print();

}
