/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterator.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmacquet <kmacquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/07 14:19:19 by kmacquet          #+#    #+#             */
/*   Updated: 2021/09/21 12:31:35 by kmacquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ITERATOR_HPP
# define ITERATOR_HPP
# include <iostream>

namespace ft {
	template <class Category,
			class T,
			class Distance = ptrdiff_t,
			class Pointer = T*,
			class Reference = T&
			>
		struct iterator {
			typedef T			value_type;
			typedef Distance	difference_type;
			typedef Pointer		pointer;
			typedef Reference	reference;
			typedef Category	iterator_category;
		};

	struct random_access_iterator_tag {};

	template <class iterator>
	struct iterator_traits {
		typedef typename	iterator::value_type			value_type;
		typedef typename	iterator::difference_type		difference_type;
		typedef typename	iterator::pointer				pointer;
		typedef typename	iterator::reference				reference;
		typedef typename	iterator::iterator_category		iterator_category;
	};

	template <class T>
	class iterator_traits<T*> {
		typedef	T								value_type;
		typedef	ptrdiff_t						difference_type;
		typedef	T*								pointer;
		typedef	T&								reference;
		typedef	ft::random_access_iterator_tag	iterator_category;
	};

	template <class T>
	class iterator_traits<const T*> {
		typedef	T								value_type;
		typedef	ptrdiff_t						difference_type;
		typedef	const T*						pointer;
		typedef	const T&						reference;
		typedef	ft::random_access_iterator_tag	iterator_category;
	};

	template <class T>
	class random_access_iterator : public iterator<ft::random_access_iterator_tag, T>
	{
		public :
			typedef typename ft::iterator<ft::random_access_iterator_tag, T>::value_type		value_type;
			typedef typename ft::iterator<ft::random_access_iterator_tag, T>::difference_type	difference_type;
			typedef typename ft::iterator<ft::random_access_iterator_tag, T>::pointer			pointer;
			typedef typename ft::iterator<ft::random_access_iterator_tag, T>::reference			reference;
			typedef typename ft::iterator<ft::random_access_iterator_tag, T>::iterator_category	iterator_category;
		public :
			random_access_iterator(void) : _current(NULL) {}
			random_access_iterator(pointer ptr) : _current(ptr) {}
			random_access_iterator(random_access_iterator const &rhs) : _current(rhs._current) {}
			random_access_iterator &operator=(random_access_iterator const &rhs)
			{
				this->_current = rhs._current;
				return (*this);
			}
			random_access_iterator &operator++(void)
			{
				this->_current++;
				return (*this);
			}
			random_access_iterator operator++(int)
			{
				random_access_iterator tmp(*this);

				operator++();
				return (tmp);
			}
			random_access_iterator &operator--(void)
			{
				this->_current--;
				return (*this);
			}
			random_access_iterator operator--(int)
			{
				random_access_iterator tmp(*this);

				operator--();
				return (tmp);
			}
			bool operator==(random_access_iterator const &rhs)
			{
				return (this->_current == rhs._current);
			}
			bool operator!=(random_access_iterator const &rhs)
			{
				return (this->_current != rhs._current);
			}
			bool operator<=(random_access_iterator const &rhs)
			{
				return (this->_current <= rhs._current);
			}
			bool operator>=(random_access_iterator const &rhs)
			{
				return (this->_current >= rhs._current);
			}
			bool operator>(random_access_iterator const &rhs)
			{
				return (this->_current > rhs._current);
			}
			bool operator<(random_access_iterator const &rhs)
			{
				return (this->_current < rhs._current);
			}
			reference operator+=(random_access_iterator const &rhs)
			{
				this->_current = this->_current + rhs._current;
				return (this->_current);
			}
			reference operator-=(random_access_iterator const &rhs)
			{
				this->_current = this->_current - rhs._current;
				return (this->_current);
			}
			reference operator*()
			{
				return (*(this->_current));
			}
			reference operator->()
			{
				return (*(this->_current));
			}
		protected :
			pointer _current;
	};

	template <class T>
	class reverse_iterator : public iterator<ft::random_access_iterator_tag, T>
	{
		public :
			typedef typename ft::iterator<ft::random_access_iterator_tag, T>::value_type		value_type;
			typedef typename ft::iterator<ft::random_access_iterator_tag, T>::difference_type	difference_type;
			typedef typename ft::iterator<ft::random_access_iterator_tag, T>::pointer			pointer;
			typedef typename ft::iterator<ft::random_access_iterator_tag, T>::reference			reference;
			typedef typename ft::iterator<ft::random_access_iterator_tag, T>::iterator_category	iterator_category;
		public :
			reverse_iterator(void) : _current(NULL) {}
			reverse_iterator(pointer ptr) : _current(ptr) {}
			reverse_iterator(reverse_iterator const &rhs) : _current(rhs._current) {}
			reverse_iterator &operator=(reverse_iterator const &rhs)
			{
				this->_current = rhs._current;
				return (*this);
			}
			reverse_iterator &operator++(void)
			{
				this->_current--;
				return (*this);
			}
			reverse_iterator operator++(int)
			{
				reverse_iterator tmp(*this);

				operator++();
				return (tmp);
			}
			reverse_iterator &operator--(void)
			{
				this->_current++;
				return (*this);
			}
			reverse_iterator operator--(int)
			{
				reverse_iterator tmp(*this);

				operator++();
				return (tmp);
			}
			bool operator==(reverse_iterator const &rhs)
			{
				return (this->_current == rhs._current);
			}
			bool operator!=(reverse_iterator const &rhs)
			{
				return (this->_current != rhs._current);
			}
			bool operator<=(reverse_iterator const &rhs)
			{
				return (this->_current <= rhs._current);
			}
			bool operator>=(reverse_iterator const &rhs)
			{
				return (this->_current >= rhs._current);
			}
			bool operator>(reverse_iterator const &rhs)
			{
				return (this->_current > rhs._current);
			}
			bool operator<(reverse_iterator const &rhs)
			{
				return (this->_current < rhs._current);
			}
			reference operator+=(reverse_iterator const &rhs)
			{
				this->_current = this->_current + rhs._current;
				return (this->_current);
			}
			reference operator-=(reverse_iterator const &rhs)
			{
				this->_current = this->_current - rhs._current;
				return (this->_current);
			}
			reference operator*()
			{
				return (*(this->_current));
			}
			reference operator->()
			{
				return (*(this->_current));
			}
		protected :
			pointer _current;
	};
};

#endif