/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vshchuki <vshchuki@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 21:48:24 by vshchuki          #+#    #+#             */
/*   Updated: 2023/11/16 10:53:14 by vshchuki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		i++;
	}
	return (i);
}

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	unsigned int	i;

	i = 0;
	if (dstsize == 0)
	{
		return (ft_strlen(src));
	}
	else if (dstsize > 1)
	{
		while (src[i] && i < dstsize - 1)
		{
			dst[i] = src[i];
			i++;
		}
		dst[i] = '\0';
		return (ft_strlen(src));
	}
	dst[i] = '\0';
	return (ft_strlen(src));
}

char	*ft_strdup_s(const char *s1)
{
	char	*ptr;

	if (!s1)
		return ((char *)0);
	ptr = (char *)malloc((ft_strlen(s1) + 1) * sizeof(char));
	if (!ptr)
		return ((char *)0);
	ft_strlcpy(ptr, s1, ft_strlen(s1) + 1);
	return (ptr);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*new_s;
	size_t	s1_len;
	size_t	s2_len;

	if (s1 && s2)
	{
		s1_len = ft_strlen(s1);
		s2_len = ft_strlen(s2);
		new_s = (char *)malloc((s1_len + s2_len + 1) * sizeof(char));
		if (!new_s)
			return ((void *)0);
		ft_strlcpy(new_s, s1, (s1_len + 1));
		ft_strlcpy(new_s + s1_len, s2, s2_len + 1);
		return (new_s);
	}
	else
	{
		if (!s1)
			return (ft_strdup_s(s2));
		else if (!s2)
			return (ft_strdup_s(s1));
	}
	return ((char *) 0);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*sub_s;
	size_t	s_size;
	size_t	i;

	if (s)
	{
		s_size = ft_strlen(s);
		if (len > (size_t) - 1 - start)
			len = (size_t) - 1 - start;
		if (len > s_size - start)
			len = s_size - start;
		else if (start >= s_size)
			len = 0;
		sub_s = (char *)malloc((len + 1) * sizeof(char));
		if (!sub_s)
			return ((char *)0);
		sub_s[len] = '\0';
		s += start;
		i = -1;
		while (++i < len)
			sub_s[i] = s[i];
		return (sub_s);
	}
	return ((char *)0);
}
