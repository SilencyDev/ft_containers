/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmacquet <kmacquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/03 13:24:26 by kmacquet          #+#    #+#             */
/*   Updated: 2021/09/27 15:42:41 by kmacquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_HPP
# define VECTOR_HPP
# include <iostream>
# include <memory>
# include <iterator> // distance
# include <limits>
# include "iterator.hpp"
# include "enable_if.hpp"

namespace ft {

	template<class T, class Alloc = std::allocator<T> >
	class vector
	{
		public :
			typedef T														value_type;
			typedef Alloc													allocator_type;
			typedef typename allocator_type::reference						reference;
			typedef typename allocator_type::const_reference				const_reference;
			typedef size_t													size_type;
			typedef typename allocator_type::pointer						pointer;
			typedef typename allocator_type::const_pointer					const_pointer;
			typedef typename ft::random_access_iterator<pointer>			iterator;
			typedef typename ft::random_access_iterator<const_pointer>		const_iterator;
			typedef typename ft::reverse_iterator<iterator>					reverse_iterator;
			typedef typename ft::reverse_iterator<const_iterator>			const_reverse_iterator;
			typedef typename iterator_traits<iterator>::difference_type		difference_type;
		
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
			template <class InputIterator>
			vector(InputIterator first, InputIterator last,
			const allocator_type& alloc = allocator_type(),
			typename ft::enable_if<ft::is_integral<InputIterator>::value>::type * = NULL)
			{
				pointer		ptr = &(*first);
				size_type	diff = &(*last) - &(*first);
				_alloc = alloc;
				_start = _alloc.allocate(diff);
				for (size_type i = 0; ptr + i != &(*last); i++)
					_alloc.construct(_start + i, *(ptr + i));
				_end = _start + diff;
				_capacity = diff;
			}
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
				this->clear();
				reserve(n);
				_end = _start;
				for(size_type i = 0; _start + i != _start + n; i++) {
						_alloc.construct(_start + i, val);
						_end++;
				}
				resize(n, val);
			}
			template< class InputIt >
			typename ft::enable_if<ft::is_integral<InputIt>::value, void>::type
			assign( InputIt first, InputIt last )
			{
				this->clear();
				size_type n = std::distance(first, last);
				if (_capacity >= n)
				{
					for(; first != last; first++)
						push_back(*first);
				}
				else
				{
					reserve(n);
					_end = _start;
					for(; first != last; first++) {
						_alloc.construct(_end, *first);
						_end++;
					}
				}
			}
			vector& operator=(vector const & src)
			{
				assign(src.begin(), src.end());
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
			bool empty() const
			{
				if (size())
					return (0);
				return (1);
			}
			iterator insert(iterator position, const value_type& val)
			{
				if (position == NULL)
					reserve(1);
				if (position < _start || position >= _end)
					position = _start;
				size_type tmp2 = &(*position) - _start;
				push_back(*(_end - 1));
				pointer tmp = _end - 1;
				for(; tmp != (_start + tmp2); tmp--)
				{
					_alloc.destroy(tmp);
					_alloc.construct(tmp, *(tmp - 1));
				}
				_alloc.destroy(&(*position));
				_alloc.construct(&(*position), val);
				return (_start + tmp2);
			}
			void insert (iterator position, size_type n, const value_type& val)
			{
				if (position == NULL)
					reserve(1);
				if (position + n < _start || position + n >= _end)
					position = _start;
				iterator pos = position;
				while (n--)
					pos = insert(pos, val);
			}
			template <class InputIterator>
			typename ft::enable_if<ft::is_integral<InputIterator>::value, void>::type
			insert (iterator position, InputIterator first, InputIterator last)
			{
				iterator pos = position;
				InputIterator ptr = first;
				for (; ptr.base() != last.base(); ptr++)
					pos = insert(pos, *(ptr.base()));
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
				size_type diff = &(*last) - ptr1;
				if (&(*last) != _end)
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
					if (n > newsize)
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
				for (;_start != _end ; _end--)
					_alloc.destroy(_end - 1);
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

				// allocator_type alloc = x._alloc;
				// x._alloc = this->_alloc;
				// this->_alloc = alloc;

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
			const_iterator begin() const
			{
				return (_start);
			}
			const_iterator end() const
			{
				return (_end);
			}
			reverse_iterator rbegin()
			{
				return reverse_iterator(end());
			}
			reverse_iterator rend()
			{
				return reverse_iterator(begin());
			}
	};

	template <class T, class Alloc>
	void swap(ft::vector<T,Alloc>& x, ft::vector<T,Alloc>& y)
	{
		x.swap(y);
	}

	template <class InputIt1, class InputIt2>
	bool lexicographical_compare(InputIt1 first1, InputIt1 last1,
									InputIt2 first2, InputIt2 last2)
	{
		while (first1 != last1)
		{
			if (first2 == last2 || *first2 < *first1)
				return (false);
			else if (*first1 < *first2)
				return (true);
			++first1;
			++first2;
		}
		return (first2 != last2);
	}

	template< class T, class Alloc >
	bool operator==(const ft::vector<T,Alloc> & lhs, const ft::vector<T,Alloc> & rhs)
	{
		if (lhs.size() != rhs.size())
			return (false);
		return (!(lhs < rhs) && !(rhs < lhs));
	}

	template< class T, class Alloc >
	bool operator!=(const ft::vector<T,Alloc> & lhs, const ft::vector<T,Alloc> & rhs)
	{
		return (!(lhs == rhs));
	}

	template< class T, class Alloc >
	bool operator<(const ft::vector<T,Alloc> & lhs, const ft::vector<T,Alloc> & rhs)
	{
		typename ft::vector<T, Alloc>::const_iterator end = lhs.end();
		typename ft::vector<T, Alloc>::const_iterator end2 = rhs.end();

		return (lexicographical_compare(lhs.begin(), --end, rhs.begin(), --end2));
	}

	template< class T, class Alloc >
	bool operator<=(const ft::vector<T,Alloc> & lhs, const ft::vector<T,Alloc> & rhs)
	{
		return (!(rhs < lhs));
	}

	template< class T, class Alloc >
	bool operator>(const ft::vector<T,Alloc> & lhs, const ft::vector<T,Alloc> & rhs)
	{
		typename ft::vector<T, Alloc>::const_iterator end = lhs.end();
		typename ft::vector<T, Alloc>::const_iterator end2 = rhs.end();

		return (lexicographical_compare(rhs.begin(), --end2, lhs.begin(), --end));
	}

	template< class T, class Alloc >
	bool operator>=(const ft::vector<T,Alloc> & lhs, const ft::vector<T,Alloc> & rhs)
	{
		return (!(lhs < rhs));
	}
};

#endif