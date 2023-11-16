/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpleutin <bpleutin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 14:10:26 by bpleutin          #+#    #+#             */
/*   Updated: 2023/11/16 17:55:45 by bpleutin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common.h"

void	init_raycast(t_game *game, t_ray *ray)
{
	int	x;

	ray->pos_x = get_start_idx(game->map).x + 0.5;
	ray->pos_y = get_start_idx(game->map).y + 0.5;
	ray->dir_x = 0;
	ray->dir_y = 0;
	if (game->map[(int)ray->pos_x][(int)ray->pos_y] == 'N')
		ray->dir_y = 1;
	if (game->map[(int)ray->pos_x][(int)ray->pos_y] == 'S')
		ray->dir_y = -1;
	if (game->map[(int)ray->pos_x][(int)ray->pos_y] == 'W')
		ray->dir_x = -1;
	if (game->map[(int)ray->pos_x][(int)ray->pos_y] == 'E')
		ray->dir_x = 1;
	ray->plane_x = 0.0;
	ray->plane_y = 0.66;
	x = 0;
	while (x++ < SCREENWIDTH)
	{
		// calculate ray position and direction
		ray->camera_x = 2 * x / (double)SCREENWIDTH - 1;
		ray->raydir_x = ray->dir_x + ray->plane_x * ray->camera_x;
		ray->raydir_y = ray->dir_y + ray->plane_y * ray->camera_x;
		ray->map_x = ray->pos_x;
		ray->map_y = ray->pos_y;
		if (ray->raydir_x == 0)
			ray->deltadist_x = INFINITY;
		else
			ray->deltadist_x = fabs(1 / ray->raydir_x);
		if (ray->raydir_y == 0)
			ray->deltadist_y = INFINITY;
		else
			ray->deltadist_y = fabs(1 / ray->raydir_y);
		ray->hit = 0;
		// calculate step and initial sideDist
		if (ray->raydir_x < 0)
		{
			ray->step_x = -1;
			ray->sidedist_x = (ray->pos_x - ray->map_x) * ray->deltadist_x;
		}
		else
		{
			ray->step_x = 1;
			ray->sidedist_x = (ray->map_x + 1.0 - ray->pos_x)
				* ray->deltadist_x;
		}
		if (ray->raydir_y < 0)
		{
			ray->step_y = -1;
			ray->sidedist_y = (ray->pos_y - ray->map_y) * ray->deltadist_y;
		}
		else
		{
			ray->step_y = 1;
			ray->sidedist_y = (ray->map_y + 1.0 - ray->pos_y)
				* ray->deltadist_y;
		}
		// perform DDA (Digital Differential Analysis) algorithm
		while (ray->hit == 0)
		{
			// jump to next map square, either in x-direction, or in y-direction
			if (ray->sidedist_x < ray->sidedist_y)
			{
				ray->sidedist_x += ray->deltadist_x;
				ray->map_x += ray->step_x;
				ray->side = 0;
			}
			else
			{
				ray->sidedist_y += ray->deltadist_y;
				ray->map_y += ray->step_y;
				ray->side = 1;
			}
			// Check if ray has hit a wall
			if (game->map[ray->map_x][ray->map_y] > 0)
				ray->hit = 1;
		}
		// Calculate distance of perpendicular ray 
		// (Euclidean distance would give fisheye effect!)
		if (ray->side == 0)
			ray->perpwalldist = (ray->sidedist_x - ray->deltadist_x);
		else
			ray->perpwalldist = (ray->sidedist_y - ray->deltadist_y);
		//Calculate height of line to draw on screen
		ray->line_height = (int)(SCREENHEIGHT / ray->perpwalldist);
		ray->pitch = 100;
		//calculate lowest and highest pixel to fill in current stripe
		ray->draw_start = -ray->line_height / 2 + SCREENHEIGHT / 2 + ray->pitch;
		if (ray->draw_start < 0)
			ray->draw_start = 0;
		ray->draw_end = ray->line_height / 2 + SCREENHEIGHT / 2 + ray->pitch;
		if (ray->draw_end >= SCREENHEIGHT)
			ray->draw_end = SCREENHEIGHT - 1;
		//texturing calculations
		ray->tex_num = game->map[ray->map_x][ray->map_y] - 1;
		// 1 subtracted from it so that texture 0 can be used!

		//calculate value of wallX
		if (ray->side == 0)
			ray->wall_x = ray->pos_y + ray->perpwalldist * ray->raydir_y;
		else
			ray->wall_x = ray->pos_x + ray->perpwalldist * ray->raydir_x;
		ray->wall_x -= floor((ray->wall_x));
		//x coordinate on the texture
		ray->tex_x = (int)(ray->wall_x * (double)TEXWIDTH);
		if (ray->side == 0 && ray->raydir_x > 0)
			ray->tex_x = TEXWIDTH - ray->tex_x - 1;
		if (ray->side == 1 && ray->raydir_y < 0)
			ray->tex_x = TEXWIDTH - ray->tex_x - 1;
		// TODO: an integer-only bresenham or DDA like algorithm
		// could make the texture coordinate stepping faster
		// How much to increase the texture coordinate per screen pixel
		ray->step = 1.0 * TEXHEIGHT / ray->line_height;
		// Starting texture coordinate
		ray->tex_pos = (ray->draw_start - ray->pitch
				- SCREENHEIGHT / 2 + ray->line_height / 2) * ray->step;
		int	y;

		y = ray->draw_start;
		while (y++ < ray->draw_end)
		{
			// Cast the texture coordinate to integer,
			// and mask with (texHeight - 1) in case of overflow
			ray->tex_y = (int) ray->tex_pos & (TEXHEIGHT - 1);
			ray->tex_pos += ray->step;
			ray->color = game->img[ray->tex_num][TEXHEIGHT
				* ray->tex_y + ray->tex_x];
			// make color darker for y-sides:
			// R, G and B byte each divided through two
			// with a "shift" and an "and"
			if (ray->side == 1)
				ray->color = (ray->color >> 1) & 8355711;
			buffer[y][x] = ray->color;
		}
	}

    drawBuffer(buffer[0]);
    for(int y = 0; y < h; y++) for(int x = 0; x < w; x++) buffer[y][x] = 0; //clear the buffer instead of cls()
    redraw();
}
