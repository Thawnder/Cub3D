/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldeville <ldeville@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 11:38:32 by ldeville          #+#    #+#             */
/*   Updated: 2023/11/15 12:33:02 by ldeville         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common.h"

static int	find_map(int file, int *size)
{
	char	*line;
	int		i;
	int		y;

	y = 0;
	line = get_next_line(file);
	i = space_until(line);
	while (line && strncmp(&line[i], "1", 1))
	{
		free(line);
		line = get_next_line(file);
		i = space_until(line);
		y++;
	}
	if (!line || line[i] != '1')
		return (free(line), close(file), printf("Error\nError while parsing the map.\n"), 0);
	while (line)
	{
		free(line);
		line = get_next_line(file);
		if (line)
			i = space_until(line);
		*size += 1;
	}
	return (close(file), free(line), y);
}

int	set_map(int file, char *nfile, t_game *g)
{
	char	*line;
	int		iMap;
	int		size;

	size = 0;
	iMap = find_map(file, &size);
	file = open(nfile, O_RDONLY);
	line = get_next_line(file);
	g->map = calloc(sizeof(char *), size + 1);
	size = 0;
	while (size++ < iMap)
	{
		free(line);
		line = get_next_line(file);
	}
	size = -1;
	while (line && ++size >= 0)
	{
		g->map[size] = calloc(sizeof(char), ft_strlen(line) + 1);
		set_line(g, line, size);
		line = get_next_line(file);
	}
	g->map[size] = calloc(sizeof(char), 1);
	return (1);
}