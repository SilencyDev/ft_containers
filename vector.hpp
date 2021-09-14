/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmacquet <kmacquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/03 13:24:26 by kmacquet          #+#    #+#             */
/*   Updated: 2021/09/14 15:32:04 by kmacquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_HPP
# define VECTOR_HPP
# include <iostream>
# include <memory>
# include "iterator.hpp"

namespace ft {

	template<class T, class Alloc = std::allocator<T> >
	class vector
	{
		public :
			typedef T									value_type;
			typedef value_type&							reference;
			typedef const value_type&					const_reference;
			typedef Alloc								allocator_type;
			typedef size_t								size_type;
			typedef ptrdiff_t							difference_type;
			typedef T*									pointer;
			typedef T* const							const_pointer;
			typedef ft::random_access_iterator<T>		iterator;
			typedef ft::random_access_iterator<T> const	const_iterator;
		
		protected :
			pointer			_start;
			pointer			_end;
			int				_capacity;
			int				_current;
			allocator_type	_alloc;

		public :
			explicit vector(const allocator_type& alloc = allocator_type())
			{
				_alloc = alloc;
				_capacity = 0;
				_current = 0;
				_start = NULL;
				_end = NULL;
			}
			explicit vector(size_type n, const value_type& val = value_type(),
				const allocator_type& alloc = allocator_type())
			{
				_alloc = alloc;
				_start = _alloc.allocate(n);
				_capacity = n;
				_current = n;
				_end = _start + n;
				while (n--)
				{
					_alloc.construct(_start + n, val);
				}
				_alloc.construct(_start, val);
			}
			// template <class InputIterator>
			// vector(InputIterator first, InputIterator last,
			// 	const allocator_type& alloc = allocator_type());
			// vector(const vector& x);

			~vector()
			{
				while (_capacity--)
				{
					_alloc.destroy(_start + _capacity);
				}
				_alloc.destroy(_start);
			}
			template< class InputIt >
			void assign( InputIt first, InputIt last );
			vector& operator=(vector const & src);

			allocator_type	get_allocator() const;
			reference		at( size_type pos );
			const_reference	at( size_type pos ) const;
			reference		operator[]( size_type pos );
			const_reference	operator[]( size_type pos ) const;
			reference		front();
			const_reference	front() const;
			reference		back();
			const_reference	back() const;

			iterator begin()
			{
				return (_start);
			}
			const_iterator begin() const;
			iterator end()
			{
				return (_end);
			}
			const_iterator end() const;
			// reverse_iterator rbegin();
			// const_reverse_iterator rbegin() const;
			// reverse_iterator rend();
			// const_reverse_iterator rend() const;

			T*				data();
			const T*		data() const;
	};
	template< class T, class Alloc >
	bool operator==(const ft::vector<T,Alloc> & lhs, const ft::vector<T,Alloc> & rhs);

	template< class T, class Alloc >
	bool operator!=(const ft::vector<T,Alloc> & lhs, const ft::vector<T,Alloc> & rhs);

	template< class T, class Alloc >
	bool operator<(const ft::vector<T,Alloc> & lhs, const ft::vector<T,Alloc> & rhs);

	template< class T, class Alloc >
	bool operator<=(const ft::vector<T,Alloc> & lhs, const ft::vector<T,Alloc> & rhs);

	template< class T, class Alloc >
	bool operator>(const ft::vector<T,Alloc> & lhs, const ft::vector<T,Alloc> & rhs);

	template< class T, class Alloc >
	bool operator>=(const ft::vector<T,Alloc> & lhs, const ft::vector<T,Alloc> & rhs);

	template< class T, class Alloc >
	void swap(const ft::vector<T,Alloc>& lhs, const ft::vector<T,Alloc>& rhs);

};

#endif