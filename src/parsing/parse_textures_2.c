/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_textures_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtskitis <gtskitis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 00:25:02 by jwadie-a          #+#    #+#             */
/*   Updated: 2024/05/27 02:54:53 by gtskitis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

static int	which_id(char *line);

void	import_textures(t_data *game, int end)
{
	char	*trimmed;
	int		texture_id;
	int		err_code;
	int		i;

	err_code = 0;
	i = 0;
	while (i < end)
	{
		trimmed = ft_strtrim(game->map_file[i], SPACE_CHARS);
		texture_id = which_id(trimmed);
		if (texture_id == -1)
			exit_code(game, MALLOC_ERR, NULL);
		else if (texture_id == FLOOR)
			game->floor_clr = parse_color(trimmed + 1, &err_code);
		else if (texture_id == CEILING)
			game->ceiling_clr = parse_color(trimmed + 1, &err_code);
		else if (texture_id >= 0 && texture_id < 4 * NUM_OF_SPRITES)
			err_code = get_texture_path(game, trimmed + 2, texture_id);
		free(trimmed);
		if (err_code)
			handle_error(game, i, err_code);
		i++;
	}
}

static int	which_id(char *line)
{
	int		i;
	char	**identifiers;

	identifiers = (char *[6]){"NO", "SO", "WE", "EA", "F", "C"};
	if (line == NULL)
		return (-1);
	if (line[0] == 'F')
		return (FLOOR);
	if (line[0] == 'C')
		return (CEILING);
	i = 0;
	while (i < 4)
	{
		if (!ft_strncmp(identifiers[i], line, 2))
			return (i);
		i++;
	}
	return (-2);
}
