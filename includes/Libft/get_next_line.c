/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldeville <ldeville@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 14:15:07 by bpleutin          #+#    #+#             */
/*   Updated: 2023/11/15 10:08:36 by ldeville         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*ft_cut_line(char *str, char *line)
{
	char	*res;
	int		n;

	res = NULL;
	if (str)
		n = ft_strlen2(str);
	else
		n = 0;
	if (!line || !line[n])
		return (free(line), res);
	if (line[n])
		res = ft_substr2(line, n, ft_strlen2(line) - n);
	return (free(line), res);
}

static char	*ft_read_line(int fd, char *line, char **res)
{
	char	*buffer;
	int		r;
	int		n;

	buffer = malloc(BUFFER_SIZE + 1);
	r = 1;
	while (r != 0 && !ft_strchr2(line, '\n'))
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
		*res = ft_substr2(line, 0, n + 1);
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
