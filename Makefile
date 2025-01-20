# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mgayout <mgayout@student.42nice.fr>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/05 12:39:21 by mgayout           #+#    #+#              #
#    Updated: 2025/01/14 16:16:30 by mgayout          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	pipex
NAMEB	=	pipex_bonus

FLAG	=	-Wextra -Wall -Werror

SRCDIR	= src
SRCBDIR	= bonus
HEADIR	= include

SRC		= $(shell find $(SRCDIR) -name '*.c')
SRCB	= $(shell find $(SRCBDIR) -name '*.c')


PRINTFDIR	=	ft_printf-main
PRINTFURL	=	https://github.com/mgayout/ft_printf/archive/refs/heads/main.tar.gz
PRINTFAR	=	libftprintf.a

GNLDIR		=	get_next_line-main
GNLURL		=	https://github.com/mgayout/get_next_line/archive/refs/heads/main.tar.gz
GNLAR		=	get_next_line.a

AR			=	$(PRINTFDIR)/$(PRINTFAR) $(GNLDIR)/$(GNLAR)

all: $(NAME)

$(NAME): $(PRINTFAR) $(GNLAR)
			@gcc $(SRC) $(AR) $(FLAG) -o $(NAME)
			
bonus: $(NAMEB)

$(NAMEB): $(PRINTFAR) $(GNLAR)
			@gcc $(SRCB) $(AR) $(FLAG) -o $(NAMEB)

$(PRINTFAR): 
					@if [ ! -d $(PRINTFDIR) ]; then \
						curl -L $(PRINTFURL) -o printf.tar.gz; \
						tar -xzf printf.tar.gz; \
						rm printf.tar.gz; \
					fi
					@make -C $(PRINTFDIR)

$(GNLAR):
					@if [ ! -d $(GNLDIR) ]; then \
						curl -L $(GNLURL) -o gnl.tar.gz; \
						tar -xzf gnl.tar.gz; \
						rm gnl.tar.gz; \
					fi
					@make -C $(GNLDIR)

clean:
			@make clean -C $(PRINTFDIR)
			@make clean -C $(GNLDIR)

fclean: clean
			@rm -rf $(NAME) $(NAMEB)
			@rm -rf $(PRINTFDIR) $(GNLDIR)

re: fclean all

rebonus: fclean bonus

.PHONY: all bonus clean fclean re rebonus