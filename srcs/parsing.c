/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldeville <ldeville@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 15:35:15 by ldeville          #+#    #+#             */
/*   Updated: 2023/11/14 16:25:59 by ldeville         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common.h"

int	setMap(int file)
{
	(void)file;
	return (1);
	
}

int	parsing(int argc, char **argv)
{
	int	file;

	if (argc != 2)
		return (printf("Error\nEnter valid argument: ./cub3d <Map>.cub'\n"), 0);
	if (strcmp(&argv[1][ft_strlen(argv[1]) - 4], ".cub"))
		return (printf("Error\nPlease enter a '.cub' map'\n"), 0);
	file = open(argv[1], O_RDONLY);
	if (!file)
		return (printf("Error\nCould not open %s'\n", argv[1]), 0);
	/*if (!setMap(file))
		return (close(file), 0);*/
	return (1);
}
