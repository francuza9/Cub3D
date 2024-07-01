/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwadie-a <jwadie-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 20:35:17 by jwadie-a          #+#    #+#             */
/*   Updated: 2024/05/15 19:40:30 by jwadie-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	char	find;

	if (!s)
		return (NULL);
	find = (char)c;
	while (*s != '\0')
	{
		if (*s == find)
			return ((char *)s);
		s++;
	}
	if (find == '\0')
		return ((char *)s);
	return (NULL);
}
