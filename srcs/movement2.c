/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldeville <ldeville@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 14:31:40 by bpleutin          #+#    #+#             */
/*   Updated: 2023/11/22 10:16:30 by ldeville         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common.h"

int	other_infos(char *line, char *cmp)
{
	int	i;

	i = -1;
	while (line[++i] && line[i] != '\n')
	{
		if (line[i] < '0' || line[i] > '9')
			return (printf("Error\nProblem with element '%s' while parsing\n"
					, cmp), 1);
	}
	return (0);
}

int	is_double(char *line, char *cmp, int file, int size)
{
	printf("LINE :%s CMP :%s\n", line, cmp);
	free(line);
	line = get_next_line(file);
	while (line && strncmp(line, cmp, size))
	{
		free(line);
		line = get_next_line(file);
	}
	if (line)
		return (close(file), free(line),
			printf("Error\nProblem with element '%s' while parsing\n", cmp), 1);
	return (0);
}

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
