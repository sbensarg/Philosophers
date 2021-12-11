# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sbensarg <sbensarg@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/11/11 19:43:47 by sbensarg          #+#    #+#              #
#    Updated: 2021/12/11 18:14:33 by sbensarg         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo
SRCS = philo.c utils_philo.c supervisor.c init.c
FLAGS= -Wall -Wextra -Werror -lpthread 
rm = rm -f
CC = gcc

all : $(NAME)

$(NAME) : $(SRCS)
	@$(CC) $(FLAGS) $(SRCS) -o $(NAME)

clean :

fclean : clean
	@$(rm) $(NAME)
	@$(rm) $(NAME_BONUS)

re: fclean all
