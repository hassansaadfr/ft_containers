#ifndef REVERSE_ITERATOR_H
# define REVERSE_ITERATOR_H

# include <iostream>
# include <cstddef>
#ifndef ITERATOR_INCLUDE
 #define ITERATOR_INCLUDE
 #include "RandomAccessIterator.hpp"
#endif

# include "Utils.hpp"

namespace ft {
	template < class T,	bool B >
	class Iterator ;

	template <typename T>
	class ReverseIterator
	{
		public:
			typedef T																iterator_type;
			typedef typename ft::iterator_traits<iterator_type>::difference_type	difference_type;
			typedef typename ft::iterator_traits<iterator_type>::pointer			pointer;
			typedef typename ft::iterator_traits<iterator_type>::reference			reference;
			typedef typename ft::iterator_traits<T>::iterator_category				iterator_category;
			typedef typename ft::iterator_traits<iterator_type>::value_type			value_type;
			/* Constructor */
			ReverseIterator(void): current() {};
			explicit ReverseIterator( iterator_type x ): current(x) {};
			/* Destructor */
			~ReverseIterator(void) {};
			/* Copy constructor */
			template< class U >
			ReverseIterator( const ReverseIterator<U>& other ): current(other.base()) {};
			/* Copy Assignation constructor */
			ReverseIterator&		operator=(const ReverseIterator& rhs)
			{
				if (this != &rhs)
					this->current = rhs.base();
				return (*this);
			}
			/* Increment Decrement Part */
			ReverseIterator&	operator--(void) { ++current; return *this; }
			ReverseIterator		operator--(int) { ReverseIterator old = *this; operator--(); return old; }
			ReverseIterator&	operator++(void) { --current; return *this; }
			ReverseIterator		operator++(int) { ReverseIterator old = *this; operator++(); return old; }
			reference			operator*(void) const { iterator_type tmp = current; return *(--tmp); }
			pointer				operator->(void) const { return &(operator*()); }
			/* Arithmetic operations */
			ReverseIterator		operator+(difference_type rhs) const { return ReverseIterator(current - rhs); }
			ReverseIterator		operator-(difference_type rhs) const { return ReverseIterator(base() + rhs); }
			difference_type		operator-(ReverseIterator const &r) { return r.base() - this->base(); }
			/* Compound assignement arithmetics operations */
			ReverseIterator&	operator+=(difference_type rhs) { current -= rhs; return *(this); }
			ReverseIterator&	operator-=(difference_type rhs) { current += rhs; return *this; }
			/* Offset dereference operator */
			reference			operator[](difference_type rhs) const { return *(current - rhs - 1); }
			iterator_type		base(void) const { return current; };
		protected:
			iterator_type		current;
	};

	template <class Iterator>
	ReverseIterator<Iterator> operator+(typename ReverseIterator<Iterator>::difference_type n, const ReverseIterator<Iterator>& rev_it) { return (rev_it + n); }
	template< class Iterator1, class Iterator2 >
	bool	operator==(const ReverseIterator<Iterator1>& lhs, const ReverseIterator<Iterator2>& rhs) { return (lhs.base() == rhs.base()); };
	template< class Iterator >
	bool	operator==(const ReverseIterator<Iterator>& lhs, const ReverseIterator<Iterator>& rhs) { return (lhs.base() == rhs.base()); };
	template< class Iterator1, class Iterator2 >
	bool 	operator!=(const ReverseIterator<Iterator1>& lhs, const ReverseIterator<Iterator2>& rhs) { return (lhs.base() != rhs.base()); }
	template< class Iterator >
	bool 	operator!=(const ReverseIterator<Iterator>& lhs, const ReverseIterator<Iterator>& rhs) { return (lhs.base() != rhs.base()); }
	template< class Iterator1, class Iterator2 >
	bool	operator<(const ReverseIterator<Iterator1>& lhs, const ReverseIterator<Iterator2>& rhs) { return (lhs.base() > rhs.base()); };
	template< class Iterator>
	bool	operator<(const ReverseIterator<Iterator>& lhs, const ReverseIterator<Iterator>& rhs) { return (lhs.base() > rhs.base()); };
	template< class Iterator1, class Iterator2 >
	bool	operator>(const ReverseIterator<Iterator1>& lhs, const ReverseIterator<Iterator2>& rhs) { return (lhs.base() < rhs.base()); };
	template< class Iterator >
	bool	operator>(const ReverseIterator<Iterator>& lhs, const ReverseIterator<Iterator>& rhs) { return (lhs.base() < rhs.base()); };
	template< class Iterator1, class Iterator2 >
	bool	operator<=(const ReverseIterator<Iterator1>& lhs, const ReverseIterator<Iterator2>& rhs) { return (lhs.base() >= rhs.base()); };
	template< class Iterator >
	bool	operator<=(const ReverseIterator<Iterator>& lhs, const ReverseIterator<Iterator>& rhs) { return (lhs.base() >= rhs.base()); };
	template< class Iterator1, class Iterator2 >
	bool	operator>=(const ReverseIterator<Iterator1>& lhs, const ReverseIterator<Iterator2>& rhs) { return (lhs.base() <= rhs.base()); };
	template< class Iterator >
	bool	operator>=(const ReverseIterator<Iterator>& lhs, const ReverseIterator<Iterator>& rhs) { return (lhs.base() <= rhs.base()); };
}

#endif
