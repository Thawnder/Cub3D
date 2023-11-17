/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldeville <ldeville@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 15:42:30 by ldeville          #+#    #+#             */
/*   Updated: 2023/11/16 17:09:54 by ldeville         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common.h"

void	camera_rotation(t_game *g, int rotSpeed)
{
	double	old_dirx;
	double	old_planex;

	old_planex = g->ray->plane_x;
	old_dirx = g->ray->dir_y;
	g->ray->dir_x = g->ray->dir_x * cos(rotSpeed)
		- g->ray->dir_y * sin(rotSpeed);
	g->ray->dir_y = old_dirx * sin(rotSpeed) + g->ray->dir_y * cos(rotSpeed);
	g->ray->plane_x = g->ray->plane_x * cos(rotSpeed)
		- g->ray->plane_y * sin(rotSpeed);
	g->ray->plane_y = old_planex * sin(rotSpeed)
		+ g->ray->plane_y * cos(rotSpeed);
}

int	update(t_game *g)
{
	if (g->end == 1)
		return (0);
	if (g->forward == 1)
		go_forward(g);
	if (g->backward == 1)
		go_backward(g);
	if (g->left == 1)
		camera_rotation(g, RS);
	if (g->right == 1)
		camera_rotation(g, -RS);

	static int debug = 0;
	if (++debug == 20000)
	{
		printf("POS JOUEUR : %lf %lf\n", g->ray->pos_x, g->ray->pos_y);
		debug = 0;
	}




	minimap(g); //last
	return (0);
}
