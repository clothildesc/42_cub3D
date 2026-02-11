/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_game_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cscache <cscache@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/25 15:33:26 by cscache           #+#    #+#             */
/*   Updated: 2025/10/25 15:43:41 by cscache          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "game.h"
#include "parsing.h"

void	put_pixel_to_img(t_img *img, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || y < 0 || x >= SCREEN_WIDTH || y >= SCREEN_HEIGHT)
		return ;
	dst = img->addr + (y * img->size_line + x * (img->bits_per_px / 8));
	*(unsigned int *)dst = color;
}

void	init_wall_texture(t_global *game)
{
	t_wall_infos	*i;
	t_img			tex;

	i = &game->infos;
	tex = game->config.textures[i->wall_dir];
	if (i->wall_dir == NORTH || i->wall_dir == SOUTH)
		i->wall_col = fmod(game->params.ray_hit.x, TILE_SIZE);
	else
		i->wall_col = fmod(game->params.ray_hit.y, TILE_SIZE);
	i->tex.x = (int)(i->wall_col * tex.width / TILE_SIZE);
	i->step = (double)tex.height / i->wall_height;
	i->tex_pos = (i->wall_top - SCREEN_HEIGHT / 2 + \
					i->wall_height / 2) * i->step;
}

int	get_texture_color(t_img *tex, t_wall_infos *i)
{
	char	*tex_px;
	int		color;

	i->tex.y = (int)i->tex_pos % tex->height;
	if (i->tex.y < 0)
		i->tex.y = 0;
	if (i->tex.y >= tex->height)
		i->tex.y = tex->height - 1;
	tex_px = tex->addr + (i->tex.y * tex->size_line + \
			i->tex.x * (tex->bits_per_px / 8));
	color = *(unsigned int *)tex_px;
	return (color);
}

void	set_wall_infos(t_global *game, double ray_angle)
{
	double	corrected_dist;
	double	proj_plane_dist;

	corrected_dist = game->params.distance * cos(game->player.pa - ray_angle);
	proj_plane_dist = (SCREEN_WIDTH / 2) / tan(FOV / 2);
	game->infos.wall_height = (TILE_SIZE / corrected_dist) * proj_plane_dist;
	game->infos.wall_top = (SCREEN_HEIGHT / 2) - (game->infos.wall_height / 2);
	game->infos.wall_bottom = (SCREEN_HEIGHT / 2) + \
							(game->infos.wall_height / 2);
	if (game->infos.wall_top < 0)
		game->infos.wall_top = 0;
	if (game->infos.wall_bottom > SCREEN_HEIGHT)
		game->infos.wall_bottom = SCREEN_HEIGHT;
}
