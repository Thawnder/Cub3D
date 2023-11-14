/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpleutin <bpleutin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 10:47:29 by ldeville          #+#    #+#             */
/*   Updated: 2023/11/14 15:44:04 by bpleutin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common.h"

int	main(int argc, char **argv)
{
	(void)argc;
	(void)argv;
	t_game	*game;

	game = ft_calloc(sizeof(t_game), 1);
	game->mlx = mlx_init();
	if (game->mlx == NULL)
		print_error("Mlx is null.\n");
	/*
	after parsing
		*/
	if (game->win == NULL)
		print_error("Window is null.\n");
	mlx_key_hook(game->win, 2, &key_press, game);
	mlx_key_hook(game->win, 3, &key_release, game);
	return (0);
}