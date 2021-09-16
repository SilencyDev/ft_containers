/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmacquet <kmacquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/03 13:24:26 by kmacquet          #+#    #+#             */
/*   Updated: 2021/09/16 17:48:14 by kmacquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_HPP
# define VECTOR_HPP
# include <iostream>
# include <memory>
# include <limits>
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
			typedef ft::reverse_iterator<T>				reverse_iterator;
		
		protected :
			pointer			_start;
			pointer			_end;
			size_type		_capacity;
			allocator_type	_alloc;

		public :
			explicit vector(const allocator_type& alloc = allocator_type())
			{
				_alloc = alloc;
				_capacity = 0;
				_start = NULL;
				_end = NULL;
			}
			explicit vector(size_type n, const value_type& val = value_type(),
				const allocator_type& alloc = allocator_type())
			{
				_alloc = alloc;
				_start = _alloc.allocate(n);
				_capacity = n;
				_end = _start + n;
				while (n--)
					_alloc.construct(_start + n, val);
			}
			// template <class InputIterator>
			// vector(InputIterator first, InputIterator last,
			// 	const allocator_type& alloc = allocator_type());
			// vector(const vector& x);

			~vector()
			{
				int tmp = _capacity;
				while (_capacity--)
					_alloc.destroy(_start + _capacity);
				_alloc.deallocate(_start, tmp);
			}
			template< class InputIt >
			void assign( InputIt first, InputIt last );
			vector& operator=(vector const & src);

			allocator_type	get_allocator() const
			{
				return (this->_alloc);
			}
			size_type		size() const
			{
				return (_end - _start);
			}
			size_type		max_size() const
			{
				if (sizeof(value_type) == 1)
					return (_alloc.max_size() / 2);
				return (_alloc.max_size());
			}
			size_type		capacity() const
			{
				return (_capacity);
			}
			bool empty() const
			{
				return (size() ? 1 : 0);
			}
			void reserve(size_type n)
			{
				if (n > this->max_size())
					throw std::length_error("vector");
				if (n <= this->_capacity)
					return ;
				pointer		fresh = _alloc.allocate(n);
				size_type	current_size = size();
				size_type	tmp = _capacity;
				this->_capacity = n;
				while (current_size--)
					_alloc.construct(fresh + current_size, *(_start + current_size));
				current_size = size();
				while (current_size--)
					_alloc.destroy(_start + current_size);
				_alloc.deallocate(_start, tmp);
				current_size = size();
				_start = fresh;
				_end = _start + current_size;
			}
			void resize (size_type n, value_type val = value_type())
			{
				if (n == _capacity)
					return ;
				if (n > _capacity)
				{
					if (_capacity == 0)
						_capacity = 1;
					else if (_capacity < SIZE_MAX / 2)
						_capacity = _capacity * 2;
					else
						_capacity = SIZE_MAX;
					if (n > _capacity)
						_capacity = n;
					reserve(_capacity);
					size_type	tmp = _capacity;
					size_type	oldsize = size();
					_end = _start + tmp;
					while (oldsize < tmp--)
					{
						if (val)
							_alloc.construct(_start + tmp, val);
						else
							_alloc.construct(_start + tmp, 0);
					}
				}
				else if (n < size())
				{
					size_type tmp = n;
					while (n++ < size())
						_alloc.destroy(_start + n);
					_end = _start + tmp;
				}
				else if (n > size())
				{
					size_type	tmp = _capacity;
					size_type	oldsize = size();
					_end = _start + n;
					while (oldsize < tmp--)
					{
						if (val)
							_alloc.construct(_start + tmp, val);
						else
							_alloc.construct(_start + tmp, 0);
					}
				}
			}
			void push_back (const value_type& val)
			{
				resize(size() + 1, val);
			}
			void pop_back()
			{
				if (size() > 0)
					_alloc.destroy(_end-- - 1);
			}
			reference		at( size_type pos )
			{
				if (pos < 0)
					throw std::out_of_range("vector");
				else if (pos >= size())
					throw std::out_of_range("vector");
				return (*(_start + pos));
			}
			const_reference	at( size_type pos ) const
			{
				if (pos < 0)
					throw std::out_of_range("vector");
				else if (pos >= size())
					throw std::out_of_range("vector");
				return (*(_start + pos));
			}
			reference		operator[]( size_type pos )
			{
				return (*(_start + pos));
			}
			const_reference	operator[]( size_type pos ) const
			{
				return (*(_start + pos));
			}
			reference		front()
			{
				return (*_start);
			}
			const_reference	front() const
			{
				return (*_start);
			}
			reference		back()
			{
				return (*(_end - 1));
			}
			const_reference	back() const
			{
				return (*(_end - 1));
			}
			iterator begin()
			{
				return (_start);
			}
			iterator end()
			{
				return (_end);
			}
			reverse_iterator rbegin()
			{
				return (_end - 1);
			}
			reverse_iterator rend()
			{
				return (_start - 1);
			}
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