#ifndef VECTOR_H
# define VECTOR_H

# include <iostream>
# include <memory>
# include <limits>
# include <iterator>
# include "Iterator.hpp"

namespace ft {
	template < class T, class Allocator = std::allocator<T> >
	class Vector
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


			Vector(void): _size(0), _capacity(0), _alloc(allocator_type()), _ptr(NULL)
			{};
			explicit Vector (const allocator_type& alloc = allocator_type()): _size(0), _capacity(0), _alloc(alloc), _ptr(NULL)
			{};
			explicit Vector (size_type n, const value_type& value = value_type(),
				const allocator_type& alloc = allocator_type()): _size(0), _capacity(0), _alloc(alloc), _ptr(NULL)
			{ assign(n, value); };

			template <class InputIterator>
			Vector (InputIterator first, InputIterator last,
				const allocator_type& alloc = allocator_type()): _alloc(alloc)
			{
				assign(first, last);
			};

			Vector(Vector const &src);

			~Vector(void);
			Vector&		operator=(Vector const &src);

			/* Modifiers */
			template <class InputIterator>
			void assign (InputIterator first, InputIterator last)
			{
				difference_type distance;

				distance = std::distance(first, last);
				_clear_alloc(distance);
				_size = distance;
				_capacity = distance;
				while (first != last)
				{
					_alloc.construct(&_ptr[_size], *first);
					first++;
				}
			}

			void assign (size_type n, const value_type& val)
			{
				_clear_alloc(n);
				_size = n;
				_capacity = n;
				for (size_type i = 0; i < n; i++)
					_alloc.construct(&_ptr[_size], val);
			}

			/* Iterators */
			iterator		begin() { return iterator(_ptr); };
			const_iterator	begin() const { return iterator(_ptr); };
			iterator		end() { return iterator(_ptr + _size); };
			const_iterator	end() const { return iterator(_ptr + _size); };
			// iterator		rbegin() { return iterator(_ptr); };
			// const_iterator	rbegin() const { return iterator(_ptr); };
			// iterator		rend() { return iterator(_ptr + _size); };
			// const_iterator	rend() const { return iterator(_ptr + _size); };

			/* Element access */
			reference		operator[](size_type n) { return _ptr[n]; };
			const_reference operator[](size_type n) const { return _ptr[n]; };
			reference		at(size_type n) { return _ptr[n]; };
			const_reference	at(size_type n) const { return _ptr[n]; };
			reference		front() { return _ptr; };
			const_reference	front() const { return _ptr; };
			reference		back() { return _ptr[_size - 1]; };
			const_reference	back() const { return _ptr[_size - 1]; };

			/* Member functions */
			size_type		size() const { return _size; };
			size_type		max_size() const { return std::numeric_limits<difference_type>::max(); };
			size_type		capacity() const { return _capacity; };
			bool			empty() const { return _size == 0; };
			allocator_type	get_allocator() const { return (std::numeric_limits<difference_type>::max()); };

		private:
			pointer			_ptr;
			size_type		_size;
			size_type		_capacity;
			allocator_type	_alloc;

			void	_clear_alloc(size_type n)
			{
				for (size_t i = 0; i < n; i++)
					_alloc.destroy(_ptr[i]);
				_capacity = 0;
				_size = 0;
			}
	};
}

#endif
