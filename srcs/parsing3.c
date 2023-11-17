/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldeville <ldeville@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 13:31:57 by ldeville          #+#    #+#             */
/*   Updated: 2023/11/17 13:37:06 by ldeville         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common.h"

void	set_orientation_2(t_game *g, char c)
{
	if (c == 'W')
	{
		g->ray->dir_x = -1;
		g->ray->dir_y = 0;
		g->ray->plane_x = 0;
		g->ray->plane_y = -0.66;
	}
	else if (c == 'E')
	{
		g->ray->dir_x = 1;
		g->ray->dir_y = 0;
		g->ray->plane_x = 0;
		g->ray->plane_y = 0.66;
	}
}

void	set_orientation(t_game *g, char c)
{
	if (c == 'S')
	{
		g->ray->dir_x = 0;
		g->ray->dir_y = 1;
		g->ray->plane_x = -0.66;
		g->ray->plane_y = 0;
	}
	else if (c == 'N')
	{
		g->ray->dir_x = 0;
		g->ray->dir_y = -1;
		g->ray->plane_x = 0.66;
		g->ray->plane_y = 0;
	}
	else
		set_orientation_2(g, c);
}
