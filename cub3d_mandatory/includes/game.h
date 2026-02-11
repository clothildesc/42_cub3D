/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cscache <cscache@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/10 14:08:30 by cscache           #+#    #+#             */
/*   Updated: 2025/11/03 20:45:39 by cscache          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GAME_H
# define GAME_H

# include "cub3d.h"

/* config */
void	display_error_message(char *message);

/* init */
void	init_ray_params(t_ray_params *params);
void	init_imgs(t_global *game);
void	init_game(t_global *game);

/* keys */
int		key_press(int keycode, void *param);
int		key_release(int keycode, void *param);
int		close_window(void *param);

/* moves */
void	move_forward(t_global *game);
void	move_backward(t_global *game);
void	move_left(t_global *game);
void	move_right(t_global *game);
void	rotate_right(t_global *game);
void	rotate_left(t_global *game);
void	update_player(t_global *game);

/* raycasting */
void	get_distance(t_global *game, double ray_angle, t_ray_params *params);

/* display */
void	put_pixel_to_img(t_img *img, int x, int y, int color);
void	init_wall_texture(t_global *game);
int		get_texture_color(t_img *tex, t_wall_infos *i);
void	set_wall_infos(t_global *game, double ray_angle);
void	display_game(t_global *game);
void	run_game(t_global *game);

/* clean */
void	destructor_game(t_global *game);
void	clean_exit(t_global *game, int exit_code);

#endif 