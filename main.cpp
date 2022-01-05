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
// template <typename T>
// void	rb_three_print_desc(nm::RedBlackTree<T> three)
// {
// 	ft::RedBlackTree<int>::node_ptr max = three.maximum(three.getRoot());
// 	while (max != NULL)
// 	{
// 		std::cout << max->data << std::endl;
// 		max = three.predecessor(max);
// 	}
// }

// template <typename T>
// void	rb_three_print_asc(nm::RedBlackTree<T> three)
// {
// 	ft::RedBlackTree<int>::node_ptr min = three.minimum(three.getRoot());
// 	while (min != NULL)
// 	{
// 		std::cout << min->data << std::endl;
// 		min = three.successor(min);
// 	}
// }

int main()
{
    nm::map<int, int> m;
    m.insert(ft::make_pair(10,12));
    m.insert(ft::make_pair(20,32));
    m.insert(ft::make_pair(42,34));
    m.print();
    nm::map<int, int>::iterator it = m.begin();

    std::cout << it->first << std::endl;

	// nm::RedBlackTree<int> three;
	// three.insert(100);
	// three.insert(1000);
	// three.insert(1);
	// rb_three_print_desc<int>(three);
	// rb_three_print_asc<int>(three);
}
// ft::RedBlackTree<ft::pair<const char, int>, ft::less<char>, std::allocator<ft::pair<const char, int> > >::node_ptr
// ft::LegacyBidirectionalIterator<ft::Node<ft::pair<const char, int>, ft::RedBlackTree<ft::pair<const char, int>, ft::less<char>, std::allocator<ft::pair<const char, int> > > >, true>::pointer
