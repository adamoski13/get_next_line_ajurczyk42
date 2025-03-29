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
#include <stdio.h>

char	*read_buffer_size_line(int fd, char *buffer_line, char *source)
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

char	*remember(char *final_line)
{
	char	*buffer_line;
	ssize_t	i;

	i = 0;
	while (final_line[i] != '\n' && final_line[i] != '\0')
		i++;
	if (final_line[i] == 0)
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
	buffer_line = remember(final_line);
	return (final_line);
}

int	main(void)
{
	int	fd;

	printf("\nTest 1\n");
	printf("Value instead fd:\n");
	printf("%s\n", get_next_line(1000)); // should be null
	printf("%s\n", get_next_line(-1));	// should be null
	printf("\n");

	printf("Test 2\n");
	printf("Empty file:\n");
	fd = open("files/empty", O_RDWR);
	printf("%s\n", get_next_line(fd)); // should be null
	close(fd);
	printf("\n");

	printf("Test 3\n");
	printf("File with just new line:\n");
	fd = open("files/nl", O_RDWR);
	printf("%s", get_next_line(fd)); // should be new line
	printf("%s\n", get_next_line(fd)); // should be null
	close(fd);
	printf("\n");

	printf("Test 4\n");
	printf("File with only string:\n");
	fd = open("files/41_no_nl", O_RDWR);
	printf("%s\n", get_next_line(fd)); // should be string
	printf("%s\n", get_next_line(fd)); // should be null
	close(fd);
	printf("\n");

	printf("Test 5\n");
	printf("File with string with new line and one char:\n");
	fd = open("files/41_with_nl", O_RDWR);
	printf("%s", get_next_line(fd)); // should be string with new line
	printf("%s\n", get_next_line(fd)); // should be one char
	printf("%s\n", get_next_line(fd)); // should be null
	close(fd);
	printf("\n");

	printf("Test 6\n");
	printf("File with only string:\n");
	fd = open("files/42_no_nl", O_RDWR);
	printf("%s\n", get_next_line(fd)); // should be string
	printf("%s\n", get_next_line(fd)); // should be null
	close(fd);
	printf("\n");

	printf("Test 7\n");
	printf("File with string with new line and one char:\n");
	fd = open("files/42_with_nl", O_RDWR);
	printf("%s", get_next_line(fd)); // should be string with new line
	printf("%s\n", get_next_line(fd)); // should be one char
	printf("%s\n", get_next_line(fd)); // should be null
	close(fd);
	printf("\n");

	printf("Test 8\n");
	printf("File with only string:\n");
	fd = open("files/43_no_nl", O_RDWR);
	printf("%s\n", get_next_line(fd)); // should be string
	printf("%s\n", get_next_line(fd)); // should be null
	close(fd);
	printf("\n");

	printf("Test 9\n");
	printf("File with string with new line and one char:\n");
	fd = open("files/43_with_nl", O_RDWR);
	printf("%s", get_next_line(fd)); // should be string with new line
	printf("%s\n", get_next_line(fd)); // should be one char
	printf("%s\n", get_next_line(fd)); // should be null
	close(fd);
	printf("\n");

	printf("Test 10\n");
	printf("File with multiple new lines (5):\n");
	fd = open("files/multiple_nlx5", O_RDWR);
	printf("%s", get_next_line(fd)); // should be new line
	printf("%s", get_next_line(fd)); // should be new line
	printf("%s", get_next_line(fd)); // should be new line
	printf("%s", get_next_line(fd)); // should be new line
	printf("%s", get_next_line(fd)); // should be new line
	printf("%s\n", get_next_line(fd)); // should be null
	close(fd);
	printf("\n");

	printf("Test 11\n");
	printf("File with 5 lines -> string with new line, string with new line, string with new line, string with new line, string:\n");
	fd = open("files/multiple_line_no_nl", O_RDWR);
	printf("%s", get_next_line(fd)); // should be string with new line
	printf("%s", get_next_line(fd)); // should be string with new line
	printf("%s", get_next_line(fd)); // should be string with new line
	printf("%s", get_next_line(fd)); // should be string with new line
	printf("%s\n", get_next_line(fd)); // should be string
	printf("%s\n", get_next_line(fd)); // should be null
	close(fd);
	printf("\n");

	printf("Test 12\n");
	printf("File with 6 lines -> string with new line, string with new line, string with new line, string with new line, string with new line:\n");
	fd = open("files/multiple_line_with_nl", O_RDWR);
	printf("%s", get_next_line(fd)); // should be string with new line
	printf("%s", get_next_line(fd)); // should be string with new line
	printf("%s", get_next_line(fd)); // should be string with new line
	printf("%s", get_next_line(fd)); // should be string with new line
	printf("%s", get_next_line(fd)); // should be string with new line
	printf("%s\n", get_next_line(fd)); // should be null
	close(fd);
	printf("\n");

	printf("Test 13\n");
	printf("File with strings with new line and new line after them, but no new line at the end:\n");
	fd = open("files/alternate_line_nl_no_nl", O_RDWR);
	printf("%s", get_next_line(fd)); // should be string with new line
	printf("%s", get_next_line(fd)); // should be new line
	printf("%s", get_next_line(fd)); // should be string with new line
	printf("%s", get_next_line(fd)); // should be new line
	printf("%s", get_next_line(fd)); // should be string with new line
	printf("%s", get_next_line(fd)); // should be new line
	printf("%s", get_next_line(fd)); // should be string with new line
	printf("%s", get_next_line(fd)); // should be new line
	printf("%s\n", get_next_line(fd)); // should be string
	printf("%s\n", get_next_line(fd)); // should be null
	close(fd);
	printf("\n");

	printf("Test 14\n");
	printf("File with strings with new line and new line after them:\n");
	fd = open("files/alternate_line_nl_with_nl", O_RDWR);
	printf("%s", get_next_line(fd)); // should be string with new line
	printf("%s", get_next_line(fd)); // should be new line
	printf("%s", get_next_line(fd)); // should be string with new line
	printf("%s", get_next_line(fd)); // should be new line
	printf("%s", get_next_line(fd)); // should be string with new line
	printf("%s", get_next_line(fd)); // should be new line
	printf("%s", get_next_line(fd)); // should be string with new line
	printf("%s", get_next_line(fd)); // should be new line
	printf("%s", get_next_line(fd)); // should be string with new line
	printf("%s\n", get_next_line(fd)); // should be null
	close(fd);
	printf("\n");

	printf("Test 15\n");
	printf("File with long long long string:\n");
	fd = open("files/big_line_no_nl", O_RDWR);
	printf("%s\n", get_next_line(fd)); // should be long long long string
	printf("%s\n", get_next_line(fd)); // should be null
	close(fd);
	printf("\n");

	printf("Test 16\n");
	printf("File with long long long string with new line:\n");
	fd = open("files/big_line_with_nl", O_RDWR);
	printf("%s", get_next_line(fd)); // should be long long long string with new line
	printf("%s\n", get_next_line(fd)); // should be null
	close(fd);
	printf("\n");

	return (0);
}
