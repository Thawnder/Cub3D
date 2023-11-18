/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldeville <ldeville@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 14:12:46 by ldeville          #+#    #+#             */
/*   Updated: 2023/11/18 13:31:13 by ldeville         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common.h"

int	try_texture(t_game *g)
{
	int	fd;
	int	i;

	fd = -1;
	i = -1;
	while (++i < 4)
	{
		fd = open(g->tex[i], O_RDONLY);
		if (fd == -1)
			return (printf("Error\nCan't open %s !\n", g->tex[i]), 0);
		close(fd);
		fd = -1;
	}
	return (1);
}

t_data	ft_add_img(t_game *g, char *path)
{
	t_data	img;

	if (!path[0])
	{
		img.ptr = NULL;
		img.addr = NULL;
		img.x = 0;
		img.y = 0;
		img.bpp = 0;
		img.length = 0;
		img.endian = 0;
	}
	else
	{
		img.ptr = mlx_xpm_file_to_image(g->mlx,
				path, &img.x, &img.y);
		img.addr = (int *)mlx_get_data_addr(img.ptr, &img.bpp,
				&img.length, &img.endian);
	}
	return (img);
}

int	add_texture(t_game *g)
{
	t_data	*img;

	img = malloc(sizeof(t_img) * (8 + 1));
	img[0] = ft_add_img(g, g->tex[0]);
	img[1] = ft_add_img(g, g->tex[1]);
	img[2] = ft_add_img(g, g->tex[2]);
	img[3] = ft_add_img(g, g->tex[3]);
	img[4] = ft_add_img(g, "./textures/doors.xpm");
	img[5] = ft_add_img(g, "./textures/cat1.xpm");
	img[6] = ft_add_img(g, "./textures/cat2.xpm");
	img[7] = ft_add_img(g, "./textures/cat3.xpm");
	img[8] = ft_add_img(g, "");
	g->img = img;
	return (1);
}