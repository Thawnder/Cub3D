/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpleutin <bpleutin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 14:31:40 by bpleutin          #+#    #+#             */
/*   Updated: 2023/11/14 16:23:56 by bpleutin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common.h"

void	camera_rotation(int rotSpeed) // a adapter
{
	double oldDirX = dirX;
    dirX = dirX * cos(rotSpeed) - dirY * sin(rotSpeed);
    dirY = oldDirX * sin(rotSpeed) + dirY * cos(rotSpeed);
    double oldPlaneX = planeX;
    planeX = planeX * cos(rotSpeed) - planeY * sin(rotSpeed);
    planeY = oldPlaneX * sin(rotSpeed) + planeY * cos(rotSpeed);
}

int	update_pos(t_game *game) // conditions a adapte
{
	if (game->end == 1)
		return (0);
	if (game->forward == 1)
	{
		if (worldMap[int(posX + dirX * moveSpeed)][int(posY)] == false)
			posX += dirX * moveSpeed;
    	if (worldMap[int(posX)][int(posY + dirY * moveSpeed)] == false)
			posY += dirY * moveSpeed;
	}
	if (game->backward == 1)
	{
		if (worldMap[int(posX - dirX * moveSpeed)][int(posY)] == false)
			posX -= dirX * moveSpeed;
    	if (worldMap[int(posX)][int(posY - dirY * moveSpeed)] == false)
			posY -= dirY * moveSpeed;
	}
	if (game->left == 1)
		camera_rotation(rotSpeed);
	if (game->right == 1)
		camera_rotation(-rotSpeed);
	return (0);
}

int	key_press(int keycode, t_game *game)
{
	if (keycode == ESC)
		shutdown(game);
	if (keycode == W || keycode == UP)
		game->forward = 1;
	if (keycode == S || keycode == DOWN)
		game->backward = 1;
	if (keycode == A || keycode == LEFT)
		game->left = 1;
	if (keycode == D || keycode == RIGHT)
		game->right = 1;
}

int	key_release(int keycode, t_game *game)
{
	if (keycode == ESC)
		shutdown(game);
	if (keycode == W || keycode == UP)
		game->forward = 0;
	if (keycode == S || keycode == DOWN)
		game->backward = 0;
	if (keycode == A || keycode == LEFT)
		game->left = 0;
	if (keycode == D || keycode == RIGHT)
		game->left = 0;
}