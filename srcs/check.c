/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldeville <ldeville@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 16:14:37 by ldeville          #+#    #+#             */
/*   Updated: 2023/11/16 14:45:12 by ldeville         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common.h"

static int	check_char(char **map)
{
	int	i;
	int	y;
	int	player;

	y = 0;
	player = 0;
	while (map[++y][0])
	{
		i = -1;
		while (map[y][++i])
		{
			if (!player && (map[y][i] == 'N' || map[y][i] == 'S'
				|| map[y][i] == 'E' || map[y][i] == 'W'))
				++player;
			else if (player && (map[y][i] == 'N' || map[y][i] == 'S'
				|| map[y][i] == 'E' || map[y][i] == 'W'))
				return (0);
			else if (map[y][i] != '0' && map[y][i] != '1' && map[y][i] != ' ')
				return (0);
		}
	}
	if (!player)
		return (0);
	return (1);
}

static int	check_side_wall(char **map)
{
	int	i;
	int	y;

	y = -1;
	while (map[++y][0])
	{
		i = 0;
		while (map[y][i] && map[y][i] == ' ')
			i++;
		if (!map[y][i] || map[y][i] != '1')
		{
			ft_printf("HERE %c - %i %i\n", map[y][i], y, i);
			return (0);
		}
		i = ft_strlen(map[y]) - 1;
		while (map[y][i] && map[y][i] == ' ')
			i--;
		if (!map[y][i] || map[y][i] != '1')
		{
			ft_printf("HERE %c - %i %i\n", map[y][i], y, i);
			return (0);
		}
	}
	return (1);
}

static int	check_uplow_wall_2(char **map, int *y, int *i)
{
	while (map[*y][*i] && map[*y][*i] == ' ')
	{
		if ((*y != ft_ylen(map) - 1
				&& !(map[*y + 1][*i] == ' ' || map[*y + 1][*i] == '1'))
			|| (*y != 0 && !(map[*y - 1][*i] == ' ' || map[*y - 1][*i] == '1')))
			return (0);
		*i += 1;
	}
	if (map[*y][*i] && map[*y][*i] != ' ' && map[*y][*i] != '1')
		return (0);
	else if (!map[*y][*i])
		*i = 0;
	else
		*y -= 1;
	return (1);
}

static int	check_uplow_wall(char **map)
{
	int	i;
	int	y;

	y = -1;
	while (map[++y][0])
	{
		while (map[y][i] && map[y][i] == ' ')
			i++;
		while (map[y][i] && map[y][i] == '1')
			i++;
		while (map[y][i] && map[y][i] != ' ')
			i++;
		if (!map[y][i])
		{
			i = 0;
			continue ;
		}
		else if (map[y][i] == ' ' && map[y][i - 1] != '1')
			return (0);
		if (!check_uplow_wall_2(map, &y, &i))
			return (0);
	}
	return (1);
}

int	check_map(t_game *g)
{
	if (!check_char(g->map))
		return (printf("Error\nMap must contain : 0/1 and 1xN/S/E/W\n"), 0);
	if (!check_side_wall(g->map) || !check_uplow_wall(g->map))
		return (printf("Error\nMap must be surrounded by wall\n"), 0);
	return (1);
}
