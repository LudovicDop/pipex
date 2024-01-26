/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parent.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldoppler <ldoppler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 17:38:45 by ldoppler          #+#    #+#             */
/*   Updated: 2024/01/26 11:30:52 by ldoppler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	parent_process_bis(int *pipefd, t_execve *info_execve, char **envp,
		int fd)
{
	close(pipefd[0]);
	if (dup2(fd, STDOUT_FILENO) == -1)
	{
		free_char_array(info_execve->args_bis);
		free_char_array(info_execve->args);
		free_info_execve(info_execve);
		perror("dup2");
		exit(EXIT_FAILURE);
	}
	close(fd);
	if (-1 == execve(info_execve->exec_file_bis_path, info_execve->args_bis,
			envp))
	{
		free_char_array(info_execve->args_bis);
		free_char_array(info_execve->envp);
		free_char_array(info_execve->args);
		free_info_execve(info_execve);
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
		free_char_array(info_execve->envp);
		free_char_array(info_execve->args_bis);
		free_char_array(info_execve->args);
		free_info_execve(info_execve);
		close(fd);
		close(pipefd[0]);
		exit(EXIT_FAILURE);
	}
	if (dup2(pipefd[0], STDIN_FILENO) == -1)
	{
		free_char_array(info_execve->args_bis);
		free_char_array(info_execve->args);
		free_info_execve(info_execve);
		perror("dup2");
		exit(EXIT_FAILURE);
	}
	parent_process_bis(pipefd, info_execve, envp, fd);
}
