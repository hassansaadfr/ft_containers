#ifndef ITERATOR_H
# define ITERATOR_H

# include <iostream>

namespace ft {
	template< class Iter >
	struct iterator_traits
	{
		typedef typename Iter::difference_type		difference_type;
		typedef typename Iter::value_type			value_type;
		typedef typename Iter::pointer				pointer;
		typedef typename Iter::reference			reference;
		typedef typename Iter::iterator_category	iterator_category;
	};

	template <typename T>
	class Iterator
	{
		public:
			typedef ptrdiff_t						difference_type;
			typedef T								value_type;
			typedef value_type *					pointer;
			typedef value_type &					reference;
			typedef std::random_access_iterator_tag	iterator_category;
			/* Constructor */
			Iterator(void) {};
			Iterator(pointer ptr): _ptr(ptr) {};
			/* Destructor */
			~Iterator(void) {};
			/* Copy constructor */
			Iterator(Iterator const &src)
			{
				this->_ptr = src->_ptr;
			}
			/* Copy Assignation constructor */
			Iterator&		operator=(Iterator const &rhs)
			{
				if (this != rhs)
					this->_ptr = rhs->_ptr;
				return *this;
			}

			/* Comparaisons Part */
			bool					operator==(Iterator const &rhs) { return (_ptr == rhs->_ptr); };
			bool					operator!=(Iterator const &rhs) { return (_ptr == rhs->_ptr); };
			bool					operator<(Iterator const &rhs) { return (_ptr < rhs->_ptr); };
			bool					operator>(Iterator const &rhs) { return (_ptr > rhs->_ptr); };
			bool					operator<=(Iterator const &rhs) { return (_ptr <= rhs->_ptr); };
			bool					operator>=(Iterator const &rhs) { return (_ptr >= rhs->_ptr); };

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

			/* Arithmetic operations */
			Iterator&	operator+(int const &rhs)
			{
				_ptr = _ptr + rhs;
				return *this;
			}
			Iterator&	operator+(Iterator const &rhs)
			{
				_ptr = _ptr + rhs._ptr;
				return *this;
			}
			Iterator&	operator-(int const &rhs)
			{
				_ptr = _ptr - rhs;
				return *this;
			}
			Iterator&	operator-(Iterator const &rhs)
			{
				_ptr = _ptr - rhs._ptr;
				return *this;
			}
			/* Compound assignement arithmetics operations */
			Iterator&	operator+=(int const &rhs)
			{
				_ptr = _ptr + rhs;
				return *this;
			}
			Iterator&	operator+=(Iterator const &rhs)
			{
				_ptr = _ptr + rhs._ptr;
				return *this;
			}
			Iterator&	operator-=(int const &rhs)
			{
				_ptr = _ptr - rhs;
				return *this;
			}
			Iterator&	operator-=(Iterator const &rhs)
			{
				_ptr = _ptr - rhs._ptr;
				return *this;
			}

			/* Offset dereference operator */
			Iterator&	operator[](int const &rhs)
			{
				_ptr = _ptr + rhs;
				return *this;
			}
		private:
			pointer	_ptr;
	};

}

#endif
