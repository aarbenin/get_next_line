#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>



char	*merge_remainder(char *remainder, char *buffer)
{
	char	*result;

	if (!buffer)
	{
		return (remainder);
	}
	size_t rem_len, buff_len;
	// Calculate lengths
	if (remainder)
	{
		rem_len = strlen(remainder);
	}
	else
	{
		rem_len = 0;
	}
	buff_len = strlen(buffer);
	// Dynamic buffer growth strategy
	size_t new_size = rem_len + buff_len + 1; // +1 for null terminator
	result = realloc(remainder, new_size);
	if (!result)
	{
		free(remainder);
		return (NULL);
	}
	// Copy the buffer content
	strcpy(result + rem_len, buffer);
	return (result);
}

char	*read_to_remainder(int fd, char *remainder)
{
	ssize_t	bytes_read;

	char buffer[BUFFER_SIZE + 1]; // +1 for null terminator
	while ((bytes_read = read(fd, buffer, BUFFER_SIZE)) > 0)
	{
		buffer[bytes_read] = '\0'; // Null-terminate the buffer
		remainder = merge_remainder(remainder, buffer);
		if (!remainder)
		{
			// If merge_remainder fails (e.g., due to memory allocation error)
			return (NULL);
		}
		// Break if a newline is found in the new remainder
		if (strchr(buffer, '\n'))
			break ;
	}
	if (bytes_read < 0)
	{
		// Handle read error
		free(remainder);
		return (NULL);
	}
	return (remainder);
		// Return the final remainder (could be NULL if EOF reached)
}

char	*extract_line(char *remainder)
{
	size_t	line_len;
	size_t	i;
	char	*newline;
	char	*line;

	if (!remainder)
		return (NULL);
	newline = ft_strchr(remainder, '\n');
	line_len = ft_strlen(remainder);
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

char	*get_next_line(int fd)
{
	static char	*remainder = NULL;
	char		*line;

	line = NULL;
	if (fd < 0 || BUFFER_SIZE <= 0)
	{
		return (NULL);
	}
	remainder = read_to_remainder(fd, remainder);
	// Check if remainder is NULL or empty after read_to_remainder call
	if (!remainder || *remainder == '\0')
	{
		free(remainder);
		remainder = NULL;
		return NULL; // EOF reached or error in reading
	}
	line = extract_line(remainder);
	remainder = update_remainder(remainder);
	return line;
}

//__________________TEST_____________________//
/*
int	main(void)
{
	char	*line;
	int		i;
	int		fd1;

	fd1 = open("test2.txt", O_RDONLY);
	i = 1;
	while (i < 7)
	{
		line = get_next_line(fd1);
		printf("line %02d: %s", i, line);
		free(line);
		i++;
	}
	close(fd1);
	return (0);
}
*/