#ifndef ITERATOR_H
# define ITERATOR_H

# include <iostream>
# include <cstddef>
# include "Utils.hpp"

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

	template <typename T, bool is_constant>
	class Iterator
	{
		public:
			typedef ptrdiff_t																		difference_type;
			typedef T																				value_type;
			typedef typename ft::is_constant<is_constant, const value_type *, value_type *>::type	pointer;
			typedef typename ft::is_constant<is_constant, const value_type &, value_type &>::type	reference;
			typedef std::random_access_iterator_tag													iterator_category;

			/* Constructor */
			Iterator(void) {};
			Iterator(pointer ptr): _ptr(ptr) {};
			/* Destructor */
			~Iterator(void) {};
			/* Copy constructor */
			Iterator(Iterator const &src): _ptr(src._ptr) {};

			/* Copy Assignation constructor */
			Iterator&		operator=(Iterator const &rhs)
			{
				if (this != &rhs)
					this->_ptr = rhs._ptr;
				return *this;
			}

			/* Comparaisons Part */
			bool					operator==(Iterator const &rhs) { return (_ptr == rhs._ptr); };
			bool					operator!=(Iterator const &rhs) { return (_ptr != rhs._ptr); };
			bool					operator<(Iterator const &rhs) { return (_ptr < rhs._ptr); };
			bool					operator>(Iterator const &rhs) { return (_ptr > rhs._ptr); };
			bool					operator<=(Iterator const &rhs) { return (_ptr <= rhs._ptr); };
			bool					operator>=(Iterator const &rhs) { return (_ptr >= rhs._ptr); };

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

			reference	operator*(void) const { return *_ptr; }
			/* Arithmetic operations */
			Iterator	operator+(difference_type rhs)
			{
				return Iterator(_ptr + rhs);
			}
			difference_type	operator+(Iterator const &rhs)
			{
				return _ptr + rhs._ptr;
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
			Iterator&	operator+=(difference_type rhs)
			{
				return Iterator(_ptr + rhs);
			}
			difference_type	operator+=(Iterator const &rhs)
			{
				return _ptr + rhs._ptr;
			}
			Iterator&	operator-=(difference_type rhs)
			{
				return Iterator(_ptr - rhs);
			}
			difference_type	operator-=(Iterator const &rhs)
			{
				return _ptr - rhs._ptr;
			}

			/* Offset dereference operator */
			reference	operator[](difference_type rhs)
			{
				return *(_ptr + rhs);
			}
		private:
			pointer	_ptr;
	};

}

#endif
