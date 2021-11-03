#ifndef ITERATOR_H
# define ITERATOR_H

# include <iostream>
# include <cstddef>
# include "Utils.hpp"

#ifndef REVERSE_INCLUDE
 #define REVERSE_INCLUDE
 #include "ReverseIterator.hpp"
#endif

namespace ft {
	template < class T, bool B >
	class ReverseIterator;

	template< class Iter >
	struct iterator_traits
	{
		typedef typename Iter::difference_type														difference_type;
		typedef typename Iter::value_type															value_type;
		typedef typename Iter::pointer																pointer;
		typedef typename Iter::reference															reference;
		typedef typename Iter::iterator_category													iterator_category;
	};

	template <typename T, bool is_constant>
	class Iterator
	{
		public:
			typedef std::ptrdiff_t																	difference_type;
			typedef T																				value_type;
			typedef typename ft::is_constant<is_constant, const value_type *, value_type *>::type	pointer;
			typedef typename ft::is_constant<is_constant, const value_type &, value_type &>::type	reference;
			typedef std::random_access_iterator_tag													iterator_category;

			/* Constructor */
			Iterator(pointer ptr = 0): _ptr(ptr) {};
			/* Destructor */
			~Iterator(void) {};
			/* Copy constructor */
			template < bool is_const >
			Iterator(const Iterator<T, is_const> & rhs)
			{
				this->_ptr = rhs.base();
			}
			// explicit Iterator(const ReverseIterator<T, false> & rhs): _ptr(rhs.base()) {}

			/* Copy Assignation constructor */
			reference		operator=(reference rhs)
			{
				if (this != &rhs)
					this->_ptr = rhs.base();
				return *this;
			}

			/* Comparaisons Part */
			bool					operator==(Iterator const &rhs) const { return (_ptr == rhs._ptr); };
			bool 					operator!=(Iterator const &rhs) const { return (rhs._ptr != _ptr); }
			bool					operator<(Iterator const &rhs) const { return (_ptr < rhs._ptr); };
			bool					operator>(Iterator const &rhs) const { return (_ptr > rhs._ptr); };
			bool					operator<=(Iterator const &rhs) const { return (_ptr <= rhs._ptr); };
			bool					operator>=(Iterator const &rhs) const { return (_ptr >= rhs._ptr); };

			/* Increment Decrement Part */
			Iterator&	operator++(void)
			{
				_ptr++;
				return *this;
			}
			Iterator&	operator--(void)
			{
				_ptr--;
				return *this;
			}
			Iterator	operator++(int)
			{
				Iterator	old = *this;
				operator++();
				return old;
			}
			Iterator	operator--(int)
			{
				Iterator	old = *this;
				operator--();
				return old;
			}

			reference operator*(void) const { return *_ptr; }
			pointer operator->(void) const { return _ptr; }
			/* Arithmetic operations */
			Iterator	operator+(difference_type const &rhs) const
			{
				return Iterator(_ptr + rhs);
			}
			Iterator	operator-(difference_type rhs)
			{
				return Iterator(_ptr - rhs);
			}
			difference_type	operator-(Iterator const &rhs)
			{
				return _ptr - rhs._ptr;
			}
			/* Compound assignement arithmetics operations */
			Iterator&		operator+=(difference_type const &rhs)
			{
				_ptr += rhs;
				return *(this);
			}

			Iterator&	operator-=(difference_type rhs)
			{
				_ptr -= rhs;
				return *this;
			}
			/* Offset dereference operator */
			reference	operator[](difference_type rhs)
			{
				return *(_ptr + rhs);
			}

			pointer base(void) const { return _ptr; };
		private:
			pointer	_ptr;
	};
}

template<typename T>
ft::Iterator<T, false> operator+(int offset, ft::Iterator<T, false> & rhs) { return (ft::Iterator<T, false>(rhs.base() + offset)); }
template<typename T>
ft::Iterator<T, false> operator-(int offset, ft::Iterator<T, false> & rhs) { return (ft::Iterator<T, false>(rhs.base() - offset)); }

template <typename T>
bool operator!=(const ft::Iterator<T, false>& lhs, const ft::Iterator<T, true>& rhs) { return lhs.base() != rhs.base(); }


template <typename T>
bool					operator==(const ft::Iterator<T, false>& lhs, const ft::Iterator<T, true>& rhs) { return (lhs.base() == rhs.base()); };
template <typename T>
bool					operator<(const ft::Iterator<T, false>& lhs, const ft::Iterator<T, true>& rhs) { return (lhs.base() < rhs.base()); };
template <typename T>
bool					operator>(const ft::Iterator<T, false>& lhs, const ft::Iterator<T, true>& rhs) { return (lhs.base() > rhs.base()); };
template <typename T>
bool					operator<=(const ft::Iterator<T, false>& lhs, const ft::Iterator<T, true>& rhs) { return (lhs.base() <= rhs.base()); };
template <typename T>
bool					operator>=(const ft::Iterator<T, false>& lhs, const ft::Iterator<T, true>& rhs) { return (lhs.base() >= rhs.base()); };
#endif
