# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nettalha <nettalha@student.1337.ma>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/10 12:32:12 by nettalha          #+#    #+#              #
#    Updated: 2023/03/12 12:14:35 by nettalha         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= philo
SRCS		= philo.c philo_utils.c utils.c
OBJS		= ${SRCS:.c=.o}

CC		= gcc
CFLAGS	= -Wall -Wextra -Werror
RM		= rm -f

all:		${NAME}

${NAME}:	${OBJS}
			$(CC) $^ -o $@

clean:
			$(RM) ${OBJS}

fclean:	clean
			$(RM) ${NAME}

re:			fclean all

.PHONY: all clean fclean re