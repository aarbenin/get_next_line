#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# include <stdlib.h>
# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 50
# endif

typedef struct s_fd_list
{
	int					fd;
	char				*remainder;
	struct s_fd_list	*next;
}						t_fd_list;



char					*get_next_line(int fd);

#endif
