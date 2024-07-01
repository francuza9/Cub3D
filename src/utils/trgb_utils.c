/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trgb_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwadie-a <jwadie-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 00:01:35 by gtskitis          #+#    #+#             */
/*   Updated: 2024/05/31 20:02:58 by jwadie-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

int	create_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

void	img_pix_put(t_img *img, int x, int y, int color)
{
	if (x < 0 || y < 0)
		return ;
	img->addr[(y * img->line_len) + x + 3] = (color >> 24) & 0xFF;
	img->addr[(y * img->line_len) + x + 2] = (color >> 16) & 0xFF;
	img->addr[(y * img->line_len) + x + 1] = (color >> 8) & 0xFF;
	img->addr[(y * img->line_len) + x] = color & 0xFF;
}

void	img_pix_put_c(t_img *img, int x, int y, char color)
{
	if (x < 0 || y < 0 || y > S_HEIGHT || x > S_WIDTH * 4)
		return ;
	img->addr[(y * img->line_len) + x + 3] = color;
	img->addr[(y * img->line_len) + x + 2] = color;
	img->addr[(y * img->line_len) + x + 1] = color;
	img->addr[(y * img->line_len) + x] = color;
}

void	put_pix_wall(t_data *game, t_img *ptr, int top_p, int x)
{
	game->img[0].addr[((int)top_p * game->img[0].line_len)
		+(int)(game->index * 4)
		+ 3] = ptr->addr[(int)game->y * ptr->line_len + (int)(x * 4) + 3];
	game->img[0].addr[((int)top_p * game->img[0].line_len)
		+(int)(game->index * 4)
		+ 2] = ptr->addr[(int)game->y * ptr->line_len + (int)(x * 4) + 2];
	game->img[0].addr[((int)top_p * game->img[0].line_len)
		+(int)(game->index * 4)
		+ 1] = ptr->addr[(int)game->y * ptr->line_len + (int)(x * 4) + 1];
	game->img[0].addr[((int)top_p * game->img[0].line_len)
		+(int)(game->index * 4)
		+ 0] = ptr->addr[(int)game->y * ptr->line_len + (int)(x * 4) + 0];
}
