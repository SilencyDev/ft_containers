/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmacquet <kmacquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/29 15:14:06 by kmacquet          #+#    #+#             */
/*   Updated: 2021/09/29 17:07:17 by kmacquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_HPP
# define MAP_HPP

namespace ft {
	template <	class Key,
				class T,
				class Compare = std::less<Key>,
				class Alloc = allocator<pair<const Key>, T> >
	>
	class map {
		public :
			typedef typename Key										key_type;
			typedef typename T											mapped_type;
			typedef	typename pair<const key_type, mapped_type>			value_type;
			typedef typename Compare									key_compare;
			typedef typename map::value_compare							value_compare;
			typedef typename Alloc										allocator_type;
			typedef typename allocator_type::reference					reference;
			typedef typename allocator_type::const_reference			const_reference;
			typedef typename allocator_type::pointer					pointer;
			typedef typename allocator_type::const_pointer				const_pointer;
			typedef typename ft::bidirectional_iterator<pointer>		iterator;
			typedef typename ft::bidirectional_iterator<const_pointer>	const_iterator;
			typedef typename ft::reverse_iterator<iterator>				reverse_iterator;
			typedef typename ft::reverse_iterator<const_iterator>		const_reverse_iterator;
			typedef typename iterator_traits<iterator>::difference_type	difference_type;
			typedef size_t												size_type;
			

		value_compare value_comp() const
		{
			template <class Key, class T, class Compare, class Alloc>
			class map<Key,T,Compare,Alloc>::value_compare
			{	// in C++98, it is required to inherit binary_function<value_type,value_type,bool>
				friend class ft::map;
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
			}
		}

	};
}
#endif