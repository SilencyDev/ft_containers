/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmacquet <kmacquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/03 13:09:39 by kmacquet          #+#    #+#             */
/*   Updated: 2021/09/17 15:58:58 by kmacquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <string>
#include <deque>
#include <vector>
#include "vector.hpp"
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
	ft::vector<int>::iterator it = lst.begin();
	ft::vector<int>::iterator end = lst.end();
	ft::vector<int>::iterator it2 = lst2.begin();
	ft::vector<int>::iterator end2 = lst2.end();
	ft::vector<int>::reverse_iterator rit = lst.rbegin();
	ft::vector<int>::reverse_iterator rend = lst.rend();

	std::cout << "===================== Standard fill" << std::endl;
	std::cout << &(*it) << std::endl;
	for (; it != end; it++)
		std::cout << *it << std::endl;
	std::cout << "===================== Standard copy" << std::endl;
	std::cout << &(*it2) << std::endl;
	for (; it2 != end2; it2++)
		std::cout << *it2 << std::endl;
	std::cout << "===================== Iter on set value" << std::endl;
	it = lst.begin();
	end = lst.end();
	for (int i = 1; it != end; it++)
	{
		*it = i++;
		std::cout << *it << std::endl;
	}
	std::cout << "===================== Reverse" << std::endl;
	for (; rit != rend; rit++)
	{
		std::cout << *rit << std::endl;
	}
	std::cout << "===================== Iter + reserve()" << std::endl;
	lst.reserve(12);
	it = lst.begin();
	end = lst.end();
	for (; it != end; it++)
		std::cout << *it << std::endl;
	std::cout << "===================== push_back(20)" << std::endl;
	lst.push_back(20);
	it = lst.begin();
	end = lst.end();
	for (; it != end; it++)
		std::cout << *it << std::endl;
	std::cout << "===================== pop_back()" << std::endl;
	lst.pop_back();
	it = lst.begin();
	end = lst.end();
	for (; it != end; it++)
	{
		std::cout << *it << std::endl;
	}
	std::cout << "===================== Reverse + reserve()" << std::endl;
	rit = lst.rbegin();
	rend = lst.rend();
	for (; rit != rend; rit++)
		std::cout << *rit << std::endl;
	std::cout << "===================== Iter + resize" << std::endl;
	lst.resize(5);
	it = lst.begin();
	end = lst.end();
	for (; it != end; it++)
		std::cout << *it << std::endl;
	std::cout << "===================== Iter + resize 2 higher with set value" << std::endl;
	lst.resize(7, 100);
	it = lst.begin();
	end = lst.end();
	for (; it != end; it++)
	{
		std::cout << *it << std::endl;
	}
	std::cout << "===================== Iter + resize 3 higher without set value" << std::endl;
	lst.resize(10);
	it = lst.begin();
	end = lst.end();
	for (; it != end; it++)
		std::cout << *it << std::endl;
	std::cout << "===================== front back and back -= front " << std::endl;
	std::cout << lst.front() << std::endl;
	std::cout << lst.back() << std::endl;
	std::cout << (lst.back() -= lst.front()) << std::endl;
	std::cout << "===================== at 2 5 7 9" << std::endl;
	std::cout << lst.at(2) << std::endl;
	std::cout << lst.at(5) << std::endl;
	std::cout << lst.at(7) << std::endl;
	std::cout << lst.at(9) << std::endl;

	std::cout << "===================== erase(begin + 1)" << std::endl;
	it = lst.begin();
	lst.erase(++it);
	it = lst.begin();
	end = lst.end();
	for (; it != end; it++)
		std::cout << *it << std::endl;
	std::cout << "===================== erase(end - 1)" << std::endl;
	end = lst.end();
	lst.erase(--end);
	end = lst.end();
	it = lst.begin();
	end = lst.end();
	for (; it != end; it++)
		std::cout << *it << std::endl;
	std::cout << "===================== erase(begin + 1, end - 1)" << std::endl;
	it = lst.begin();
	end = lst.end();
	lst.erase(++it, --end);
	end = lst.end();
	it = lst.begin();
	end = lst.end();
	for (; it != end; it++)
		std::cout << *it << std::endl;
	std::cout << "===================== swap lst and lst2 " << std::endl;
	lst.swap(lst2);
	it = lst.begin();
	end = lst.end();
	for (; it != end; it++)
		std::cout << *it << std::endl;
	std::cout << "===================== assign(n, val) " << std::endl;
	lst.assign(10, 10);
	it = lst.begin();
	end = lst.end();
	for (; it != end; it++)
		std::cout << *it << std::endl;
	std::cout << "===================== clear lst2 " << std::endl;
	lst.clear();
	std::cout << lst.size() << std::endl;
	return (0);
}

// int main(int argc, char** argv) {
// 	if (argc != 2)
// 	{
// 		std::cerr << "Usage: ./test seed" << std::endl;
// 		std::cerr << "Provide a seed please" << std::endl;
// 		std::cerr << "Count value:" << COUNT << std::endl;
// 		return 1;
// 	}
// 	const int seed = atoi(argv[1]);
// 	srand(seed);

// 	std::vector<std::string> vector_str;
// 	std::vector<int> vector_int;
// 	std::stack<int> stack_int;
// 	std::vector<Buffer> vector_buffer;
// 	std::stack<Buffer, std::deque<int> > stack_deq_buffer;
// 	std::map<int, int> map_int;

// 	for (int i = 0; i < COUNT; i++)
// 	{
// 		vector_buffer.push_back(Buffer());
// 	}

// 	for (int i = 0; i < COUNT; i++)
// 	{
// 		const int idx = rand() % COUNT;
// 		vector_buffer[idx].idx = 5;
// 	}
// 	std::vector<Buffer>().swap(vector_buffer);

// 	try
// 	{
// 		for (int i = 0; i < COUNT; i++)
// 		{
// 			const int idx = rand() % COUNT;
// 			vector_buffer.at(idx);
// 			std::cerr << "Error: THIS VECTOR SHOULD BE EMPTY!!" <<std::endl;
// 		}
// 	}
// 	catch(const std::exception& e)
// 	{
// 		//NORMAL ! :P
// 	}
	
// 	for (int i = 0; i < COUNT; ++i)
// 	{
// 		map_int.insert(std::make_pair(rand(), rand()));
// 	}

// 	int sum = 0;
// 	for (int i = 0; i < 10000; i++)
// 	{
// 		int access = rand();
// 		sum += map_int[access];
// 	}
// 	std::cout << "should be constant with the same seed: " << sum << std::endl;

// 	{
// 		std::map<int, int> copy = map_int;
// 	}
// 	MutantStack<char> iterable_stack;
// 	for (char letter = 'a'; letter <= 'z'; letter++)
// 		iterable_stack.push(letter);
// 	for (MutantStack<char>::iterator it = iterable_stack.begin(); it != iterable_stack.end(); it++)
// 	{
// 		std::cout << *it;
// 	}
// 	std::cout << std::endl;
// 	return (0);
// }