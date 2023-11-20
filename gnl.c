#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include "get_next_line.h"


size_t	ft_strlen(const char *str)
{
	size_t	len;

	len = 0;
	while (str[len])
		len++;
	return (len);
}
int	find_new_line(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\n')
			return (i);
		i++;
	}
	return (-1);
}
char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*str;
	char	*str_ptr;
	int		len_s1;
	int		len_s2;

	len_s1 = 0;
	len_s2 = 0;
	if (s1 != NULL)
		len_s1 = ft_strlen(s1);
	if (s2 != NULL)
		len_s2 = ft_strlen(s2);
	str = (char *)malloc(sizeof(char) * (len_s1 + len_s2 + 1));
	if (str == NULL)
		return (NULL);
	str_ptr = str;
	while (s1 && *s1)
	{
		*str++ = *s1++;
	}
	while (s2 && *s2)
	{
		*str++ = *s2++;
	}
	*str = '\0';
	return (str_ptr);
}
char	*ft_strdup(const char *str)
{
	size_t	len;
	size_t	i;
	char	*dup;

	len = ft_strlen(str);
	i = 0;
	dup = (char *)malloc(len + 1);
	if (!dup)
		return (NULL);
	while (i < len)
	{
		dup[i] = str[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}

char	*get_next_line(int fd)
{
	char		*buffer;
	char		*line;
	char		*temp;
	static char	*remainder;
	ssize_t		bytes_read;
	int			line_index;

	if (fd < 0 || BUFF_SIZE <= 0)
		return (NULL);
	buffer = (char *)malloc(BUFF_SIZE + 1);
	if (!buffer)
		return (NULL);
	line = NULL;
	while (1)
	{
		bytes_read = read(fd, buffer, BUFF_SIZE);
		if (bytes_read < 0)
		{
			free(buffer);
			return (NULL);
		}
		if(bytes_read == 0)
		{
			if (remainder && *remainder)
			{
				line = remainder;
				free(remainder);
				remainder = NULL;
				break;
			}
			else
			{
				
				free(remainder);
				remainder = NULL;
				break;
			}
		}
		buffer[bytes_read] = '\0';
		temp = ft_strjoin(remainder, buffer);
		if(!temp)
		{
			free(buffer);
			free(remainder);
			return (NULL);
		}
			
		if (remainder)
			free(remainder);
		remainder = temp;
		line_index = find_new_line(remainder);
		if (line_index >= 0)
		{
			char	*new_remainder;
			remainder[line_index] = '\0';
			line = ft_strdup(remainder);
			if(!line)
				return (NULL);
			new_remainder = ft_strdup(remainder + line_index + 1);
			free(remainder);
			remainder = new_remainder;
			break;
		}
		
	}
	free(buffer);
	return (line);
}

//_______________Test_______________//



int main() {
    const char *filename = "text6.txt"; 
    int fd = open(filename, O_RDONLY);  

    if (fd == -1) {
        perror("Error opening file");
        return 1;
    }

    char *line;
    int line_count = 0;
    while ((line = get_next_line(fd)) != NULL) {
        printf("Line %d: %s", line_count, line);
        free(line); 
        line_count++;
    }

    close(fd); 
    return 0;
}














