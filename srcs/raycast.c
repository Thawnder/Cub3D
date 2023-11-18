/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldeville <ldeville@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 14:10:26 by bpleutin          #+#    #+#             */
/*   Updated: 2023/11/18 13:36:28 by ldeville         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common.h"

static int	index_texture(t_game *g)
{
	if (g->ray->hit == 2)
		return (4);
	if (g->ray->hit == 3)
		return (g->actual_anim);
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


void	init_raycast(t_game *g)
{
	int	x;

	x = 0;
	while (x < SCREENWIDTH)
	{
		g->ray->camera_x = 0;
		g->ray->raydir_x = 0;
		g->ray->raydir_y = 0;
		g->ray->map_x = 0;
		g->ray->map_y = 0;
		g->ray->step_x = 0;
		g->ray->step_y = 0;
		g->ray->sidedist_x = 0;
		g->ray->sidedist_y = 0;
		g->ray->deltadist_x = 0;
		g->ray->deltadist_y = 0;
		g->ray->perpwalldist = 0;
		g->ray->wall_x = 0;
		g->ray->side = 0;
		g->ray->line_height = 0;
		g->ray->draw_start = 0;
		g->ray->draw_end = 0;


		// calculate ray position and direction
		g->ray->camera_x = 2 * x / (double)SCREENWIDTH - 1;
		g->ray->raydir_x = g->ray->dir_x + g->ray->plane_x * g->ray->camera_x;
		g->ray->raydir_y = g->ray->dir_y + g->ray->plane_y * g->ray->camera_x;
		g->ray->map_x = g->ray->pos_x;
		g->ray->map_y = g->ray->pos_y;
		g->ray->deltadist_x = fabs(1 / g->ray->raydir_x);
		g->ray->deltadist_y = fabs(1 / g->ray->raydir_y);
		g->ray->hit = 0;
		// calculate step and initial sideDist
		if (g->ray->raydir_x < 0)
		{
			g->ray->step_x = -1;
			g->ray->sidedist_x = (g->ray->pos_x - g->ray->map_x) * g->ray->deltadist_x;
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
			g->ray->sidedist_y = (g->ray->pos_y - g->ray->map_y) * g->ray->deltadist_y;
		}
		else
		{
			g->ray->step_y = 1;
			g->ray->sidedist_y = (g->ray->map_y + 1.0 - g->ray->pos_y)
				* g->ray->deltadist_y;
		}
		// perform DDA (Digital Differential Analysis) algorithm
		while (g->ray->hit == 0)
		{
			// jump to next map square, either in x-direction, or in y-direction
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
			// Check if ray has hit a wall
			if (g->ray->map_y < 0.25
				|| g->ray->map_x < 0.25
				|| g->ray->map_y > g->x_len - 0.25
				|| g->ray->map_x > g->y_len - 1.25)
				break ;
			if (g->map[g->ray->map_x][g->ray->map_y] == 'P')
				g->ray->hit = 2;
			else if (g->map[g->ray->map_x][g->ray->map_y] == 'A')
				g->ray->hit = 3;
			else if (g->map[g->ray->map_x][g->ray->map_y] > '0')
				g->ray->hit = 1;
		}
		// Calculate distance of perpendicular ray 
		// (Euclidean distance would give fisheye effect!)
		if (g->ray->side == 0)
			g->ray->perpwalldist = (g->ray->sidedist_x - g->ray->deltadist_x);
		else
			g->ray->perpwalldist = (g->ray->sidedist_y - g->ray->deltadist_y);
		//Calculate height of line to draw on screen
		g->ray->line_height = (int)(SCREENHEIGHT / g->ray->perpwalldist);
		//calculate lowest and highest pixel to fill in current stripe
		g->ray->draw_start = -(g->ray->line_height) / 2 + SCREENHEIGHT / 2;
		if (g->ray->draw_start < 0)
			g->ray->draw_start = 0;
		g->ray->draw_end = g->ray->line_height / 2 + SCREENHEIGHT / 2;
		if (g->ray->draw_end >= SCREENHEIGHT)
			g->ray->draw_end = SCREENHEIGHT - 1;
		//calculate value of wallX
		if (g->ray->side == 0)
			g->ray->wall_x = g->ray->pos_y + g->ray->perpwalldist * g->ray->raydir_y;
		else
			g->ray->wall_x = g->ray->pos_x + g->ray->perpwalldist * g->ray->raydir_x;
		g->ray->wall_x -= floor(g->ray->wall_x);
		//x coordinate on the texture
		g->ray->tex_num = index_texture(g);
		g->ray->tex_x = (int)(g->ray->wall_x * TEXWIDTH);


		if (g->ray->side == 0 && g->ray->raydir_x < 0)
			g->ray->tex_x = TEXWIDTH - g->ray->tex_x - 1;
		if (g->ray->side == 1 && g->ray->raydir_y > 0)
			g->ray->tex_x = TEXWIDTH - g->ray->tex_x - 1;


		// TODO: an integer-only bresenham or DDA like algorithm
		// could make the texture coordinate stepping faster
		// How much to increase the texture coordinate per screen pixel
		g->ray->step = 1.0 * TEXHEIGHT / g->ray->line_height;
		// Starting texture coordinate
		g->ray->tex_pos = (g->ray->draw_start - SCREENHEIGHT / 2 + g->ray->line_height / 2) * g->ray->step;

		int	y;
		y = g->ray->draw_start;
		while (y < g->ray->draw_end)
		{
			// Cast the texture coordinate to integer,
			// and mask with (texHeight - 1) in case of overflow
			g->ray->tex_y = (int)g->ray->tex_pos & (TEXHEIGHT - 1);
			g->ray->tex_pos += g->ray->step;
			g->ray->color = g->img[g->ray->tex_num].addr[TEXHEIGHT
				* g->ray->tex_y + g->ray->tex_x];
			// make color darker for y-sides:
			// R, G and B byte each divided through two
			// with a "shift" and an "and"
			// if (g->ray->tex_num == 0)
			// 	g->ray->color = (g->ray->color >> 1) & 8355711;
			if (g->ray->color > 0)
				g->buffer[y][x] = g->ray->color;
			y++;
		}
		x++;
	}

    // drawBuffer(buffer[0]);
    // for(int y = 0; y < h; y++) for(int x = 0; x < w; x++) buffer[y][x] = 0; //clear the buffer instead of cls()
    // redraw();
}
