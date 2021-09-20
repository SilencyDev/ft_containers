/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmacquet <kmacquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/03 13:24:26 by kmacquet          #+#    #+#             */
/*   Updated: 2021/09/20 11:39:22 by kmacquet         ###   ########.fr       */
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
			typedef T											value_type;
			typedef Alloc										allocator_type;
			typedef typename allocator_type::reference			reference;
			typedef typename allocator_type::const_reference	const_reference;
			typedef size_t										size_type;
			typedef ptrdiff_t									difference_type;
			typedef typename allocator_type::pointer			pointer;
			typedef typename allocator_type::const_pointer		const_pointer;
			typedef ft::random_access_iterator<value_type>		iterator;
			typedef ft::reverse_iterator<value_type>			reverse_iterator;
		
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
			vector(const vector& x)
			{
				_start = NULL;
				_end = NULL;
				_capacity = 0;
				if (this != &x)
					*this = x;
			}

			~vector()
			{
				int tmp = _capacity;
				while (_capacity--)
					_alloc.destroy(_start + _capacity);
				_alloc.deallocate(_start, tmp);
			}
			void assign(size_type n, const value_type& val)
			{
				pointer ptr = _start;
				for (; ptr != _end; ptr++)
					_alloc.destroy(ptr);
				_end = _start;
				resize(n, val);
			}
			// template< class InputIt >
			// void assign( InputIt first, InputIt last )
			// {
			// 	this->clear();
			// 	for(; first != last + 1; first++)
			// 		push_back(*first);
			// }
			vector& operator=(vector const & src)
			{
				if (this->size())
				{
					pointer ptr = _start;
					for (; ptr != _end; ptr++)
						_alloc.destroy(ptr);
					this->_alloc.deallocate(_start, _capacity);
					_end = _start;
				}
				_start = this->_alloc.allocate(src.size());
				for(size_type i = 0; i < src.size(); i++)
					_alloc.construct(_start + i, *(src._start + i));
				_capacity = src.size();
				_end = _start + src.size();
				return (*this);
			}
			allocator_type	get_allocator() const
			{
				return (_alloc);
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
			bool empty() const {
				return (size() ? 1 : 0);
			}
			iterator insert(iterator position, const value_type& val)
			{
				value_type lastval = *(_end - 1);
				pointer tmp = _end - 1;
				for(; tmp != &(*position); tmp--)
				{
					_alloc.destroy(tmp);
					_alloc.construct(tmp, *(tmp - 1));
				}
				_alloc.destroy(&(*position));
				_alloc.construct(&(*position), val);
				*position = val;
				size_type tmp2 = &(*position) - _start + 1;
				push_back(lastval);
				return (_start + tmp2);
			}
			void insert (iterator position, size_type n, const value_type& val)
			{
				iterator pos = position;
				while (n--)
					pos = insert(pos, val);
			}
			template <class InputIterator>
			void insert (iterator position, InputIterator first, InputIterator last)
			{
				iterator pos = position;
				pointer ptr = &(*first);
				for (; ptr != &(*(last + 1)); ptr++)
					pos = insert(pos, *ptr);
			}
			iterator erase(iterator position)
			{
				pointer ptr = &(*position);
				_alloc.destroy(ptr);
				if (ptr != _end - 1)
				{
					for (; ptr != _end;)
					{
						_alloc.construct(ptr, *(ptr + 1));
						_alloc.destroy(ptr++ + 1);
					}
				}
				_end -= 1;
				return (&(*position));
			}
			iterator erase(iterator first, iterator last)
			{
				pointer ptr1 = &(*first);
				size_type diff = &(*last) - ptr1 + 1;
				if (&(*last) != _end - 1)
				{
					for (; (ptr1 + diff) != _end;)
					{
						_alloc.construct(ptr1, *(ptr1 + diff));
						_alloc.destroy(ptr1++ + diff);
					}
				}
				else
					for (; ptr1 != _end; ptr1++)
						_alloc.destroy(ptr1);
				_end -= diff;
				return (&(*first));
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
				while (current_size--)
					_alloc.construct(fresh + current_size, *(_start + current_size));
				current_size = size();
				while (current_size--)
					_alloc.destroy(_start + current_size);
				_alloc.deallocate(_start, tmp);
				current_size = size();
				_start = fresh;
				_end = _start + current_size;
				this->_capacity = n;
			}
			void resize (size_type n, value_type val = value_type())
			{
				size_type	newsize;
				size_type	oldsize = size();
				if (n > _capacity)
				{
					if (_capacity == 0)
						newsize = 1;
					else if (_capacity < SIZE_MAX / 2)
						newsize = _capacity * 2;
					else
						newsize = SIZE_MAX;
					if (n > _capacity)
						newsize = n;
					reserve(newsize);
					size_type	tmp = n;
					_end = _start + tmp;
					while (oldsize < tmp--)
						_alloc.construct(_start + tmp, val);
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
					_end = _start + n;
					while (oldsize < tmp--)
						_alloc.construct(_start + tmp, val);
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
			void clear()
			{
				size_type tmp = size();
				while (tmp--)
					_alloc.destroy(_start + tmp);
				_end = _start;
			}
			void swap (vector& x)
			{
				pointer ptr = x._start;
				x._start = this->_start;
				this->_start = ptr;

				ptr = x._end;
				x._end = this->_end;
				this->_end = ptr;

				allocator_type alloc = x._alloc;
				x._alloc = this->_alloc;
				this->_alloc = alloc;

				size_type capacity = x._capacity;
				x._capacity = this->_capacity;
				this->_capacity = capacity;
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

	template <class T, class Alloc>
	void swap(ft::vector<T,Alloc>& x, ft::vector<T,Alloc>& y)
	{
		x.swap(y);
	}

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

};

#endif