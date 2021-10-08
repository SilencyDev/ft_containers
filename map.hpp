/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmacquet <kmacquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/29 15:14:06 by kmacquet          #+#    #+#             */
/*   Updated: 2021/10/08 18:35:00 by kmacquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_HPP
# define MAP_HPP
# include <memory>
# include <map>
# include "tree.hpp"
# include "iterator.hpp"

namespace ft {
	template <	class Key,
				class T,
				class Compare = std::less<Key>,
				class Alloc = std::allocator<ft::pair<const Key, T> >
	>
	class map {
		public :
			typedef Key																key_type;
			typedef T																mapped_type;
			typedef	pair<const key_type, mapped_type>								value_type;
			typedef Compare															key_compare;
			typedef Alloc															allocator_type;
			typedef typename allocator_type::reference								reference;
			typedef typename allocator_type::const_reference						const_reference;
			typedef typename allocator_type::pointer								pointer;
			typedef typename allocator_type::const_pointer							const_pointer;
			typedef typename ft::tree<value_type, Compare>::iterator				iterator;
			typedef typename ft::tree<value_type, Compare>::const_iterator			const_iterator;
			typedef typename ft::tree<value_type, Compare>::reverse_iterator		reverse_iterator;
			typedef typename ft::tree<value_type, Compare>::const_reverse_iterator	const_reverse_iterator;
			typedef typename iterator_traits<iterator>::difference_type				difference_type;
			typedef size_t															size_type;

		protected:
			allocator_type						_alloc;
			key_compare							_key_compare;
			ft::tree<value_type, Compare>		_tree;
			size_type							_size;
			
		public :
			explicit map (const key_compare& comp = key_compare(),
			const allocator_type& alloc = allocator_type())
			: _alloc(alloc), _key_compare(comp), _tree(), _size(0) {}
			
			// template <class InputIterator>
			// map (InputIterator first, InputIterator last,
			// const key_compare& comp = key_compare(),
			// const allocator_type& alloc = allocator_type())
			// {
			// 	;
			// }
			map (const map& x)
			{
				_alloc = x._alloc;
				if (*this != x)
					*this = x;
				return (*this);
			}
			map& operator=(const map& x)
			{
				if (*this != x)
				{
					_tree = x._tree;
					_key_compare = x._key_compare;
					_size = x._size;
				}
				return (*this);
			}
			~map();
			iterator begin()
			{
				return (_tree.begin());
			}
			const_iterator begin() const
			{
				return (_tree.begin());
			}
			iterator end()
			{
				return (_tree.end());
			}
			const_iterator end() const
			{
				return (_tree.end());
			}
			reverse_iterator rbegin()
			{
				return (_tree.rbegin());
			}
			const_reverse_iterator rbegin() const
			{
				return (_tree.rbegin());
			}
			class value_compare : public std::binary_function<value_type,value_type,bool>
			{
				// friend class ft::map;
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
			value_compare value_comp() const
			{
				return (value_compare(key_compare()));
			}

			allocator_type	get_allocator() const
			{
				return (_alloc);
			}
			size_type	max_size() const
			{
				if (sizeof(value_type) == 1)
					return (_alloc.max_size() / 2);
				return (_alloc.max_size());
			}
			size_type	size() const;
			bool empty() const
			{
				if (size() > 0)
					return (false);
				return (true);
			}
	};
}
#endif