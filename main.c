/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwadie-a <jwadie-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 20:59:44 by gtskitis          #+#    #+#             */
/*   Updated: 2024/05/25 20:18:57 by jwadie-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(int argc, char **argv)
{
	t_data	game;

	argc--;
	argv++;
	init_data(&game);
	if (argc != 1)
		exit_code(&game, WRONG_ARGV_ERR, NULL);
	parse_cub_file(&game, argv[0]);
	init_mlx(&game);
	hook_mlx(&game);
	mlx_loop(game.mlx);
	free_data(&game);
	return (0);
}
