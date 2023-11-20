/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldeville <ldeville@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 14:31:40 by bpleutin          #+#    #+#             */
/*   Updated: 2023/11/20 13:43:07 by ldeville         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common.h"

void	go_left(t_game *g)
{
	if (g->map[(int)(g->ray->pos_x - g->ray->dir_y * MS)]
		[(int)(g->ray->pos_y)] == '0')
		g->ray->pos_x -= g->ray->dir_y * MS;
	if (g->map[(int)(g->ray->pos_x)]
		[(int)(g->ray->pos_y + g->ray->dir_x * MS)] == '0')
		g->ray->pos_y += g->ray->dir_x * MS; 
	g->has_moved = 1;
}

void	go_right(t_game *g)
{
	if (g->map[(int)(g->ray->pos_x + g->ray->dir_y * MS)]
		[(int)(g->ray->pos_y)] == '0')
		g->ray->pos_x += g->ray->dir_y * MS;
	if (g->map[(int)(g->ray->pos_x)]
		[(int)(g->ray->pos_y - g->ray->dir_x * MS)] == '0')
		g->ray->pos_y -= g->ray->dir_x * MS; 
	g->has_moved = 1;
}
