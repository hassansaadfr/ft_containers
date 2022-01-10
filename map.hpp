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

			typedef typename ft::RedBlackTree<value_type, Compare, allocator_type>				Tree;
			typedef typename Tree::node_ptr														node_ptr;

			typedef ft::LegacyBidirectionalIterator<ft::Node<value_type>, false, Compare>		iterator;
			typedef ft::LegacyBidirectionalIterator<ft::Node<value_type>, true, Compare>		const_iterator;

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
			map(): _alloc(Allocator()), _comp(Compare())
			{};
			explicit map(const Compare& comp, const Allocator& alloc = Allocator()): _comp(comp), _alloc(alloc)
			{};
			map(const map& other): _alloc(other._alloc), _comp(other._comp)
			{
				iterator it = other.begin();
				while (it != other.end())
				{
					_bst.insert(*it);
					it++;
				}
			}

			~map() {};

			template< class InputIt >
			map(InputIt first, InputIt last, const Compare& comp = Compare(), const Allocator& alloc = Allocator())
			{
				_comp = comp;
				_alloc = alloc;
				insert(first, last);
				// while (first != last)
				// {
				// 	std::cout << first->first << std::endl;
				// 	_bst.insert(*first);
				// 	first++;
				// }
			}

			iterator insert ( iterator hint, const value_type& value )
			{
				(void)hint;
				return iterator(_bst.insert(value), _bst.getEnd());
			}

			template< class InputIt >
			void insert ( InputIt first, InputIt last )
			{
				while (first != last)
				{
					_bst.insert(*first);
					first++;
				}
			}

			ft::pair<iterator, bool>	insert ( const value_type& value )
			{
				ft::pair<node_ptr, bool> searchResult = _bst.search_node(value);
				if (searchResult.second == false)
				{
					return (ft::make_pair(iterator(_bst.insert(value), _bst.getEnd()), true));
				}
				return ft::make_pair(iterator(searchResult.first, _bst.getEnd()), false);
			}

			void clear()
			{
				_bst.clear();
			}

			// TEMPORARY
			void print() { _bst.printTree(); };

			allocator_type get_allocator() const { return _alloc; };
			size_type size() const { return _bst.getSize(); };
			size_type max_size() const { return _alloc.max_size(); };
			bool empty() const { return size() == 0; };

			iterator begin() { return iterator((_bst.minimum(_bst.getRoot())), _bst.getEnd()); };
			const_iterator begin() const { return const_iterator(_bst.minimum(_bst.getRoot()), _bst.getEnd()); };
			iterator end() { return iterator(_bst.getEnd(), _bst.getEnd()); };
			const_iterator end() const { return const_iterator(_bst.getEnd(), _bst.getEnd()); };

			reverse_iterator		rbegin() { return reverse_iterator(end()); };
			const_reverse_iterator	rbegin() const { return const_reverse_iterator(end()); };
			reverse_iterator		rend() { return reverse_iterator(begin()); };
			const_reverse_iterator	rend() const { return const_reverse_iterator(begin()); };

			mapped_type& operator[] (const key_type& k)
			{
				iterator tmp = this->find(k);

				if (tmp == _bst.getEnd())
					this->insert(ft::make_pair(k, mapped_type()));
				tmp = this->find(k);
				return ((*tmp).second);
			}

			key_compare key_comp() const { return _comp; }
			value_compare value_comp() const { return value_compare(_comp); }

			iterator find(const key_type& k)
			{
				ft::pair<node_ptr, bool> searchResult = _bst.search_node(ft::make_pair(k, T()));
				return (iterator(searchResult.first));
			}
			const_iterator find (const key_type& k) const
			{
				ft::pair<node_ptr, bool> searchResult = _bst.search_node(ft::make_pair(k, T()));
				return (const_iterator(searchResult.first));
			}
		private:
			Tree			_bst;
			allocator_type	_alloc;
			Compare			_comp;

	};
}
#endif
