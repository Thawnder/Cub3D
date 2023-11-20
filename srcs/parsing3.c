/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldeville <ldeville@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 13:31:57 by ldeville          #+#    #+#             */
/*   Updated: 2023/11/20 14:12:12 by ldeville         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common.h"

void	debug(t_game *g)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		printf("%i - <|%s|>\n", i, g->tex[i]);
		i++;
	}
	printf("RGB - FLOOR 	- <|%i, %i, %i|>\n",
		g->rgb[0][0], g->rgb[0][1], g->rgb[0][2]);
	printf("RGB - CEILING 	- <|%i, %i, %i|>\n",
		g->rgb[1][0], g->rgb[1][1], g->rgb[1][2]);
	i = 0;
	printf("\nMAP :\n");
	while (g->map[i][0])
		printf("|%s|\n", g->map[i++]);
}

void	set_sprite(int x, int y, t_game *g)
{
	
	
}

void	doors_map(t_game *g)
{
	int	y;
	int	x;
	int	len;

	y = -1;
	len = ft_strlen(g->map[0]);
	g->doors = ft_calloc(sizeof(char *), ft_ylen(g->map) + 1);
	while (g->map[++y][0])
	{
		x = 0;
		g->doors[y] = ft_calloc(sizeof(char), len + 1);
		while (g->map[y][x])
		{
			g->doors[y][x] = g->map[y][x];
			x++;
		}
	}
	g->doors[y] = ft_calloc(sizeof(char *), 1);
}

void	set_orientation_2(t_game *g, char c)
{
	if (c == 'W')
	{
		g->ray->dir_x = 0;
		g->ray->dir_y = -1;
		g->ray->plane_x = -0.66;
		g->ray->plane_y = 0;
	}
	else if (c == 'E')
	{
		g->ray->dir_x = 0;
		g->ray->dir_y = 1;
		g->ray->plane_x = 0.66;
		g->ray->plane_y = 0;
	}
}

void	set_orientation(t_game *g, char c)
{
	if (c == 'S')
	{
		g->ray->dir_x = 1;
		g->ray->dir_y = 0;
		g->ray->plane_x = 0;
		g->ray->plane_y = 0.66;
	}
	else if (c == 'N')
	{
		g->ray->dir_x = -1;
		g->ray->dir_y = 0;
		g->ray->plane_x = 0;
		g->ray->plane_y = 0.66;
	}
	else
		set_orientation_2(g, c);
}
