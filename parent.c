/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parent.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldoppler <ldoppler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 17:38:45 by ldoppler          #+#    #+#             */
/*   Updated: 2024/01/29 09:10:02 by ldoppler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	parent_process_bis(int *pipefd, t_execve *info_execve, char **envp,
		int fd)
{
	close(pipefd[0]);
	if (dup2(fd, STDOUT_FILENO) == -1)
	{
		free_everything(info_execve);
		close(fd);
		perror("dup2");
		exit(EXIT_FAILURE);
	}
	close(fd);
	if (-1 == execve(info_execve->exec_file_bis_path, info_execve->args_bis,
			envp))
	{
		printf("ICI\n");
		free_everything(info_execve);
		perror("execve");
		exit(EXIT_FAILURE);
	}
}

void	parent_process(int *pipefd, t_execve *info_execve, char **envp)
{
	int	fd;

	close(pipefd[1]);
	fd = open(info_execve->file2, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
	{
		perror("open");
		free_everything(info_execve);
		close(fd);
		close(info_execve->fd);
		close(pipefd[0]);
		exit(EXIT_FAILURE);
	}
	if (dup2(pipefd[0], STDIN_FILENO) == -1)
	{
		perror("dup2");
		free_everything(info_execve);
		close(fd);
		close(pipefd[0]);
		exit(EXIT_FAILURE);
	}
	parent_process_bis(pipefd, info_execve, envp, fd);
}
