#FOR LINUX: ~~~~~~~~~~~~~~~~~~~~~~~~~

NAME = miniRT
CC = gcc
FLAGS = -Werror -Wextra -Wall

files = main.c\
	image.c\
	ft_pixelput.c\
	vct_operations.c\
	pln_intersects.c\
	sph_intersects.c\
	inits.c\
	get_infos.c\
	colour.c\
	
	
SRCS = $(addprefix ./SRCS/, $(files))
OBJS = $(SRCS:c=o)

gnl = get_next_line.c\
			get_next_line_utils.c\

GNL_SRCS = $(addprefix ./get_next_line/, $(gnl))
GNL_OBJS = $(GNL_SRCS:c=o)

LIBFTPRINTF = ./libftprintf/libftprintf.a
MINILIBX = ./mlx_linux/libmlx.a

.PHONY: all clean fclean re

all: $(NAME)

$(LIBFTPRINTF):
	$(MAKE) -C ./libftprintf

$(MINILIBX):
	$(MAKE) -sC ./mlx_linux

$(NAME): $(LIBFTPRINTF) $(MINILIBX) $(GNL_OBJS) $(OBJS)
	$(CC) $(GNL_OBJS) $(OBJS) $(LIBFTPRINTF) -Lmlx_linux -lmlx_Linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz -o $(NAME)
	@echo "\n miniRT compiled\n"

clean:
	rm -rf ./SRCS/*.o
	rm -rf ./get_next_line/*.o
	$(MAKE) clean -C ./libftprintf
	$(MAKE) clean -C ./mlx_linux

fclean:
	rm -rf ./SRCS/*.o
	rm -rf ./get_next_line/*.o
	rm -rf libmlx.dylib
	rm -rf $(NAME)
	$(MAKE) fclean -C ./libftprintf
	$(MAKE) clean -C ./mlx_linux

re: fclean all




#FOR MACOS: ~~~~~~~~~~~~~~~~~~~~~~~~~

# NAME = miniRT
# CC = gcc
# FLAGS = -Werror -Wextra -Wall

# files = main.c\
# 	image.c\
# 	ft_pixelput.c\
# 	vct_operations.c\
# 	pln_intersects.c\
# 	sph_intersects.c\
# 	inits.c\
# 	get_infos.c\
# 	colour.c\
	
	
# SRCS = $(addprefix ./SRCS/, $(files))
# OBJS = $(SRCS:c=o)

# gnl = get_next_line.c\
# 			get_next_line_utils.c\

# GNL_SRCS = $(addprefix ./get_next_line/, $(gnl))
# GNL_OBJS = $(GNL_SRCS:c=o)

# LIBFTPRINTF = ./libftprintf/libftprintf.a
# MINILIBX = ./minilibx/libmlx.a

# .PHONY: all clean fclean re

# all: $(NAME)

# $(LIBFTPRINTF):
# 	$(MAKE) -C ./libftprintf

# $(MINILIBX):
# 	$(MAKE) -sC ./minilibx

# $(NAME): $(LIBFTPRINTF) $(MINILIBX) $(GNL_OBJS) $(OBJS)
# 	$(CC) $(FLAGS) -Lminilibx -lmlx -framework OpenGL -framework AppKit $(GNL_OBJS) $(OBJS) -lm $(LIBFTPRINTF) $(MINILIBX) -o $(NAME)
# 	@echo "\n miniRT compiled\n"

# clean:
# 	rm -rf ./SRCS/*.o
# 	rm -rf ./get_next_line/*.o
# 	$(MAKE) clean -C ./libftprintf
# 	$(MAKE) clean -C ./minilibx

# fclean:
# 	rm -rf ./SRCS/*.o
# 	rm -rf ./get_next_line/*.o
# 	rm -rf libmlx.dylib
# 	rm -rf $(NAME)
# 	$(MAKE) fclean -C ./libftprintf
# 	$(MAKE) clean -C ./minilibx

# re: fclean all
