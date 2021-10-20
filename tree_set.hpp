/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_set.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmacquet <kmacquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/20 17:01:39 by kmacquet          #+#    #+#             */
/*   Updated: 2021/10/20 17:52:29 by kmacquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TREE_SET_HPP
# define TREE_SET_HPP
# include <memory>
# include "iterator.hpp"

namespace ft {
	template < class T,
				class Compare,
				class Alloc = std::allocator<T>
	>
	class treeset {
		public :
			typedef	T													value_type;
			typedef node<const T>										const_node;
			typedef node<const T>												node;
			typedef node*												node_ptr;
			typedef const_node*											const_node_ptr;
			typedef Compare												key_compare;
			typedef typename Alloc::template rebind<node>::other		allocator_type;
			typedef typename allocator_type::reference					reference;
			typedef typename allocator_type::const_reference			const_reference;
			typedef typename allocator_type::pointer					pointer;
			typedef typename allocator_type::const_pointer				const_pointer;
			typedef typename ft::const_bidirectional_iterator<const T>	const_iterator;
			typedef const_iterator										iterator;
			typedef typename ft::reverse_iterator<iterator>				reverse_iterator;
			typedef typename ft::reverse_iterator<const_iterator>		const_reverse_iterator;
			typedef ptrdiff_t											difference_type;
			typedef size_t												size_type;
		public :
			size_type		_size;
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
				_size++;
				return (node);
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
			void	left_rotate(node_ptr x)
			{
				node_ptr y = x->right;
				x->right = y->left;
				if (y->left != NIL)
					y->left->parent = x;
				y->parent = x->parent;
				if (x->parent == NIL)
					root = y;
				else if (x == x->parent->left)
					x->parent->left = y;
				else
					x->parent->right = y;
				y->left = x;
				x->parent = y;
			}
			void	right_rotate(node_ptr x)
			{
				node_ptr y = x->left;
				x->left = y->right;
				if (y->right != NIL)
					y->right->parent = x;
				y->parent = x->parent;
				if (x->parent == NIL)
					root = y;
				else if (x == x->parent->right)
					x->parent->right = y;
				else
					x->parent->left = y;
				y->right = x;
				x->parent = y;
			}
			void	insertion_fix(node_ptr z)
			{
				node_ptr y;
				while (z->parent->color == RED)
				{
					if (z->parent == z->parent->parent->left)
					{
						y = z->parent->parent->right;
						if (y->color == RED)
						{
							z->parent->color = BLACK;
							y->color = BLACK;
							z->parent->parent->color = RED;
							z = z->parent->parent;
						}
						else
						{
							if (z == z->parent->right)
							{
								z = z->parent;
								left_rotate(z);
							}
							z->parent->color = BLACK;
							z->parent->parent->color = RED;
							right_rotate(z->parent->parent);
						}
					}
					else
					{
						y = z->parent->parent->left;
						if (y->color == RED)
						{
							z->parent->color = BLACK;
							y->color = BLACK;
							z->parent->parent->color = RED;
							z = z->parent->parent;
						}
						else
						{
							if (z == z->parent->left)
							{
								z = z->parent;
								right_rotate(z);
							}
							z->parent->color = BLACK;
							z->parent->parent->color = RED;
							left_rotate(z->parent->parent);
						}
					}
				}
				root->color = BLACK;
			}
			void	transplant(node_ptr u, node_ptr v)
			{
				if (u->parent == NIL)
					root = v;
				else if (u == u->parent->left)
					u->parent->left = v;
				else
					u->parent->right = v;
				v->parent = u->parent;
			}
			node_ptr	minimum(node_ptr x)
			{
				while (x->left != NIL)
					x = x->left;
				return x;
			}
			void	delete_fix(node_ptr x)
			{
				while (x != root && x->color == BLACK)
				{
					if (x == x->parent->left)
					{
						node_ptr w = x->parent->right;
						if (w->color == RED)
						{
							w->color = BLACK;
							x->parent->color = RED;
							left_rotate(x->parent);
							w = x->parent->right;
						}
						if (w->left->color == BLACK && w->right->color == BLACK)
						{
							w->color = RED;
							x = x->parent;
						}
						else
						{
							if (w->right->color == BLACK)
							{
								w->left->color = BLACK;
								w->color = RED;
								right_rotate(w);
								w = x->parent->right;
							}
							w->color = x->parent->color;
							x->parent->color = BLACK;
							w->right->color = BLACK;
							left_rotate(x->parent);
							x = root;
						}
					}
					else
					{
						node_ptr w = x->parent->left;
						if (w->color == RED)
						{
							w->color = BLACK;
							x->parent->color = RED;
							right_rotate(x->parent);
							w = x->parent->left;
						}
						if (w->right->color == BLACK && w->left->color == BLACK)
						{
							w->color = RED;
							x = x->parent;
						}
						else
						{
							if (w->left->color == BLACK)
							{
								w->right->color = BLACK;
								w->color = RED;
								left_rotate(w);
								w = x->parent->left;
							}
							w->color = x->parent->color;
							x->parent->color = BLACK;
							w->left->color = BLACK;
							right_rotate(x->parent);
							x = root;
						}
					}
				}
				x->color = BLACK;
			}
			void	delete_node(node_ptr z)
			{
				node_ptr y = z;
				node_ptr x;
				color o_color = y->color;
				if (z->left == NIL)
				{
					x = z->right;
					transplant(z, z->right);
				}
				else if (z->right == NIL)
				{
					x = z->left;
					transplant(z, z->left);
				}
				else
				{
					y = minimum(z->right);
					o_color = y->color;
					x = y->right;
					if ( y->parent == z)
						x->parent = y;
					else
					{
						transplant(y, y->right);
						y->right = z->right;
						y->right->parent = y;
					}
					transplant(z, y);
					y->left = z->left;
					y->left->parent = y;
					y->color = z->color;
				}
				if (o_color == BLACK)
					delete_fix(x);
			}
		public :
			treeset(void) : _alloc(allocator_type()), _key_compare(key_compare()) {
				NIL = _alloc.allocate(1);
				_alloc.construct(NIL, value_type());
				NIL->parent = NULL;
				NIL->NIL = NULL;
				NIL->left = NULL;
				NIL->right = NULL;
				NIL->color = BLACK;
				_size = 0;
				root = NIL;
			}
			treeset(key_compare key) : _alloc(allocator_type()), _key_compare(key) {
				NIL = _alloc.allocate(1);
				_alloc.construct(NIL, value_type());
				NIL->parent = NULL;
				NIL->NIL = NULL;
				NIL->left = NULL;
				NIL->right = NULL;
				NIL->color = BLACK;
				_size = 0;
				root = NIL;
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
				std::cerr << root->content << " - " <<  root->content << std::endl;
				btree_display(root->left, space);
			}
			node_ptr find(node_ptr nodes, value_type element) const
			{
				while (nodes != NIL)
				{
					if (!_key_compare(nodes->content, element)
				 	&& !_key_compare(element, nodes->content))
					 return (nodes);
					if (_key_compare(element, nodes->content))
						nodes = nodes->left;
					else if (_key_compare(nodes->content, element))
						nodes = nodes->right;
				}
				return NIL;
			}
			void swap(treeset &x)
			{
				if (this == &x)
					return ;
				allocator_type	tmp_alloc = _alloc;
				key_compare		tmp_key = _key_compare;
				node*			tmp_root = root;
				node*			tmp_nil = NIL;
				size_type		tmp_size = _size;

				NIL = x.NIL;
				_alloc = x._alloc;
				_key_compare  = x._key_compare;
				root = x.root;
				_size = x._size;

				x.NIL = tmp_nil;
				x._alloc = tmp_alloc;
				x._key_compare = tmp_key;
				x.root = tmp_root;
				x._size = tmp_size;
			}
			size_type	max_size() const
			{
				return (std::numeric_limits<size_type>::max() / (sizeof(node) - sizeof(node_ptr)));
			}
			void erase(iterator position)
			{
				delete_node(position.base_node());
				_size--;
			}
			void erase_ptr(node_ptr node)
			{
				delete_node(node);
				_size--;
			}
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
				{
					root = create_node(element);
					root->color = BLACK;
					return (root);
				}
				while (tmp != NIL)
				{
					if (_key_compare(element, tmp->content))
					{
						if (tmp->left != NIL)
							tmp = tmp->left;
						else
						{
							tmp->left = create_node(element, tmp);
							insertion_fix(tmp->left);
							return (tmp->left);
						}
					}
					else if (_key_compare(tmp->content, element))
					{
						if (tmp->right != NIL)
							tmp = tmp->right;
						else
						{
							tmp->right = create_node(element, tmp);
							insertion_fix(tmp->right);
							return (tmp->right);
						}
					}
					else
						break;
				}
				return (tmp);
			}
	};
}

#endif