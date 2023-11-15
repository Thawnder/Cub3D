/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldeville <ldeville@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 15:56:18 by ldeville          #+#    #+#             */
/*   Updated: 2023/11/15 12:32:35 by ldeville         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common.h"

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
