#ifndef EXO_H
# define EXO_H

#include <iostream>

template <typename T>
struct foo {
	typedef T	type;
	type debug() { return a; }
	private:
		type a;
};


template<bool B, class T = void>
struct enable_if {};

template<class T>
struct enable_if<true, T> { typedef T type; };



template<class T>
struct is_pointer { static const bool value = false; };

template<class T>
struct is_pointer<T*> { static const bool value = true; };

template <class T, class U>
struct is_same { static const bool value = false; };


template <class T>
struct is_same<T, T> { static const bool value = true; };

template <typename T>
typename T::type	test(T val, typename enable_if<is_same< T, foo<int*> >::value>::type* = 0)
{
	std::cout << "ptr" << std::endl;
	return val.debug();
}

template <typename T>
int	test(T val, typename enable_if<!is_same< T, foo<int*> >::value>::type* = 0)
{
	(void)val;
	std::cout << "not ptr" << std::endl;
	return 0;
}

#endif
