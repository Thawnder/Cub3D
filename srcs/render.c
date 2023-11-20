/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldeville <ldeville@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 15:26:21 by ldeville          #+#    #+#             */
/*   Updated: 2023/11/20 23:33:49 by ldeville         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common.h"

static void	prepare_render(t_game *g)
{
	int	y;

	y = 0;
	if (g->render)
	{
		mlx_destroy_image(g->mlx, g->render->ptr);
		free(g->render);
	}
	g->render = ft_calloc(sizeof(t_data), 1);
	g->render->ptr = mlx_new_image(g->mlx, SCREENWIDTH, SCREENHEIGHT);
	g->render->addr = (int *)mlx_get_data_addr(g->render->ptr, &g->render->bpp,
			&g->render->length, &g->render->endian);
	ft_free_buffer(g);
	g->buffer = ft_calloc(sizeof * g->buffer, SCREENHEIGHT + 1);
	while (y < SCREENHEIGHT)
	{
		g->buffer[y] = ft_calloc(sizeof * g->buffer, SCREENWIDTH + 1);
		y++;
	}
}

static void	render_frame(t_game *g)
{
	int		x;
	int		y;
	int		pixel;

	y = 0;
	while (y < SCREENHEIGHT)
	{
		x = 0;
		while (x < SCREENWIDTH)
		{
			pixel = y * (g->render->length / 4) + x;
			if (g->buffer[y][x] > 0)
				g->render->addr[pixel] = g->buffer[y][x];
			else if (y < SCREENHEIGHT / 2)
				g->render->addr[pixel] = g->hex[0];
			else if (y < SCREENHEIGHT -1)
				g->render->addr[pixel] = g->hex[1];
			x++;
		}
		y++;
	}
}

void	init_raycast(t_game *g, int x)
{
	g->ray->camera_x = 2 * x / (double)SCREENWIDTH - 1;
	g->ray->raydir_x = g->ray->dir_x + g->ray->plane_x * g->ray->camera_x;
	g->ray->raydir_y = g->ray->dir_y + g->ray->plane_y * g->ray->camera_x;
	g->ray->map_x = g->ray->pos_x;
	g->ray->map_y = g->ray->pos_y;
	g->ray->step_x = 0;
	g->ray->step_y = 0;
	g->ray->sidedist_x = 0;
	g->ray->sidedist_y = 0;
	g->ray->deltadist_x = fabs(1 / g->ray->raydir_x);
	g->ray->deltadist_y = fabs(1 / g->ray->raydir_y);
	g->ray->perpwalldist = 0;
	g->ray->wall_x = 0;
	g->ray->side = 0;
	g->ray->line_height = 0;
	g->ray->draw_start = 0;
	g->ray->draw_end = 0;
	g->ray->hit = 0;
}

void	sort_sprite(t_game *g)
{
	int			x;
	int			y;
	t_sprite	tmp;

	x = -1;
	while (g->sprite[++x].x)
	{
		y = -1;
		while (g->sprite[++y + 1].x)
		{
			if (g->sprite[y].distance > g->sprite[y + 1].distance)
			{
				tmp = g->sprite[y];
				g->sprite[y] = g->sprite[y + 1];
				g->sprite[y + 1] = tmp;
			}
		}
	}
}

void	render(t_game *g)
{
	int	x;

	x = 0;
	prepare_render(g);
	while (x < SCREENWIDTH)
	{
		init_raycast(g, x);
		set_sidedist(g);
		set_hit_texture(g);
		set_draw_start_end(g);
		set_buffer_color(g, x);
		x++;
	}
	x = -1;
	while (g->sprite[++x].x)
		g->sprite[x].distance = ((g->ray->pos_x - g->sprite[x].x)
				* (g->ray->pos_x - g->sprite[x].x) + (g->ray->pos_y
					- g->sprite[x].y) * (g->ray->pos_y - g->sprite[x].y));
	sort_sprite(g);
	render_sprites(g);
	minimap(g);
	render_frame(g);
	mlx_put_image_to_window(g->mlx, g->win, g->render->ptr, 0, 0);
}
