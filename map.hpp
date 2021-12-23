#ifndef MAP_H
# define MAP_H

#include "Utils.hpp"
#include "RandomAccessIterator.hpp"
#include "RandomReverseAccessIterator.hpp"
#include "RedBlackTree.hpp"

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
			map():_alloc(NULL), _comp(NULL), _size(0) {};
			explicit map(const Compare& comp, const Allocator& alloc = Allocator()): _comp(comp), _alloc(alloc), _size(0) {};
			// map(const map& other);
			template< class InputIt >
			map(InputIt first, InputIt last, const Compare& comp = Compare(), const Allocator& alloc = Allocator())
			{
				_comp = comp;
				_alloc = alloc;
				while (first != last)
				{
					_bst.insert(*first);
					first++;
					_size++;
				}
			}
			~map();

		private:
			RedBlackTree<value_type>	_bst;
			allocator_type				_alloc;
			Compare						_comp;
			size_type					_size;
	};
}
#endif
