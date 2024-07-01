/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map_1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwadie-a <jwadie-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 00:44:05 by jwadie-a          #+#    #+#             */
/*   Updated: 2024/05/31 19:12:19 by jwadie-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

static bool	check_empty_line(t_data *game, int i);
static void	check_starting_pos(t_data *game, int start);
static void	check_separate_maps(t_data *game);
static void	flood_fill(char **map, int i, int j);

void	check_map(t_data *game, int start)
{
	int		i;
	char	*trimmed;
	int		err_code;

	if (!game->map_file[start])
		exit_code(game, NO_MAP_ERR, NULL);
	err_code = NO_ERROR;
	i = start;
	while (game->map_file[i])
	{
		if (check_empty_line(game, i))
			handle_error(game, i, EMPTY_LINE_ERR);
		trimmed = ft_strtrim(game->map_file[i], COMPONENTS);
		if (trimmed && trimmed[0] == '\t')
			err_code = FOUND_TAB_ERR;
		else if (trimmed && trimmed[0])
			err_code = UNRECOGNIZED_ERR;
		free(trimmed);
		if (err_code)
			handle_error(game, i, err_code);
		i++;
	}
	check_starting_pos(game, start);
	normalize_map(game, game->map_file + start);
	check_separate_maps(game);
}

static bool	check_empty_line(t_data *game, int i)
{
	int	j;

	if (!is_empty_line(game->map_file[i]))
		return (false);
	j = i + 1;
	while (game->map_file[j])
	{
		if (!is_empty_line(game->map_file[j]))
			return (true);
		j++;
	}
	return (false);
}

static void	check_starting_pos(t_data *game, int start)
{
	int		i;
	int		count;

	count = 0;
	i = start;
	while (game->map_file[i])
	{
		count += count_chars(game->map_file[i], "NEWS");
		i++;
	}
	if (!count)
		exit_code(game, NO_START_POS_ERR, NULL);
	if (count > 1)
		exit_code(game, MULTI_START_ERR, NULL);
}

static void	check_separate_maps(t_data *game)
{
	int		i;
	bool	flag;
	char	**temp_map;

	temp_map = copy_array(game->map);
	if (temp_map == NULL)
		exit_code(game, MALLOC_ERR, NULL);
	i = 0;
	while (temp_map[0][i] == ' ')
		i++;
	flood_fill(temp_map, i, 0);
	flag = false;
	i = -1;
	while (temp_map[++i])
		if (count_chars(temp_map[i], "01NEWS"))
			flag = true;
	free_2d(temp_map);
	if (flag)
		exit_code(game, SEPRT_MAPS_ERR, NULL);
}

static void	flood_fill(char **map, int i, int j)
{
	map[j][i] = ' ';
	if (j > 0 && map[j - 1][i] != ' ')
		flood_fill(map, i, j - 1);
	if (map[j + 1] && map[j + 1][i] != ' ')
		flood_fill(map, i, j + 1);
	if (i > 0 && map[j][i - 1] != ' ')
		flood_fill(map, i - 1, j);
	if (map[j][i + 1] && map[j][i + 1] != ' ')
		flood_fill(map, i + 1, j);
}
