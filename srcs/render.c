/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldeville <ldeville@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 15:26:21 by ldeville          #+#    #+#             */
/*   Updated: 2023/11/17 19:30:18 by ldeville         ###   ########.fr       */
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

void	render(t_game *g)
{
	prepare_render(g);
	init_raycast(g);
	render_frame(g);
	mlx_put_image_to_window(g->mlx, g->win, g->render->ptr, 0, 0);
}
