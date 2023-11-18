/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldeville <ldeville@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 12:34:18 by ldeville          #+#    #+#             */
/*   Updated: 2023/11/18 14:13:56 by ldeville         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common.h"

void	ft_free_buffer(t_game *g)
{
	int	y;

	y = 0;
	if (g->buffer)
	{
		while (y < SCREENHEIGHT)
		{
			free(g->buffer[y]);
			y++;
		}
		free(g->buffer);
	}
}

void	ft_free_img(t_game *g)
{
	int	i;

	i = 0;
	while (g->img[i].ptr)
	{
		mlx_destroy_image(g->mlx, g->img[i].ptr);
		i++;
	}
	free(g->img);
}

void	free_map(t_game *g)
{
	int	i;

	i = 0;
	while (g->map[i][0])
		free(g->map[i++]);
	free(g->map[i]);
	free(g->map);
	if (g->doors)
	{
		i = 0;
		while (g->doors[i][0])
			free(g->doors[i++]);
		free(g->doors[i]);
		free(g->doors);
	}
}

void	free_all_2(t_game *g)
{
	if (g->render)
	{
		mlx_destroy_image(g->mlx, g->render->ptr);
		free(g->render);
	}
	if (g->ray)
		free(g->ray);
	if (g->mlx)
	{
		mlx_destroy_window(g->mlx, g->win);
		mlx_destroy_display(g->mlx);
		free(g->mlx);
	}
}

void	free_all(t_game *g)
{
	int	i;

	i = 0;
	if (g->tex)
	{
		while (i < 4)
			free(g->tex[i++]);
		free(g->tex);
	}
	if (g->map)
		free_map(g);
	if (g->img)
		ft_free_img(g);
	if (g->minimap)
	{
		mlx_destroy_image(g->mlx, g->minimap->ptr);
		free(g->minimap);
	}
	free_all_2(g);
	ft_free_buffer(g);
	free(g);
}
