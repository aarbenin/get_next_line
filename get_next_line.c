#include "get_next_line.h"
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include "get_next_line.h"

size_t	ft_strlen(const char *str)
{
	size_t	len;

	len = 0;
	while (str[len])
		len++;
	return (len);
}

char	*ft_strchr(char *s, int c)
{
	int	i;

	i = 0;
	if (!s)
		return (0);
	if (c == '\0')
		return ((char *)&s[ft_strlen(s)]);
	while (s[i] != '\0')
	{
		if (s[i] == (char) c)
			return ((char *)&s[i]);
		i++;
	}
	return (0);
}

char	*join_and_free(char *remainder, char *buffer)
{
	size_t i = 0;
    size_t j = 0;
    size_t remainder_len;
    size_t buffer_len;
    char *str;

    if (remainder)
        remainder_len = ft_strlen(remainder);
    else
        remainder_len = 0;
    buffer_len = ft_strlen(buffer);
    if (!buffer)
        return (NULL);
    str = malloc(sizeof(char) * (remainder_len + buffer_len + 1));
    if (str == NULL)
        return (NULL);
    while (remainder && remainder[i] != '\0') 
	{
        str[i] = remainder[i];
        i++;
    }
    while (buffer[j] != '\0') 
        str[i++] = buffer[j++];
    str[i] = '\0';
    free(remainder);
    return str;
}

char	*merge_remainder(char *remainder, char *buffer)
{
	char	*result;
	size_t	rem_len;
	size_t	buff_len;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (!remainder)
		rem_len = 0;
	else
		rem_len = ft_strlen(remainder);
	if (!buffer)
		return (NULL);
	buff_len = ft_strlen(buffer);
	result = (char *)malloc(sizeof(char) * (rem_len + buff_len + 1));
	if (!result)
		return (NULL);
	result_ptr = result;
	while (remainder && remainder[i++])
		result[i] = reminder[i];
	while ( buffer[j])
	{
		result[i++] = buffer[j++]
	}
	result[i] = '\0';
	free(remainder);
	return (result_ptr);
}

char	*read_to_remainder(int fd, char *remainder)
{
	char	*buffer;
	ssize_t	bytes_read;

	if (ft_strchr(remainder, '\n'))
		return (remainder);
	buffer = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (NULL);
	bytes_read = 1;
	while (!ft_strchr(remainder, '\n') && bytes_read != 0)

	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read == -1)
			return (NULL);
		buffer[bytes_read] = '\0';
		remainder = merge_remainder(remainder, buffer);
		if (!remainder)
		{
			free(buffer);
			return (NULL);
		}
	}
	free(buffer);
	return(remainder);
}







char	*get_next_line(int fd)
{
	static char	*remainder;
	char		*line;
	remainder = read_to_remainder(fd, remainder);
	

	return (remainder);
}





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