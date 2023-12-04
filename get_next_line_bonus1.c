#include "get_next_line_bonus.h"


char	*merge_remainder(char *remainder, char *buffer)
{
	size_t	rem_len;
	size_t	buff_len;
	size_t	i;
	char	*result;

	i = 0;
	if (!buffer)
		return (NULL);
	rem_len = 0;
	if (remainder)
		rem_len = ft_strlen(remainder);
	buff_len = ft_strlen(buffer);
	result = malloc(sizeof(char) * (rem_len + buff_len + 1));
	if (!result)
		return (NULL);
	while (remainder && remainder[i])
	{
		result[i] = remainder[i];
		i++;
	}
	while (*buffer)
		result[i++] = *buffer++;
	result[i] = '\0';
	free(remainder);
	return (result);
}

char	*read_to_remainder(int fd, char *remainder)
{
	ssize_t	bytes_read;
	char	*buffer;

	buffer = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buffer)
		return (NULL);
	bytes_read = read(fd, buffer, BUFFER_SIZE);
	while (bytes_read > 0)
	{
		buffer[bytes_read] = '\0';
		remainder = merge_remainder(remainder, buffer);
		if (ft_strchr(remainder, '\n') || !remainder)
			break ;
		bytes_read = read(fd, buffer, BUFFER_SIZE);
	}
	free(buffer);
	if (bytes_read == -1)
	{
		free(remainder);
		return (NULL);
	}
	return (remainder);
}

char	*extract_line(char *remainder)
{
	size_t	i;
	size_t	line_len;
	char	*line;
	char	*newline;

	i = 0;
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
	i = 0; // maybe replace with ft_strncpy
	while (i < line_len)
	{
		line[i] = remainder[i];
		i++;
	}
	line[i] = '\0';
	return (line);
}

char	*update_remainder(char *remainder)
{
	char	*newline;
	char	*new_remainder;

	if (!remainder)
		return (NULL);
	newline = ft_strchr(remainder, '\n');
	if (!newline)
	{
		free(remainder);
		return (NULL);
	}
	new_remainder = ft_strdup(newline + 1);
	free(remainder);
	if (new_remainder && *new_remainder == '\0')
	{
		// If the new_remainder is an empty string, free it and return NULL.
		free(new_remainder);
		return (NULL);
	}
	return (new_remainder);
}

#include "get_next_line_bonus.h"

t_fd_list	*find_or_create_fd_node(t_fd_list **head, int fd);
void		delete_fd_node(t_fd_list **head, int fd);

char	*get_next_line(int fd)
{
	static t_fd_list	*fd_list = NULL;
	t_fd_list			*current_node;
	char				*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return NULL;
	current_node = find_or_create_fd_node(&fd_list, fd);
	if (!current_node)
		return NULL;
	current_node->remainder = read_to_remainder(fd, current_node->remainder);
	if (!current_node->remainder)
	{
		delete_fd_node(&fd_list, fd);
		return NULL;
	}
	line = extract_line(current_node->remainder);
	current_node->remainder = update_remainder(current_node->remainder);
	if (!current_node->remainder)
		delete_fd_node(&fd_list, fd);
	return line;
}
