/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldoppler <ldoppler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 12:16:13 by ldoppler          #+#    #+#             */
/*   Updated: 2024/01/22 13:02:00 by ldoppler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*ft_strchr(char *s, int c)
{
	int				i;
	unsigned char	*ret;

	ret = (unsigned char *)s;
	i = 0;
	while (ret[i] != '\0' && ret[i] != (char)c)
	{
		i++;
	}
	if (ret[i] == (char)c)
	{
		return ((char *)(ret + i));
	}
	return (s);
}
