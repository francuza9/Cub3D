/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_textures_3.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtskitis <gtskitis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 23:26:26 by jwadie-a          #+#    #+#             */
/*   Updated: 2024/05/26 02:35:53 by gtskitis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

static char	**check_format(char *format, int *err_code);
static bool	check_rgb(char **rgb, int *err_code);
static int	get_rgb(char **rgb);

int	parse_color(char *line, int *err_code)
{
	char	*trimmed;
	char	**split;

	if (!line[0])
	{
		*err_code = ID_NOT_SPEC_ERR;
		return (0);
	}
	trimmed = ft_strtrim(line, SPACE_CHARS);
	split = check_format(trimmed, err_code);
	if (split == NULL)
		return (0);
	if (check_rgb(split, err_code))
		return (0);
	return (get_rgb(split));
}

static char	**check_format(char *format, int *err_code)
{
	char	**split;

	if (count_chars(format, ",") != 2)
	{
		free(format);
		*err_code = BAD_COLOR_ERR;
		return (NULL);
	}
	split = ft_split(format, ',');
	free(format);
	if (!split)
	{
		*err_code = MALLOC_ERR;
		return (NULL);
	}
	if (!split[0] || !split[1] || !split[2] || split[3])
	{
		*err_code = BAD_COLOR_ERR;
		free_2d(split);
		return (NULL);
	}
	split = trim_array(split);
	if (!split)
		*err_code = MALLOC_ERR;
	return (split);
}

static bool	check_rgb(char **rgb, int *err_code)
{
	int		i;
	bool	flag;

	flag = false;
	i = 0;
	while (rgb[i])
	{
		if (!is_numerical(rgb[i]))
			flag = true;
		else if (ft_strlen(rgb[i]) > 3)
			flag = true;
		else if (ft_atoi(rgb[i]) > 255)
			flag = true;
		if (flag)
		{
			*err_code = BAD_COLOR_ERR;
			free_2d(rgb);
			return (true);
		}
		i++;
	}
	return (false);
}

static int	get_rgb(char **rgb)
{
	int	color;
	int	r;
	int	g;
	int	b;

	r = ft_atoi(rgb[0]);
	g = ft_atoi(rgb[1]);
	b = ft_atoi(rgb[2]);
	color = r << 16 | g << 8 | b;
	free_2d(rgb);
	return (color);
}
