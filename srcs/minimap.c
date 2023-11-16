/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldeville <ldeville@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 15:43:18 by ldeville          #+#    #+#             */
/*   Updated: 2023/11/16 22:01:30 by ldeville         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common.h"

int	find_color(char c)
{
	switch (c)
	{
		case '0':
			return (0x0ed5a1);
		case '1':
			return (0);
		case ' ':
			return (0);
		default:
			return (0x0ed5a1);
	}
	return (0);
}

void	generate_minimap(t_game *g)
{
	int	x;
	int	y;
	int	color;
	int	pixel;

	y = 4;
	g->minimap->ptr = mlx_new_image(g->mlx, (int)(4 * g->x_len + 8),
			(int)(4 * g->y_len + 8));
	g->minimap->addr = mlx_get_data_addr(g->minimap->ptr, &g->minimap->bpp,
			&g->minimap->length, &g->minimap->endian);
	while (y < 4 * g->y_len + 2)
	{
		x = 4;
		while (x < 4 * g->x_len + 2)
		{
			pixel = (y * g->minimap->length) + (x * 4);
			color = find_color(g->map[(int)(y / 4 - 1)][(int)(x / 4 - 1)]);
			g->minimap->addr[pixel + 0] = (color >> 24);
			g->minimap->addr[pixel + 1] = (color >> 16) & 0xFF;
			g->minimap->addr[pixel + 2] = (color >> 8) & 0xFF;
			g->minimap->addr[pixel + 3] = (color) & 0xFF;
			x++;
		}
		y++;
	}
}

void	minimap(t_game *g)
{
	int	optx;
	int	opty;

	optx = (int)(g->ray->pos_x) * 4 + 54;
	opty = (int)(g->ray->pos_y) * 4 + 54;
	if (!g->minimap)
	{
		g->minimap = ft_calloc(sizeof(t_data), 1);
		generate_minimap(g);
	}
	mlx_put_image_to_window(g->mlx, g->win, g->minimap->ptr, 50, 50);
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
	mlx_pixel_put(g->mlx, g->win, optx, opty, 0xffd5a1);
}
