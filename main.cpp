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

    // loop to insert make_pair 1..10
    for (int i = 1; i <= 10; i++)
        m.insert(nm::make_pair(i, i));


    nm::map<int, int>::iterator it = m.end();

    std::cout << *((--(--it))--) << std::endl;
    std::cout << *it-- << std::endl;
    std::cout << *it-- << std::endl;
    std::cout << *it-- << std::endl;
    std::cout << *it-- << std::endl;
    std::cout << *it-- << std::endl;



}
