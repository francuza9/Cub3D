/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_execution.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwadie-a <jwadie-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 21:02:07 by gtskitis          #+#    #+#             */
/*   Updated: 2024/05/31 20:01:45 by jwadie-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

static int	get_x(t_data *game);
static int	get_y(t_data *game);

int	execute(t_data *game)
{
	game->counter++;
	if (!game->win)
		return (0);
	move_p(game, 0, 0);
	choose_rotation(game);
	project_rays(game);
	if (BONUS)
	{
		if (game->disp_map && !game->too_large)
		{
			render_map(game);
			render_pointer(game, get_x(game), get_y(game));
		}
		else
		{
			render_minimap(game);
			render_pointer(game, 100, 100);
		}
	}
	mlx_put_image_to_window(game->mlx, game->win, game->img[0].mlx_img, 0, 0);
	return (0);
}

static int	get_x(t_data *game)
{
	return ((int)((float)game->pix_p_x * ((float)MINI_TILE
			/ (float)TILE_LEN) - (MINI_TILE * 2)));
}

static int	get_y(t_data *game)
{
	return ((int)((float)game->pix_p_y * ((float)MINI_TILE
			/ (float)TILE_LEN) - (MINI_TILE * 2)));
}
