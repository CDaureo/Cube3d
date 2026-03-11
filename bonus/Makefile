# =========================
# Proyecto: cub3D (simple)
# =========================

NAME	= cub3D_bonus
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

SRC = $(SRC_DIR)/main_bonus.c \
	$(PARSING_DIR)/parser_bonus.c \
	$(PARSING_DIR)/p_colors_bonus.c \
	$(PARSING_DIR)/p_map_bonus.c \
	$(PARSING_DIR)/p_textures_bonus.c \
	$(RAYCASTING_DIR)/r_drawing_bonus.c \
	$(RAYCASTING_DIR)/r_rendering_bonus.c \
	$(RAYCASTING_DIR)/r_textures_bonus.c \
	$(CONTROLS_DIR)/c_hooks_bonus.c \
	$(CONTROLS_DIR)/c_keys_bonus.c \
	$(CONTROLS_DIR)/c_mouse_bonus.c \
	$(CONTROLS_DIR)/c_movement_bonus.c \
	$(MINIMAP_DIR)/m_arrow_bonus.c \
	$(MINIMAP_DIR)/m_map_drawing_bonus.c \
	$(PLAYER_DIR)/p_interactions_bonus.c \
	$(PLAYER_DIR)/p_setting_bonus.c \
	$(UTILS_DIR)/u_trim_bonus.c \
	$(UTILS_DIR)/u_rendering_bonus.c \
	$(UTILS_DIR)/u_minimap_bonus.c \
	$(UTILS_DIR)/u_sprites_bonus.c \
	$(UTILS_DIR)/u_maps_bonus.c \
	$(UTILS_DIR)/u_blank_bonus.c \
	$(UTILS_DIR)/u_dda_bonus.c \
	$(UTILS_DIR)/u_dda_2_bonus.c \
	$(UTILS_DIR)/u_parser_bonus.c \
	$(UTILS_DIR)/u_arrow_bonus.c \
	$(SPRITES_DIR)/s_rendering_bonus.c \
	$(SPRITES_DIR)/s_rendering_2_bonus.c \
	$(FREE_DIR)/f_textures_bonus.c \
	$(FREE_DIR)/f_map_bonus.c \
	$(FREE_DIR)/f_mlx_bonus.c \
	$(FREE_DIR)/f_game_bonus.c \
	$(VALIDATE_DIR)/validator_bonus.c \
	$(VALIDATE_DIR)/v_map_bonus.c \
	$(MLXS_DIR)/m_init_bonus.c


OBJ = $(SRC:_bonus.c=.o)

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
%.o: %_bonus.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	@rm -f $(OBJ)

fclean:
	@rm -f $(OBJ) $(NAME)
	@$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re