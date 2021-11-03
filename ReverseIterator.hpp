#ifndef REVERSE_ITERATOR_H
# define REVERSE_ITERATOR_H

# include <iostream>
# include <cstddef>
#ifndef ITERATOR_INCLUDE
 #define ITERATOR_INCLUDE
 #include "Iterator.hpp"
#endif

# include "Utils.hpp"

namespace ft {
	template < class T,	bool B >
	class Iterator ;

	template <typename T, bool is_constant>
	class ReverseIterator
	{
		public:
			typedef std::ptrdiff_t																	difference_type;
			typedef T																				value_type;
			typedef typename ft::is_constant<is_constant, const value_type *, value_type *>::type	pointer;
			typedef typename ft::is_constant<is_constant, const value_type &, value_type &>::type	reference;
			typedef std::random_access_iterator_tag													iterator_category;

			/* Constructor */
			ReverseIterator(pointer ptr = 0): _ptr(ptr) {};
			/* Destructor */
			~ReverseIterator(void) {};

			/* Copy constructor */
			template <bool Any>
			ReverseIterator(const ft::Iterator<T, Any> & rhs): _ptr(rhs.base()) {}
			template < bool Any >
			ReverseIterator(const ReverseIterator<T, Any> & rhs)
			{
				this->_ptr = rhs.base();
			}

			/* Copy Assignation constructor */
			reference		operator=(reference rhs)
			{
				if (this != &rhs)
					this->_ptr = rhs.base();
				return *this;
			}

			/* Comparaisons Part */
			bool					operator==(ReverseIterator const &rhs) const { return (_ptr == rhs._ptr); };
			bool 					operator!=(ReverseIterator const &rhs) const { return (rhs._ptr != _ptr); }
			bool					operator<(ReverseIterator const &rhs) const { return (_ptr < rhs._ptr); };
			bool					operator>(ReverseIterator const &rhs) const { return (_ptr > rhs._ptr); };
			bool					operator<=(ReverseIterator const &rhs) const { return (_ptr <= rhs._ptr); };
			bool					operator>=(ReverseIterator const &rhs) const { return (_ptr >= rhs._ptr); };

			/* Increment Decrement Part */
			ReverseIterator&	operator++(void)
			{
				_ptr--;
				return *this;
			}
			ReverseIterator&	operator--(void)
			{
				_ptr++;
				return *this;
			}
			ReverseIterator	operator++(int)
			{
				ReverseIterator	old = *this;
				operator--();
				return old;
			}
			ReverseIterator	operator--(int)
			{
				ReverseIterator	old = *this;
				operator++();
				return old;
			}

			reference operator*(void) const { return *_ptr; }
			pointer operator->(void) const { return _ptr; }
			/* Arithmetic operations */
			ReverseIterator	operator+(difference_type const &rhs) const
			{
				return ReverseIterator(_ptr - rhs);
			}
			ReverseIterator	operator-(difference_type rhs)
			{
				return ReverseIterator(_ptr + rhs);
			}
			difference_type	operator-(ReverseIterator const &rhs)
			{
				return _ptr + rhs._ptr;
			}
			/* Compound assignement arithmetics operations */
			ReverseIterator&		operator+=(difference_type const &rhs)
			{
				_ptr -= rhs;
				return *(this);
			}

			ReverseIterator&	operator-=(difference_type rhs)
			{
				_ptr += rhs;
				return *this;
			}
			/* Offset dereference operator */
			ReverseIterator&	operator[](difference_type rhs)
			{
				return *(_ptr - rhs - 1);
			}

			pointer base(void) const { return _ptr; };
		private:
			pointer	_ptr;
	};
}

template<typename T>
ft::ReverseIterator<T, false> operator+(int offset, ft::ReverseIterator<T, false> & rhs) { return (ft::ReverseIterator<T, false>(rhs.base() - offset)); }
template<typename T>
ft::ReverseIterator<T, false> operator-(int offset, ft::ReverseIterator<T, false> & rhs) { return (ft::ReverseIterator<T, false>(rhs.base() + offset)); }

template <typename T>
bool operator!=(const ft::ReverseIterator<T, false>& lhs, const ft::ReverseIterator<T, true>& rhs) { return lhs.base() != rhs.base(); }


template <typename T>
bool					operator==(const ft::ReverseIterator<T, false>& lhs, const ft::ReverseIterator<T, true>& rhs) { return (lhs.base() == rhs.base()); };
template <typename T>
bool					operator<(const ft::ReverseIterator<T, false>& lhs, const ft::ReverseIterator<T, true>& rhs) { return (lhs.base() < rhs.base()); };
template <typename T>
bool					operator>(const ft::ReverseIterator<T, false>& lhs, const ft::ReverseIterator<T, true>& rhs) { return (lhs.base() > rhs.base()); };
template <typename T>
bool					operator<=(const ft::ReverseIterator<T, false>& lhs, const ft::ReverseIterator<T, true>& rhs) { return (lhs.base() <= rhs.base()); };
template <typename T>
bool					operator>=(const ft::ReverseIterator<T, false>& lhs, const ft::ReverseIterator<T, true>& rhs) { return (lhs.base() >= rhs.base()); };
#endif
