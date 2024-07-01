/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwadie-a <jwadie-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 00:58:56 by gtskitis          #+#    #+#             */
/*   Updated: 2024/05/30 17:42:23 by jwadie-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

void	draw_square(t_data *game, int x, int y, int color)
{
	int	i;
	int	j;

	j = 0;
	while (j < MINI_TILE)
	{
		i = 0;
		while (i < MINI_TILE)
		{
			if (i == 0 || i == MINI_TILE - 1 || j == 0 || j == MINI_TILE - 1)
				img_pix_put(&game->img[1], (MINI_TILE * x + i) * 4,
					j + (MINI_TILE * y), create_trgb(0, 220, 220, 220));
			else
				img_pix_put(&game->img[1], (MINI_TILE * x + i) * 4,
					j + (MINI_TILE * y), color);
			i++;
		}
		j++;
	}
}

void	fill_mini_img(t_data *game, int x, int y)
{
	while (y < game->map_height)
	{
		x = 0;
		while (x < game->map_width)
		{
			if (game->map[y][x] == '0')
				draw_square(game, x, y, create_trgb(0, 250, 255, 100));
			else
				draw_square(game, x, y, create_trgb(0, 102, 102, 0));
			x++;
		}
		y++;
	}
}

void	draw_frame(t_data *game)
{
	int	x;
	int	y;

	y = 0;
	while (y < 200)
	{
		x = 0;
		while (x < 200)
		{
			if (y < 5 || y > 195 || x < 5 || x > 195)
				img_pix_put(&game->img[0], x * 4,
					y, create_trgb(0, 139, 69, 19));
			x++;
		}
		y++;
	}
}
