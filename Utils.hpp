#ifndef UTILS_H
# define UTILS_H

# include <iostream>

namespace ft {
	template< class Iter >
	struct iterator_traits
	{
		typedef typename Iter::difference_type														difference_type;
		typedef typename Iter::value_type															value_type;
		typedef typename Iter::pointer																pointer;
		typedef typename Iter::reference															reference;
		typedef typename Iter::iterator_category													iterator_category;
	};
	template<bool B, class T = void>
	struct enable_if {};

	template<class T>
	struct enable_if<true, T> { typedef T type; };

	template <bool isConstant, typename const_type, typename notConst_type>
	struct is_constant {};

	template <typename const_type, typename notConst_type>
	struct is_constant<true, const_type, notConst_type> {
		typedef const_type		type;
	};
	template <typename const_type, typename notConst_type>
	struct is_constant<false, const_type, notConst_type> {
		typedef notConst_type	type;
	};


	template <typename T>
	struct is_integral { static const bool value = false; };
	template <>
	struct is_integral<bool> { static const bool value = true; };
	template <>
	struct is_integral<char> { static const bool value = true; };
	template <>
	struct is_integral<float> { static const bool value = true; };
	template <>
	struct is_integral<short> { static const bool value = true; };
	template <>
	struct is_integral<int> { static const bool value = true; };
	template <>
	struct is_integral<long> { static const bool value = true; };
	template <>
	struct is_integral<long long> { static const bool value = true; };
	template <>
	struct is_integral<unsigned char> { static const bool value = true; };
	template <>
	struct is_integral<unsigned short> { static const bool value = true; };
	template <>
	struct is_integral<unsigned int> { static const bool value = true; };
	template <>
	struct is_integral<unsigned long> { static const bool value = true; };
	template <>
	struct is_integral<unsigned long long> { static const bool value = true; };

	template <class InputIterator1, class InputIterator2>
	bool lexicographical_compare(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, InputIterator2 last2)
	{
		while (first1!=last1)
		{
			if (first2==last2 || *first2<*first1)
				return false;
			else if (*first1 < *first2)
				return true;
			++first1;
			++first2;
		}
		return (first2 != last2);
	}

	template < class T >
	typename ft::iterator_traits<T>::difference_type	distance(T first, T last)
	{
		typename ft::iterator_traits<T>::difference_type result = 0;
		while (first != last)
		{
			++first;
			++result;
		}
		return result;
	}

};

#endif
