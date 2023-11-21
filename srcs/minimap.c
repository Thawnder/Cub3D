/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldeville <ldeville@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 15:43:18 by ldeville          #+#    #+#             */
/*   Updated: 2023/11/21 14:45:30 by ldeville         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common.h"

int	find_color(char c)
{
	if (c == '1' || c == ' ')
		return (0);
	return (0xd50e0e);
}

void	generate_minimap(t_game *g)
{
	int	x;
	int	y;
	int	color;

	y = 4;
	while (y < 4 * g->y_len + 2)
	{
		x = 4;
		while (x < 4 * g->x_len + 2)
		{
			if (x >= SCREENWIDTH - 1)
				break ;
			color = find_color(g->map[(int)(y / 4 - 1)][(int)(x / 4 - 1)]);
			g->buffer[y][x] = color;
			x++;
		}
		y++;
	}
}

void	border_minimap(t_game *g)
{
	int	x;
	int	y;
	int	color;

	y = 0;
	color = mlx_get_color_value(g->mlx, 0x007369);
	while (y < 4 * g->y_len + 8)
	{
		x = 0;
		while (x < 4 * g->x_len + 8)
		{
			if (y > 2 && y < 4 * g->y_len + 6 && x > 2 && x < 4 * g->x_len + 5
				&& ++x > 0)
				continue ;
			g->buffer[y][x] = color;
			x++;
		}
		y++;
	}
}

void	minimap(t_game *g)
{
	int	optx;
	int	opty;

	optx = (int)(g->ray->pos_x) * 4 + 4;
	opty = (int)(g->ray->pos_y) * 4 + 4;
	generate_minimap(g);
	if (g->ray->pos_x - (int)g->ray->pos_x > 0.750)
		optx += 3;
	else if (g->ray->pos_x - (int)g->ray->pos_x > 0.500)
		optx += 2;
	else if (g->ray->pos_x - (int)g->ray->pos_x > 0.250)
		++optx;
	if (g->ray->pos_y - (int)g->ray->pos_y > 0.750)
		opty += 3;
	else if (g->ray->pos_y - (int)g->ray->pos_y > 0.500)
		opty += 2;
	else if (g->ray->pos_y - (int)g->ray->pos_y > 0.250)
		++opty;
	g->buffer[optx][opty] = 0xffff00;
}
