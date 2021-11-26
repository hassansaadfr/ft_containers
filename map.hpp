#ifndef MAP_H
# define MAP_H

#include "Utils.hpp"
#include "Iterator.hpp"
#include "ReverseIterator.hpp"

namespace ft {
	template< class Key, class T, class Compare = ft::less<Key>, class Allocator = std::allocator<std::pair<const Key, T> > >
	class map {
		public:
			typedef Key									key_type;
			typedef T									mapped_type;
			typedef ft::pair<const Key, T>				value_type;
			typedef std::size_t							size_type;
			typedef std::ptrdiff_t						difference_type;
			typedef Compare								key_compare;
			typedef Allocator							allocator_type;
			typedef value_type&							reference;
			typedef const value_type&					const_reference;
			typedef typename Allocator::pointer			pointer;
			typedef typename Allocator::const_pointer	const_pointer;
			typedef Iterator<T, false>					iterator;
			typedef Iterator<T, true>					const_iterator;
			typedef ReverseIterator<iterator>			reverse_iterator;
			typedef ReverseIterator<const_iterator>		const_reverse_iterator;

			/* Constructors */
			map();
			explicit map(const Compare& comp, const Allocator& alloc = Allocator());
			map(const map& other);
	};
}
#endif
