/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmacquet <kmacquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/30 15:51:46 by kmacquet          #+#    #+#             */
/*   Updated: 2021/10/08 18:47:35 by kmacquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TREE_HPP
# define TREE_HPP
# include <memory>
# include "pair.hpp"
# include "iterator.hpp"

namespace ft {
	template < class T >
	struct node
	{
		node*	parent;
		node*	left;
		node*	right;
		T		content;
	};
	template < class T,
				class Compare,
				class Alloc = std::allocator<T>
	>
	class tree {
		public :
			typedef	T													value_type;
			typedef node<T>												node;
			typedef Compare												key_compare;
			typedef typename Alloc::template rebind<node>::other		allocator_type;
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
		protected :
			node*			root;
			node*			_last;
			allocator_type	_alloc;
			key_compare		_key_compare;
		private :
			node *create_node(value_type element)
			{
				node *node;
				node = _alloc.allocate(1);
				node->left = NULL;
				node->right = NULL;
				node->parent = NULL;
				node->content = element;
				return (node);
			}
			node *find(node *root, value_type element)
			{
				node *ret = NULL;
				if (!root)
					return (NULL);
				ret = find(root, element);
				if (!ret && !_key_compare(element.first, root->left->content.first)
					&& !_key_compare(element.first, root->right->content.first))
					return (root);
				if (!ret)
					ret = find(root->right, element);
				return (root);
			}
		public :
			node* getlast() const
			{
				return (_last);
			}
			iterator begin()
			{
				node* tmp = root;
				if (root)
					while (tmp->left != NULL)
						tmp = tmp->left;
				return (tmp);
			}
			const_iterator begin() const
			{
				node* tmp = root;
				if (root)
					while (tmp->left != NULL)
						tmp = tmp->left;
				return (tmp);
			}
			iterator end()
			{
				return (iterator(NULL));
			}
			const_iterator end() const
			{
				return (iterator(NULL));
			}
			node *insert(node **root, value_type element)
			{
				if (!(*root))
					(*root) = create_node(element);
				else if (_key_compare(element.first, (*root)->content.first))
				{
					if ((*root)->left)
						insert(&(*root)->left, element);
					else
						return ((*root)->left = create_node(element));
				}
				else if (_key_compare((*root)->content.first), element.first)
				{
					if ((*root)->right)
						insert(&(*root)->right, element);
					else
						return ((*root)->right = create_node(element, *root));
				}
				return (NULL);
			}
	};
}

#endif