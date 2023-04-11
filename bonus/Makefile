# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nettalha <nettalha@student.1337.ma>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/10 22:39:57 by nettalha          #+#    #+#              #
#    Updated: 2023/04/10 22:40:01 by nettalha         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= philo_bonus
SRCS		= philo_bonus.c philo_bonus_utils1.c  philo_bonus_utils2.c bonus_utils.c
OBJS		= ${SRCS:.c=.o}

CC		= gcc
CFLAGS	= -Wall -Wextra -Werror -pthread
RM		= rm -f

all:		${NAME}

${NAME}:	${OBJS}
			$(CC) $(CFLAGS) $^ -o $@

clean:
			$(RM) ${OBJS}

fclean:	clean
			$(RM) ${NAME}

re:			fclean all

.PHONY: all clean fclean re
