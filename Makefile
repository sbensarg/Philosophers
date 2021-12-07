# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sbensarg <sbensarg@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/11/11 19:43:47 by sbensarg          #+#    #+#              #
#    Updated: 2021/12/05 21:35:14 by sbensarg         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo
SRCS = philo.c ft_atoi.c
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
