/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_next_line.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdaureo- <cdaureo-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 14:00:16 by simgarci          #+#    #+#             */
/*   Updated: 2025/09/11 17:11:15 by cdaureo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 1
#endif
#include "../../includes/libft.h"

static	int	find_newline(char *buffer)
{
	int	i;

	i = 0;
	while (buffer[i])
	{
		if (buffer[i] == '\n')
			return (i);
		i++;
	}
	return (-1);
}

static	char	*extract_line(char **static_buffer)
{
	int		newline_index;
	char	*line;
	char	*remaining;

	if (!*static_buffer || !**static_buffer)
	{
		free(*static_buffer);
		*static_buffer = NULL;
		return (NULL);
	}
	newline_index = find_newline(*static_buffer);
	if (newline_index == -1)
	{
		line = ft_strdup(*static_buffer);
		free(*static_buffer);
		*static_buffer = NULL;
		return (line);
	}
	line = ft_substr(*static_buffer, 0, newline_index + 1);
	remaining = ft_strdup(*static_buffer + newline_index + 1);
	free(*static_buffer);
	*static_buffer = remaining;
	return (line);
}

static	int	read_and_store(int fd, char **static_buffer)
{
	char	*buffer;
	int		nbytes;
	char	*temp;

	buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (-1);
	while (find_newline(*static_buffer) == -1)
	{
		nbytes = read(fd, buffer, BUFFER_SIZE);
		if (nbytes < 0)
			return (free(buffer), buffer = NULL, -1);
		else if (nbytes == 0)
			break ;
		buffer[nbytes] = '\0';
		temp = ft_strjoin(*static_buffer, buffer);
		if (!temp)
			return (free(buffer), free(*static_buffer), -1);
		free(*static_buffer);
		*static_buffer = temp;
	}
	free(buffer);
	return (1);
}

char	*get_next_line(int fd)
{
	static char	*static_buffer = NULL;
	char		*line;
	int			read_result;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (free(static_buffer), static_buffer = NULL, NULL);
	if (!static_buffer)
		static_buffer = ft_strdup("");
	if (!static_buffer)
		return (NULL);
	read_result = read_and_store(fd, &static_buffer);
	if (read_result == -1)
		return (free(static_buffer), static_buffer = NULL, NULL);
	line = extract_line(&static_buffer);
	if (line)
		return (line);
	if (read_result == 0 && static_buffer && *static_buffer != '\0')
	{
		line = ft_strdup(static_buffer);
		free(static_buffer);
		static_buffer = NULL;
		return (line);
	}
	return (free(static_buffer), static_buffer = NULL, NULL);
}

//int	main(void)
//{
//	int fd = open("test", O_RDONLY);
//	char *result;
//	while ((result = get_next_line(fd)) != NULL)
//	{
//		printf("%s", result);
//		free(result);
//	}
//	close(fd);
//	return (0);
//}