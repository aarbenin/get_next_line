#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

#include "get_next_line.h"

#define BUFF_SIZE 100

char	*get_next_line(int fd)
{
	static char	static_buffer[BUFF_SIZE];
	char		temp_buffer[BUFF_SIZE];
	char		*line;
	ssize_t		bytes_read;

	
	bytes_read = read(fd, temp_buffer, BUFF_SIZE - 1);
	if (bytes_read <= 0)
	{
		return (NULL);
	}
	temp_buffer[bytes_read] = '\0';

	line = (char *)malloc(1000);
	if (!line)
		return (NULL);
	line[0] = '\0';
	int	i;
	i = 0;
	while (temp_buffer[i] != '\n' && temp_buffer != '\0')
	{
		line[i] = temp_buffer[i];
		i++;
	}
	if (temp_buffer[i] == '\n')
	{
		line[i] = '\n';
		i++;
	}
	line[i] = '\0';
	return (line);





}


int	main(void)
{
	int	fd;


	fd = open("text.txt", O_RDONLY);
	if (fd == -1)
	{
		printf("Error while openning file\n");
	}
	else
	{
		char	*res = get_next_line(fd);
		write (1, res, sizeof(res));

	}


}