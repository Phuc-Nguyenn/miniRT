# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: phunguye <phunguye@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/20 11:12:55 by phunguye          #+#    #+#              #
#    Updated: 2022/12/02 15:46:38 by phunguye         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS =	ft_atoi.c\
		ft_isalnum.c\
		ft_isalpha.c\
		ft_isascii.c\
		ft_isdigit.c\
		ft_isprint.c\
		ft_bzero.c\
		ft_calloc.c\
		ft_memchr.c\
		ft_memcmp.c\
		ft_memcpy.c\
		ft_memmove.c\
		ft_memset.c\
		ft_putchar_fd.c\
		ft_putnbr_fd.c\
		ft_putendl_fd.c\
		ft_putchar.c\
		ft_putstr_fd.c\
		ft_strchr.c\
		ft_strlcat.c\
		ft_strlcpy.c\
		ft_strlen.c\
		ft_strncmp.c\
		ft_strnstr.c\
		ft_strdup.c\
		ft_strtrim.c\
		ft_split.c\
		ft_strmapi.c\
		ft_striteri.c\
		ft_strjoin.c\
		ft_substr.c\
		ft_itoa.c\
		ft_tolower.c\
		ft_toupper.c\
		ft_strrchr.c\
		ft_putnstr_fd.c\

OBJS = $(SRCS:c=o)

CC = gcc
CFLAGS = -Wall -Wextra -Werror -c
RM = rm -rf
HEADER = libft.h

NAME = libft.a

all:	$(NAME)

$(NAME):
	$(CC) $(CFLAGS) $(SRCS)
	ar rcs $(NAME) $(OBJS)

clean:	
	$(RM) $(OBJS)

fclean:		clean
	$(RM) $(NAME)

re:	fclean all

.PHONY: all clean fclean