/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtskitis <gtskitis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 21:02:33 by gtskitis          #+#    #+#             */
/*   Updated: 2024/05/26 02:35:53 by gtskitis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

void	rotate_p(t_data *game, int i)
{
	if (i == 1)
	{
		game->p_angle += ROT_SPEED;
		if (game->p_angle > 2 * M_PI)
			game->p_angle -= 2 * M_PI;
	}
	else
	{
		game->p_angle -= ROT_SPEED;
		if (game->p_angle < 0)
			game->p_angle += 2 * M_PI;
	}
}

void	assign_movement(t_data *game, double x, double y)
{
	int	map_x;
	int	map_y;
	int	new_x;
	int	new_y;

	new_x = roundf(game->pix_p_x + x);
	new_y = roundf(game->pix_p_y + y);
	map_x = (new_x / TILE_LEN);
	map_y = (new_y / TILE_LEN);
	if (game->map[map_y][map_x] != '1' &&
		(game->map[map_y][game->pix_p_x / TILE_LEN] != '1' &&
		game->map[game->pix_p_y / TILE_LEN][map_x] != '1'))
	{
		game->pix_p_x = new_x;
		game->pix_p_y = new_y;
	}
}

void	choose_rotation(t_data *game)
{
	if (game->l_r == 1)
		rotate_p(game, 1);
	else if (game->l_r == -1)
		rotate_p(game, 0);
}

void	move_p(t_data *game, double x, double y)
{
	if (game->a_d == 1)
	{
		x = -sin(game->p_angle) * P_SPEED;
		y = cos(game->p_angle) * P_SPEED;
	}
	else if (game->a_d == -1)
	{
		x = sin(game->p_angle) * P_SPEED;
		y = -cos(game->p_angle) * P_SPEED;
	}
	else if (game->w_s == 1)
	{
		x = cos(game->p_angle) * P_SPEED;
		y = sin(game->p_angle) * P_SPEED;
	}
	else if (game->w_s == -1)
	{
		x = -cos(game->p_angle) * P_SPEED;
		y = -sin(game->p_angle) * P_SPEED;
	}
	if (x || y)
		assign_movement(game, x, y);
}
