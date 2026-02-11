/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cscache <cscache@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 18:39:49 by cscache           #+#    #+#             */
/*   Updated: 2025/11/06 10:09:44 by bsuger           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_BONUS_H
# define CUB3D_BONUS_H

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
# include <sys/time.h>
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
# define MAX_DOORS 16
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
# define KEY_SPACE 32

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
	WEST
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

typedef enum e_door_state {
	CLOSED = 0,
	OPENED = 1,
	HIDDEN = 2,
	PORTAL_ACTIVE = 3,
}	t_door_state;

typedef struct s_door {
	int				index;
	t_point_i		tile;
	bool			is_open;
	bool			is_portal;
	long long		open_time;
	int				curr_frame;
	t_door_state	state;
}	t_door;

typedef struct s_door_textures {
	t_img	closed;
	t_img	open_frame[4];
	int		frame_nb;
}	t_door_textures;

typedef struct s_config {
	char			**map;
	int				map_width;
	int				map_height;
	char			*texture_paths[4];
	t_img			wall_textures[4];
	t_door_textures	door_textures;
	int				doors_nb;
	t_door			doors[MAX_DOORS];
	t_color			colors;
}	t_config;

typedef struct s_player {
	t_point_i	tile;
	t_point_d	pos;
	char		dir;
	double		pa;
	double		move_speed;
	double		rot_speed;
}	t_player;

typedef struct s_bresenham {
	t_point_i	start;
	t_point_i	end;
	t_point_i	delta;
	t_point_i	step;
	int			error;
	int			error_temp;
}	t_bresenham;

typedef struct s_texture {
	t_img		img;
	t_point_i	p;
	double		pos;
	char		*px;
	double		step;
}	t_texture;

typedef struct s_wall {
	double		height;
	double		top;
	double		bottom;
	t_direction	dir;
	double		col;
	t_texture	tex;
}	t_wall;

typedef struct s_ray_params {
	t_point_d	ray_hit;
	t_point_d	ray_dir;
	t_point_d	step;
	t_point_i	map;
	bool		found_wall;
	double		distance;
	bool		is_door;
}	t_ray_params;

typedef struct s_minimap_clip {
	t_point_d	delta;
	double		dir[4];
	double		dist[4];
	double		t_in;
	double		t_out;
}	t_minimap_clip;

typedef struct s_minimap {
	int					scale;
	t_point_i			pixel;
	t_point_i			offset;
	int					visible_width;
	int					visible_height;
	int					start_row;
	int					start_col;
}	t_minimap;

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
	t_wall			wall;
}	t_global;

#endif
