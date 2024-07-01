/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtskitis <gtskitis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 21:02:28 by gtskitis          #+#    #+#             */
/*   Updated: 2024/05/26 02:35:53 by gtskitis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

float	angle_lim(float angle)
{
	if (angle < 0)
		angle += (2 * M_PI);
	if (angle > (2 * M_PI))
		angle -= (2 * M_PI);
	return (angle);
}

bool	touch_nothing(t_data *game, float r_x, float r_y)
{
	int	x;
	int	y;

	if (r_x < 0 || r_y < 0)
		return (false);
	x = floor(r_x / TILE_LEN);
	y = floor(r_y / TILE_LEN);
	if (x >= game->map_width || y >= game->map_height)
		return (false);
	if (game->map[y] && x < (int)ft_strlen(game->map[y]) && x >= 0)
	{
		if ((game->is_hor && game->ray_angle > 0
				&& game->ray_angle < M_PI && game->map[y][x] == '1')
			|| (game->is_hor && game->ray_angle > M_PI
			&& game->map[y - 1][x] == '1')
			|| (!game->is_hor && game->ray_angle > M_PI / 2
			&& game->ray_angle < 3 * M_PI / 2 && game->map[y][x - 1] == '1')
			|| (!game->is_hor && (game->ray_angle < M_PI / 2
			|| game->ray_angle > 3 * M_PI / 2) && game->map[y][x] == '1'))
			return (false);
	}
	return (true);
}

float	get_hor_len(t_data *game, float angle, float step_x, float step_y)
{
	float	delta_y;
	float	delta_x;

	if (angle > 0 && angle < M_PI)
		step_y = TILE_LEN;
	else
		step_y = -(TILE_LEN);
	step_x = step_y / tan(angle);
	if (angle > 0 && angle < M_PI)
		delta_y = TILE_LEN - game->pix_p_y % TILE_LEN;
	else
		delta_y = -(game->pix_p_y % TILE_LEN);
	delta_x = (delta_y * step_x) / step_y;
	game->hor_y = game->pix_p_y + delta_y;
	game->hor_y = (game->hor_y / TILE_LEN) * TILE_LEN;
	game->hor_x = game->pix_p_x + delta_x;
	game->is_hor = true;
	while (touch_nothing(game, game->hor_x, game->hor_y))
	{
		game->hor_x += step_x;
		game->hor_y += step_y;
	}
	return (sqrt(pow(game->hor_x - game->pix_p_x, 2)
			+ pow(game->hor_y - game->pix_p_y, 2)));
}

float	get_ver_len(t_data *game, float angle, float step_x, float step_y)
{
	float	delta_y;
	float	delta_x;

	if (angle > M_PI / 2 && angle < 3 * M_PI / 2)
		step_x = -(TILE_LEN);
	else
		step_x = TILE_LEN;
	step_y = step_x * tan(angle);
	if (angle > M_PI / 2 && angle < 3 * M_PI / 2)
		delta_x = -(game->pix_p_x % TILE_LEN);
	else
		delta_x = TILE_LEN - game->pix_p_x % TILE_LEN;
	delta_y = (delta_x * step_y) / step_x;
	game->ver_x = game->pix_p_x + delta_x;
	game->ver_x = (game->ver_x / TILE_LEN) * TILE_LEN;
	game->ver_y = game->pix_p_y + delta_y;
	game->is_hor = false;
	while (touch_nothing(game, game->ver_x, game->ver_y))
	{
		game->ver_y += step_y;
		game->ver_x += step_x;
	}
	return (sqrt(pow(game->ver_x - game->pix_p_x, 2)
			+ pow(game->ver_y - game->pix_p_y, 2)));
}

void	project_rays(t_data *game)
{
	double	hor_len;
	double	ver_len;
	int		ray;

	ray = 0;
	game->ray_angle = game->p_angle - (game->fov_rad / 2);
	while (ray < S_WIDTH)
	{
		game->wall_side_flag = false;
		hor_len = get_hor_len(game, game->ray_angle, 0, 0);
		ver_len = get_ver_len(game, game->ray_angle, 0, 0);
		if (hor_len > ver_len)
			game->ray_dist = ver_len;
		else
		{
			game->ray_dist = hor_len;
			game->wall_side_flag = true;
		}
		render_ray(game, ray);
		ray++;
		game->ray_angle += (game->fov_rad / S_WIDTH);
	}
}
