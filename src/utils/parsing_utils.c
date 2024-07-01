/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtskitis <gtskitis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 01:37:06 by jwadie-a          #+#    #+#             */
/*   Updated: 2024/05/26 02:35:53 by gtskitis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

bool	is_empty_line(char *line)
{
	bool	is_empty;
	char	*trimmed;

	trimmed = ft_strtrim(line, SPACE_CHARS);
	if (trimmed == NULL)
		return (false);
	if (trimmed[0])
		is_empty = false;
	else
		is_empty = true;
	free(trimmed);
	return (is_empty);
}

char	**trim_array(char **array)
{
	int		i;
	char	*buffer;

	if (!array)
		return (NULL);
	i = 0;
	while (array[i])
	{
		buffer = ft_strtrim(array[i], SPACE_CHARS);
		if (!buffer)
		{
			free_2d(array);
			return (NULL);
		}
		free(array[i]);
		array[i] = buffer;
		i++;
	}
	return (array);
}

int	count_chars(char *s, char *c)
{
	int	count;
	int	i;

	if (!s)
		return (0);
	count = 0;
	while (*s)
	{
		i = 0;
		while (c[i])
		{
			if (*s == c[i])
			{
				count++;
				break ;
			}
			i++;
		}
		s++;
	}
	return (count);
}

bool	is_numerical(char *s)
{
	if (!s)
		return (false);
	if (*s == '\0')
		return (false);
	if (*s == '0' && *(s + 1))
		return (false);
	while (*s)
	{
		if (!ft_isdigit(*s))
			return (false);
		s++;
	}
	return (true);
}

char	**copy_array(char **array)
{
	int		size;
	int		i;
	char	**new;

	size = 0;
	while (array[size])
		size++;
	new = malloc((size + 1) * sizeof(char *));
	if (!new)
		return (NULL);
	i = 0;
	while (i < size)
	{
		if (is_empty_line(array[i]))
			break ;
		new[i] = ft_strdup(array[i]);
		if (new[i] == NULL)
		{
			free_2d(new);
			return (NULL);
		}
		i++;
	}
	new[i] = NULL;
	return (new);
}
