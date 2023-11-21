/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   common.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpleutin <bpleutin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 10:46:35 by ldeville          #+#    #+#             */
/*   Updated: 2023/11/21 10:58:15 by bpleutin         ###   ########.fr       */
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
# include <limits.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <math.h>
# include <stdint.h>

# define SCREENWIDTH 1280
# define SCREENHEIGHT 720
# define TEXWIDTH 64
# define TEXHEIGHT 64
# define MAPWIDTH 24
# define MAPHEIGHT 24
# define PET 5
# define SPEED_ANIM 20000
# define ESC 65307
# define W 119
# define A 97
# define S 115
# define D 100
# define UP 65362
# define LEFT 65361
# define DOWN 65364
# define RIGHT 65363
# define SPACE 32

# define MS 0.045
# define RS 0.04

# define NO 0
# define SO 1
# define WE 2
# define EA 3
# define FLOOR 0
# define CEILING 1

typedef struct s_data
{
	void	*ptr;
	int		*addr;
	char	*addr2;
	int		bpp;
	int		length;
	int		x;
	int		y;
	int		endian;
}				t_data;

typedef struct s_ray
{
	double		camera_x;
	double		raydir_x;
	double		raydir_y;
	double		plane_x;
	double		plane_y;
	double		sidedist_x;
	double		sidedist_y;
	double		deltadist_x;
	double		deltadist_y;
	double		perpwalldist;
	double		wall_x;
	double		sprite_x;
	double		sprite_y;
	int			tex_num;
	int			tex_tmp;
	double		inv_det;
	double		transform_x;
	double		transform_y;
	int			sprite_screen_x;
	int			sprite_height;
	int			sprite_width;
	int			draw_start_y;
	int			draw_end_y;
	int			draw_start_x;
	int			draw_end_x;
	int			draw_start;
	int			draw_end;
	int			stripe;
	int			step_x;
	int			step_y;
	int			hit;
	int			side;
	int			line_height;
	double		step;
	double		pos_x;
	double		pos_y;
	double		dir_x;
	double		dir_y;
	int			map_x;
	int			map_y;
	int			tex_x;
	int			tex_y;
	double		tex_pos;
	int			color;
	double		*z_buffer;
}				t_ray;

typedef struct s_sprite
{
	double		x;
	double		y;
	double		distance;
}				t_sprite;

typedef struct s_game
{
	void			*mlx;
	void			*win;
	char			**map;
	char			**doors;
	char			**tex;
	t_sprite		*sprite;
	int				rgb[2][3];
	unsigned int	hex[2];
	int				has_moved;
	int				**buffer;
	int				actual_anim;
	t_data			*render;
	t_data			*img;
	t_ray			*ray;
	int				lm;
	int				idx[2];
	int				end;
	int				forward;
	int				backward;
	int				left;
	int				right;
	int				cleft;
	int				cright;
	int				open;
	int				y_len;
	int				x_len;
	int				parse_map;
	int				mouse;
}					t_game;

/*	parsing.c	*/
int		parsing(int argc, char **argv, t_game *game);

/*	parsing2.c	*/
void	set_sprite(int size, t_game *g);
int		find_map(int file, int *size);
int		set_map(int file, char *nfile, t_game *g);
int		parsing_2(t_game *g);

/*	parsing3.c	*/
void	doors_map(t_game *g);
void	rgb_to_hex(t_game *g);
void	set_orientation(t_game *g, char c);
void	debug(t_game *g);

/*	check.c	*/
int		check_map(t_game *g);

/*	utils.c	*/
int		space_until(char *str);
void	set_line(t_game *g, char *line, int y);
char	*set_sized_line(char *tmp, char *old, int max);
int		ft_ylen(char **map);
char	*delete_endl(char *str);

/*	movement.c	*/
void	go_forward(t_game *g);
void	go_backward(t_game *g);
int		mouse_interact(int x, int y, t_game *g);
int		key_release(int keycode, t_game *game);
int		key_press(int keycode, t_game *game);

/*	movement2.c	*/
void	go_left(t_game *g);
void	go_right(t_game *g);

/*	texture.c	*/
int		try_texture(t_game *g);
int		add_texture(t_game *g);

/*	update.c	*/
void	camera_rotation(t_game *g, double rotspeed);
int		update(t_game *g);

/*	render.c	*/
void	render(t_game *g);

/*	render2.c	*/
void	set_sidedist(t_game *g);
void	set_hit_texture(t_game *g);
void	set_draw_start_end(t_game *g);
void	set_buffer_color(t_game *g, int x);

/*	sprites.c	*/
void	render_sprites(t_game *g);

/*	minimap.c	*/
void	minimap(t_game *g);

/*	free.c	*/
void	free_map(t_game *g);
void	free_all(t_game *g);
void	ft_free_buffer(t_game *g);

#endif