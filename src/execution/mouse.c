/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtskitis <gtskitis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 21:02:36 by gtskitis          #+#    #+#             */
/*   Updated: 2024/05/26 04:13:56 by gtskitis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

int	mouse_move(int mouse_x, int mouse_y, t_data *game)
{
	(void)mouse_y;
	if (BONUS)
	{
		mlx_mouse_move(game->mlx, game->win, S_WIDTH / 2, S_HEIGHT / 2);
		if (mouse_x < S_WIDTH / 2)
			game->p_angle -= 0.015;
		else if (mouse_x > S_WIDTH / 2)
			game->p_angle += 0.015;
		if (game->p_angle > 2 * M_PI)
			game->p_angle -= 2 * M_PI;
		else if (game->p_angle < 0)
			game->p_angle += 2 * M_PI;
	}
	return (0);
}
