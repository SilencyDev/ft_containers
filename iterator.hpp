/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterator.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmacquet <kmacquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/07 14:19:19 by kmacquet          #+#    #+#             */
/*   Updated: 2021/10/20 11:48:10 by kmacquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ITERATOR_HPP
# define ITERATOR_HPP
# include <iostream>
# include "pair.hpp"
# include "node.hpp"

namespace ft {

	template <class iterator>
	struct iterator_traits {
		typedef typename	iterator::value_type			value_type;
		typedef typename	iterator::difference_type		difference_type;
		typedef typename	iterator::pointer				pointer;
		typedef typename	iterator::reference				reference;
		typedef typename	iterator::iterator_category		iterator_category;
	};

	template <class T>
	struct iterator_traits<T*> {
		typedef	T								value_type;
		typedef	ptrdiff_t						difference_type;
		typedef	T*								pointer;
		typedef	T&								reference;
		typedef	std::random_access_iterator_tag	iterator_category;
	};

	template <class T>
	struct iterator_traits<const T*> {
		typedef	T								value_type;
		typedef	ptrdiff_t						difference_type;
		typedef	const T*						pointer;
		typedef	const T&						reference;
		typedef	std::random_access_iterator_tag	iterator_category;
	};

	template < class T >
	class bidirectional_iterator
	{
		// private :
		// 	typedef iterator_traits<T> it;
		public :
			typedef T											value_type;
			typedef value_type*									pointer;
			typedef value_type&									reference;
			typedef node<value_type>							node;
			typedef node*										node_ptr;
			typedef ptrdiff_t									difference_type;
			typedef typename std::bidirectional_iterator_tag	iterator_category;

			bidirectional_iterator(void) : _current(NULL), _last(NULL) {}
			bidirectional_iterator(node_ptr ptr, node_ptr last = NULL) : _current(ptr), _last(last) {}
			template <class Ts>
			bidirectional_iterator (const ft::bidirectional_iterator<Ts>& it) : _current(it.base_node()), _last(it._last) {}
			~bidirectional_iterator(void) {}
			node_ptr	_current;
			node_ptr	_last;

			bidirectional_iterator &operator++(void)
			{
				// std::cout << "HERE ++ : " << std::endl;

				if (_current == _last)
				{
					_current = _current->NIL;
					return *this;
				}
				if (!_current->NIL)
					return (*this);
				if (_current->right->NIL)
				{
					_current = _current->right;
					while (_current->left->NIL)
						_current = _current->left;
				}
				else
				{
					while (_current->parent->NIL && _current == _current->parent->right)
						_current = _current->parent;
					_current = _current->parent;
				}
				return (*this);
			}
			bidirectional_iterator operator++(int)
			{
				bidirectional_iterator tmp(*this);

				operator++();
				return (tmp);
			}
			bidirectional_iterator &operator--(void)
			{
				// std::cout << "HERE-- :" << std::endl;
				if (!_current->NIL)
				{
					_current = _last;
					return *this;
				}
				if (_current->left->NIL)
				{
					_current = _current->left;
					while (_current->right->NIL)
						_current = _current->right;
				}
				else
				{
					while (_current->parent->NIL && _current == _current->parent->left)
						_current = _current->parent;
					_current = _current->parent;
				}
				return *this;
			}
			bidirectional_iterator operator--(int)
			{
				bidirectional_iterator tmp(*this);

				operator--();
				return (tmp);
			}
			template<class Ts>
			bidirectional_iterator &operator=(ft::bidirectional_iterator<Ts> const &rhs)
			{
				this->_current = rhs.base_node();
				return (*this);
			}
			value_type &operator*() const
			{
				return (_current->content);
			}
			pointer operator->() const
			{
				return (&(operator*()));
			}
			pointer base() const
			{
				return (&(_current->content));
			}
			node_ptr	base_node() const
			{
				return (_current);
			}
	};

	template <class T1, class T2>
	bool operator==(ft::bidirectional_iterator<T1> const &lhs,
					ft::bidirectional_iterator<T2> const &rhs)
	{
		return (lhs.base() == rhs.base());
	}
	template <class T1, class T2>
	bool operator!=(ft::bidirectional_iterator<T1> const &lhs,
					ft::bidirectional_iterator<T2> const &rhs)
	{
		return (lhs.base() != rhs.base());
	}
	// template <class T1, class T2>
	// bool operator<=(ft::bidirectional_iterator<T1> const &lhs,
	// 				ft::bidirectional_iterator<T2> const &rhs)
	// {
	// 	return (lhs.base() <= rhs.base());
	// }
	// template <class T1, class T2>
	// bool operator>=(ft::bidirectional_iterator<T1> const &lhs,
	// 				ft::bidirectional_iterator<T2> const &rhs)
	// {
	// 	return (lhs.base() >= rhs.base());
	// }
	// template <class T1, class T2>
	// bool operator>(ft::bidirectional_iterator<T1> const &lhs,
	// 				ft::bidirectional_iterator<T2> const &rhs)
	// {
	// 	return (lhs.base() > rhs.base());
	// }
	// template <class T1, class T2>
	// bool operator<(ft::bidirectional_iterator<T1> const &lhs,
	// 				ft::bidirectional_iterator<T2> const &rhs)
	// {
	// 	return (lhs.base() < rhs.base());
	// }

	template < class T >
	class const_bidirectional_iterator
	{
		// private :
		// 	typedef iterator_traits<T> it;
		public :
			typedef T											value_type;
			typedef value_type*									pointer;
			typedef value_type&									reference;
			typedef node<value_type>							node;
			typedef node*										node_ptr;
			typedef ptrdiff_t									difference_type;
			typedef typename std::bidirectional_iterator_tag	iterator_category;

			const_bidirectional_iterator(void) : _current(NULL), _last(NULL) {}
			const_bidirectional_iterator(node_ptr ptr, node_ptr last = NULL) : _current(ptr), _last(last) {}
			template <class Ts>
			const_bidirectional_iterator (const ft::const_bidirectional_iterator<Ts>& it) : _current(it.base_node()), _last(it._last) {}
			template <class Ts>
			const_bidirectional_iterator (const ft::bidirectional_iterator<Ts>& it) : _current(reinterpret_cast<node_ptr>(it.base_node())), _last(reinterpret_cast<node_ptr>(it._last)) {}
			~const_bidirectional_iterator(void) {}
			node_ptr	_current;
			node_ptr	_last;
			const_bidirectional_iterator &operator++(void)
			{
				// std::cout << "HERE++ const : " << _current << std::endl;
				if (_current == _last)
				{
					_current = _current->NIL;
					return *this;
				}
				if (!_current->NIL)
					return *this;
				if (_current->right->NIL)
				{
					_current = _current->right;
					while (_current->left->NIL)
						_current = _current->left;
				}
				else
				{
					while (_current->parent->NIL && _current == _current->parent->right)
						_current = _current->parent;
					_current = _current->parent;
				}
				return *this;
			}
			const_bidirectional_iterator operator++(int)
			{
				const_bidirectional_iterator tmp(*this);

				operator++();
				return (tmp);
			}
			const_bidirectional_iterator &operator--(void)
			{
				// std::cout << "HERE-- const : " << _current << std::endl;
				if (!_current->NIL)
				{
					_current = _last;
					return *this;
				}
				
				if (_current->left->NIL)
				{
					_current = _current->left;
					while (_current->right->NIL)
						_current = _current->right;
				}
				else
				{
					while (_current->parent->NIL && _current == _current->parent->left)
						_current = _current->parent;
					_current = _current->parent;
				}
				return (*this);
			}
			const_bidirectional_iterator operator--(int)
			{
				const_bidirectional_iterator tmp(*this);

				operator--();
				return (tmp);
			}
			template<class Ts>
			const_bidirectional_iterator &operator=(ft::const_bidirectional_iterator<Ts> const &rhs)
			{
				this->_current = rhs.base_node();
				return (*this);
			}
			value_type &operator*() const
			{
				return (_current->content);
			}
			pointer operator->() const
			{
				return (&(operator*()));
			}
			pointer base() const
			{
				return (&(_current->content));
			}
			node_ptr	base_node() const
			{
				return (_current);
			}
	};

	template <class T1, class T2>
	bool operator==(ft::const_bidirectional_iterator<T1> const &lhs,
					ft::const_bidirectional_iterator<T2> const &rhs)
	{
		return (lhs.base() == rhs.base());
	}
	template <class T1, class T2>
	bool operator!=(ft::const_bidirectional_iterator<T1> const &lhs,
					ft::const_bidirectional_iterator<T2> const &rhs)
	{
		return (lhs.base() != rhs.base());
	}
	// template <class T1, class T2>
	// bool operator<=(ft::const_bidirectional_iterator<T1> const &lhs,
	// 				ft::const_bidirectional_iterator<T2> const &rhs)
	// {
	// 	return (lhs.base() <= rhs.base());
	// }
	// template <class T1, class T2>
	// bool operator>=(ft::const_bidirectional_iterator<T1> const &lhs,
	// 				ft::const_bidirectional_iterator<T2> const &rhs)
	// {
	// 	return (lhs.base() >= rhs.base());
	// }
	// template <class T1, class T2>
	// bool operator>(ft::const_bidirectional_iterator<T1> const &lhs,
	// 				ft::const_bidirectional_iterator<T2> const &rhs)
	// {
	// 	return (lhs.base() > rhs.base());
	// }
	// template <class T1, class T2>
	// bool operator<(ft::const_bidirectional_iterator<T1> const &lhs,
	// 				ft::const_bidirectional_iterator<T2> const &rhs)
	// {
	// 	return (lhs.base() < rhs.base());
	// }

	// const / bi
		template <class T1, class T2>
	bool operator==(ft::const_bidirectional_iterator<T1> const &lhs,
					ft::bidirectional_iterator<T2> const &rhs)
	{
		return (lhs.base() == rhs.base());
	}
	template <class T1, class T2>
	bool operator!=(ft::const_bidirectional_iterator<T1> const &lhs,
					ft::bidirectional_iterator<T2> const &rhs)
	{
		return (lhs.base() != rhs.base());
	}
	// template <class T1, class T2>
	// bool operator<=(ft::const_bidirectional_iterator<T1> const &lhs,
	// 				ft::bidirectional_iterator<T2> const &rhs)
	// {
	// 	return (lhs.base() <= rhs.base());
	// }
	// template <class T1, class T2>
	// bool operator>=(ft::const_bidirectional_iterator<T1> const &lhs,
	// 				ft::bidirectional_iterator<T2> const &rhs)
	// {
	// 	return (lhs.base() >= rhs.base());
	// }
	// template <class T1, class T2>
	// bool operator>(ft::const_bidirectional_iterator<T1> const &lhs,
	// 				ft::bidirectional_iterator<T2> const &rhs)
	// {
	// 	return (lhs.base() > rhs.base());
	// }
	// template <class T1, class T2>
	// bool operator<(ft::const_bidirectional_iterator<T1> const &lhs,
	// 				ft::bidirectional_iterator<T2> const &rhs)
	// {
	// 	return (lhs.base() < rhs.base());
	// }

	template < class T >
	class random_access_iterator
	{
		private :
			typedef iterator_traits<T> it;
		public :
			typedef typename it::value_type			value_type;
			typedef typename it::difference_type	difference_type;
			typedef typename it::pointer			pointer;
			typedef typename it::reference			reference;
			typedef typename it::iterator_category	iterator_category;

			random_access_iterator(void) : _current(NULL) {}
			random_access_iterator(pointer ptr) : _current(ptr) {}
			template <class Ts>
			random_access_iterator (const ft::random_access_iterator<Ts>& it) : _current(it.base()) {}
			~random_access_iterator(void) {}
			template<class Ts>
			random_access_iterator &operator=(ft::random_access_iterator<Ts> const &rhs)
			{
				this->_current = rhs.base();
				return (*this);
			}
			pointer base() const
			{
				return (_current);
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

			reference operator[](difference_type n)
			{
				return (this->_current[n]);
			}
			random_access_iterator operator+=(random_access_iterator const &rhs)
			{
				this->_current = this->_current + rhs._current;
				return (this->_current);
			}
			random_access_iterator operator-=(random_access_iterator const &rhs)
			{
				this->_current = this->_current - rhs._current;
				return (this->_current);
			}
			random_access_iterator operator+=(difference_type n)
			{
				return (this->_current = this->_current + n);
			}
			random_access_iterator operator-=(difference_type n)
			{
				return (this->_current = this->_current - n);
			}
			random_access_iterator operator+(difference_type n) const
			{
				return (this->_current + n);
			}
			random_access_iterator operator-(difference_type n) const
			{
				return (this->_current - n);
			}
			difference_type operator+(random_access_iterator n) const
			{
				return (this->_current + n._current);
			}
			difference_type operator-(random_access_iterator n) const
			{
				return (this->_current - n._current);
			}
			reference operator*()
			{
				return (*(this->_current));
			}
			pointer operator->()
			{
				return (&(operator*()));
			}
		protected :
			pointer _current;
	};
	template <class T1, class T2>
	bool operator==(ft::random_access_iterator<T1> const &lhs,
					ft::random_access_iterator<T2> const &rhs)
	{
		return (lhs.base() == rhs.base());
	}
	template <class T1, class T2>
	bool operator!=(ft::random_access_iterator<T1> const &lhs,
					ft::random_access_iterator<T2> const &rhs)
	{
		return (lhs.base() != rhs.base());
	}
	template <class T1, class T2>
	bool operator<=(ft::random_access_iterator<T1> const &lhs,
					ft::random_access_iterator<T2> const &rhs)
	{
		return (lhs.base() <= rhs.base());
	}
	template <class T1, class T2>
	bool operator>=(ft::random_access_iterator<T1> const &lhs,
					ft::random_access_iterator<T2> const &rhs)
	{
		return (lhs.base() >= rhs.base());
	}
	template <class T1, class T2>
	bool operator>(ft::random_access_iterator<T1> const &lhs,
					ft::random_access_iterator<T2> const &rhs)
	{
		return (lhs.base() > rhs.base());
	}
	template <class T1, class T2>
	bool operator<(ft::random_access_iterator<T1> const &lhs,
					ft::random_access_iterator<T2> const &rhs)
	{
		return (lhs.base() < rhs.base());
	}

	template <class Iterator>
	ft::random_access_iterator<Iterator> operator+(
	typename ft::random_access_iterator<Iterator>::difference_type n,
	const ft::random_access_iterator<Iterator>& it)
	{
		return (it + n);
	}
	template <class Iterator1, class Iterator2>
	typename ft::random_access_iterator<Iterator1>::difference_type operator-(
	const ft::random_access_iterator<Iterator1>& lhs,
	const ft::random_access_iterator<Iterator2>& rhs)
	{
		return (lhs.base() - rhs.base());
	}

	template < class Iterator>
	class reverse_iterator
	{
		private :
			typedef iterator_traits<Iterator> iter;
		public :
			typedef Iterator							iterator_type;
			typedef typename iter::value_type				value_type;
			typedef typename iter::difference_type		difference_type;
			typedef typename iter::pointer				pointer;
			typedef typename iter::reference				reference;
			typedef typename iter::iterator_category		iterator_category;
		protected :
			iterator_type _it;
		public :
			reverse_iterator(void) : _it(NULL) {}
			explicit reverse_iterator(iterator_type ptr) : _it(ptr) {}
			template <class Iter>
			reverse_iterator (const reverse_iterator<Iter>& rev_it) : _it(rev_it.base()) {}
			~reverse_iterator(void) {}
			
			iterator_type base() const
			{
				return (_it);
			}
			reverse_iterator &operator++(void)
			{
				this->_it--;
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
				this->_it++;
				return (*this);
			}
			reverse_iterator operator--(int)
			{
				reverse_iterator tmp(*this);

				operator--();
				return (tmp);
			}
			reference operator[](difference_type n)
			{
				return (base()[-n-1]);
			}
			reverse_iterator &operator+=(difference_type n)
			{
				this->_it -= n;
				return (*this);
			}
			reverse_iterator &operator-=(difference_type n)
			{
				this->_it += n;
				return (*this);
			}
			reverse_iterator operator+(difference_type n) const
			{
				return reverse_iterator(this->_it - n);
			}
			reverse_iterator operator-(difference_type n) const
			{
				return reverse_iterator(this->_it + n);
			}
			reference operator*() const
			{
				iterator_type tmp = _it;

				return (*(--tmp));
			}
			pointer operator->() const
			{
				return (&(operator*()));
			}
	};
	template <class T1, class T2>
	bool operator==(ft::reverse_iterator<T1> const &lhs,
					ft::reverse_iterator<T2> const &rhs)
	{
		return (lhs.base() == rhs.base());
	}
	template <class T1, class T2>
	bool operator!=(ft::reverse_iterator<T1> const &lhs,
					ft::reverse_iterator<T2> const &rhs)
	{
		return (lhs.base() != rhs.base());
	}
	template <class T1, class T2>
	bool operator<=(ft::reverse_iterator<T1> const &lhs,
					ft::reverse_iterator<T2> const &rhs)
	{
		return (lhs.base() >= rhs.base());
	}
	template <class T1, class T2>
	bool operator>=(ft::reverse_iterator<T1> const &lhs,
					ft::reverse_iterator<T2> const &rhs)
	{
		return (lhs.base() <= rhs.base());
	}
	template <class T1, class T2>
	bool operator>(ft::reverse_iterator<T1> const &lhs,
					ft::reverse_iterator<T2> const &rhs)
	{
		return (lhs.base() < rhs.base());
	}
	template <class T1, class T2>
	bool operator<(ft::reverse_iterator<T1> const &lhs,
					ft::reverse_iterator<T2> const &rhs)
	{
		return (lhs.base() > rhs.base());
	}
	template <class Iterator>
	reverse_iterator<Iterator> operator+(
	typename reverse_iterator<Iterator>::difference_type n,
	const reverse_iterator<Iterator>& rev_it)
	{
		return (rev_it + n);
	}
	template <class Iterator1, class Iterator2>
	typename reverse_iterator<Iterator1>::difference_type operator-(
	const reverse_iterator<Iterator1>& lhs,
	const reverse_iterator<Iterator2>& rhs)
	{
		return (rhs.base() - lhs.base());
	}
}

#endif