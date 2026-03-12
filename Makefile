# =========================
# Proyecto: cub3D
# =========================

NAME = cub3D
BONUS_NAME = cub3D_bonus
CC = cc
CFLAGS = -Wall -Wextra -Werror
INCLUDES = -I./includes

# miniLibX (fuente local)
MLX_DIR = ./minilibx-linux
MLX_A = $(MLX_DIR)/libmlx.a
MLX_FLAGS = -L$(MLX_DIR) -lmlx -lXext -lX11 -lm

# Libft directories and libraries
LIBFT_MANDATORY_DIR = ./mandatory_src/library
LIBFT_BONUS_DIR = ./bonus_src/library
LIBFT_MANDATORY_A = $(LIBFT_MANDATORY_DIR)/libft.a
LIBFT_BONUS_A = $(LIBFT_BONUS_DIR)/libft.a
LIBFT_MANDATORY_FLAGS = -L$(LIBFT_MANDATORY_DIR) -lft
LIBFT_BONUS_FLAGS = -L$(LIBFT_BONUS_DIR) -lft

# =========================
# Directories
# =========================
MANDATORY_DIR = ./mandatory_src
BONUS_DIR = ./bonus_src

# Mandatory directories
M_PARSING_DIR = $(MANDATORY_DIR)/parsing
M_RAYCASTING_DIR = $(MANDATORY_DIR)/raycasting
M_UTILS_DIR = $(MANDATORY_DIR)/utils
M_FREE_DIR = $(MANDATORY_DIR)/free
M_VALIDATE_DIR = $(MANDATORY_DIR)/validate
M_MLXS_DIR = $(MANDATORY_DIR)/mlx
M_PLAYER_DIR = $(MANDATORY_DIR)/player

# Bonus directories
B_PARSING_DIR = $(BONUS_DIR)/parsing
B_RAYCASTING_DIR = $(BONUS_DIR)/raycasting
B_UTILS_DIR = $(BONUS_DIR)/utils
B_FREE_DIR = $(BONUS_DIR)/free
B_VALIDATE_DIR = $(BONUS_DIR)/validate
B_MLXS_DIR = $(BONUS_DIR)/mlx
B_PLAYER_DIR = $(BONUS_DIR)/player
B_SPRITES_DIR = $(BONUS_DIR)/sprites
B_MINIMAP_DIR = $(BONUS_DIR)/minimap
B_CONTROLS_DIR = $(BONUS_DIR)/controls

# =========================
# Mandatory Sources
# =========================
SRC = $(MANDATORY_DIR)/main.c \
	 $(M_PARSING_DIR)/parser.c \
	 $(M_PARSING_DIR)/p_colors.c \
	 $(M_PARSING_DIR)/p_map.c \
	 $(M_PARSING_DIR)/p_textures.c \
	 $(M_RAYCASTING_DIR)/r_drawing.c \
	 $(M_RAYCASTING_DIR)/r_rendering.c \
	 $(M_RAYCASTING_DIR)/r_textures.c \
	 $(M_UTILS_DIR)/u_trim.c \
	 $(M_UTILS_DIR)/u_rendering.c \
	 $(M_UTILS_DIR)/u_maps.c \
	 $(M_UTILS_DIR)/u_blank.c \
	 $(M_UTILS_DIR)/u_dda.c \
	 $(M_UTILS_DIR)/u_parser.c \
	 $(M_FREE_DIR)/f_textures.c \
	 $(M_FREE_DIR)/f_map.c \
	 $(M_FREE_DIR)/f_mlx.c \
	 $(M_FREE_DIR)/f_game.c \
	 $(M_VALIDATE_DIR)/validator.c \
	 $(M_VALIDATE_DIR)/v_map.c \
	 $(M_MLXS_DIR)/m_init.c \
	 $(M_PLAYER_DIR)/p_setting.c \
	 $(M_PLAYER_DIR)/p_interactions.c \
	 $(M_UTILS_DIR)/u_dda_2.c \
	 $(MANDATORY_DIR)/controls/c_hooks.c \
	 $(MANDATORY_DIR)/controls/c_keys.c \
	 $(MANDATORY_DIR)/controls/c_mouse.c \
	 $(MANDATORY_DIR)/controls/c_movement.c

