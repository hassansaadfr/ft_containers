#ifndef LEGACY_BIDIRECTIONAL_ITERATOR_HPP
# define LEGACY_BIDIRECTIONAL_ITERATOR_HPP

# include <iostream>
# include <cstddef>
# include "Utils.hpp"

#ifndef REVERSE_BIDIRECTIONAL_INCLUDE
 #define REVERSE_BIDIRECTIONAL_INCLUDE
 #include "LegacyReverseBidirectionalIterator.hpp"
#endif

namespace ft {
	template < class T>
	class LegacyReverseBidirectionalIterator;
	template <typename T, bool is_constant>
	class LegacyBidirectionalIterator
	{
		public:
			typedef std::ptrdiff_t																						difference_type;
			typedef T																									value_type;
			typedef typename ft::is_constant<is_constant, const typename T::value_type, typename T::value_type >::type	pair_type;
			typedef typename ft::is_constant<is_constant, const value_type *, value_type * >::type						pointer;
			typedef typename ft::is_constant<is_constant, const value_type &, value_type &>::type						reference;
			typedef ft::bidirectional_iterator_tag																		iterator_category;

			/* Constructor */
			LegacyBidirectionalIterator(pointer ptr = 0): _ptr(ptr) {};
			/* Destructor */
			~LegacyBidirectionalIterator(void) {};
			/* Copy constructor */
			template < bool is_const >
			LegacyBidirectionalIterator(const LegacyBidirectionalIterator<T, is_const> & rhs): _ptr(rhs.base()) {}

			/* Copy Assignation constructor */
			LegacyBidirectionalIterator&	operator=(LegacyBidirectionalIterator const &rhs)
			{
				if (this != &rhs)
				{
					this->_ptr = rhs.base();
				}
				return *this;
			}

			/* Comparaisons Part */
			bool							operator==(LegacyBidirectionalIterator const &rhs) const { return (_ptr == rhs._ptr); };
			bool 							operator!=(LegacyBidirectionalIterator const &rhs) const { return (rhs._ptr != _ptr); }
			bool							operator<(LegacyBidirectionalIterator const &rhs) const { return (_ptr < rhs._ptr); };
			bool							operator>(LegacyBidirectionalIterator const &rhs) const { return (_ptr > rhs._ptr); };
			bool							operator<=(LegacyBidirectionalIterator const &rhs) const { return (_ptr <= rhs._ptr); };
			bool							operator>=(LegacyBidirectionalIterator const &rhs) const { return (_ptr >= rhs._ptr); };

			/* Increment Decrement Part */
			LegacyBidirectionalIterator&	operator++(void)
			{
				 _ptr++; return *this;
			}
			LegacyBidirectionalIterator&	operator--(void) { _ptr--; return *this; }
			LegacyBidirectionalIterator		operator++(int) { LegacyBidirectionalIterator	old = *this; operator++(); return old; }
			LegacyBidirectionalIterator		operator--(int) { LegacyBidirectionalIterator	old = *this; operator--(); return old; }
			pair_type&						operator*(void) const { return (_ptr->data); }
			pair_type*						operator->(void) const { return &(operator*()); }
			/* Offset dereference operator */
			reference						operator[](difference_type rhs) { return *(_ptr + rhs); }
			pointer							base(void) const { return _ptr; };
		private:
			pointer							_ptr;
	};
}

template <typename T>
bool					operator!=(const ft::LegacyBidirectionalIterator<T, false>& lhs, const ft::LegacyBidirectionalIterator<T, true>& rhs) { return lhs.base() != rhs.base(); }
template <typename T>
bool					operator==(const ft::LegacyBidirectionalIterator<T, false>& lhs, const ft::LegacyBidirectionalIterator<T, true>& rhs) { return (lhs.base() == rhs.base()); };
// template<typename T>
// ft::LegacyBidirectionalIterator<T, false>	operator+(typename ft::LegacyBidirectionalIterator<T, false>::difference_type offset, ft::LegacyBidirectionalIterator<T, false> & rhs) { return (ft::LegacyBidirectionalIterator<T, false>(rhs.base() + offset)); }
// template<typename T>
// ft::LegacyBidirectionalIterator<T, false>	operator-(typename ft::LegacyBidirectionalIterator<T, false>::difference_type offset, ft::LegacyBidirectionalIterator<T, false> & rhs) { return (ft::LegacyBidirectionalIterator<T, false>(rhs.base() - offset)); }
template <typename T>
bool					operator<(const ft::LegacyBidirectionalIterator<T, false>& lhs, const ft::LegacyBidirectionalIterator<T, true>& rhs) { return (lhs.base() < rhs.base()); };
template <typename T>
bool					operator>(const ft::LegacyBidirectionalIterator<T, false>& lhs, const ft::LegacyBidirectionalIterator<T, true>& rhs) { return (lhs.base() > rhs.base()); };
template <typename T>
bool					operator<=(const ft::LegacyBidirectionalIterator<T, false>& lhs, const ft::LegacyBidirectionalIterator<T, true>& rhs) { return (lhs.base() <= rhs.base()); };
template <typename T>
bool					operator>=(const ft::LegacyBidirectionalIterator<T, false>& lhs, const ft::LegacyBidirectionalIterator<T, true>& rhs) { return (lhs.base() >= rhs.base()); };
#endif