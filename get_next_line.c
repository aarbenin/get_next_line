#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

#define BUFF_SIZE 100

char	*ft_strchr(const char *s, int c)
{
	char	*str;
	char	ch;

	str = (char *)s;
	ch = (char)c;
	while (*str)
	{
		if (*str == ch)
			return (str);
		str++;
	}
	if (ch == '\0')
		return (str);
	return (NULL);
}

char	*get_next_line(int fd)
{
	char		temp_buffer[BUFF_SIZE];
	char		*line;
	static char	buffer[BUFF_SIZE];
	ssize_t		bytes_read;

	bytes_read = read(fd, temp_buffer, BUFF_SIZE - 1);
	if (bytes_read < 0)
	{
		printf("error while reading file\n");
		close(fd);
	}
	temp_buffer[bytes_read] = '\0';
	char *end_line = ft_strchr(temp_buffer, '\n');

	 if (end_line)
	 {
		size_t	len;

		len = sizeof(temp_buffer) - sizeof(end_line);
		line = (char *)malloc((len + 1) * sizeof(char));
		if (!line)
		{
			printf("error while allocating memory\n");
			return (NULL);
		}
		int	i;

		i = 0;
		while (i < len)
		{
			line [i] = temp_buffer[i];
			i++;
		}
		line[i] = '\0';
		

	 }
	
	return (line);
	

}




int	main(void)
{
int	fd;

fd = open("text.txt", O_RDONLY);
if (fd < 0)
	printf("error while openning file\n");

char	*line = get_next_line(fd);
printf("%s\n", line);




}