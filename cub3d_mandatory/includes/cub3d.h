/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cscache <cscache@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 18:39:49 by cscache           #+#    #+#             */
/*   Updated: 2025/11/03 20:45:43 by cscache          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

/* ************************************************************************** */
/*                              INCLUDES                                      */
/* ************************************************************************** */

# include <stdlib.h>
# include <math.h>
# include <fcntl.h>
# include <errno.h>
# include <stdio.h>
# include <unistd.h>
# include <math.h>
# include <limits.h>
# include <stdbool.h>
# include "../minilibx-linux/mlx.h"
# include "../libft/libft.h"

/* ************************************************************************** */
/*                         CONSTANTS & MACROS                                 */
/* ************************************************************************** */

/* Window and game settings */
# define SCREEN_WIDTH 1200
# define SCREEN_HEIGHT 800
# define TILE_SIZE 64
# define FOV 1.0471975512

/* Maths constant */
# ifndef M_PI
#  define M_PI 3.14159265358979323846
# endif

/* Keyboard keys */
# define KEY_W 119
# define KEY_S 115
# define KEY_D 100
# define KEY_A 97
# define KEY_RIGHT 65363
# define KEY_LEFT 65361
# define KEY_ESC 65307
# define KEY_Q 113

/* ************************************************************************** */
/*                             GAME STRUCTS                                   */
/* ************************************************************************** */

typedef struct s_point_d
{
	double	x;
	double	y;
}	t_point_d;

typedef struct s_point_i
{
	int	x;
	int	y;
}	t_point_i;

typedef enum e_direction {
	NORTH,
	SOUTH,
	EAST,
	WEST,
}	t_direction;

typedef struct s_keys {
	int	w;
	int	s;
	int	a;
	int	d;
	int	quit;
	int	left;
	int	right;
}	t_keys;

typedef struct s_color {
	int	floor;
	int	ceiling;
}	t_color;

typedef struct s_img {
	void	*ptr;
	char	*addr;
	int		bits_per_px;
	int		size_line;
	int		endian;
	int		width;
	int		height;
}	t_img;

typedef struct s_config {
	char	**map;
	int		map_width;
	int		map_height;
	char	*texture_paths[4];
	t_img	textures[4];
	t_color	colors;
}	t_config;

typedef struct s_player {
	t_point_i	tile;
	t_point_d	pos;
	char		dir;
	double		pa;
	double		move_speed;
	double		rot_speed;
}	t_player;

typedef struct s_wall_infos {
	double		wall_height;
	double		wall_top;
	double		wall_bottom;
	t_direction	wall_dir;
	double		wall_col;
	t_point_i	tex;
	double		tex_pos;
	char		*tex_px;
	double		step;
}	t_wall_infos;

typedef struct s_ray_params {
	t_point_d	ray_hit;
	t_point_d	step;
	t_point_i	map;
	bool		found_wall;
	double		distance;
}	t_ray_params;

typedef struct s_mlx {
	void	*ptr;
	void	*win_ptr;
	t_img	img_game;
}	t_mlx;

typedef struct s_global
{
	t_config		config;
	t_mlx			mlx;
	t_keys			key;
	t_player		player;
	t_ray_params	params;
	t_wall_infos	infos;
}	t_global;

#endif
