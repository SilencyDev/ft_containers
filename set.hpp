/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmacquet <kmacquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/20 16:51:44 by kmacquet          #+#    #+#             */
/*   Updated: 2021/10/20 19:26:35 by kmacquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SET_HPP
# define SET_HPP
# include <memory>
# include <map>
# include "vector.hpp"
# include "tree_set.hpp"
# include "iterator.hpp"
# include "pair.hpp"

namespace ft {
	template <	class T,
				class Compare = std::less<T>,
				class Alloc = std::allocator<T>
	>
	class set {
		public :
			typedef	T													key_type;
			typedef	T													value_type;
			typedef Compare												key_compare;
			typedef Alloc												allocator_type;
			typedef typename allocator_type::reference					reference;
			typedef typename allocator_type::const_reference			const_reference;
			typedef typename allocator_type::pointer					pointer;
			typedef typename allocator_type::const_pointer				const_pointer;
		private :
			typedef typename ft::treeset<value_type, Compare, allocator_type>	tree;
		public :
			typedef typename tree::iterator								iterator;
			typedef typename tree::const_iterator						const_iterator;
			// typedef const_iterator										iterator;
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
			explicit set (const key_compare& comp = key_compare(),
			const allocator_type& alloc = allocator_type())
			: _alloc(alloc), _key_compare(comp), _tree(), _size(0) {}
			
			template <class InputIterator>
			set (InputIterator first, InputIterator last,
			const key_compare& comp = key_compare(),
			const allocator_type& alloc = allocator_type())
			{
				_alloc = alloc;
				_key_compare = comp;
				while (first != last)
					insert(*first++);
			}
			set (const set& x)
			{
				_alloc = x._alloc;
				if (this != &x)
					*this = x;
			}
			set& operator=(const set& x)
			{
				if (this != &x)
				{
					clear();
					insert(x.begin(), x.end());
					_key_compare = x._key_compare;
				}
				return (*this);
			}
			~set()
			{
				_tree._alloc.destroy(_tree.NIL);
				_tree._alloc.deallocate(_tree.NIL, 1);
			}
			iterator find (const value_type& k)
			{
				if (_tree.find(_tree.root, k) != NULL)
					return iterator(_tree.find(_tree.root, k));
				return (end());
			}
			const_iterator find (const value_type& k) const
			{
				if (_tree.find(_tree.root, k))
					return const_iterator(reinterpret_cast<typename tree::const_node_ptr>(_tree.find(_tree.root, k)));
				return (end());
			}
			pair<iterator,bool> insert (const value_type& val)
			{
				bool exist = _tree.find(_tree.root, val) == _tree.NIL ? true : false;
				_tree.insert(val);
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
				size_type exist;
				exist = _tree.find(_tree.root, *position) != _tree.NIL ? true : false;
				if (exist)
					_tree.erase(position);
			}
			size_type erase (const value_type& k)
			{
				size_type exist;
				node< const value_type>* it = _tree.find(_tree.root, k);
				exist = it != _tree.NIL ? true : false;
				if (exist)
					_tree.erase_ptr(it);
				return (exist);
			}
			void erase (iterator first, iterator last)
			{
				size_type exist;
				while (first != last)
				{
					exist = _tree.find(_tree.root, *(first.base())) != _tree.NIL ? true : false;
					if (exist)
						_tree.erase(first++);
				}
			}
			size_type count (const value_type& k) const
			{
				if (_tree.find(_tree.root, k) != _tree.NIL)
					return (1);
				return (0);
			}
			void clear()
			{
				_tree.clear(_tree.root);
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
				friend class set;
				protected:
					Compare comp;
					value_compare (Compare c) : comp(c) {} 
				public:
					typedef bool result_type;
					typedef value_type first_argument_type;
					typedef value_type second_argument_type;
				bool operator() (const value_type& x, const value_type& y) const
				{
					return comp(x, y);
				}
			};
			void swap (set& x)
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
			pair<const_iterator,const_iterator> equal_range (const value_type& k) const
			{
				return ft::make_pair(lower_bound(k), upper_bound(k));
			}
			pair<iterator,iterator> equal_range (const value_type& k)
			{
				return ft::make_pair(lower_bound(k), upper_bound(k));
			}
			iterator upper_bound (const value_type& k)
			{
				iterator it = begin();
				iterator ite = end();

				for (; it != ite; it++)
					if (_key_compare(k, *it) == true)
						break;
				return (it);
			}
			const_iterator upper_bound (const value_type& k) const
			{
				const_iterator it = begin();
				const_iterator ite = end();

				for (; it != ite; it++)
					if (_key_compare(k, *it) == true)
						break;
				return (it);
			}
			iterator lower_bound (const value_type& k)
			{
				iterator it = begin();
				iterator ite = end();

				for (; it != ite; it++)
					if (_key_compare(*it, k) == false)
						break;
				return (it);
			}
			const_iterator lower_bound (const value_type& k) const
			{
				const_iterator it = begin();
				const_iterator ite = end();

				for (; it != ite; it++)
					if (_key_compare(*it, k) == false)
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
				return _tree._size;
			}
			bool empty() const
			{
				if (size() > 0)
					return (false);
				return (true);
			}

			void	print_tree(void) {
				_tree.btree_display(_tree.root, 0);
			}
	};
	template <class T, class Compare, class Alloc>
	void swap(ft::set<T,Compare,Alloc>& x, ft::set<T,Compare,Alloc>& y)
	{
		x.swap(y);
	}
	template <class T, class Compare, class Alloc>
	bool operator== ( const set<T,Compare,Alloc>& lhs,
					const set<T,Compare,Alloc>& rhs )
	{
		if (lhs.size() != rhs.size())
			return (false);
		return (ft::equal(lhs.begin(), lhs.end(), rhs.begin()));
	}

	template <class T, class Compare, class Alloc>
	bool operator!= ( const set<T,Compare,Alloc>& lhs,
					const set<T,Compare,Alloc>& rhs )
	{
		return (!(lhs == rhs));
	}

	template <class T, class Compare, class Alloc>
	bool operator<  ( const set<T,Compare,Alloc>& lhs,
					const set<T,Compare,Alloc>& rhs )
	{
		return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
	}

	template <class T, class Compare, class Alloc>
	bool operator<= ( const set<T,Compare,Alloc>& lhs,
					const set<T,Compare,Alloc>& rhs )
	{
		return (!(rhs < lhs));
	}

	template <class T, class Compare, class Alloc>
	bool operator>  ( const set<T,Compare,Alloc>& lhs,
					const set<T,Compare,Alloc>& rhs )
	{
		return (ft::lexicographical_compare(rhs.begin(), rhs.end(), lhs.begin(), lhs.end()));
	}

	template <class T, class Compare, class Alloc>
	bool operator>= ( const set<T,Compare,Alloc>& lhs,
					const set<T,Compare,Alloc>& rhs )
	{
		return (!(lhs < rhs));
	}

}
#endif