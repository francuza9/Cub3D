/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pointer.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwadie-a <jwadie-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 20:17:12 by jwadie-a          #+#    #+#             */
/*   Updated: 2024/05/31 20:01:38 by jwadie-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

t_point	rotate_ptr(t_point old, int origin, double angle)
{
	t_point	new;

	new.x = -((origin - old.x) * cos(angle) - (origin - old.y) * sin(angle));
	new.y = -((origin - old.x) * sin(angle) + (origin - old.y) * cos(angle));
	return (new);
}

void	render_pointer(t_data *game, int x_0, int y_0)
{
	t_img	img;
	int		*px;
	t_point	old;
	t_point	new;

	img = game->pointer_xpm;
	old.y = 0;
	while (old.y < PTR_SIZE)
	{
		old.x = 0;
		while (old.x < PTR_SIZE)
		{
			px = (int *)(img.addr + (old.y
						* img.line_len + old.x * (img.bpp / 8)));
			if (*px)
			{
				new = rotate_ptr(old, PTR_SIZE / 2, game->p_angle);
				img_pix_put(&game->img[0], (x_0 + new.x) * 4, \
				(y_0 + new.y), *px);
			}
			old.x++;
		}
		old.y++;
	}
}
