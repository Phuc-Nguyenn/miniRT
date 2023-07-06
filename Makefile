GREEN=\033[38;5;046m
YELLOW =\033[38;5;220m
END=\033[0m
NEWSECTION = "$(GREEN)--------------------------------------------------$(END)"

NAME = miniRT
LIBFT = ./libft/libft.a
CC = gcc
FLAGS = -Wall -Wextra -Werror
HEADER= miniRT.h

LIBRARIES = -lmlx -lm -lft -L$(LIBFT_DIRECTORY) -L$(MINILIBX_DIRECTORY) -framework OpenGL -framework AppKit
INCLUDES = -I$(LIBFT_HEADERS) -I$(MINILIBX_HEADERS)

LIBFT = $(LIBFT_DIRECTORY)libft.a
LIBFT_DIRECTORY = ./libft/
LIBFT_HEADERS = $(LIBFT_DIRECTORY)

#for linux
#MINILIBX = $(MINILIBX_DIRECTORY)libmlx.a
#MINILIBX_DIRECTORY = ./minilibx-linux/
#MINILIBX_HEADERS = $(MINILIBX_DIRECTORY)

#for mac
MINILIBX = $(MINILIBX_DIRECTORY)libmlx.a
MINILIBX_DIRECTORY = ./minilibx/
MINILIBX_HEADERS = $(MINILIBX_DIRECTORY)

srcs = 

gnl_srcs =	get_next_line.c\
			get_next_line_utils.c\

SRCS = $(addprefix ./SRCS/, $(srcs))
OBJS = $(SRCS:c=o)
GNL_SRCS = $(addprefix ./get_next_line/, $(gnl_srcs))
GNL_OBJS = $(GNL_SRCS:c=o)

.PHONY: all clean fclean re

all: $(NAME)

$(LIBFT):
	@echo "$(YELLOW)Building libft library...$(END)"
	$(MAKE) -C ./libft
	@echo "$(GREEN)libft library built successfully!$(END)"
	@echo $(NEWSECTION)

$(MINILIBX):
	@echo "$(NAME): $(GREEN)Creating $(MINILIBX)...$(END)"
	@$(MAKE) -sC $(MINILIBX_DIRECTORY)

$(NAME): $(OBJS) $(LIBFT) $(GNL_OBJS) $(MINILIBX)
	@echo "$(YELLOW)Compiling FdF program...$(END)"
	@$(CC) $(CFLAGS) $(LIBRARIES) $(OBJS) $(GNL_OBJS) -lm $(MLX_FLAGS) $(LIBFT) -o $(NAME)
	@echo "$(GREEN)FdF program compiled!$(END)"
	@echo $(NEWSECTION)

$(MINILIBX):
	@echo "$(NAME): $(GREEN)Creating $(MINILIBX)...$(END)"
	@$(MAKE) -sC $(MINILIBX_DIRECTORY)

clean:
	@echo "$(YELLOW)Removing object files...$(END)"
	@rm -rf ./SRCS/*.o
	@rm -rf ./get_next_line/*.o
	@$(MAKE) clean -C ./libft
	@$(MAKE) clean -C $(MINILIBX_DIRECTORY)
	@echo "$(GREEN)Object files deleted!$(END)"
	@echo $(NEWSECTION)

fclean: clean
	@echo "$(YELLOW)Removing object files and program...$(END)"
	$(MAKE) fclean -C ./libft
	@rm -rf libmlx.dylib
	@rm -rf $(NAME)
	@echo "$(GREEN)fclean completed!$(END)"
	@echo $(NEWSECTION)
	
re: fclean all