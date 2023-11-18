/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldeville <ldeville@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 10:47:29 by ldeville          #+#    #+#             */
/*   Updated: 2023/11/17 19:56:24 by ldeville         ###   ########.fr       */
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
	if (!parsing(argc, argv, game))
		return (free_all(game), EXIT_FAILURE);
	game->mlx = mlx_init();
	if (game->mlx == NULL)
		return (ft_printf("Error\nMLX is null.\n"), EXIT_FAILURE);
	game->win = mlx_new_window(game->mlx, SCREENWIDTH, SCREENHEIGHT, "cub3d");
	if (game->win == NULL)
		return (ft_printf("Error\nWIN is null.\n"), EXIT_FAILURE);
	if (!parsing_2(game))
		return (free_all(game), EXIT_FAILURE);
	render(game);
	// mlx_mouse_hide(game->mlx, game->win);
	mlx_hook(game->win, 2, (1L << 0), &key_press, game);
	mlx_hook(game->win, 3, (1L << 1), &key_release, game);
	mlx_hook(game->win, 6, (1L << 6), &mouse_interact, game);
	mlx_hook(game->win, 17, 0, &ft_close, game);
	mlx_loop_hook(game->mlx, &update, game);
	mlx_loop(game->mlx);
	free_all(game);
	return (0);
}
