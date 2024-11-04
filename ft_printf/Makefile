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

SRC =			ft_printf.c

OBJ =			$(SRC:.c=.o)

LIBFT_PATH =	./libft
LIBFT =			$(LIBFT_PATH)/libft.a

NAME =			libftprintf.a
CC =			cc
CFLAGS =		-Wall -Wextra -Werror

all:			$(NAME)

$(NAME):		$(OBJ) $(LIBFT)
				ar -rcs $(NAME) $(OBJ) $(LIBFT_PATH)/*.o

$(LIBFT):
				$(MAKE) -C $(LIBFT_PATH) all

clean:
				$(MAKE) -C $(LIBFT_PATH) clean
				rm -f $(OBJ)

fclean:			clean
				$(MAKE) -C $(LIBFT_PATH) fclean
				rm -f $(NAME)

re:				fclean all

.PHONY:			all clean fclean re libft