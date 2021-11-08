#ifndef VECTOR_H
# define VECTOR_H

# include <iostream>
# include <memory>
# include <limits>
# include "Iterator.hpp"
# include "ReverseIterator.hpp"

namespace ft {
	template < class T, class Allocator = std::allocator<T> >
	class vector
	{
		public:
			typedef T 											value_type;
			typedef Allocator									allocator_type;
			typedef typename allocator_type::reference			reference;
			typedef typename allocator_type::const_reference	const_reference	;
			typedef typename allocator_type::pointer			pointer;
			typedef typename allocator_type::const_pointer		const_pointer;
			typedef Iterator<T, false>							iterator;
			typedef Iterator<T, true>							const_iterator;
			typedef ReverseIterator<iterator>					reverse_iterator;
			typedef ReverseIterator<const_iterator>				const_reverse_iterator;
			typedef ptrdiff_t									difference_type;
			typedef size_t										size_type;

			explicit vector (const allocator_type& alloc = allocator_type()): _ptr(NULL), _size(0), _capacity(0), _alloc(alloc)
			{};
			explicit vector (size_type n, const value_type& value = value_type(),
				const allocator_type& alloc = allocator_type()): _ptr(NULL), _size(0), _capacity(0), _alloc(alloc)
			{ assign(n, value); };

			template <class InputIterator>
			vector (InputIterator first, InputIterator last,
				const allocator_type& alloc = allocator_type()): _ptr(NULL), _size(0), _capacity(0), _alloc(alloc)
			{
				assign(first, last);
			};

			vector(vector const &src): _ptr(NULL), _size(0), _capacity(0), _alloc(src._alloc)
			{
				assign(src.begin(), src.end());
			};

			~vector(void)
			{
				if (_capacity > 0)
					_alloc.deallocate(_ptr, _capacity);
			};
			vector&		operator=(vector const &src)
			{
				if (this == &src)
					return *this;
				assign(src.begin(), src.end());
				return *this;
			};

			/* Modifiers */
			template <class InputIterator>
			void assign(InputIterator first, InputIterator last, typename enable_if< !is_integral< InputIterator >::value >::type* = 0)
			{
				difference_type distance;

				distance = ft::distance(first, last);
				_clear_alloc(_size);
				reserve(distance);
				_capacity = distance;
				while (first != last)
				{
					_alloc.construct(&_ptr[_size++], *first);
					first++;
				}
			};

			void assign(size_type n, const value_type& val)
			{
				_clear_alloc(_size);
				reserve(n);
				_size = n;
				for (size_type i = 0; i < n; i++)
					_alloc.construct(_ptr + i, val);
			};

			void push_back (const value_type& val)
			{
				if (_size + 1 > _capacity)
					reserve(_size + 1);
				_alloc.construct(_ptr + _size, val);
				_size++;
			};

			void pop_back()
			{
				if (_size == 0)
					return ;
				_alloc.destroy(&_ptr[_size - 1]);
				_size--;
			};

			iterator insert(iterator position, const value_type& val)
			{
				return _insert_n(position, val, 1);
			}
			void insert(iterator position, size_type n, const value_type& val)
			{
				for (size_type i = 0; i < n; i++)
					position = _insert_n(position, val, 1);
			}
			template <class InputIterator>
			void insert(iterator position, InputIterator first, InputIterator last, typename enable_if< !is_integral< InputIterator >::value >::type* = 0)
			{
				InputIterator tmp_first = first;
				size_type pos = &(*position) - _ptr;
				pointer   tmp;
				size_type len = 0;

				for (InputIterator to = first; to != last; to++)
					len++;
				if (_size + len > _capacity)
				{
					tmp = _alloc.allocate(len);
					for (size_type i = 0; tmp_first != last; tmp_first++, i++)
						_alloc.construct(tmp + i, *tmp_first);
					size_type i = 0;
					size_type tmp_size = _size;
					pointer tab;

					tab = _alloc.allocate(_capacity + len);
					for (; i < pos; i++)
						_alloc.construct(tab + i, *(_ptr + i));
					for (size_type l = 0; l < len; l++, i++)
						_alloc.construct(tab + i, *(tmp + l));
					for (; i - len < _size; i++)
						_alloc.construct(tab + i, *(_ptr + i - len));
					clear();
					_size = tmp_size;
					_alloc.deallocate(_ptr, _capacity);
					for (size_type l = 0; l < len; l++)
						_alloc.destroy(tmp + l);
					_alloc.deallocate(tmp, len);
					_ptr = tab;
					_capacity += len;
					_size += len;
				}
				else
				{
					while (first != last)
						position = insert(position, *first++);
				}
			}

			iterator erase(iterator position)
			{

				size_type pos = &(*position) - _ptr;

				_alloc.destroy(_ptr + pos);
				for (; pos < _size - 1; pos++)
				{
					_alloc.construct(_ptr + pos, *(_ptr + pos + 1));
					_alloc.destroy(_ptr + pos + 1);
				}
				_size -= 1;
				return (iterator(position));
			}

