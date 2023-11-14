/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   common.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldeville <ldeville@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 10:46:35 by ldeville          #+#    #+#             */
/*   Updated: 2023/11/14 17:16:17 by ldeville         ###   ########.fr       */
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
	t_data		**img;
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
int		parsing(int argc, char** argv);

/*	movement.c	*/
int		key_release(int keycode, t_game *game);
int		key_press(int keycode, t_game *game);
int		update_pos(t_game *game);

#endif