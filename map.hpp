/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmacquet <kmacquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/29 15:14:06 by kmacquet          #+#    #+#             */
/*   Updated: 2021/10/19 14:29:38 by kmacquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_HPP
# define MAP_HPP
# include <memory>
# include <map>
# include "vector.hpp"
# include "tree.hpp"
# include "iterator.hpp"
# include "pair.hpp"

namespace ft {
	template <	class Key,
				class T,
				class Compare = std::less<Key>,
				class Alloc = std::allocator<ft::pair<const Key, T> >
	>
	class map {
		public :
			typedef Key													key_type;
			typedef T													mapped_type;
			typedef	pair<const key_type, mapped_type>					value_type;
			typedef Compare												key_compare;
			typedef Alloc												allocator_type;
			typedef typename allocator_type::reference					reference;
			typedef typename allocator_type::const_reference			const_reference;
			typedef typename allocator_type::pointer					pointer;
			typedef typename allocator_type::const_pointer				const_pointer;
		private :
			typedef typename ft::tree<value_type, Compare, allocator_type> tree;
		public :
			typedef typename tree::iterator								iterator;
			typedef typename tree::const_iterator						const_iterator;
			typedef typename tree::reverse_iterator						reverse_iterator;
			typedef typename tree::const_reverse_iterator				const_reverse_iterator;
			typedef ptrdiff_t											difference_type;
			typedef size_t												size_type;

		protected:
			allocator_type						_alloc;
			key_compare							_key_compare;
			tree								_tree;
			size_type							_size;
			
		public :
			explicit map (const key_compare& comp = key_compare(),
			const allocator_type& alloc = allocator_type())
			: _alloc(alloc), _key_compare(comp), _tree(tree()), _size(0) {}
			
			template <class InputIterator>
			map (InputIterator first, InputIterator last,
			const key_compare& comp = key_compare(),
			const allocator_type& alloc = allocator_type())
			{
				_alloc = alloc;
				_key_compare = comp;
				_size = 0;
				_tree = tree();
				while (first != last)
					insert(*first++);
			}
			map (const map& x)
			{
				_alloc = x._alloc;
				if (this != &x)
					*this = x;
			}
			map& operator=(const map& x)
			{
				if (this != &x)
				{
					clear();
					insert(x.begin(), x.end());
					_key_compare = x._key_compare;
					_size = x._size;
				}
				return (*this);
			}
			mapped_type& operator[] (const key_type& k)
			{
				return (*((this->insert(ft::make_pair(k,mapped_type()))).first)).second;
			}
			~map() {}
			iterator find (const key_type& k)
			{
				if (_tree.find(_tree.root, ft::make_pair(k, mapped_type())) != NULL)
					return iterator(_tree.find(_tree.root, ft::make_pair(k, mapped_type())));
				return (end());
			}
			const_iterator find (const key_type& k) const
			{
				if (_tree.find(_tree.root, ft::make_pair(k, mapped_type())))
					return const_iterator(reinterpret_cast<typename tree::const_node_ptr>(_tree.find(_tree.root, ft::make_pair(k, mapped_type()))));
				return (end());
			}
			pair<iterator,bool> insert (const value_type& val)
			{
				bool exist = _tree.find(_tree.root, val) == _tree.NIL ? true : false;
				_tree.insert(val);
				if (exist)
					_size++;
				return(ft::make_pair(iterator(_tree.find(_tree.root, val), _tree.NIL), exist));
			}
			iterator insert (iterator position, const value_type& val)
			{
				(void)position;
				insert(val);
				return iterator(_tree.find(_tree.root, val));
			}
			template <class InputIterator>
			void insert (InputIterator first, InputIterator last)
			{
				while (first != last)
					insert(*first++);
			}
			void erase (iterator position)
			{
				if (_tree.erase(position))
					_size--;
			}
			size_type erase (const key_type& k)
			{
				size_type exist;
				exist = _tree.find(_tree.root, ft::make_pair(k, mapped_type())) != _tree.NIL ? true : false;
				_tree.erase(_tree.find(_tree.root, ft::make_pair(k, mapped_type())));
				return (exist);
			}
			void erase (iterator first, iterator last)
			{
				for (; first != last; first++)
					_tree.erase(first);
			}
			size_type count (const key_type& k) const
			{
				if (_tree.find(_tree.root, ft::make_pair(k, mapped_type())) != _tree.NIL)
					return (1);
				return (0);
			}
			void clear()
			{
				_tree.clear(_tree.root);
				_size = 0;
			}
			iterator begin()
			{
				return iterator(_tree.begin());
			}
			const_iterator begin() const
			{
				return const_iterator(_tree.begin());
			}
			iterator end()
			{
				return iterator(_tree.end());
			}
			const_iterator end() const
			{
				return const_iterator(_tree.end());
			}
			reverse_iterator rbegin()
			{
				return reverse_iterator(end());
			}
			const_reverse_iterator rbegin() const
			{
				return const_reverse_iterator(end());
			}
			reverse_iterator rend()
			{
				return reverse_iterator(begin());
			}
			const_reverse_iterator rend() const
			{
				return const_reverse_iterator(begin());
			}
			class value_compare : public std::binary_function<value_type, value_type, bool>
			{
				friend class map;
				protected:
					Compare comp;
					value_compare (Compare c) : comp(c) {}  // constructed with map's comparison object
				public:
					typedef bool result_type;
					typedef value_type first_argument_type;
					typedef value_type second_argument_type;
				bool operator() (const value_type& x, const value_type& y) const
				{
					return comp(x.first, y.first);
				}
			};
			void swap (map& x)
			{
				if (this == &x)
					return ;
				_tree.swap(x._tree);
				allocator_type	tmp_alloc = _alloc;
				key_compare		tmp_key = _key_compare;
				size_type		tmp_size = _size;

				_alloc = x._alloc;
				_key_compare  = x._key_compare;
				_size = x._size;

				x._alloc = tmp_alloc;
				x._key_compare = tmp_key;
				x._size = tmp_size;
			}
			value_compare value_comp() const
			{
				return (value_compare(_key_compare));
			}
			key_compare key_comp() const
			{
				return _key_compare;
			}
			pair<const_iterator,const_iterator> equal_range (const key_type& k) const
			{
				return ft::make_pair(lower_bound(k), upper_bound(k));
			}
			pair<iterator,iterator> equal_range (const key_type& k)
			{
				return ft::make_pair(lower_bound(k), upper_bound(k));
			}
			iterator upper_bound (const key_type& k)
			{
				iterator it = begin();
				iterator ite = end();

				for (; it != ite; it++)
					if (_key_compare(k, it->first) == true)
						break;
				return (it);
			}
			const_iterator upper_bound (const key_type& k) const
			{
				const_iterator it = begin();
				const_iterator ite = end();

				for (; it != ite; it++)
					if (_key_compare(k, it->first) == true)
						break;
				return (it);
			}
			iterator lower_bound (const key_type& k)
			{
				iterator it = begin();
				iterator ite = end();

				for (; it != ite; it++)
					if (_key_compare(it->first, k) == false)
						break;
				return (it);
			}
			const_iterator lower_bound (const key_type& k) const
			{
				const_iterator it = begin();
				const_iterator ite = end();

				for (; it != ite; it++)
					if (_key_compare(it->first, k) == false)
						break;
				return (it);
			}
			allocator_type	get_allocator() const
			{
				return (_alloc);
			}
			size_type	max_size() const
			{
				return (_tree.max_size());
			}
			size_type	size() const
			{
				return _size;
			}
			bool empty() const
			{
				if (size() > 0)
					return (false);
				return (true);
			}
	};
	template <class Key, class T, class Compare, class Alloc>
	void swap(ft::map<Key,T,Compare,Alloc>& x, ft::map<Key,T,Compare,Alloc>& y)
	{
		x.swap(y);
	}
	template <class Key, class T, class Compare, class Alloc>
	bool operator== ( const map<Key,T,Compare,Alloc>& lhs,
					const map<Key,T,Compare,Alloc>& rhs )
	{
		if (lhs.size() != rhs.size())
			return (false);
		return (ft::equal(lhs.begin(), lhs.end(), rhs.begin()));
	}

	template <class Key, class T, class Compare, class Alloc>
	bool operator!= ( const map<Key,T,Compare,Alloc>& lhs,
					const map<Key,T,Compare,Alloc>& rhs )
	{
		return (!(lhs == rhs));
	}

	template <class Key, class T, class Compare, class Alloc>
	bool operator<  ( const map<Key,T,Compare,Alloc>& lhs,
					const map<Key,T,Compare,Alloc>& rhs )
	{
		return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
	}

	template <class Key, class T, class Compare, class Alloc>
	bool operator<= ( const map<Key,T,Compare,Alloc>& lhs,
					const map<Key,T,Compare,Alloc>& rhs )
	{
		return (!(rhs < lhs));
	}

	template <class Key, class T, class Compare, class Alloc>
	bool operator>  ( const map<Key,T,Compare,Alloc>& lhs,
					const map<Key,T,Compare,Alloc>& rhs )
	{
		return (ft::lexicographical_compare(rhs.begin(), rhs.end(), lhs.begin(), lhs.end()));
	}

	template <class Key, class T, class Compare, class Alloc>
	bool operator>= ( const map<Key,T,Compare,Alloc>& lhs,
					const map<Key,T,Compare,Alloc>& rhs )
	{
		return (!(lhs < rhs));
	}
}
#endif