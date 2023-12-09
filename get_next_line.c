/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarbenin <aarbenin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 09:44:22 by aarbenin          #+#    #+#             */
/*   Updated: 2023/12/07 09:44:31 by aarbenin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "get_next_line.h"

char	*merge_remainder(char *remainder, char *buffer)
{
	size_t	rem_len;
	size_t	buf_len;
	char	*new_str;

	rem_len = 0;
	buf_len = ft_strlen(buffer);
	if (remainder)
		rem_len = ft_strlen(remainder);
	new_str = malloc(rem_len + buf_len + 1);
	if (!new_str)
	{
		free(remainder);
		return (NULL);
	}
	if (remainder)
	{
		ft_memcpy(new_str, remainder, rem_len);
		free(remainder);
	}
	ft_memcpy(new_str + rem_len, buffer, buf_len + 1);
	return (new_str);
}

char	*read_to_remainder(int fd, char *remainder)
{
	ssize_t	bytes_read;
	char	buffer[BUFFER_SIZE + 1];
	char	*temp;
	char	*newline;

	bytes_read = read(fd, buffer, BUFFER_SIZE);
	while (bytes_read > 0)
	{
		buffer[bytes_read] = '\0';
		newline = ft_strchr(buffer, '\n');
		temp = merge_remainder(remainder, buffer);
		if (!temp)
			return (NULL);
		remainder = temp;
		if (newline)
			break ;
		bytes_read = read(fd, buffer, BUFFER_SIZE);
	}
	if (bytes_read == -1)
	{
		free(remainder);
		return (NULL);
	}
	return (remainder);
}

char	*extract_line(char *remainder)
{
	size_t	line_len;
	char	*line;
	char	*newline;

	if (!remainder)
		return (NULL);
	newline = ft_strchr(remainder, '\n');
	if (newline)
		line_len = newline - remainder + 1;
	else
		line_len = ft_strlen(remainder);
	line = malloc(line_len + 1);
	if (!line)
		return (NULL);
	ft_memcpy(line, remainder, line_len);
	line[line_len] = '\0';
	return (line);
}

char	*update_remainder(char *remainder)
{
	char	*newline;
	char	*new_remainder;
	size_t	new_len;

	newline = ft_strchr(remainder, '\n');
	if (!newline)
	{
		free(remainder);
		return (NULL);
	}
	new_len = ft_strlen(newline + 1);
	new_remainder = malloc(new_len + 1);
	if (!new_remainder)
	{
		free(remainder);
		return (NULL);
	}
	ft_memcpy(new_remainder, newline + 1, new_len);
	new_remainder[new_len] = '\0';
	free(remainder);
	return (new_remainder);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*remainder;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	remainder = read_to_remainder(fd, remainder);
	if (!remainder || *remainder == '\0')
	{
		free(remainder);
		remainder = NULL;
		return (NULL);
	}
	line = extract_line(remainder);
	if (!line)
	{
		free(remainder);
		remainder = NULL;
		return (NULL);
	}
	remainder = update_remainder(remainder);
	return (line);
}

/*
#include <stdio.h>
#include <fcntl.h>

int	main(void)
{
	int fd = open("test1.txt", O_RDONLY);
	char *line1;

	if (fd == -1)
	{
		printf("Error opening.\n");
		return (1);
	}

	while ((line1 = get_next_line(fd)) != NULL)
	{
		printf("%s", line1);
		free(line1);
	}
	close(fd);

	char *line2;

	printf("\n\nTesting standard input.\n");
	printf("Print something (ctrl + C to quit):\n");

	while ((line2 = get_next_line(STDIN_FILENO)) != NULL)
	{
		printf("%s", line2);
		free(line2);
	}

	return (0);
} */
