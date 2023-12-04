#include "get_next_line.h"
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
/*
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
} */
char *merge_remainder(char *remainder, char *buffer) {
    size_t rem_len;
    size_t buff_len;
    size_t i;
    char *result;

	i = 0;
    if (!buffer) 
        return remainder;
	rem_len = 0;
    if (remainder) 
        rem_len = ft_strlen(remainder);
    buff_len = ft_strlen(buffer);
    result = malloc(sizeof(char) * (rem_len + buff_len + 1));
    if (!result) 
	{
        free(remainder); // remove this
        return NULL;
	}
    while (remainder && remainder[i]) 
	{
        result[i] = remainder[i];
        i++;
    }
    while (*buffer) 
        result[i++] = *buffer++;
    result[i] = '\0';
    free(remainder);
    return result;
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
		//if (ft_strchr(remainder, '\n') || !remainder) //introduces KO Segfault
		if (!remainder || ft_strchr(remainder, '\n')) // introduces NULL_CHECK.KO 
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
	new_remainder = ft_strdup(newline + 1); //with strdup everything works perfectly
	free(remainder);
	if (new_remainder && *new_remainder == '\0')
	{
		// If the new_remainder is an empty string, free it and return NULL.
		free(new_remainder);
		return (NULL);
	}
	return (new_remainder);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*remainder;

	line = NULL;
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	remainder = read_to_remainder(fd, remainder);
	// Check if remainder is NULL or empty after read_to_remainder call
	if (!remainder || *remainder == '\0')
	{
		free(remainder);
		remainder = NULL;
		return (NULL); // EOF reached or error in reading
	}
	line = extract_line(remainder);
	remainder = update_remainder(remainder);
	return (line);
}
