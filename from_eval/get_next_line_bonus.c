/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vshchuki <vshchuki@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 21:48:22 by vshchuki          #+#    #+#             */
/*   Updated: 2023/11/16 10:47:27 by vshchuki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*ft_strchr(const char *s, int c)
{
	int		i;
	int		len;

	c = c & 0xFF;
	if (c < 0 || c >= 127)
		return ((char *)s);
	if (c == '\0')
	{
		len = ft_strlen(s);
		return ((char *)(&s[len]));
	}
	i = 0;
	while (s[i])
	{
		if (s[i] == c)
			return ((char *)(&s[i]));
		i++;
	}
	return ((char *) 0);
}

int	ft_read_chunk(int fd, char **cache, t_state *s_store)
{
	s_store->read_size = read(fd, s_store->buffer, BUFFER_SIZE);
	if (s_store->read_size <= 0)
		free(s_store->buffer);
	if (s_store->read_size < 0)
		return (-1);
	if (s_store->read_size == 0)
		return (2);
	if (s_store->read_size < BUFFER_SIZE)
		s_store->buffer[s_store->read_size] = '\0';
	s_store->buffer[BUFFER_SIZE] = '\0';
	while (s_store->buffer[s_store->i] && s_store->buffer[s_store->i] != '\n')
		s_store->i++;
	if (s_store->buffer[s_store->i] == '\n' && cache == NULL)
		s_store->result = ft_substr(s_store->buffer, 0, s_store->i + 1);
	else
	{
		s_store->t = ft_strdup_s(cache[fd]);
		free(cache[fd]);
		cache[fd] = ft_strjoin(s_store->t, s_store->buffer);
		free(s_store->t);
	}
	free(s_store->buffer);
	return (0);
}

int	ft_handle_cache(int fd, char **cache, t_state *s_store)
{
	char	*t;

	s_store->result = ft_substr(cache[fd], 0,
			ft_strchr(cache[fd], '\n') - cache[fd] + 1);
	if (!s_store->result)
		return (-1);
	t = ft_strdup_s(cache[fd]);
	if (!t)
	{
		free(s_store->result);
		s_store->result = NULL;
		return (-1);
	}
	free(cache[fd]);
	if (*(ft_strchr(t, '\n') + 1) == '\0')
		cache[fd] = ft_substr(t, ft_strchr(t, '\n') - t + 1,
				BUFFER_SIZE - (ft_strchr(t, '\n') - t) - 1);
	else
		cache[fd] = ft_substr(t, ft_strchr(t, '\n') - t + 1, BUFFER_SIZE);
	free(t);
	return (0);
}

int	ft_handle_read(int fd, char **cache, t_state *s_store)
{
	int			r;

	s_store->i = 0;
	s_store->buffer = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!s_store->buffer)
		s_store->result = NULL;
	r = ft_read_chunk(fd, cache, s_store);
	if (r == -1)
		s_store->result = NULL;
	else if (r == 2)
		s_store->result = ft_strdup_s(cache[fd]);
	if (r == -1 || r == 2)
		return (-1);
	return (0);
}

char	*get_next_line(int fd)
{
	static char	*cache[10240];
	t_state		s_store;

	if (fd < 0 || BUFFER_SIZE < 0)
		return (NULL);
	while (1)
	{
		if (cache[fd] != NULL && ft_strchr(cache[fd], '\n'))
		{
			if (ft_handle_cache(fd, cache, &s_store) == -1)
				break ;
			else
				return (s_store.result);
		}
		else if (ft_handle_read(fd, cache, &s_store) == -1)
			break ;
	}
	if (s_store.result && s_store.result[0] == '\0')
	{
		free(s_store.result);
		s_store.result = NULL;
	}
	free(cache[fd]);
	cache[fd] = NULL;
	return (s_store.result);
}
