# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mgayout <mgayout@student.42nice.fr>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/05 12:39:21 by mgayout           #+#    #+#              #
#    Updated: 2024/03/06 15:29:14 by mgayout          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	pipex
CC		=	gcc
CFLAGS	=	-Wextra -Wall -Werror -g3
REMOVE	=	rm -f
SRC_DIR	=	./src/
LIBFT	=	./libft-/libft.a

SRCS	=	src/main.c \
			src/init_pipex.c \
			src/children.c \

all: $(LIBFT) $(NAME)

$(NAME):
			$(CC) $(SRCS) $(LIBFT) $(CFLAGS) -o $(NAME)

$(LIBFT):
			@make -C libft-/

clean:	
			@make clean -C libft-/

fclean:		clean
			$(REMOVE) $(NAME)
			$(REMOVE) $(LIBFT)

re: fclean all

.PHONY: all clean fclean re