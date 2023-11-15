/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldeville <ldeville@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 16:54:57 by bpleutin          #+#    #+#             */
/*   Updated: 2023/11/15 10:08:35 by ldeville         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen2(char *str)
{
	size_t	i;

	i = 0;
	if (str)
	{
		while (str[i])
			i++;
	}
	return (i);
}

char	*ft_strjoin2(char *s1, char *s2)
{
	char	*res;
	size_t	i;
	size_t	j;

	i = 0;
	if (!s1 && !s2)
		return (NULL);
	if (!s1)
		return (ft_strdup2(s2));
	if (!s2)
		return (ft_strdup2(s1));
	res = malloc(ft_strlen2(s1) + ft_strlen2(s2) + 1);
	if (!res)
		return (NULL);
	j = 0;
	while (s1[i])
		res[i++] = s1[j++];
	j = 0;
	while (s2[j])
		res[i++] = s2[j++];
	return (res[i] = 0, free(s1), res);
}

char	*ft_strchr2(char *s, int c)
{
	int	i;

	i = 0;
	if (!s)
		return (NULL);
	while (s[i])
	{
		if (s[i] == c)
			return (s + i);
		i++;
	}
	if (c == 0)
		return (s + i);
	else
		return (0);
}

char	*ft_strdup2(char *s)
{
	char	*res;
	size_t	i;
	size_t	len;

	len = ft_strlen2(s);
	res = malloc(len + 1);
	if (!res)
		return (NULL);
	i = 0;
	while (i < len)
	{
		res[i] = s[i];
		i++;
	}
	return (res[i] = 0, res);
}

char	*ft_substr2(char *s, unsigned int start, size_t len)
{
	char	*res;
	size_t	size;
	size_t	i;

	if (!s)
		return (NULL);
	if (start >= ft_strlen2(s))
		return (NULL);
	if (ft_strlen2(s) - start < len)
		size = ft_strlen2(s) - start;
	else
		size = len;
	res = malloc(size + 1);
	if (!res)
		return (NULL);
	i = 0;
	while (i < size && s)
	{
		res[i] = s[i + start];
		i++;
	}
	return (res[i] = 0, res);
}
