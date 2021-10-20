# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kmacquet <kmacquet@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/08/03 13:10:40 by kmacquet          #+#    #+#              #
#    Updated: 2021/10/20 18:02:36 by kmacquet         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = Containers
NAME2 = std
CXX = clang++
CXXFLAGS = -Wall -Wextra -Werror  -std=c++98
SRCS = main.cpp
SRCS2 = main2.cpp
OBJS = $(SRCS:.cpp=.o)
OBJS2 = $(SRCS2:.cpp=.o)

all : $(NAME)

$(NAME) : $(OBJS)
	$(CXX) $(CXXFLAGS) $^ -o $@

$(NAME2) : $(OBJS2)
	$(CXX) $(CXXFLAGS) $^ -o $@

clean :
	$(RM) $(OBJS)
	$(RM) $(OBJS2)

fclean : clean
	$(RM) $(NAME)
	$(RM) $(NAME2)

re : fclean all

diff : $(NAME) $(NAME2)
	./$(NAME) > log1
	./$(NAME2) > log2
	diff log1 log2
	@make fclean

.PHONY: all re fclean clean