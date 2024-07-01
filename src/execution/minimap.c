/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwadie-a <jwadie-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 00:48:39 by gtskitis          #+#    #+#             */
/*   Updated: 2024/05/30 18:46:36 by jwadie-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

void	get_mini_pos(t_data *game, int *x, int *y)
{
	*x = (int)((float)game->pix_p_x * ((float)MINI_TILE
				/ (float)TILE_LEN)) - (MINI_TILE * 2 + (MINI_TILE / 2));
	*y = (int)((float)game->pix_p_y * ((float)MINI_TILE
				/ (float)TILE_LEN)) - (MINI_TILE * 2 + (MINI_TILE / 2));
}

void	copy_mini(t_data *game, int x, int y)
{
	t_img	*ptr;
	char	*arr;
	int		i;
	int		j;

	j = 0;
	ptr = &game->img[1];
	arr = ptr->addr;
	while (j < 5 * MINI_TILE)
	{
		i = 0;
		while (i < 5 * MINI_TILE * 4)
		{
			game->img[0].addr[(j * game->img[0].line_len) + i]
				= ptr->addr[((y + j) * ptr->line_len) + (x * 4) + i];
			i++;
		}
		j++;
	}
	draw_frame(game);
}

void	render_minimap(t_data *game)
{
	int	x;
	int	y;

	fill_mini_img(game, 0, 0);
	get_mini_pos(game, &x, &y);
	copy_mini(game, x, y);
}

void	draw_square_map(t_data *game, int x, int y, int color)
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
				img_pix_put(&game->img[0], (MINI_TILE * x + i)
					* 4, j + (MINI_TILE * y), create_trgb(0, 220, 220, 220));
			else
				img_pix_put(&game->img[0], (MINI_TILE * x + i)
					* 4, j + (MINI_TILE * y), color);
			i++;
		}
		j++;
	}
}

void	render_map(t_data *game)
{
	int	y;
	int	x;

	y = 2;
	while (game->map[y + 2])
	{
		x = 2;
		while (game->map[y][x + 2])
		{
			if (game->map[y][x] == '0')
				draw_square_map(game, x - 2,
					y - 2, create_trgb(0, 250, 255, 100));
			else
				draw_square_map(game, x - 2,
					y - 2, create_trgb(0, 102, 102, 0));
			x++;
		}
		y++;
	}
}
