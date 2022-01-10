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
	template <typename T, bool is_constant, class Compare>
	class LegacyBidirectionalIterator
	{
		public:
			typedef std::ptrdiff_t																						difference_type;
			typedef T																									value_type;
			typedef typename T::node_ptr																				node_ptr;
			typedef typename ft::is_constant<is_constant, const typename T::value_type, typename T::value_type >::type	pair_type;
			typedef typename ft::is_constant<is_constant, const typename T::node_ptr, typename T::node_ptr >::type		pointer;
			typedef typename ft::is_constant<is_constant, const value_type &, T &>::type								reference;
			typedef ft::bidirectional_iterator_tag																		iterator_category;

			/* Constructor */
			LegacyBidirectionalIterator(const Compare& comp = Compare()): _ptr(), _last(), _comp(comp) {}
			LegacyBidirectionalIterator(T* ptr, T* last, const Compare& comp = Compare())
			:
				_ptr(ptr),
				_last(last),
				_comp(comp)
			{}
			/* Destructor */
			~LegacyBidirectionalIterator(void) {};
			/* Copy constructor */
			template < bool is_const >
			LegacyBidirectionalIterator(const LegacyBidirectionalIterator<T, is_const, Compare> & rhs): _ptr(rhs.base()), _last(rhs.end()), _comp(Compare()) {}

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
				_ptr = successor(_ptr);
				return *this;
			}
			LegacyBidirectionalIterator&	operator--(void) { _ptr = predecessor(_ptr); return *this; }
			LegacyBidirectionalIterator		operator++(int) { LegacyBidirectionalIterator	old = *this; operator++(); return old; }
			LegacyBidirectionalIterator		operator--(int) { LegacyBidirectionalIterator	old = *this; operator--(); return old; }
			pair_type&						operator*(void) const { return (_ptr->data); }
			pair_type*						operator->(void) const { return &(operator*()); }
			/* Offset dereference operator */
			reference						operator[](difference_type rhs) { return *(_ptr + rhs); }
			pointer							base(void) const { return _ptr; };
			pointer							end(void) const { return _last; };
		private:
			node_ptr	_ptr;
			node_ptr	_last;
			Compare		_comp;

			node_ptr minimum(node_ptr node) const {
                while (node && node->left != _last)
                    node = node->left;
                return !node ? _last : node;
            }

            node_ptr maximum(node_ptr node) const {
                while (node && node->right != _last)
                    node = node->right;
                return !node ? _last : node;
            }

            node_ptr successor(node_ptr x) const {
                if (x == _last)
                    return (minimum(x));
                if (x->right != _last) {
                    return minimum(x->right);
                }

                node_ptr y = x->parent;
                while (y && x && y != _last && x == y->right) {
                    x = y;
                    y = y->parent;
                }
                return !y ? _last : y ;
            }

            node_ptr predecessor(node_ptr x) const {
                if (x == _last)
                    return (maximum(x));

                if (x->left != _last) {
                    return maximum(x->left);
                }

                node_ptr y = x->parent;
                while (y && x && y != _last && x == y->left) {
                    x = y;
                    if (y->parent == NULL)
                        return NULL;
                    y = y->parent;
                }

                return !y ? _last : y ;
            }
	};
}

// template <typename T>
// bool					operator!=(const ft::LegacyBidirectionalIterator<T, false>& lhs, const ft::LegacyBidirectionalIterator<T, true>& rhs) { return lhs.base() != rhs.base(); }
// template <typename T>
// bool					operator==(const ft::LegacyBidirectionalIterator<T, false>& lhs, const ft::LegacyBidirectionalIterator<T, true>& rhs) { return (lhs.base() == rhs.base()); };
// template <typename T>
// bool					operator<(const ft::LegacyBidirectionalIterator<T, false>& lhs, const ft::LegacyBidirectionalIterator<T, true>& rhs) { return (lhs.base() < rhs.base()); };
// template <typename T>
// bool					operator>(const ft::LegacyBidirectionalIterator<T, false>& lhs, const ft::LegacyBidirectionalIterator<T, true>& rhs) { return (lhs.base() > rhs.base()); };
// template <typename T>
// bool					operator<=(const ft::LegacyBidirectionalIterator<T, false>& lhs, const ft::LegacyBidirectionalIterator<T, true>& rhs) { return (lhs.base() <= rhs.base()); };
// template <typename T>
// bool					operator>=(const ft::LegacyBidirectionalIterator<T, false>& lhs, const ft::LegacyBidirectionalIterator<T, true>& rhs) { return (lhs.base() >= rhs.base()); };

#endif
