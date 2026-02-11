/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_game_utils_bonus.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cscache <cscache@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/25 15:33:26 by cscache           #+#    #+#             */
/*   Updated: 2025/11/03 13:45:02 by cscache          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"
#include "game_bonus.h"
#include "parsing_bonus.h"

void	put_pixel_to_img(t_img *img, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || y < 0 || x >= SCREEN_WIDTH || y >= SCREEN_HEIGHT)
		return ;
	dst = img->addr + (y * img->size_line + x * (img->bits_per_px / 8));
	*(unsigned int *)dst = color;
}

void	init_texture(t_global *game)
{
	t_wall	*wall;

	wall = &game->wall;
	if (wall->dir == NORTH || wall->dir == SOUTH)
		wall->col = fmod(game->params.ray_hit.x, TILE_SIZE);
	else
		wall->col = fmod(game->params.ray_hit.y, TILE_SIZE);
	wall->tex.p.x = (int)(wall->col * wall->tex.img.width / TILE_SIZE);
	wall->tex.step = (double)wall->tex.img.height / wall->height;
	wall->tex.pos = (wall->top - SCREEN_HEIGHT / 2 + \
					wall->height / 2) * wall->tex.step;
}

int	get_texture_color(t_img *tex, t_wall *wall)
{
	char	*tex_px;
	int		color;

	wall->tex.p.y = (int)wall->tex.pos % tex->height;
	if (wall->tex.p.y < 0)
		wall->tex.p.y = 0;
	if (wall->tex.p.y >= tex->height)
		wall->tex.p.y = tex->height - 1;
	tex_px = tex->addr + (wall->tex.p.y * tex->size_line + \
			wall->tex.p.x * (tex->bits_per_px / 8));
	color = *(unsigned int *)tex_px;
	return (color);
}

void	set_wall_infos(t_global *game, double ray_angle)
{
	double	corrected_dist;
	double	proj_plane_dist;

	corrected_dist = game->params.distance * cos(game->player.pa - ray_angle);
	proj_plane_dist = (SCREEN_WIDTH / 2) / tan(FOV / 2);
	game->wall.height = (TILE_SIZE / corrected_dist) * proj_plane_dist;
	game->wall.top = (SCREEN_HEIGHT / 2) - (game->wall.height / 2);
	game->wall.bottom = (SCREEN_HEIGHT / 2) + \
							(game->wall.height / 2);
	if (game->wall.top < 0)
		game->wall.top = 0;
	if (game->wall.bottom > SCREEN_HEIGHT)
		game->wall.bottom = SCREEN_HEIGHT;
}
