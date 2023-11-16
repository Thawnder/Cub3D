/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldeville <ldeville@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 10:47:29 by ldeville          #+#    #+#             */
/*   Updated: 2023/11/16 15:42:02 by ldeville         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common.h"

static int	ft_close(t_game *g)
{
	free_all(g);
	exit(EXIT_SUCCESS);
	return (0);
}

int	main(int argc, char **argv)
{
	t_game	*game;

	game = ft_calloc(sizeof(t_game), 1);
	game->mlx = mlx_init();
	if (game->mlx == NULL)
		return (ft_printf("Error\nMLX is null.\n"), EXIT_FAILURE);
	game->win = mlx_new_window(game->mlx, 1920, 1080, "cub3d");
	if (game->win == NULL)
		return (ft_printf("Error\nWIN is null.\n"), EXIT_FAILURE);
	if (!parsing(argc, argv, game))
		return (free_all(game), EXIT_FAILURE);
	/*mlx_key_hook(game->win, 2, 1L << 0, &key_press, game);
	mlx_key_hook(game->win, 3, 1L << 1, &key_release, game);*/
	mlx_hook(game->win, 17, 0, &ft_close, game);

	mlx_put_image_to_window(game->mlx, game->win, game->img[0].ptr, 0, 0);
	mlx_put_image_to_window(game->mlx, game->win, game->img[1].ptr, 0, 64);
	mlx_put_image_to_window(game->mlx, game->win, game->img[2].ptr, 0, 128);
	mlx_put_image_to_window(game->mlx, game->win, game->img[3].ptr, 0, 192);

	mlx_loop_hook(game->mlx, &update, game);
	mlx_loop(game->mlx);
	free_all(game);
	return (0);
}
