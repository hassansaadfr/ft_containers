#ifndef VECTOR_H
# define VECTOR_H

# include <iostream>
# include <memory>
# include <limits>
# include <iterator>
# include "Iterator.hpp"

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
			// typedef Iterator<T, true>							reverse_iterator;
			// typedef Iterator<T, true>							const_reverse_iterator;
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

				distance = std::distance(first, last);
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
				while (first != last)
					position = _insert_n(position, *first++, 1);
			}
			void	clear() { _clear_alloc(_size); };

			/* Iterators */
			iterator		begin() { return iterator(_ptr); };
			const_iterator	begin() const { return const_iterator(_ptr); };
			iterator		end() { return iterator(_ptr + _size); };
			const_iterator	end() const { return const_iterator(_ptr + _size); };
			// iterator		rbegin() { return iterator(_ptr); };
			// const_iterator	rbegin() const { return iterator(_ptr); };
			// iterator		rend() { return iterator(_ptr + _size); };
			// const_iterator	rend() const { return iterator(_ptr + _size); };

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

			iterator	_insert_n(iterator position, value_type const & val, size_type step)
			{
				size_type n = &(*position) - _ptr;

				if (_size + step > _capacity)
				{
					reserve(_size + step);
					position = iterator(_ptr + n);
				}
				for (iterator last = end(); last != position; last--)
				{
					_alloc.construct(&(*last), *(last - step));
					_alloc.destroy(&(*last));
				}
				_alloc.construct(&(*position), val);
				_size = _size + step;
				return position;
			}
	};
}

#endif
