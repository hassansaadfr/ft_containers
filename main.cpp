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
	m.insert(ft::make_pair(10,12));
	m.insert(ft::make_pair(20,32));
	nm::map<int, int>::iterator it = m.begin();
	std::cout << it->first << std::endl;
	it++;
	std::cout << it->first << std::endl;

}
