#ifndef RANDOMACCESSITERATOR_H
# define RANDOMACCESSITERATOR_H

# include <iostream>

namespace ft {
	template <typename T>
	class RandomAccessIterator
	{
		public:
			/* Constructor */
			RandomAccessIterator(void) {};
			/* Destructor */
			~RandomAccessIterator(void) {};
			/* Copy constructor */
			RandomAccessIterator(RandomAccessIterator const &src)
			{
				this->_ptr = src->_ptr;
			}
			/* Copy Assignation constructor */
			RandomAccessIterator&		operator=(RandomAccessIterator const &rhs)
			{
				if (this != rhs)
					this->_ptr = rhs->_ptr;
				return *this;
			}

			/* Comparaisons Part */
			bool					operator==(RandomAccessIterator const &rhs) { return (_ptr == rhs->_ptr); };
			bool					operator!=(RandomAccessIterator const &rhs) { return (_ptr == rhs->_ptr); };
			bool					operator<(RandomAccessIterator const &rhs) { return (_ptr < rhs->_ptr); };
			bool					operator>(RandomAccessIterator const &rhs) { return (_ptr > rhs->_ptr); };
			bool					operator<=(RandomAccessIterator const &rhs) { return (_ptr <= rhs->_ptr); };
			bool					operator>=(RandomAccessIterator const &rhs) { return (_ptr >= rhs->_ptr); };

			/* Increment Decrement Part */
			RandomAccessIterator&	operator++(void)
			{
				_ptr++;
				return *this;
			}
			RandomAccessIterator&	operator--(void)
			{
				_ptr--;
				return *this;
			}
			RandomAccessIterator	operator++(int)
			{
				RandomAccessIterator	old = *this;
				operator++();
				return old;
			}
			RandomAccessIterator	operator--(int)
			{
				RandomAccessIterator	old = *this;
				operator--();
				return old;
			}

			/* Arithmetic operations */
			RandomAccessIterator&	operator+(int const &rhs)
			{
				_ptr = _ptr + rhs;
				return *this;
			}
			RandomAccessIterator&	operator+(RandomAccessIterator const &rhs)
			{
				_ptr = _ptr + rhs._ptr;
				return *this;
			}
			RandomAccessIterator&	operator-(int const &rhs)
			{
				_ptr = _ptr - rhs;
				return *this;
			}
			RandomAccessIterator&	operator-(RandomAccessIterator const &rhs)
			{
				_ptr = _ptr - rhs._ptr;
				return *this;
			}
			/* Compound assignement arithmetics operations */
			RandomAccessIterator&	operator+=(int const &rhs)
			{
				_ptr = _ptr + rhs;
				return *this;
			}
			RandomAccessIterator&	operator+=(RandomAccessIterator const &rhs)
			{
				_ptr = _ptr + rhs._ptr;
				return *this;
			}
			RandomAccessIterator&	operator-=(int const &rhs)
			{
				_ptr = _ptr - rhs;
				return *this;
			}
			RandomAccessIterator&	operator-=(RandomAccessIterator const &rhs)
			{
				_ptr = _ptr - rhs._ptr;
				return *this;
			}

			/* Offset dereference operator */
			RandomAccessIterator&	operator[](int const &rhs)
			{
				_ptr = _ptr + rhs;
				return *this;
			}
		private:
			T	*_ptr;
	};

}

#endif
