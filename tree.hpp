/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmacquet <kmacquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/30 15:51:46 by kmacquet          #+#    #+#             */
/*   Updated: 2021/10/19 14:35:03 by kmacquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TREE_HPP
# define TREE_HPP
# include <memory>
# include "pair.hpp"
# include "iterator.hpp"

namespace ft {
	template < class T,
				class Compare,
				class Alloc = std::allocator<T>
	>
	class tree {
		public :
			typedef	T													value_type;
			typedef typename value_type::first_type						key;
			typedef typename value_type::second_type					value;
			typedef node<const T>										const_node;
			typedef node<T>												node;
			typedef node*												node_ptr;
			typedef const_node*											const_node_ptr;
			typedef Compare												key_compare;
			typedef typename Alloc::template rebind<node>::other		allocator_type;
			typedef typename allocator_type::reference					reference;
			typedef typename allocator_type::const_reference			const_reference;
			typedef typename allocator_type::pointer					pointer;
			typedef typename allocator_type::const_pointer				const_pointer;
			typedef typename ft::bidirectional_iterator<T>				iterator;
			typedef typename ft::const_bidirectional_iterator<const T>	const_iterator;
			typedef typename ft::reverse_iterator<iterator>				reverse_iterator;
			typedef typename ft::reverse_iterator<const_iterator>		const_reverse_iterator;
			typedef ptrdiff_t											difference_type;
			typedef size_t												size_type;
		public :
			node*			root;
			node*			NIL;
			allocator_type	_alloc;
			key_compare		_key_compare;
		private :
			node *create_node(value_type element, node* parent = NULL)
			{
				node *node;
				node = _alloc.allocate(1);
				_alloc.construct(node, element);
				if (parent == NULL)
					node->parent = NIL;
				else
					node->parent = parent;
				node->left = NIL;
				node->right = NIL;
				node->NIL = NIL;
				return (node);
			}
			void	btree_display(node *root, int space)
			{
				int	i = 5;

				if (root == NIL)
					return ;
				space += 5;
				btree_display(root->right, space);
				while (i++ < space)
					std::cerr << " ";
				std::cerr << root->content.first << " - " <<  root->content.second << std::endl;
				btree_display(root->left, space);
			}
			node_ptr btree_successor(node_ptr node)
			{
				if (node->right != NIL)
				{
					node = node->right;
					while (node->left != NIL)
						node = node->left;
					if (node->right != NIL)
						btree_successor(node->right);
					return node;
				}
				else if (node->left != NIL)
				{
					node = node->left;
					while (node->right != NIL)
						node = node->right;
					if (node->left != NIL)
						btree_successor(node->left);
					return node;
				}
				return node;
			}
		public :
			tree(void) : _alloc(allocator_type()), _key_compare(key_compare()) {
				NIL = _alloc.allocate(1);
				_alloc.construct(NIL, value_type());
				NIL->parent = NULL;
				NIL->NIL = NULL;
				NIL->left = NULL;
				NIL->right = NULL;
				NIL->color = BLACK;

				root = NIL;
			}
			tree(key_compare key) : _alloc(allocator_type()), _key_compare(key) {
				NIL = _alloc.allocate(1);
				_alloc.construct(NIL, value_type());
				NIL->parent = NULL;
				NIL->NIL = NULL;
				NIL->left = NULL;
				NIL->right = NULL;
				NIL->color = BLACK;
				root = NIL;
			}
			node_ptr find(node_ptr nodes, value_type element) const
			{
				node_ptr ret;
 				if (nodes == NIL)
					return (NIL);
				ret = find(nodes->left, element);
				if (ret == NIL && !_key_compare(nodes->content.first, element.first)
					&& !_key_compare(element.first, nodes->content.first))
					return (nodes);
				if (ret == NIL)
					ret = find(nodes->right, element);
				return (ret);
			}
			void swap(tree &x)
			{
				if (this == &x)
					return ;
				allocator_type	tmp_alloc = _alloc;
				key_compare		tmp_key = _key_compare;
				node*			tmp_root = root;
				node*			tmp_nil = NIL;

				NIL = x.NIL;
				_alloc = x._alloc;
				_key_compare  = x._key_compare;
				root = x.root;

				x.NIL = tmp_nil;
				x._alloc = tmp_alloc;
				x._key_compare = tmp_key;
				x.root = tmp_root;
			}
			size_type	max_size() const
			{
				if (sizeof(value_type) == 1)
					return (_alloc.max_size() / 2);
				return (_alloc.max_size());
			}
			bool erase(iterator position)
			{
				node_ptr node = position.base_node();
				if (node == NIL)
					return false;
				if (node->left == NIL && node->right == NIL)
				{
					if (node->parent == NIL)
					{
						if (node->parent->left == node)
							node->parent->left = NIL;
						else
							node->parent->right = NIL;
					}
					// if (node == root)
					// 	root = NIL;
					// _alloc.deallocate(node, 1);
				}
				// else
				// {
				// 	node_ptr tmp = btree_successor(node);
				// 	swap(node, tmp);
				// 	if (tmp->parent)
				// 	{
				// 		if (tmp->parent->left == tmp)
				// 			tmp->parent->left = NIL;
				// 		else
				// 			tmp->parent->right = NIL;
				// 	}
				// 	_alloc.deallocate(tmp, 1);
				// }
				return true;
			}
			// void swap(node_ptr node1, node_ptr node2)
			// {
			// 	key tmpk = node1->content.first;
			// 	value tmpv = node1->content.second;
			// 	node1->content.first = node2->content.first;
			// 	node1->content.second = node2->content.second;
			// 	node2->content.first = tmpk;
			// 	node2->content.second = tmpv;
			// }
			// void swap(const_node_ptr node1, const_node_ptr node2) const
			// {
			// 	reinterpret_cast<node_ptr>(node1);
			// 	reinterpret_cast<node_ptr>(node2);
			// 	key tmpk = node1->content.first;
			// 	value tmpv = node1->content.second;
			// 	node1->content.first = node2->content.first;
			// 	node1->content.second = node2->content.second;
			// 	node2->content.first = tmpk;
			// 	node2->content.second = tmpv;
			// 	reinterpret_cast<const_node_ptr>(node1);
			// 	reinterpret_cast<const_node_ptr>(node2);
			// }
			void clear(node_ptr node)
			{
				if (node == NIL)
					return ;
				clear(node->left);
				clear(node->right);
				_alloc.destroy(node);
				root = NIL;
			}
			node_ptr setlast() const 
			{
				node_ptr tmp = root;
				if (tmp != tmp->NIL)
					while (tmp->right != tmp->NIL)
						tmp = tmp->right;
				return (tmp);
			}
			iterator begin()
			{
				node_ptr tmp = root;
				if (root != NIL)
					while (tmp->left != NIL)
						tmp = tmp->left;
				return iterator(tmp, setlast());
			}
			const_iterator begin() const
			{
				const_node_ptr tmp = reinterpret_cast<const_node_ptr>(root);
				if (tmp == reinterpret_cast<const_node_ptr>(NIL))
					return const_iterator(tmp, reinterpret_cast<const_node_ptr>(setlast()));
				while (tmp->left != reinterpret_cast<const_node_ptr>(tmp->NIL))
					tmp = tmp->left;
				return const_iterator(tmp, reinterpret_cast<const_node_ptr>(setlast()));
			}
			iterator end()
			{
				return iterator(NIL, setlast());
			}
			const_iterator end() const
			{
				return const_iterator(reinterpret_cast<const_node_ptr>(NIL), reinterpret_cast<const_node_ptr>(setlast()));
			}
			node_ptr insert(value_type element)
			{
				node_ptr tmp = root;
				// btree_display(root, 10);
				if (root == NIL)
					return (root = create_node(element));
				while (tmp != NIL)
				{
					if (_key_compare(element.first, tmp->content.first))
					{
						if (tmp->left != NIL)
							tmp = tmp->left;
						else
							return (tmp->left = create_node(element, tmp));
					}
					else if (_key_compare(tmp->content.first, element.first))
					{
						if (tmp->right != NIL)
							tmp = tmp->right;
						else
							return (tmp->right = create_node(element, tmp));
					}
					else
						break;
				}
				return (tmp);
			}
	};
}

#endif