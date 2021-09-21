# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kmacquet <kmacquet@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/08/03 13:10:40 by kmacquet          #+#    #+#              #
#    Updated: 2021/09/21 13:29:25 by kmacquet         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = Containers
CXX = clang++
CXXFLAGS = -Wall -Wextra -Werror -fsanitize=address -std=c++98
SRCS = $(wildcard *.cpp)
OBJS = $(SRCS:.cpp=.o)

all : $(NAME)

$(NAME) : $(OBJS)
	$(CXX) $(CXXFLAGS) $^ -o $@

clean :
	$(RM) $(OBJS)

fclean : clean
	$(RM) $(NAME)

re : fclean all

.PHONY: all re fclean clean