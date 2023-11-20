/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldeville <ldeville@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 14:02:38 by ldeville          #+#    #+#             */
/*   Updated: 2023/11/20 15:43:41 by ldeville         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common.h"

static int	index_texture(t_game *g, int out)
{
	if (!out && g->ray->hit == 2)
		return (4);
	if (g->ray->side == 0)
	{
		if (g->ray->raydir_x < 0)
			return (0);
		else
			return (2);
	}
	else
	{
		if (g->ray->raydir_y > 0)
			return (3);
		else
			return (1);
	}
	return (0);
}

void	set_sidedist(t_game *g)
{
	if (g->ray->raydir_x < 0)
	{
		g->ray->step_x = -1;
		g->ray->sidedist_x = (g->ray->pos_x - g->ray->map_x)
			* g->ray->deltadist_x;
	}
	else
	{
		g->ray->step_x = 1;
		g->ray->sidedist_x = (g->ray->map_x + 1.0 - g->ray->pos_x)
			* g->ray->deltadist_x;
	}
	if (g->ray->raydir_y < 0)
	{
		g->ray->step_y = -1;
		g->ray->sidedist_y = (g->ray->pos_y - g->ray->map_y)
			* g->ray->deltadist_y;
	}
	else
	{
		g->ray->step_y = 1;
		g->ray->sidedist_y = (g->ray->map_y + 1.0 - g->ray->pos_y)
			* g->ray->deltadist_y;
	}
}

void	set_hit_texture(t_game *g)
{
	while (g->ray->hit == 0)
	{
		if (g->ray->sidedist_x < g->ray->sidedist_y)
		{
			g->ray->sidedist_x += g->ray->deltadist_x;
			g->ray->map_x += g->ray->step_x;
			g->ray->side = 0;
		}
		else
		{
			g->ray->sidedist_y += g->ray->deltadist_y;
			g->ray->map_y += g->ray->step_y;
			g->ray->side = 1;
		}
		if (g->ray->map_y < 0.2 || g->ray->map_x < 0.2
			|| g->ray->map_y > g->x_len - 0.2
			|| g->ray->map_x > g->y_len - 0.2)
			break ;
		if (g->map[g->ray->map_x][g->ray->map_y] == 'P')
			g->ray->hit = 2;
		else if (g->map[g->ray->map_x][g->ray->map_y] == '1')
			g->ray->hit = 1;
	}
}

void	set_draw_start_end(t_game *g)
{
	if (g->ray->side == 0)
		g->ray->perpwalldist = (g->ray->sidedist_x - g->ray->deltadist_x);
	else
		g->ray->perpwalldist = (g->ray->sidedist_y - g->ray->deltadist_y);
	g->ray->line_height = (int)(SCREENHEIGHT / g->ray->perpwalldist);
	g->ray->draw_start = -(g->ray->line_height) / 2 + SCREENHEIGHT / 2;
	if (g->ray->draw_start < 0)
		g->ray->draw_start = 0;
	g->ray->draw_end = g->ray->line_height / 2 + SCREENHEIGHT / 2;
	if (g->ray->draw_end >= SCREENHEIGHT)
		g->ray->draw_end = SCREENHEIGHT - 1;
	if (g->ray->side == 0)
		g->ray->wall_x = g->ray->pos_y + g->ray->perpwalldist
			* g->ray->raydir_y;
	else
		g->ray->wall_x = g->ray->pos_x + g->ray->perpwalldist
			* g->ray->raydir_x;
	g->ray->wall_x -= floor(g->ray->wall_x);
	g->ray->tex_num = index_texture(g, 0);
	g->ray->tex_tmp = index_texture(g, 1);
	g->ray->tex_x = (int)(g->ray->wall_x * TEXWIDTH);
	if (g->ray->side == 0 && g->ray->raydir_x < 0)
		g->ray->tex_x = TEXWIDTH - g->ray->tex_x - 1;
	if (g->ray->side == 1 && g->ray->raydir_y > 0)
		g->ray->tex_x = TEXWIDTH - g->ray->tex_x - 1;
}

void	set_buffer_color(t_game *g, int x)
{
	int	y;

	y = g->ray->draw_start;
	g->ray->step = 1.0 * TEXHEIGHT / g->ray->line_height;
	g->ray->tex_pos = (g->ray->draw_start - SCREENHEIGHT / 2
			+ g->ray->line_height / 2) * g->ray->step;
	while (y < g->ray->draw_end)
	{
		g->ray->tex_y = (int)g->ray->tex_pos & (TEXHEIGHT - 1);
		g->ray->tex_pos += g->ray->step;
		g->ray->color = g->img[g->ray->tex_num].addr[TEXHEIGHT
			* g->ray->tex_y + g->ray->tex_x];
		if (g->ray->color > 0)
			g->buffer[y][x] = g->ray->color;
		y++;
	}
	g->ray->z_buffer[x] = g->ray->perpwalldist;
}
