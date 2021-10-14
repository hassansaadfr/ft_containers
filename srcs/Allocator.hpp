#ifndef ALLOCATOR_H
# define ALLOCATOR_H

# include <iostream>

template <class T>
class Allocator
{
	public:
		Allocator(void);
		~Allocator(void);
		Allocator(Allocator const &src);

		Allocator&		operator=(Allocator const &src);
};

// std::ostream &		operator<<(std::ostream &o, Allocator const &src);

#endif
