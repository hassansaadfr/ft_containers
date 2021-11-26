#ifndef STACK_H
# define STACK_H

# include "vector.hpp"

namespace ft
{
	template< class T, class Container = ft::vector<T> >
	class stack
	{
		public:
			typedef Container								container_type;
			typedef typename Container::value_type			value_type;
			typedef typename Container::size_type			size_type;
			typedef typename Container::reference			reference;
			typedef typename Container::const_reference		const_reference;

			explicit stack(const Container& cont = Container()): c(cont) {};
			~stack() {};

			stack& operator=(const stack& other)
			{
				if (this == &other)
					return *this;
				c = other.c;
				return *this;
			}

			reference top()						{ return c.back(); };
			const_reference top() const			{ return c.back(); };

			bool empty() const 					{ return c.empty(); };
			size_type size() const				{ return c.size(); };
			void push(const value_type& value)	{ c.push_back(value); };
			void pop()							{ c.pop_back(); };

			template <class U, class C>
			friend	bool operator==(const stack<U, C> &lhs, const stack<U, C> &rhs);
			template <class U, class C>
			friend bool operator!=(const stack<U, C> &lhs, const stack<U, C> &rhs);
			template <class U, class C>
			friend bool operator<(const stack<U, C> &lhs, const stack<U, C> &rhs);
			template <class U, class C>
			friend bool operator<=(const stack<U, C> &lhs, const stack<U, C> &rhs);
			template <class U, class C>
			friend bool operator>(const stack<U, C> &lhs, const stack<U, C> &rhs);
			template <class U, class C>
			friend bool operator>=(const stack<U, C> &lhs, const stack<U, C> &rhs);
		protected:
			container_type	c;
	};
	template< class T, class Container >
	bool operator==( const stack<T,Container>& lhs, const stack<T,Container>& rhs ) { return lhs.c == rhs.c; };
	template< class T, class Container >
	bool operator!=( const stack<T,Container>& lhs, const stack<T,Container>& rhs ) { return lhs.c != rhs.c; };
	template< class T, class Container >
	bool operator<( const stack<T,Container>& lhs, const stack<T,Container>& rhs ) { return lhs.c < rhs.c; };
	template< class T, class Container >
	bool operator<=( const stack<T,Container>& lhs, const stack<T,Container>& rhs ) { return lhs.c <= rhs.c; };
	template< class T, class Container >
	bool operator>( const stack<T,Container>& lhs, const stack<T,Container>& rhs ) { return lhs.c > rhs.c; };
	template< class T, class Container >
	bool operator>=( const stack<T,Container>& lhs, const stack<T,Container>& rhs ) { return lhs.c >= rhs.c; };

};

#endif
