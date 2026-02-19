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
RAYCASTING_DIR = $(SRC_DIR)/raycasting
UTILS_DIR = $(SRC_DIR)/utils
FREE_DIR = $(SRC_DIR)/free
VALIDATE_DIR = $(SRC_DIR)/validate
MLXS_DIR = $(SRC_DIR)/mlx
PLAYER_DIR = $(SRC_DIR)/player
SPRITES_DIR = $(SRC_DIR)/sprites
MINIMAP_DIR = $(SRC_DIR)/minimap
CONTROLS_DIR = $(SRC_DIR)/controls

SRC = $(SRC_DIR)/main.c \
	$(PARSING_DIR)/parser.c \
	$(PARSING_DIR)/p_colors.c \
	$(PARSING_DIR)/p_map.c \
	$(PARSING_DIR)/p_textures.c \
	$(RAYCASTING_DIR)/r_drawing.c \
	$(RAYCASTING_DIR)/r_rendering.c \
	$(RAYCASTING_DIR)/r_textures.c \
	$(CONTROLS_DIR)/c_hooks.c \
	$(CONTROLS_DIR)/c_keys.c \
	$(CONTROLS_DIR)/c_mouse.c \
	$(CONTROLS_DIR)/c_movement.c \
	$(MINIMAP_DIR)/m_arrow.c \
	$(MINIMAP_DIR)/m_map_drawing.c \
	$(PLAYER_DIR)/p_interactions.c \
	$(PLAYER_DIR)/p_setting.c \
	$(UTILS_DIR)/u_trim.c \
	$(UTILS_DIR)/u_rendering.c \
	$(UTILS_DIR)/u_minimap.c \
	$(UTILS_DIR)/u_sprites.c \
	$(UTILS_DIR)/u_maps.c \
	$(UTILS_DIR)/u_blank.c \
	$(UTILS_DIR)/u_dda.c \
	$(UTILS_DIR)/u_dda_2.c \
	$(UTILS_DIR)/u_arrow.c \
	$(SPRITES_DIR)/s_rendering.c \
	$(SPRITES_DIR)/s_rendering_2.c \
	$(FREE_DIR)/f_textures.c \
	$(FREE_DIR)/f_map.c \
	$(FREE_DIR)/f_mlx.c \
	$(FREE_DIR)/f_game.c \
	$(VALIDATE_DIR)/validator.c \
	$(VALIDATE_DIR)/v_map.c \
	$(MLXS_DIR)/m_init.c


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