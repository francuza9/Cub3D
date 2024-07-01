/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwadie-a <jwadie-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 23:55:29 by jwadie-a          #+#    #+#             */
/*   Updated: 2024/05/30 17:27:44 by jwadie-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

static void		remove_leading_spaces(char **new_map, size_t max_offset);
static void		add_trailing_spaces(char **new_map, size_t max_len);
static size_t	get_true_len(char *line);
static size_t	get_max_offset(char **map);

void	normalize_map(t_data *game, char **map)
{
	size_t	max_offset;
	size_t	max_len;
	int		i;

	game->map = copy_array(map);
	if (game->map == NULL)
		exit_code(game, MALLOC_ERR, NULL);
	max_offset = get_max_offset(game->map);
	max_len = 0;
	i = -1;
	while (game->map[++i])
		if (get_true_len(game->map[i]) > max_len)
			max_len = get_true_len(game->map[i]);
	game->map_height = i;
	game->map_width = max_len - max_offset;
	if (game->map_width > MAX_WIDTH || game->map_height > MAX_HEIGHT)
		exit_code(game, TOO_LARGE_ERR, NULL);
	if (BONUS && (game->map_width > MINI_MAX_WIDTH || \
	game->map_height > MINI_MAX_HEIGHT))
		game->too_large = true;
	else
		game->too_large = false;
	remove_leading_spaces(game->map, max_offset);
	add_trailing_spaces(game->map, max_len - max_offset);
}

static void	remove_leading_spaces(char **new_map, size_t max_offset)
{
	char	*buffer;
	int		j;

	if (max_offset == 0)
		return ;
	j = 0;
	while (new_map[j])
	{
		buffer = ft_substr(new_map[j], max_offset, \
		ft_strlen(new_map[j]) - max_offset);
		if (!buffer)
			return ;
		free(new_map[j]);
		new_map[j] = buffer;
		j++;
	}
}

static void	add_trailing_spaces(char **new_map, size_t max_len)
{
	char	*buffer;
	int		len;
	int		j;
	size_t	i;

	j = 0;
	while (new_map[j])
	{
		buffer = ft_calloc(sizeof(char), max_len + 1);
		if (!buffer)
			return ;
		len = get_true_len(new_map[j]);
		ft_strlcat(buffer, new_map[j], len + 1);
		i = len;
		while (i < max_len)
		{
			buffer[i] = ' ';
			i++;
		}
		free(new_map[j]);
		new_map[j] = buffer;
		j++;
	}
}

static size_t	get_true_len(char *line)
{
	size_t	i;
	size_t	len;

	len = ft_strlen(line);
	i = 0;
	while (len > i && line[len - i - 1] == ' ')
		i++;
	return (len - i);
}

static size_t	get_max_offset(char **map)
{
	size_t	i;
	size_t	j;
	size_t	max_offset;

	max_offset = 0;
	while (map[0][max_offset] == ' ')
		max_offset++;
	j = 1;
	while (map[j])
	{
		if (is_empty_line(map[j]))
		{
			j++;
			continue ;
		}
		if (max_offset == 0)
			return (0);
		i = 0;
		while (map[j][i] == ' ')
			i++;
		if (i < max_offset)
			max_offset = i;
		j++;
	}
	return (max_offset);
}
