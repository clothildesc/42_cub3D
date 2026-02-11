/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_bonus.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cscache <cscache@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 18:41:41 by cscache           #+#    #+#             */
/*   Updated: 2025/11/06 11:27:36 by bsuger           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_BONUS_H
# define PARSING_BONUS_H

# include "cub3d_bonus.h"
# include "game_bonus.h"

/*check extension*/
int		check_extension(char *arg, char *extension);
int		check_args(t_global *game, int argc, char **argv);

/*opening file*/
int		opening_file(char *file);
int		parsing_map(t_global *game, char *file);

/*RGB manipulation*/
int		rgb_reading(char **temp, int *rgb);
int		rgb_extract(t_global *game, int info, char *extract);
int		len(char **str);
int		rgb_comma_verification(char *extract);
int		rgb_trim(char **tab);
int		rgb_cursor(char *extract);
int		rgb_assignement(t_global *game, int info, int *rgb);

/*utils_parsing*/
int		check_overflow_underflow(char *str);
int		check_validity(char *str);
void	set_minus(t_global *game);
int		set_up_map(t_global *game);
void	update_space_n_player(t_global *game);

/*extracting map*/
int		extracting_map(t_global *game, char *line);
int		is_in(char c, char *sep);

/*line pass*/
int		is_empty(char *str);
int		line_pass_empty(char **line, int fd);
int		line_pass_nonempty(t_global *game, char **line, int fd);

/*map transformation*/
int		map_transformation(t_global *game);

/*validation_map*/
int		flood_fill(t_global *game, int row, int column);

/*bonus_part*/
int		check_doors(t_global *game);
int		check_textures(void);

#endif 
