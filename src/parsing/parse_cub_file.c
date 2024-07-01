/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cub_file.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtskitis <gtskitis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 19:58:44 by jwadie-a          #+#    #+#             */
/*   Updated: 2024/05/26 02:35:53 by gtskitis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

static void		read_map_file(t_data *game, char *filename);
static size_t	get_file_size(t_data *game, char *filename);

void	parse_cub_file(t_data *game, char *argv)
{
	char	*filename;
	char	*ext;
	int		i;

	filename = ft_strtrim(argv, SPACE_CHARS);
	if (!filename)
		exit_code(game, MALLOC_ERR, NULL);
	ext = ft_strrchr(filename, '.');
	if (ft_strlen(ext) != 4 || ft_strncmp(ext, ".cub", 4))
		exit_code(game, BAD_EXT_ERR, filename);
	read_map_file(game, filename);
	free(filename);
	if (!game->map_file)
		exit_code(game, MALLOC_ERR, NULL);
	i = check_texture_ids(game);
	import_textures(game, i);
	check_map(game, i);
	check_borders(game);
	get_player_pos(game);
}

static void	read_map_file(t_data *game, char *filename)
{
	int		fd;
	size_t	len;
	char	*line;
	char	*map_line;

	len = get_file_size(game, filename);
	map_line = ft_calloc(sizeof(char), len + 1);
	if (!map_line)
		return ;
	fd = open(filename, O_RDONLY);
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		ft_strlcat(map_line, line, ft_strlen(map_line) + ft_strlen(line) + 1);
		free(line);
	}
	close(fd);
	game->map_file = split_mod(map_line, '\n');
	free(map_line);
}

static size_t	get_file_size(t_data *game, char *filename)
{
	char	*line;
	int		fd;
	size_t	len;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
		exit_code(game, OPEN_FILE_ERR, filename);
	len = 0;
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		len += ft_strlen(line);
		free(line);
	}
	close(fd);
	if (!len)
		exit_code(game, EMPTY_FILE_ERR, filename);
	return (len);
}
