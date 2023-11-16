/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldeville <ldeville@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 15:56:18 by ldeville          #+#    #+#             */
/*   Updated: 2023/11/16 14:08:22 by ldeville         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common.h"

char	*delete_endl(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != '\n')
		i++;
	while (str[i] && str[i] == '\n')
		str[i++] = 0;
	return (str);
}

int	ft_ylen(char **map)
{
	int	y;

	y = 0;
	while (map[y][0])
		y++;
	return (y);
}

int	space_until(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] == ' ')
		i++;
	return (i);
}

void	set_line(t_game *g, char *line, int y)
{
	int	i;

	i = 0;
	while (line[i] && line[i] != '\n')
	{
		g->map[y][i] = line[i];
		i++;
	}
	free(line);
}

char	*set_sized_line(char *tmp, char *old, int max)
{
	int	i;

	i = -1;
	while (old[++i])
		tmp[i] = old[i];
	while (i < max)
		tmp[i++] = ' ';
	return (free(old), tmp);
}
