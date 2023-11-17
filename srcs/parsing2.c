/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldeville <ldeville@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 11:38:32 by ldeville          #+#    #+#             */
/*   Updated: 2023/11/17 19:30:42 by ldeville         ###   ########.fr       */
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
		return (free(line), close(file), printf("Error\nError parsing.\n"), 0);
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

void	resize_map(t_game *g)
{
	int		y;
	int		max_len;

	max_len = 0;
	y = -1;
	while (g->map[++y][0])
	{
		if (max_len < (int)ft_strlen(g->map[y]))
			max_len = (int)ft_strlen(g->map[y]);
	}
	y = -1;
	while (g->map[++y][0])
	{
		if ((int)ft_strlen(g->map[y]) != max_len)
			g->map[y] = set_sized_line(ft_calloc(sizeof(char), max_len + 1),
					g->map[y], max_len);
	}
}

int	set_map(int file, char *nfile, t_game *g)
{
	char	*line;
	int		i_map;
	int		size;

	size = 0;
	i_map = find_map(file, &size);
	file = open(nfile, O_RDONLY);
	line = get_next_line(file);
	g->map = ft_calloc(sizeof(char *), size + 1);
	size = 0;
	while (size++ < i_map)
	{
		free(line);
		line = get_next_line(file);
	}
	size = -1;
	while (++size >= 0 && line)
	{
		g->map[size] = ft_calloc(sizeof(char), ft_strlen(line) + 1);
		set_line(g, line, size);
		line = get_next_line(file);
	}
	g->map[size] = ft_calloc(sizeof(char), 1);
	resize_map(g);
	return (close(file), 1);
}

void	add_info(t_game *g)
{
	int	x;
	int	y;

	y = -1;
	g->ray = ft_calloc(sizeof(t_ray), 1);
	while (g->map[++y][0])
	{
		x = 0;
		while (g->map[y][x])
		{
			if (g->map[y][x] == 'N' || g->map[y][x] == 'S'
				|| g->map[y][x] == 'E' || g->map[y][x] == 'W')
			{
				g->ray->pos_x = y + 0.5;
				g->ray->pos_y = x + 0.5;
				set_orientation(g, g->map[y][x]);
				g->map[y][x] = '0';
				break ;
			}
			x++;
		}
	}
	g->x_len = (int)ft_strlen(g->map[0]);
	g->y_len = (int)ft_ylen(g->map);
}

int	parsing_2(t_game *g)
{
	if (!add_texture(g))
		return (0);
	add_info(g);
	g->hex[0] = ((g->rgb[0][1] & 0xff) << 16) + ((g->rgb[0][2] & 0xff) << 8)
		+ (g->rgb[0][3] & 0xff);
	g->hex[1] = ((g->rgb[1][1] & 0xff) << 16) + ((g->rgb[1][2] & 0xff) << 8)
		+ (g->rgb[1][3] & 0xff);
	return (1);
}
