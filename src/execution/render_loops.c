/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_loops.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtskitis <gtskitis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 21:02:23 by gtskitis          #+#    #+#             */
/*   Updated: 2024/05/27 02:55:04 by gtskitis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

t_img	*calc_color(t_data *game, int x)
{
	int	offset;

	game->ray_angle = angle_lim(game->ray_angle);
	offset = (game->counter / RENDER_SPEED) % NUM_OF_SPRITES;
	if (!x)
	{
		if (game->ray_angle > M_PI / 2 && game->ray_angle < 3 * (M_PI / 2))
			return (&game->xpm_img[EAST_WALL * NUM_OF_SPRITES + offset]);
		else
			return (&game->xpm_img[WEST_WALL * NUM_OF_SPRITES + offset]);
	}
	if (game->ray_angle > 0 && game->ray_angle < M_PI)
		return (&game->xpm_img[NORTH_WALL * NUM_OF_SPRITES + offset]);
	else
		return (&game->xpm_img[SOUTH_WALL * NUM_OF_SPRITES + offset]);
}

double	get_x_side(t_data *game, t_img *ptr)
{
	double	x;

	if (game->wall_side_flag)
		x = (int)fmodf((game->hor_x
					* ((ptr->line_len / 4) / TILE_LEN)), ptr->line_len / 4);
	else
		x = (int)fmodf((game->ver_y
					* ((ptr->line_len / 4) / TILE_LEN)), ptr->line_len / 4);
	return (x);
}

void	render_wall(t_data *game, int top_p, int bot_p, double wall_height)
{
	t_img		*ptr;
	double		x;
	double		factor;

	ptr = calc_color(game, game->wall_side_flag);
	factor = (double)(ptr->line_len / 4) / wall_height;
	x = get_x_side(game, ptr);
	game->y = (top_p - (S_HEIGHT / 2) + (wall_height / 2)) * factor;
	if (game->y < 0)
		game->y = 0;
	while (top_p < bot_p)
	{
		put_pix_wall(game, ptr, top_p, x);
		game->y += factor;
		top_p++;
	}
}

void	render_rest(t_data *game, int ray, int bot_pixel, int top_pixel)
{
	int	i;

	i = bot_pixel;
	while (i < S_HEIGHT)
	{
		img_pix_put(&game->img[0], ray * 4, i, game->floor_clr);
		i++;
	}
	i = 0;
	while (i < top_pixel)
	{
		img_pix_put(&game->img[0], ray * 4, i, game->ceiling_clr);
		i++;
	}
}

void	render_ray(t_data *game, int ray)
{
	double	wall_height;
	double	bot_pixel;
	double	top_pixel;

	game->ray_dist *= cos(angle_lim(game->ray_angle - game->p_angle));
	wall_height = ((TILE_LEN / game->ray_dist)
			* ((S_WIDTH / 2) / tan(game->fov_rad / 2)));
	bot_pixel = (S_HEIGHT / 2) + (wall_height / 2);
	top_pixel = (S_HEIGHT / 2) - (wall_height / 2);
	if (bot_pixel > S_HEIGHT)
		bot_pixel = S_HEIGHT;
	if (top_pixel < 0)
		top_pixel = 0;
	game->index = ray;
	render_rest(game, ray, top_pixel, bot_pixel);
	render_wall(game, top_pixel, bot_pixel, wall_height);
}
