/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldeville <ldeville@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 15:42:30 by ldeville          #+#    #+#             */
/*   Updated: 2023/11/18 13:37:29 by ldeville         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common.h"

void	camera_rotation(t_game *g, double rotspeed)
{
	double	old_dirx;
	double	old_planex;

	old_planex = g->ray->plane_x;
	old_dirx = g->ray->dir_x;
	g->ray->dir_x = g->ray->dir_x * cos(rotspeed)
		- g->ray->dir_y * sin(rotspeed);
	g->ray->dir_y = old_dirx * sin(rotspeed) + g->ray->dir_y * cos(rotspeed);
	g->ray->plane_x = g->ray->plane_x * cos(rotspeed)
		- g->ray->plane_y * sin(rotspeed);
	g->ray->plane_y = old_planex * sin(rotspeed)
		+ g->ray->plane_y * cos(rotspeed);
	g->has_moved = 1;
}

int	check_doors(t_game *g, int x, int y)
{
	if (g->doors[x][y] && g->doors[x][y] == 'P')
	{
		if (g->map[x][y] == 'P')
			g->map[x][y] = '0';
		else
			g->map[x][y] = 'P';
		g->has_moved = 1;
		return (1);
	}
	return (0);
}

void	open_doors(t_game *g)
{
	int	x;
	int	y;

	x = g->ray->pos_x;
	y = g->ray->pos_y;
	g->open = 0;
	if (check_doors(g, x + 1, y))
		return ;
	else if (check_doors(g, x - 1, y))
		return ;
	else if (check_doors(g, x, y + 1))
		return ;
	else if (check_doors(g, x, y - 1))
		return ;
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
	if (g->open == 1)
		open_doors(g);
	if (g->has_moved == 1)
	{
		render(g);
		g->has_moved = 0;
	}
	static int debug = 0;
	if (++debug == 20000)
	{
		++g->actual_anim;
		if (g->actual_anim == PET + 3)
			g->actual_anim = PET;
		render(g);
		printf("POS JOUEUR : %lf %lf\n", g->ray->pos_x, g->ray->pos_y);
		printf("ROTA JOUEUR : %lf %lf\n", g->ray->dir_x, g->ray->dir_y);
		debug = 0;
	}




	minimap(g); //last
	return (0);
}
