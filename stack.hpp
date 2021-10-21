/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmacquet <kmacquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/29 10:41:50 by kmacquet          #+#    #+#             */
/*   Updated: 2021/10/21 11:51:09 by kmacquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STACK_HPP
# define STACK_HPP
# include <iostream>
# include <assert.h>
# include "vector.hpp"

namespace ft {
	template <bool b>
	struct StaticAssert {};

	template <>
	struct StaticAssert<true>
	{
		static void assertsame() {}
	};
	template <class T, class U>
	struct issame
	{
		static const bool value = false;
	};
	template <class T>
	struct issame<T,T>
	{
		static const bool value = true;
	};
	
	template <class T, class Container = ft::vector<T> >
	class stack
	{	
		public:
			typedef T				value_type;
			typedef Container		container_type;
			typedef size_t			size_type;
		protected:
			container_type c;
	
		public:
		explicit stack (const container_type& ctnr1 = container_type()) : c(ctnr1)
		{
			StaticAssert<issame<T, typename container_type::value_type>::value>::assertsame();
		}
		bool empty() const
		{
			if (c.size())
				return (false);
			return (true);
		}
		size_type size() const
		{
			return (c.size());
		}
		value_type& top()
		{
			return *(--c.end());
		}
		const value_type& top() const
		{
			return *(--c.end());
		}
		void push (const value_type& val)
		{
			c.push_back(val);
		}
		void pop (void)
		{
			c.pop_back();
		}
		
		template <class Ts, class Containers>
		friend bool operator== (const ft::stack<Ts,Containers>& lhs, const ft::stack<Ts,Containers>& rhs);

		template <class Ts, class Containers>
		friend bool operator!= (const ft::stack<Ts,Containers>& lhs, const ft::stack<Ts,Containers>& rhs);

		template <class Ts, class Containers>
		friend bool operator<  (const ft::stack<Ts,Containers>& lhs, const ft::stack<Ts,Containers>& rhs);

		template <class Ts, class Containers>
		friend bool operator<= (const ft::stack<Ts,Containers>& lhs, const ft::stack<Ts,Containers>& rhs);

		template <class Ts, class Containers>
		friend bool operator>  (const ft::stack<Ts,Containers>& lhs, const ft::stack<Ts,Containers>& rhs);

		template <class Ts, class Containers>
		friend bool operator>= (const ft::stack<Ts,Containers>& lhs, const ft::stack<Ts,Containers>& rhs);
	};
	template <class Ts, class Containers>
	bool operator== (const ft::stack<Ts,Containers>& lhs, const ft::stack<Ts,Containers>& rhs)
	{
		return (lhs.c == rhs.c);
	}

	template <class Ts, class Containers>
	bool operator!= (const ft::stack<Ts,Containers>& lhs, const ft::stack<Ts,Containers>& rhs)
	{
		return (lhs.c != rhs.c);
	}

	template <class Ts, class Containers>
	bool operator<  (const ft::stack<Ts,Containers>& lhs, const ft::stack<Ts,Containers>& rhs)
	{
		return (lhs.c < rhs.c);
	}

	template <class Ts, class Containers>
	bool operator<= (const ft::stack<Ts,Containers>& lhs, const ft::stack<Ts,Containers>& rhs)
	{
		return (lhs.c <= rhs.c);
	}

	template <class Ts, class Containers>
	bool operator>  (const ft::stack<Ts,Containers>& lhs, const ft::stack<Ts,Containers>& rhs)
	{
		return (lhs.c > rhs.c);
	}

	template <class Ts, class Containers>
	bool operator>= (const ft::stack<Ts,Containers>& lhs, const ft::stack<Ts,Containers>& rhs)
	{
		return (lhs.c >= rhs.c);
	}
}

#endif