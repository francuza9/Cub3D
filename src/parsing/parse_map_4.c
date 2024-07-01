/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map_4.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwadie-a <jwadie-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 19:45:18 by jwadie-a          #+#    #+#             */
/*   Updated: 2024/05/26 19:45:58 by jwadie-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

static void	get_player_angle(t_data *game, char orientation);

void	get_player_pos(t_data *game)
{
	int	i;
	int	j;

	j = 0;
	while (game->map[j])
	{
		i = 0;
		while (game->map[j][i])
		{
			if (ft_strchr("NEWS", game->map[j][i]))
			{
				game->map_p_x = i;
				game->map_p_y = j;
				get_player_angle(game, game->map[j][i]);
				game->map[j][i] = '0';
				break ;
			}
			i++;
		}
		j++;
	}
}

static void	get_player_angle(t_data *game, char orientation)
{
	if (orientation == 'E')
		game->p_angle = 0;
	else if (orientation == 'S')
		game->p_angle = M_PI / 2;
	else if (orientation == 'W')
		game->p_angle = M_PI;
	else if (orientation == 'N')
		game->p_angle = 3 * M_PI / 2;
}
