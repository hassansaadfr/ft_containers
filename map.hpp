#ifndef MAP_H
# define MAP_H

#include "Utils.hpp"
#include "LegacyBidirectionalIterator.hpp"
#include "LegacyReverseBidirectionalIterator.hpp"
#include "RedBlackTree.hpp"

namespace ft {
	template< class Key, class T, class Compare = ft::less<Key>, class Allocator = std::allocator<ft::pair<const Key, T> > >
	class map {
		public:
			typedef Key																			key_type;
			typedef T																			mapped_type;
			typedef ft::pair<const Key, T>														value_type;
			typedef std::size_t																	size_type;
			typedef std::ptrdiff_t																difference_type;
			typedef Compare																		key_compare;
			typedef Allocator																	allocator_type;
			typedef value_type&																	reference;
			typedef const value_type&															const_reference;
			typedef typename Allocator::pointer													pointer;
			typedef typename Allocator::const_pointer											const_pointer;

			typedef typename ft::RedBlackTree<value_type, Compare, allocator_type>				tree;
			typedef typename tree::node_ptr	node_ptr;


			typedef ft::LegacyBidirectionalIterator<typename tree::node_type, false>			iterator;
			typedef ft::LegacyBidirectionalIterator<typename tree::node_type, true>				const_iterator;

			typedef LegacyReverseBidirectionalIterator<iterator>								reverse_iterator;
			typedef LegacyReverseBidirectionalIterator<const_iterator>							const_reverse_iterator;

			class value_compare : std::binary_function<value_type, value_type, bool> {
				public:
					friend class map;
					bool operator()(const value_type &lhs, const value_type &rhs) const { return comp(lhs.first, rhs.first); }
				protected:
					Compare comp;
					value_compare(Compare c) : comp(c) {}
			};
			/* Constructors */
			map(): _alloc(Allocator()), _comp(Compare()), _size(0)
			{
				// _bst.insert(value_type());
			};
			explicit map(const Compare& comp, const Allocator& alloc = Allocator()): _comp(comp), _alloc(alloc), _size(0)
			{
				// _bst.insert(value_type());
			};
			map(const map& other): _alloc(other._alloc), _comp(other._comp)
			{
				iterator it = other.begin();
				while (it != NULL)
				{
					_bst.insert(*it);
					_size++;
					it++;
				}
			}

			~map() {};

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

			iterator insert( iterator hint, const value_type& value )
			{
				(void)hint;
				return _bst.insert(value);
			}

			template< class InputIt >
			void insert( InputIt first, InputIt last )
			{
				while (first != last)
				{
					_bst.insert(*first);
					first++;
				}
			}

			ft::pair<iterator, bool>	insert( const value_type& value )
			{
				ft::pair<node_ptr, bool> searchResult = _bst.search_node(value);
				if (searchResult.second == false)
				{
					return (ft::make_pair(_bst.insert(value), true));
				}
				return ft::make_pair(searchResult.first, false);
			}

			void clear()
			{
				_size = 0;
			}


			// TEMPORARY
			void print() { _bst.printTree(); };

			allocator_type get_allocator() const { return _alloc; };
			bool empty() const { return _size == 0; };
			size_type size() const { return _size; };
			size_type max_size() const { return _alloc.max_size(); };

			iterator begin() { return iterator((_bst.minimum(_bst.getRoot()))); };
			//const_iterator begin() const { return const_iterator(_bst.minimum(_bst.getRoot())); };
			//iterator end() { return iterator(_bst.maximum(_bst.getRoot())); };
			//const_iterator end() const { return const_iterator(_bst.maximum(_bst.getRoot())); };
//
			//reverse_iterator		rbegin() { return reverse_iterator(_bst.maximum(_bst.getRoot())); };
			//const_reverse_iterator	rbegin() const { return const_reverse_iterator(_bst.maximum(_bst.getRoot())); };
			//reverse_iterator		rend() { return reverse_iterator(begin()); };
			//const_reverse_iterator	rend() const { return const_reverse_iterator(begin()); };

			mapped_type& operator[] (const key_type& k)
			{
				typename ft::RedBlackTree<value_type>::node_ptr res = _bst.searchTree(k);
				if (res->first != k)
					insert(ft::make_pair(k, mapped_type()));
				return res->second;

				// iterator find = searchNode(k);
                // if (find._M_node == _end)
                //     find = insert(_root, ft::make_pair(k, mapped_type()));
                // return find->second;
			}

		private:
			// RedBlackTree<value_type, Compare, allocator_type>	_bst;
			RedBlackTree<value_type>						_bst;
			allocator_type									_alloc;
			Compare											_comp;
			size_type										_size;

	};
}
#endif
