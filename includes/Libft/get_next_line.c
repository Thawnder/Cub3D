/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldeville <ldeville@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 14:15:07 by bpleutin          #+#    #+#             */
/*   Updated: 2023/11/14 16:21:03 by ldeville         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin2(char *s1, char *s2)
{
	char	*res;
	size_t	i;
	size_t	j;

	i = 0;
	if (!s1 && !s2)
		return (NULL);
	if (!s1)
		return (ft_strdup(s2));
	if (!s2)
		return (ft_strdup(s1));
	res = malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
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

static char	*ft_cut_line(char *str, char *line)
{
	char	*res;
	int		n;

	res = NULL;
	if (str)
		n = ft_strlen(str);
	else
		n = 0;
	if (!line || !line[n])
		return (free(line), res);
	if (line[n])
		res = ft_substr(line, n, ft_strlen(line) - n);
	return (free(line), res);
}

static char	*ft_read_line(int fd, char *line, char **res)
{
	char	*buffer;
	int		r;
	int		n;

	buffer = malloc(BUFFER_SIZE + 1);
	r = 1;
	while (r != 0 && !ft_strchr(line, '\n'))
	{
		r = read(fd, buffer, BUFFER_SIZE);
		buffer[r] = '\0';
		line = ft_strjoin2(line, buffer);
	}
	free(buffer);
	n = 0;
	if (line && line[n])
	{
		while (line[n] && line[n] != '\n')
			n++;
		*res = ft_substr(line, 0, n + 1);
	}
	else
		*res = NULL;
	return (line = ft_cut_line(*res, line));
}

char	*get_next_line(int fd)
{
	static char	*line = NULL;
	char		*res;

	if (fd < 0 || BUFFER_SIZE < 1 || read(fd, 0, 0) < 0)
		return (free(line), line = NULL, NULL);
	return (res = NULL, line = ft_read_line(fd, line, &res), res);
}
