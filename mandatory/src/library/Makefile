# ======================= CONFIG =========================
NAME    := libft.a
CC      := cc
CFLAGS  := -Wall -Werror -Wextra -fPIE
LDFLAGS := -pie

SRC     := 	ft_atoi.c \
			ft_bzero.c \
			ft_calloc.c \
			ft_isalnum.c \
			ft_isalpha.c \
			ft_isascii.c \
			ft_isdigit.c \
			ft_isprint.c \
			ft_itoa.c \
			ft_memchr.c \
			ft_memcmp.c \
			ft_memcpy.c \
			ft_memmove.c \
			ft_memset.c \
			ft_putchar_fd.c \
			ft_putendl_fd.c \
			ft_putnbr_fd.c \
			ft_putstr_fd.c \
			ft_split.c \
			ft_strchr.c \
			ft_strdup.c \
			ft_striteri.c \
			ft_strcat.c \
			ft_strlcat.c \
			ft_strlcpy.c \
			ft_strlen.c \
			ft_strmapi.c \
			ft_strncmp.c \
			ft_strnstr.c \
			ft_strrchr.c \
			ft_strtrim.c \
			ft_substr.c \
			ft_strjoin.c \
			ft_tolower.c \
			ft_toupper.c \
			ft_printf.c \
			ft_printf_utils.c \
			ft_printf_utils_2.c \
			ft_get_next_line.c \
			ft_sqrt.c \
			ft_free_split.c \
			ft_strndup.c \
			ft_strcmp.c \
			ft_strcpy.c

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
