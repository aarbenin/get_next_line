/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarbenin <aarbenin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 09:45:58 by aarbenin          #+#    #+#             */
/*   Updated: 2023/12/07 09:46:03 by aarbenin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "get_next_line_bonus.h"

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
	static t_fd_list	*fd_list;
	t_fd_list			*current_fd;
	char				*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	current_fd = get_fd_node(fd, &fd_list);
	if (!current_fd)
		return (NULL);
	current_fd->remainder = read_to_remainder(fd, current_fd->remainder);
	if (!current_fd->remainder || *current_fd->remainder == '\0')
	{
		remove_fd_node(fd, &fd_list);
		return (NULL);
	}
	line = extract_line(current_fd->remainder);
	if (!line)
	{
		remove_fd_node(fd, &fd_list);
		return (NULL);
	}
	current_fd->remainder = update_remainder(current_fd->remainder);
	return (line);
}
