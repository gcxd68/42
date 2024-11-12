# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gdosch <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/05 11:47:52 by gdosch            #+#    #+#              #
#    Updated: 2024/11/05 11:47:53 by gdosch           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC =			ft_printf.c

OBJ =			$(SRC:.c=.o)

NAME =			libftprintf.a
CC =			cc
CFLAGS =		-Wall -Wextra -Werror

all:			$(NAME)

$(NAME):		$(OBJ)
				ar -rcs $(NAME) $(OBJ)

clean:
				rm -f $(OBJ)

fclean:			clean
				rm -f $(NAME)

re:				fclean all

.PHONY:			all clean fclean re
