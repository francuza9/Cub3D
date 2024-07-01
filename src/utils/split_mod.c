/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_mod.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtskitis <gtskitis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 19:55:03 by jwadie-a          #+#    #+#             */
/*   Updated: 2024/05/26 02:35:53 by gtskitis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

static char	**allocate_word(char **arr, char *s, int len);
static char	**free_arrays(char **arr, char *word);

char	**split_mod(char const *s, char c)
{
	char	**arr;
	char	*i;

	arr = malloc(sizeof(char *));
	if (s == NULL || arr == NULL)
		return (NULL);
	arr[0] = NULL;
	while (*s != '\0')
	{
		i = (char *)s;
		while (*s != c && *s != '\0')
			s++;
		arr = allocate_word(arr, i, (int)(s - i));
		if (arr == NULL)
			return (NULL);
		if (*s == c)
			s++;
	}
	return (arr);
}

static char	**free_arrays(char **arr, char *word)
{
	size_t	i;

	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	if (word != NULL)
		free(word);
	free(arr);
	return (NULL);
}

static char	**allocate_word(char **arr, char *s, int len)
{
	int		i;
	char	*word;
	char	**new;

	word = ft_calloc(sizeof(char), len + 1);
	if (word == NULL)
		return (free_arrays(arr, NULL));
	ft_strlcpy(word, s, len + 1);
	i = 0;
	while (arr[i])
		i++;
	new = malloc(sizeof(char *) * (i + 2));
	if (new == NULL)
		return (free_arrays(arr, word));
	i = 0;
	while (arr[i])
	{
		new[i] = arr[i];
		i++;
	}
	new[i] = word;
	new[i + 1] = NULL;
	free(arr);
	return (new);
}
