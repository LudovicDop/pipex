/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldoppler <ldoppler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 17:03:41 by ldoppler          #+#    #+#             */
/*   Updated: 2024/01/12 17:44:09 by ldoppler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char **argv)
{
	if (argc == 3)
	{
        execv(argv[1], argv);
        perror("execv");
	}
	else
	{
		ft_putstr_fd("❌ Too many or not enough arguments ❌\n", 2);
	}
}
