/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwadie-a <jwadie-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 20:58:36 by jwadie-a          #+#    #+#             */
/*   Updated: 2024/05/15 19:37:19 by jwadie-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*check;

	if (!s)
		return (NULL);
	check = (char *)s;
	while (*check != '\0')
		check++;
	if ((char)c == '\0')
		return (check);
	while (check != (s - 1))
	{
		if (*check == (char)c)
			return (check);
		check--;
	}
	return (NULL);
}