# =========================
# Bonus Sources
# =========================
BONUS_SRC = $(BONUS_DIR)/main_bonus.c \
	 $(B_PARSING_DIR)/parser_bonus.c \
	 $(B_PARSING_DIR)/p_colors_bonus.c \
	 $(B_PARSING_DIR)/p_map_bonus.c \
	 $(B_PARSING_DIR)/p_textures_bonus.c \
	 $(B_RAYCASTING_DIR)/r_drawing_bonus.c \
	 $(B_RAYCASTING_DIR)/r_rendering_bonus.c \
	 $(B_RAYCASTING_DIR)/r_textures_bonus.c \
	 $(B_CONTROLS_DIR)/c_hooks_bonus.c \
	 $(B_CONTROLS_DIR)/c_keys_bonus.c \
	 $(B_CONTROLS_DIR)/c_mouse_bonus.c \
	 $(B_CONTROLS_DIR)/c_movement_bonus.c \
	 $(B_MINIMAP_DIR)/m_arrow_bonus.c \
	 $(B_MINIMAP_DIR)/m_map_drawing_bonus.c \
	 $(B_PLAYER_DIR)/p_interactions_bonus.c \
	 $(B_PLAYER_DIR)/p_setting_bonus.c \
	 $(B_UTILS_DIR)/u_trim_bonus.c \
	 $(B_UTILS_DIR)/u_rendering_bonus.c \
	 $(B_UTILS_DIR)/u_minimap_bonus.c \
	 $(B_UTILS_DIR)/u_sprites_bonus.c \
	 $(B_UTILS_DIR)/u_maps_bonus.c \
	 $(B_UTILS_DIR)/u_blank_bonus.c \
	 $(B_UTILS_DIR)/u_dda_bonus.c \
	 $(B_UTILS_DIR)/u_dda_2_bonus.c \
	 $(B_UTILS_DIR)/u_parser_bonus.c \
	 $(B_UTILS_DIR)/u_arrow_bonus.c \
	 $(B_SPRITES_DIR)/s_rendering_bonus.c \
	 $(B_SPRITES_DIR)/s_rendering_2_bonus.c \
	 $(B_FREE_DIR)/f_textures_bonus.c \
	 $(B_FREE_DIR)/f_map_bonus.c \
	 $(B_FREE_DIR)/f_mlx_bonus.c \
	 $(B_FREE_DIR)/f_game_bonus.c \
	 $(B_VALIDATE_DIR)/validator_bonus.c \
	 $(B_VALIDATE_DIR)/v_map_bonus.c \
	 $(B_MLXS_DIR)/m_init_bonus.c

OBJ = $(SRC:.c=.o)
BONUS_OBJ = $(BONUS_SRC:.c=.o)

# =========================
# Rules
# =========================
all: $(LIBFT_MANDATORY_A) $(MLX_A) $(NAME)

bonus: $(LIBFT_BONUS_A) $(MLX_A) $(BONUS_NAME)

$(LIBFT_MANDATORY_A):
	 @$(MAKE) -C $(LIBFT_MANDATORY_DIR)

$(LIBFT_BONUS_A):
	 @$(MAKE) -C $(LIBFT_BONUS_DIR)

$(MLX_A):
	 @$(MAKE) -C $(MLX_DIR)

$(NAME): $(OBJ)
	 $(CC) $(CFLAGS) $(OBJ) $(INCLUDES) $(MLX_FLAGS) $(LIBFT_MANDATORY_FLAGS) -o $(NAME)

$(BONUS_NAME): $(BONUS_OBJ)
	 $(CC) $(CFLAGS) $(BONUS_OBJ) $(INCLUDES) $(MLX_FLAGS) $(LIBFT_BONUS_FLAGS) -o $(BONUS_NAME)

%.o: %.c
	 $(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	 @rm -f $(OBJ) $(BONUS_OBJ)

fclean: clean
	 @rm -f $(NAME) $(BONUS_NAME)
	 @$(MAKE) -C $(LIBFT_MANDATORY_DIR) fclean
	 @$(MAKE) -C $(LIBFT_BONUS_DIR) fclean

re: fclean all

.PHONY: all bonus clean fclean re