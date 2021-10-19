/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmacquet <kmacquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 14:46:02 by kmacquet          #+#    #+#             */
/*   Updated: 2021/10/19 11:01:49 by kmacquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NODE_HPP
# define NODE_HPP

enum  e_color
{
	BLACK,
	RED
};

template < class T >
class node
{
	public :
		typedef T		pair;
		node(T pair) : parent(NULL), left(NULL), right(NULL), content(pair) {
			color = RED;
		}
		node*	parent;
		node*	left;
		node*	right;
		T		content;
		e_color	color;
		node*	NIL;
};

#endif