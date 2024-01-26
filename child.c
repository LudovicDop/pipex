/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldoppler <ldoppler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 17:38:40 by ldoppler          #+#    #+#             */
/*   Updated: 2024/01/26 10:58:14 by ldoppler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	child_process(int fd, char **args, t_execve *info_execve, int *pipefd)
{
	if (access(info_execve->file1, F_OK) != 0)
	{
		close(info_execve->fd);
		free_char_array(info_execve->args_bis);
		free_char_array(info_execve->envp);
		free_char_array(info_execve->args);
		free_info_execve(info_execve);
	}
	close(pipefd[0]);
	dup2(pipefd[1], STDOUT_FILENO);
	close(pipefd[1]);
	dup2(fd, STDIN_FILENO);
	close(fd);
	if (execve(info_execve->exec_file_path, args, info_execve->envp) < 0)
	{
		close(info_execve->fd);
		free_char_array(info_execve->args_bis);
		free_char_array(info_execve->envp);
		free_char_array(info_execve->args);
		free_info_execve(info_execve);
		perror("execve");
		exit(EXIT_FAILURE);
	}
	close(info_execve->fd);
	exit(EXIT_SUCCESS);
}
