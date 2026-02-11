/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game_imgs_utils_bonus.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cscache <cscache@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 11:13:56 by cscache           #+#    #+#             */
/*   Updated: 2025/10/31 16:07:49 by cscache          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"
#include "game_bonus.h"
#include "parsing_bonus.h"

void	get_img_data(t_img *img)
{
	img->addr = mlx_get_data_addr(img->ptr, \
								&img->bits_per_px, \
								&img->size_line, \
								&img->endian);
}

void	check_img_error(t_global *game, t_img *img_ptr)
{
	if (!img_ptr)
	{
		display_error_message("Failed to load image");
		clean_exit(game, EXIT_FAILURE);
	}
}

void	load_texture(t_global *game, t_img *img, char *path)
{
	img->ptr = mlx_xpm_file_to_image(game->mlx.ptr, path, \
									&img->width, &img->height);
	check_img_error(game, img->ptr);
	get_img_data(img);
}