			iterator erase (iterator first, iterator last)
			{
				size_type n = 0;
				size_type pos = (&(*first) - _ptr);
				for (iterator tmp = first; first != last; first++)
					n++;
				if (_size > 0 && n > 0) {
					for (size_type i = 0; i < n; i++)
						_alloc.destroy(_ptr + pos + i);
					for (size_type l = pos; l + n < _size; l++) {
						_alloc.construct(_ptr + l, *(_ptr + l + n));
						_alloc.destroy(_ptr + l + n);
					}
					_size -= n;
				}
				return iterator(_ptr + pos);
			};

			void	clear() { _clear_alloc(_size); };

			/* Iterators */
			iterator				begin() { return iterator(_ptr); };
			const_iterator			begin() const { return const_iterator(_ptr); };
			iterator				end() { return iterator(_ptr + _size); };
			const_iterator			end() const { return const_iterator(_ptr + _size); };
			reverse_iterator		rbegin() { return reverse_iterator(_ptr + _size); };
			const_reverse_iterator	rbegin() const { return const_reverse_iterator(_ptr + _size); };
			reverse_iterator		rend() { return reverse_iterator(_ptr); };
			const_reverse_iterator	rend() const { return const_reverse_iterator(_ptr); };

			/* Element access */
			reference		operator[](size_type n) { return _ptr[n]; };
			const_reference operator[](size_type n) const { return _ptr[n]; };
			reference		at(size_type n)
			{
				if (n >= _size)
					throw std::out_of_range("out of bound");
				return _ptr[n];
			};
			const_reference	at(size_type n) const
			{
				if (n >= _size)
					throw std::out_of_range("out of bound");
				return _ptr[n];
			};
			reference		front() { return *_ptr; };
			const_reference	front() const { return *_ptr; };
			reference		back() { return _ptr[_size - 1]; };
			const_reference	back() const { return _ptr[_size - 1]; };

			/* Capacity */
			size_type		size() const { return _size; };
			size_type		max_size() const { return allocator_type().max_size(); };
			void resize		(size_type n, value_type val = value_type())
			{
				if (n < 0)
					throw std::length_error("Invalid resize value");
				reserve(n);
				if (n > _size)
				{
					size_type	old_size = _size;
					for (; old_size < n; old_size++)
						_alloc.construct(_ptr + old_size, val);

					_size = n;
				}
				else
				{
					iterator last = end();
					for (size_type i = n; i > _size; i++)
					{
						_alloc.destroy(&(*(last - i)));
					}
					_size = n;
				}
			}
			size_type		capacity() const { return _capacity; };
			bool			empty() const { return _size == 0; };
			void			reserve (size_type n)
			{
				if (n > max_size())
					throw std::length_error("Max size excessed");
				if (n <= _capacity)
					return ;
				pointer	tmp;
				tmp = _alloc.allocate(n, 0);
				for (size_type i = 0; i < _size; i++)
				{
					_alloc.construct(tmp + i, _ptr[i]);
					_alloc.destroy(_ptr + i);
				}
				_alloc.deallocate(_ptr, _capacity);
				_ptr = tmp;
				_capacity = n;
			};

			/* Allocator */
			allocator_type	get_allocator() const { return allocator_type(); };

		private:
			pointer			_ptr;
			size_type		_size;
			size_type		_capacity;
			allocator_type	_alloc;

			void	_clear_alloc(size_type n)
			{
				for (size_t i = 0; i < n; i++)
					_alloc.destroy(&_ptr[i]);
				_size = 0;
			}
			template < class InputIterator >
			iterator	_insert_n(InputIterator position, value_type const & val, size_type step)
			{
				size_type n = &(*position) - _ptr;

				if (_size + step > _capacity)
				{
					reserve(_size + step);
					position = InputIterator(_ptr + n);
				}
				for (InputIterator last = end(); last != position; last--)
				{
					_alloc.construct(&(*last), *(last - step));
					// _alloc.destroy(&(*last));
				}
				_alloc.construct(&(*position), val);
				_size = _size + step;
				return position;
			}
			template < class InputIterator >
			void	_move_elem(InputIterator position, int offset)
			{
				_alloc.construct(&(*(position + offset)), *position);
				_alloc.destroy(&(*position));
			}
	};

	template <class T, class Alloc>
	bool operator==(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
	{
		if (lhs.size() != rhs.size())
			return false;
		for (size_t i = 0; i < lhs.size(); i++)
		{
			if (lhs[i] != rhs[i])
				return false;
		}
		return true;
	};
	template <class T, class Alloc>
	bool operator!=(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
	{
		return !(lhs == rhs);
	}
	template <class T, class Alloc>
	bool operator<(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
	{
		return lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
	}
	template <class T, class Alloc>
	bool operator<=(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
	{
		return !(rhs < lhs);
	}
	template <class T, class Alloc>
	bool operator>(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
	{
		return (rhs < lhs);
	}
	template <class T, class Alloc>
	bool operator>=(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
	{
		return !(lhs < rhs);
	}
}


#endif
