# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: chicky <chicky@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/11/11 19:43:47 by sbensarg          #+#    #+#              #
#    Updated: 2021/12/08 19:53:03 by chicky           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo
SRCS = philo.c ft_atoi.c utils_philo.c
FLAGS= -Wall -Wextra -Werror -lpthread -g
rm = rm -f
CC = gcc

all : $(NAME)

$(NAME) : $(SRCS)
	@$(CC) $(FLAGS) $(SRCS) -pthread -o $(NAME)

clean :

fclean : clean
	@$(rm) $(NAME)
	@$(rm) $(NAME_BONUS)

re: fclean all
