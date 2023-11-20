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

char	*join_and_free(char *remainder, char *buffer) //takes old remainder and free it
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

char	*join2(char *remainder, char *buffer)
{
	char	*joined_str;
	size_t	rem_len;
	size_t	buff_len;

	
	rem_len = ft_strlen(remainder);
	buff_len = ft_strlen(buffer);
	joined_str = (char *)malloc(sizeof(char) * (rem_len + buff_len + 1));
	if (!joined_str)
		return (NULL);
	

	
}

char	read_to_remainder(int fd, char *remainder)
{
	char	*buffer;
	ssize_t	bytes_read;

	if (ft_strchr(remainder, '\n'))
		return (remainder);
	buffer = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (NULL);
	bytes_read = 1;
	while (bytes_read != 0 && !ft_strchr('/n', remainder))
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read = -1)
			return (NULL);
		buffer[bytes_read] = '\0';
		remainder = join_and_free(remainder, buffer);
		if (!remainder)
		{
			free(buffer);
			return (NULL);
		}
		free(buffer);
		return(remainder);
	}
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

	/*i = 1;
	while (i < 7)
	{
		line = get_next_line(fd1);
		printf("line %d:	%s", i, line);
		free(line);
		
		i++;
	}*/

	line = get_next_line(fd1);
	close(fd1);
	
	return (0);
}