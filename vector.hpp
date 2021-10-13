/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmacquet <kmacquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/03 13:24:26 by kmacquet          #+#    #+#             */
/*   Updated: 2021/10/13 13:59:52 by kmacquet         ###   ########.fr       */
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
				_capacity = std::distance(first,last);
				_alloc = alloc;
				_start = _alloc.allocate(_capacity);
				_end = _start + _capacity;
				assign(first, last);
			}
			vector(const vector& x)
			{
				_start = NULL;
				_end = NULL;
				_capacity = 0;
				_alloc = x._alloc;
				if (this != &x)
					*this = x;
			}

			~vector()
			{
				int tmp = size();
				while (tmp--)
					_alloc.destroy(_start + tmp);
				_alloc.deallocate(_start, _capacity);
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
				if (*this != src)
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
				size_type tmp2 = 0;
				if (position.base() != NULL && position.base() < _start)
					position = _start;
				else if (position.base() != NULL && position.base() > _end)
					position = _end;
				else if (position.base() == NULL)
				{
					reserve(1);
					push_back(val);
					return (_end - 1);
				}
				else if (position.base() == _end && position.base() != _start)
				{
					push_back(val);
					return (_end - 1);
				}
				tmp2 = position.base() - _start;
				push_back(*(_end - 1));
				position = _start + tmp2;
				pointer tmp = _end - 1;
				for(; tmp != (_start + tmp2); tmp--)
				{
						_alloc.destroy(tmp);
						_alloc.construct(tmp, *(tmp - 1));
				}
				_alloc.destroy(position.base());
				_alloc.construct(position.base(), val);
				return (position);
			}
			void insert (iterator position, size_type n, const value_type& val)
			{
				if (position.base() != NULL && position.base() < _start)
					position = _start;
				else if (position.base() != NULL && position.base() > _end)
					position = _end;
				difference_type dist = std::distance(iterator(_start), position);
				if (_start == NULL)
					reserve(1);
				if (_capacity < n + size())
				{
					reserve(_capacity * 2);
					if (_capacity < n + size())
						reserve(n + size());
				}
				ft::vector<value_type> tmp;

				pointer save_start = _start;
				tmp._start = _alloc.allocate(_capacity);
				tmp._capacity = _capacity;
				tmp._end = tmp._start;
				
				pointer pos = _start + dist;
				for (; _start != pos; _start++)
					_alloc.construct(tmp._end++, *_start);
				for (size_type i = 0; i < n; i++)
					_alloc.construct(tmp._end++, val);
				for (;_start != _end; _start++)
					_alloc.construct(tmp._end++, *_start);
				
				_start = save_start;
				swap(tmp);
			}
			template <class InputIterator>
			typename ft::enable_if<ft::is_integral<InputIterator>::value, void>::type
			insert (iterator position, InputIterator first, InputIterator last)
			{
				if (position.base() != NULL && position.base() < _start)
					position = _start;
				else if (position.base() != NULL && position.base() > _end)
					position = _end;
				difference_type dist = std::distance(first, last);
				difference_type range_pos = std::distance(iterator(_start), position);
				if (_start == NULL)
					reserve(1);
				if (_capacity < dist + size())
				{
					reserve(_capacity * 2);
					if (_capacity < dist + size())
						reserve(dist + size());
				}
				ft::vector<value_type> tmp;

				pointer save_start = _start;
				tmp._start = _alloc.allocate(_capacity);
				tmp._capacity = _capacity;
				tmp._end = tmp._start;
				
				pointer pos = _start + range_pos;
				for (; _start != pos; _start++)
					_alloc.construct(tmp._end++, *_start);
				for (; first != last; first++)
					_alloc.construct(tmp._end++, *(first));
				for (;_start != _end; _start++)
					_alloc.construct(tmp._end++, *_start);
				
				_start = save_start;
				swap(tmp);
			}
			iterator erase(iterator position)
			{
				pointer ptr = position.base();
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
				return (position.base());
			}
			iterator erase(iterator first, iterator last)
			{
				pointer ptr1 = first.base();
				size_type diff = last.base() - ptr1;
				if (last.base() != _end)
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
				return (first.base());
			}
			void reserve(size_type n)
			{
				if (n > max_size())
					throw std::length_error("allocator<T>::allocate(size_t n) 'n' exceeds maximum supported size");
				if (n <= _capacity)
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
				_capacity = n;
			}
			void resize (size_type n, value_type val = value_type())
			{
				size_type	newsize = 0;
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
					size_type tmp = size();
					while (n < tmp--)
						_alloc.destroy(_start + tmp);
					_end = _start + n;
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
				value_type	tmp = val;
				size_type	newsize = 0;
				if (size() + 1 > _capacity)
				{
					if (_capacity == 0)
						newsize = 1;
					else if (_capacity + 1 < SIZE_MAX / 2)
						newsize = _capacity * 2;
					else
						newsize = SIZE_MAX;
					reserve(newsize);
				}
				_alloc.construct(_end++, tmp);
				// resize(size() + 1, val);
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
			const_reverse_iterator rbegin() const
			{
				return const_reverse_iterator(end());
			}
			const_reverse_iterator rend() const
			{
				return const_reverse_iterator(begin());
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

	template <class InputIterator1, class InputIterator2>
	bool equal ( InputIterator1 first1, InputIterator1 last1, InputIterator2 first2 )
	{
		while (first1!=last1) {
			if (!(*first1 == *first2))   // or: if (!pred(*first1,*first2)), for version 2
				return (false);
			++first1; ++first2;
		}
		return (true);
	}

	template< class T, class Alloc >
	bool operator==(const ft::vector<T,Alloc> & lhs, const ft::vector<T,Alloc> & rhs)
	{
		if (lhs.size() != rhs.size())
			return (false);
		return (ft::equal(lhs.begin(), lhs.end(), rhs.begin()));
	}

	template< class T, class Alloc >
	bool operator!=(const ft::vector<T,Alloc> & lhs, const ft::vector<T,Alloc> & rhs)
	{
		return (!(lhs == rhs));
	}

	template< class T, class Alloc >
	bool operator<(const ft::vector<T,Alloc> & lhs, const ft::vector<T,Alloc> & rhs)
	{
		return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
	}

	template< class T, class Alloc >
	bool operator<=(const ft::vector<T,Alloc> & lhs, const ft::vector<T,Alloc> & rhs)
	{
		return (!(rhs < lhs));
	}

	template< class T, class Alloc >
	bool operator>(const ft::vector<T,Alloc> & lhs, const ft::vector<T,Alloc> & rhs)
	{
		return (ft::lexicographical_compare(rhs.begin(), rhs.end(), lhs.begin(), lhs.end()));
	}

	template< class T, class Alloc >
	bool operator>=(const ft::vector<T,Alloc> & lhs, const ft::vector<T,Alloc> & rhs)
	{
		return (!(lhs < rhs));
	}
};

#endif