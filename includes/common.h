/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   common.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldeville <ldeville@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 10:46:35 by ldeville          #+#    #+#             */
/*   Updated: 2023/11/16 17:20:46 by ldeville         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMON_H
# define COMMON_H

# include "Libft/libft.h"
# include "minilibx-linux/mlx.h"
# include "minilibx-linux/mlx_int.h"
# include <string.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <math.h>
# include <stdint.h>

# define SCREENWIDTH 640
# define SCREENHEIGHT 480
# define TEXWIDTH 64
# define TEXHEIGHT 64
# define MAPWIDTH 24
# define MAPHEIGHT 24
# define ESC 65307
# define W 11
# define A 97
# define S 115
# define D 100
# define UP 65362
# define LEFT 65361
# define DOWN 65364
# define RIGHT 65363

# define NO 0
# define SO 1
# define WE 2
# define EA 3
# define FLOOR 0
# define CEILING 1


typedef struct s_data
{
	void	*ptr;
	char	*addr;
	int		bpp;
	int		length;
	int		x;
	int		y;
	int		endian;
}				t_data;

typedef struct s_game
{
	void		*mlx;
	void		*win;
	char		**map;
	char		**tex;
	int			rgb[2][3];
	t_data		*img;
	int			lm;
	int			idx[2];
	int			end;
	int			forward;
	int			backward;
	int			left;
	int			right;
}				t_game;

//int32_t	g_buffer[SCREENHEIGHT][SCREENWIDTH];

/*	parsing.c	*/
int		parsing(int argc, char** argv, t_game *game);

/*	parsing2.c	*/
int		set_map(int file, char *nfile, t_game *g);
int		parsing_2(t_game *game);

/*	check.c	*/
int		check_map(t_game *g);

/*	utils.c	*/
int		space_until(char *str);
void	set_line(t_game *g, char *line, int y);
char*	set_sized_line(char *tmp, char *old, int max);
int		ft_ylen(char **map);
char	*delete_endl(char *str);

/*	movement.c	*/
int		key_release(int keycode, t_game *game);
int		key_press(int keycode, t_game *game);
int		update_pos(t_game *game);

/*	texture.c	*/
int		try_texture(t_game *g);
int		add_texture(t_game *g);

/*	update.c	*/
int		update(t_game *game);

/*	minimap.c	*/
void	minimap(t_game *g);

/*	free.c	*/
void	free_map(t_game *g);
void	free_all(t_game *g);

#endif