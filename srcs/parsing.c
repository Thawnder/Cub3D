/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldeville <ldeville@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 15:35:15 by ldeville          #+#    #+#             */
/*   Updated: 2023/11/27 17:54:35 by bpleutin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common.h"

static int	set_rgb(char *line, int id, char *cmp, t_game *g)
{
	int	i;

	i = 2;
	g->rgb[id][0] = atoi(&line[2]);
	while (line[i] && line[i - 1] != ',')
		i++;
	if (!line[i] || g->rgb[id][0] < 0 || g->rgb[id][0] > 255)
		return (free(line),
			printf("Error\nProblem with element '%s' while parsing\n", cmp), 0);
	g->rgb[id][1] = atoi(&line[i++]);
	while (line[i] && line[i - 1] != ',')
		i++;
	if (!line[i] || g->rgb[id][1] < 0 || g->rgb[id][1] > 255)
		return (free(line),
			printf("Error\nProblem with element '%s' while parsing\n", cmp), 0);
	g->rgb[id][2] = atoi(&line[i]);
	if (g->rgb[id][2] < 0 || g->rgb[id][2] > 255)
		return (free(line),
			printf("Error\nProblem with element '%s' while parsing\n", cmp), 0);
	if (other_infos(&line[i], cmp))
		return (free(line), 0);
	return (1);
}

static int	find_rgb(int file, char *cmp, int id, t_game *g)
{
	char	*line;

	line = get_next_line(file);
	while (line && ft_strncmp(line, cmp, 2))
	{
		free(line);
		line = get_next_line(file);
	}
	if (!line || ft_strncmp(line, cmp, 2))
		return (close(file), free(line),
			printf("Error\nCan't find element '%s' while parsing\n", cmp), 0);
	if (!set_rgb(line, id, cmp, g))
		return (close(file), 0);
	if (is_double(line, cmp, file, 2))
		return (0);
	return (1);
}

static int	find_element(int file, char *cmp, int id, t_game *g)
{
	char	*line;
	int		i;

	i = 2;
	line = get_next_line(file);
	while (line && ft_strncmp(line, cmp, 3))
	{
		free(line);
		line = get_next_line(file);
	}
	if (!line || ft_strncmp(line, cmp, 3))
		return (close(file), free(line),
			printf("Error\nCan't find element '%s' while parsing\n", cmp), 0);
	while (line[i] && line[i] == ' ')
		i++;
	printf("line: %s", &line[i]);
	if (!line[i] || ft_strcmp(&line[ft_strlen(line) - 5]
			, ".xpm\n") > 0)
		return (close(file), free(line),
			printf("Error\nProblem with element '%s' while parsing\n", cmp), 0);
	g->tex[id] = ft_strdup(delete_endl(&line[i]));
	if (is_double(line, cmp, file, 3))
		return (0);
	return (close(file), 1);
}

static int	do_parsing(int file, char *nfile, t_game *g)
{
	find_map(open(nfile, O_RDONLY), &g->parse_map);
	g->tex = ft_calloc(sizeof(char *), 4);
	if ((close(file) || !find_element(open(nfile, O_RDONLY), "NO ", NO, g))
		|| !find_element(open(nfile, O_RDONLY), "SO ", SO, g)
		|| !find_element(open(nfile, O_RDONLY), "WE ", WE, g)
		|| !find_element(open(nfile, O_RDONLY), "EA ", EA, g)
		|| !find_rgb(open(nfile, O_RDONLY), "F ", FLOOR, g)
		|| !find_rgb(open(nfile, O_RDONLY), "C ", CEILING, g)
		|| !try_texture(g)
		|| !set_map(open(nfile, O_RDONLY), nfile, g))
		return (0);
	return (1);
}

int	parsing(int argc, char **argv, t_game *game)
{
	int	file;

	if (argc != 2)
		return (printf("Error\nEnter valid argument: ./cub3d <Map>.cub'\n"), 0);
	if (ft_strcmp(&argv[1][ft_strlen(argv[1]) - 4], ".cub"))
		return (printf("Error\nPlease enter a '.cub' map'\n"), 0);
	file = open(argv[1], O_RDONLY);
	if (file == -1)
		return (printf("Error\nCould not open '%s'\n", argv[1]), 0);
	if (!do_parsing(file, argv[1], game))
		return (close(file), 0);
	if (!check_map(game))
		return (0);
	return (close(file), 1);
}
