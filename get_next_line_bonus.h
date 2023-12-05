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
size_t					ft_strlen(const char *str);
char					*ft_strchr(const char *s, int c);
char					*ft_strjoin(char const *s1, char const *s2);
char					*ft_strdup(const char *str);
void					*ft_memcpy(void *dst, const void *src, size_t n);
t_fd_list				*get_fd_node(int fd, t_fd_list **fd_list);
void					remove_fd_node(int fd, t_fd_list **fd_list);

#endif
