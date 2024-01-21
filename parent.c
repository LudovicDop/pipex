/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parent.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldoppler <ldoppler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 17:38:45 by ldoppler          #+#    #+#             */
/*   Updated: 2024/01/18 19:53:10 by ldoppler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void parent_process(int *pipefd, t_execve *info_execve)
{
	int fd = open(info_execve->file2, O_WRONLY);
    close(pipefd[1]); // Close the unused write end
	dup2(pipefd[0], fd);
    close(pipefd[0]); // Close the read end now that we're done with it
	execve(info_execve->exec_file_bis_path, info_execve->args_bis, NULL);
    wait(NULL); // Wait for the child process to finish
}
