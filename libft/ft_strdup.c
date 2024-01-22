/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldoppler <ldoppler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 14:00:05 by ldoppler          #+#    #+#             */
/*   Updated: 2024/01/22 13:10:36 by ldoppler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	char	*ret;
	int		i;

	i = 0;
	if (!s)
		return (NULL);
	while (s[i] != '\0')
	{
		i++;
	}
	ret = malloc(i * sizeof(char) + 1);
	if (!ret)
		return (NULL);
	i = 0;
	while (s[i] != '\0')
	{
		ret[i] = s[i];
		i++;
	}
	ret[i] = '\0';
	return (ret);
}
