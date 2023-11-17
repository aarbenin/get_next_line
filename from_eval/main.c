#include "get_next_line_bonus.h"
#include <fcntl.h>
#include <stdio.h>

int	main()
{

	int fd1;
	int fd2;
	int fd3;

	fd1 = open("test.txt", O_RDONLY);
	fd2 = open("test2.txt", O_RDONLY);
	fd3 = open("test3.txt", O_RDONLY);

	printf("Line: %s\n", get_next_line(fd1));
	printf("Line: %s\n", get_next_line(fd1));

	printf("Line: %s\n", get_next_line(fd2));

	printf("Line: %s\n", get_next_line(fd1));
	printf("Line: %s\n", get_next_line(fd1));

	printf("Line: %s\n", get_next_line(fd3));

	printf("Line: %s\n", get_next_line(fd1));
	printf("Line: %s\n", get_next_line(fd1));
	printf("Line: %s\n", get_next_line(fd1));
	printf("Line: %s\n", get_next_line(fd1));
	printf("Line: %s\n", get_next_line(fd1));
	printf("Line: %s\n", get_next_line(fd1));
	printf("Line: %s\n", get_next_line(fd1));
	printf("Line: %s\n", get_next_line(fd1));
	printf("Line: %s\n", get_next_line(fd1));
	printf("Line: %s\n", get_next_line(fd1));
	printf("Line: %s\n", get_next_line(fd1));
	printf("Line: %s\n", get_next_line(fd1));
	printf("Line: %s\n", get_next_line(fd1));
	close(0);
	return (0); 
}