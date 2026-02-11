/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_bonus.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cscache <cscache@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/10 14:08:30 by cscache           #+#    #+#             */
/*   Updated: 2025/11/03 20:34:29 by cscache          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GAME_BONUS_H
# define GAME_BONUS_H

# include "cub3d_bonus.h"

/* config */
void		display_error_message(char *message);

/* init */
void		check_img_error(t_global *game, t_img *img_ptr);
void		get_img_data(t_img *img);
void		load_texture(t_global *game, t_img *img, char *path);
void		init_ray_params(t_ray_params *params);
void		init_imgs(t_global *game);
void		init_game(t_global *game);

/* keys */
int			key_press(int keycode, void *param);
int			key_release(int keycode, void *param);
int			close_window(void *param);

/* moves */
void		move_forward(t_global *game);
void		move_backward(t_global *game);
void		move_left(t_global *game);
void		move_right(t_global *game);
void		rotate_right(t_global *game);
void		rotate_left(t_global *game);
int			mouse_move(int x, int y, t_global *game);
void		update_player(t_global *game);
void		normalize_angle(double angle);

/* raycasting */
void		get_distance(t_global *game, double ray_angle, \
							t_ray_params *params);

/* display */
void		put_pixel_to_img(t_img *img, int x, int y, int color);
void		init_texture(t_global *game);
int			get_texture_color(t_img *tex, t_wall *wall);
void		set_wall_infos(t_global *game, double ray_angle);
void		display_game(t_global *game);
int			render(t_global *game);
void		run_game(t_global *game);

/* minimap */
bool		clip_ray(t_minimap *mini, t_point_d *start, t_point_d *end);
void		cast_all_rays_minimap(t_global *game, t_minimap *mini);
void		display_minimap(t_global *game);

/* door */
long long	get_timestamp_in_ms(void);
t_door		*get_door(t_global *game, int x, int y);
bool		is_valid_door(t_global *game, int x, int y);
bool		is_player_in_door_tile(t_global *game);
void		teleport_player(int door_idx, t_global *game);
void		try_open_door(t_global *game);
void		update_doors(t_global *game);

/* clean */
void		destructor_game(t_global *game);
void		clean_exit(t_global *game, int exit_code);

#endif 