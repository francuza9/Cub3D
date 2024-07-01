/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map_3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtskitis <gtskitis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 03:24:59 by jwadie-a          #+#    #+#             */
/*   Updated: 2024/05/26 20:55:35 by gtskitis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

static void	flood_fill(t_data *game, int i, int j);
static void	replace_spaces(t_data *game);
static void	check_zeros(t_data *game);

void	check_borders(t_data *game)
{
	if (BONUS)
	{
		add_layer(game);
		flood_fill(game, 0, 0);
	}
	else
		check_zeros(game);
	replace_spaces(game);
}

static void	flood_fill(t_data *game, int i, int j)
{
	game->map[j][i] = 'x';
	if (i > 0 && ft_strchr("0NEWS", game->map[j][i - 1]))
		exit_code(game, NOT_SURROUND_ERR, NULL);
	if (j > 0 && ft_strchr("0NEWS", game->map[j - 1][i]))
		exit_code(game, NOT_SURROUND_ERR, NULL);
	if (game->map[j][i + 1] && ft_strchr("0NEWS", game->map[j][i + 1]))
		exit_code(game, NOT_SURROUND_ERR, NULL);
	if (game->map[j + 1] && ft_strchr("0NEWS", game->map[j + 1][i]))
		exit_code(game, NOT_SURROUND_ERR, NULL);
	if (i > 0 && game->map[j][i - 1] == ' ')
		flood_fill(game, i - 1, j);
	if (j > 0 && game->map[j - 1][i] == ' ')
		flood_fill(game, i, j - 1);
	if (game->map[j][i + 1] == ' ')
		flood_fill(game, i + 1, j);
	if (game->map[j + 1] && game->map[j + 1][i] == ' ')
		flood_fill(game, i, j + 1);
}

static void	check_zeros(t_data *game)
{
	int	i;
	int	j;

	j = 0;
	while (game->map[j])
	{
		i = 0;
		while (game->map[j][i])
		{
			if (ft_strchr("0NEWS", game->map[j][i]))
			{
				if (i == 0 || i == (game->map_width - 1) || \
				j == 0 || j == (game->map_height - 1))
					exit_code(game, NOT_SURROUND_ERR, NULL);
				if (game->map[j][i + 1] == ' ' || game->map[j][i - 1] == ' ' || \
				game->map[j - 1][i] == ' ' || game->map[j + 1][i] == ' ')
					exit_code(game, NOT_SURROUND_ERR, NULL);
			}
			i++;
		}
		j++;
	}
}

static void	replace_spaces(t_data *game)
{
	int	i;
	int	j;

	j = 0;
	while (game->map[j])
	{
		i = 0;
		while (game->map[j][i])
		{
			if (BONUS)
			{
				if (game->map[j][i] == 'x')
					game->map[j][i] = '1';
				else if (game->map[j][i] == ' ')
					game->map[j][i] = '0';
			}
			else if (game->map[j][i] == ' ')
				game->map[j][i] = '1';
			i++;
		}
		j++;
	}
}
