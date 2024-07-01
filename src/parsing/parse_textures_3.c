/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_textures_3.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtskitis <gtskitis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 21:53:45 by jwadie-a          #+#    #+#             */
/*   Updated: 2024/05/27 02:40:05 by gtskitis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

static int	check_extension(char *path);
static int	get_sprites(t_data *game, char **split, int texture_id);

int	get_texture_path(t_data *game, char *line, int texture_id)
{
	char	**split;
	int		err_code;

	if (!line[0])
		return (ID_NOT_SPEC_ERR);
	split = ft_split2(line, false);
	if (!split)
		return (MALLOC_ERR);
	err_code = NO_ERROR;
	if (BONUS)
		err_code = get_sprites(game, split, texture_id);
	else
	{
		if (split[1])
			err_code = SPACE_IN_PATH_ERR;
		game->texture_paths[texture_id] = ft_strdup(split[0]);
		if (!err_code)
			err_code = check_extension(game->texture_paths[texture_id]);
	}
	free_2d(split);
	return (err_code);
}

static int	check_extension(char *path)
{
	char	*ext;

	if (!path)
		return (MALLOC_ERR);
	ext = ft_strrchr(path, '.');
	if (ft_strlen(ext) != 4 || ft_strncmp(ext, ".xpm", 4))
		return (EXT_NOT_XPM_ERR);
	else
		return (NO_ERROR);
}

static int	get_sprites(t_data *game, char **split, int texture_id)
{
	int		i;
	int		err_code;
	int		index;

	i = -1;
	while (++i < NUM_OF_SPRITES)
		if (!split[i])
			return (TOO_FEW_PATH_ERR);
	if (split[i])
		return (TOO_MANY_PATH_ERR);
	err_code = NO_ERROR;
	i = 0;
	while (i < NUM_OF_SPRITES)
	{
		index = texture_id * NUM_OF_SPRITES + i;
		game->texture_paths[index] = ft_strdup(split[i]);
		err_code = check_extension(game->texture_paths[index]);
		if (err_code)
			break ;
		i++;
	}
	return (err_code);
}
