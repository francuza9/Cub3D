/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwadie-a <jwadie-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 21:31:32 by jwadie-a          #+#    #+#             */
/*   Updated: 2024/05/31 20:02:27 by jwadie-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

int	close_game(t_data *game)
{
	free_data(game);
	exit(EXIT_SUCCESS);
}

void	free_data(t_data *game)
{
	int	i;

	free_2d(game->map);
	free_2d(game->map_file);
	i = 0;
	while (i < 4 * NUM_OF_SPRITES)
	{
		free(game->texture_paths[i]);
		if (game->xpm_img[i].mlx_img)
			mlx_destroy_image(game->mlx, game->xpm_img[i].mlx_img);
		i++;
	}
	if (game->img[0].mlx_img)
		mlx_destroy_image(game->mlx, game->img[0].mlx_img);
	if (game->img[1].mlx_img)
		mlx_destroy_image(game->mlx, game->img[1].mlx_img);
	if (game->pointer_xpm.mlx_img)
		mlx_destroy_image(game->mlx, game->pointer_xpm.mlx_img);
	if (game->mlx)
	{
		if (game->win)
			mlx_destroy_window(game->mlx, game->win);
		mlx_destroy_display(game->mlx);
		free(game->mlx);
	}
}

static void	print_err(int err_code)
{
	char	**err_msg;

	err_msg = (char *[NUM_OF_ERR]){MALLOC_ERR_MSG, WRONG_ARGV_MSG, BAD_EXT_MSG, \
	OPEN_FILE_MSG, EMPTY_FILE_MSG, ID_NOT_FOUND_MSG, DUPLICATE_ID_MSG, \
	MISSING_ID_MSG, ID_NOT_SPEC_MSG, SPACE_IN_PATH_MSG, EXT_NOT_XPM_MSG, \
	TOO_FEW_PATH_MSG, TOO_MANY_PATH_MSG, BAD_COLOR_MSG, NO_MAP_MSG, \
	EMPTY_LINE_MSG, UNRECOGNIZED_MSG, FOUND_TAB_MSG, NO_START_POS_MSG, \
	MULTI_START_MSG, TOO_LARGE_MSG, SEPRT_MAPS_MSG, NOT_SURROUND_MSG, \
	TEX_IMPORT_MSG, TEX_NOT_SQR_MSG, MLX_INIT_FAIL_MSG};
	ft_putstr_fd(err_msg[err_code], STDERR_FILENO);
	if (errno)
	{
		ft_putstr_fd(strerror(errno), STDERR_FILENO);
		ft_putchar_fd('\n', STDERR_FILENO);
	}
}

void	exit_code(t_data *game, int err_code, char *err_str)
{
	ft_putstr_fd("Error\n", STDERR_FILENO);
	if (err_str)
		ft_putstr_fd(err_str, STDERR_FILENO);
	print_err(err_code);
	free(err_str);
	free_data(game);
	exit(EXIT_FAILURE);
}

void	handle_error(t_data *game, int i, int err_code)
{
	char	*err_line;
	char	*buffer;
	char	*i_char;

	i_char = ft_itoa(i + 1);
	err_line = ft_strjoin("Line ", i_char);
	free(i_char);
	buffer = ft_strjoin(err_line, ": ");
	free(err_line);
	err_line = ft_strjoin(buffer, game->map_file[i]);
	free(buffer);
	exit_code(game, err_code, err_line);
}
