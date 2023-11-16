#include "get_next_line.h"
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>

// Helper functions declarations
int find_newline(const char *s) {
    int i = 0;
    while (s && s[i]) {
        if (s[i] == '\n') {
            return i;
        }
        i++;
    }
    return -1;
}

char	*strjoin(char const *s1, char const *s2)
{
	char	*str;
	char	*str_ptr;
	int		len_s1;
	int		len_s2;

	len_s1 = 0;
	len_s2 = 0;
	if (s1 != NULL)
		len_s1 = strlen(s1);
	if (s2 != NULL)
		len_s2 = strlen(s2);
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

char *get_next_line(int fd) {
    static char *remainder = NULL;
    char *buffer;
    char *line;
    int newline_index;
    ssize_t bytes_read;

    if (fd < 0 || BUFFER_SIZE <= 0) {
        return NULL;
    }

    buffer = malloc(BUFFER_SIZE + 1);
    if (!buffer) {
        return NULL;
    }

    line = NULL;
    while (1) {
        bytes_read = read(fd, buffer, BUFFER_SIZE);
        if (bytes_read <= 0) {
            break;
        }

        buffer[bytes_read] = '\0';
        char *temp = strjoin(remainder, buffer);
        free(remainder);
        remainder = temp;

        newline_index = find_newline(remainder);
        if (newline_index >= 0) {
    remainder[newline_index] = '\0';
    line = strdup(remainder);
    char *new_remainder = strdup(remainder + newline_index + 1);
    free(remainder);
    remainder = new_remainder;
    break;
}

    }

    free(buffer);
    return line;
}

void run_test(int fd)
{
	char *line = get_next_line(fd);
	if (line)
	{
		printf("%s\n", line);
		free(line);
	}
}

int	main(void)
{
	int	fd;
	int	i;
	char *filename;

	filename = "text.txt";
	fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		perror("Error opening file");
		return (1);
	}
	i = 0;
	while (i <= 10)
	{
		
		run_test(fd);
		
	}
	close(fd);
}