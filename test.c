#include "get_next_line.h"
#include "get_next_line.h"
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>

size_t	ft_strlen(char *s)
{
	size_t	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i] != '\0')
		i++;
	return (i);
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

char	*ft_strjoin(char *remainder, char *buffer) 
{
	size_t	rem_len;
	size_t	buff_len;
	char	*result;
	char	*result_ptr;

	if (!remainder)
		rem_len = 0;
	else
		rem_len = ft_strlen(remainder);
	if (!buffer)
		return (NULL);
	buff_len = ft_strlen(buffer);
	result = malloc(sizeof(char) * (rem_len + buff_len + 1));
	if (!result)
		return (NULL);
	result_ptr = result;
	while (remainder && *remainder)
		*result++ = *remainder++;
	while (*buffer)
		*result++ = *buffer++;	
	*result = '\0';
	free(remainder - rem_len);
	return (result_ptr);
}

char	*extract_line(char *remainder)
{
	int		i;
	char	*str;

	i = 0;
	if (!remainder[i])
		return (NULL);
	while (remainder[i] && remainder[i] != '\n')
		i++;
	str = (char *)malloc(sizeof(char) * (i + 2));
	if (!str)
		return (NULL);
	i = 0;
	while (remainder[i] && remainder[i] != '\n')
	{
		str[i] = remainder[i];
		i++;
	}
	if (remainder[i] == '\n')
	{
		str[i] = remainder[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

char	*ft_new_remainder(char *remainder) //old remainder with line extracted
{
	int		i;
	int		j;
	char	*str;

	i = 0;
	while (remainder[i] && remainder[i] != '\n')
		i++;
	if (!remainder[i])
	{
		free(remainder);
		return (NULL);
	}
	str = (char *)malloc(sizeof(char) * (ft_strlen(remainder) - i + 1));
	if (!str)
		return (NULL);
	i++;
	j = 0;
	while (remainder[i])
		str[j++] = remainder[i++];
	str[j] = '\0';
	free(remainder);
	return (str);
}
char	*ft_read_to_remainder(int fd, char *remainder)
{
	char	*buff;
	int		rd_bytes;

	buff = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buff)
		return (NULL);
	rd_bytes = 1;
	while (!ft_strchr(remainder, '\n') && rd_bytes != 0)
	{
		rd_bytes = read(fd, buff, BUFFER_SIZE);
		if (rd_bytes == -1)
		{
			free(buff);
			return (NULL);
		}
		buff[rd_bytes] = '\0';
		remainder = ft_strjoin(remainder, buff);
	}
	free(buff);
	return (remainder);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*remainder;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (0);
	remainder = ft_read_to_remainder(fd, remainder);
	if (!remainder)
		return (NULL);
	line = extract_line(remainder);
	remainder = ft_new_remainder
(remainder);
	return (line);
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