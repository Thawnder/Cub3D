/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldeville <ldeville@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 16:14:37 by ldeville          #+#    #+#             */
/*   Updated: 2023/11/15 16:32:16 by ldeville         ###   ########.fr       */
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
	return (1);
}

int	check_map(t_game *g)
{
	if (!check_char(g->map))
		return (printf("Error\nMap can only contain : 0, 1 and 1x(N,S,E or W)\n"), 0);
	/*if (!check_wall(g->map))
		return (printf("Error\nMap must be surrounded by wall\n"), 0);*/

	return (1);
}