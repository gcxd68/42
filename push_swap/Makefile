# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gdosch <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/17 10:34:21 by gdosch            #+#    #+#              #
#    Updated: 2024/10/17 10:34:24 by gdosch           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC =		push_swap.c \
			array.c \
			ops.c \
			sort_few.c \
			sort_many.c \
			sort_utils.c

OBJ =		$(SRC:.c=.o)

SRCB =		checker.c \
			array.c \
			ops.c

OBJB =		$(SRCB:.c=.o)

NAME =		push_swap
CC =		cc
CFLAGS =	-Wall -Wextra -Werror

all:		$(NAME)

$(NAME):	$(OBJ)
			ar -rcs $(NAME) $(OBJ)

bonus:		$(OBJB)
			ar -rcs $(NAME) $(OBJB)

clean:
			rm -f $(OBJ) $(OBJB)

fclean:		clean
			rm -f $(NAME)

re:			fclean all

.PHONY:		bonus all clean fclean re