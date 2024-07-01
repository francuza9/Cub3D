/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_layer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtskitis <gtskitis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 01:11:18 by jwadie-a          #+#    #+#             */
/*   Updated: 2024/05/26 20:54:52 by gtskitis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

static char	**create_bigger_map(t_data *game, int width, int height);
static void	copy_line(char *new, char *old, int len);

void	add_layer(t_data *game)
{
	char	**new_map;

	new_map = create_bigger_map(game, game->map_width, game->map_height);
	if (!new_map)
		exit_code(game, MALLOC_ERR, NULL);
	free_2d(game->map);
	game->map = new_map;
	game->map_height += 4;
	game->map_width += 4;
}

static void	copy_line(char *new, char *old, int len)
{
	int	i;

	i = 0;
	while (i < len)
	{
		new[i + 2] = old[i];
		i++;
	}
}

static char	**create_bigger_map(t_data *game, int width, int height)
{
	char	**new_map;
	int		i;

	new_map = ft_calloc(height + 5, sizeof(char *));
	if (!new_map)
		return (NULL);
	i = 0;
	while (i < (height + 4))
	{
		new_map[i] = ft_calloc(width + 5, sizeof(char));
		if (!new_map[i])
			return (free_2d(new_map));
		ft_memset(new_map[i], ' ', width + 4);
		if (i >= 2 && i < (height + 2))
			copy_line(new_map[i], game->map[i - 2], width);
		i++;
	}
	return (new_map);
}
