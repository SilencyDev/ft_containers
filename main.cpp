/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmacquet <kmacquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/03 13:09:39 by kmacquet          #+#    #+#             */
/*   Updated: 2021/10/21 15:30:17 by kmacquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <string>
#include <deque>
#include <vector>
#include <map>
#include <set>
#include <stack>
#include "vector.hpp"
#include "pair.hpp"
#include "map.hpp"
#include "set.hpp"
#include "stack.hpp"
#include "iterator.hpp"

#include <stdlib.h>

#define MAX_RAM 4294967296
#define BUFFER_SIZE 4096
struct Buffer
{
	int idx;
	char buff[BUFFER_SIZE];
};

#define COUNT (MAX_RAM / (int)sizeof(Buffer))

int	main(void)
{
	ft::vector<int> lst = ft::vector<int>(10, 5);
	ft::vector<int> lst2(lst);
	ft::vector<int> lsthigh = ft::vector<int>(20, 5);
	ft::vector<int>::iterator it = lst.begin();
	ft::vector<int>::iterator end = lst.end();
	ft::vector<int>::iterator it2 = lst2.begin();
	ft::vector<int>::iterator end2 = lst2.end();
	ft::vector<int>::iterator it3;
	ft::vector<int>::iterator end3;
	ft::vector<int>::iterator tmp;
	ft::vector<int>::reverse_iterator rit = lst.rbegin();
	ft::vector<int>::reverse_iterator rend = lst.rend();

	std::cout << "===================== Operators" << std::endl;
	std::cout << "lst	  == lst2 (1)	: " << (lst == lst2) << std::endl;
	std::cout << "lst	  != lst2 (0)	: " << (lst != lst2) << std::endl;
	std::cout << "lst	  >  lst2 (0)	: " << (lst > lst2) << std::endl;
	std::cout << "lst	  >=  lst2 (1)	: " << (lst >= lst2) << std::endl;
	std::cout << "lst	  <=  lst2 (1)	: " << (lst <= lst2) << std::endl;
	std::cout << "lsthigh >  lst2 (1)	: " << (lsthigh > lst2) << std::endl;
	std::cout << "lst	  <  lsthigh (1): " << (lst < lsthigh) << std::endl;
	std::cout << "lst	  <  lst2 (0)	: " << (lst < lst2) << std::endl;
	std::cout << "===================== Standard fill lst" << std::endl;
	std::cout << (*it) << std::endl;
	for (; it != end; it++)
		std::cout << *it << std::endl;
	std::cout << "capacity : " << lst.capacity() << std::endl;
	std::cout << "===================== Standard copy lst2" << std::endl;
	std::cout << (*it2) << std::endl;
	for (; it2 != end2; it2++)
		std::cout << *it2 << std::endl;
	std::cout << lst2.capacity() << std::endl;
	std::cout << "===================== Standard range lst3" << std::endl;
	ft::vector<int> lst3(lst.begin(), lst.end());
	it3 = lst3.begin();
	end3 = lst3.end();
	std::cout << (*it3) << std::endl;
	for (; it3 != end3; it3++)
		std::cout << *it3 << std::endl;
	std::cout << lst3.capacity() << std::endl;
	std::cout << "===================== Iter on set value" << std::endl;
	it = lst.begin();
	end = lst.end();
	for (int i = 1; it != end; it++)
	{
		*it = i++;
		std::cout << *it << std::endl;
	}
	std::cout << "capacity : " << lst.capacity() << std::endl;
	std::cout << "===================== Reverse" << std::endl;
	for (; rit != rend; rit++)
		std::cout << *rit << std::endl;
	std::cout << "capacity : " << lst.capacity() << std::endl;
	std::cout << "===================== Iter + reserve()" << std::endl;
	lst.reserve(12);
	it = lst.begin();
	end = lst.end();
	for (; it != end; it++)
		std::cout << *it << std::endl;
	std::cout << "capacity : " << lst.capacity() << std::endl;
	std::cout << "===================== push_back(20)" << std::endl;
	lst.push_back(20);
	it = lst.begin();
	end = lst.end();
	for (; it != end; it++)
		std::cout << *it << std::endl;
	std::cout << "capacity : " << lst.capacity() << std::endl;
	std::cout << "===================== pop_back()" << std::endl;
	lst.pop_back();
	it = lst.begin();
	end = lst.end();
	for (; it != end; it++)
		std::cout << *it << std::endl;
	std::cout << "capacity : " << lst.capacity() << std::endl;
	std::cout << "===================== Reverse + reserve()" << std::endl;
	rit = lst.rbegin();
	rend = lst.rend();
	for (; rit != rend; rit++)
		std::cout << *rit << std::endl;
	std::cout << "capacity : " << lst.capacity() << std::endl;
	std::cout << "===================== Iter + resize" << std::endl;
	lst.resize(5);
	it = lst.begin();
	end = lst.end();
	for (; it != end; it++)
		std::cout << *it << std::endl;
	std::cout << "capacity : " << lst.capacity() << std::endl;
	std::cout << "===================== Iter + resize 2 higher with set value" << std::endl;
	lst.resize(7, 100);
	it = lst.begin();
	end = lst.end();
	for (; it != end; it++)
		std::cout << *it << std::endl;
	std::cout << "capacity : " << lst.capacity() << std::endl;
	std::cout << "===================== Iter + resize 3 higher without set value" << std::endl;
	lst.resize(10);
	it = lst.begin();
	end = lst.end();
	for (; it != end; it++)
		std::cout << *it << std::endl;
	std::cout << "capacity : " << lst.capacity() << std::endl;
	std::cout << "===================== front back and back -= front " << std::endl;
	std::cout << lst.front() << std::endl;
	std::cout << lst.back() << std::endl;
	std::cout << (lst.back() -= lst.front()) << std::endl;
	std::cout << "capacity : " << lst.capacity() << std::endl;
	std::cout << "===================== at 2 5 7 9" << std::endl;
	std::cout << lst.at(2) << std::endl;
	std::cout << lst.at(5) << std::endl;
	std::cout << lst.at(7) << std::endl;
	std::cout << lst.at(9) << std::endl;
	std::cout << "capacity : " << lst.capacity() << std::endl;
	std::cout << "===================== erase(begin + 1)" << std::endl;
	it = lst.begin();
	lst.erase(++it);
	it = lst.begin();
	end = lst.end();
	for (; it != end; it++)
		std::cout << *it << std::endl;
	std::cout << "capacity : " << lst.capacity() << std::endl;
	std::cout << "===================== erase(end - 1)" << std::endl;
	end = lst.end();
	lst.erase(--end);
	end = lst.end();
	it = lst.begin();
	end = lst.end();
	for (; it != end; it++)
		std::cout << *it << std::endl;
	std::cout << "capacity : " << lst.capacity() << std::endl;
	std::cout << "===================== erase(begin + 1, end - 1)" << std::endl;
	it = lst.begin();
	end = lst.end();
	lst.erase(++it, --end);
	end = lst.end();
	it = lst.begin();
	end = lst.end();
	for (; it != end; it++)
		std::cout << *it << std::endl;
	std::cout << "capacity : " << lst.capacity() << std::endl;
	std::cout << "===================== swap lst and lst2 " << std::endl;
	lst.swap(lst2);
	it = lst.begin();
	end = lst.end();
	for (; it != end; it++)
		std::cout << *it << std::endl;
	std::cout << "capacity : " << lst.capacity() << std::endl;
	std::cout << "===================== swap non-member x2 " << std::endl;
	swap(lst, lst2);
	it = lst.begin();
	end = lst.end();
	for (; it != end; it++)
		std::cout << *it << std::endl;
	std::cout << "capacity : " << lst.capacity() << std::endl;
	std::cout << "==" << std::endl;
	swap(lst, lst2);
	it = lst.begin();
	end = lst.end();
	for (; it != end; it++)
		std::cout << *it << std::endl;
	std::cout << "capacity : " << lst.capacity() << std::endl;
	std::cout << "===================== assign(n, val) " << std::endl;
	lst.assign(10, 10);
	it = lst.begin();
	end = lst.end();
	for (; it != end; it++)
		std::cout << *it << std::endl;
	std::cout << "capacity : " << lst.capacity() << std::endl;
	std::cout << "===================== assign(first, last) " << std::endl;
	it2 = lst2.begin();
	end2 = lst2.end();
	tmp = end2;
	for (; it2 != end2; it2++)
		std::cout << *it2 << std::endl;
	std::cout << "==" << std::endl;
	it2 = lst2.begin();
	lst.assign(it2, tmp);
	it = lst.begin();
	end = lst.end();
	for (; it != end; it++)
		std::cout << *it << std::endl;
	std::cout << "capacity : " << lst.capacity() << std::endl;
	std::cout << "===================== insert x3 " << std::endl;
	it = lst.begin();
	std::cout << "inserted : " << *(lst.insert(it, 20)) << std::endl;
	it = lst.begin();
	std::cout << "inserted : " << *(lst.insert(it, 20)) << std::endl;
	it = lst.begin();
	std::cout << "inserted : " << *(lst.insert(it, 20)) << std::endl;
	it = lst.begin();
	end = lst.end();
	for (; it != end; it++)
		std::cout << *it << std::endl;
	std::cout << "capacity : " << lst.capacity() << std::endl;
	std::cout << "===================== insert range 3 " << std::endl;
	it = lst.begin();
	lst.insert(++it, (size_t)3, 300);
	it = lst.begin();
	end = lst.end();
	for (; it != end; it++)
		std::cout << *it << std::endl;
	std::cout << "capacity : " << lst.capacity() << std::endl;
	std::cout << "===================== clear lst2 " << std::endl;
	lst.clear();
	std::cout << "capacity : " << lst.capacity() << std::endl;
	std::cout << lst.size() << std::endl;
	std::cout << "===================== stack " << std::endl;
	ft::stack<int, ft::vector<int> > stk;
	for (int i = 0; i < 10; i++)
		stk.push(i);
	while (stk.top())
	{
		std::cout << stk.top() << std::endl;
		stk.pop();
	}
	std::cout << "===================== map " << std::endl;
	ft::map<int, int> map;

	for (int i = 0; i < 19; i++)
		map.insert(ft::make_pair(i, 10));

	map.insert(ft::make_pair(7, 10));

	map.erase(18);
	map.erase(0);

	ft::map<int, int>::iterator it_m = map.begin();
	ft::map<int, int>::iterator end_m = map.end();
	for (; it_m != end_m; it_m++)
		std::cout << it_m->first << std::endl;
	it_m = map.begin();
	end_m = map.end();
	while (it_m != end_m)
		map.erase(it_m++);

	std::cout << "===================== set " << std::endl;
	ft::set<int> set;


	for (int i = 0; i < 19; i++)
		set.insert(i);
	set.insert(7);
	set.erase(18);
	set.erase(0);

	ft::set<int, int>::iterator it_s = set.begin();
	ft::set<int, int>::iterator end_s = set.end();
	for (; it_s != end_s; it_s++)
		std::cout << *it_s << std::endl;
	it_s = set.begin();
	end_s = set.end();
	while (it_s != end_s)
		set.erase(it_s++);

	std::cout << "FINITO" << std::endl;
	return (0);
}