# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: phunguye <phunguye@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/05/02 16:17:56 by phunguye          #+#    #+#              #
#    Updated: 2022/05/02 16:17:56 by phunguye         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #
SRCS =	ft_printf.c\
		ft_printf_util.c\
		sub_utils.c\
		ft_print_hex.c\

OBJS = $(SRCS:c=o)

CC = gcc
CFLAGS = -Wall -Wextra -Werror -c
RM = rm -rf
HEADER = ft_printf.h

NAME = libftprintf.a

all: $(OBJ) $(NAME)

$(NAME):
	$(MAKE) -C ./libft
	cp libft/libft.a $(NAME)
	$(CC) $(CFLAGS) $(HEADER) $(SRCS)
	ar rcs $(NAME) $(OBJS)

clean:
	$(MAKE) clean -C ./libft
	$(RM) $(OBJS)

fclean:
	$(MAKE) fclean -C ./libft
	$(RM) $(OBJS)
	$(RM) $(NAME)

re:	fclean all

.PHONY: all clean fclean