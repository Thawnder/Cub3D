/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldeville <ldeville@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 14:31:40 by bpleutin          #+#    #+#             */
/*   Updated: 2023/11/22 10:13:02 by ldeville         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common.h"

void	go_forward(t_game *g)
{
	if (g->map[(int)(g->ray->pos_x + g->ray->dir_x * MS)]
		[(int)(g->ray->pos_y)] == '0')
		g->ray->pos_x += g->ray->dir_x * MS;
	if (g->map[(int)(g->ray->pos_x)]
		[(int)(g->ray->pos_y + g->ray->dir_y * MS)] == '0')
		g->ray->pos_y += g->ray->dir_y * MS;
	g->has_moved = 1;
}

void	go_backward(t_game *g)
{
	if (g->map[(int)(g->ray->pos_x - g->ray->dir_x * MS)]
		[(int)(g->ray->pos_y)] == '0')
		g->ray->pos_x -= g->ray->dir_x * MS;
	if (g->map[(int)(g->ray->pos_x)]
		[(int)(g->ray->pos_y - g->ray->dir_y * MS)] == '0')
		g->ray->pos_y -= g->ray->dir_y * MS;
	g->has_moved = 1;
}

int	mouse_interact(int x, int y, t_game *g)
{
	int	mid_x;

	(void)y;
	mid_x = SCREENWIDTH / 2;
	if (g->mouse_input == 1)
	{
		mlx_mouse_hide(g->mlx, g->win);
		if (x == mid_x)
			return (0);
		else if (x < mid_x)
			g->cleft = 1;
		else if (x > mid_x)
			g->cright = 1;
		g->mouse = 1;
		mlx_mouse_move(g->mlx, g->win, SCREENWIDTH / 2, SCREENHEIGHT / 2);
	}
	else
		mlx_mouse_show(g->mlx, g->win);
	return (0);
}

int	key_press(int keycode, t_game *game)
{
	if (keycode == ESC && ++game->end > 0)
		return (free_all(game), exit(EXIT_SUCCESS), 0);
	else if (keycode == W || keycode == UP)
		game->forward = 1;
	else if (keycode == S || keycode == DOWN)
		game->backward = 1;
	else if (keycode == A)
		game->left = 1;
	else if (keycode == D)
		game->right = 1;
	else if (keycode == LEFT)
		game->cleft = 1;
	else if (keycode == RIGHT)
		game->cright = 1;
	else if (keycode == SPACE)
		game->open = 1;
	else if (keycode == Q)
		game->mouse_input *= -1;
	return (0);
}

int	key_release(int keycode, t_game *game)
{
	if (keycode == W || keycode == UP)
		game->forward = 0;
	else if (keycode == S || keycode == DOWN)
		game->backward = 0;
	else if (keycode == A)
		game->left = 0;
	else if (keycode == D)
		game->right = 0;
	else if (keycode == LEFT)
		game->cleft = 0;
	else if (keycode == RIGHT)
		game->cright = 0;
	return (0);
}
