#include <iostream>
#include "RedBlackTree.hpp"
#include "Utils.hpp"
#include "map.hpp"
#include <iostream>
#include <map>

namespace nm = ft;

int main()
{

    nm::RedBlackTree<ft::pair<int, int> > m;
    for (size_t i = 0; i < 10; i++)
    {
        m.insert(ft::make_pair(i,i));
    }
    nm::RedBlackTree<ft::pair<int, int> > m2(m);

    m.printTree();
    m2.printTree();
}
