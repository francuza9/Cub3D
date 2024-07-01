/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_hooks.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwadie-a <jwadie-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 20:59:07 by gtskitis          #+#    #+#             */
/*   Updated: 2024/05/31 20:02:02 by jwadie-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

int	buttons(int key, t_data *game)
{
	if (key == KEY_ESC)
		close_game(game);
	else if (key == KEY_A)
		game->a_d = -1;
	else if (key == KEY_D)
		game->a_d = 1;
	if (key == KEY_W)
		game->w_s = 1;
	else if (key == KEY_S)
		game->w_s = -1;
	else if (key == KEY_LEFT)
		game->l_r = -1;
	else if (key == KEY_RIGHT)
		game->l_r = 1;
	if (key == KEY_M && !game->disp_map)
		game->disp_map = true;
	else if (key == KEY_M)
		game->disp_map = false;
	return (0);
}

int	buttons_rel(int key, t_data *game)
{
	if (key == KEY_A)
		game->a_d = 0;
	else if (key == KEY_D)
		game->a_d = 0;
	if (key == KEY_W)
		game->w_s = 0;
	else if (key == KEY_S)
		game->w_s = 0;
	else if (key == KEY_LEFT)
		game->l_r = 0;
	else if (key == KEY_RIGHT)
		game->l_r = 0;
	return (0);
}

void	hook_mlx(t_data *game)
{
	if (BONUS)
		mlx_mouse_hide(game->mlx, game->win);
	mlx_loop_hook(game->mlx, &execute, game);
	mlx_hook(game->win, KeyPress, KeyPressMask, &buttons, game);
	mlx_hook(game->win, KeyRelease, KeyReleaseMask, &buttons_rel, game);
	mlx_hook(game->win, DestroyNotify, ButtonPressMask, &close_game, game);
	mlx_hook(game->win, MOUSE_HOOK, 1L << 6, &mouse_move, game);
}
