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

	template <typename T>
	class ReverseIterator
	{
		public:
			typedef std::ptrdiff_t									difference_type;
			typedef T												iterator_type;
			typedef typename ft::iterator_traits<T>::pointer		pointer;
			typedef typename ft::iterator_traits<T>::reference		reference;
			typedef std::random_access_iterator_tag					iterator_category;

			/* Constructor */
			ReverseIterator(void);
			explicit ReverseIterator( iterator_type x ): current(x) {};
			/* Destructor */
			~ReverseIterator(void) {};

			/* Copy constructor */
			template< class U >
			ReverseIterator( const ReverseIterator<U>& other ): current(other.base()) {};

			/* Copy Assignation constructor */
			template< class U >
			ReverseIterator& operator=(const ReverseIterator<U>& rhs)
			{
				if (this != &rhs)
					this->current = rhs.base();
				return *this;
			}
			/* Comparaisons Part */
			bool					operator==(ReverseIterator const &rhs) const { return (current == rhs.current); };
			bool 					operator!=(ReverseIterator const &rhs) const { return (rhs.current != current); }
			bool					operator<(ReverseIterator const &rhs) const { return (current < rhs.current); };
			bool					operator>(ReverseIterator const &rhs) const { return (current > rhs.current); };
			bool					operator<=(ReverseIterator const &rhs) const { return (current <= rhs.current); };
			bool					operator>=(ReverseIterator const &rhs) const { return (current >= rhs.current); };

			/* Increment Decrement Part */
			ReverseIterator&	operator++(void)
			{
				--current;
				return *this;
			}
			ReverseIterator&	operator--(void)
			{
				++current;
				return *this;
			}
			ReverseIterator	operator++(int)
			{
				ReverseIterator	old = *this;
				operator++();
				return old;
			}
			ReverseIterator	operator--(int)
			{
				ReverseIterator	old = *this;
				operator--();
				return old;
			}

			reference operator*(void) const
			{
				iterator_type tmp = current;
				return *(--tmp);
			}
			pointer operator->(void) const { return &(operator*()); }
			/* Arithmetic operations */
			ReverseIterator	operator+(difference_type const &rhs) const
			{
				return ReverseIterator(current - rhs);
			}
			ReverseIterator	operator-(difference_type rhs)
			{
				return ReverseIterator(current + rhs);
			}
			difference_type	operator-(ReverseIterator const &rhs)
			{
				return current + rhs.current;
			}
			/* Compound assignement arithmetics operations */
			ReverseIterator&		operator+=(difference_type const &rhs)
			{
				current -= rhs;
				return *(this);
			}

			ReverseIterator&	operator-=(difference_type rhs)
			{
				current += rhs;
				return *this;
			}
			/* Offset dereference operator */
			ReverseIterator&	operator[](difference_type rhs)
			{
				return *(current - rhs - 1);
			}

			iterator_type base(void) const { return current; };
		protected:
			iterator_type	current;
	};
}

template<typename T>
ft::ReverseIterator<T> operator+(typename ft::ReverseIterator<T>::difference_type offset, ft::ReverseIterator<T> & rhs) { return (ft::ReverseIterator<T>(rhs.base() - offset)); }
template<typename T>
ft::ReverseIterator<T> operator-(typename ft::ReverseIterator<T>::difference_type offset, ft::ReverseIterator<T> & rhs) { return (ft::ReverseIterator<T>(rhs.base() + offset)); }



template <typename T>
bool					operator==(const ft::ReverseIterator<T>& lhs, const ft::ReverseIterator<T>& rhs) { return (lhs.base() == rhs.base()); };
template <typename T>
bool operator!=(const ft::ReverseIterator<T>& lhs, const ft::ReverseIterator<T>& rhs) { return !(lhs.base() == rhs.base()); }
template <typename T>
bool					operator<(const ft::ReverseIterator<T>& lhs, const ft::ReverseIterator<T>& rhs) { return (lhs.base() < rhs.base()); };
template <typename T>
bool					operator>(const ft::ReverseIterator<T>& lhs, const ft::ReverseIterator<T>& rhs) { return (lhs.base() > rhs.base()); };
template <typename T>
bool					operator<=(const ft::ReverseIterator<T>& lhs, const ft::ReverseIterator<T>& rhs) { return (lhs.base() <= rhs.base()); };
template <typename T>
bool					operator>=(const ft::ReverseIterator<T>& lhs, const ft::ReverseIterator<T>& rhs) { return (lhs.base() >= rhs.base()); };
#endif
