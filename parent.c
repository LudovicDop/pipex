/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parent.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldoppler <ldoppler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 17:38:45 by ldoppler          #+#    #+#             */
/*   Updated: 2024/01/24 14:14:34 by ldoppler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	parent_process_bis(int *pipefd, t_execve *info_execve, char **envp,
		int fd)
{
	if (dup2(fd, STDOUT_FILENO) == -1)
	{
		perror("dup2");
		exit(EXIT_FAILURE);
	}
	close(fd);
	if (execve(info_execve->exec_file_bis_path, info_execve->args_bis, envp)
		== -1)
	{
		perror("execve");
		exit(EXIT_FAILURE);
	}
}

void	parent_process(int *pipefd, t_execve *info_execve, char **envp)
{
	int		wstatus;
	pid_t	ret;
	int		fd;

	ret = waitpid(0, &wstatus, 0);
	wstatus = 0;
	close(pipefd[1]);
	fd = open(info_execve->file2, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
	{
		perror("open");
		exit(EXIT_FAILURE);
	}
	if (dup2(pipefd[0], STDIN_FILENO) == -1)
	{
		perror("dup2");
		exit(EXIT_FAILURE);
	}
	close(pipefd[0]);
	parent_process_bis(pipefd, info_execve, envp, fd);
}
