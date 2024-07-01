/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_textures_1.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtskitis <gtskitis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 20:05:09 by jwadie-a          #+#    #+#             */
/*   Updated: 2024/05/26 02:35:53 by gtskitis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

static bool	is_identifier(char *line, bool **found_ids, bool *is_repeat_id);
static bool	found_all_ids(bool *found_ids);
static bool	is_map_line(char *line);

int	check_texture_ids(t_data *game)
{
	int		i;
	bool	*found_ids;
	bool	is_repeat_id;

	found_ids = (bool[6]){false, false, false, false, false, false};
	is_repeat_id = false;
	i = -1;
	while (game->map_file[++i])
	{
		if (is_empty_line(game->map_file[i]))
			continue ;
		if (found_all_ids(found_ids) || is_map_line(game->map_file[i]))
			break ;
		if (!is_identifier(ft_strtrim(game->map_file[i], SPACE_CHARS), \
		&found_ids, &is_repeat_id))
			handle_error(game, i, ID_NOT_FOUND_ERR);
		if (is_repeat_id)
			handle_error(game, i, DUPLICATE_ID_ERR);
	}
	if (!found_all_ids(found_ids))
		exit_code(game, MISSING_ID_ERR, NULL);
	return (i);
}

static bool	is_identifier(char *line, bool **found_ids, bool *is_repeat_id)
{
	char	**identifiers;
	int		i;

	identifiers = (char *[6]){"NO", "SO", "WE", "EA", "F", "C"};
	if (line == NULL)
		return (false);
	i = 0;
	while (i < 6)
	{
		if (!ft_strncmp(identifiers[i], line, ft_strlen(identifiers[i])) && \
		(ft_strchr(BLANK_CHARS, line[ft_strlen(identifiers[i])]) || \
		line[ft_strlen(identifiers[i])] == '\0'))
		{
			if ((*found_ids)[i] == true)
				*is_repeat_id = true;
			(*found_ids)[i] = true;
			free(line);
			return (true);
		}
		i++;
	}
	free(line);
	return (false);
}

static bool	found_all_ids(bool *found_ids)
{
	int	i;

	i = 0;
	while (i < 6)
	{
		if (found_ids[i] == false)
			return (false);
		i++;
	}
	return (true);
}

static bool	is_map_line(char *line)
{
	char	*trimmed;
	bool	flag;

	flag = false;
	if (ft_strchr(line, 'W') && !ft_strncmp(ft_strchr(line, 'W'), "WE", 2))
		return (false);
	trimmed = ft_strtrim(line, COMPONENTS);
	if (!trimmed)
		return (false);
	if (!trimmed[0])
		flag = true;
	free(trimmed);
	return (flag);
}
