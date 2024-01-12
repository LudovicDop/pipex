/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldoppler <ldoppler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 17:03:41 by ldoppler          #+#    #+#             */
/*   Updated: 2024/01/12 18:40:34 by ldoppler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char **argv)
{
	pid_t	pid;
    char    *execv_args[3];

	pid = fork();
	if (pid == 0)
	{
		printf("Child pid = %d\n",getpid());
	}
	else if (pid > 1)
	{
		printf("Parent pid = %d\n",getpid());
	}
	else
	{
		perror("fork");
	}
	//unlink("./file1");
	if (argc == 3)
	{
        execv_args[0] = argv[1];
        execv_args[1] = argv[2];
        execv_args[2] = NULL;
        execv(execv_args[0], execv_args);
        perror("execv");
	}
	else
	{
		ft_putstr_fd("❌ Too many or not enough arguments ❌\n", 2);
	}
}
