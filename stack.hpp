/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmacquet <kmacquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/29 10:41:50 by kmacquet          #+#    #+#             */
/*   Updated: 2021/09/29 14:52:58 by kmacquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STACK_HPP
# define STACK_HPP
# include <iostream>
# include "vector.hpp"

namespace ft {
	template <class T, class Container = ft::vector<T> >
	class stack
	{	
		public:
			typedef T				value_type;
			typedef Container		container_type;
			typedef size_t			size_type;
		protected:
			container_type ctnr;
	
		public:
		explicit stack (const container_type& ctnr1 = container_type()) : ctnr(ctnr1)
		{
			;
		}
		bool empty() const
		{
			if (ctnr.size())
				return (false);
			return (true);
		}
		size_type size() const
		{
			return (ctnr.size());
		}
		value_type& top()
		{
			return *(--ctnr.end());
		}
		const value_type& top() const
		{
			return *(--ctnr.end());
		}
		void push (const value_type& val)
		{
			ctnr.push_back(val);
		}
		void pop (void)
		{
			ctnr.pop_back();
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
		return (lhs.ctnr == rhs.ctnr);
	}

	template <class Ts, class Containers>
	bool operator!= (const ft::stack<Ts,Containers>& lhs, const ft::stack<Ts,Containers>& rhs)
	{
		return (lhs.ctnr != rhs.ctnr);
	}

	template <class Ts, class Containers>
	bool operator<  (const ft::stack<Ts,Containers>& lhs, const ft::stack<Ts,Containers>& rhs)
	{
		return (lhs.ctnr < rhs.ctnr);
	}

	template <class Ts, class Containers>
	bool operator<= (const ft::stack<Ts,Containers>& lhs, const ft::stack<Ts,Containers>& rhs)
	{
		return (lhs.ctnr <= rhs.ctnr);
	}

	template <class Ts, class Containers>
	bool operator>  (const ft::stack<Ts,Containers>& lhs, const ft::stack<Ts,Containers>& rhs)
	{
		return (lhs.ctnr > rhs.ctnr);
	}

	template <class Ts, class Containers>
	bool operator>= (const ft::stack<Ts,Containers>& lhs, const ft::stack<Ts,Containers>& rhs)
	{
		return (lhs.ctnr >= rhs.ctnr);
	}
}

#endif