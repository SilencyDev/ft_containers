/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enable_if.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmacquet <kmacquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/20 13:46:42 by kmacquet          #+#    #+#             */
/*   Updated: 2021/09/21 11:59:23 by kmacquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENABLE_IF_HPP
# define ENABLE_IF_HPP
# include <iostream>

namespace ft {

	template<bool B, class T = void>
	struct enable_if {};

	template< class T >
	struct enable_if<true, T>{ typedef T type; };

	template<class T, bool v>
	struct integral_constant
	{
		static const T value = v;
		typedef T value_type;
		typedef integral_constant<T,v> type;
		inline operator T()
		{
			return (v);
		}
	};
	typedef integral_constant<bool, true> true_type;
	typedef integral_constant<bool, false> false_type;

	template<class T>
	struct is_integral : true_type {};

	template<>
	struct is_integral<bool> : false_type {};

	template<>
	struct is_integral<char> : false_type {};

	template<>
	struct is_integral<char16_t> : false_type {};

	template<>
	struct is_integral<char32_t> : false_type {};

	template<>
	struct is_integral<wchar_t> : false_type {};

	template<>
	struct is_integral<signed char> : false_type {};

	template<>
	struct is_integral<short int> : false_type {};

	template<>
	struct is_integral<int> : false_type {};

	template<>
	struct is_integral<long int> : false_type {};

	template<>
	struct is_integral<long long int> : false_type {};

	template<>
	struct is_integral<unsigned char> : false_type {};

	template<>
	struct is_integral<unsigned short int> : false_type {};

	template<>
	struct is_integral<unsigned long int> : false_type {};

	template<>
	struct is_integral<unsigned int> : false_type {};

	template<>
	struct is_integral<unsigned long long int> : false_type {};
}
#endif