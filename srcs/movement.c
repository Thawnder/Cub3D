/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpleutin <bpleutin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 14:31:40 by bpleutin          #+#    #+#             */
/*   Updated: 2023/11/16 11:17:59 by bpleutin         ###   ########.fr       */
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
}

void	go_backward(t_game *g)
{
	if (g->map[(int)(g->ray->pos_x - g->ray->dir_x * MS)]
		[(int)(g->ray->pos_y)] == '0')
		g->ray->pos_x -= g->ray->dir_x * MS;
	if (g->map[(int)(g->ray->pos_x)]
		[(int)(g->ray->pos_y - g->ray->dir_y * MS)] == '0')
		g->ray->pos_y -= g->ray->dir_y * MS;
}

int	key_press(int keycode, t_game *game)
{
	printf("KEY DOWN = %i\n", keycode);
	if (keycode == W || keycode == UP)
		game->forward = 1;
	else if (keycode == S || keycode == DOWN)
		game->backward = 1;
	else if (keycode == A || keycode == LEFT)
		game->left = 1;
	else if (keycode == D || keycode == RIGHT)
		game->right = 1;
	return (0);
}

int	key_release(int keycode, t_game *game)
{
	printf("KEY UP= %i\n", keycode);
	if (keycode == W || keycode == UP)
		game->forward = 0;
	else if (keycode == S || keycode == DOWN)
		game->backward = 0;
	else if (keycode == A || keycode == LEFT)
		game->left = 0;
	else if (keycode == D || keycode == RIGHT)
		game->left = 0;
	return (0);
}
