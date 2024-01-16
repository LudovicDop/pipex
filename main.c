/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ludovicdoppler <ludovicdoppler@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 17:03:41 by ldoppler          #+#    #+#             */
/*   Updated: 2024/01/15 16:23:28 by ludovicdopp      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <fcntl.h>

/*
fd[0] - read
fd[1] - write
*/
int	main(int argc, char **argv)
{
	int	fd[2];
	int	id;

	if(pipe(fd) == -1)
		perror("pipe");
	id = fork();
	if (id == 0)
	{
		close(fd[0]);
		int x = 5;
		write(fd[1], &x, sizeof(int));
		close(fd[1]);
		
	}
	else
	{
		int y;
		close(fd[1]);
		read(fd[0], &y, sizeof(int));
		printf("%d\n",y);
		close(fd[0]);
	}
	return (0);
}
