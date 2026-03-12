# ======================= CONFIG =========================
NAME    := libft.a
CC      := cc
CFLAGS  := -Wall -Werror -Wextra -fPIE
LDFLAGS := -pie

SRC     := 	ft_atoi_bonus.c \
			ft_bzero_bonus.c \
			ft_calloc_bonus.c \
			ft_isalnum_bonus.c \
			ft_isalpha_bonus.c \
			ft_isascii_bonus.c \
			ft_isdigit_bonus.c \
			ft_isprint_bonus.c \
			ft_itoa_bonus.c \
			ft_memchr_bonus.c \
			ft_memcmp_bonus.c \
			ft_memcpy_bonus.c \
			ft_memmove_bonus.c \
			ft_memset_bonus.c \
			ft_putchar_fd_bonus.c \
			ft_putendl_fd_bonus.c \
			ft_putnbr_fd_bonus.c \
			ft_putstr_fd_bonus.c \
			ft_split_bonus.c \
			ft_strchr_bonus.c \
			ft_strdup_bonus.c \
			ft_striteri_bonus.c \
			ft_strcat_bonus.c \
			ft_strlcat_bonus.c \
			ft_strlcpy_bonus.c \
			ft_strlen_bonus.c \
			ft_strmapi_bonus.c \
			ft_strncmp_bonus.c \
			ft_strnstr_bonus.c \
			ft_strrchr_bonus.c \
			ft_strtrim_bonus.c \
			ft_substr_bonus.c \
			ft_strjoin_bonus.c \
			ft_tolower_bonus.c \
			ft_toupper_bonus.c \
			ft_printf_bonus.c \
			ft_printf_utils_bonus.c \
			ft_printf_utils_2_bonus.c \
			ft_get_next_line_bonus.c \
			ft_sqrt_bonus.c \
			ft_free_split_bonus.c \
			ft_strndup_bonus.c \
			ft_strcmp_bonus.c \
			ft_strcpy_bonus.c

OBJ     := $(SRC:.c=.o)

# ======================= COLORS =========================
GREEN   := \033[1;32m
BLUE    := \033[1;34m
YELLOW  := \033[1;33m
RED     := \033[1;31m
RESET   := \033[0m

# ======================= RULES ==========================

all: $(NAME)
	@echo "$(GREEN)✅ Biblioteca compilada correctamente: $(NAME)$(RESET)"

$(NAME): $(OBJ)
	@echo "$(BLUE)📚 Creando archivo $(NAME)...$(RESET)"
	@ar rcs $(NAME) $(OBJ)

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@rm -f $(OBJ)

fclean: clean
	@echo "$(RED)🔥 Eliminando archivo $(NAME)...$(RESET)"
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
