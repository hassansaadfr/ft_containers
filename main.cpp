// constructing maps
#include <iostream>
// #include <map>

// bool fncomp (char lhs, char rhs) {return lhs<rhs;}

// struct classcomp {
//   bool operator() (const char& lhs, const char& rhs) const
//   {return lhs<rhs;}
// };

// int main ()
// {
//   std::map<char,int> first;

//   first['a']=10;
//   first['b']=30;
//   first['c']=50;
//   first['d']=70;

//   std::map<char,int> second (first.begin(),first.end());

//   std::map<char,int> third (second);

//   std::map<char,int,classcomp> fourth;                 // class as Compare

//   bool(*fn_pt)(char,char) = fncomp;
//   std::map<char,int,bool(*)(char,char)> fifth (fn_pt); // function pointer as Compare

//   return 0;
// }

#include "RedBlackTree.hpp"
#include "Utils.hpp"
#include "map.hpp"
#include <iostream>
#include <map>

namespace nm = ft;

int main()
{

    nm::map<int, int> m;

    std::cout << m.size() << std::endl;
    m.insert(nm::make_pair(1, 1));
    std::cout << m.size() << std::endl;
    m.insert(nm::make_pair(2, 2));
    std::cout << m.size() << std::endl;
    m.insert(nm::make_pair(3, 3));
    std::cout << m.size() << std::endl;

    nm::map<int, int>::iterator it = m.begin();
    nm::map<int, int>::iterator ite = m.end();

    for (; it != ite; it++)
    {
        std::cout << it->first << " " << it->second << std::endl;
    }
//
//    std::cout << ite->first << " " << ite->second << std::endl;

	// nm::RedBlackTree<int> three;
	// three.insert(100);
	// three.insert(1000);
	// three.insert(1);
	// rb_three_print_desc<int>(three);
	// rb_three_print_asc<int>(three);
}
