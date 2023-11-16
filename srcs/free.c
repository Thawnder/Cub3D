/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldeville <ldeville@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 12:34:18 by ldeville          #+#    #+#             */
/*   Updated: 2023/11/15 16:13:49 by ldeville         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common.h"

void	free_map(t_game *g)
{
	int	i;

	i = 0;
	while (g->map[i][0])
		free(g->map[i++]);
	free(g->map[i]);
	free(g->map);
}

void	free_all(t_game *g)
{
	int	i;

	i = 0;
	if (g->tex)
	{
		while (i < 4)
			free(g->tex[i++]);
		free(g->tex);
	}
	if (g->map)
		free_map(g);
	free(g);
}