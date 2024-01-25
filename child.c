/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldoppler <ldoppler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 17:38:40 by ldoppler          #+#    #+#             */
/*   Updated: 2024/01/25 13:47:21 by ldoppler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	child_process(int fd, char **args, t_execve *info_execve, int *pipefd)
{
	if (access(info_execve->file1, F_OK) != 0)
	{
		free_char_array(info_execve->args_bis);
		free_char_array(info_execve->args);
		free_info_execve(info_execve);
	}
	close(pipefd[0]);
	dup2(pipefd[1], STDOUT_FILENO);
	close(pipefd[1]);
	dup2(fd, STDIN_FILENO);
	close(fd);
	execve(info_execve->exec_file_path, args, info_execve->envp);
	perror("execve");
	exit(EXIT_SUCCESS);
}
