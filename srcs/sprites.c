/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldeville <ldeville@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 14:13:05 by bpleutin          #+#    #+#             */
/*   Updated: 2023/11/20 17:59:06 by ldeville         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common.h"

void	sprites_projection(t_game *g, int i, double inv_det)
{
	g->ray->sprite_x = g->sprite[i].x - g->ray->pos_x;
	g->ray->sprite_y = g->sprite[i].y - g->ray->pos_y;
	g->ray->transform_x = inv_det * (g->ray->dir_y * g->ray->sprite_x
			- g->ray->dir_x * g->ray->sprite_y);
	g->ray->transform_y = inv_det * ((g->ray->plane_y * -1) * g->ray->sprite_x
			+ g->ray->plane_x * g->ray->sprite_y);
	g->ray->sprite_screen_x = (int)(SCREENWIDTH / 2)*(1 + g->ray->transform_x
			/ g->ray->transform_y);
	g->ray->sprite_height = abs((int)(SCREENHEIGHT / g->ray->transform_y));
	g->ray->draw_start_y = -g->ray->sprite_height / 2 + SCREENHEIGHT / 2;
	if (g->ray->draw_start_y < 0)
		g->ray->draw_start_y = 0;
	g->ray->draw_end_y = g->ray->sprite_height / 2 + SCREENHEIGHT / 2;
	if (g->ray->draw_end_y >= SCREENHEIGHT)
		g->ray->draw_end_y = SCREENHEIGHT - 1;
	g->ray->sprite_width = abs((int)(SCREENHEIGHT / (g->ray->transform_y)));
	g->ray->draw_start_x = -g->ray->sprite_width / 2 + g->ray->sprite_screen_x;
	if (g->ray->draw_start_x < 0)
		g->ray->draw_start_x = 0;
	g->ray->draw_end_x = g->ray->sprite_width / 2 + g->ray->sprite_screen_x;
	if (g->ray->draw_end_x >= SCREENWIDTH)
		g->ray->draw_end_x = SCREENWIDTH - 1;
}

void	draw_sprites(t_game *g)
{
	int		y;
	int		d;

	g->ray->tex_x = (int)(256 * (g->ray->stripe
				- (-g->ray->sprite_width / 2 + g->ray->sprite_screen_x))
			* TEXWIDTH / g->ray->sprite_width) / 256;
	if (g->ray->transform_y > 0 && g->ray->stripe > 0
		&& g->ray->stripe < SCREENWIDTH
		&& g->ray->transform_y < g->ray->z_buffer[g->ray->stripe]) // OWUEGHFIYUWEGHYI
	{
		y = g->ray->draw_start_y - 1;
		while (++y < g->ray->draw_end_y)
		{
			d = (y) * 256 - SCREENHEIGHT * 128
				+ g->ray->sprite_height * 128;
			g->ray->tex_y = ((d * TEXHEIGHT)
					/ g->ray->sprite_height) / 256;
			g->ray->color = g->img[g->actual_anim].addr[TEXWIDTH
				* g->ray->tex_y + g->ray->tex_x];
			if (g->ray->color > 0)
				g->buffer[y][g->ray->stripe] = g->ray->color;
		}
	}
}

void	render_sprites(t_game *g)
{
	int		i;
	double	inv_det;

	i = -1;
	while (g->sprite[++i].x)
	{
		inv_det = 1.0 / (g->ray->plane_x * g->ray->dir_y
				- g->ray->dir_x * g->ray->plane_y);
		sprites_projection(g, i, inv_det);
		g->ray->stripe = g->ray->draw_start_x - 1;
		while (++g->ray->stripe < g->ray->draw_end_x)
			draw_sprites(g);
	}
}