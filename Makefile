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
#BONUS_DIR = bonus/
INC = -I$(INC_DIR)

CC = cc #-g3 -O3 -fsanitize=address
CFLAGS = -Wall -Wextra -Werror -I$(INC_DIR) -I$(LIBFT_DIR) -Imlx_linux

#Source Files
#addprefix <prefix>, <list>
#<prefix> is the string that added to the beginning of each word
SRC = $(wildcard $(SRC_DIR)*.c)

#BONUS = $(BONUS_DIR)bonus.c $(BONUS_DIR)utils_bonus.c $(BONUS_DIR)utils2_bonus.c

OBJ_SRC = $(SRC:.c=.o)
#OBJ_BONUS = $(BONUS:.c=.o)

all: $(NAME)

# -L tells the linker where to look for libraries -L<directory>
$(NAME) : $(OBJ_SRC)
	@make -C $(LIBFT_DIR)
	@make -C $(MLX_DIR)
	$(CC) $(CFLAGS) $(OBJ_SRC) -L$(LIBFT_DIR) -lft -L$(MLX_DIR) -lmlx -lXext -lX11 -lm -lz -o $(NAME)
	@echo "$(GREEN)-----COMPILED DONE-----\n"

#bonus: $(OBJ_BONUS)
#	@make -C libft
#	$(CC) $(CFLAGS) $(OBJ_BONUS) $(LIBFT) -o $(NAME)
#	@echo "$(GREEN)-----COMPILED DONE-----\n"

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

.PHONY: all clean fclean re #bonus
