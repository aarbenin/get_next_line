#include "get_next_line_bonus.h"

size_t	ft_strlen(const char *str)
{
	size_t	len;

	len = 0;
	while (str[len])
		len++;
	return (len);
}

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

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t			i;
	unsigned char	*ptr_dst;
	unsigned char	*ptr_src;

	if (n == 0)
		return (dst);
	if (!src && !dst)
		return (NULL);
	i = 0;
	ptr_dst = (unsigned char *)dst;
	ptr_src = (unsigned char *)src;
	while (i < n)
	{
		ptr_dst[i] = ptr_src[i];
		i++;
	}
	return (dst);
}

t_fd_list	*get_fd_node(int fd, t_fd_list **fd_list)
{
	t_fd_list	*temp;

	temp = *fd_list;
	while (temp)
	{
		if (temp->fd == fd)
			return (temp);
		temp = temp->next;
	}
	temp = malloc(sizeof(t_fd_list));
	if (!temp)
		return (NULL);
	temp->fd = fd;
	temp->remainder = NULL;
	temp->next = *fd_list;
	*fd_list = temp;
	return (temp);
}

void	remove_fd_node(int fd, t_fd_list **fd_list)
{
	t_fd_list	*temp;
	t_fd_list	*prev;

	temp = *fd_list;
	prev = NULL;
	while (temp)
	{
		if (temp->fd == fd)
		{
			if (prev)
				prev->next = temp->next;
			else
				*fd_list = temp->next;
			free(temp->remainder);
			free(temp);
			return ;
		}
		prev = temp;
		temp = temp->next;
	}
}
