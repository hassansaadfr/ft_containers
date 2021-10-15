#ifndef UTILS_H
# define UTILS_H

# include <iostream>

namespace ft {
	template <bool isConstant, typename const_type, typename notConst_type>
	struct is_constant {};

	template <typename const_type, typename notConst_type>
	struct is_constant<true, const_type, notConst_type> {
		typedef const_type		type;
	};
	template <typename const_type, typename notConst_type>
	struct is_constant<false, const_type, notConst_type> {
		typedef notConst_type	type;
	};
};

#endif
