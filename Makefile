# =========================
# Proyecto: cub3D (simple)
# =========================

NAME	  = cub3D
CC  = cc
CFLAGS  = -Wall -Wextra -Werror
INCLUDES  = -I./includes

# miniLibX (fuente local)
MLX_DIR    = ./minilibx-linux
MLX_FLAGS  = -L$(MLX_DIR) -lmlx -lXext -lX11 -lm

# Libft en src/library
LIBFT_DIR   = ./src/library
LIBFT_A     = $(LIBFT_DIR)/libft.a
LIBFT_FLAGS = -L$(LIBFT_DIR) -lft

# =========================
# Fuentes
# =========================
SRC_DIR  = ./src

SRC = main.c \
      $(SRC_DIR)/parser.c

OBJ = $(SRC:.c=.o)

# =========================
# Reglas
# =========================
all: $(LIBFT_A) $(NAME)

$(LIBFT_A):
	@$(MAKE) -C $(LIBFT_DIR)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(INCLUDES) $(MLX_FLAGS) $(LIBFT_FLAGS) -o $(NAME)

# Compilación objetos
%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	@rm -f $(OBJ)
	@$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	@rm -f $(NAME)
	@$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re