/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmacquet <kmacquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/03 13:24:26 by kmacquet          #+#    #+#             */
/*   Updated: 2021/09/15 17:36:21 by kmacquet         ###   ########.fr       */
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
			typedef ft::reverse_iterator<T>				reverse_iterator;
		
		protected :
			pointer			_start;
			pointer			_end;
			size_type		_capacity;
			size_type		_current;
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
			}
			// template <class InputIterator>
			// vector(InputIterator first, InputIterator last,
			// 	const allocator_type& alloc = allocator_type());
			// vector(const vector& x);

			~vector()
			{
				int tmp = _capacity;
				while (_capacity--)
				{
					_alloc.destroy(_start + _capacity);
				}
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
				return (this->_current);
			};
			size_type		max_size() const
			{
				return (std::numeric_limits<size_type>::max());
			};
			size_type		capacity() const
			{
				return (this->_capacity);
			};
			bool empty() const
			{
				return (size() ? 1 : 0);
			}
			void reserve(size_type n)
			{
				if (n <= this->_capacity)
					return ;
				pointer		fresh = _alloc.allocate(n);
				size_type	current_size = _current;
				size_type	tmp = _capacity;
				this->_capacity = n;
				while (current_size--)
				{
					_alloc.construct(fresh + current_size, *(_start + current_size));
				}
				current_size = _current;
				while (current_size--)
					_alloc.destroy(_start + current_size);
				_alloc.deallocate(_start, tmp);
				_start = fresh;
				_end = _start + _current;
			}
			void resize (size_type n, value_type val = value_type())
			{
				if (n > _capacity)
				{
					size_type	tmp = _capacity;
					reserve(n);
					_end = _start + n;
					_current = n;
					while (tmp < n--)
					{
						if (val)
							_alloc.construct(_start + n, val);
						else
							_alloc.construct(_start + n, 0);
					}
				}
				else if (n < _capacity)
				{
					pointer		fresh = _alloc.allocate(n);
					size_type	current_size = _current;
					size_type	tmp = _capacity;
					_capacity = n;
					_current = n;
					while (n--)
					{
						_alloc.construct(fresh + n, *(_start + n));
					}
					while (current_size--)
						_alloc.destroy(_start + current_size);
					_alloc.deallocate(_start, tmp);
					_start = fresh;
					_end = _start + _current;
				}
			}
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