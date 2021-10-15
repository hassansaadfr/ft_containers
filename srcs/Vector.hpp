#ifndef VECTOR_H
# define VECTOR_H

# include <iostream>
# include <memory>
# include "Iterator.hpp"

namespace ft {
	template < class T, class Alloc = std::allocator<T> >
	class Vector
	{
		public:
			typedef T 											value_type;
			typedef Alloc										allocator_type;
			typedef typename allocator_type::reference			reference;
			typedef typename allocator_type::const_reference	const_reference	;
			typedef typename allocator_type::pointer			pointer;
			typedef typename allocator_type::const_pointer		const_pointer;

			typedef Iterator<T>									iterator;

			Vector(void);
			~Vector(void);
			Vector(Vector const &src);

			Vector&		operator=(Vector const &src);
	};

	// std::ostream &		operator<<(std::ostream &o, Vector const &src);
}

#endif
