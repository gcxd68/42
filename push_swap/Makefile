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

SRC =			push_swap.c \
				array.c \
				ops.c \
				sort_few.c \
				sort_many.c \
				sort_utils.c

SRCB =			push_swap_bonus.c \
				array_bonus.c \
				ops_bonus.c

OBJ =			$(SRC:.c=.o)
OBJB =			$(SRCB:.c=.o)

NAME =			push_swap
BONUS_NAME =	checker

CC =			cc
CFLAGS =		-Wall -Wextra -Werror

LIBFT =			libft/libft.a
LIBFT_DIR = 	libft

all:			$(LIBFT) $(NAME)

$(NAME):		$(OBJ)
				$(CC) $(CFLAGS) -o $(NAME) $(OBJ) $(LIBFT)

bonus:			$(LIBFT) $(BONUS_NAME)

$(BONUS_NAME):	$(OBJB)
				$(CC) $(CFLAGS) -o $(BONUS_NAME) $(OBJB) $(LIBFT)

$(LIBFT):
				make -C $(LIBFT_DIR)

clean:
				rm -f $(OBJ) $(OBJB)
				make clean -C $(LIBFT_DIR)

fclean:			clean
				rm -f $(NAME) $(BONUS_NAME)
				make fclean -C $(LIBFT_DIR)

re:				fclean all

.PHONY:			bonus all clean fclean re