/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thacharo <thacharo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 15:05:50 by thacharo          #+#    #+#             */
/*   Updated: 2026/05/01 12:51:00 by thacharo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	size_t	i;
	char	*word;

	i = 0;
	if (!s)
		return (NULL);
	word = (char *)s;
	while (i < ft_strlen(s) + 1)
	{
		if (word[i] == (char)c)
			return (&word[i]);
		i++;
	}
	return (NULL);
}
