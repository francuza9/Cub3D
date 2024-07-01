/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwadie-a <jwadie-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 21:30:25 by gtskitis          #+#    #+#             */
/*   Updated: 2024/05/31 20:02:13 by jwadie-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

void	calc_values(t_data *game)
{
	game->pix_p_x = (game->map_p_x * TILE_LEN) + TILE_LEN / 2;
	game->pix_p_y = (game->map_p_y * TILE_LEN) + TILE_LEN / 2;
	game->fov_rad = (M_PI * FOV) / 180;
	game->a_d = 0;
	game->w_s = 0;
	game->l_r = 0;
}

void	init_data(t_data *game)
{
	int	i;

	game->map_file = NULL;
	game->map = NULL;
	game->counter = 0;
	i = 0;
	while (i < 4 * NUM_OF_SPRITES)
	{
		game->texture_paths[i] = NULL;
		game->xpm_img[i].mlx_img = NULL;
		i++;
	}
	game->mlx = NULL;
	game->win = NULL;
	game->img[0].mlx_img = NULL;
	game->img[1].mlx_img = NULL;
	game->pointer_xpm.mlx_img = NULL;
	game->map_height = 0;
	game->map_width = 0;
	game->disp_map = false;
}

void	mlx_and_window_init(t_data *game)
{
	game->mlx = mlx_init();
	if (!game->mlx)
		exit_code(game, MLX_INIT_FAIL_ERR, NULL);
	game->win = mlx_new_window(game->mlx, S_WIDTH, S_HEIGHT, "CUB3D");
	if (!game->win)
	{
		mlx_destroy_display(game->mlx);
		free(game->mlx);
		exit_code(game, MLX_INIT_FAIL_ERR, NULL);
	}
}

void	load_mini_imgs(t_data *game)
{
	int	width;
	int	height;

	if (!BONUS)
		return ;
	game->img[1].mlx_img = mlx_new_image(game->mlx,
			game->map_width * MINI_TILE, game->map_height * MINI_TILE);
	if (!game->img[1].mlx_img)
		exit_code(game, MLX_INIT_FAIL_ERR, NULL);
	game->img[1].addr = mlx_get_data_addr(game->img[1].mlx_img,
			&game->img[1].bpp, &game->img[1].line_len, &game->img[1].endian);
	game->pointer_xpm.mlx_img = mlx_xpm_file_to_image(game->mlx, PATH_TO_PTR, \
	&width, &height);
	if (!game->pointer_xpm.mlx_img)
		exit_code(game, TEX_IMPORT_ERR, ft_strdup(PATH_TO_PTR));
	if (width > PTR_SIZE || height > PTR_SIZE)
		exit_code(game, TEX_IMPORT_ERR, ft_strdup(PATH_TO_PTR));
	game->pointer_xpm.addr = mlx_get_data_addr(game->pointer_xpm.mlx_img, \
	&game->pointer_xpm.bpp, &game->pointer_xpm.line_len, \
	&game->pointer_xpm.endian);
}

void	init_mlx(t_data *game)
{
	int	i;
	int	width;
	int	height;

	calc_values(game);
	mlx_and_window_init(game);
	game->img[0].mlx_img = mlx_new_image(game->mlx, S_WIDTH, S_HEIGHT);
	if (!game->img[0].mlx_img)
		exit_code(game, MLX_INIT_FAIL_ERR, NULL);
	game->img[0].addr = mlx_get_data_addr(game->img[0].mlx_img,
			&game->img[0].bpp, &game->img[0].line_len, &game->img[0].endian);
	load_mini_imgs(game);
	i = -1;
	while (++i < 4 * NUM_OF_SPRITES)
	{
		game->xpm_img[i].mlx_img = mlx_xpm_file_to_image(game->mlx, \
		game->texture_paths[i], &width, &height);
		if (!game->xpm_img[i].mlx_img)
			exit_code(game, TEX_IMPORT_ERR, ft_strdup(game->texture_paths[i]));
		if (height != width)
			exit_code(game, TEX_NOT_SQR_ERR, ft_strdup(game->texture_paths[i]));
		game->xpm_img[i].addr = mlx_get_data_addr(game->xpm_img[i].mlx_img, \
		&game->xpm_img[i].bpp, &game->xpm_img[i].line_len, \
		&game->xpm_img[i].endian);
	}
}
