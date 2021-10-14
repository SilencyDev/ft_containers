/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmacquet <kmacquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/30 15:51:46 by kmacquet          #+#    #+#             */
/*   Updated: 2021/10/14 18:22:00 by kmacquet         ###   ########.fr       */
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
			node*			_last;
			allocator_type	_alloc;
			key_compare		_key_compare;
		private :
			node *create_node(value_type element, node* parent = NULL)
			{
				node *node;
				node = _alloc.allocate(1);
				_alloc.construct(node, element);
				node->parent = parent;
				return (node);
			}
			void	btree_display(node *root, int space)
			{
				int	i = 5;

				if (root == NULL)
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
				if (node->right)
				{
					node = node->right;
					while (node->left)
						node = node->left;
					if (node->right)
						btree_successor(node->right);
					return node;
				}
				else if (node->left)
				{
					node = node->left;
					while (node->right)
						node = node->right;
					if (node->left)
						btree_successor(node->left);
					return node;
				}
				return node;
			}
		public :
			tree(void) : root(NULL), _last(NULL), _alloc(allocator_type()), _key_compare(key_compare()) {}
			tree(key_compare key) : root(NULL), _last(NULL), _alloc(allocator_type()), _key_compare(key) {}
			node_ptr find(node_ptr nodes, value_type element) const
			{
				node_ptr ret = NULL;
				if (!nodes)
					return (NULL);
				ret = find(nodes->left, element);
				if (!ret && !_key_compare(nodes->content.first, element.first)
					&& !_key_compare(element.first, nodes->content.first))
					return (nodes);
				if (!ret)
					ret = find(nodes->right, element);
				return (ret);
			}
			bool erase(iterator position)
			{
				node_ptr node = position.base_node();
				if (node == NULL)
					return false;
				if (!node->left && !node->right)
				{
					if (node->parent)
					{
						if (node->parent->left == node)
							node->parent->left = NULL;
						else
							node->parent->right = NULL;
					}
					// if (node == root)
					// 	root = NULL;
					// _alloc.deallocate(node, 1);
				}
				// else
				// {
				// 	node_ptr tmp = btree_successor(node);
				// 	swap(node, tmp);
				// 	if (tmp->parent)
				// 	{
				// 		if (tmp->parent->left == tmp)
				// 			tmp->parent->left = NULL;
				// 		else
				// 			tmp->parent->right = NULL;
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
				if (!node)
					return ;
				clear(node->left);
				clear(node->right);
				_alloc.destroy(node);
				root = NULL;
			}
			node_ptr setlast() const
			{
				node_ptr tmp = root;
				if (tmp != NULL)
					while (tmp->right)
						tmp = tmp->right;
				return (tmp);
			}
			node_ptr getlast() const
			{
				return (_last);
			}
			iterator begin()
			{
				node_ptr tmp = root;
				if (root)
					while (tmp->left != NULL)
						tmp = tmp->left;
				return iterator(tmp, getlast());
			}
			const_iterator begin() const
			{
				const_node_ptr tmp = reinterpret_cast<const_node_ptr>(root);
				if (root)
					while (tmp->left != NULL)
						tmp = tmp->left;
				return const_iterator(tmp, reinterpret_cast<const_node_ptr>(getlast()));
			}
			iterator end()
			{
				return iterator(NULL, setlast());
			}
			const_iterator end() const
			{
				return const_iterator(NULL, reinterpret_cast<const_node_ptr>(setlast()));
			}
			node_ptr insert(value_type element)
			{
				node_ptr tmp = root;
				// btree_display(root, 10);
				if (!root)
					return (root = create_node(element));
				while (tmp)
				{
					if (_key_compare(element.first, tmp->content.first))
					{
						if (tmp->left)
							tmp = tmp->left;
						else
							return (tmp->left = create_node(element, tmp));
					}
					else if (_key_compare(tmp->content.first, element.first))
					{
						if (tmp->right)
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