/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdaureo- <cdaureo-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 12:12:20 by simgarci          #+#    #+#             */
/*   Updated: 2026/01/19 13:46:12 by cdaureo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H
# include <limits.h>
# include <stddef.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdarg.h>
# include <fcntl.h>

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
	struct s_list	*former;
}					t_list;

int		ft_atoi(char const *nptr);
void	ft_bzero(void *s, int n);
void	*ft_calloc(size_t nmemb, size_t size);
int		ft_isalnum(int i);
int		ft_isalpha(int i);
int		ft_isascii(int i);
int		ft_isdigit(int i);
int		ft_isprint(int i);
char	*ft_itoa(int n);
void	*ft_memchr(const void *s, int c, size_t n);
int		ft_memcmp(const void *s1, const void *s2, size_t n);
void	*ft_memcpy(void *dest, const void *src, size_t n);
void	*ft_memmove(void *dest, const void *src, size_t n);
void	*ft_memset(void *str, int c, int n);
void	ft_putchar_fd(char c, int fd);
void	ft_putendl_fd(char *s, int fd);
void	ft_putnbr_fd(int n, int fd);
void	ft_putstr_fd(char *s, int fd);
char	**ft_split(char const *s, char c);
char	*ft_strchr(const char *s, int c);
char	*ft_strdup(const char *s);
void	ft_striteri(char *s, void (*f)(unsigned int, char*));
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strcat(char *dst, const char *src);
size_t	ft_strlcat(char *dst, const char *src, size_t size);
size_t	ft_strlcpy(char *dst, const char *src, size_t size);
size_t	ft_strlen(const char *str);
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strnstr(const char *big, const char *little, size_t len);
char	*ft_strrchr(const char *s, int c);
char	*ft_strtrim(char const *s1, char const *set);
char	*ft_substr(char const *s, unsigned int start, size_t len);
int		ft_tolower(int c);
int		ft_toupper(int c);
void	*ft_calloc(size_t nmemb, size_t size);
void	handle_char_or_ints(int c, char *format, int *count);
void	handle_string(char *str, int *count);
void	handle_pointer(void *ptr, int *count);
void	handle_unsigned(unsigned int u, char *format, int *count);
void	ft_putnbr_base(unsigned long nbr, char *base);
int		ft_numlen_base(unsigned long num, int base);
int		ft_printf(char const *format, ...);
void	ft_putnbr_u_fd(unsigned int n, int fd);
char	*get_next_line(int fd);
int		check_base(char *base);
void	check_exception(int nbr, char *base, int div);
void	ft_free_split(char **split);
void	ft_lstclear(t_list **head, void (*del)(void*));
void	ft_lstdelone(t_list *head, void (*del)(void*));
void	ft_lstiter(t_list *head, void (*f)(void *));
t_list	*ft_lstlast(t_list *head);
t_list	*ft_lstmap(t_list *head, void *(*f)(void *), void (*del)(void *));
t_list	*ft_lstnew(void *content);
int		ft_lstsize(t_list *head);
int		ft_sqrt(int number);
char	*ft_strndup(const char *s, size_t n);
int		ft_strcmp(const char *s1, const char *s2);
char	*ft_strcpy(char *dst, const char *src);

#endif