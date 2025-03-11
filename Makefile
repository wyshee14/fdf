# color
GREEN = \033[0;32m
WHITE = \033[0m

#Program Name
NAME = fdf

#The -I (uppercase i) flag is used to add a directory to the list of directories
#the compiler searches for header files (#include directives).
#Directories
LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a
MLX_DIR = minilibx-linux
MINILIBX-LINUX = $(MLX_DIR)/libmlx.a
INC_DIR = include/
SRC_DIR = src/
INC = -I$(INC_DIR)

CC = cc #-fsanitize=address
CFLAGS = -Wall -Wextra -Werror -g3 -O3 -I$(INC_DIR) -I$(LIBFT_DIR) -Imlx_linux

#Source Files
#addprefix <prefix>, <list>
#<prefix> is the string that added to the beginning of each word
SRC_FILES = bresenham.c	color.c			draw.c	error_handling.c	init_fdf.c	init_point.c\
			key_hooks.c	key_hooks2.c	main.c	parse_map.c			rotate.c	utils.c
SRC = $(addprefix $(SRC_DIR), $(SRC_FILES))

OBJ_SRC = $(SRC:.c=.o)

all: $(NAME)

# -L tells the linker where to look for libraries -L<directory>
$(NAME) : $(OBJ_SRC)
	@make -C $(LIBFT_DIR)
	@make -C $(MLX_DIR)
	$(CC) $(CFLAGS) $(OBJ_SRC) -L$(LIBFT_DIR) -lft -L$(MLX_DIR) -lmlx -lXext -lX11 -lm -lz -o $(NAME)
	@echo "$(GREEN)-----COMPILED DONE-----\n"

%.o : %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJ_SRC)
	@make -C $(LIBFT_DIR) clean
	@make -C $(MLX_DIR) clean

fclean : clean
	rm -f $(NAME)
	@make -C $(LIBFT_DIR) fclean
	@echo "$(GREEN)-----FULLY REMOVED-----\n$(WHITE)"

re: fclean all

norm:
	@echo "----- check include -----"
	@norminette include/
	@echo "\n----- check libft -----"
	@norminette libft/
	@echo "\n----- check src -----"
	@norminette src/

.PHONY: all clean fclean re norm
