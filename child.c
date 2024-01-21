/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldoppler <ldoppler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 17:38:40 by ldoppler          #+#    #+#             */
/*   Updated: 2024/01/21 16:59:21 by ldoppler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
/*
fd[0] - read
fd[1] - write
*/
void	child_process(int fd, char **args, t_execve *info_execve, int *pipefd)
{
	//char	buf[10000];

	//printf("info_execve->exec_file_path = %s\n",info_execve->exec_file_path);
	close(pipefd[0]);
	dup2(pipefd[1], STDOUT_FILENO);
	close(pipefd[1]);
	execve(info_execve->exec_file_path, args, NULL);
	perror("execve");
	exit(EXIT_SUCCESS);
}
