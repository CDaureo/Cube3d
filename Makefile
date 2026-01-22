# =========================
# Proyecto: cub3D (simple)
# =========================

NAME	= cub3D
CC  = cc
CFLAGS  = -Wall -Wextra -Werror
INCLUDES  = -I./includes

# miniLibX (fuente local)
MLX_DIR	= ./minilibx-linux
MLX_A	= $(MLX_DIR)/libmlx.a
MLX_FLAGS  = -L$(MLX_DIR) -lmlx -lXext -lX11 -lm

# Libft en src/library
LIBFT_DIR   = ./src/library
LIBFT_A	 = $(LIBFT_DIR)/libft.a
LIBFT_FLAGS = -L$(LIBFT_DIR) -lft

# =========================
# Fuentes
# =========================
SRC_DIR  = ./src
PARSING_DIR = $(SRC_DIR)/parsing
UTILS_DIR = $(SRC_DIR)/utils
FREE_DIR = $(SRC_DIR)/free
VALIDATE_DIR = $(SRC_DIR)/validate

SRC = $(SRC_DIR)/main.c \
	$(PARSING_DIR)/parser.c \
	$(PARSING_DIR)/p_colors.c \
	$(PARSING_DIR)/p_map.c \
	$(PARSING_DIR)/p_textures.c \
	$(UTILS_DIR)/u_trim.c \
	$(UTILS_DIR)/u_maps.c \
	$(UTILS_DIR)/u_blank.c \
	$(FREE_DIR)/f_textures.c \
	$(FREE_DIR)/f_map.c \
	$(FREE_DIR)/f_game.c \
	$(VALIDATE_DIR)/validator.c

OBJ = $(SRC:.c=.o)

# =========================
# Reglas
# =========================
all: $(LIBFT_A) $(MLX_A) $(NAME)

$(LIBFT_A):
	@$(MAKE) -C $(LIBFT_DIR)

$(MLX_A):
	@$(MAKE) -C $(MLX_DIR)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(INCLUDES) $(MLX_FLAGS) $(LIBFT_FLAGS) -o $(NAME)

# Compilación objetos
%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	@rm -f $(OBJ)

fclean:
	@rm -f $(OBJ) $(NAME)
	@$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re