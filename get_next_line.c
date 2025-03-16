/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajurczyk <ajurczyk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 20:24:03 by ajurczyk          #+#    #+#             */
/*   Updated: 2025/03/16 17:58:46 by ajurczyk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*ft_strchr(char *str, int c)
{
	unsigned int	i;
	char			temp;

	temp = (char)c;
	i = 0;
	while (str[i])
	{
		if (str[i] == temp)
			return ((char *)&str[i]);
		i++;
	}
	if (str[i] == temp)
		return ((char *)&str[i]);
	return (0);
}

static char	*read_buffer_size_line(int fd, char *buffer_line, char *source)
{
	ssize_t	s_read;
	char	*temp;

	s_read = 1;
	while (s_read > 0)
	{
		s_read = read(fd, source, BUFFER_SIZE);
		if (s_read == -1)
		{
			free(buffer_line);
			return (0);
		}
		else if (s_read == 0)
			break ;
		source[s_read] = 0;
		if (!buffer_line)
			buffer_line = ft_strdup("");
		temp = buffer_line;
		buffer_line = ft_strjoin(temp, source);
		free(temp);
		temp = NULL;
		if (ft_strchr(source, '\n'))
			break ;
	}
	return (buffer_line);
}

static char	*read_line(char *final_line)
{
	char	*buffer_line;
	ssize_t	i;

	i = 0;
	while (final_line[i] != '\n' && final_line[i] != '\0')
		i++;
	if (final_line[i] == 0 || final_line[i + 1] == 0)
		return (0);
	buffer_line = ft_substr(final_line, i + 1, ft_strlen(final_line) - i);
	if (*buffer_line == 0)
	{
		free(buffer_line);
		buffer_line = NULL;
	}
	final_line[i + 1] = 0;
	return (buffer_line);
}

char	*get_next_line(int fd)
{
	char		*final_line;
	char		*source;
	static char	*buffer_line;

	source = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!source)
		return (NULL);
	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
	{
		free(buffer_line);
		free(source);
		buffer_line = NULL;
		source = NULL;
		return (NULL);
	}
	final_line = read_buffer_size_line(fd, buffer_line, source);
	free(source);
	source = NULL;
	if (!final_line)
		return (NULL);
	buffer_line = read_line(final_line);
	return (final_line);
}
